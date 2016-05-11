#include "ControlEventReceiver.hh"

ControlEventReceiver::ControlEventReceiver() {
  _KeyIsDown.resize(irr::KEY_KEY_CODES_COUNT);
}
bool ControlEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const {
  return _KeyIsDown[keyCode].PressedDown;
}
const std::vector<irr::SEvent::SKeyInput>& ControlEventReceiver::get_key_event()
    const {
  return (_KeyIsDown);
}
const irr::SEvent::SJoystickEvent& ControlEventReceiver::get_joy_event() const {
  return (_JoystickEvent);
}
bool ControlEventReceiver::OnEvent(const irr::SEvent& event) {
  if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
    _KeyIsDown[event.KeyInput.Key] = event.KeyInput;
  }
  if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT) {
    _JoystickEvent = event.JoystickEvent;
  }
  return false;
}
