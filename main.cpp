#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "RgbImage.h"
#include <gl/glut.h>

#define BLUE     0.0, 0.0, 1.0
#define RED         1.0, 0.0, 0.0
#define YELLOW     1.0, 1.0, 0.0
#define GREEN    0.0, 1.0, 0.0
#define ORANGE   1.0, 0.5, 0.1
#define CYAN     0.0, 1.0, 1.0
#define WHITE    1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0
#define GRAY     0.3, 0.3, 0.3

#define PI         3.14159

struct {
    char name[30];
    GLfloat ambient[3];
    GLfloat diffuse[3];
    GLfloat specular[3];
    GLfloat shininess;
} materials[24];

struct {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat intensity;
    GLfloat angle;
    GLfloat shininess;
} light;



GLint msec = 10;
char text[30];

GLint doorAngle = 0;
GLint handleAngle = 0;
GLfloat lock = 0;

/*Window Coordinates and Size*/
GLint wScreen = 800, hScreen = 600;
GLfloat yC = 200.0;

/*Observer*/
GLfloat rVisao = 4, aVisao = PI, incVisao = 0.05;
GLfloat obsP[] = {rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao)};
GLfloat obsT[] = {obsP[0] - rVisao * cos(aVisao), obsP[1], obsP[2] - rVisao * sin(aVisao)};

float angleZ = 95;
int projection = 0;

RgbImage img;

struct{
    GLint factor;
    GLint material;
    GLint day;
    GLint object;
}status;

struct{
    GLint wood;
    GLint window;
    GLint brick;
    GLint dirt;
}status_init;

const GLint tex_num = 6;
GLuint tex[tex_num];

