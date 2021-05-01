#include "../headers/ship.h"

ship::ship() {
    this->mainComponent;
    this->mainNacelleRight;
    this->mainNacelleLeft;
    this->frontNacelleLeft;
    this->frontNacelleRight;
    this->status = OFF;
}

ship::ship(shader * objShader) {
    this->objects.clear();
    this->objects.push_back(new object("./resources/mainBody.obj","./resources/ship_texture.bmp", objShader));
    this->objects.push_back(new object("./resources/nacelle_body.obj","./resources/ship_texture.bmp", objShader));
    this->objects.push_back(new object("./resources/nacelle_body.obj","./resources/ship_texture.bmp", objShader));
    this->objects.push_back(new object("./resources/nacelle_front.obj","./resources/front_texture.bmp", objShader));
    this->objects.push_back(new object("./resources/nacelle_front.obj","./resources/front_texture.bmp", objShader));
    

    this->mainComponent = objects[0];
    this->mainComponent->name = "mainComponent";
    this->mainNacelleLeft = objects[1];
    this->mainNacelleLeft->name = "left Nacelle";
    this->mainNacelleRight = objects[2];
    this->mainNacelleRight->name = "right Nacelle";
    this->frontNacelleLeft = objects[3];
    this->frontNacelleLeft->name = "front left Nacelle";
    this->frontNacelleRight = objects[4];
    this->frontNacelleRight->name = "front right Nacelle";

    this->mainNacelleRight->setParent(this->mainComponent, glm::vec3(-1,0.2,0.1));
    this->mainNacelleLeft->setParent(this->mainComponent, glm::vec3(-1,0.2,-0.1));
    this->frontNacelleRight->setParent(this->mainNacelleRight, glm::vec3(1.67493,1.80568,0));
    this->frontNacelleLeft->setParent(this->mainNacelleLeft, glm::vec3(1.67493,1.80568,0));

    this->status = OFF;
    if (this->status == ON) {
        this->mainNacelleRight->setBank(1.2);
        this->mainNacelleLeft->setBank(-1.2);
    }
    else {
        this->mainNacelleRight->setBank(M_PI/2);
        this->mainNacelleLeft->setBank(-M_PI/2);
    }
}

void ship::setPos(glm::vec3 new_pos) {
    this->mainComponent->setPosition(new_pos);
}

void ship::setHeading(float new_heading) {
    this->mainComponent->setHeading(new_heading);
}

void ship::renderShip(shader * objShader, double ctime, double ltime) {
    this->frontNacelleLeft->setBank(25*ctime);
    this->frontNacelleRight->setBank(-25*ctime);


    updateNacelleOri(ctime - ltime);

    this->mainNacelleLeft->setPosition(glm::vec3(sin(10*ctime)/40.0f,sin(10*2*ctime)/40.0f,sin(10*3*ctime)/40.0f));
    this->mainNacelleRight->setPosition(glm::vec3(sin(10*ctime)/40.0f,sin(10*2*ctime)/40.0f,sin(10*3*ctime)/40.0f));

    for (int i = 0; i < objects.size(); i++) {
        objects[i]->renderObject(objShader);
    }
}

void ship::changeStatus() {
    switch(this->status) {
        case(TRANSITION_OFF):
            this->status = TRANSITION_ON;
            break;
        case(TRANSITION_ON):
            this->status = TRANSITION_OFF;
            break;
        case(OFF):
            this->status = TRANSITION_ON;
            break;
        case(ON):
            this->status = TRANSITION_OFF;
            break;
    }
}

void ship::updateNacelleOri(double deltaTime) {
    float curr_Bank = this->mainNacelleRight->getBank();
    if (this->status == TRANSITION_OFF) {
        curr_Bank += deltaTime;
        if (curr_Bank > M_PI/2) {
            curr_Bank = M_PI/2;
            this->status = OFF;
        }
    }
    else if (this->status == TRANSITION_ON) {
        curr_Bank -= deltaTime;
        if (curr_Bank < 1.2) {
            curr_Bank = 1.2;
            this->status = ON;
        }
    }
    this->mainNacelleLeft->setBank(-curr_Bank);
    this->mainNacelleRight->setBank(curr_Bank);
}

ship::~ship() {
    for (int i = 0; i < objects.size(); i++) {
        delete objects[i];
    }
}