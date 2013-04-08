/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose, Steve Poskitt
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * --------------------------------------------------------------------------
 */


////////////////////////////// LOCAL INCLUDES //////////////////////////

#include "gx_common.h"      // faust support and denormal protection (SSE)
#include "gx_studiopre.h"        // define struct PortIndex
#include "gx_pluginlv2.h"   // define struct PluginLV2
#include "gx_studiopre.cc"    // dsp class generated by faust -> dsp2cc

////////////////////////////// PLUG-IN CLASS ///////////////////////////

class Gx_studiopre
{
private:
  // internal stuff
  float*                       output;
  float*                       input;
  PluginLV2*                   studiopre_mono;
public:

  inline void run_dsp_mono(uint32_t n_samples);
  inline void connect_mono(uint32_t port,void* data);
  inline void init_dsp_mono(uint32_t rate);
  inline void connect_all_mono_ports(uint32_t port, void* data);
  inline void activate_f();
  inline void clean_up();
  Gx_studiopre();
  ~Gx_studiopre();
};

// constructor
Gx_studiopre::Gx_studiopre() :
  output(NULL),
  input(NULL),
  studiopre_mono(gx_studiopre::plugin()) {};

// destructor
Gx_studiopre::~Gx_studiopre()
{
  // just to be sure the plug have given free the allocated mem
  // it didn't hurd if the mem is already given free by clean_up()
 // studiopre_mono->activate_plugin(false, studiopre_mono);
  // delete DSP class
  studiopre_mono->delete_instance(studiopre_mono);
};

////////////////////////////// PLUG-IN CLASS  FUNCTIONS ////////////////

void Gx_studiopre::init_dsp_mono(uint32_t rate)
{
  AVOIDDENORMALS(); // init the SSE denormal protection
  studiopre_mono->set_samplerate(rate, studiopre_mono); // init the DSP class
  
}

// connect the Ports used by the plug-in class
void Gx_studiopre::connect_mono(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case EFFECTS_OUTPUT:
      output = static_cast<float*>(data);
      break;
    case EFFECTS_INPUT:
      input = static_cast<float*>(data);
      break;
    default:
      break;
    }
}

void Gx_studiopre::activate_f()
{
  // allocate the internal DSP mem
  //  studiopre_mono->activate_plugin(true, studiopre_mono);
}

void Gx_studiopre::clean_up()
{
  // delete the internal DSP mem
 // studiopre_mono->activate_plugin(false, studiopre_mono);
}

void Gx_studiopre::run_dsp_mono(uint32_t n_samples)
{
  studiopre_mono->mono_audio(static_cast<int>(n_samples), input,
                        output, studiopre_mono);
}

void Gx_studiopre::connect_all_mono_ports(uint32_t port, void* data)
{
  // connect the Ports used by the plug-in class
  connect_mono(port,data); 
  // connect the Ports used by the DSP class
  studiopre_mono->connect_ports(port,  data, studiopre_mono);
}

///////////////////////////// LV2 defines //////////////////////////////

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
  // init the plug-in class
  Gx_studiopre *self = new Gx_studiopre();
  if (!self)
    {
      return NULL;
    }
  self->init_dsp_mono((uint32_t)rate);

  return (LV2_Handle)self;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  // connect all ports
  
  static_cast<Gx_studiopre*>(instance)->connect_all_mono_ports(port, data);
}

static void
activate(LV2_Handle instance)
{
  // allocate needed mem
 
  static_cast<Gx_studiopre*>(instance)->activate_f();
}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  // run dsp
  
  static_cast<Gx_studiopre*>(instance)->run_dsp_mono(n_samples);
}

static void
cleanup(LV2_Handle instance)
{
  // well, clean up after us
  Gx_studiopre* self = static_cast<Gx_studiopre*>(instance);
  self->clean_up();
  delete self;
}

///////////////////////////// LV2 DESCRIPTOR ///////////////////////////

static const LV2_Descriptor descriptor =
{
  GXPLUGIN_URI "#studiopre",
  instantiate,
  connect_port,
  activate,
  run,
  NULL,
  cleanup,
  NULL
};

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index)
    {
    case 0:
      return &descriptor;
    default:
      return NULL;
    }
}

///////////////////////////// FIN //////////////////////////////////////