#include "AABB.h"


vec3 kAABB::GetCorner( const unsigned i ) const {

    ASSERT( i < 8 && "AABB::getCorner() invalid index");
    vec3 corner = {};
    switch(i) {
        case 0:
            corner = this->center - this->half;
            break;
        case 1:
            corner = this->center + Vec3( this->half.x, -this->half.y, -this->half.z);
            break;
        case 2:
            corner = this->center + Vec3( -this->half.x, -this->half.y, this->half.z);
            break;
        case 3:
            corner = this->center + Vec3( this->half.x, -this->half.y, this->half.z);
            break;
        case 4:
            corner = this->center + Vec3( -this->half.x, this->half.y, -this->half.z);
            break;
        case 5:
            corner = this->center + Vec3( this->half.x, this->half.y, -this->half.z);
            break;
        case 6:
            corner = this->center + Vec3( -this->half.x, this->half.y, this->half.z);
            break;
        case 7:
            corner = this->center + this->half;
            break;
    };
    return corner;
}
