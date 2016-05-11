#ifndef CONTROLEVENTRECEIVER_HH
#define CONTROLEVENTRECEIVER_HH

#include "irrlicht.h"
#include <vector>

class ControlEventReceiver : public irr::IEventReceiver {
 public:
  virtual bool OnEvent(const irr::SEvent& event);
  const irr::SEvent::SJoystickEvent& get_joy_event() const;
  const std::vector<irr::SEvent::SKeyInput>& get_key_event() const;
  virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
  ControlEventReceiver();

 private:
  std::vector<irr::SEvent::SKeyInput> _KeyIsDown;
  irr::SEvent::SJoystickEvent _JoystickEvent;
};

#endif  // CONTROLEVENTRECEIVER_HH
