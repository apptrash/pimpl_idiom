#include "fridge.h"
#include "engine.h"
#include <iostream>

class FridgeImpl final {
 public:
  void CoolDown() const;
 private:
  Engine engine_;
};

void FridgeImpl::CoolDown() const {
  std::cout << "Let's just cool you down a little bit, huh?\n";
  engine_.DoCoolStuff();
}

Fridge::Fridge() : impl_(std::make_unique<FridgeImpl>()) {}
Fridge::~Fridge() = default;

void Fridge::CoolDown() const
{
  impl_->CoolDown();
}
