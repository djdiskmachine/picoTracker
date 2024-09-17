#include "Config.h"
#include "Application/Persistency/PersistencyDocument.h"
#include "Externals/etl/include/etl/flat_map.h"
#include "Externals/etl/include/etl/string.h"
#include "Externals/etl/include/etl/string_utilities.h"
#include <stdlib.h>

#define CONFIG_FILE_PATH "/.config.xml"
#define CONFIG_VERSION_NUMBER 1

static const char *lineOutOptions[3] = {"Line level", "HP High", "HP Low"};

// Param keys MUST fit in this length limit!
typedef etl::string<12> ParamString;

static const etl::flat_map validParameters{
    etl::pair{ParamString("BACKGROUND"), 0x0F0F0F},
    etl::pair{ParamString("FOREGROUND"), 0xADADAD},
    etl::pair{ParamString("HICOLOR1"), 0x846F94},
    etl::pair{ParamString("HICOLOR2"), 0x6B316B},
    etl::pair{ParamString("CONSOLECOLOR"), 0xFF00FF},
    etl::pair{ParamString("CURSORCOLOR"), 0x776B56},
    etl::pair{ParamString("INFOCOLOR"), 0x29EE3D},
    etl::pair{ParamString("WARNCOLOR"), 0xEFFA52},
    etl::pair{ParamString("ERRORCOLOR"), 0xE84D15},
    etl::pair{ParamString("LINEOUT"), 0x2},
    etl::pair{ParamString("MIDIDEVICE"), 0x0},
    etl::pair{ParamString("MIDISYNC"), 0x1},
};

Config::Config() : lineOut_("lineout", VAR_LINEOUT, lineOutOptions, 3, 0) {
  PersistencyDocument doc;

  if (!doc.Load(CONFIG_FILE_PATH)) {
    Trace::Error("CONFIG: Could not open file for reading: %s",
                 CONFIG_FILE_PATH);
    useDefaultConfig();
    return;
  }

  bool elem = doc.FirstChild();
  if (!elem || strcmp(doc.ElemName(), "CONFIG")) {
    Trace::Log("CONFIG", "Bad config.xml format!");
    // TODO: need show user some UI that config file is invalid
    useDefaultConfig();
    return;
  }
  elem = doc.FirstChild(); // now get first child element of CONFIG
  while (elem) {
    if (!validParameters.contains(ParamString(doc.ElemName()))) {
      Trace::Log("CONFIG", "Found unknown config parameter \"%s\", skipping...",
                 doc.ElemName());
      break;
    }
    bool hasAttr = doc.NextAttribute();
    while (hasAttr) {
      if (!strcasecmp(doc.attrname_, "VALUE")) {
        processParams(doc.ElemName(), atoi(doc.attrval_));
        Trace::Log("CONFIG", "Read Param:%s->[%s]", doc.ElemName(),
                   doc.attrval_);
      }
      hasAttr = doc.NextAttribute();
    }
    elem = doc.NextSibling();
  }
  Trace::Log("CONFIG", "Loaded successfully");
}

Config::~Config() {}

void Config::Save() {
  auto picoFS = PicoFileSystem::GetInstance();
  PI_File *fp = picoFS->Open(CONFIG_FILE_PATH, "w");
  if (!fp) {
    Trace::Error("CONFIG: Could not open file for writing: %s",
                 CONFIG_FILE_PATH);
  }
  Trace::Log("PERSISTENCYSERVICE", "Opened Proj File: %s\n", CONFIG_FILE_PATH);
  tinyxml2::XMLPrinter printer(fp);

  SaveContent(&printer);

  fp->Close();
}

void Config::SaveContent(tinyxml2::XMLPrinter *printer) {
  // store config version
  printer->OpenElement("CONFIG");
  printer->PushAttribute("VERSION", CONFIG_VERSION_NUMBER);

  // save all of the config parameters
  auto it = begin();
  for (size_t i = 0; i < size(); i++) {
    etl::string<16> elemName = (*it)->GetName();
    to_upper_case(elemName);
    printer->OpenElement(elemName.c_str());
    if (elemName.compare("LINEOUT") == 0) {
      printer->PushAttribute("VALUE", std::to_string((*it)->GetInt()).c_str());
    } else {
      printer->PushAttribute("VALUE", (*it)->GetString().c_str());
    }
    printer->CloseElement();
    it++;
  }
  printer->CloseElement();
  Trace::Log("CONFIG", "Saved config");
};

int Config::GetValue(const char *key) {
  Variable *v = FindVariable(key);
  if (v) {
    Trace::Log("CONFIG", "Got value for %s=%s", key, v->GetString().c_str());
  } else {
    Trace::Log("CONFIG", "No value for requested key:%s", key);
  }
  return v ? v->GetInt() : 0;
};

// need to handle some variable like LINEOUT separately
void Config::processParams(const char *name, int value) {
  if (!strcmp(name, "LINEOUT")) {
    lineOut_.SetInt(value);
    insert(end(), &lineOut_);
  } else {
    auto fourcc = 0;
    // TODO: need to be able to assign fourcc based on name of element from the
    // Xml config
    if (!strcmp(name, "FOREGROUND")) {
      fourcc = VAR_FG_COLOR;
    } else if (!strcmp(name, "BACKGROUND")) {
      fourcc = VAR_BG_COLOR;
    } else if (!strcmp(name, "HICOLOR1")) {
      fourcc = VAR_HI1_COLOR;
    } else if (!strcmp(name, "HICOLOR2")) {
      fourcc = VAR_HI2_COLOR;
    } else if (!strcmp(name, "CONSOLECOLOR")) {
      fourcc = VAR_CONSOLE_COLOR;
    } else if (!strcmp(name, "CURSORCOLOR")) {
      fourcc = VAR_CURSOR_COLOR;
    } else if (!strcmp(name, "INFOCOLOR")) {
      fourcc = VAR_INFO_COLOR;
    } else if (!strcmp(name, "WARNCOLOR")) {
      fourcc = VAR_WARN_COLOR;
    } else if (!strcmp(name, "ERRORCOLOR")) {
      fourcc = VAR_ERROR_COLOR;
    } else if (!strcmp(name, "MIDIDEVICE")) {
      fourcc = VAR_MIDI_DEVICE;
    } else if (!strcmp(name, "MIDISYNC")) {
      fourcc = VAR_MIDI_SYNC;
    }
    Variable *v = new Variable(name, fourcc, value);
    insert(end(), v);
  }
}

void Config::useDefaultConfig() {
  Trace::Log("CONFIG", "Setting DEFAULT values for config parameters");
  for (auto const &p : validParameters) {
    processParams(p.first.c_str(), p.second);
  }
  Save(); // and write the defaults to SDCard
}