void UploadMaterials() {
    strcpy(materials[0].name, "Esmerald");
    materials[0].ambient[0] = 0.021500; materials[0].ambient[1] = 0.174500; materials[0].ambient[2] = 0.021500;
    materials[0].diffuse[0] = 0.075680; materials[0].diffuse[1] = 0.614240; materials[0].diffuse[2] = 0.075680;
    materials[0].specular[0] = 0.633000; materials[0].specular[1] = 0.727811; materials[0].specular[2] = 0.633000;
    materials[0].shininess = 76.800000;

    strcpy(materials[1].name, "Jade");
    materials[1].ambient[0] = 0.135000;
    materials[1].ambient[1] = 0.222500;
    materials[1].ambient[2] = 0.157500;
    materials[1].diffuse[0] = 0.540000;
    materials[1].diffuse[1] = 0.890000;
    materials[1].diffuse[2] = 0.630000;
    materials[1].specular[0] = 0.316228;
    materials[1].specular[1] = 0.316228;
    materials[1].specular[2] = 0.316228;
    materials[1].shininess = 12.800000;

    strcpy(materials[2].name, "Obsidian");
    materials[2].ambient[0] = 0.053750;
    materials[2].ambient[1] = 0.050000;
    materials[2].ambient[2] = 0.066250;
    materials[2].diffuse[0] = 0.182750;
    materials[2].diffuse[1] = 0.170000;
    materials[2].diffuse[2] = 0.225250;
    materials[2].specular[0] = 0.332741;
    materials[2].specular[1] = 0.328634;
    materials[2].specular[2] = 0.346435;
    materials[2].shininess = 38.400000;

    strcpy(materials[3].name, "Pearl");
    materials[3].ambient[0] = 0.250000;
    materials[3].ambient[1] = 0.207250;
    materials[3].ambient[2] = 0.207250;
    materials[3].diffuse[0] = 1.000000;
    materials[3].diffuse[1] = 0.829000;
    materials[3].diffuse[2] = 0.829000;
    materials[3].specular[0] = 0.296648;
    materials[3].specular[1] = 0.296648;
    materials[3].specular[2] = 0.296648;
    materials[3].shininess = 11.264000;

    strcpy(materials[4].name, "Ruby");
    materials[4].ambient[0] = 0.174500;
    materials[4].ambient[1] = 0.011750;
    materials[4].ambient[2] = 0.011750;
    materials[4].diffuse[0] = 0.614240;
    materials[4].diffuse[1] = 0.041360;
    materials[4].diffuse[2] = 0.041360;
    materials[4].specular[0] = 0.727811;
    materials[4].specular[1] = 0.626959;
    materials[4].specular[2] = 0.626959;
    materials[4].shininess = 76.800000;

    strcpy(materials[5].name, "Turquiose");
    materials[5].ambient[0] = 0.100000;
    materials[5].ambient[1] = 0.187250;
    materials[5].ambient[2] = 0.174500;
    materials[5].diffuse[0] = 0.396000;
    materials[5].diffuse[1] = 0.741510;
    materials[5].diffuse[2] = 0.691020;
    materials[5].specular[0] = 0.297254;
    materials[5].specular[1] = 0.308290;
    materials[5].specular[2] = 0.306678;
    materials[5].shininess = 12.800000;

    strcpy(materials[6].name, "Brass");
    materials[6].ambient[0] = 0.329412;
    materials[6].ambient[1] = 0.223529;
    materials[6].ambient[2] = 0.027451;
    materials[6].diffuse[0] = 0.780392;
    materials[6].diffuse[1] = 0.568627;
    materials[6].diffuse[2] = 0.113725;
    materials[6].specular[0] = 0.992157;
    materials[6].specular[1] = 0.941176;
    materials[6].specular[2] = 0.807843;
    materials[6].shininess = 27.897436;

    strcpy(materials[7].name, "Bronze");
    materials[7].ambient[0] = 0.212500;
    materials[7].ambient[1] = 0.127500;
    materials[7].ambient[2] = 0.054000;
    materials[7].diffuse[0] = 0.714000;
    materials[7].diffuse[1] = 0.428400;
    materials[7].diffuse[2] = 0.181440;
    materials[7].specular[0] = 0.393548;
    materials[7].specular[1] = 0.271906;
    materials[7].specular[2] = 0.166721;
    materials[7].shininess = 25.600000;

    strcpy(materials[8].name, "Chrome");
    materials[8].ambient[0] = 0.250000;
    materials[8].ambient[1] = 0.250000;
    materials[8].ambient[2] = 0.250000;
    materials[8].diffuse[0] = 0.400000;
    materials[8].diffuse[1] = 0.400000;
    materials[8].diffuse[2] = 0.400000;
    materials[8].specular[0] = 0.774597;
    materials[8].specular[1] = 0.774597;
    materials[8].specular[2] = 0.774597;
    materials[8].shininess = 76.800000;

    strcpy(materials[9].name, "Copper");
    materials[9].ambient[0] = 0.191250;
    materials[9].ambient[1] = 0.073500;
    materials[9].ambient[2] = 0.022500;
    materials[9].diffuse[0] = 0.703800;
    materials[9].diffuse[1] = 0.270480;
    materials[9].diffuse[2] = 0.082800;
    materials[9].specular[0] = 0.256777;
    materials[9].specular[1] = 0.137622;
    materials[9].specular[2] = 0.086014;
    materials[9].shininess = 12.800000;

    strcpy(materials[10].name, "Gold");
    materials[10].ambient[0] = 0.247250;
    materials[10].ambient[1] = 0.199500;
    materials[10].ambient[2] = 0.074500;
    materials[10].diffuse[0] = 0.751640;
    materials[10].diffuse[1] = 0.606480;
    materials[10].diffuse[2] = 0.226480;
    materials[10].specular[0] = 0.628281;
    materials[10].specular[1] = 0.555802;
    materials[10].specular[2] = 0.366065;
    materials[10].shininess = 51.200000;

    strcpy(materials[11].name, "Silver");
    materials[11].ambient[0] = 0.192250;
    materials[11].ambient[1] = 0.192250;
    materials[11].ambient[2] = 0.192250;
    materials[11].diffuse[0] = 0.507540;
    materials[11].diffuse[1] = 0.507540;
    materials[11].diffuse[2] = 0.507540;
    materials[11].specular[0] = 0.508273;
    materials[11].specular[1] = 0.508273;
    materials[11].specular[2] = 0.508273;
    materials[11].shininess = 51.200000;

    strcpy(materials[12].name, "Black Plastic");
    materials[12].ambient[0] = 0.000000;
    materials[12].ambient[1] = 0.000000;
    materials[12].ambient[2] = 0.000000;
    materials[12].diffuse[0] = 0.010000;
    materials[12].diffuse[1] = 0.010000;
    materials[12].diffuse[2] = 0.010000;
    materials[12].specular[0] = 0.500000;
    materials[12].specular[1] = 0.500000;
    materials[12].specular[2] = 0.500000;
    materials[12].shininess = 32.000000;

    strcpy(materials[13].name, "Cyank Plastic");
    materials[13].ambient[0] = 0.000000;
    materials[13].ambient[1] = 0.100000;
    materials[13].ambient[2] = 0.060000;
    materials[13].diffuse[0] = 0.000000;
    materials[13].diffuse[1] = 0.509804;
    materials[13].diffuse[2] = 0.509804;
    materials[13].specular[0] = 0.501961;
    materials[13].specular[1] = 0.501961;
    materials[13].specular[2] = 0.501961;
    materials[13].shininess = 32.000000;

    strcpy(materials[14].name, "Green Plastic");
    materials[14].ambient[0] = 0.000000;
    materials[14].ambient[1] = 0.000000;
    materials[14].ambient[2] = 0.000000;
    materials[14].diffuse[0] = 0.100000;
    materials[14].diffuse[1] = 0.350000;
    materials[14].diffuse[2] = 0.100000;
    materials[14].specular[0] = 0.450000;
    materials[14].specular[1] = 0.550000;
    materials[14].specular[2] = 0.450000;
    materials[14].shininess = 32.000000;

    strcpy(materials[15].name, "Red Plastic");
    materials[15].ambient[0] = 0.000000;
    materials[15].ambient[1] = 0.000000;
    materials[15].ambient[2] = 0.000000;
    materials[15].diffuse[0] = 0.500000;
    materials[15].diffuse[1] = 0.000000;
    materials[15].diffuse[2] = 0.000000;
    materials[15].specular[0] = 0.700000;
    materials[15].specular[1] = 0.600000;
    materials[15].specular[2] = 0.600000;
    materials[15].shininess = 32.000000;

    strcpy(materials[16].name, "White Plastic");
    materials[16].ambient[0] = 0.800000;
    materials[16].ambient[1] = 0.800000;
    materials[16].ambient[2] = 0.800000;
    materials[16].diffuse[0] = 0.550000;
    materials[16].diffuse[1] = 0.550000;
    materials[16].diffuse[2] = 0.550000;
    materials[16].specular[0] = 0.870000;
    materials[16].specular[1] = 0.870000;
    materials[16].specular[2] = 0.870000;
    materials[16].shininess = 32.000000;

    strcpy(materials[17].name, "Yellow Plastic");
    materials[17].ambient[0] = 0.000000;
    materials[17].ambient[1] = 0.000000;
    materials[17].ambient[2] = 0.000000;
    materials[17].diffuse[0] = 0.500000;
    materials[17].diffuse[1] = 0.500000;
    materials[17].diffuse[2] = 0.000000;
    materials[17].specular[0] = 0.600000;
    materials[17].specular[1] = 0.600000;
    materials[17].specular[2] = 0.500000;
    materials[17].shininess = 32.000000;

    strcpy(materials[18].name, "Black Rubber");
    materials[18].ambient[0] = 0.020000;
    materials[18].ambient[1] = 0.020000;
    materials[18].ambient[2] = 0.020000;
    materials[18].diffuse[0] = 0.010000;
    materials[18].diffuse[1] = 0.010000;
    materials[18].diffuse[2] = 0.010000;
    materials[18].specular[0] = 0.400000;
    materials[18].specular[1] = 0.400000;
    materials[18].specular[2] = 0.400000;
    materials[18].shininess = 10.000000;

    strcpy(materials[19].name, "Cyan Rubber");
    materials[19].ambient[0] = 0.000000;
    materials[19].ambient[1] = 0.050000;
    materials[19].ambient[2] = 0.050000;
    materials[19].diffuse[0] = 0.400000;
    materials[19].diffuse[1] = 0.500000;
    materials[19].diffuse[2] = 0.500000;
    materials[19].specular[0] = 0.040000;
    materials[19].specular[1] = 0.700000;
    materials[19].specular[2] = 0.700000;
    materials[19].shininess = 10.000000;

    strcpy(materials[20].name, "Green Rubber");
    materials[20].ambient[0] = 0.000000;
    materials[20].ambient[1] = 0.050000;
    materials[20].ambient[2] = 0.000000;
    materials[20].diffuse[0] = 0.400000;
    materials[20].diffuse[1] = 0.500000;
    materials[20].diffuse[2] = 0.400000;
    materials[20].specular[0] = 0.040000;
    materials[20].specular[1] = 0.700000;
    materials[20].specular[2] = 0.040000;
    materials[20].shininess = 10.000000;

    strcpy(materials[21].name, "Red Rubber");
    materials[21].ambient[0] = 0.050000;
    materials[21].ambient[1] = 0.000000;
    materials[21].ambient[2] = 0.000000;
    materials[21].diffuse[0] = 0.500000;
    materials[21].diffuse[1] = 0.400000;
    materials[21].diffuse[2] = 0.400000;
    materials[21].specular[0] = 0.700000;
    materials[21].specular[1] = 0.040000;
    materials[21].specular[2] = 0.040000;
    materials[21].shininess = 10.000000;
}

