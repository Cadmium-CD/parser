
//
// Created by keren on 9/23/17.
//

#include "LefReader.h"

PROJECT_NAMESPACE_BEGIN


    void LefReader::lef_version_cbk(const std::string &v) {

    }

    void LefReader::lef_version_cbk(double v) {

    }

    void LefReader::lef_dividerchar_cbk(const std::string &v) {

    }

    void LefReader::lef_casesensitive_cbk(int v) {

    }

    void LefReader::lef_nowireextension_cbk(const std::string &v) {

    }

    void LefReader::lef_manufacturing_cbk(double v) {

    }

    void LefReader::lef_useminspacing_cbk(lefiUseMinSpacing const &v) {

    }

    void LefReader::lef_clearancemeasure_cbk(const std::string &v) {

    }

    void LefReader::lef_units_cbk(lefiUnits const &v) {

    }

    void LefReader::lef_busbitchars_cbk(const std::string &v) {

    }

    void LefReader::lef_layer_cbk(lefiLayer const &v) {

    }

    void LefReader::lef_maxstackvia_cbk(lefiMaxStackVia const &v) {

    }

    void LefReader::lef_via_cbk(lefiVia const &v) {

    }

    void LefReader::lef_viarule_cbk(lefiViaRule const &v) {

    }

    void LefReader::lef_spacing_cbk(lefiSpacing const &v) {

    }

    void LefReader::lef_irdrop_cbk(lefiIRDrop const &v) {

    }

    void LefReader::lef_minfeature_cbk(lefiMinFeature const &v) {

    }

    void LefReader::lef_dielectric_cbk(double v) {

    }

    void LefReader::lef_nondefault_cbk(lefiNonDefault const &v) {

    }

    void LefReader::lef_site_cbk(lefiSite const &v) {
        if (v.hasSize()) {
            _db.setLefSiteSizeX(v.sizeX());
            _db.setLefSiteSizeY(v.sizeY());
        } else {
            assert(false);
        }
    }

    void LefReader::lef_macrobegin_cbk(std::string const &v) {
        /// For pin parsering
        //lef_macrobegin_cbk(v);
        //std::cout<<v<<std::endl;
        currentMacroName = v;
        StdCell temp = StdCell();
        temp.setMacroName(currentMacroName);
        _db.addStdCellLib(currentMacroName, temp);
    }

    void LefReader::lef_macro_cbk(lefiMacro const &v) {
        //LefDataBase::lef_macro_cbk(v);
        assert(v.hasXSymmetry());
        assert(v.hasYSymmetry());
        assert(v.originX() == 0 && v.originY() == 0);
        _db.getStdCellLib()[currentMacroName].setSizeX(v.sizeX());
        _db.getStdCellLib()[currentMacroName].setSizeY(v.sizeY());

        /// Process the string for extracting the edgetype information
        bool left = true;
        bool right = true;
        bool hasedge = false;
        IndexType property_num = static_cast<IndexType>(v.numProperties());
        std::string property_value;
        for (IndexType i = 0; i < property_num; ++i) {
            //cout<<"Index: "<<i<< " Property name:"<<v.propName(i)<<" Property value: "<< v.propValue(i)<<endl;
            property_value = v.propValue(i);
            size_t found = property_value.find("EDGETYPE");
            if (found != std::string::npos)
                hasedge = true;
            while (found != std::string::npos) {
                property_value = property_value.substr(found + 8, property_value.length());
                size_t indi = property_value.find(" ");
                if (property_value.substr(indi + 1, indi + 4) == "LEFT") {

                    if (property_value[indi + 6] == '2')
                        left = true;
                    else
                        left = false;
                } else if (property_value.substr(indi + 1, indi + 5) == "RIGHT") {
                    if (property_value[indi + 7] == '2')
                        right = true;
                    else
                        right = false;
                }
                found = property_value.find("EDGETYPE");


            }
            assert(hasedge);
            if (hasedge) {
                if (left) {
                    _db.getStdCellLib(currentMacroName).setEdgeLeft(2);
                }
                else {
                    _db.getStdCellLib(currentMacroName).setEdgeLeft(1);
                }
                if (right) {
                    _db.getStdCellLib(currentMacroName).setEdgeRight(2);
                }
                else {
                    _db.getStdCellLib(currentMacroName).setEdgeRight(1);
                }

            }

        }

    }

    void LefReader::lef_macro_endcbk(const char *macroName) {
        //LefDataBase::lef_macro_endcbk(macroName);
        /*
        std::cout<< _db.getStdCellLib()[currentMacroName].getMacroName()<<std::endl;
        std::cout<<_db.getStdCellLib()[currentMacroName].getSizeX()<<" "<<_db.getStdCellLib()[currentMacroName].getSizeY()<<std::endl;
        for (auto const &pin : _db.getStdCellLib()[currentMacroName].getPins()) {
            std::cout<<pin.xLo()<<" "<<pin.yLo()<<" "<<pin.xHi()<<" "<<pin.yHi()<<std::endl;
        }
        */
    }

    void LefReader::lef_pin_cbk(lefiPin const &v) {

        //LefDataBase::lef_pin_cbk(v);
        //std::cout<<v.name()<<std::endl;
        std::string str = std::string(v.name());
        if (str == "vdd") {
            for (IndexType portIndex = 0; portIndex < v.numPorts(); ++portIndex) {
                //lefiGeometries test = *v.port(portIndex);
                for (IndexType geoIndex = 0; geoIndex < v.port(portIndex)->numItems(); ++geoIndex) {
                    if (v.port(portIndex)->itemType(geoIndex) == lefiGeomRectE) {
                        if (v.port(portIndex)->getRect(geoIndex)->yh < 0.5) {
                            _db.getStdCellLib(currentMacroName).setBottomVss(false);
                            //std::cout<<currentMacroName<<" vdd"<<std::endl;
                            break;
                        }
                    }
                }

            }
        } else if (str == "vss") {
            for (IndexType portIndex = 0; portIndex < v.numPorts(); ++portIndex) {
                //lefiGeometries test = *v.port(portIndex);
                for (IndexType geoIndex = 0; geoIndex < v.port(portIndex)->numItems(); ++geoIndex) {
                    if (v.port(portIndex)->itemType(geoIndex) == lefiGeomRectE) {
                        if (v.port(portIndex)->getRect(geoIndex)->yh < 0.5) {
                            _db.getStdCellLib(currentMacroName).setBottomVss(true);
                            //std::cout<<currentMacroName<<" vss"<<std::endl;
                            break;
                        }
                    }
                }

            }
        } else {
            for (IndexType portIndex = 0; portIndex < v.numPorts(); ++portIndex) {
                //lefiGeometries test = *v.port(portIndex);
                for (IndexType geoIndex = 0; geoIndex < v.port(portIndex)->numItems(); ++geoIndex) {
                    if (v.port(portIndex)->itemType(geoIndex) == lefiGeomRectE) {
                        _db.getStdCellLib(currentMacroName).addPin(
                                v.port(portIndex)->getRect(geoIndex)->xl,
                                v.port(portIndex)->getRect(geoIndex)->yl,
                                v.port(portIndex)->getRect(geoIndex)->xh,
                                v.port(portIndex)->getRect(geoIndex)->yh,
				v.name()
                        );
                        //_db.getStdCellLib(currentMacroName).addPinName(v.name());
                    }


                }

            }

        }

    }

    void LefReader::lef_obstruction_cbk(lefiObstruction const &v) {

    }

    void LefReader::lef_density_cbk(lefiDensity const &v) {

    }

    void LefReader::lef_timing_cbk(lefiTiming const &v) {

    }

    void LefReader::lef_array_cbk(lefiArray const &v) {

    }

    void LefReader::lef_prop_cbk(lefiProp const &v) {
/*
        std::string spacingkwd = "CELLEDGESPACINGTABLE";
        std::string edgetpkwd = "EDGETYPE";
        if (v.hasString()) {
            std::vector<std::string> vt;
            std::string s = v.string();
            boost::algorithm::split(vt, s, boost::algorithm::is_space());
            for (int i = 0; i < vt.size(); ++i) {
                if (boost::iequals(vt[i], spacingkwd)) {

                }
                if (boost::iequals(vt[i], edgetpkwd)) {
                    if (vt[i + 1] == "2" && vt[i + 2] == "1") {
                        _db.setLefEdgeSpacing12(atof(vt[i + 3].c_str()));
                    } else if (vt[i + 1] == "1" && vt[i + 2] == "2") {
                        _db.setLefEdgeSpacing12(atof(vt[i + 3].c_str()));
                    } else if (vt[i + 1] == "2" && vt[i + 2] == "2") {
                        _db.setLefEdgeSpacing22(atof(vt[i + 3].c_str()));
                    } else if (vt[i + 1] == "1" && vt[i + 2] == "1") {
                        _db.setLefEdgeSpacing11(atof(vt[i + 3].c_str()));
                    }

                }

            }
        }
    */
    }

    void LefReader::lef_noisemargin_cbk(lefiNoiseMargin const &v) {

    }

    void LefReader::lef_edgeratethreshold1_cbk(double v) {

    }

    void LefReader::lef_edgeratethreshold2_cbk(double v) {

    }

    void LefReader::lef_edgeratescalefactor_cbk(double v) {

    }

    void LefReader::lef_noisetable_cbk(lefiNoiseTable const &v) {

    }

    void LefReader::lef_correctiontable_cbk(lefiCorrectionTable const &v) {

    }

    void LefReader::lef_inputantenna_cbk(double v) {

    }

    void LefReader::lef_outputantenna_cbk(double v) {

    }

    void LefReader::lef_inoutantenna_cbk(double v) {

    }

    void LefReader::lef_antennainput_cbk(double v) {

    }

    void LefReader::lef_antennaoutput_cbk(double v) {

    }

    void LefReader::lef_antennainout_cbk(double v) {

    }

    void LefReader::lef_extension_cbk(const std::string &v) {

    }

    void readLef(std::string const &fileName, RawDatabase &db) {
        LefReader reader = LefReader(db);
        LefParser::read(reader, fileName.c_str());
        //db =reader.getDb();
    }
PROJECT_NAME_SPACE_END
