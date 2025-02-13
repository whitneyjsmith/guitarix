// Generated by gmmproc 2.66.7 -- DO NOT MODIFY!


#include <glibmm.h>

#include <gxwmm/iredit.h>
#include <gxwmm/private/iredit_p.h>


/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 */

#include <gxw/GxIREdit.h>

namespace Gxw
{

void IREdit::set_state(
	float *data, int chan, int data_len, int samplerate, int cutoff_low,
	int cutoff_high, int offset, const Gainline& gain)
{
	gx_ir_edit_set_state(
		gobj(), data, chan, data_len, samplerate, cutoff_low, cutoff_high,
		offset, gain.points(), gain.size());
}

Gainline IREdit::get_gain()
{
	gain_points* p;
	int n;
	gx_ir_edit_get_gain(gobj(), &p, &n); 
	return Gainline(p, n);
}

void IREdit::set_gain(const Gainline& g)
{
	gx_ir_edit_set_gain(gobj(), g.points(), g.size()); 
}

} // namespace Gxw

namespace
{


static void IREdit_signal_delay_changed_callback(GxIREdit* self, gint p0,gint p1,void* data)
{
  using namespace Gxw;
  using SlotType = sigc::slot< void,int,int >;

  auto obj = dynamic_cast<IREdit*>(Glib::ObjectBase::_get_current_wrapper((GObject*) self));
  // Do not try to call a signal on a disassociated wrapper.
  if(obj)
  {
    try
    {
      if(const auto slot = Glib::SignalProxyNormal::data_to_slot(data))
        (*static_cast<SlotType*>(slot))(p0
, p1
);
    }
    catch(...)
    {
       Glib::exception_handlers_invoke();
    }
  }
}

static const Glib::SignalProxyInfo IREdit_signal_delay_changed_info =
{
  "delay-changed",
  (GCallback) &IREdit_signal_delay_changed_callback,
  (GCallback) &IREdit_signal_delay_changed_callback
};


static void IREdit_signal_offset_changed_callback(GxIREdit* self, gint p0,gint p1,void* data)
{
  using namespace Gxw;
  using SlotType = sigc::slot< void,int,int >;

  auto obj = dynamic_cast<IREdit*>(Glib::ObjectBase::_get_current_wrapper((GObject*) self));
  // Do not try to call a signal on a disassociated wrapper.
  if(obj)
  {
    try
    {
      if(const auto slot = Glib::SignalProxyNormal::data_to_slot(data))
        (*static_cast<SlotType*>(slot))(p0
, p1
);
    }
    catch(...)
    {
       Glib::exception_handlers_invoke();
    }
  }
}

static const Glib::SignalProxyInfo IREdit_signal_offset_changed_info =
{
  "offset-changed",
  (GCallback) &IREdit_signal_offset_changed_callback,
  (GCallback) &IREdit_signal_offset_changed_callback
};


static void IREdit_signal_length_changed_callback(GxIREdit* self, gint p0,gint p1,void* data)
{
  using namespace Gxw;
  using SlotType = sigc::slot< void,int,int >;

  auto obj = dynamic_cast<IREdit*>(Glib::ObjectBase::_get_current_wrapper((GObject*) self));
  // Do not try to call a signal on a disassociated wrapper.
  if(obj)
  {
    try
    {
      if(const auto slot = Glib::SignalProxyNormal::data_to_slot(data))
        (*static_cast<SlotType*>(slot))(p0
, p1
);
    }
    catch(...)
    {
       Glib::exception_handlers_invoke();
    }
  }
}

static const Glib::SignalProxyInfo IREdit_signal_length_changed_info =
{
  "length-changed",
  (GCallback) &IREdit_signal_length_changed_callback,
  (GCallback) &IREdit_signal_length_changed_callback
};


static void IREdit_signal_scale_max_reached_callback(GxIREdit* self, gboolean p0,void* data)
{
  using namespace Gxw;
  using SlotType = sigc::slot< void,bool >;

  auto obj = dynamic_cast<IREdit*>(Glib::ObjectBase::_get_current_wrapper((GObject*) self));
  // Do not try to call a signal on a disassociated wrapper.
  if(obj)
  {
    try
    {
      if(const auto slot = Glib::SignalProxyNormal::data_to_slot(data))
        (*static_cast<SlotType*>(slot))(p0
);
    }
    catch(...)
    {
       Glib::exception_handlers_invoke();
    }
  }
}

static const Glib::SignalProxyInfo IREdit_signal_scale_max_reached_info =
{
  "scale-max-reached",
  (GCallback) &IREdit_signal_scale_max_reached_callback,
  (GCallback) &IREdit_signal_scale_max_reached_callback
};


static void IREdit_signal_scale_min_reached_callback(GxIREdit* self, gboolean p0,void* data)
{
  using namespace Gxw;
  using SlotType = sigc::slot< void,bool >;

  auto obj = dynamic_cast<IREdit*>(Glib::ObjectBase::_get_current_wrapper((GObject*) self));
  // Do not try to call a signal on a disassociated wrapper.
  if(obj)
  {
    try
    {
      if(const auto slot = Glib::SignalProxyNormal::data_to_slot(data))
        (*static_cast<SlotType*>(slot))(p0
);
    }
    catch(...)
    {
       Glib::exception_handlers_invoke();
    }
  }
}

static const Glib::SignalProxyInfo IREdit_signal_scale_min_reached_info =
{
  "scale-min-reached",
  (GCallback) &IREdit_signal_scale_min_reached_callback,
  (GCallback) &IREdit_signal_scale_min_reached_callback
};


} // anonymous namespace


