//
// Created by keren on 9/23/17.
//

#ifndef _LEFREADER_H
#define _LEFREADER_H

#include "LefDriver.h"
#include <boost/algorithm/string.hpp>
//#include "config.h"
//#include "RawDatabase.h"

PROJECT_NAMESPACE_BEGIN
    class LefReader : public LefParser::LefDataBase {
    public:
        /*
         * Constructor
         */
        //LefReader() = default;

        explicit LefReader(RawDatabase &db)
                : _db(db) {
            //_db = db;
            currentMacroName = "";
        }

        /*
         * Getter
         */
        const RawDatabase &getDb() const {
            return _db;
        }

        /*
         * Setter
         */
        void setDb(const RawDatabase &_db) {
            LefReader::_db = _db;
        }

        /*
         * Override functions
         */


        void lef_version_cbk(const std::string &v) override;

        void lef_version_cbk(double v) override;

        void lef_dividerchar_cbk(const std::string &v) override;

        void lef_casesensitive_cbk(int v) override;

        void lef_nowireextension_cbk(const std::string &v) override;

        void lef_manufacturing_cbk(double v) override;

        void lef_useminspacing_cbk(lefiUseMinSpacing const &v) override;

        void lef_clearancemeasure_cbk(const std::string &v) override;

        void lef_units_cbk(lefiUnits const &v) override;

        void lef_busbitchars_cbk(const std::string &v) override;

        void lef_laye_cbk(lefiLayer const &v) override;

        void lef_maxstackvia_cbk(lefiMaxStackVia const &v) override;

        void lef_via_cbk(lefiVia const &v) override;

        void lef_viarule_cbk(lefiViaRule const &v) override;

        void lef_spacing_cbk(lefiSpacing const &v) override;

        void lef_irdrop_cbk(lefiIRDrop const &v) override;

        void lef_minfeature_cbk(lefiMinFeature const &v) override;

        void lef_dielectric_cbk(double v) override;

        void lef_nondefault_cbk(lefiNonDefault const &v) override;

        void lef_site_cbk(lefiSite const &v) override;

        void lef_macrobegin_cbk(std::string const &v) override;

        void lef_macro_cbk(lefiMacro const &v) override;

        void lef_pin_cbk(lefiPin const &v) override;

        void lef_obstruction_cbk(lefiObstruction const &v) override;

        void lef_density_cbk(lefiDensity const &v) override;

        void lef_timing_cbk(lefiTiming const &v) override;

        void lef_array_cbk(lefiArray const &v) override;

        void lef_prop_cbk(lefiProp const &v) override;

        void lef_noisemargin_cbk(lefiNoiseMargin const &v) override;

        void lef_edgeratethreshold1_cbk(double v) override;

        void lef_edgeratethreshold2_cbk(double v) override;

        void lef_edgeratescalefactor_cbk(double v) override;

        void lef_noisetable_cbk(lefiNoiseTable const &v) override;

        void lef_correctiontable_cbk(lefiCorrectionTable const &v) override;

        void lef_inputantenna_cbk(double v) override;

        void lef_outputantenna_cbk(double v) override;

        void lef_inoutantenna_cbk(double v) override;

        void lef_antennainput_cbk(double v) override;

        void lef_antennaoutput_cbk(double v) override;

        void lef_antennainout_cbk(double v) override;

        void lef_extension_cbk(const std::string &v) override;

        void lef_macro_endcbk(const char *macroName) override;



    private:
        RawDatabase &_db;
        std::string currentMacroName = "";
    };
    void readLef(std::string const &fileName, RawDatabase &db);
PROJECT_NAME_SPACE_END

#endif //MIXEDSTACKLEGALIZATION_LEFREADER_H