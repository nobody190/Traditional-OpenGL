GLfloat DistancePoint(GLfloat *a, GLfloat *b) {
    return sqrt(pow(a[0] - b[0], 2.0) + pow(a[1] - b[1], 2.0) + pow(a[2] - b[2], 2.0));
}
GLfloat max(GLfloat num1, GLfloat num2){
    return (num1 > num2) ? num1 : num2;
}

GLfloat min(GLfloat num1, GLfloat num2){
    return (num1 > num2) ? num2 : num1;
}
void DrawQuadv(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, materials[material].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[material].diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materials[material].specular);
    glMaterialf(GL_FRONT, GL_SHININESS, materials[material].shininess);

    auto normal = GetNormal(a, b, c);

    glNormal3fv(normal);

    GLfloat factor = 1;

    glPushMatrix();
    glBegin(GL_QUADS);

    if((a[2] == b[2]) && (b[2] == c[2]) && (c[2] == d[2])){
        GLfloat hor_dist = DistancePoint(a, b);
        GLfloat ver_dist = DistancePoint(a, d);
        GLfloat hor_inc = hor_dist / factor;
        GLfloat ver_inc = ver_dist / factor;

        GLfloat hor_count = min(a[0], b[0]);
        GLfloat ver_count = min(a[1], d[1]);

        GLfloat hor_save = hor_count;
        GLfloat ver_save = hor_count;

        //printf("Plano Z\nHorizontal: Distance: %f Count: %f Max: %f\n Vertical Distance: %f Count: %f Max: %f\n", hor_dist, hor_count, a[0], ver_dist, ver_count, a[2]);

        while (hor_count < max(a[0], b[0])) {
            while (ver_count < max(a[1], d[1])) {
                glTexCoord2f((hor_count - hor_save) / hor_dist, (ver_count - ver_save) / ver_dist);
                glVertex3f(hor_count, ver_count, a[2]);

                glTexCoord2f((hor_count - hor_save) / hor_dist, (ver_count - ver_save + ver_inc) / ver_dist);
                glVertex3f(hor_count, ver_count + ver_inc, b[2]);

                glTexCoord2f((hor_count - hor_save + hor_inc) / hor_dist, (ver_count - ver_save + ver_inc) / ver_dist);
                glVertex3f(hor_count + hor_inc, ver_count + ver_inc, c[2]);

                glTexCoord2f((hor_count - hor_save + hor_inc) / hor_dist, (ver_count - ver_save) / ver_dist);
                glVertex3f(hor_count + hor_inc, ver_count, d[2]);

                ver_count += ver_inc;
            }
            hor_count += hor_inc;
        }
    }
    else if((a[1] == b[1]) && (b[1] == c[1]) && (c[1] == d[1])){
        GLfloat hor_dist = DistancePoint(b, a);
        GLfloat ver_dist = DistancePoint(d, a);
        GLfloat hor_inc = hor_dist / factor;
        GLfloat ver_inc = ver_dist / factor;

        GLfloat hor_count = min(a[0], b[0]);
        GLfloat ver_count = min(a[2], d[2]);

        GLfloat hor_save = hor_count;
        GLfloat ver_save = hor_count;

        //printf("Plano Y\nHorizontal: Distance: %f Count: %f Max: %f\n Vertical Distance: %f Count: %f Max: %f\n", hor_dist, hor_count, b[0], ver_dist, ver_count, d[2]);

        while (hor_count < max(a[0], b[0])) {
            while (ver_count <  max(a[2], d[2])) {
                glTexCoord2f((hor_count - hor_save) / hor_dist, (ver_count - ver_save) / ver_dist);
                glVertex3f(hor_count, a[1], ver_count);

                glTexCoord2f((hor_count - hor_save) / hor_dist, (ver_count - ver_save + ver_inc) / ver_dist);
                glVertex3f(hor_count, b[1], ver_count + ver_inc);

                glTexCoord2f((hor_count - hor_save + hor_inc) / hor_dist, (ver_count - ver_save + ver_inc) / ver_dist);
                glVertex3f(hor_count + hor_inc, c[1], ver_count + ver_inc);

                glTexCoord2f((hor_count - hor_save + hor_inc) / hor_dist, (ver_count - ver_save) / ver_dist);
                glVertex3f(hor_count + hor_inc, d[1], ver_count);

                ver_count += ver_inc;
            }
            hor_count += hor_inc;
        }
    }
    else{
        GLfloat hor_dist = DistancePoint(a, b);
        GLfloat ver_dist = DistancePoint(a, d);
        GLfloat hor_inc = hor_dist / factor;
        GLfloat ver_inc = ver_dist / factor;

        GLfloat hor_count = min(a[1], b[1]);
        GLfloat ver_count = min(a[2], d[2]);

        GLfloat hor_save = hor_count;
        GLfloat ver_save = hor_count;

        while (hor_count < max(a[1], b[1])) {
            while (ver_count < max(a[2], d[2])) {
                glTexCoord2f((hor_count - hor_save) / hor_dist, (ver_count - ver_save) / ver_dist); glVertex3f(a[0], hor_count, ver_count);
                glTexCoord2f((hor_count - hor_save) / hor_dist, (ver_count - ver_save + ver_inc) / ver_dist); glVertex3f(b[0], hor_count, ver_count + ver_inc);
                glTexCoord2f((hor_count - hor_save + hor_inc) / hor_dist, (ver_count - ver_save + ver_inc) / ver_dist); glVertex3f( c[0], hor_count + hor_inc,ver_count + ver_inc);
                glTexCoord2f((hor_count - hor_save + hor_inc) / hor_dist, (ver_count - ver_save) / ver_dist); glVertex3f(d[0], hor_count + hor_inc, ver_count);
                ver_count += ver_inc;
            }
            hor_count += hor_inc;
        }
    }
    glEnd();
    glPopMatrix();
}