#include "Collider.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset)
    : Component(associated), box(0, 0, 0, 0), scale(scale), offset(offset) {}

void Collider::Update(float dt) {
  box = Rect(associated.box.x + offset.x, associated.box.y + offset.y,
             associated.box.w * scale.x, associated.box.h * scale.y);
}

void Collider::Render() {}

bool Collider::Is(std::string type) { return type == "Collider"; }
void Collider::SetScale(Vec2 scale) { this->scale = scale; }
void Collider::SetOffset(Vec2 offset) { this->offset = offset; }
