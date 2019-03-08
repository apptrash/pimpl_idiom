#ifndef FRIDGE_H_
#define FRIDGE_H_

#include <memory>

class Fridge final {
 public:
  Fridge();
  ~Fridge();
  void CoolDown() const;
 private:
  std::unique_ptr<class FridgeImpl> impl_;
};

#endif // FRIDGE_H_
