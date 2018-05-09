/**
 *
 * Camera.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */

#include "Camera.h"
#include "GameShared.h"

void kCamera::Update() {
    UpdateVectors();
}

/**
 * TODO(Kasper): Switch to a weighted sample buffer
 * TODO(Kasper): Switch Update functions to a script
 */
void kCamera::Update( f32 deltaTime ) {
    gameInput_t * input = GetGameInput();

    if( input->up.endedDown ) {
        this->position = this->position + (this->front * this->movementSpeed) * deltaTime;
        printf("Camera pos: %f,%f,%f\nCamera front: %f,%f,%f\n\n", this->position.x, this->position.y, this->position.z, this->front.x, this->front.y, this->front.z);
    }
    if( input->down.endedDown ) {
        this->position = this->position + (-this->front * this->movementSpeed) * deltaTime;
        printf("Camera pos: %f,%f,%f\nCamera front: %f,%f,%f\n\n", this->position.x, this->position.y, this->position.z, this->front.x, this->front.y, this->front.z);
    }
    if( input->left.endedDown ) {
        this->position = this->position + (-this->right * this->movementSpeed) * deltaTime;
        printf("Camera pos: %f,%f,%f\nCamera front: %f,%f,%f\n\n", this->position.x, this->position.y, this->position.z, this->front.x, this->front.y, this->front.z);
    }
    if( input->right.endedDown ) {
        this->position = this->position + (this->right * this->movementSpeed) * deltaTime;
        printf("Camera pos: %f,%f,%f\nCamera front: %f,%f,%f\n\n", this->position.x, this->position.y, this->position.z, this->front.x, this->front.y, this->front.z);
    }
    if( input->actionR.endedDown ) {
        this->position = this->position + (this->up * this->movementSpeed) * deltaTime;
        printf("Camera pos: %f,%f,%f\nCamera front: %f,%f,%f\n\n", this->position.x, this->position.y, this->position.z, this->front.x, this->front.y, this->front.z);
    }
    if( input->actionF.endedDown ) {
        this->position = this->position + (-this->up * this->movementSpeed) * deltaTime;
        printf("Camera pos: %f,%f,%f\nCamera front: %f,%f,%f\n\n", this->position.x, this->position.y, this->position.z, this->front.x, this->front.y, this->front.z);
    }

    UpdateVectors();
}




void kCamera::Initialize( vec3 position, vec3 worldUp, f32 yaw, f32 pitch, f32 movementSpeed,
                                                        f32 mouseSensitivity, f32 zoom ) {
    this->position = position;
    this->worldUp = worldUp;
    this->yaw = yaw;
    this->pitch = pitch;

    this->mouseSensitivity = mouseSensitivity;
    this->movementSpeed = movementSpeed;
    this->zoom = zoom;

    this->UpdateVectors();
}


mat4 kCamera::GetViewMatrix() const {
    mat4 M;
    if( cameraTargetObject ) {
        M =  LookAt( this->position, cameraTargetObject->position, this->worldUp );
    } else {
        M = LookAt( this->position, this->position + this->front, this->worldUp );
    }
    return M;
}


void kCamera::UpdateVectors() {
    vec3 front;
    front.x = cosf( Radians( this->yaw )) * cosf( Radians( this->pitch ));
    front.y = sinf( Radians( this->pitch ));
    front.z = sinf( Radians( this->yaw )) * cosf( Radians( this->pitch ));
    this->front = Normalized( front );

    this->right = Normalized( Cross( this->front, this->worldUp));
    this->up = Normalized( Cross( this->right, this->front));
}