namespace Glib
{

Gxw::IREdit* wrap(GxIREdit* object, bool take_copy)
{
  return dynamic_cast<Gxw::IREdit *> (Glib::wrap_auto ((GObject*)(object), take_copy));
}

} /* namespace Glib */

namespace Gxw
{


/* The *_Class implementation: */

const Glib::Class& IREdit_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &IREdit_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gx_ir_edit_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:

  }

  return *this;
}


void IREdit_Class::class_init_function(void* g_class, void* class_data)
{
  const auto klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);


}


Glib::ObjectBase* IREdit_Class::wrap_new(GObject* o)
{
  return manage(new IREdit((GxIREdit*)(o)));

}


/* The implementation: */

IREdit::IREdit(const Glib::ConstructParams& construct_params)
:
  Gtk::DrawingArea(construct_params)
{
  }

IREdit::IREdit(GxIREdit* castitem)
:
  Gtk::DrawingArea((GtkDrawingArea*)(castitem))
{
  }


IREdit::IREdit(IREdit&& src) noexcept
: Gtk::DrawingArea(std::move(src))
{}

IREdit& IREdit::operator=(IREdit&& src) noexcept
{
  Gtk::DrawingArea::operator=(std::move(src));
  return *this;
}

IREdit::~IREdit() noexcept
{
  destroy_();
}

IREdit::CppClassType IREdit::iredit_class_; // initialize static member

GType IREdit::get_type()
{
  return iredit_class_.init().get_type();
}


GType IREdit::get_base_type()
{
  return gx_ir_edit_get_type();
}


IREdit::IREdit()
:
  // Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(nullptr),
  Gtk::DrawingArea(Glib::ConstructParams(iredit_class_.init()))
{
  

}

void IREdit::set_ir_data(float* p1, int p2, int p3, int p4)
{
  gx_ir_edit_set_ir_data(gobj(), p1, p2, p3, p4);
}

void IREdit::home()
{
  gx_ir_edit_home(gobj());
}

void IREdit::jump_zoom_mark()
{
  gx_ir_edit_jump_zoom_mark(gobj());
}

void IREdit::set_channel(int p1)
{
  gx_ir_edit_set_channel(gobj(), p1);
}

void IREdit::incr_scale(double p1)
{
  gx_ir_edit_incr_scale(gobj(), p1);
}

void IREdit::decr_scale(double p1)
{
  gx_ir_edit_decr_scale(gobj(), p1);
}

void IREdit::set_log(bool p1)
{
  gx_ir_edit_set_log(gobj(), static_cast<int>(p1));
}

int IREdit::get_delay()
{
  return gx_ir_edit_get_delay(gobj());
}

void IREdit::set_delay(int p1)
{
  gx_ir_edit_set_delay(gobj(), p1);
}

int IREdit::get_offset()
{
  return gx_ir_edit_get_offset(gobj());
}

void IREdit::set_offset(int p1)
{
  gx_ir_edit_set_offset(gobj(), p1);
}

int IREdit::get_length()
{
  return gx_ir_edit_get_length(gobj());
}

void IREdit::set_length(int p1)
{
  gx_ir_edit_set_length(gobj(), p1);
}


Glib::SignalProxy< void,int,int > IREdit::signal_delay_changed()
{
  return Glib::SignalProxy< void,int,int >(this, &IREdit_signal_delay_changed_info);
}


Glib::SignalProxy< void,int,int > IREdit::signal_offset_changed()
{
  return Glib::SignalProxy< void,int,int >(this, &IREdit_signal_offset_changed_info);
}