void UploadTextures() {
    char files[tex_num][20] = {"stone.bmp", "planks_oak.bmp", "glass.bmp", "grass.bmp","sky-box.bmp", "night.bmp"};

    for (int i = 0; i < tex_num; i++) {
        glGenTextures(1, &tex[i]);
        glBindTexture(GL_TEXTURE_2D, tex[i]);

        img.LoadBmpFile(files[i]);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
                     img.GetNumCols(),
                     img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     img.ImageData());
    }
}

void init() {
    glClearColor(BLACK, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    /*Upload Data*/
    UploadMaterials();
    UploadTextures();

    /*Initialize Vars*/
    light.r = 1.0;
    light.g = 1.0;
    light.b = 1.0;
    light.intensity = 0.1;
    light.angle = 10.0;
    light.shininess = -1;

    //Mesh
    status.factor = 1.0;
    status.material = -1;
    status.day = 0;
    status.object = 1;

    status_init.brick = 8;
    /*Copper Propriety*/
    status_init.wood = 9;
    status_init.dirt = 10;
    status_init.window = 1;

    srand(1);
}

void UpdatePos() {
    obsP[0] = rVisao * cos(aVisao);
    obsP[2] = rVisao * sin(aVisao);
    obsT[0] = obsP[0] - rVisao * cos(aVisao);
    obsT[2] = obsP[2] - rVisao * sin(aVisao);
}

void Normalize(GLfloat *v) {
    GLfloat length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    for (int i = 0; i < 3; i++) {
        v[i] = v[i] / length;
    }
}

GLfloat *CrossProduct(const GLfloat *a, const GLfloat *b) {
    auto *v = (GLfloat *) malloc(3 * sizeof(GLfloat));

    v[0] = a[1] * b[2] - a[2] * b[1];
    v[1] = a[0] * b[2] - a[2] * b[0];
    v[2] = a[0] * b[1] - a[1] * b[0];

    Normalize(v);

    return v;
}

GLfloat *GetNormal(const GLfloat a[], const GLfloat b[], const GLfloat c[]) {
    auto *x = (GLfloat *) malloc(3 * sizeof(GLfloat));
    auto *y = (GLfloat *) malloc(3 * sizeof(GLfloat));

    x[0] = b[0] - a[0];
    x[1] = b[1] - a[1];
    x[2] = b[2] - a[2];
    y[0] = c[0] - a[0];
    y[1] = c[1] - a[1];
    y[2] = c[2] - a[2];

    return CrossProduct(x, y);
}

void DrawLight() {
    /*Global Light Settings*/
    GLfloat intensity = 1;
    GLfloat globalAmbient[] = {intensity, intensity, intensity, 1.0};
    /*Global*/
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
    /*Enable Light*/
    glEnable(GL_LIGHTING);
    if (status.day) {
        /*Focus Settings*/
        GLfloat focusCutoff = light.angle;
        GLfloat focusPosition[] = {2.0f, 3.0f, 20.0f, 1.0f};
        GLfloat focusDirection[] = {0, 0, -1, 0};
        GLfloat focusColor[] = {light.intensity * light.r, light.intensity * light.g, light.intensity * light.b, 1};
        GLfloat focusAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat focusConstantAttenuation = 1.0;
        GLfloat focusLinearAttenuation = 0.05f;
        GLfloat focusSquareAttenuation = 0.0f;
        GLfloat focusExponent = 2.0;
        /*Focus*/
        glLightfv(GL_LIGHT1, GL_POSITION, focusPosition);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, focusColor);
        glLightfv(GL_LIGHT0, GL_AMBIENT, focusAmbient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, focusColor);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, focusConstantAttenuation);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, focusLinearAttenuation);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, focusSquareAttenuation);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, focusCutoff);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, focusDirection);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, focusExponent);
        glEnable(GL_LIGHT1);
    } else {
        /*Directional Light Settings*/
        GLfloat directionalPosition[] = {0, -51, 0, 1, 0};
        GLfloat directionalDirection[] = {0, 1, 0, 0};
        GLfloat directionalColor[] = {light.intensity * light.r, light.intensity * light.g, light.intensity * light.b, 1};
        GLfloat directionalAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
        /*Directional*/
        glLightfv(GL_LIGHT0, GL_POSITION, directionalPosition);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, directionalColor);
        glLightfv(GL_LIGHT0, GL_AMBIENT, directionalAmbient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, directionalColor);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, directionalDirection);
        glEnable(GL_LIGHT0);
    }

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void SkySphere() {
    //glDepthMask(false);

    GLUquadricObj *skybox = gluNewQuadric();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex[4 + status.day]);

    glPushMatrix();
    gluQuadricNormals(skybox, GLU_SMOOTH);
    gluQuadricTexture(skybox, GL_TRUE);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    gluSphere(skybox, 50, 32, 32);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    //glDepthMask(true);
}

