
#include "shadowmap.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/glfw.h>
#include "opengp.h"

#include "shadowmap_vshader.h"
#include "shadowmap_fshader.h"


Shadowmap::Shadowmap(unsigned int width, unsigned int height) :
    RenderingContext(width, height) {
}


void Shadowmap::init(GLuint heightMapTexID) {

    /// Common initialization : vertex array and shader programs.
    RenderingContext::init(shadowmap_vshader, shadowmap_fshader);

    /// Create a framebuffer (container for textures, and an optional depth buffer).
    /// The shadow map will be rendered to this FBO instead of the screen.
    glGenFramebuffers(1, &_frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);

    /// Bind the heightmap to texture 0.
    const GLuint heightMapTex = 0;
    glActiveTexture(GL_TEXTURE0+heightMapTex);
    glBindTexture(GL_TEXTURE_2D, heightMapTexID);
    GLuint uniformID = glGetUniformLocation(_programID, "heightMapTex");
    glUniform1i(uniformID, heightMapTex);

    /// Create the texture which will contain the color / depth output
    /// (the actual shadow map) of our shader.
    // Depth texture. Slower than a depth buffer, but we can sample it later in the shader.
    glGenTextures(1, &_shadowMapTexID);
    glBindTexture(GL_TEXTURE_2D, _shadowMapTexID);
    // Depth format is unsigned int. Set it to 16 bits.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

    /// Attach the created texture to the depth attachment point.
    /// The texture becomes the fragment shader first output buffer.
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _shadowMapTexID, 0);

    /// There is only depth (no color) output in the bound framebuffer.
    glDrawBuffer(GL_NONE);

    /// Check that our framebuffer is complete.
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Shadowmap framebuffer not complete." << std::endl;
        exit(EXIT_FAILURE);
    }

}


void Shadowmap::draw(mat4& /*projection*/, mat4& /*modelview*/) const {

    // Common drawing.
    RenderingContext::draw();

    //--- Bind the necessary textures

    //--- Update the content of the uniforms (texture IDs, matrices, ...)

    /// Spot light projection.
    float fieldOfView = 45.0f;
    float aspectRatio = 1.f;
    float nearPlane = 0.1f;
    float farPlane  = 10.f;
    static mat4 projection = Eigen::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);

    /// Light position.
    vec3 lightPosition(3.0, 3.0, 3.0);
    vec3 lightAt(0.0,0.0,0.0);
    vec3 lightUp(0.0,1.0,0.0);
    static mat4 view = Eigen::lookAt(lightPosition, lightAt, lightUp);

    /// Assemble the lightMVP matrix for a spotlight source.
    mat4 lightMVP = projection * view;
    GLuint lightMatrixID = glGetUniformLocation(_programID, "lightMVP");
    glUniformMatrix4fv(lightMatrixID, 1, GL_FALSE, lightMVP.data());



    /// Clear the framebuffer object.
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    /// Render the terrain from light source point of view to FBO.
//    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);

}


void Shadowmap::clean() {
    RenderingContext::clean();
}
