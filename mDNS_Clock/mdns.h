#pragma once

#include <ESP8266mDNS.h>
#include <PolledTimeout.h>

#include "ntpclock.h"
#include "dallastemp.h"

/*
   Include the MDNSResponder (the library needs to be included also)
   As LEA MDNSResponder is experimantal in the ESP8266 environment currently, the
   legacy MDNSResponder is defaulted in th include file.
   There are two ways to access LEA MDNSResponder:
   1. Prepend every declaration and call to global declarations or functions with the namespace, like:
      'LEAmDNS::MDNSResponder::hMDNSService  hMDNSService;'
      This way is used in the example. But be careful, if the namespace declaration is missing
      somewhere, the call might go to the legacy implementation...
   2. Open 'ESP8266mDNS.h' and set LEAmDNS to default.

*/

namespace mdns {

  char*                         pcHostDomain            = 0;        // Negociated host domain
  bool                          bHostDomainConfirmed    = false;    // Flags the confirmation of the host domain
  MDNSResponder::hMDNSService   hMDNSService            = 0;        // The handle of the clock service in the MDNS responder

  bool setStationHostname(const char* p_pcHostname) {

    if (p_pcHostname) {
      WiFi.hostname(p_pcHostname);
      Serial.printf("setDeviceHostname: Station hostname is set to '%s'\n", p_pcHostname);
    }
    return true;
  }


  /*
     MDNSDynamicServiceTxtCallback

     Add a dynamic MDNS TXT item 'ct' to the clock service.
     The callback function is called every time, the TXT items for the clock service
     are needed.
     This can be triggered by calling MDNS.announce().

  */
  void MDNSDynamicServiceTxtCallback(const MDNSResponder::hMDNSService p_hService) {
    Serial.println("MDNSDynamicServiceTxtCallback");

    if (hMDNSService == p_hService) {
      Serial.printf("Updating curtime TXT item to: %s\n", ntpclock::getTimeString());
      MDNS.addDynamicServiceTxt(p_hService, "curtime", ntpclock::getTimeString());
      MDNS.addDynamicServiceTxt(p_hService, "temp_c", dallastemp::temperature().c_str());
    }
  }


  /*
     MDNSProbeResultCallback

     Probe result callback for the host domain.
     If the domain is free, the host domain is set and the clock service is
     added.
     If the domain is already used, a new name is created and the probing is
     restarted via p_pMDNSResponder->setHostname().

  */
  void hostProbeResult(String p_pcDomainName, bool p_bProbeResult) {

    Serial.println("MDNSProbeResultCallback");
    Serial.printf("MDNSProbeResultCallback: Host domain '%s.local' is %s\n", p_pcDomainName.c_str(), (p_bProbeResult ? "free" : "already USED!"));
    if (true == p_bProbeResult) {
      // Set station hostname
      setStationHostname(pcHostDomain);

      if (!bHostDomainConfirmed) {
        // Hostname free -> setup clock service
        bHostDomainConfirmed = true;

        if (!hMDNSService) {
          // Add a 'clock.tcp' service to port 'SERVICE_PORT', using the host domain as instance domain
          hMDNSService = MDNS.addService(0, "espclk", "tcp", SERVICE_PORT);
          if (hMDNSService) {
            // Add a simple static MDNS service TXT item
            MDNS.addServiceTxt(hMDNSService, "port#", SERVICE_PORT);
            // Set the callback function for dynamic service TXTs
            MDNS.setDynamicServiceTxtCallback(MDNSDynamicServiceTxtCallback);
          }
        }
      }
    } else {
      // Change hostname, use '-' as divider between base name and index
      if (MDNSResponder::indexDomain(pcHostDomain, "-", 0)) {
        MDNS.setHostname(pcHostDomain);
      } else {
        Serial.println("MDNSProbeResultCallback: FAILED to update hostname!");
      }
    }
  }

  void setup() {
    // Setup MDNS responder
    MDNS.setHostProbeResultCallback(hostProbeResult);
    // Init the (currently empty) host domain string with 'esp8266'
    if ((!MDNSResponder::indexDomain(pcHostDomain, 0, "esp8266")) ||
        (!MDNS.begin(pcHostDomain))) {
      Serial.println("Error setting up MDNS responder!");
      while (1) { // STOP
        delay(1000);
      }
    }
    Serial.println("MDNS responder started");
  }

  void loop() {
    MDNS.update();

    static esp8266::polledTimeout::periodicMs timeout(UPDATE_CYCLE);
    if (timeout.expired()) {

      if (hMDNSService) {
        // Just trigger a new MDNS announcement, this will lead to a call to
        // 'MDNSDynamicServiceTxtCallback', which will update the time TXT item
        MDNS.announce();
      }
    }
  }

}
