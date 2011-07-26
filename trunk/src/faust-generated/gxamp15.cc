namespace gxamp15 {
// generated from file '../src/faust/gxamp15.dsp'

double 	fConst0;
double 	fConst1;
double 	fConst2;
double 	fConst3;
double 	fConst4;
double 	fConst5;
double 	fVec0[2];
double 	fConst6;
double 	fRec2[2];
FAUSTFLOAT&	fslider0 = get_alias("amp2.stage2.gain1");
double 	fRec3[2];
FAUSTFLOAT&	fslider1 = get_alias("gxdistortion.wet_dry");
double 	fRec5[2];
FAUSTFLOAT&	fslider2 = get_alias("amp2.stage1.Pregain");
double 	fRec13[2];
double 	fConst7;
double 	fConst8;
double 	fConst9;
double 	fVec1[2];
double 	fConst10;
double 	fRec14[2];
double 	fRec12[2];
double 	fConst11;
double 	fConst12;
double 	fRec11[2];
double 	fConst13;
double 	fRec10[2];
double 	fConst14;
double 	fConst15;
double 	fConst16;
double 	fVec2[2];
double 	fConst17;
double 	fRec15[2];
double 	fRec9[2];
double 	fRec8[2];
double 	fConst18;
double 	fConst19;
double 	fConst20;
double 	fVec3[2];
double 	fConst21;
double 	fRec16[2];
double 	fRec7[2];
double 	fRec6[2];
FAUSTFLOAT&	fslider3 = get_alias("gxdistortion.drive");
double 	fRec17[2];
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
double 	fRec24[3];
double 	fVec4[2];
double 	fConst49;
double 	fRec23[2];
double 	fConst50;
double 	fConst51;
double 	fRec22[2];
double 	fRec21[3];
double 	fConst52;
double 	fRec20[3];
double 	fRec19[3];
double 	fConst53;
double 	fConst54;
double 	fConst55;
double 	fConst56;
double 	fConst57;
double 	fConst58;
double 	fConst59;
double 	fConst60;
double 	fConst61;
double 	fRec30[2];
double 	fRec29[3];
double 	fVec5[2];
double 	fConst62;
double 	fRec28[2];
double 	fRec27[3];
double 	fVec6[2];
double 	fConst63;
double 	fConst64;
double 	fRec26[2];
double 	fRec25[3];
double 	fConst65;
double 	fRec32[2];
double 	fRec31[3];
double 	fConst66;
double 	fRec35[2];
double 	fRec34[3];
double 	fConst67;
double 	fRec33[3];
double 	fVec7[2];
double 	fConst68;
double 	fRec18[2];
double 	fVec8[2];
double 	fRec4[2];
double 	fRec1[2];
double 	fRec0[2];
double 	fVec9[2];
double 	fRec38[2];
double 	fRec37[2];
double 	fRec36[2];
int	fSamplingFreq;

void init(int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1.0 / tan((97.38937226128358 / fSamplingFreq)));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((1 - fConst0) / fConst1));
	fConst3 = (1.0 / tan((20517.741620594938 / fSamplingFreq)));
	fConst4 = (1 + fConst3);
	fConst5 = (0 - ((1 - fConst3) / fConst4));
	for (int i=0; i<2; i++) fVec0[i] = 0;
	fConst6 = (0.0082 / fConst4);
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	fConst7 = (1.0 / tan((270.1769682087222 / fSamplingFreq)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	for (int i=0; i<2; i++) fVec1[i] = 0;
	fConst10 = (0.027 / fConst8);
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	fConst11 = (0 - fConst0);
	fConst12 = (0.025 / fConst1);
	for (int i=0; i<2; i++) fRec11[i] = 0;
	fConst13 = (1.0 / fConst4);
	for (int i=0; i<2; i++) fRec10[i] = 0;
	fConst14 = (1.0 / tan((414.6902302738527 / fSamplingFreq)));
	fConst15 = (1 + fConst14);
	fConst16 = (0 - ((1 - fConst14) / fConst15));
	for (int i=0; i<2; i++) fVec2[i] = 0;
	fConst17 = (0.015 / fConst15);
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	fConst18 = (1.0 / tan((609.4689747964198 / fSamplingFreq)));
	fConst19 = (1 + fConst18);
	fConst20 = (0 - ((1 - fConst18) / fConst19));
	for (int i=0; i<2; i++) fVec3[i] = 0;
	fConst21 = (0.0082 / fConst19);
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	fConst22 = tan((942.4777960769379 / fSamplingFreq));
	fConst23 = (1.0 / faustpower<2>(fConst22));
	fConst24 = (2 * (1 - fConst23));
	fConst25 = (1.0 / fConst22);
	fConst26 = (1 + ((fConst25 - 1.0) / fConst22));
	fConst27 = (1.0 / (1 + ((1.0 + fConst25) / fConst22)));
	fConst28 = tan((3769.9111843077517 / fSamplingFreq));
	fConst29 = (1.0 / faustpower<2>(fConst28));
	fConst30 = (2 * (1 - fConst29));
	fConst31 = (1.0 / fConst28);
	fConst32 = (1 + ((fConst31 - 1.0) / fConst28));
	fConst33 = (1.0 / (1 + ((1.0 + fConst31) / fConst28)));
	fConst34 = tan((10053.096491487338 / fSamplingFreq));
	fConst35 = (1.0 / faustpower<2>(fConst34));
	fConst36 = (2 * (1 - fConst35));
	fConst37 = (1.0 / fConst34);
	fConst38 = (1 + ((fConst37 - 1.0000000000000004) / fConst34));
	fConst39 = (1 + ((1.0000000000000004 + fConst37) / fConst34));
	fConst40 = (1.0 / fConst39);
	fConst41 = (1 + fConst37);
	fConst42 = (0 - ((1 - fConst37) / fConst41));
	fConst43 = tan((47123.8898038469 / fSamplingFreq));
	fConst44 = (2 * (1 - (1.0 / faustpower<2>(fConst43))));
	fConst45 = (1.0 / fConst43);
	fConst46 = (1 + ((fConst45 - 1.414213562373095) / fConst43));
	fConst47 = (1 + ((1.414213562373095 + fConst45) / fConst43));
	fConst48 = (1.0 / fConst47);
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	fConst49 = (1.0 / (fConst1 * fConst47));
	for (int i=0; i<2; i++) fRec23[i] = 0;
	fConst50 = (0 - fConst37);
	fConst51 = (1.0 / fConst41);
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	fConst52 = (2 * (0 - fConst35));
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	fConst53 = (1 + ((fConst25 - 1.0000000000000004) / fConst22));
	fConst54 = (1.0 / (1 + ((fConst25 + 1.0000000000000004) / fConst22)));
	fConst55 = (1 + fConst25);
	fConst56 = (0 - ((1 - fConst25) / fConst55));
	fConst57 = (1 + ((fConst31 - 1.0000000000000004) / fConst28));
	fConst58 = (1 + ((fConst31 + 1.0000000000000004) / fConst28));
	fConst59 = (1.0 / fConst58);
	fConst60 = (1 + fConst31);
	fConst61 = (0 - ((1 - fConst31) / fConst60));
	for (int i=0; i<2; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	fConst62 = (1.0 / (fConst60 * fConst39));
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fVec6[i] = 0;
	fConst63 = (0 - fConst25);
	fConst64 = (1.0 / (fConst55 * fConst58));
	for (int i=0; i<2; i++) fRec26[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	fConst65 = (2 * (0 - fConst23));
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	fConst66 = (0 - fConst31);
	for (int i=0; i<2; i++) fRec35[i] = 0;
	for (int i=0; i<3; i++) fRec34[i] = 0;
	fConst67 = (2 * (0 - fConst29));
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fVec7[i] = 0;
	fConst68 = (1.5848931924611136 / fConst4);
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fVec8[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fVec9[i] = 0;
	for (int i=0; i<2; i++) fRec38[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<2; i++) fRec36[i] = 0;
}

void compute(int count, float *input0, float *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = fslider1;
	double 	fSlow2 = (0.0010000000000000009 * (1 - (0.01 * fSlow1)));
	double 	fSlow3 = (0.0010000000000000009 * pow(10,(0.05 * fslider2)));
	double 	fSlow4 = fslider3;
	double 	fSlow5 = (1.25 * fSlow4);
	double 	fSlow6 = (1.000000000000001e-05 * fSlow1);
	double 	fSlow7 = (2 * (fSlow4 - 0.5));
	double 	fSlow8 = (1 - max(0, fSlow7));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow4));
	double 	fSlow10 = (fConst54 * pow(1e+01,(2 * fSlow4)));
	double 	fSlow11 = (fConst54 * pow(1e+01,(0.9 * fSlow4)));
	double 	fSlow12 = pow(1e+01,(1.2 * fSlow4));
	double 	fSlow13 = (1 - max(0, (0 - fSlow7)));
	for (int i=0; i<count; i++) {
		double fTemp0 = (fRec1[1] - 2.5e+02);
		fVec0[0] = fTemp0;
		fRec2[0] = ((fConst6 * (fVec0[0] + fVec0[1])) + (fConst5 * fRec2[1]));
		fRec3[0] = (fSlow0 + (0.999 * fRec3[1]));
		fRec5[0] = (fSlow2 + (0.999 * fRec5[1]));
		fRec13[0] = (fSlow3 + (0.999 * fRec13[1]));
		double fTemp1 = (fRec12[1] - 2.5e+02);
		fVec1[0] = fTemp1;
		fRec14[0] = ((fConst10 * (fVec1[0] + fVec1[1])) + (fConst9 * fRec14[1]));
		fRec12[0] = Ftube6(0, (fRec14[0] + ((double)input0[i] * fRec13[0])));
		fRec11[0] = ((fConst12 * ((fConst11 * fRec12[1]) + (fConst0 * fRec12[0]))) + (fConst2 * fRec11[1]));
		fRec10[0] = ((fConst13 * (fRec11[0] + fRec11[1])) + (fConst5 * fRec10[1]));
		double fTemp2 = (fRec9[1] - 2.5e+02);
		fVec2[0] = fTemp2;
		fRec15[0] = ((fConst17 * (fVec2[0] + fVec2[1])) + (fConst16 * fRec15[1]));
		fRec9[0] = Ftube6(1, (fRec15[0] + fRec10[0]));
		fRec8[0] = ((fConst12 * ((fConst11 * fRec9[1]) + (fConst0 * fRec9[0]))) + (fConst2 * fRec8[1]));
		double fTemp3 = (fRec7[1] - 2.5e+02);
		fVec3[0] = fTemp3;
		fRec16[0] = ((fConst21 * (fVec3[0] + fVec3[1])) + (fConst20 * fRec16[1]));
		fRec7[0] = Ftube6(1, (fRec16[0] + fRec8[0]));
		fRec6[0] = ((fConst12 * ((fConst11 * fRec7[1]) + (fConst0 * fRec7[0]))) + (fConst2 * fRec6[1]));
		fRec17[0] = (fSlow6 + (0.999 * fRec17[1]));
		double fTemp4 = (fConst24 * fRec19[1]);
		double fTemp5 = (fConst30 * fRec20[1]);
		fRec24[0] = ((fRec6[0] * fRec17[0]) - (fConst48 * ((fConst46 * fRec24[2]) + (fConst44 * fRec24[1]))));
		double fTemp6 = (fRec24[2] + (fRec24[0] + (2 * fRec24[1])));
		fVec4[0] = fTemp6;
		fRec23[0] = ((fConst49 * ((fConst11 * fVec4[1]) + (fConst0 * fVec4[0]))) + (fConst2 * fRec23[1]));
		fRec22[0] = ((fConst51 * ((fConst50 * fRec23[1]) + (fConst37 * fRec23[0]))) + (fConst42 * fRec22[1]));
		fRec21[0] = (fRec22[0] - (fConst40 * ((fConst38 * fRec21[2]) + (fConst36 * fRec21[1]))));
		fRec20[0] = ((fConst40 * (((fConst35 * fRec21[0]) + (fConst52 * fRec21[1])) + (fConst35 * fRec21[2]))) - (fConst33 * ((fConst32 * fRec20[2]) + fTemp5)));
		fRec19[0] = ((fRec20[2] + (fConst33 * (fTemp5 + (fConst32 * fRec20[0])))) - (fConst27 * ((fConst26 * fRec19[2]) + fTemp4)));
		double fTemp7 = max(-1, min(1, (fSlow9 * (fRec19[2] + (fConst27 * (fTemp4 + (fConst26 * fRec19[0])))))));
		fRec30[0] = ((fConst51 * (fRec23[0] + fRec23[1])) + (fConst42 * fRec30[1]));
		fRec29[0] = (fRec30[0] - (fConst40 * ((fConst38 * fRec29[2]) + (fConst36 * fRec29[1]))));
		double fTemp8 = (fRec29[2] + (fRec29[0] + (2 * fRec29[1])));
		fVec5[0] = fTemp8;
		fRec28[0] = ((fConst62 * (fVec5[0] + fVec5[1])) + (fConst61 * fRec28[1]));
		fRec27[0] = (fRec28[0] - (fConst59 * ((fConst57 * fRec27[2]) + (fConst30 * fRec27[1]))));
		double fTemp9 = (fRec27[2] + (fRec27[0] + (2 * fRec27[1])));
		fVec6[0] = fTemp9;
		fRec26[0] = ((fConst64 * ((fConst63 * fVec6[1]) + (fConst25 * fVec6[0]))) + (fConst56 * fRec26[1]));
		fRec25[0] = (fRec26[0] - (fConst54 * ((fConst53 * fRec25[2]) + (fConst24 * fRec25[1]))));
		double fTemp10 = max(-1, min(1, (fSlow10 * (((fConst23 * fRec25[0]) + (fConst65 * fRec25[1])) + (fConst23 * fRec25[2])))));
		fRec32[0] = ((fConst64 * (fVec6[0] + fVec6[1])) + (fConst56 * fRec32[1]));
		fRec31[0] = (fRec32[0] - (fConst54 * ((fConst53 * fRec31[2]) + (fConst24 * fRec31[1]))));
		double fTemp11 = max(-1, min(1, (fSlow11 * (fRec31[2] + (fRec31[0] + (2 * fRec31[1]))))));
		double fTemp12 = (fConst24 * fRec33[1]);
		fRec35[0] = ((fConst62 * ((fConst66 * fVec5[1]) + (fConst31 * fVec5[0]))) + (fConst61 * fRec35[1]));
		fRec34[0] = (fRec35[0] - (fConst59 * ((fConst57 * fRec34[2]) + (fConst30 * fRec34[1]))));
		fRec33[0] = ((fConst59 * (((fConst29 * fRec34[0]) + (fConst67 * fRec34[1])) + (fConst29 * fRec34[2]))) - (fConst27 * ((fConst26 * fRec33[2]) + fTemp12)));
		double fTemp13 = max(-1, min(1, (fSlow12 * (fRec33[2] + (fConst27 * (fTemp12 + (fConst26 * fRec33[0])))))));
		double fTemp14 = (((fTemp13 * (1 - (0.3333333333333333 * faustpower<2>(fTemp13)))) + ((fTemp11 * (1 - (0.3333333333333333 * faustpower<2>(fTemp11)))) + (0.841395141645195 * (fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10))))))) + (0.7943282347242815 * (fTemp7 * (1 - (0.3333333333333333 * faustpower<2>(fTemp7))))));
		fVec7[0] = fTemp14;
		fRec18[0] = ((fConst68 * (fVec7[0] + fVec7[1])) + (fConst5 * fRec18[1]));
		double fTemp15 = ((fSlow13 * fRec18[0]) + (fRec6[0] * ((fSlow8 * fRec17[0]) + (fRec5[0] * (1 + (fSlow5 * ((4 - (4 * fabs((fRec6[0] * fRec5[0])))) - 1)))))));
		fVec8[0] = fTemp15;
		fRec4[0] = ((fConst13 * (fVec8[0] + fVec8[1])) + (fConst5 * fRec4[1]));
		double fTemp16 = (fRec4[0] * fRec3[0]);
		fRec1[0] = Ftube2(0, (fTemp16 + fRec2[0]));
		fRec0[0] = ((fConst12 * ((fConst11 * fRec1[1]) + (fConst0 * fRec1[0]))) + (fConst2 * fRec0[1]));
		double fTemp17 = (fRec37[1] - 2.5e+02);
		fVec9[0] = fTemp17;
		fRec38[0] = ((fConst6 * (fVec9[0] + fVec9[1])) + (fConst5 * fRec38[1]));
		fRec37[0] = Ftube2(1, (fRec38[0] + fTemp16));
		fRec36[0] = ((fConst12 * ((fConst11 * fRec37[1]) + (fConst0 * fRec37[0]))) + (fConst2 * fRec36[1]));
		output0[i] = (FAUSTFLOAT)(fRec36[0] + fRec0[0]);
		// post processing
		fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec38[1] = fRec38[0];
		fVec9[1] = fVec9[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec4[1] = fRec4[0];
		fVec8[1] = fVec8[0];
		fRec18[1] = fRec18[0];
		fVec7[1] = fVec7[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[2] = fRec34[1]; fRec34[1] = fRec34[0];
		fRec35[1] = fRec35[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec26[1] = fRec26[0];
		fVec6[1] = fVec6[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fVec5[1] = fVec5[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[1] = fRec30[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fVec4[1] = fVec4[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec17[1] = fRec17[0];
		fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec16[1] = fRec16[0];
		fVec3[1] = fVec3[0];
		fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fRec15[1] = fRec15[0];
		fVec2[1] = fVec2[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fVec1[1] = fVec1[0];
		fRec13[1] = fRec13[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fVec0[1] = fVec0[0];
	}
}

static struct RegisterParams { RegisterParams(); } RegisterParams;
RegisterParams::RegisterParams()
{
	registerInit("amp2", init);
}

} // end namespace gxamp15
