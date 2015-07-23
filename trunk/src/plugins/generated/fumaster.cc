// generated from file '../src/plugins/fumaster.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace fumaster {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider1;
	double 	fRec6[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fslider2;
	double 	fRec7[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fRec8[7];
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fRec9[2];
	double 	fRec5[3];
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fRec4[2];
	double 	fRec10[2];
	double 	fRec3[3];
	double 	fRec2[2];
	double 	fRec11[2];
	double 	fRec1[3];
	double 	fRec0[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "fumaster";
	name = N_("Fuzz Master");
	groups = 0;
	description = N_("Vintage Fuzz Master"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Fuzz Master");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<7; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (1.00949675143598e-28 * fConst1);
	fConst3 = (3.94912717206244e-15 + (fConst1 * (7.52873102578757e-17 + (fConst1 * (3.72110810064138e-19 + (fConst1 * (5.95381363906935e-22 + (fConst1 * (3.20513868924941e-25 + fConst2)))))))));
	fConst4 = (1.00799506674223e-28 * fConst1);
	fConst5 = (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (2.59175366383786e-25 + fConst4))) - 4.35259230096405e-22)) - 1.02583553103419e-19)) - 2.16974948431515e-18));
	fConst6 = (1.5016846937505e-31 * fConst1);
	fConst7 = (1.08487474215758e-15 + (fConst1 * (5.11414335446406e-17 + (fConst1 * (2.16655787499057e-19 + (fConst1 * (1.27917670111645e-22 + (fConst1 * (4.96235474586462e-26 - fConst6)))))))));
	fConst8 = (1.41775270516311e-29 * fConst1);
	fConst9 = ((fConst1 * (4.70999825737972e-24 + fConst8)) - 2.59478774349197e-21);
	fConst10 = (1.41775270516311e-27 * fConst1);
	fConst11 = (0.1 * ((fConst1 * (4.70999825737972e-22 + fConst10)) - 2.59478774349197e-19));
	fConst12 = (0 - (4.71779589725812e-22 + fConst10));
	fConst13 = (0 - (4.71779589725812e-24 + fConst8));
	fConst14 = ((fConst1 * (7.52873102578757e-17 + (fConst1 * ((fConst1 * (5.95381363906935e-22 + (fConst1 * (fConst2 - 3.20513868924941e-25)))) - 3.72110810064138e-19)))) - 3.94912717206244e-15);
	fConst15 = (fConst1 * ((fConst1 * (1.02583553103419e-19 + (fConst1 * ((fConst1 * (2.59175366383786e-25 - fConst4)) - 4.35259230096405e-22)))) - 2.16974948431515e-18));
	fConst16 = ((fConst1 * (5.11414335446406e-17 + (fConst1 * ((fConst1 * (1.27917670111645e-22 + (fConst1 * (0 - (4.96235474586462e-26 + fConst6))))) - 2.16655787499057e-19)))) - 1.08487474215758e-15);
	fConst17 = (6.0569805086159e-28 * fConst1);
	fConst18 = faustpower<2>(fConst1);
	fConst19 = ((fConst1 * (1.50574620515751e-16 + (fConst18 * ((fConst1 * (1.28205547569977e-24 - fConst17)) - 1.19076272781387e-21)))) - 1.57965086882498e-14);
	fConst20 = (6.0479704004534e-28 * fConst1);
	fConst21 = (fConst1 * ((fConst18 * (8.70518460192809e-22 + (fConst1 * (fConst20 - 1.03670146553514e-24)))) - 4.3394989686303e-18));
	fConst22 = (9.01010816250298e-31 * fConst1);
	fConst23 = ((fConst1 * (1.02282867089281e-16 + (fConst18 * ((fConst1 * (1.98494189834585e-25 + fConst22)) - 2.5583534022329e-22)))) - 4.3394989686303e-15);
	fConst24 = (1.51424512715397e-27 * fConst1);
	fConst25 = ((fConst1 * ((fConst1 * (1.11633243019242e-18 + (fConst1 * ((fConst1 * (fConst24 - 1.60256934462471e-24)) - 5.95381363906935e-22)))) - 7.52873102578757e-17)) - 1.97456358603122e-14);
	fConst26 = (1.51199260011335e-27 * fConst1);
	fConst27 = (fConst1 * (2.16974948431515e-18 + (fConst1 * ((fConst1 * (4.35259230096405e-22 + (fConst1 * (1.29587683191893e-24 - fConst26)))) - 3.07750659310257e-19))));
	fConst28 = (2.25252704062574e-30 * fConst1);
	fConst29 = ((fConst1 * ((fConst1 * (6.4996736249717e-19 + (fConst1 * ((fConst1 * (0 - (2.48117737293231e-25 + fConst28))) - 1.27917670111645e-22)))) - 5.11414335446406e-17)) - 5.42437371078788e-15);
	fConst30 = ((fConst18 * (2.38152545562774e-21 - (2.01899350287197e-27 * fConst18))) - 3.01149241031503e-16);
	fConst31 = (8.6789979372606e-18 + (fConst18 * ((2.01599013348447e-27 * fConst18) - 1.74103692038562e-21)));
	fConst32 = ((fConst18 * (5.11670680446579e-22 + (3.00336938750099e-30 * fConst18))) - 2.04565734178562e-16);
	fConst33 = (1.97456358603122e-14 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.60256934462471e-24 + fConst24)) - 5.95381363906935e-22)) - 1.11633243019242e-18)) - 7.52873102578757e-17)));
	fConst34 = (fConst1 * (2.16974948431515e-18 + (fConst1 * (3.07750659310257e-19 + (fConst1 * (4.35259230096405e-22 + (fConst1 * (0 - (1.29587683191893e-24 + fConst26)))))))));
	fConst35 = (5.42437371078788e-15 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (2.48117737293231e-25 - fConst28)) - 1.27917670111645e-22)) - 6.4996736249717e-19)) - 5.11414335446406e-17)));
	fConst36 = (1.57965086882498e-14 + (fConst1 * (1.50574620515751e-16 + (fConst18 * ((fConst1 * (0 - (1.28205547569977e-24 + fConst17))) - 1.19076272781387e-21)))));
	fConst37 = (fConst1 * ((fConst18 * (8.70518460192809e-22 + (fConst1 * (1.03670146553514e-24 + fConst20)))) - 4.3394989686303e-18));
	fConst38 = (4.3394989686303e-15 + (fConst1 * (1.02282867089281e-16 + (fConst18 * ((fConst1 * (fConst22 - 1.98494189834585e-25)) - 2.5583534022329e-22)))));
	fConst39 = (8.50651623097868e-29 * fConst1);
	fConst40 = (5.18957548698393e-21 + (fConst1 * (0 - (1.88399930295189e-23 + fConst39))));
	fConst41 = (8.50651623097868e-27 * fConst1);
	fConst42 = (0.1 * (5.18957548698393e-19 + (fConst1 * (0 - (1.88399930295189e-21 + fConst41)))));
	fConst43 = (1.88711835890325e-21 + fConst41);
	fConst44 = (1.88711835890325e-23 + fConst39);
	fConst45 = (2.12662905774467e-26 * fConst1);
	fConst46 = (0.1 * (2.59478774349197e-19 + (fConst1 * (2.35499912868986e-21 + fConst45))));
	fConst47 = (0 - (2.35889794862906e-21 + fConst45));
	fConst48 = (2.12662905774467e-28 * fConst1);
	fConst49 = (0 - (2.35889794862906e-23 + fConst48));
	fConst50 = (2.59478774349197e-21 + (fConst1 * (2.35499912868986e-23 + fConst48)));
	fConst51 = (0 - (1.03791509739679e-20 + (2.83550541032623e-28 * fConst18)));
	fConst52 = (0.1 * (0 - (1.03791509739679e-18 + (2.83550541032623e-26 * fConst18))));
	fConst53 = (2.59478774349197e-21 + (fConst1 * (fConst48 - 2.35499912868986e-23)));
	fConst54 = (0.1 * (2.59478774349197e-19 + (fConst1 * (fConst45 - 2.35499912868986e-21))));
	fConst55 = (2.35889794862906e-21 - fConst45);
	fConst56 = (2.35889794862906e-23 - fConst48);
	fConst57 = (5.18957548698393e-21 + (fConst1 * (1.88399930295189e-23 - fConst39)));
	fConst58 = (0.1 * (5.18957548698393e-19 + (fConst1 * (1.88399930295189e-21 - fConst41))));
	fConst59 = (fConst41 - 1.88711835890325e-21);
	fConst60 = (fConst39 - 1.88711835890325e-23);
	fConst61 = (0.1 * ((fConst1 * (fConst10 - 4.70999825737972e-22)) - 2.59478774349197e-19));
	fConst62 = (4.71779589725812e-22 - fConst10);
	fConst63 = (4.71779589725812e-24 - fConst8);
	fConst64 = ((fConst1 * (fConst8 - 4.70999825737972e-24)) - 2.59478774349197e-21);
	fConst65 = faustpower<4>(fConst1);
	fConst66 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst67 = (1 + fConst66);
	fConst68 = (0.027 / fConst67);
	fConst69 = (0 - ((1 - fConst66) / fConst67));
	fConst70 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst71 = (0 - fConst70);
	fConst72 = (1 + fConst70);
	fConst73 = (0.025 / fConst72);
	fConst74 = (0 - ((1 - fConst70) / fConst72));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.01 * double(fslider0));
	double 	fSlow1 = (1 - fSlow0);
	double 	fSlow2 = (0.007000000000000006 * double(fslider1));
	double 	fSlow3 = (0.007000000000000006 * double(fslider2));
	for (int i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fRec6[0] = ((0.993 * fRec6[1]) + fSlow2);
		double fTemp1 = (5.42437371078787e-14 + (fConst1 * ((fRec6[0] * (fConst7 + (fConst5 * fRec6[0]))) + fConst3)));
		fRec7[0] = ((0.993 * fRec7[1]) + fSlow3);
		fRec8[0] = ((fSlow0 * fTemp0) - (((((((fRec8[1] * (3.25462422647273e-13 + (fConst1 * ((fRec6[0] * (fConst38 + (fConst37 * fRec6[0]))) + fConst36)))) + (fRec8[2] * (8.13656056618181e-13 + (fConst1 * ((fRec6[0] * (fConst35 + (fConst34 * fRec6[0]))) + fConst33))))) + (fRec8[3] * (1.08487474215758e-12 + (fConst18 * ((fRec6[0] * (fConst32 + (fConst31 * fRec6[0]))) + fConst30))))) + (fRec8[4] * (8.13656056618181e-13 + (fConst1 * ((fRec6[0] * (fConst29 + (fConst27 * fRec6[0]))) + fConst25))))) + (fRec8[5] * (3.25462422647273e-13 + (fConst1 * ((fRec6[0] * (fConst23 + (fConst21 * fRec6[0]))) + fConst19))))) + (fRec8[6] * (5.42437371078787e-14 + (fConst1 * ((fRec6[0] * (fConst16 + (fConst15 * fRec6[0]))) + fConst14))))) / fTemp1));
		fRec9[0] = ((fConst69 * fRec9[1]) + (fConst68 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec9[0] + (fConst65 * ((((((((fRec8[0] * (fConst64 + ((fConst1 * (fRec6[0] * (fConst63 + (fConst62 * fRec7[0])))) + (fConst61 * fRec7[0])))) + (fRec8[1] * (((fConst1 * (fRec6[0] * (fConst60 + (fConst59 * fRec7[0])))) + (fConst58 * fRec7[0])) + fConst57))) + (fRec8[2] * (((fConst1 * (fRec6[0] * (fConst56 + (fConst55 * fRec7[0])))) + (fConst54 * fRec7[0])) + fConst53))) + (fRec8[3] * (((fConst18 * (fRec6[0] * (2.83550541032623e-28 + (2.83550541032623e-26 * fRec7[0])))) + (fConst52 * fRec7[0])) + fConst51))) + (fRec8[4] * (fConst50 + ((fConst1 * (fRec6[0] * (fConst49 + (fConst47 * fRec7[0])))) + (fConst46 * fRec7[0]))))) + (fRec8[5] * (((fConst1 * (fRec6[0] * (fConst44 + (fConst43 * fRec7[0])))) + (fConst42 * fRec7[0])) + fConst40))) + (fRec8[6] * (((fConst1 * (fRec6[0] * (fConst13 + (fConst12 * fRec7[0])))) + (fConst11 * fRec7[0])) + fConst9))) / fTemp1))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst74 * fRec4[1]) + (fConst73 * ((fConst70 * fRec5[0]) + (fConst71 * fRec5[1]))));
		fRec10[0] = ((fConst69 * fRec10[1]) + (fConst68 * (fRec3[1] + fRec3[2])));
		fRec3[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec10[0] + fRec4[0]) - 3.571981)) - 117.70440740740739);
		fRec2[0] = ((fConst74 * fRec2[1]) + (fConst73 * ((fConst70 * fRec3[0]) + (fConst71 * fRec3[1]))));
		fRec11[0] = ((fConst69 * fRec11[1]) + (fConst68 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec11[0] + fRec2[0]) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst74 * fRec0[1]) + (fConst73 * ((fConst70 * fRec1[0]) + (fConst71 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)(fRec0[0] + (fSlow1 * fTemp0));
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec11[1] = fRec11[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec10[1] = fRec10[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec9[1] = fRec9[0];
		for (int i=6; i>0; i--) fRec8[i] = fRec8[i-1];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("fumaster.Level",N_("Level"),"S","",&fslider2, 0.1, 0.0, 1.0, 0.01);
	reg.registerVar("fumaster.Tone",N_("Tone"),"S","",&fslider1, 0.5, 0.0, 0.99, 0.01);
	reg.registerVar("fumaster.wet_dry",N_("wet/dry"),"S",N_("percentage of processed signal in output signal"),&fslider0, 1e+02, 0.0, 1e+02, 1.0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("fumaster" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Tone"), "Tone");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Tone"), "Tone");

    b.create_small_rackknobr(PARAM("Level"), "Level");
    b.create_small_rackknobr(PARAM("wet_dry"), "dry/wet");
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace fumaster
} // end namespace pluginlib