Glib::SignalProxy< void,int,int > IREdit::signal_length_changed()
{
  return Glib::SignalProxy< void,int,int >(this, &IREdit_signal_length_changed_info);
}


Glib::SignalProxy< void,bool > IREdit::signal_scale_max_reached()
{
  return Glib::SignalProxy< void,bool >(this, &IREdit_signal_scale_max_reached_info);
}


Glib::SignalProxy< void,bool > IREdit::signal_scale_min_reached()
{
  return Glib::SignalProxy< void,bool >(this, &IREdit_signal_scale_min_reached_info);
}


Glib::PropertyProxy< int > IREdit::property_y_border_top() 
{
  return Glib::PropertyProxy< int >(this, "y-border-top");
}

Glib::PropertyProxy_ReadOnly< int > IREdit::property_y_border_top() const
{
  return Glib::PropertyProxy_ReadOnly< int >(this, "y-border-top");
}

Glib::PropertyProxy< int > IREdit::property_y_border_bottom() 
{
  return Glib::PropertyProxy< int >(this, "y-border-bottom");
}

Glib::PropertyProxy_ReadOnly< int > IREdit::property_y_border_bottom() const
{
  return Glib::PropertyProxy_ReadOnly< int >(this, "y-border-bottom");
}

Glib::PropertyProxy< int > IREdit::property_x_border() 
{
  return Glib::PropertyProxy< int >(this, "x-border");
}

Glib::PropertyProxy_ReadOnly< int > IREdit::property_x_border() const
{
  return Glib::PropertyProxy_ReadOnly< int >(this, "x-border");
}

Glib::PropertyProxy< int > IREdit::property_label_sep() 
{
  return Glib::PropertyProxy< int >(this, "label-sep");
}

Glib::PropertyProxy_ReadOnly< int > IREdit::property_label_sep() const
{
  return Glib::PropertyProxy_ReadOnly< int >(this, "label-sep");
}

Glib::PropertyProxy< double > IREdit::property_dot_diameter() 
{
  return Glib::PropertyProxy< double >(this, "dot-diameter");
}

Glib::PropertyProxy_ReadOnly< double > IREdit::property_dot_diameter() const
{
  return Glib::PropertyProxy_ReadOnly< double >(this, "dot-diameter");
}

Glib::PropertyProxy< double > IREdit::property_segment_distance() 
{
  return Glib::PropertyProxy< double >(this, "segment-distance");
}

Glib::PropertyProxy_ReadOnly< double > IREdit::property_segment_distance() const
{
  return Glib::PropertyProxy_ReadOnly< double >(this, "segment-distance");
}

Glib::PropertyProxy< double > IREdit::property_limit() 
{
  return Glib::PropertyProxy< double >(this, "limit");
}

Glib::PropertyProxy_ReadOnly< double > IREdit::property_limit() const
{
  return Glib::PropertyProxy_ReadOnly< double >(this, "limit");
}

Glib::PropertyProxy_ReadOnly< int > IREdit::property_fs() const
{
  return Glib::PropertyProxy_ReadOnly< int >(this, "fs");
}

Glib::PropertyProxy< double > IREdit::property_max_scale_fact() 
{
  return Glib::PropertyProxy< double >(this, "max-scale-fact");
}

Glib::PropertyProxy_ReadOnly< double > IREdit::property_max_scale_fact() const
{
  return Glib::PropertyProxy_ReadOnly< double >(this, "max-scale-fact");
}

Glib::PropertyProxy< double > IREdit::property_min_scale() 
{
  return Glib::PropertyProxy< double >(this, "min-scale");
}

Glib::PropertyProxy_ReadOnly< double > IREdit::property_min_scale() const
{
  return Glib::PropertyProxy_ReadOnly< double >(this, "min-scale");
}

Glib::PropertyProxy< double > IREdit::property_scale() 
{
  return Glib::PropertyProxy< double >(this, "scale");
}

Glib::PropertyProxy_ReadOnly< double > IREdit::property_scale() const
{
  return Glib::PropertyProxy_ReadOnly< double >(this, "scale");
}

Glib::PropertyProxy< Glib::ustring > IREdit::property_no_data_text() 
{
  return Glib::PropertyProxy< Glib::ustring >(this, "no-data-text");
}

Glib::PropertyProxy_ReadOnly< Glib::ustring > IREdit::property_no_data_text() const
{
  return Glib::PropertyProxy_ReadOnly< Glib::ustring >(this, "no-data-text");
}


} // namespace Gxw


