#include "render.h"
#include <GL/glew.h>
#include <math.h>

#define M_PI 3.14159265358979323846


void init_renderer() {
    // Placeholder: for now we use immediate mode
}

void draw_plate(float x, float y, float z,
                float nx, float ny, float nz,
                float radius) {
    const int segments = 20;
    glPushMatrix();
    glTranslatef(x, y, z);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.6f, 0.8f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);  // center
    for (int i = 0; i <= segments; i++) {
        float theta = (2.0f * M_PI * i) / segments;
        float dx = radius * cosf(theta);
        float dz = radius * sinf(theta);
        glVertex3f(dx, 0.0f, dz);  // flat in XZ
    }
    glEnd();
    glPopMatrix();
}
