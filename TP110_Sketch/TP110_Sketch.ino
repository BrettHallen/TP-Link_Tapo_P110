/********************************************/
/* Simple Arduino Mega - TP-Link Tapo P110  */
/* MCU (Realtek RTL8710CF) Serial Interface */
/* Brett Hallen, 6/Apr/2026                 */
/*                                          */
/* Mega      P110  Purpose                  */
/* --------  ----  -------------------      */
/* RX1 (19)  TP6   Serial TX from MCU       */
/* TX1 (18)  TP5   Serial RX to MCU         */
/* 3.3V      TP3   3.3V power supply        */
/* GND       TP4   Ground                   */
/*                                          */
/* RTL8710CF serial interface:              */
/* 115200bps, 8N1                           */
/********************************************/

bool hexDump = false; /* Change to true for hex output of received data  */
bool autoSend = false; /* Auto-send commands to try to trigger a response */

/******************/
/* Send a command */
/******************/
void sendCommand(const char* cmd, bool autoSend) 
{
  if (autoSend)
  {
    Serial.print(F(">> [AUTO] Sending: "));
  }
  else
  {
    Serial.print(F(">> [MAN] Sending: "));
  }
  Serial.println(cmd);
  Serial1.print(cmd);
  Serial1.print(F("\r\n"));
}

/******************/
/* Send raw input */
/******************/
void sendRaw(const String& cmd)
{
  Serial.print(F(">> [MAN] Sending: "));
  Serial.println(cmd);
  Serial1.print(cmd);
  Serial1.print(F("\r\n"));
}

/*****************/
/***** SETUP *****/
/*****************/
void setup() 
{
  Serial.begin(115200);   /* Serial from Tapo MCU to PC */
  Serial1.begin(115200);  /* Serial from PC to Tapo MCU */

  while (!Serial) { ; }   /* Wait for Serial Monitor */

  Serial.println(F(">> Arduino Mega Serial Passthrough for Tapo P110 MCU"));
  Serial.println(F("   TP6 = Serial TX from MXU"));
  Serial.println(F("   TP5 = Serial RX to MXU"));
  Serial.println(F("   115200 8N1"));
  Serial.println(F("======================================"));
  Serial.println(F("Menu (type and press ENTER):"));
  Serial.println(F("  h  = help / ?"));
  Serial.println(F("  r  = reboot (ATSR)"));
  Serial.println(F("  s  = Wi-Fi scan (ATWS)"));
  Serial.println(F("  a  = AT test")); 
  Serial.println(F("  d  = debug mode toggle"));
  Serial.println(F("  x  = toggle hex dump"));
  Serial.println(F("  any other text = send as-is"));
  Serial.println(F("======================================"));

  /* Wait for the Tapo MCU to finish booting */
  delay(2000); /* 2s */

  if (autoSend)
  {
    Serial.println(F(">> [AUTO] Sending newline to wake console ..."));
    Serial1.println();

    delay(800); /* 0.8s */

    /* Auto-send common Realtek debug commands */
    sendCommand("help",true);
    delay(400);               /* 0.4s */
    sendCommand("?",true);
    delay(400);               /* 0.4s */
    sendCommand("AT",true);
    delay(400);               /* 0.4s */
    sendCommand("ATSR",true); /* Reboot test */
    delay(400);               /* 0.4s */
    sendCommand("ATWS",true); /* Wi-Fi scan */
  }
}

/*********************/
/***** MAIN LOOP *****/
/*********************/
void loop() 
{
  /* Forward Tapo MCU to PC */
  if (Serial1.available()) 
  {
    char c = Serial1.read();
    if (hexDump) 
    {
      Serial.print("0x");
      if (c < 0x10) Serial.print("0");
      Serial.print(c, HEX);
      Serial.print(" ");
      if (c == '\n') Serial.println();
    } 
    else 
    {
      Serial.write(c);
    }
  }

  /* Forward PC to Tapo MCU + handle menu */
  if (Serial.available()) 
  {
    String input = Serial.readStringUntil('\n');
    input.trim();

    /* Ignore empty lines */
    if (input.length() == 0) return;

    if (input.length() == 1)
    {
      char cmd = input.charAt(0);
      switch (cmd)
      {
        case 'h':
        case '?':
         sendCommand("help",false);
         break;
        case 'r':
          sendCommand("ATSR",false);
          break;
        case 's':
          sendCommand("ATWS",false);
          break;
        case 'a':
          sendCommand("AT",false);
          break;
        case 'd':
          sendCommand("debug",false);
          break;
        case 'x':
          hexDump = !hexDump;
          Serial.print(F(">> Hex dump :"));
          Serial.println(hexDump ? "ENABLED" : "DISABLED");
          break;
        default:
          sendRaw(input); /* Send undefined single character */
          break;
      }
    }
    else
    {
      /* Send anything else directly/raw */
      sendRaw(input);
    }
  }
}