void drawText(char *string, GLfloat x, GLfloat y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRasterPos2f(0, 0);
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *string++);
    glPopMatrix();
}

GLfloat DistancePoint(GLfloat *a, GLfloat *b) {
    return sqrt(pow(a[0] - b[0], 2.0) + pow(a[1] - b[1], 2.0) + pow(a[2] - b[2], 2.0));
}

GLfloat max(GLfloat num1, GLfloat num2){
    return (num1 > num2) ? num1 : num2;
}

GLfloat min(GLfloat num1, GLfloat num2){
    return (num1 > num2) ? num2 : num1;
}

void SetMaterial(int slot){
    int material, shininess;
    if(status.material == -1 || slot != status.object - 1){
        switch(slot){
            case 0:
                /*Brick*/
                material = status_init.brick;
                break;
            case 1:
                material = status_init.wood;
                /*Wood*/
                break;
            case 2:
                material = status_init.window;
                /*Window*/
                break;
            case 3:
                material = status_init.dirt;
                /*Dirt*/
                break;
            default:
                glEnable(GL_COLOR_MATERIAL);
                return;
        }
    }
    else material = status.material;

    if(light.shininess != -1) shininess = light.shininess;
    else shininess = materials[material].shininess;


    glMaterialfv(GL_FRONT, GL_AMBIENT, materials[material].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[material].diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materials[material].specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void DrawQuadv(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int slot) {
    SetMaterial(slot);

    auto normal = GetNormal(a, b, c);

    glNormal3fv(normal);

    glPushMatrix();
    glBegin(GL_QUADS);

    if((a[2] == b[2]) && (b[2] == c[2]) && (c[2] == d[2])){
        GLfloat hor_dist = DistancePoint(a, b);
        GLfloat ver_dist = DistancePoint(a, d);
        GLfloat hor_inc = hor_dist / status.factor;
        GLfloat ver_inc = ver_dist / status.factor;

        GLfloat hor_count = min(a[0], b[0]);
        GLfloat ver_count = min(a[1], d[1]);

        GLfloat hor_save = hor_count;
        GLfloat ver_save = hor_count;

        //printf("Plano Z\nHorizontal: Distance: %f Count: %f Max: %f\n Vertical Distance: %f Count: %f Max: %f\n", hor_dist, hor_count, a[0], ver_dist, ver_count, a[2]);

        while (hor_count < max(a[0], b[0])) {
            ver_count = min(a[1], d[1]);
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
        GLfloat hor_inc = hor_dist / status.factor;
        GLfloat ver_inc = ver_dist / status.factor;

        GLfloat hor_count = min(a[0], b[0]);
        GLfloat ver_count = min(a[2], d[2]);

        GLfloat hor_save = hor_count;
        GLfloat ver_save = hor_count;

        //printf("Plano Y\nHorizontal: Distance: %f Count: %f Max: %f\n Vertical Distance: %f Count: %f Max: %f\n", hor_dist, hor_count, b[0], ver_dist, ver_count, d[2]);

        while (hor_count < max(a[0], b[0])) {
            ver_count = min(a[2], d[2]);
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
    else if((a[0] == b[0]) && (b[0] == c[0]) && (c[0] == d[0])){
        GLfloat hor_dist = DistancePoint(c, b);
        GLfloat ver_dist = DistancePoint(c, d);
        GLfloat hor_inc = hor_dist / status.factor;
        GLfloat ver_inc = ver_dist / status.factor;

        GLfloat hor_count = min(c[1], b[1]);
        GLfloat ver_count = min(c[2], d[2]);

        GLfloat hor_save = hor_count;
        GLfloat ver_save = hor_count;

        //printf("Plano X\nHorizontal: Distance: %f Min: %f Max: %f Inc: %f\nVertical Distance: %f Min: %f Max: %f Inc: %f\n", hor_dist, hor_count, max(a[1], b[1]), hor_inc, ver_dist, ver_count, max(a[2], d[2]), ver_inc);

        while (hor_count < max(c[1], b[1])) {
            ver_count = min(c[2], d[2]);
            while (ver_count < max(c[2], d[2])) {
                //printf("Horizontal Count: %f\nVertical Count: %f\n", hor_count, ver_count);
                glTexCoord2f((hor_count - hor_save) / hor_dist, (ver_count - ver_save) / ver_dist);
                glVertex3f(a[0], hor_count, ver_count);

                glTexCoord2f((hor_count - hor_save) / hor_dist, (ver_count - ver_save + ver_inc) / ver_dist);
                glVertex3f(b[0], hor_count, ver_count + ver_inc);

                glTexCoord2f((hor_count - hor_save + hor_inc) / hor_dist, (ver_count - ver_save + ver_inc) / ver_dist);
                glVertex3f(c[0], hor_count + hor_inc,ver_count + ver_inc);

                glTexCoord2f((hor_count - hor_save + hor_inc) / hor_dist, (ver_count - ver_save) / ver_dist);
                glVertex3f(d[0], hor_count + hor_inc, ver_count);
                ver_count += ver_inc;
            }
            hor_count += hor_inc;
        }
    }
    glEnd();
    glPopMatrix();

    glDisable(GL_COLOR_MATERIAL);
}

void DrawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat base, GLfloat height, GLfloat border, int slot) {
    GLfloat half_base = base * 0.5f;
    GLfloat half_height = height * 0.5f;
    GLfloat half_border = border * 0.5f;

    auto a = (GLfloat *) malloc(3 * sizeof(GLfloat));
    auto b = (GLfloat *) malloc(3 * sizeof(GLfloat));
    auto c = (GLfloat *) malloc(3 * sizeof(GLfloat));
    auto d = (GLfloat *) malloc(3 * sizeof(GLfloat));

    if(slot >= 0){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex[slot]);
    }

    a[0] = x + half_base; a[1] = y + half_height; a[2] = z - half_border;
    b[0] = x - half_base; b[1] = y + half_height; b[2] = z - half_border;
    c[0] = x - half_base; c[1] = y + half_height; c[2] = z + half_border;
    d[0] = x + half_base; d[1] = y + half_height; d[2] = z + half_border;

    DrawQuadv(a, b, c, d, slot);

    a[0] = x + half_base; a[1] = y - half_height; a[2] = z + half_border;
    b[0] = x - half_base; b[1] = y - half_height; b[2] = z + half_border;
    c[0] = x - half_base; c[1] = y - half_height; c[2] = z - half_border;
    d[0] = x + half_base; d[1] = y - half_height; d[2] = z - half_border;

    DrawQuadv(a, b, c, d, slot);

    a[0] = x + half_base; a[1] = y + half_height; a[2] = z + half_border;
    b[0] = x - half_base; b[1] = y + half_height; b[2] = z + half_border;
    c[0] = x - half_base; c[1] = y - half_height; c[2] = z + half_border;
    d[0] = x + half_base; d[1] = y - half_height; d[2] = z + half_border;

    DrawQuadv(a, b, c, d, slot);

    a[0] = x + half_base; a[1] = y - half_height; a[2] = z - half_border;
    b[0] = x - half_base; b[1] = y - half_height; b[2] = z - half_border;
    c[0] = x - half_base; c[1] = y + half_height; c[2] = z - half_border;
    d[0] = x + half_base; d[1] = y + half_height; d[2] = z - half_border;

    DrawQuadv(a, b, c, d, slot);

    a[0] = x - half_base; a[1] = y + half_height; a[2] = z + half_border;
    b[0] = x - half_base; b[1] = y + half_height; b[2] = z - half_border;
    c[0] = x - half_base; c[1] = y - half_height; c[2] = z - half_border;
    d[0] = x - half_base; d[1] = y - half_height; d[2] = z + half_border;

    DrawQuadv(a, b, c, d, slot);

    a[0] = x + half_base; a[1] = y + half_height; a[2] = z - half_border;
    b[0] = x + half_base; b[1] = y + half_height; b[2] = z + half_border;
    c[0] = x + half_base; c[1] = y - half_height; c[2] = z + half_border;
    d[0] = x + half_base; d[1] = y - half_height; d[2] = z - half_border;

    DrawQuadv(a, b, c, d, slot);

    if (slot >= 0) glDisable(GL_TEXTURE_2D);
}

void DrawFloor(GLfloat x, GLfloat y, GLfloat z, GLfloat base, GLfloat height, int slot) {
    //Divisions to draw
    GLint step = 40;

    GLfloat half_base = base * 0.5f;
    GLfloat half_height = height * 0.5f;

    GLfloat step_base = half_base / step;
    GLfloat step_height = half_height / step;

    auto a = (GLfloat *) malloc(3 * sizeof(GLfloat));
    auto b = (GLfloat *) malloc(3 * sizeof(GLfloat));
    auto c = (GLfloat *) malloc(3 * sizeof(GLfloat));
    auto d = (GLfloat *) malloc(3 * sizeof(GLfloat));

    if (slot >= 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex[slot]);
    }

    GLfloat i = -half_base;
    while (i <= half_base) {
        GLfloat j = -half_height;
        while (j <= half_height) {
            a[0] = (x + i) - step_base; a[1] = y; a[2] = (z + j) - step_height;
            b[0] = (x + i) + step_base; b[1] = y; b[2] = (z + j) - step_height;
            c[0] = (x + i) + step_base; c[1] = y; c[2] = (z + j) + step_height;
            d[0] = (x + i) - step_base; d[1] = y; d[2] = (z + j) + step_height;

            DrawQuadv(d, c, b, a, slot);

            j += 2 * step_height;
        }
        i += 2 * step_base;
    }

    if (slot >= 0) glDisable(GL_TEXTURE_2D);
}

void DrawQuad(GLfloat x, GLfloat y, GLfloat z, GLfloat side, int slot) {
    if (slot >= 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex[slot]);
    }

    side /= 2;

    auto a = (GLfloat *) malloc(3 * sizeof(GLfloat));
    auto b = (GLfloat *) malloc(3 * sizeof(GLfloat));
    auto c = (GLfloat *) malloc(3 * sizeof(GLfloat));
    auto d = (GLfloat *) malloc(3 * sizeof(GLfloat));

    a[0] = x + side; a[1] = y + side; a[2] = z;
    b[0] = x - side; b[1] = y + side; b[2] = z;
    c[0] = x - side; c[1] = y - side; c[2] = z;
    d[0] = x + side; d[1] = y - side; d[2] = z;

    DrawQuadv(a, b, c, d, slot);

    if (slot >= 0) glDisable(GL_TEXTURE_2D);
}

void DrawAxis() {
    glColor4f(ORANGE, 1.0);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(10, 0, 0);
    glEnd();
    glColor4f(GREEN, 1.0);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 10, 0);
    glEnd();
    glColor4f(CYAN, 1.0);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 10);
    glEnd();
}

