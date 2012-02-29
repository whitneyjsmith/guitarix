/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
* ---------------------------------------------------------------------------
*
*    This file is a part ofthe gx_head interface builder
*    and build the mono effect rack,
*
* ----------------------------------------------------------------------------
*/

#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

// -------- the gx_head user interface build instruktions

namespace gx_gui {
#if 0
class RackTunerBox: public sigc::trackable {
private:
    static struct TuningTab {
	const char *name;
	const char* key;
	bool flat;
    int notes[6];
    } tuning_tab[3];
    Gxw::RackTuner tuner;
    float scale_lim;
    int streaming;
    float refpitch;
    int tuning_mode;
    int current_mode;
    bool tuner_ui;
    GxMainInterface& intf;
    void freq_poll();
    void on_off(bool v);
    bool set_active();
public:
    RackTunerBox(GxMainInterface& intf);
};

RackTunerBox::TuningTab RackTunerBox::tuning_tab[] = {
    { "Standard",    "E",  false, {40, 45, 50, 55, 59, 64}},
    { "Standard/Es", "Es", true,  {39, 44, 49, 54, 58, 63}},
    { "Open E",      "E",  false, {40, 47, 52, 56, 59, 64}},
};

RackTunerBox::RackTunerBox(GxMainInterface& intf_)
    : tuner(),
      scale_lim(3.0),
      streaming(false),
      refpitch(),
      tuning_mode(0),
      current_mode(0),
      tuner_ui(false),
      intf(intf_) {
    gx_engine::get_group_table().insert("racktuner", "Rack Tuner");
    static bool s_h;
    intf.pmap.reg_non_midi_par("ui.racktuner", &tuner_ui, true);
    static const value_pair streaming_labels[] = {{"scale"}, {"stream"}, {0}};
    intf.pmap.reg_enum_par("racktuner.streaming", "Streaming Mode", streaming_labels, &streaming, 1);
    static const value_pair tuning_labels[] = {{"(Chromatic)"},{"Standard"}, {"Standard/Es"}, {"Open E"}, {0}};
    intf.pmap.reg_enum_par("racktuner.tuning", "Tuning", tuning_labels, &tuning_mode, 0);
    intf.pmap.reg_par("racktuner.scale_lim", "Limit", &scale_lim, 3.0, 1.0, 10.0, 1.0);
    intf.pmap.reg_non_midi_par("tuner.s_h", &s_h, true);
    intf.pmap.reg_par_non_preset(
	"ui.tuner_reference_pitch", "?Tuner Reference Pitch",
	&refpitch, 440, 427, 453, 0.1);
    //tuner.set_scale(1.5);
    tuner.signal_frequency_poll().connect(
	sigc::mem_fun(*this, &RackTunerBox::freq_poll));
    intf.mainmenu.fShowTuner.signal_activate().connect(
	sigc::compose(
	    sigc::mem_fun(*this, &RackTunerBox::on_off),
	    sigc::mem_fun(intf.mainmenu.fShowTuner, &MenuCheckItem::get_active)));
    tuner.show();
    static int pos = 1;
    intf.openTunerRackBox("RackTuner", &pos, "tuner.on_off", NULL, "ui.racktuner");
    {
        intf.openHorizontalhideBox("");
        intf.closeBox();
        intf.openVerticalBox("");
        {
            intf.openpaintampBox("");
            {
                intf.addwidget(GTK_WIDGET(tuner.gobj()));
            }
            intf.closeBox();
            intf.openHorizontalBox("");
            {
            intf.create_selector("racktuner.tuning");
            intf.create_selector("racktuner.streaming");
            intf.create_spin_value("ui.tuner_reference_pitch");
            intf.create_minislider("racktuner.scale_lim");
            }
            intf.closeBox();
        }
        intf.closeBox();
    }
    intf.closeMonoRackBox();
}

void RackTunerBox::freq_poll() {
    tuner.set_freq(intf.engine.tuner.get_freq());
    tuner.set_scale_lim(scale_lim/100);
    tuner.set_streaming(streaming);
    if (tuning_mode != current_mode) {
	current_mode = tuning_mode;
	tuner.clear_notes();
	if (current_mode > 0) {
	    tuner.set_display_flat(tuning_tab[current_mode-1].flat);
	    for (int i = 0; i < 6; ++i) {
		tuner.push_note(tuning_tab[current_mode-1].notes[i]);
	    }
	} else {
	    tuner.set_display_flat(false);
	}
    }
}

void RackTunerBox::on_off(bool v) {
    tuner.set_sensitive(v);
}


void StackBoxBuilder::make_rackbox_ampdetail() {
    openVerticalHideBox("mp");
    {
	openHorizontalBox("");
	{
	    openVerticalBox(" noise gate      ");
	    {
		openHorizontalBox("");
		{
		    create_switch_no_caption(sw_switchit, "noise_gate.on_off");
		    openpaintampBox("noise gate");
		    {
			create_wheel("noise_gate.threshold");
		    }
		    closeBox();
		}
		closeBox();
	    }
	    closeBox();
	    
	    openVerticalBox(_("noise shaper       "));
	    {
		openHorizontalBox("");
		{
		    create_switch_no_caption(sw_switchit, "shaper.on_off");
		    
		    openpaintampBox("shaper");
		    {
			create_wheel("shaper.sharper");
		    }
		    closeBox();
		}
		closeBox();
	    }
	    closeBox();
	    
	    openVerticalBox(_("mono level out       "));
	    {
		openHorizontalBox("");
		{
		    create_switch_no_caption(sw_switchit, "amp.on_off");
		    
		    openpaintampBox("level");
		    {
			create_spin_value("amp.out_amp");
			create_wheel("amp.out_amp");
		    }
		    closeBox();
		}
		closeBox();
	    }
	    closeBox();
	    
	    openVerticalBox(_("clip       "));
	    {
		openHorizontalBox("");
		{
		    create_switch_no_caption(sw_switchit, "amp.clip.on_off");
		    
		    openpaintampBox("level");
		    {
			create_wheel("amp.fuzz");
		    }
		    closeBox();
		}
		closeBox();
	    }
	    closeBox();
	}
	closeBox();
    }
    closeBox();
}
#endif

void StackBoxBuilder::make_rackbox_low_highpass() {
    // low high pass filter
    openMonoRackBox(_("l/h/filter"), engine.pluginlist.pos_var("low_highpass"), "low_highpass.on_off","low_highpass.pp","ui.low high pass");
    {
	openHorizontalhideBox("");
	closeBox();
	openHorizontalBox("");
	{
	    openHorizontalBox("");
	    {
		create_small_rackknob("low_high_pass.lhp.high_freq", _("high-pass "));
		create_small_rackknob("low_high_pass.lhp.low_freq", _(" low-pass "));
		create_switch_no_caption(sw_switchit, "low_high_pass.lhp.on_off");
	    }
	    closeBox();
	    openSpaceBox("");
	    closeBox();
	    openHorizontalBox("");
	    {
		create_small_rackknob("low_high_pass.lhc.low_freq", _("low-cut "));
		create_small_rackknob("low_high_pass.lhc.high_freq", _("high-cut "));
		create_switch_no_caption(sw_switchit, "low_high_pass.lhc.on_off");
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_eqs() {
    // EQ
    openMonoRackBox(_("EQ"), engine.pluginlist.pos_var("eqs"), "eqs.on_off", "eqs.pp","ui.Scaleable EQ");
    {
	openHorizontalhideBox("");
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalTableBox("");
	    {
		create_simple_spin_value("eqs.freq31_25");
		create_simple_spin_value("eqs.freq62_5");
		create_simple_spin_value("eqs.freq125");
		create_simple_spin_value("eqs.freq250");
		create_simple_spin_value("eqs.freq500");
		create_simple_spin_value("eqs.freq1k");
		create_simple_spin_value("eqs.freq2k");
		create_simple_spin_value("eqs.freq4k");
		create_simple_spin_value("eqs.freq8k");
		create_simple_spin_value("eqs.freq16k");
	    }
	    closeBox();
	    openHorizontalTableBox("");
	    {
		create_eq_rackslider_no_caption("eqs.fs31_25");
		create_eq_rackslider_no_caption("eqs.fs62_5");
		create_eq_rackslider_no_caption("eqs.fs125");
		create_eq_rackslider_no_caption("eqs.fs250");
		create_eq_rackslider_no_caption("eqs.fs500");
		create_eq_rackslider_no_caption("eqs.fs1k");
		create_eq_rackslider_no_caption("eqs.fs2k");
		create_eq_rackslider_no_caption("eqs.fs4k");
		create_eq_rackslider_no_caption("eqs.fs8k");
		create_eq_rackslider_no_caption("eqs.fs16k");
	    }
	    closeBox();
	    openHorizontalTableBox("");
	    {
		create_small_rackknob("eqs.Qs31_25", "Q");
		create_small_rackknob("eqs.Qs62_5", "Q");
		create_small_rackknob("eqs.Qs125", "Q");
		create_small_rackknob("eqs.Qs250", "Q");
		create_small_rackknob("eqs.Qs500", "Q");
		create_small_rackknob("eqs.Qs1k", "Q");
		create_small_rackknob("eqs.Qs2k", "Q");
		create_small_rackknob("eqs.Qs4k", "Q");
		create_small_rackknob("eqs.Qs8k", "Q");
		create_small_rackknob("eqs.Qs16k", "Q");
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_crybaby() {
    // ----- crybaby
    openMonoRackBox(_("crybaby"), engine.pluginlist.pos_var("crybaby"), "crybaby.on_off", "crybaby.pp", "ui.Crybaby");
    {
	openHorizontalhideBox("");
	create_master_slider("crybaby.level", _("  level  "));
	closeBox();
	openHorizontalBox("");
	{
	    openSpaceBox("");
	    closeBox();
	    create_selector("crybaby.autowah");
	    openSpaceBox("");
	    closeBox();
	    openSpaceBox("");
	    closeBox();
	    openHorizontalTableBox("");
	    {
		create_small_rackknobr("crybaby.wah", _("  wah   "));
		create_small_rackknob("crybaby.level", _("  level  "));
		create_small_rackknob("crybaby.wet_dry", _("  dry/wet  "));
	    }
	    closeBox();
	    openSpaceBox("");
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_gx_distortion() {
    // ----- distortion
    openMonoRackBox(_("distortion"), engine.pluginlist.pos_var("gx_distortion"), "gx_distortion.on_off", "gx_distortion.pp", "ui.Multi Band Distortion");
    {
	openHorizontalhideBox("");
	create_master_slider("gx_distortion.drive", _("drive"));
	closeBox();
	openHorizontalBox("");
	{
	    openVerticalBox("");
	    {
		openVerticalBox("");
		{
		    openFlipLabelBox(_("  drive "));
		    {
			openHorizontalBox("");
			{
			    create_small_rackknobr("gx_distortion.drive", _("  drive "));
			    create_small_rackknobr("gx_distortion.low_drive", _(" low "));
			    create_small_rackknobr("gx_distortion.middle_l_drive", _(" middle l. "));
			    create_small_rackknobr("gx_distortion.middle_h_drive", _(" middle h. "));
			    create_small_rackknobr("gx_distortion.high_drive", _(" high "));
			}
			closeBox();
		    }
		    closeBox();
		    openFlipLabelBox(_("  gain  "));
		    {
			openHorizontalBox("");
			{
			    create_small_rackknob("gx_distortion.gain", _("  gain  "));
			    create_small_rackknob("gx_distortion.low_gain", _(" low "));
			    create_small_rackknob("gx_distortion.middle_l_gain", _(" middle l. "));
			    create_small_rackknob("gx_distortion.middle_h_gain", _(" middle h. "));
			    create_small_rackknob("gx_distortion.high_gain", _(" high "));
			}
			closeBox();
		    }
		    closeBox();
		}
		closeBox();

		openHorizontalBox("");
		{
		    create_small_rackknob("gx_distortion.wet_dry", _("dry/wet"));
		    create_small_rackknob("gx_distortion.level", _("  level  "));
		    openVerticalBox(_("frequency split Hz"));
		    {
			openpaintampBox("");
			{
			    openHorizontalBox("");
			    {
				openSpaceBox("");
				closeBox();
				create_wheel("gx_distortion.split_low_freq", _("split low freq"));
				openSpaceBox("");
				closeBox();
				create_wheel("gx_distortion.split_middle_freq", _("split m. freq"));
				openSpaceBox("");
				closeBox();
				create_wheel("gx_distortion.split_high_freq", _("split high freq"));
				openSpaceBox("");
				closeBox();
			    }
			    closeBox();
			}
			closeBox();
		    }
		    closeBox();
		}
		closeBox();
	    }
	    closeBox();

	    openVerticalBox(_("resonator"));
	    {
		create_small_rackknob("gx_distortion.trigger", _("trigger "));
		create_small_rackknob("gx_distortion.vibrato", _(" vibrato "));
		create_switch_no_caption(sw_switchit, "gx_distortion.resonator.on_off");
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_IR() {
    // ----- IR
    openMonoRackBox(_("IR"), engine.pluginlist.pos_var("IR"), "IR.on_off", "IR.pp" ,"ui.ImpulseResponse");
    {
	openHorizontalhideBox("");
	create_master_slider("IR.peak", _(" peak "));
	closeBox();
	openVerticalBox1("");
	{
	    openHorizontalBox("");
	    {
		openSpaceBox("");
		closeBox();
		create_selector("IR.auto_freq");
		openSpaceBox("");
		closeBox();

		openHorizontalTableBox("");
		{
		    create_small_rackknob("IR.freq", _(" freq "));
		    create_small_rackknob("IR.peak", _(" peak "));
		    create_small_rackknob("IR.bandwidth", _(" bandwidth "));
		}
		closeBox();
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_compressor() {
    // ----- the compressor
    openMonoRackBox(_("Compr."), engine.pluginlist.pos_var("compressor"), "compressor.on_off", "compressor.pp", "ui.Compressor");
    {
	openHorizontalhideBox("");
	create_master_slider("compressor.ratio", _("ratio"));
	closeBox();
	openHorizontalTableBox("");
	{
	    create_small_rackknob("compressor.knee", _("knee"));
	    create_small_rackknobr("compressor.ratio", _("ratio"));
	    create_small_rackknob("compressor.threshold", _("threshold"));


	    create_small_rackknob("compressor.attack", _("attack"));
	    create_small_rackknob("compressor.release", _("release"));
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_overdrive() {
    // -----overdrive
    openMonoRackBox(_("overdrive"), engine.pluginlist.pos_var("overdrive"), "overdrive.on_off", "overdrive.pp", "ui.Overdrive");
    {
	openHorizontalhideBox("");
	create_master_slider("overdrive.drive", _("  drive "));
	closeBox();
	openHorizontalTableBox("");
	{
	    openSpaceBox("");
	    closeBox();
	    create_small_rackknobr("overdrive.drive", _("  drive "));
	    create_small_rackknob("overdrive.wet_dry", _("dry/wet"));
	    openSpaceBox("");
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_echo() {
    // ----- echo
    openMonoRackBox(_("echo"), engine.pluginlist.pos_var("echo"), "echo.on_off", "echo.pp", "ui.Echo");
    {
	openHorizontalhideBox("");
	create_master_slider("echo.percent", _("    %    "));
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalTableBox("");
	    {
		create_small_rackknobr("echo.time", _("  time  "));

		create_small_rackknob("echo.percent", _("    %    "));
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_delay() {
    // -----delay
    openMonoRackBox(_("delay"), engine.pluginlist.pos_var("delay"), "delay.on_off", "delay.pp", "ui.Delay");
    {
	openHorizontalhideBox("");
	create_master_slider("delay.delay", _(" delay "));
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalTableBox("");
	    {
		create_small_rackknobr("delay.delay", _(" delay "));

		create_small_rackknob("delay.gain", _("  gain "));
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_freeverb() {
    // ----- freeverb
    openMonoRackBox(_("freeverb"), engine.pluginlist.pos_var("freeverb"), "freeverb.on_off", "freeverb.pp", "ui.Freeverb");
    {
	openHorizontalhideBox("");
	create_master_slider("freeverb.RoomSize", _("RoomSize"));
	closeBox();
	openHorizontalBox("");
	{
            openFrameBox("");
            closeBox();
            openFrameBox("");
            closeBox();
            openHorizontalTableBox("");
            {
                create_small_rackknobr("freeverb.RoomSize", _("RoomSize"));
                create_small_rackknob("freeverb.damp", _("damp"));
                create_small_rackknob("freeverb.wet_dry", _("dry/wet"));
            }
            closeBox();
            openFrameBox("");
            closeBox();
            openFrameBox("");
            closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_oscilloscope() {
    // -----osc
    openMonoRackBox(_("osc"), engine.pluginlist.pos_var("oscilloscope"), "oscilloscope.on_off", "oscilloscope.pp", "ui.Oscilloscope");
    {
	openHorizontalhideBox("");
	closeBox();
	openVerticalBox("");
	{
	    openFrameBox("");
	    closeBox();
	    openHorizontalBox("");
	    {
		openFrameBox("");
		closeBox();
		addLiveWaveDisplay(" ");
		openFrameBox("");
		closeBox();
	    }
	    closeBox();
	    openFrameBox("");
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_biquad() {
    openMonoRackBox(_("biquad"), engine.pluginlist.pos_var("biquad"), "biquad.on_off", "biquad.pp", "ui.BiQuad Filter");
    {
	openHorizontalhideBox("");
	create_master_slider("biquad.Freq", _("Freq"));
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalBox("");
	    {
		create_small_rackknobr("biquad.Freq", _("Freq"));
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_tremolo() {
    openMonoRackBox(_("tremolo"), engine.pluginlist.pos_var("tremolo"), "tremolo.on_off", "tremolo.pp", "ui.Tremolo");
    {
	openHorizontalhideBox("");
	create_master_slider("tremolo.freq", _("Freq"));
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalBox("");
	    {
		openSpaceBox("");
		closeBox();
		create_selector("tremolo.SINE");
		openSpaceBox("");
		closeBox();
		openSpaceBox("");
		closeBox();
		openHorizontalTableBox("");
		{
		    create_small_rackknobr("tremolo.freq", _("Freq"));
		    openSpaceBox("");
		    closeBox();
		    create_small_rackknobr("tremolo.depth", _("Depth"));
		    openSpaceBox("");
		    closeBox();
		    create_small_rackknob("tremolo.wet_dry", _("dry/wet"));
		}
		closeBox();
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_phaser_mono() {
    openMonoRackBox(_("phaser"), engine.pluginlist.pos_var("phaser"), "phaser_mono.on_off", "phaser_mono.pp", "ui.Phaser Mono");
    {
	openHorizontalhideBox("");
	create_master_slider("phaser_mono.level", _("level"));
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalBox("");
	    {
		create_small_rackknobr("phaser_mono.level", _("level"));
		create_small_rackknob("phaser_mono.Speed", _("speed"));
		create_small_rackknob("phaser_mono.wet_dry", _("dry/wet"));
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_chorus_mono() {
    openMonoRackBox(_("chorus"), engine.pluginlist.pos_var("chorus"), "chorus_mono.on_off", "chorus_mono.pp", "ui.Chorus Mono");
    {
	openHorizontalhideBox("");
	create_master_slider("chorus_mono.level", _("level"));
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalBox("");
	    {
		create_small_rackknobr("chorus_mono.level", _("level"));
		create_small_rackknob("chorus_mono.freq", _("speed"));
		create_small_rackknob("chorus_mono.wet_dry", _("dry/wet"));
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_flanger_mono() {
    openMonoRackBox(_("flanger"), engine.pluginlist.pos_var("flanger_mono"), "flanger_mono.on_off", "flanger_mono.pp", "ui.Flanger Mono");
    {
	openHorizontalhideBox("");
	create_master_slider("flanger_mono.level", _("level"));
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalBox("");
	    {
		create_small_rackknobr("flanger_mono.level", _("level"));
		create_small_rackknob("flanger_mono.freq", _("speed"));
		create_small_rackknob("flanger_mono.wet_dry", _("dry/wet"));
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_feedback() {
    openMonoRackBox(_("feedback"), engine.pluginlist.pos_var("feedback"), "feedback.on_off", "feedback.pp", "ui.Feedback");
    {
	openHorizontalhideBox("");
	create_master_slider("feedback.feedback",  _("feedback"));
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalBox("");
	    {
		create_small_rackknobr("feedback.feedback",  _("feedback"));
		create_small_rackknob("feedback.wet_dry",  _("dry/wet"));
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_amp_tonestack() {
    openMonoRackBox(_("tonestack"), engine.pluginlist.pos_var("amp.tonestack"), "amp.tonestack.on_off", "amp.tonestack.pp", "ui.Tonestack");
    {
	openHorizontalhideBox("");
	create_selector("amp.tonestack.select");
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalBox("");
	    {
		create_selector("amp.tonestack.select");

		create_small_rackknob("amp.tonestack.Bass", _("bass"));

		create_small_rackknob("amp.tonestack.Middle", _("middle"));

		create_small_rackknob("amp.tonestack.Treble", _("treble"));
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_cab() {
    openMonoRackBox(_("cabinet"), engine.pluginlist.pos_var("cab"), "cab.on_off", "cab.pp", "ui.Cabinet");
    {
	openHorizontalhideBox("");
	create_selector("cab.select");
	closeBox();
	openVerticalBox("");
	{
	    openHorizontalBox("");
	    {
		create_selector("cab.select");
		create_small_rackknob("cab.bass", "bass");
		create_small_rackknob("cab.treble", "treble");
		create_small_rackknobr("cab.Level", "level");
	    }
	    closeBox();
	}
	closeBox();
    }
    closeMonoRackBox();
}

void StackBoxBuilder::make_rackbox_midi_out() {
    openVerticalMidiBox(_("  MIDI out  "));
    {
	openHorizontalhideBox("");
	closeBox();
	openHorizontalBox("");
	{
	    openVerticalBox(_("  MIDI out  "));
	    {
		create_switch_no_caption(sw_switchit, "midi_out.on_off");
		openFrameBox("");
		closeBox();
		openHorizontalBox("");
		{
		    openFrameBox("");
		    closeBox();
		    openPaintBox2("gree_box");
		    {
			create_switch_no_caption(sw_led, "midi_out.midistat");
		    }
		    closeBox();
		    openFrameBox("");
		    closeBox();
		}
		closeBox();
		openFrameBox("");
		closeBox();
	    }
	    closeBox();
	    // ----- create the midi settings dialog
	    openVerticalBox("");
	    {
		openTabBox("");
		{
		    openVerticalBox(_("channel1"));
		    {
			openpaintampBox("MIDI OUT");
			{
			    openVerticalBox("");
			    {
				openHorizontalBox("");
				{
				    create_small_rackknob("midi_out.channel_1.velocity", _("velocity"));
				    openVerticalBox("");
				    {
					openPaintBox2("dark_box");
					{
					    create_small_rackknob("midi_out.channel_1.volume", _("volume"));
					}
					closeBox();
					addCheckButton("midi_out.channel_1.autogain", _("autogain"));
				    }
				    closeBox();
				    openVerticalBox("");
				    {
					addNumEntry("midi_out.channel_1.channel", _("channel"));
					addNumEntry("midi_out.channel_1.program", _("program"));
				    }
				    closeBox();
				    create_small_rackknob("midi_out.channel_1.oktave", _("oktave"));
				    create_small_rackknob("midi_out.channel_1.sensity", _("sensity"));
				}
				closeBox();
				openHorizontalBox("");
				{
				    openHorizontalBox(" ");
				    closeBox();
				    openFrameBox("");
				    closeBox();
				    openVerticalBox("");
				    {
					openFrameBox("");
					closeBox();
					openPaintBox2("darker_box");
					{
					    create_switch_no_caption(sw_led, "midi_out.midistat1");
					}
					closeBox();
					openFrameBox("");
					closeBox();
				    }
				    closeBox();
				    openFrameBox("");
				    closeBox();
				    openHorizontalBox(" ");
				    {
					addMToggleButton("midi_out.channel_1.auto_pitch", _("auto_pitch"));
				    }
				    closeBox();
				}
				closeBox();
			    }
			    closeBox();
			}
			closeBox();
		    }
		    closeBox();

		    openVerticalBox(_("channel2"));
		    {
			openpaintampBox("MIDI OUT");
			{
			    openVerticalBox("");
			    {
				openHorizontalBox("");
				{
				    create_small_rackknob("midi_out.channel_2.velocity", _("velocity"));
				    openVerticalBox("");
				    {
					openPaintBox2("dark_box");
					{
					    create_small_rackknob("midi_out.channel_2.volume", _("volume"));
					}
					closeBox();
					addCheckButton("midi_out.channel_2.autogain", _("autogain"));
				    }
				    closeBox();
				    openVerticalBox("");
				    {
					addNumEntry("midi_out.channel_2.channel", _("channel"));
					addNumEntry("midi_out.channel_2.program", _("program"));
				    }
				    closeBox();
				    create_small_rackknob("midi_out.channel_2.oktave", _("oktave"));
				    create_small_rackknob("midi_out.channel_2.sensity", _("sensity"));
				}
				closeBox();
				openHorizontalBox("");
				{
				    create_switch_no_caption(sw_switchit, "midi_out.channel_2.on_off");
				    openFrameBox("");
				    closeBox();
				    openVerticalBox("");
				    {
					openFrameBox("");
					closeBox();
					openPaintBox2("darker_box");
					{
					    create_switch_no_caption(sw_led, "midi_out.midistat2");
					}
					closeBox();
					openFrameBox("");
					closeBox();
				    }
				    closeBox();
				    openFrameBox("");
				    closeBox();

				    openHorizontalBox(" ");
				    {
					addMToggleButton("midi_out.channel_2.auto_pitch", _("auto_pitch"));
				    }
				    closeBox();
				}
				closeBox();
			    }
			    closeBox();
			}
			closeBox();
		    }
		    closeBox();

		    openVerticalBox(_("channel3"));
		    {
			openpaintampBox("MIDI OUT");
			{
			    openVerticalBox("");
			    {
				openHorizontalBox("");
				{
				    create_small_rackknob("midi_out.channel_3.velocity", _("velocity"));
				    openVerticalBox("");
				    {
					openPaintBox2("dark_box");
					{
					    create_small_rackknob("midi_out.channel_3.volume", _("volume"));
					}
					closeBox();
					addCheckButton("midi_out.channel_3.autogain", _("autogain"));
				    }
				    closeBox();
				    openVerticalBox("");
				    {
					addNumEntry("midi_out.channel_3.channel", _("channel"));
					addNumEntry("midi_out.channel_3.program", _("program"));
				    }
				    closeBox();
				    create_small_rackknob("midi_out.channel_3.oktave", _("oktave"));
				    create_small_rackknob("midi_out.channel_3.sensity", _("sensity"));
				}
				closeBox();
				openHorizontalBox("");
				{
				    create_switch_no_caption(sw_switchit, "midi_out.channel_3.on_off");
				    openFrameBox("");
				    closeBox();
				    openVerticalBox("");
				    {
					openFrameBox("");
					closeBox();
					openPaintBox2("darker_box");
					{
					    create_switch_no_caption(sw_led, "midi_out.midistat3");
					}
					closeBox();
					openFrameBox("");
					closeBox();
				    }
				    closeBox();

				    openFrameBox("");
				    closeBox();
				    openHorizontalBox(" ");
				    {
					addMToggleButton("midi_out.channel_3.auto_pitch", _("auto_pitch"));
				    }
				    closeBox();
				}
				closeBox();
			    }
			    closeBox();
			}
			closeBox();
		    }
		    closeBox();

		    openVerticalBox(_("beat_detector"));
		    {
			openpaintampBox("MIDI OUT");
			{
			    openVerticalBox("");
			    {

				openHorizontalBox("");
				{
				    create_small_rackknob("beat_detector.stepper", _("stepper"));
				    create_small_rackknob("beat_detector.note_off", _("note_off"));
				    create_small_rackknob("beat_detector.atack_gain", _("atack_gain"));
				    create_small_rackknob("beat_detector.beat_gain", _("beat_gain"));
				}
				closeBox();
				openHorizontalBox("");
				{
				    openFrameBox("");
				    closeBox();
				    openPaintBox2("darker_box");
				    {
					create_switch_no_caption(sw_led, "midi_out.midistat1");
				    }
				    closeBox();
				    openFrameBox("");
				    closeBox();
				    openPaintBox2("darker_box");
				    {
					create_switch_no_caption(sw_led, "midi_out.midistat2");
				    }
				    closeBox();
				    openFrameBox("");
				    closeBox();
				    openPaintBox2("darker_box");
				    {
					create_switch_no_caption(sw_led, "midi_out.midistat3");
				    }
				    closeBox();
				    openFrameBox("");
				    closeBox();
				}
				closeBox();

				openVerticalBox(_("Midi gain"));
				{
				    create_wheel("beat_detector.midi_gain");
				}
				closeBox();
			    }
			    closeBox();
			}
			closeBox();
		    }
		    closeBox();
		}
		closeBox();
	    }
	    closeBox();
	}
	closeBox();
    }
    closeBox();
}

} // end namespace gx_gui