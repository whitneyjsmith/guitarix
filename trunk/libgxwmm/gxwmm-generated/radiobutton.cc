// Generated by gmmproc 2.66.7 -- DO NOT MODIFY!


#include <glibmm.h>

#include <gxwmm/radiobutton.h>
#include <gxwmm/private/radiobutton_p.h>


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

#include <gxw/GxRadioButton.h>

namespace
{
} // anonymous namespace


namespace Glib
{

Gxw::RadioButton* wrap(GxRadioButton* object, bool take_copy)
{
  return dynamic_cast<Gxw::RadioButton *> (Glib::wrap_auto ((GObject*)(object), take_copy));
}

} /* namespace Glib */

namespace Gxw
{


/* The *_Class implementation: */

const Glib::Class& RadioButton_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &RadioButton_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gx_radio_button_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:

  }

  return *this;
}


void RadioButton_Class::class_init_function(void* g_class, void* class_data)
{
  const auto klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);


}


Glib::ObjectBase* RadioButton_Class::wrap_new(GObject* o)
{
  return manage(new RadioButton((GxRadioButton*)(o)));

}


/* The implementation: */

RadioButton::RadioButton(const Glib::ConstructParams& construct_params)
:
  Gtk::RadioButton(construct_params)
{
  }

RadioButton::RadioButton(GxRadioButton* castitem)
:
  Gtk::RadioButton((GtkRadioButton*)(castitem))
{
  }


RadioButton::RadioButton(RadioButton&& src) noexcept
: Gtk::RadioButton(std::move(src))
{}

RadioButton& RadioButton::operator=(RadioButton&& src) noexcept
{
  Gtk::RadioButton::operator=(std::move(src));
  return *this;
}

RadioButton::~RadioButton() noexcept
{
  destroy_();
}

RadioButton::CppClassType RadioButton::radiobutton_class_; // initialize static member

GType RadioButton::get_type()
{
  return radiobutton_class_.init().get_type();
}


GType RadioButton::get_base_type()
{
  return gx_radio_button_get_type();
}


RadioButton::RadioButton()
:
  // Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(nullptr),
  Gtk::RadioButton(Glib::ConstructParams(radiobutton_class_.init()))
{
  

}


Glib::PropertyProxy< Glib::ustring > RadioButton::property_base_name() 
{
  return Glib::PropertyProxy< Glib::ustring >(this, "base-name");
}

Glib::PropertyProxy_ReadOnly< Glib::ustring > RadioButton::property_base_name() const
{
  return Glib::PropertyProxy_ReadOnly< Glib::ustring >(this, "base-name");
}


} // namespace Gxw