void DrawLocalObserver() {
    glColor4f(GREEN, 1.0);
    glPushMatrix();
    glTranslatef(obsP[0], obsP[1], obsP[2]);
    glutSolidCube(1);
    glPopMatrix();
}

void DrawTargetObserver() {
    glColor4f(YELLOW, 1.0);
    glPushMatrix();
    glTranslatef(obsT[0], obsT[1], obsT[2]);
    glutSolidCube(0.8);
    glPopMatrix();
}

char *GetColor(GLfloat r, GLfloat g, GLfloat b) {
    GLint total = r * 100 + g * 10 + b;
    switch (total) {
        case 0:
            return strdup("OFF");
        case 1:
            return strdup("BLUE");
        case 10:
            return strdup("GREEN");
        case 11:
            return strdup("CYAN");
        case 100:
            return strdup("RED");
        case 101:
            return strdup("PURPLE");
        case 110:
            return strdup("YELLOW");
        case 111:
            return strdup("WHITE");
        default:
            return strdup("Undefined");
    }
}

void DrawInfo() {
    int x = -17, y = -17;

    if (handleAngle != 50 && doorAngle == 0) snprintf(text, 30, "[R] Locked!");
    else snprintf(text, 30, "[r] Unlocked!");

    drawText(text, x, y); y+=2;

    if (status.day) snprintf(text, 30, "[D] Night");
    else snprintf(text, 30, "[D] Day");

    drawText(text, x, y); y+=2;

    snprintf(text, 30, "[R] %d [G] %d [B] %d: %s", (int) light.r, (int) light.g, (int) light.b,
             GetColor(light.r, light.g, light.b));

    drawText(text, x, y); y+=2;

    snprintf(text, 30, "[I] Intensity: %d%", (int) (light.intensity * 100));
    drawText(text, x, y); y+=2;

    if (status.day) {
        snprintf(text, 30, "[A] Angleº: %d", (int) light.angle);
        drawText(text, x, y); y+=2;
    }
    if(status.factor == 1) snprintf(text, 30, "[F] Mesh: OFF");
    else snprintf(text, 30, "[F] Mesh: ON");
    drawText(text, x, y); y+=2;

    if(light.shininess == -1) snprintf(text, 30, "[S] Shininess: Default");
    else snprintf(text, 30, "[S] Shininess: %d", (int) light.shininess);
    drawText(text, x, y); y+=2;

    if(status.material == -1) snprintf(text, 30, "[M] Propriety: Default");
    else snprintf(text, 30, "[M] Propriety: %s", materials[status.material].name);
    drawText(text, x, y); y+=2;

    switch (status.object) {
        case 1:
            snprintf(text, 30, "[P] Current: Brick");
            /*Brick*/
            break;
        case 2:
            snprintf(text, 30, "[P] Current: Wood");
            /*Wood*/
            break;
        case 3:
            snprintf(text, 30, "[P] Current: Window");
            /*Window*/
            break;
        case 4:
            snprintf(text, 30, "[P] Current: Dirt");
            /*Dirt*/
            break;
    }
    drawText(text, x, y); y+=2;

}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);

    /*Projection*/
    glViewport(0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*Draw Orientation Info*/
    //DrawAxis();
    //DrawLocalObserver();
    //DrawTargetObserver();

    glColor4f(CYAN, 1.0);
    DrawInfo();
    glColor4f(1,1,1,1);

    /*Setup ViewPort*/
    glViewport(0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angleZ, (float) wScreen / hScreen, 0.1, 9999);

    UpdatePos();
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(obsP[0], obsP[1], obsP[2], obsT[0], obsT[1], obsT[2], 0, 1, 0);

    /*SkySphere*/
    SkySphere();

    /*Light Components*/
    DrawLight();

    if(status.day){
        glColor4f(BLACK, 1.0);
        DrawCube(2.0f, 3.0f, 20.0f, 0.5, 0.5, 1, -1);
        DrawCube(2.0f, 3.0f, 19.5f, 0.7, 0.7, 0.5, -1);
        glColor4f(1,1,1,1);
    }

    /*Draw Scene*/

    DrawAxis();
    DrawFloor(0, 0, 0, 100, 100, 3);

    GLdouble i, j, aux;

    /*Ceiling*/
    i = -6.5;
    while(i <= 6.5){
        j = -6.5;
        while(j <= 6.5){
            if(abs(i) == abs(j)) aux = abs(i);
            else aux = max(abs(i), abs(j));
            aux = (6.5 - aux) / 2;
            DrawCube(i, 9.25 + aux, j - 5.75, 1, 0.5, 1, 1);
            j += 1;
        }
        i += 1;
    }

    /*Walls*/
    i = -5.5;
    while(i <= 5.5){
        j = 0.5;
        while(j <= 8.5){
            //Jumps Door Coordinates
            if(!(i >= 0.5 && i <= 3.5 && j >= 0.5 && j <= 7.5)){
                DrawCube(i, j, 0, 1, 1, 0.5, 0);
            }
            DrawCube(i, j, -12, 1, 1, 0.5, 0);
            DrawCube(-5.75, j, i - 5.75, 0.5, 1, 1, 0);
            DrawCube(5.75, j, i - 5.75, 0.5, 1, 1, 0);
            j += 1;
        }
        i += 1;
    }

    /*Open door*/
    glRotatef(doorAngle, 0, 1, 0);

    /*Align door with y axis*/
    glTranslatef(2, 4, 0);

    /*Door*/
    i = -1.5;
    while (i <= 1.5) {
        j = -3.5;
        while (j <= 3.5) {
            /*Jumps Window */
            if ((j == 1.5 || j == 2.5) && (i == -0.5 || i == 0.5)) {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                DrawQuad(i, j, 0, 1, 2);
                glDisable(GL_BLEND);
            }
                /*Draws Wood UploadTextures*/
            else DrawCube(i, j, 0, 1, 1, 0.5, 1);
            j += 1;
        }
        i += 1;
    }

    /*Door Lock*/
    DrawCube(1.70 - lock, 0, 0, 1, 0.25, 0.25, -1);

    /*Door Handle*/
    glTranslatef(1.5, 0, 0.5);
    glRotatef(handleAngle, 0, 0, 1);
    glTranslatef(-1.5, 0, -0.5);

    glColor4f(GRAY, 1.0);

    DrawCube(1.5, 0, 0.5, 0.25, 0.25, 0.5, -1);
    DrawCube(1.125, 0, 0.775, 1, 0.25, 0.125, -1);

    glutSwapBuffers();
}

