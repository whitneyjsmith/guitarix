// Generated by gmmproc 2.64.2 -- DO NOT MODIFY!


#include <glibmm.h>

#include <gxwmm/waveview.h>
#include <gxwmm/private/waveview_p.h>


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

#include <gxw/GxWaveView.h>

namespace
{
} // anonymous namespace


namespace Glib
{

Gxw::WaveView* wrap(GxWaveView* object, bool take_copy)
{
  return dynamic_cast<Gxw::WaveView *> (Glib::wrap_auto ((GObject*)(object), take_copy));
}

} /* namespace Glib */

namespace Gxw
{


/* The *_Class implementation: */

const Glib::Class& WaveView_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &WaveView_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gx_wave_view_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:

  }

  return *this;
}


void WaveView_Class::class_init_function(void* g_class, void* class_data)
{
  const auto klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);


}


Glib::ObjectBase* WaveView_Class::wrap_new(GObject* o)
{
  return manage(new WaveView((GxWaveView*)(o)));

}


/* The implementation: */

WaveView::WaveView(const Glib::ConstructParams& construct_params)
:
  Gtk::DrawingArea(construct_params)
{
  }

WaveView::WaveView(GxWaveView* castitem)
:
  Gtk::DrawingArea((GtkDrawingArea*)(castitem))
{
  }


WaveView::WaveView(WaveView&& src) noexcept
: Gtk::DrawingArea(std::move(src))
{}

WaveView& WaveView::operator=(WaveView&& src) noexcept
{
  Gtk::DrawingArea::operator=(std::move(src));
  return *this;
}

WaveView::~WaveView() noexcept
{
  destroy_();
}

WaveView::CppClassType WaveView::waveview_class_; // initialize static member

GType WaveView::get_type()
{
  return waveview_class_.init().get_type();
}


GType WaveView::get_base_type()
{
  return gx_wave_view_get_type();
}


WaveView::WaveView()
:
  // Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(nullptr),
  Gtk::DrawingArea(Glib::ConstructParams(waveview_class_.init()))
{
  

}

void WaveView::set_multiplicator(double p1, double p2)
{
  gx_wave_view_set_multiplicator(gobj(), p1, p2);
}

void WaveView::set_frame(const float* p1, int p2)
{
  gx_wave_view_set_frame(gobj(), p1, p2);
}

void WaveView::set_text(const Glib::ustring& p1, Gtk::CornerType p2)
{
  gx_wave_view_set_text(gobj(), p1.c_str(), ((GtkCornerType)(p2)));
}


Glib::PropertyProxy< Glib::ustring > WaveView::property_text_top_left() 
{
  return Glib::PropertyProxy< Glib::ustring >(this, "text-top-left");
}

Glib::PropertyProxy_ReadOnly< Glib::ustring > WaveView::property_text_top_left() const
{
  return Glib::PropertyProxy_ReadOnly< Glib::ustring >(this, "text-top-left");
}

Glib::PropertyProxy< Glib::ustring > WaveView::property_text_top_right() 
{
  return Glib::PropertyProxy< Glib::ustring >(this, "text-top-right");
}

Glib::PropertyProxy_ReadOnly< Glib::ustring > WaveView::property_text_top_right() const
{
  return Glib::PropertyProxy_ReadOnly< Glib::ustring >(this, "text-top-right");
}

Glib::PropertyProxy< Glib::ustring > WaveView::property_text_bottom_left() 
{
  return Glib::PropertyProxy< Glib::ustring >(this, "text-bottom-left");
}

Glib::PropertyProxy_ReadOnly< Glib::ustring > WaveView::property_text_bottom_left() const
{
  return Glib::PropertyProxy_ReadOnly< Glib::ustring >(this, "text-bottom-left");
}

Glib::PropertyProxy< Glib::ustring > WaveView::property_text_bottom_right() 
{
  return Glib::PropertyProxy< Glib::ustring >(this, "text-bottom-right");
}

Glib::PropertyProxy_ReadOnly< Glib::ustring > WaveView::property_text_bottom_right() const
{
  return Glib::PropertyProxy_ReadOnly< Glib::ustring >(this, "text-bottom-right");
}

Glib::PropertyProxy< double > WaveView::property_text_pos_left() 
{
  return Glib::PropertyProxy< double >(this, "text-pos-left");
}

Glib::PropertyProxy_ReadOnly< double > WaveView::property_text_pos_left() const
{
  return Glib::PropertyProxy_ReadOnly< double >(this, "text-pos-left");
}

Glib::PropertyProxy< double > WaveView::property_text_pos_right() 
{
  return Glib::PropertyProxy< double >(this, "text-pos-right");
}

Glib::PropertyProxy_ReadOnly< double > WaveView::property_text_pos_right() const
{
  return Glib::PropertyProxy_ReadOnly< double >(this, "text-pos-right");
}


} // namespace Gxw


