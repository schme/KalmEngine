/**
 *
 * Camera.h
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */
#ifndef CAMERA_H_
#define CAMERA_H_

#include "Object.h"
#include "kMath.h"

const f32 YAW = -90.0f;
const f32 PITCH = 0.0f;
const f32 SPEED = 2.5f;
const f32 SENSITIVITY = 0.1f;
const f32 ZOOM = 60.0f;

enum cameraMovement_e {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class kCamera : public kObject {

    public:
    vec3 position = Vec3( 0.0f, 0.0f, 0.0f);
    vec3 worldUp = Vec3( 0.0f, 1.0f, 0.0f);
    vec3 up = worldUp;
    vec3 front = Vec3( 0.0f, 0.0f, -1.0f);
    vec3 right = Vec3( 1.0f, 0.0f, 0.0f);

    kObject *cameraTargetObject = nullptr;

    f32 yaw = YAW;
    f32 pitch = PITCH;

    f32 movementSpeed = SPEED;
    f32 mouseSensitivity = SENSITIVITY;
    f32 zoom = ZOOM;


    /**
     * methods
     */
    void Initialize( vec3 position, vec3 worldUp, f32 yaw = YAW, f32 pitch = PITCH, f32 movementSpeed = SPEED,
                                                                f32 mouseSensitivity = SENSITIVITY,
                                                                f32 zoom = ZOOM);
    mat4 GetViewMatrix() const ;

    void Update();
    void Update( f32 deltaTime);
    private:
    void UpdateVectors();
};

#endif /* end of include guard: CAMERA_H_ */
