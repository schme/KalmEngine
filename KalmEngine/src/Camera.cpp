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

void kCamera::Input( const f32 deltaTime ) {

    gameInput_t * input = GetGameInput();
    mouseInput_t * mouse = &input->mouseInput;

    this->yaw += mouse->offsetX * mouseSensitivity;
    this->pitch += mouse->offsetY * mouseSensitivity;

    if( this->pitch > 89.0f) {
        this->pitch = 89.0f;
    }
    if( this->pitch < -89.0f) {
        this->pitch = -89.0f;
    }

    UpdateVectors();

    if( input->up.endedDown ) {
        this->velocity += (this->front * this->movementSpeed) * deltaTime;
    }
    if( input->down.endedDown ) {
        this->velocity += (-this->front * this->movementSpeed) * deltaTime;
    }
    if( input->left.endedDown ) {
        this->velocity += (-this->right * this->movementSpeed) * deltaTime;
    }
    if( input->right.endedDown ) {
        this->velocity += (this->right * this->movementSpeed) * deltaTime;
    }
    if( input->actionR.endedDown ) {
        this->velocity += (this->up * this->movementSpeed) * deltaTime;
    }
    if( input->actionF.endedDown ) {
        this->velocity += (-this->up * this->movementSpeed) * deltaTime;
    }

}

/**
 * TODO(Kasper): Switch to a weighted sample buffer
 * TODO(Kasper): Switch Update functions to a script
 */
void kCamera::Update( const f32 deltaTime ) {
    this->position += this->velocity;
    this->velocity = Vec3(0.0f);
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
        M =  LookAt( this->position, Normalized( this->position - cameraTargetObject->position), this->right, this->up );
    } else {
        M = LookAt( this->position, this->position + this->front, this->right, this->up );
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
