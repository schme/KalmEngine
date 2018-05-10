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

    f32 movSpeedModifier = 3.0f;
    f32 movSpeed = this->movementSpeed;

    if( input->l_shift.endedDown ) {
        movSpeed *= movSpeedModifier;
    }

    if( input->up.endedDown ) {
        this->velocity += (this->front * movSpeed);
    }
    if( input->down.endedDown ) {
        this->velocity += (-this->front * movSpeed);
    }
    if( input->left.endedDown ) {
        this->velocity += (-this->right * movSpeed);
    }
    if( input->right.endedDown ) {
        this->velocity += (this->right * movSpeed);
    }
    if( input->actionR.endedDown || input->actionSpace.endedDown ) {
        this->velocity += (this->up * movSpeed);
    }
    if( input->actionF.endedDown || input->actionC.endedDown) {
        this->velocity += (-this->up * movSpeed);
    }

}

/**
 * TODO(Kasper): Switch to a weighted sample buffer
 * TODO(Kasper): Move Update functions to a script
 */
void kCamera::Update( const f32 deltaTime ) {
    this->position += this->velocity * deltaTime;
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
