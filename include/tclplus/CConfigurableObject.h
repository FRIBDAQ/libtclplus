/*
    This software is Copyright by the Board of Trustees of Michigan
    State University (c) Copyright 2005.

    You may use this software under the terms of the GNU public license
    (GPL).  The terms of this license are described at:

     http://www.gnu.org/licenses/gpl.txt

     Author:
             Ron Fox
	     NSCL
	     Michigan State University
	     East Lansing, MI 48824-1321
*/

#ifndef CCONFIGURABLEOBJECT_H
#define CCONFIGURABLEOBJECT_H

#include <string>

#ifndef CITEMCONFIGURATION_H
#include "CItemConfiguration.h"
#endif

/*!
  This is the base class for an item that has a configuration.
  Normally this has to be extended tremendously to be usable
  as e.g. a readout module.

  The class contains as a protected member, an object of
  type CItemConfiguration*  At construction time, this is NULL.
  It is attached via the Attach member function, whic is virtual,
  and invokes the pure virtual onAttach member function to allow
  concrete classes to setup the configuration keywords supported.

  Copy construction is supported and results in a copy of the item configuration
  itself.


  The CItemConfiguration member functions:

  - getName
  - cget
  - configure
  - clearConfiguration

  are facaded through this base class so that configurable objects can be configured
  and inquired by script level beasts that only need to manipulate configurations.

  
*/
class CConfigurableObject
{
  // Data:
protected:
  CItemConfiguration* m_pConfiguration;
private:
  bool                m_deleteOnDestroy;

  // Construction and canonicals:

public:
  CConfigurableObject();
  CConfigurableObject(const CConfigurableObject& rhs);
  virtual ~CConfigurableObject();

  CConfigurableObject& operator=(const CConfigurableObject& rsh);
  int operator==(const CConfigurableObject& rhs) const;
  int operator!=(const CConfigurableObject& rhs) const;

  // Attachment:

  void Attach(CItemConfiguration* pConfiguration, bool dynamic = true);

  // Configuration
  
  void configure(std::string name, std::string value);

  // Inquiry:

  std::string getName() const;
  std::string cget(std::string name);
  CItemConfiguration::ConfigurationArray cget();


  // Concrete classes must implement this interface:

  virtual void onAttach() = 0;	// Define the configuration parameters, normally.

  // Utilities
private:
  void throwIfNull(const char* message) const;

};

#endif
