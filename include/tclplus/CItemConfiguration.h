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

#ifndef CITEMCONFIGURATION_H
#define CITEMCONFIGURATION_H

// Necessary includes (kept to a minimum using forward class defs).

#include <string>
#include <map>			// also defines std::pair
#include <vector>
#include <set>

// Typedefs for the parameter checker are in the global namespace:

typedef bool (*typeChecker)(std::string name, std::string value, void* arg);

/*!

   An Item configuration is a set of name value pairs.  Each name value
   pair can have an associated validity checker who is responsible
   for ensuring that for any configuration value a candidate new value
   is legal.  Type checkers are just unbound functions, or static
   member functions.  See
   the typedef for typeChecker above.
 
   For convenience, some of the static functions of this class provide
   commonly used type checkers.

   How to use this:

   In general, one would create an object that contains a CItemConfiguration
   object.  That object would provide mechanisms to set/get the configuration.
   The object itself, would register the configuration names it needs.
   It would, in appropriate methods, get the values of the configuration names.

   See e.g. CConfigurableObject for a base class that can be used and that
   has those properties.
   
   The configuration subsystem would at some point call configure to set up
   the configuration (note subclassed objects can also call this to set up their
   default configuration).

   The data taking system would then call subclass functions to inform it that
   configuration is complete.  The subclass then would call cget to get and
   react to its configuration.

   This class does not implement any policy about how the configuration is gotten.
   This can be  done by manual parsing of data files, by internal data structures,
   by a Tcl interpreter reading scripts or any other practical means.
*/
class CItemConfiguration {

  // public typedefs:

public:
  typedef std::pair<typeChecker, void*>         TypeCheckInfo;	// Type checker + arg.
  typedef std::vector<std::pair<std::string, std::string> > ConfigurationArray;
  
  // Arg types for the standard type checkers.

  struct  limit {
    bool   s_checkMe;
    long    s_value;
    limit() :
      s_checkMe(false) 
    {}
    limit(long value) : 
      s_checkMe(true), 
      s_value(value) {}
  } ;
  typedef std::pair<limit, limit>   Limits;
  typedef std::set<std::string> isEnumParameter;
  typedef struct _ListSizeConstraint {
    limit s_atLeast;
    limit s_atMost;
  } ListSizeConstraint;

  typedef struct _isListParameter {
    ListSizeConstraint s_allowedSize;
    TypeCheckInfo      s_checker;
  } isListParameter;


  struct  flimit {
    bool   s_checkMe;
    float s_value;
    flimit() :
      s_checkMe(false) {}
    flimit(float value) :
      s_checkMe(true), 
      s_value(value) {}
  };

  typedef std::pair<flimit, flimit> FloatingLimits;


  // Internal typedefs
private:
  typedef std::pair<std::string, TypeCheckInfo> ConfigData;
  typedef std::map<std::string, ConfigData>     Configuration;
  typedef Configuration::iterator               ConfigIterator;


private:
  std::string     m_name;	//!< Name of this object.
  Configuration   m_parameters;	//!< Contains the configuration parameters.

public:
  // Canonicals..

  CItemConfiguration(std::string name);
  CItemConfiguration(const CItemConfiguration& rhs);
  virtual ~CItemConfiguration();
  CItemConfiguration& operator=(const CItemConfiguration& rhs);
  int operator==(const CItemConfiguration& rhs) const;
  int operator!=(const CItemConfiguration& rhs) const;

  //  Selectors:

public:
  std::string getName() const;
  std::string cget(std::string name) ;
  ConfigurationArray cget();

  // Convenience functions that get common conversions:

  int              getIntegerParameter (std::string name);
  unsigned int     getUnsignedParameter(std::string name);
  bool             getBoolParameter    (std::string name);
  double           getFloatParameter   (std::string name);
  std::vector<int> getIntegerList      (std::string name);
  
  // Operations:

public:
  // Establishing the configuration:

  void addParameter(std::string name, typeChecker checker, void* arg,
		    std::string defaultValue = std::string(""));

  void clearConfiguration();

  // Manipulating and querying the configuration:

  bool isValid(std::string name, std::string value);
  void configure(std::string name, std::string value);

 
  // common type checkers:

  static bool isInteger(std::string name, std::string value, void* arg);
  static bool isBool(   std::string name, std::string value, void* arg);
  static bool isEnum(   std::string name, std::string value, void* arg);
  static bool isFloat(  std::string name, std::string value, void* arg);
  static bool isList(   std::string name, std::string value, void* arg);
  static bool isBoolList(std::string name,std::string value, void* arg);
  static bool isIntList(std::string name, std::string value, void* arg);
  static bool isStringList(std::string name, std::string value, void* arg);

 
  // utilities:
private:
  static void addTrueValues(std::set<std::string>& values);
  static void addFalseValues(std::set<std::string>& values);
  ConfigIterator findOrThrow(std::string name);
};


#endif
