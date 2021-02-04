#include <VirtualWire.h>
void setup()
{
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
}
void loop()
{
  send("Hello there");
  delay(1000);
}
void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}
