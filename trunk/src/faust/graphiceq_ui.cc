// ----- graphiceq
b.openHorizontalhideBox("");
b.closeBox();
b.openHorizontalBox("");
{
    b.openFrameBox("");
    b.closeBox();
    b.create_simple_c_meter(PARAM("v1"), PARAM("g1"),"<31");
    b.create_simple_c_meter(PARAM("v2"), PARAM("g2"),"62");
    b.create_simple_c_meter(PARAM("v3"), PARAM("g3"),"125");
    b.create_simple_c_meter(PARAM("v4"), PARAM("g4"),"250");
    b.create_simple_c_meter(PARAM("v5"), PARAM("g5"),"500");
    b.create_simple_c_meter(PARAM("v6"), PARAM("g6"),"1k");
    b.create_simple_c_meter(PARAM("v7"), PARAM("g7"),"2k");
    b.create_simple_c_meter(PARAM("v8"), PARAM("g8"),"4k");
    b.create_simple_c_meter(PARAM("v9"), PARAM("g9"),"8k");
    b.create_simple_c_meter(PARAM("v10"), PARAM("g10"),"16k");
    b.create_simple_c_meter(PARAM("v11"), PARAM("g11"),"<");
    b.openFrameBox("");
    b.closeBox();
}
b.closeBox();