void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(msec, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'k': case 'K':
            status.material = -1;
            light.shininess = -1;
            break;
        case 'p': case 'P':
            status.object++;
            if(status.object > 4) status.object = 1;
            break;
        case 's': case 'S':
            if (light.shininess) light.shininess = 0;
            else light.shininess = 1;
            break;
        case 'f': case 'F':
            if(status.factor == 1) status.factor = 20.0;
            else status.factor = 1;
            break;
        case 'i': case 'I':
            light.intensity += 0.1;
            if (light.intensity > 1.0) light.intensity = 0.0;
            break;
        case 'd': case 'D':
            if (status.day) status.day = 0;
            else status.day = 1;
            glutPostRedisplay();
            break;
            /*Light*/
        case 'r': case 'R':
            if (light.r) light.r = 0.0;
            else light.r = 1.0;
            glutPostRedisplay();
            break;
        case 'g': case 'G':
            if (light.g) light.g = 0;
            else light.g = 1;
            glutPostRedisplay();
            break;
        case 'b': case 'B':
            if (light.b) light.b = 0;
            else light.b = 1;
            glutPostRedisplay();
            break;
        case 'a': case 'A':
            light.angle += 5;
            if (light.angle == 45)
                light.angle = 0;
            break;
            /*Zoom*/
        case 'z':
            rVisao -= 0.25;
            glutPostRedisplay();
            break;
        case 'Z':
            rVisao += 0.25;
            glutPostRedisplay();
            break;
            /*Handle Manipulation*/
        case 'l':
            handleAngle += 10;
            lock += 0.05;
            if (handleAngle > 50) {
                handleAngle = 50;
                lock = 0.25;
            }
            glutPostRedisplay();
            break;
        case 'L':
            handleAngle -= 10;
            lock -= 0.05;
            if (handleAngle < 0) {
                handleAngle = 0;
                lock = 0;
            }
            glutPostRedisplay();
            break;
            /*Door Manipulation*/
        case 'o':
            if (handleAngle != 50 && doorAngle == 0) break;
            doorAngle += 10;
            if (doorAngle > 90)
                doorAngle = 90;
            glutPostRedisplay();
            break;
        case 'O':
            doorAngle -= 10;
            if (doorAngle < 0)
                doorAngle = 0;
            glutPostRedisplay();
            break;
            /*Escape*/
        case 'm': case 'M':
            status.material += 1;
            if (status.material == 21) {
                status.material = 0;
            }
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }

}

void KeysNotAscii(int key, int x, int y) {
    obsT[0] = 0;
    obsT[1] = 0;
    obsT[2] = 0;

    if (key == GLUT_KEY_UP) obsP[1] = obsP[1] + 0.5;
    if (key == GLUT_KEY_DOWN) obsP[1] = obsP[1] - 0.5;
    if (key == GLUT_KEY_LEFT) aVisao = aVisao + 0.1;
    if (key == GLUT_KEY_RIGHT) aVisao = aVisao - 0.1;

    if (obsP[1] > yC) obsP[1] = yC;
    if (obsP[1] < -yC) obsP[1] = -yC;

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(400, 100);

    glutCreateWindow("Projeto CG");

    init();

    glutSpecialFunc(KeysNotAscii);
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(msec, Timer, 1);

    glutMainLoop();

    return 0;
}