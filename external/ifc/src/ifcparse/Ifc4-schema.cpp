#include <ifcparse/Ifc4.h>
#include <ifcparse/IfcSchema.h>
#include <string>

using namespace std::string_literals;
using namespace IfcParse;

declaration *IFC4_types[1173] = {nullptr};

const std::string strings[] = {
    "IfcAbsorbedDoseMeasure"s,
    "IfcAccelerationMeasure"s,
    "IfcActionRequestTypeEnum"s,
    "EMAIL"s,
    "FAX"s,
    "PHONE"s,
    "POST"s,
    "VERBAL"s,
    "USERDEFINED"s,
    "NOTDEFINED"s,
    "IfcActionSourceTypeEnum"s,
    "DEAD_LOAD_G"s,
    "COMPLETION_G1"s,
    "LIVE_LOAD_Q"s,
    "SNOW_S"s,
    "WIND_W"s,
    "PRESTRESSING_P"s,
    "SETTLEMENT_U"s,
    "TEMPERATURE_T"s,
    "EARTHQUAKE_E"s,
    "FIRE"s,
    "IMPULSE"s,
    "IMPACT"s,
    "TRANSPORT"s,
    "ERECTION"s,
    "PROPPING"s,
    "SYSTEM_IMPERFECTION"s,
    "SHRINKAGE"s,
    "CREEP"s,
    "LACK_OF_FIT"s,
    "BUOYANCY"s,
    "ICE"s,
    "CURRENT"s,
    "WAVE"s,
    "RAIN"s,
    "BRAKES"s,
    "IfcActionTypeEnum"s,
    "PERMANENT_G"s,
    "VARIABLE_Q"s,
    "EXTRAORDINARY_A"s,
    "IfcActuatorTypeEnum"s,
    "ELECTRICACTUATOR"s,
    "HANDOPERATEDACTUATOR"s,
    "HYDRAULICACTUATOR"s,
    "PNEUMATICACTUATOR"s,
    "THERMOSTATICACTUATOR"s,
    "IfcAddressTypeEnum"s,
    "OFFICE"s,
    "SITE"s,
    "HOME"s,
    "DISTRIBUTIONPOINT"s,
    "IfcAirTerminalBoxTypeEnum"s,
    "CONSTANTFLOW"s,
    "VARIABLEFLOWPRESSUREDEPENDANT"s,
    "VARIABLEFLOWPRESSUREINDEPENDANT"s,
    "IfcAirTerminalTypeEnum"s,
    "DIFFUSER"s,
    "GRILLE"s,
    "LOUVRE"s,
    "REGISTER"s,
    "IfcAirToAirHeatRecoveryTypeEnum"s,
    "FIXEDPLATECOUNTERFLOWEXCHANGER"s,
    "FIXEDPLATECROSSFLOWEXCHANGER"s,
    "FIXEDPLATEPARALLELFLOWEXCHANGER"s,
    "ROTARYWHEEL"s,
    "RUNAROUNDCOILLOOP"s,
    "HEATPIPE"s,
    "TWINTOWERENTHALPYRECOVERYLOOPS"s,
    "THERMOSIPHONSEALEDTUBEHEATEXCHANGERS"s,
    "THERMOSIPHONCOILTYPEHEATEXCHANGERS"s,
    "IfcAlarmTypeEnum"s,
    "BELL"s,
    "BREAKGLASSBUTTON"s,
    "LIGHT"s,
    "MANUALPULLBOX"s,
    "SIREN"s,
    "WHISTLE"s,
    "IfcAmountOfSubstanceMeasure"s,
    "IfcAnalysisModelTypeEnum"s,
    "IN_PLANE_LOADING_2D"s,
    "OUT_PLANE_LOADING_2D"s,
    "LOADING_3D"s,
    "IfcAnalysisTheoryTypeEnum"s,
    "FIRST_ORDER_THEORY"s,
    "SECOND_ORDER_THEORY"s,
    "THIRD_ORDER_THEORY"s,
    "FULL_NONLINEAR_THEORY"s,
    "IfcAngularVelocityMeasure"s,
    "IfcAreaDensityMeasure"s,
    "IfcAreaMeasure"s,
    "IfcArithmeticOperatorEnum"s,
    "ADD"s,
    "DIVIDE"s,
    "MULTIPLY"s,
    "SUBTRACT"s,
    "IfcAssemblyPlaceEnum"s,
    "FACTORY"s,
    "IfcAudioVisualApplianceTypeEnum"s,
    "AMPLIFIER"s,
    "CAMERA"s,
    "DISPLAY"s,
    "MICROPHONE"s,
    "PLAYER"s,
    "PROJECTOR"s,
    "RECEIVER"s,
    "SPEAKER"s,
    "SWITCHER"s,
    "TELEPHONE"s,
    "TUNER"s,
    "IfcBSplineCurveForm"s,
    "POLYLINE_FORM"s,
    "CIRCULAR_ARC"s,
    "ELLIPTIC_ARC"s,
    "PARABOLIC_ARC"s,
    "HYPERBOLIC_ARC"s,
    "UNSPECIFIED"s,
    "IfcBSplineSurfaceForm"s,
    "PLANE_SURF"s,
    "CYLINDRICAL_SURF"s,
    "CONICAL_SURF"s,
    "SPHERICAL_SURF"s,
    "TOROIDAL_SURF"s,
    "SURF_OF_REVOLUTION"s,
    "RULED_SURF"s,
    "GENERALISED_CONE"s,
    "QUADRIC_SURF"s,
    "SURF_OF_LINEAR_EXTRUSION"s,
    "IfcBeamTypeEnum"s,
    "BEAM"s,
    "JOIST"s,
    "HOLLOWCORE"s,
    "LINTEL"s,
    "SPANDREL"s,
    "T_BEAM"s,
    "IfcBenchmarkEnum"s,
    "GREATERTHAN"s,
    "GREATERTHANOREQUALTO"s,
    "LESSTHAN"s,
    "LESSTHANOREQUALTO"s,
    "EQUALTO"s,
    "NOTEQUALTO"s,
    "INCLUDES"s,
    "NOTINCLUDES"s,
    "INCLUDEDIN"s,
    "NOTINCLUDEDIN"s,
    "IfcBinary"s,
    "IfcBoilerTypeEnum"s,
    "WATER"s,
    "STEAM"s,
    "IfcBoolean"s,
    "IfcBooleanOperator"s,
    "UNION"s,
    "INTERSECTION"s,
    "DIFFERENCE"s,
    "IfcBuildingElementPartTypeEnum"s,
    "INSULATION"s,
    "PRECASTPANEL"s,
    "IfcBuildingElementProxyTypeEnum"s,
    "COMPLEX"s,
    "ELEMENT"s,
    "PARTIAL"s,
    "PROVISIONFORVOID"s,
    "PROVISIONFORSPACE"s,
    "IfcBuildingSystemTypeEnum"s,
    "FENESTRATION"s,
    "FOUNDATION"s,
    "LOADBEARING"s,
    "OUTERSHELL"s,
    "SHADING"s,
    "IfcBurnerTypeEnum"s,
    "IfcCableCarrierFittingTypeEnum"s,
    "BEND"s,
    "CROSS"s,
    "REDUCER"s,
    "TEE"s,
    "IfcCableCarrierSegmentTypeEnum"s,
    "CABLELADDERSEGMENT"s,
    "CABLETRAYSEGMENT"s,
    "CABLETRUNKINGSEGMENT"s,
    "CONDUITSEGMENT"s,
    "IfcCableFittingTypeEnum"s,
    "CONNECTOR"s,
    "ENTRY"s,
    "EXIT"s,
    "JUNCTION"s,
    "TRANSITION"s,
    "IfcCableSegmentTypeEnum"s,
    "BUSBARSEGMENT"s,
    "CABLESEGMENT"s,
    "CONDUCTORSEGMENT"s,
    "CORESEGMENT"s,
    "IfcCardinalPointReference"s,
    "IfcChangeActionEnum"s,
    "NOCHANGE"s,
    "MODIFIED"s,
    "ADDED"s,
    "DELETED"s,
    "IfcChillerTypeEnum"s,
    "AIRCOOLED"s,
    "WATERCOOLED"s,
    "HEATRECOVERY"s,
    "IfcChimneyTypeEnum"s,
    "IfcCoilTypeEnum"s,
    "DXCOOLINGCOIL"s,
    "ELECTRICHEATINGCOIL"s,
    "GASHEATINGCOIL"s,
    "HYDRONICCOIL"s,
    "STEAMHEATINGCOIL"s,
    "WATERCOOLINGCOIL"s,
    "WATERHEATINGCOIL"s,
    "IfcColumnTypeEnum"s,
    "COLUMN"s,
    "PILASTER"s,
    "IfcCommunicationsApplianceTypeEnum"s,
    "ANTENNA"s,
    "COMPUTER"s,
    "GATEWAY"s,
    "MODEM"s,
    "NETWORKAPPLIANCE"s,
    "NETWORKBRIDGE"s,
    "NETWORKHUB"s,
    "PRINTER"s,
    "REPEATER"s,
    "ROUTER"s,
    "SCANNER"s,
    "IfcComplexNumber"s,
    "IfcComplexPropertyTemplateTypeEnum"s,
    "P_COMPLEX"s,
    "Q_COMPLEX"s,
    "IfcCompoundPlaneAngleMeasure"s,
    "IfcCompressorTypeEnum"s,
    "DYNAMIC"s,
    "RECIPROCATING"s,
    "ROTARY"s,
    "SCROLL"s,
    "TROCHOIDAL"s,
    "SINGLESTAGE"s,
    "BOOSTER"s,
    "OPENTYPE"s,
    "HERMETIC"s,
    "SEMIHERMETIC"s,
    "WELDEDSHELLHERMETIC"s,
    "ROLLINGPISTON"s,
    "ROTARYVANE"s,
    "SINGLESCREW"s,
    "TWINSCREW"s,
    "IfcCondenserTypeEnum"s,
    "EVAPORATIVECOOLED"s,
    "WATERCOOLEDBRAZEDPLATE"s,
    "WATERCOOLEDSHELLCOIL"s,
    "WATERCOOLEDSHELLTUBE"s,
    "WATERCOOLEDTUBEINTUBE"s,
    "IfcConnectionTypeEnum"s,
    "ATPATH"s,
    "ATSTART"s,
    "ATEND"s,
    "IfcConstraintEnum"s,
    "HARD"s,
    "SOFT"s,
    "ADVISORY"s,
    "IfcConstructionEquipmentResourceTypeEnum"s,
    "DEMOLISHING"s,
    "EARTHMOVING"s,
    "ERECTING"s,
    "HEATING"s,
    "LIGHTING"s,
    "PAVING"s,
    "PUMPING"s,
    "TRANSPORTING"s,
    "IfcConstructionMaterialResourceTypeEnum"s,
    "AGGREGATES"s,
    "CONCRETE"s,
    "DRYWALL"s,
    "FUEL"s,
    "GYPSUM"s,
    "MASONRY"s,
    "METAL"s,
    "PLASTIC"s,
    "WOOD"s,
    "IfcConstructionProductResourceTypeEnum"s,
    "ASSEMBLY"s,
    "FORMWORK"s,
    "IfcContextDependentMeasure"s,
    "IfcControllerTypeEnum"s,
    "FLOATING"s,
    "PROGRAMMABLE"s,
    "PROPORTIONAL"s,
    "MULTIPOSITION"s,
    "TWOPOSITION"s,
    "IfcCooledBeamTypeEnum"s,
    "ACTIVE"s,
    "PASSIVE"s,
    "IfcCoolingTowerTypeEnum"s,
    "NATURALDRAFT"s,
    "MECHANICALINDUCEDDRAFT"s,
    "MECHANICALFORCEDDRAFT"s,
    "IfcCostItemTypeEnum"s,
    "IfcCostScheduleTypeEnum"s,
    "BUDGET"s,
    "COSTPLAN"s,
    "ESTIMATE"s,
    "TENDER"s,
    "PRICEDBILLOFQUANTITIES"s,
    "UNPRICEDBILLOFQUANTITIES"s,
    "SCHEDULEOFRATES"s,
    "IfcCountMeasure"s,
    "IfcCoveringTypeEnum"s,
    "CEILING"s,
    "FLOORING"s,
    "CLADDING"s,
    "ROOFING"s,
    "MOLDING"s,
    "SKIRTINGBOARD"s,
    "MEMBRANE"s,
    "SLEEVING"s,
    "WRAPPING"s,
    "IfcCrewResourceTypeEnum"s,
    "IfcCurtainWallTypeEnum"s,
    "IfcCurvatureMeasure"s,
    "IfcCurveInterpolationEnum"s,
    "LINEAR"s,
    "LOG_LINEAR"s,
    "LOG_LOG"s,
    "IfcDamperTypeEnum"s,
    "BACKDRAFTDAMPER"s,
    "BALANCINGDAMPER"s,
    "BLASTDAMPER"s,
    "CONTROLDAMPER"s,
    "FIREDAMPER"s,
    "FIRESMOKEDAMPER"s,
    "FUMEHOODEXHAUST"s,
    "GRAVITYDAMPER"s,
    "GRAVITYRELIEFDAMPER"s,
    "RELIEFDAMPER"s,
    "SMOKEDAMPER"s,
    "IfcDataOriginEnum"s,
    "MEASURED"s,
    "PREDICTED"s,
    "SIMULATED"s,
    "IfcDate"s,
    "IfcDateTime"s,
    "IfcDayInMonthNumber"s,
    "IfcDayInWeekNumber"s,
    "IfcDerivedUnitEnum"s,
    "ANGULARVELOCITYUNIT"s,
    "AREADENSITYUNIT"s,
    "COMPOUNDPLANEANGLEUNIT"s,
    "DYNAMICVISCOSITYUNIT"s,
    "HEATFLUXDENSITYUNIT"s,
    "INTEGERCOUNTRATEUNIT"s,
    "ISOTHERMALMOISTURECAPACITYUNIT"s,
    "KINEMATICVISCOSITYUNIT"s,
    "LINEARVELOCITYUNIT"s,
    "MASSDENSITYUNIT"s,
    "MASSFLOWRATEUNIT"s,
    "MOISTUREDIFFUSIVITYUNIT"s,
    "MOLECULARWEIGHTUNIT"s,
    "SPECIFICHEATCAPACITYUNIT"s,
    "THERMALADMITTANCEUNIT"s,
    "THERMALCONDUCTANCEUNIT"s,
    "THERMALRESISTANCEUNIT"s,
    "THERMALTRANSMITTANCEUNIT"s,
    "VAPORPERMEABILITYUNIT"s,
    "VOLUMETRICFLOWRATEUNIT"s,
    "ROTATIONALFREQUENCYUNIT"s,
    "TORQUEUNIT"s,
    "MOMENTOFINERTIAUNIT"s,
    "LINEARMOMENTUNIT"s,
    "LINEARFORCEUNIT"s,
    "PLANARFORCEUNIT"s,
    "MODULUSOFELASTICITYUNIT"s,
    "SHEARMODULUSUNIT"s,
    "LINEARSTIFFNESSUNIT"s,
    "ROTATIONALSTIFFNESSUNIT"s,
    "MODULUSOFSUBGRADEREACTIONUNIT"s,
    "ACCELERATIONUNIT"s,
    "CURVATUREUNIT"s,
    "HEATINGVALUEUNIT"s,
    "IONCONCENTRATIONUNIT"s,
    "LUMINOUSINTENSITYDISTRIBUTIONUNIT"s,
    "MASSPERLENGTHUNIT"s,
    "MODULUSOFLINEARSUBGRADEREACTIONUNIT"s,
    "MODULUSOFROTATIONALSUBGRADEREACTIONUNIT"s,
    "PHUNIT"s,
    "ROTATIONALMASSUNIT"s,
    "SECTIONAREAINTEGRALUNIT"s,
    "SECTIONMODULUSUNIT"s,
    "SOUNDPOWERLEVELUNIT"s,
    "SOUNDPOWERUNIT"s,
    "SOUNDPRESSURELEVELUNIT"s,
    "SOUNDPRESSUREUNIT"s,
    "TEMPERATUREGRADIENTUNIT"s,
    "TEMPERATURERATEOFCHANGEUNIT"s,
    "THERMALEXPANSIONCOEFFICIENTUNIT"s,
    "WARPINGCONSTANTUNIT"s,
    "WARPINGMOMENTUNIT"s,
    "IfcDescriptiveMeasure"s,
    "IfcDimensionCount"s,
    "IfcDirectionSenseEnum"s,
    "POSITIVE"s,
    "NEGATIVE"s,
    "IfcDiscreteAccessoryTypeEnum"s,
    "ANCHORPLATE"s,
    "BRACKET"s,
    "SHOE"s,
    "IfcDistributionChamberElementTypeEnum"s,
    "FORMEDDUCT"s,
    "INSPECTIONCHAMBER"s,
    "INSPECTIONPIT"s,
    "MANHOLE"s,
    "METERCHAMBER"s,
    "SUMP"s,
    "TRENCH"s,
    "VALVECHAMBER"s,
    "IfcDistributionPortTypeEnum"s,
    "CABLE"s,
    "CABLECARRIER"s,
    "DUCT"s,
    "PIPE"s,
    "IfcDistributionSystemEnum"s,
    "AIRCONDITIONING"s,
    "AUDIOVISUAL"s,
    "CHEMICAL"s,
    "CHILLEDWATER"s,
    "COMMUNICATION"s,
    "COMPRESSEDAIR"s,
    "CONDENSERWATER"s,
    "CONTROL"s,
    "CONVEYING"s,
    "DATA"s,
    "DISPOSAL"s,
    "DOMESTICCOLDWATER"s,
    "DOMESTICHOTWATER"s,
    "DRAINAGE"s,
    "EARTHING"s,
    "ELECTRICAL"s,
    "ELECTROACOUSTIC"s,
    "EXHAUST"s,
    "FIREPROTECTION"s,
    "GAS"s,
    "HAZARDOUS"s,
    "LIGHTNINGPROTECTION"s,
    "MUNICIPALSOLIDWASTE"s,
    "OIL"s,
    "OPERATIONAL"s,
    "POWERGENERATION"s,
    "RAINWATER"s,
    "REFRIGERATION"s,
    "SECURITY"s,
    "SEWAGE"s,
    "SIGNAL"s,
    "STORMWATER"s,
    "TV"s,
    "VACUUM"s,
    "VENT"s,
    "VENTILATION"s,
    "WASTEWATER"s,
    "WATERSUPPLY"s,
    "IfcDocumentConfidentialityEnum"s,
    "PUBLIC"s,
    "RESTRICTED"s,
    "CONFIDENTIAL"s,
    "PERSONAL"s,
    "IfcDocumentStatusEnum"s,
    "DRAFT"s,
    "FINALDRAFT"s,
    "FINAL"s,
    "REVISION"s,
    "IfcDoorPanelOperationEnum"s,
    "SWINGING"s,
    "DOUBLE_ACTING"s,
    "SLIDING"s,
    "FOLDING"s,
    "REVOLVING"s,
    "ROLLINGUP"s,
    "FIXEDPANEL"s,
    "IfcDoorPanelPositionEnum"s,
    "LEFT"s,
    "MIDDLE"s,
    "RIGHT"s,
    "IfcDoorStyleConstructionEnum"s,
    "ALUMINIUM"s,
    "HIGH_GRADE_STEEL"s,
    "STEEL"s,
    "ALUMINIUM_WOOD"s,
    "ALUMINIUM_PLASTIC"s,
    "IfcDoorStyleOperationEnum"s,
    "SINGLE_SWING_LEFT"s,
    "SINGLE_SWING_RIGHT"s,
    "DOUBLE_DOOR_SINGLE_SWING"s,
    "DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_LEFT"s,
    "DOUBLE_DOOR_SINGLE_SWING_OPPOSITE_RIGHT"s,
    "DOUBLE_SWING_LEFT"s,
    "DOUBLE_SWING_RIGHT"s,
    "DOUBLE_DOOR_DOUBLE_SWING"s,
    "SLIDING_TO_LEFT"s,
    "SLIDING_TO_RIGHT"s,
    "DOUBLE_DOOR_SLIDING"s,
    "FOLDING_TO_LEFT"s,
    "FOLDING_TO_RIGHT"s,
    "DOUBLE_DOOR_FOLDING"s,
    "IfcDoorTypeEnum"s,
    "DOOR"s,
    "GATE"s,
    "TRAPDOOR"s,
    "IfcDoorTypeOperationEnum"s,
    "SWING_FIXED_LEFT"s,
    "SWING_FIXED_RIGHT"s,
    "IfcDoseEquivalentMeasure"s,
    "IfcDuctFittingTypeEnum"s,
    "OBSTRUCTION"s,
    "IfcDuctSegmentTypeEnum"s,
    "RIGIDSEGMENT"s,
    "FLEXIBLESEGMENT"s,
    "IfcDuctSilencerTypeEnum"s,
    "FLATOVAL"s,
    "RECTANGULAR"s,
    "ROUND"s,
    "IfcDuration"s,
    "IfcDynamicViscosityMeasure"s,
    "IfcElectricApplianceTypeEnum"s,
    "DISHWASHER"s,
    "ELECTRICCOOKER"s,
    "FREESTANDINGELECTRICHEATER"s,
    "FREESTANDINGFAN"s,
    "FREESTANDINGWATERHEATER"s,
    "FREESTANDINGWATERCOOLER"s,
    "FREEZER"s,
    "FRIDGE_FREEZER"s,
    "HANDDRYER"s,
    "KITCHENMACHINE"s,
    "MICROWAVE"s,
    "PHOTOCOPIER"s,
    "REFRIGERATOR"s,
    "TUMBLEDRYER"s,
    "VENDINGMACHINE"s,
    "WASHINGMACHINE"s,
    "IfcElectricCapacitanceMeasure"s,
    "IfcElectricChargeMeasure"s,
    "IfcElectricConductanceMeasure"s,
    "IfcElectricCurrentMeasure"s,
    "IfcElectricDistributionBoardTypeEnum"s,
    "CONSUMERUNIT"s,
    "DISTRIBUTIONBOARD"s,
    "MOTORCONTROLCENTRE"s,
    "SWITCHBOARD"s,
    "IfcElectricFlowStorageDeviceTypeEnum"s,
    "BATTERY"s,
    "CAPACITORBANK"s,
    "HARMONICFILTER"s,
    "INDUCTORBANK"s,
    "UPS"s,
    "IfcElectricGeneratorTypeEnum"s,
    "CHP"s,
    "ENGINEGENERATOR"s,
    "STANDALONE"s,
    "IfcElectricMotorTypeEnum"s,
    "DC"s,
    "INDUCTION"s,
    "POLYPHASE"s,
    "RELUCTANCESYNCHRONOUS"s,
    "SYNCHRONOUS"s,
    "IfcElectricResistanceMeasure"s,
    "IfcElectricTimeControlTypeEnum"s,
    "TIMECLOCK"s,
    "TIMEDELAY"s,
    "RELAY"s,
    "IfcElectricVoltageMeasure"s,
    "IfcElementAssemblyTypeEnum"s,
    "ACCESSORY_ASSEMBLY"s,
    "ARCH"s,
    "BEAM_GRID"s,
    "BRACED_FRAME"s,
    "GIRDER"s,
    "REINFORCEMENT_UNIT"s,
    "RIGID_FRAME"s,
    "SLAB_FIELD"s,
    "TRUSS"s,
    "IfcElementCompositionEnum"s,
    "IfcEnergyMeasure"s,
    "IfcEngineTypeEnum"s,
    "EXTERNALCOMBUSTION"s,
    "INTERNALCOMBUSTION"s,
    "IfcEvaporativeCoolerTypeEnum"s,
    "DIRECTEVAPORATIVERANDOMMEDIAAIRCOOLER"s,
    "DIRECTEVAPORATIVERIGIDMEDIAAIRCOOLER"s,
    "DIRECTEVAPORATIVESLINGERSPACKAGEDAIRCOOLER"s,
    "DIRECTEVAPORATIVEPACKAGEDROTARYAIRCOOLER"s,
    "DIRECTEVAPORATIVEAIRWASHER"s,
    "INDIRECTEVAPORATIVEPACKAGEAIRCOOLER"s,
    "INDIRECTEVAPORATIVEWETCOIL"s,
    "INDIRECTEVAPORATIVECOOLINGTOWERORCOILCOOLER"s,
    "INDIRECTDIRECTCOMBINATION"s,
    "IfcEvaporatorTypeEnum"s,
    "DIRECTEXPANSION"s,
    "DIRECTEXPANSIONSHELLANDTUBE"s,
    "DIRECTEXPANSIONTUBEINTUBE"s,
    "DIRECTEXPANSIONBRAZEDPLATE"s,
    "FLOODEDSHELLANDTUBE"s,
    "SHELLANDCOIL"s,
    "IfcEventTriggerTypeEnum"s,
    "EVENTRULE"s,
    "EVENTMESSAGE"s,
    "EVENTTIME"s,
    "EVENTCOMPLEX"s,
    "IfcEventTypeEnum"s,
    "STARTEVENT"s,
    "ENDEVENT"s,
    "INTERMEDIATEEVENT"s,
    "IfcExternalSpatialElementTypeEnum"s,
    "EXTERNAL"s,
    "EXTERNAL_EARTH"s,
    "EXTERNAL_WATER"s,
    "EXTERNAL_FIRE"s,
    "IfcFanTypeEnum"s,
    "CENTRIFUGALFORWARDCURVED"s,
    "CENTRIFUGALRADIAL"s,
    "CENTRIFUGALBACKWARDINCLINEDCURVED"s,
    "CENTRIFUGALAIRFOIL"s,
    "TUBEAXIAL"s,
    "VANEAXIAL"s,
    "PROPELLORAXIAL"s,
    "IfcFastenerTypeEnum"s,
    "GLUE"s,
    "MORTAR"s,
    "WELD"s,
    "IfcFilterTypeEnum"s,
    "AIRPARTICLEFILTER"s,
    "COMPRESSEDAIRFILTER"s,
    "ODORFILTER"s,
    "OILFILTER"s,
    "STRAINER"s,
    "WATERFILTER"s,
    "IfcFireSuppressionTerminalTypeEnum"s,
    "BREECHINGINLET"s,
    "FIREHYDRANT"s,
    "HOSEREEL"s,
    "SPRINKLER"s,
    "SPRINKLERDEFLECTOR"s,
    "IfcFlowDirectionEnum"s,
    "SOURCE"s,
    "SINK"s,
    "SOURCEANDSINK"s,
    "IfcFlowInstrumentTypeEnum"s,
    "PRESSUREGAUGE"s,
    "THERMOMETER"s,
    "AMMETER"s,
    "FREQUENCYMETER"s,
    "POWERFACTORMETER"s,
    "PHASEANGLEMETER"s,
    "VOLTMETER_PEAK"s,
    "VOLTMETER_RMS"s,
    "IfcFlowMeterTypeEnum"s,
    "ENERGYMETER"s,
    "GASMETER"s,
    "OILMETER"s,
    "WATERMETER"s,
    "IfcFontStyle"s,
    "IfcFontVariant"s,
    "IfcFontWeight"s,
    "IfcFootingTypeEnum"s,
    "CAISSON_FOUNDATION"s,
    "FOOTING_BEAM"s,
    "PAD_FOOTING"s,
    "PILE_CAP"s,
    "STRIP_FOOTING"s,
    "IfcForceMeasure"s,
    "IfcFrequencyMeasure"s,
    "IfcFurnitureTypeEnum"s,
    "CHAIR"s,
    "TABLE"s,
    "DESK"s,
    "BED"s,
    "FILECABINET"s,
    "SHELF"s,
    "SOFA"s,
    "IfcGeographicElementTypeEnum"s,
    "TERRAIN"s,
    "IfcGeometricProjectionEnum"s,
    "GRAPH_VIEW"s,
    "SKETCH_VIEW"s,
    "MODEL_VIEW"s,
    "PLAN_VIEW"s,
    "REFLECTED_PLAN_VIEW"s,
    "SECTION_VIEW"s,
    "ELEVATION_VIEW"s,
    "IfcGlobalOrLocalEnum"s,
    "GLOBAL_COORDS"s,
    "LOCAL_COORDS"s,
    "IfcGloballyUniqueId"s,
    "IfcGridTypeEnum"s,
    "RADIAL"s,
    "TRIANGULAR"s,
    "IRREGULAR"s,
    "IfcHeatExchangerTypeEnum"s,
    "PLATE"s,
    "SHELLANDTUBE"s,
    "IfcHeatFluxDensityMeasure"s,
    "IfcHeatingValueMeasure"s,
    "IfcHumidifierTypeEnum"s,
    "STEAMINJECTION"s,
    "ADIABATICAIRWASHER"s,
    "ADIABATICPAN"s,
    "ADIABATICWETTEDELEMENT"s,
    "ADIABATICATOMIZING"s,
    "ADIABATICULTRASONIC"s,
    "ADIABATICRIGIDMEDIA"s,
    "ADIABATICCOMPRESSEDAIRNOZZLE"s,
    "ASSISTEDELECTRIC"s,
    "ASSISTEDNATURALGAS"s,
    "ASSISTEDPROPANE"s,
    "ASSISTEDBUTANE"s,
    "ASSISTEDSTEAM"s,
    "IfcIdentifier"s,
    "IfcIlluminanceMeasure"s,
    "IfcInductanceMeasure"s,
    "IfcInteger"s,
    "IfcIntegerCountRateMeasure"s,
    "IfcInterceptorTypeEnum"s,
    "CYCLONIC"s,
    "GREASE"s,
    "PETROL"s,
    "IfcInternalOrExternalEnum"s,
    "INTERNAL"s,
    "IfcInventoryTypeEnum"s,
    "ASSETINVENTORY"s,
    "SPACEINVENTORY"s,
    "FURNITUREINVENTORY"s,
    "IfcIonConcentrationMeasure"s,
    "IfcIsothermalMoistureCapacityMeasure"s,
    "IfcJunctionBoxTypeEnum"s,
    "POWER"s,
    "IfcKinematicViscosityMeasure"s,
    "IfcKnotType"s,
    "UNIFORM_KNOTS"s,
    "QUASI_UNIFORM_KNOTS"s,
    "PIECEWISE_BEZIER_KNOTS"s,
    "IfcLabel"s,
    "IfcLaborResourceTypeEnum"s,
    "ADMINISTRATION"s,
    "CARPENTRY"s,
    "CLEANING"s,
    "ELECTRIC"s,
    "FINISHING"s,
    "GENERAL"s,
    "HVAC"s,
    "LANDSCAPING"s,
    "PAINTING"s,
    "PLUMBING"s,
    "SITEGRADING"s,
    "STEELWORK"s,
    "SURVEYING"s,
    "IfcLampTypeEnum"s,
    "COMPACTFLUORESCENT"s,
    "FLUORESCENT"s,
    "HALOGEN"s,
    "HIGHPRESSUREMERCURY"s,
    "HIGHPRESSURESODIUM"s,
    "LED"s,
    "METALHALIDE"s,
    "OLED"s,
    "TUNGSTENFILAMENT"s,
    "IfcLanguageId"s,
    "IfcLayerSetDirectionEnum"s,
    "AXIS1"s,
    "AXIS2"s,
    "AXIS3"s,
    "IfcLengthMeasure"s,
    "IfcLightDistributionCurveEnum"s,
    "TYPE_A"s,
    "TYPE_B"s,
    "TYPE_C"s,
    "IfcLightEmissionSourceEnum"s,
    "LIGHTEMITTINGDIODE"s,
    "LOWPRESSURESODIUM"s,
    "LOWVOLTAGEHALOGEN"s,
    "MAINVOLTAGEHALOGEN"s,
    "IfcLightFixtureTypeEnum"s,
    "POINTSOURCE"s,
    "DIRECTIONSOURCE"s,
    "SECURITYLIGHTING"s,
    "IfcLinearForceMeasure"s,
    "IfcLinearMomentMeasure"s,
    "IfcLinearStiffnessMeasure"s,
    "IfcLinearVelocityMeasure"s,
    "IfcLoadGroupTypeEnum"s,
    "LOAD_GROUP"s,
    "LOAD_CASE"s,
    "LOAD_COMBINATION"s,
    "IfcLogical"s,
    "IfcLogicalOperatorEnum"s,
    "LOGICALAND"s,
    "LOGICALOR"s,
    "LOGICALXOR"s,
    "LOGICALNOTAND"s,
    "LOGICALNOTOR"s,
    "IfcLuminousFluxMeasure"s,
    "IfcLuminousIntensityDistributionMeasure"s,
    "IfcLuminousIntensityMeasure"s,
    "IfcMagneticFluxDensityMeasure"s,
    "IfcMagneticFluxMeasure"s,
    "IfcMassDensityMeasure"s,
    "IfcMassFlowRateMeasure"s,
    "IfcMassMeasure"s,
    "IfcMassPerLengthMeasure"s,
    "IfcMechanicalFastenerTypeEnum"s,
    "ANCHORBOLT"s,
    "BOLT"s,
    "DOWEL"s,
    "NAIL"s,
    "NAILPLATE"s,
    "RIVET"s,
    "SCREW"s,
    "SHEARCONNECTOR"s,
    "STAPLE"s,
    "STUDSHEARCONNECTOR"s,
    "IfcMedicalDeviceTypeEnum"s,
    "AIRSTATION"s,
    "FEEDAIRUNIT"s,
    "OXYGENGENERATOR"s,
    "OXYGENPLANT"s,
    "VACUUMSTATION"s,
    "IfcMemberTypeEnum"s,
    "BRACE"s,
    "CHORD"s,
    "COLLAR"s,
    "MEMBER"s,
    "MULLION"s,
    "PURLIN"s,
    "RAFTER"s,
    "STRINGER"s,
    "STRUT"s,
    "STUD"s,
    "IfcModulusOfElasticityMeasure"s,
    "IfcModulusOfLinearSubgradeReactionMeasure"s,
    "IfcModulusOfRotationalSubgradeReactionMeasure"s,
    "IfcModulusOfRotationalSubgradeReactionSelect"s,
    "IfcModulusOfSubgradeReactionMeasure"s,
    "IfcModulusOfSubgradeReactionSelect"s,
    "IfcModulusOfTranslationalSubgradeReactionSelect"s,
    "IfcMoistureDiffusivityMeasure"s,
    "IfcMolecularWeightMeasure"s,
    "IfcMomentOfInertiaMeasure"s,
    "IfcMonetaryMeasure"s,
    "IfcMonthInYearNumber"s,
    "IfcMotorConnectionTypeEnum"s,
    "BELTDRIVE"s,
    "COUPLING"s,
    "DIRECTDRIVE"s,
    "IfcNonNegativeLengthMeasure"s,
    "IfcNullStyle"s,
    "NULL"s,
    "IfcNumericMeasure"s,
    "IfcObjectTypeEnum"s,
    "PRODUCT"s,
    "PROCESS"s,
    "RESOURCE"s,
    "ACTOR"s,
    "GROUP"s,
    "PROJECT"s,
    "IfcObjectiveEnum"s,
    "CODECOMPLIANCE"s,
    "CODEWAIVER"s,
    "DESIGNINTENT"s,
    "HEALTHANDSAFETY"s,
    "MERGECONFLICT"s,
    "MODELVIEW"s,
    "PARAMETER"s,
    "REQUIREMENT"s,
    "SPECIFICATION"s,
    "TRIGGERCONDITION"s,
    "IfcOccupantTypeEnum"s,
    "ASSIGNEE"s,
    "ASSIGNOR"s,
    "LESSEE"s,
    "LESSOR"s,
    "LETTINGAGENT"s,
    "OWNER"s,
    "TENANT"s,
    "IfcOpeningElementTypeEnum"s,
    "OPENING"s,
    "RECESS"s,
    "IfcOutletTypeEnum"s,
    "AUDIOVISUALOUTLET"s,
    "COMMUNICATIONSOUTLET"s,
    "POWEROUTLET"s,
    "DATAOUTLET"s,
    "TELEPHONEOUTLET"s,
    "IfcPHMeasure"s,
    "IfcParameterValue"s,
    "IfcPerformanceHistoryTypeEnum"s,
    "IfcPermeableCoveringOperationEnum"s,
    "GRILL"s,
    "LOUVER"s,
    "SCREEN"s,
    "IfcPermitTypeEnum"s,
    "ACCESS"s,
    "BUILDING"s,
    "WORK"s,
    "IfcPhysicalOrVirtualEnum"s,
    "PHYSICAL"s,
    "VIRTUAL"s,
    "IfcPileConstructionEnum"s,
    "CAST_IN_PLACE"s,
    "COMPOSITE"s,
    "PRECAST_CONCRETE"s,
    "PREFAB_STEEL"s,
    "IfcPileTypeEnum"s,
    "BORED"s,
    "DRIVEN"s,
    "JETGROUTING"s,
    "COHESION"s,
    "FRICTION"s,
    "SUPPORT"s,
    "IfcPipeFittingTypeEnum"s,
    "IfcPipeSegmentTypeEnum"s,
    "CULVERT"s,
    "GUTTER"s,
    "SPOOL"s,
    "IfcPlanarForceMeasure"s,
    "IfcPlaneAngleMeasure"s,
    "IfcPlateTypeEnum"s,
    "CURTAIN_PANEL"s,
    "SHEET"s,
    "IfcPositiveInteger"s,
    "IfcPositiveLengthMeasure"s,
    "IfcPositivePlaneAngleMeasure"s,
    "IfcPowerMeasure"s,
    "IfcPreferredSurfaceCurveRepresentation"s,
    "CURVE3D"s,
    "PCURVE_S1"s,
    "PCURVE_S2"s,
    "IfcPresentableText"s,
    "IfcPressureMeasure"s,
    "IfcProcedureTypeEnum"s,
    "ADVICE_CAUTION"s,
    "ADVICE_NOTE"s,
    "ADVICE_WARNING"s,
    "CALIBRATION"s,
    "DIAGNOSTIC"s,
    "SHUTDOWN"s,
    "STARTUP"s,
    "IfcProfileTypeEnum"s,
    "CURVE"s,
    "AREA"s,
    "IfcProjectOrderTypeEnum"s,
    "CHANGEORDER"s,
    "MAINTENANCEWORKORDER"s,
    "MOVEORDER"s,
    "PURCHASEORDER"s,
    "WORKORDER"s,
    "IfcProjectedOrTrueLengthEnum"s,
    "PROJECTED_LENGTH"s,
    "TRUE_LENGTH"s,
    "IfcProjectionElementTypeEnum"s,
    "IfcPropertySetTemplateTypeEnum"s,
    "PSET_TYPEDRIVENONLY"s,
    "PSET_TYPEDRIVENOVERRIDE"s,
    "PSET_OCCURRENCEDRIVEN"s,
    "PSET_PERFORMANCEDRIVEN"s,
    "QTO_TYPEDRIVENONLY"s,
    "QTO_TYPEDRIVENOVERRIDE"s,
    "QTO_OCCURRENCEDRIVEN"s,
    "IfcProtectiveDeviceTrippingUnitTypeEnum"s,
    "ELECTRONIC"s,
    "ELECTROMAGNETIC"s,
    "RESIDUALCURRENT"s,
    "THERMAL"s,
    "IfcProtectiveDeviceTypeEnum"s,
    "CIRCUITBREAKER"s,
    "EARTHLEAKAGECIRCUITBREAKER"s,
    "EARTHINGSWITCH"s,
    "FUSEDISCONNECTOR"s,
    "RESIDUALCURRENTCIRCUITBREAKER"s,
    "RESIDUALCURRENTSWITCH"s,
    "VARISTOR"s,
    "IfcPumpTypeEnum"s,
    "CIRCULATOR"s,
    "ENDSUCTION"s,
    "SPLITCASE"s,
    "SUBMERSIBLEPUMP"s,
    "SUMPPUMP"s,
    "VERTICALINLINE"s,
    "VERTICALTURBINE"s,
    "IfcRadioActivityMeasure"s,
    "IfcRailingTypeEnum"s,
    "HANDRAIL"s,
    "GUARDRAIL"s,
    "BALUSTRADE"s,
    "IfcRampFlightTypeEnum"s,
    "STRAIGHT"s,
    "SPIRAL"s,
    "IfcRampTypeEnum"s,
    "STRAIGHT_RUN_RAMP"s,
    "TWO_STRAIGHT_RUN_RAMP"s,
    "QUARTER_TURN_RAMP"s,
    "TWO_QUARTER_TURN_RAMP"s,
    "HALF_TURN_RAMP"s,
    "SPIRAL_RAMP"s,
    "IfcRatioMeasure"s,
    "IfcReal"s,
    "IfcRecurrenceTypeEnum"s,
    "DAILY"s,
    "WEEKLY"s,
    "MONTHLY_BY_DAY_OF_MONTH"s,
    "MONTHLY_BY_POSITION"s,
    "BY_DAY_COUNT"s,
    "BY_WEEKDAY_COUNT"s,
    "YEARLY_BY_DAY_OF_MONTH"s,
    "YEARLY_BY_POSITION"s,
    "IfcReflectanceMethodEnum"s,
    "BLINN"s,
    "FLAT"s,
    "GLASS"s,
    "MATT"s,
    "MIRROR"s,
    "PHONG"s,
    "STRAUSS"s,
    "IfcReinforcingBarRoleEnum"s,
    "MAIN"s,
    "SHEAR"s,
    "LIGATURE"s,
    "PUNCHING"s,
    "EDGE"s,
    "RING"s,
    "ANCHORING"s,
    "IfcReinforcingBarSurfaceEnum"s,
    "PLAIN"s,
    "TEXTURED"s,
    "IfcReinforcingBarTypeEnum"s,
    "IfcReinforcingMeshTypeEnum"s,
    "IfcRoleEnum"s,
    "SUPPLIER"s,
    "MANUFACTURER"s,
    "CONTRACTOR"s,
    "SUBCONTRACTOR"s,
    "ARCHITECT"s,
    "STRUCTURALENGINEER"s,
    "COSTENGINEER"s,
    "CLIENT"s,
    "BUILDINGOWNER"s,
    "BUILDINGOPERATOR"s,
    "MECHANICALENGINEER"s,
    "ELECTRICALENGINEER"s,
    "PROJECTMANAGER"s,
    "FACILITIESMANAGER"s,
    "CIVILENGINEER"s,
    "COMMISSIONINGENGINEER"s,
    "ENGINEER"s,
    "CONSULTANT"s,
    "CONSTRUCTIONMANAGER"s,
    "FIELDCONSTRUCTIONMANAGER"s,
    "RESELLER"s,
    "IfcRoofTypeEnum"s,
    "FLAT_ROOF"s,
    "SHED_ROOF"s,
    "GABLE_ROOF"s,
    "HIP_ROOF"s,
    "HIPPED_GABLE_ROOF"s,
    "GAMBREL_ROOF"s,
    "MANSARD_ROOF"s,
    "BARREL_ROOF"s,
    "RAINBOW_ROOF"s,
    "BUTTERFLY_ROOF"s,
    "PAVILION_ROOF"s,
    "DOME_ROOF"s,
    "FREEFORM"s,
    "IfcRotationalFrequencyMeasure"s,
    "IfcRotationalMassMeasure"s,
    "IfcRotationalStiffnessMeasure"s,
    "IfcRotationalStiffnessSelect"s,
    "IfcSIPrefix"s,
    "EXA"s,
    "PETA"s,
    "TERA"s,
    "GIGA"s,
    "MEGA"s,
    "KILO"s,
    "HECTO"s,
    "DECA"s,
    "DECI"s,
    "CENTI"s,
    "MILLI"s,
    "MICRO"s,
    "NANO"s,
    "PICO"s,
    "FEMTO"s,
    "ATTO"s,
    "IfcSIUnitName"s,
    "AMPERE"s,
    "BECQUEREL"s,
    "CANDELA"s,
    "COULOMB"s,
    "CUBIC_METRE"s,
    "DEGREE_CELSIUS"s,
    "FARAD"s,
    "GRAM"s,
    "GRAY"s,
    "HENRY"s,
    "HERTZ"s,
    "JOULE"s,
    "KELVIN"s,
    "LUMEN"s,
    "LUX"s,
    "METRE"s,
    "MOLE"s,
    "NEWTON"s,
    "OHM"s,
    "PASCAL"s,
    "RADIAN"s,
    "SECOND"s,
    "SIEMENS"s,
    "SIEVERT"s,
    "SQUARE_METRE"s,
    "STERADIAN"s,
    "TESLA"s,
    "VOLT"s,
    "WATT"s,
    "WEBER"s,
    "IfcSanitaryTerminalTypeEnum"s,
    "BATH"s,
    "BIDET"s,
    "CISTERN"s,
    "SHOWER"s,
    "SANITARYFOUNTAIN"s,
    "TOILETPAN"s,
    "URINAL"s,
    "WASHHANDBASIN"s,
    "WCSEAT"s,
    "IfcSectionModulusMeasure"s,
    "IfcSectionTypeEnum"s,
    "UNIFORM"s,
    "TAPERED"s,
    "IfcSectionalAreaIntegralMeasure"s,
    "IfcSensorTypeEnum"s,
    "COSENSOR"s,
    "CO2SENSOR"s,
    "CONDUCTANCESENSOR"s,
    "CONTACTSENSOR"s,
    "FIRESENSOR"s,
    "FLOWSENSOR"s,
    "FROSTSENSOR"s,
    "GASSENSOR"s,
    "HEATSENSOR"s,
    "HUMIDITYSENSOR"s,
    "IDENTIFIERSENSOR"s,
    "IONCONCENTRATIONSENSOR"s,
    "LEVELSENSOR"s,
    "LIGHTSENSOR"s,
    "MOISTURESENSOR"s,
    "MOVEMENTSENSOR"s,
    "PHSENSOR"s,
    "PRESSURESENSOR"s,
    "RADIATIONSENSOR"s,
    "RADIOACTIVITYSENSOR"s,
    "SMOKESENSOR"s,
    "SOUNDSENSOR"s,
    "TEMPERATURESENSOR"s,
    "WINDSENSOR"s,
    "IfcSequenceEnum"s,
    "START_START"s,
    "START_FINISH"s,
    "FINISH_START"s,
    "FINISH_FINISH"s,
    "IfcShadingDeviceTypeEnum"s,
    "JALOUSIE"s,
    "SHUTTER"s,
    "AWNING"s,
    "IfcShearModulusMeasure"s,
    "IfcSimplePropertyTemplateTypeEnum"s,
    "P_SINGLEVALUE"s,
    "P_ENUMERATEDVALUE"s,
    "P_BOUNDEDVALUE"s,
    "P_LISTVALUE"s,
    "P_TABLEVALUE"s,
    "P_REFERENCEVALUE"s,
    "Q_LENGTH"s,
    "Q_AREA"s,
    "Q_VOLUME"s,
    "Q_COUNT"s,
    "Q_WEIGHT"s,
    "Q_TIME"s,
    "IfcSlabTypeEnum"s,
    "FLOOR"s,
    "ROOF"s,
    "LANDING"s,
    "BASESLAB"s,
    "IfcSolarDeviceTypeEnum"s,
    "SOLARCOLLECTOR"s,
    "SOLARPANEL"s,
    "IfcSolidAngleMeasure"s,
    "IfcSoundPowerLevelMeasure"s,
    "IfcSoundPowerMeasure"s,
    "IfcSoundPressureLevelMeasure"s,
    "IfcSoundPressureMeasure"s,
    "IfcSpaceHeaterTypeEnum"s,
    "CONVECTOR"s,
    "RADIATOR"s,
    "IfcSpaceTypeEnum"s,
    "SPACE"s,
    "PARKING"s,
    "GFA"s,
    "IfcSpatialZoneTypeEnum"s,
    "CONSTRUCTION"s,
    "FIRESAFETY"s,
    "OCCUPANCY"s,
    "IfcSpecificHeatCapacityMeasure"s,
    "IfcSpecularExponent"s,
    "IfcSpecularRoughness"s,
    "IfcStackTerminalTypeEnum"s,
    "BIRDCAGE"s,
    "COWL"s,
    "RAINWATERHOPPER"s,
    "IfcStairFlightTypeEnum"s,
    "WINDER"s,
    "CURVED"s,
    "IfcStairTypeEnum"s,
    "STRAIGHT_RUN_STAIR"s,
    "TWO_STRAIGHT_RUN_STAIR"s,
    "QUARTER_WINDING_STAIR"s,
    "QUARTER_TURN_STAIR"s,
    "HALF_WINDING_STAIR"s,
    "HALF_TURN_STAIR"s,
    "TWO_QUARTER_WINDING_STAIR"s,
    "TWO_QUARTER_TURN_STAIR"s,
    "THREE_QUARTER_WINDING_STAIR"s,
    "THREE_QUARTER_TURN_STAIR"s,
    "SPIRAL_STAIR"s,
    "DOUBLE_RETURN_STAIR"s,
    "CURVED_RUN_STAIR"s,
    "TWO_CURVED_RUN_STAIR"s,
    "IfcStateEnum"s,
    "READWRITE"s,
    "READONLY"s,
    "LOCKED"s,
    "READWRITELOCKED"s,
    "READONLYLOCKED"s,
    "IfcStructuralCurveActivityTypeEnum"s,
    "CONST"s,
    "POLYGONAL"s,
    "EQUIDISTANT"s,
    "SINUS"s,
    "PARABOLA"s,
    "DISCRETE"s,
    "IfcStructuralCurveMemberTypeEnum"s,
    "RIGID_JOINED_MEMBER"s,
    "PIN_JOINED_MEMBER"s,
    "TENSION_MEMBER"s,
    "COMPRESSION_MEMBER"s,
    "IfcStructuralSurfaceActivityTypeEnum"s,
    "BILINEAR"s,
    "ISOCONTOUR"s,
    "IfcStructuralSurfaceMemberTypeEnum"s,
    "BENDING_ELEMENT"s,
    "MEMBRANE_ELEMENT"s,
    "SHELL"s,
    "IfcSubContractResourceTypeEnum"s,
    "PURCHASE"s,
    "IfcSurfaceFeatureTypeEnum"s,
    "MARK"s,
    "TAG"s,
    "TREATMENT"s,
    "IfcSurfaceSide"s,
    "BOTH"s,
    "IfcSwitchingDeviceTypeEnum"s,
    "CONTACTOR"s,
    "DIMMERSWITCH"s,
    "EMERGENCYSTOP"s,
    "KEYPAD"s,
    "MOMENTARYSWITCH"s,
    "SELECTORSWITCH"s,
    "STARTER"s,
    "SWITCHDISCONNECTOR"s,
    "TOGGLESWITCH"s,
    "IfcSystemFurnitureElementTypeEnum"s,
    "PANEL"s,
    "WORKSURFACE"s,
    "IfcTankTypeEnum"s,
    "BASIN"s,
    "BREAKPRESSURE"s,
    "EXPANSION"s,
    "FEEDANDEXPANSION"s,
    "PRESSUREVESSEL"s,
    "STORAGE"s,
    "VESSEL"s,
    "IfcTaskDurationEnum"s,
    "ELAPSEDTIME"s,
    "WORKTIME"s,
    "IfcTaskTypeEnum"s,
    "ATTENDANCE"s,
    "DEMOLITION"s,
    "DISMANTLE"s,
    "INSTALLATION"s,
    "LOGISTIC"s,
    "MAINTENANCE"s,
    "MOVE"s,
    "OPERATION"s,
    "REMOVAL"s,
    "RENOVATION"s,
    "IfcTemperatureGradientMeasure"s,
    "IfcTemperatureRateOfChangeMeasure"s,
    "IfcTendonAnchorTypeEnum"s,
    "COUPLER"s,
    "FIXED_END"s,
    "TENSIONING_END"s,
    "IfcTendonTypeEnum"s,
    "BAR"s,
    "COATED"s,
    "STRAND"s,
    "WIRE"s,
    "IfcText"s,
    "IfcTextAlignment"s,
    "IfcTextDecoration"s,
    "IfcTextFontName"s,
    "IfcTextPath"s,
    "UP"s,
    "DOWN"s,
    "IfcTextTransformation"s,
    "IfcThermalAdmittanceMeasure"s,
    "IfcThermalConductivityMeasure"s,
    "IfcThermalExpansionCoefficientMeasure"s,
    "IfcThermalResistanceMeasure"s,
    "IfcThermalTransmittanceMeasure"s,
    "IfcThermodynamicTemperatureMeasure"s,
    "IfcTime"s,
    "IfcTimeMeasure"s,
    "IfcTimeOrRatioSelect"s,
    "IfcTimeSeriesDataTypeEnum"s,
    "CONTINUOUS"s,
    "DISCRETEBINARY"s,
    "PIECEWISEBINARY"s,
    "PIECEWISECONSTANT"s,
    "PIECEWISECONTINUOUS"s,
    "IfcTimeStamp"s,
    "IfcTorqueMeasure"s,
    "IfcTransformerTypeEnum"s,
    "FREQUENCY"s,
    "INVERTER"s,
    "RECTIFIER"s,
    "VOLTAGE"s,
    "IfcTransitionCode"s,
    "DISCONTINUOUS"s,
    "CONTSAMEGRADIENT"s,
    "CONTSAMEGRADIENTSAMECURVATURE"s,
    "IfcTranslationalStiffnessSelect"s,
    "IfcTransportElementTypeEnum"s,
    "ELEVATOR"s,
    "ESCALATOR"s,
    "MOVINGWALKWAY"s,
    "CRANEWAY"s,
    "LIFTINGGEAR"s,
    "IfcTrimmingPreference"s,
    "CARTESIAN"s,
    "IfcTubeBundleTypeEnum"s,
    "FINNED"s,
    "IfcURIReference"s,
    "IfcUnitEnum"s,
    "ABSORBEDDOSEUNIT"s,
    "AMOUNTOFSUBSTANCEUNIT"s,
    "AREAUNIT"s,
    "DOSEEQUIVALENTUNIT"s,
    "ELECTRICCAPACITANCEUNIT"s,
    "ELECTRICCHARGEUNIT"s,
    "ELECTRICCONDUCTANCEUNIT"s,
    "ELECTRICCURRENTUNIT"s,
    "ELECTRICRESISTANCEUNIT"s,
    "ELECTRICVOLTAGEUNIT"s,
    "ENERGYUNIT"s,
    "FORCEUNIT"s,
    "FREQUENCYUNIT"s,
    "ILLUMINANCEUNIT"s,
    "INDUCTANCEUNIT"s,
    "LENGTHUNIT"s,
    "LUMINOUSFLUXUNIT"s,
    "LUMINOUSINTENSITYUNIT"s,
    "MAGNETICFLUXDENSITYUNIT"s,
    "MAGNETICFLUXUNIT"s,
    "MASSUNIT"s,
    "PLANEANGLEUNIT"s,
    "POWERUNIT"s,
    "PRESSUREUNIT"s,
    "RADIOACTIVITYUNIT"s,
    "SOLIDANGLEUNIT"s,
    "THERMODYNAMICTEMPERATUREUNIT"s,
    "TIMEUNIT"s,
    "VOLUMEUNIT"s,
    "IfcUnitaryControlElementTypeEnum"s,
    "ALARMPANEL"s,
    "CONTROLPANEL"s,
    "GASDETECTIONPANEL"s,
    "INDICATORPANEL"s,
    "MIMICPANEL"s,
    "HUMIDISTAT"s,
    "THERMOSTAT"s,
    "WEATHERSTATION"s,
    "IfcUnitaryEquipmentTypeEnum"s,
    "AIRHANDLER"s,
    "AIRCONDITIONINGUNIT"s,
    "DEHUMIDIFIER"s,
    "SPLITSYSTEM"s,
    "ROOFTOPUNIT"s,
    "IfcValveTypeEnum"s,
    "AIRRELEASE"s,
    "ANTIVACUUM"s,
    "CHANGEOVER"s,
    "CHECK"s,
    "COMMISSIONING"s,
    "DIVERTING"s,
    "DRAWOFFCOCK"s,
    "DOUBLECHECK"s,
    "DOUBLEREGULATING"s,
    "FAUCET"s,
    "FLUSHING"s,
    "GASCOCK"s,
    "GASTAP"s,
    "ISOLATING"s,
    "MIXING"s,
    "PRESSUREREDUCING"s,
    "PRESSURERELIEF"s,
    "REGULATING"s,
    "SAFETYCUTOFF"s,
    "STEAMTRAP"s,
    "STOPCOCK"s,
    "IfcVaporPermeabilityMeasure"s,
    "IfcVibrationIsolatorTypeEnum"s,
    "COMPRESSION"s,
    "SPRING"s,
    "IfcVoidingFeatureTypeEnum"s,
    "CUTOUT"s,
    "NOTCH"s,
    "HOLE"s,
    "MITER"s,
    "CHAMFER"s,
    "IfcVolumeMeasure"s,
    "IfcVolumetricFlowRateMeasure"s,
    "IfcWallTypeEnum"s,
    "MOVABLE"s,
    "PARAPET"s,
    "PARTITIONING"s,
    "PLUMBINGWALL"s,
    "SOLIDWALL"s,
    "STANDARD"s,
    "ELEMENTEDWALL"s,
    "IfcWarpingConstantMeasure"s,
    "IfcWarpingMomentMeasure"s,
    "IfcWarpingStiffnessSelect"s,
    "IfcWasteTerminalTypeEnum"s,
    "FLOORTRAP"s,
    "FLOORWASTE"s,
    "GULLYSUMP"s,
    "GULLYTRAP"s,
    "ROOFDRAIN"s,
    "WASTEDISPOSALUNIT"s,
    "WASTETRAP"s,
    "IfcWindowPanelOperationEnum"s,
    "SIDEHUNGRIGHTHAND"s,
    "SIDEHUNGLEFTHAND"s,
    "TILTANDTURNRIGHTHAND"s,
    "TILTANDTURNLEFTHAND"s,
    "TOPHUNG"s,
    "BOTTOMHUNG"s,
    "PIVOTHORIZONTAL"s,
    "PIVOTVERTICAL"s,
    "SLIDINGHORIZONTAL"s,
    "SLIDINGVERTICAL"s,
    "REMOVABLECASEMENT"s,
    "FIXEDCASEMENT"s,
    "OTHEROPERATION"s,
    "IfcWindowPanelPositionEnum"s,
    "BOTTOM"s,
    "TOP"s,
    "IfcWindowStyleConstructionEnum"s,
    "OTHER_CONSTRUCTION"s,
    "IfcWindowStyleOperationEnum"s,
    "SINGLE_PANEL"s,
    "DOUBLE_PANEL_VERTICAL"s,
    "DOUBLE_PANEL_HORIZONTAL"s,
    "TRIPLE_PANEL_VERTICAL"s,
    "TRIPLE_PANEL_BOTTOM"s,
    "TRIPLE_PANEL_TOP"s,
    "TRIPLE_PANEL_LEFT"s,
    "TRIPLE_PANEL_RIGHT"s,
    "TRIPLE_PANEL_HORIZONTAL"s,
    "IfcWindowTypeEnum"s,
    "WINDOW"s,
    "SKYLIGHT"s,
    "LIGHTDOME"s,
    "IfcWindowTypePartitioningEnum"s,
    "IfcWorkCalendarTypeEnum"s,
    "FIRSTSHIFT"s,
    "SECONDSHIFT"s,
    "THIRDSHIFT"s,
    "IfcWorkPlanTypeEnum"s,
    "ACTUAL"s,
    "BASELINE"s,
    "PLANNED"s,
    "IfcWorkScheduleTypeEnum"s,
    "IfcActorRole"s,
    "IfcAddress"s,
    "IfcApplication"s,
    "IfcAppliedValue"s,
    "IfcApproval"s,
    "IfcBoundaryCondition"s,
    "IfcBoundaryEdgeCondition"s,
    "IfcBoundaryFaceCondition"s,
    "IfcBoundaryNodeCondition"s,
    "IfcBoundaryNodeConditionWarping"s,
    "IfcConnectionGeometry"s,
    "IfcConnectionPointGeometry"s,
    "IfcConnectionSurfaceGeometry"s,
    "IfcConnectionVolumeGeometry"s,
    "IfcConstraint"s,
    "IfcCoordinateOperation"s,
    "IfcCoordinateReferenceSystem"s,
    "IfcCostValue"s,
    "IfcDerivedUnit"s,
    "IfcDerivedUnitElement"s,
    "IfcDimensionalExponents"s,
    "IfcExternalInformation"s,
    "IfcExternalReference"s,
    "IfcExternallyDefinedHatchStyle"s,
    "IfcExternallyDefinedSurfaceStyle"s,
    "IfcExternallyDefinedTextFont"s,
    "IfcGridAxis"s,
    "IfcIrregularTimeSeriesValue"s,
    "IfcLibraryInformation"s,
    "IfcLibraryReference"s,
    "IfcLightDistributionData"s,
    "IfcLightIntensityDistribution"s,
    "IfcMapConversion"s,
    "IfcMaterialClassificationRelationship"s,
    "IfcMaterialDefinition"s,
    "IfcMaterialLayer"s,
    "IfcMaterialLayerSet"s,
    "IfcMaterialLayerWithOffsets"s,
    "IfcMaterialList"s,
    "IfcMaterialProfile"s,
    "IfcMaterialProfileSet"s,
    "IfcMaterialProfileWithOffsets"s,
    "IfcMaterialUsageDefinition"s,
    "IfcMeasureWithUnit"s,
    "IfcMetric"s,
    "IfcMonetaryUnit"s,
    "IfcNamedUnit"s,
    "IfcObjectPlacement"s,
    "IfcObjective"s,
    "IfcOrganization"s,
    "IfcOwnerHistory"s,
    "IfcPerson"s,
    "IfcPersonAndOrganization"s,
    "IfcPhysicalQuantity"s,
    "IfcPhysicalSimpleQuantity"s,
    "IfcPostalAddress"s,
    "IfcPresentationItem"s,
    "IfcPresentationLayerAssignment"s,
    "IfcPresentationLayerWithStyle"s,
    "IfcPresentationStyle"s,
    "IfcPresentationStyleAssignment"s,
    "IfcProductRepresentation"s,
    "IfcProfileDef"s,
    "IfcProjectedCRS"s,
    "IfcPropertyAbstraction"s,
    "IfcPropertyEnumeration"s,
    "IfcQuantityArea"s,
    "IfcQuantityCount"s,
    "IfcQuantityLength"s,
    "IfcQuantityTime"s,
    "IfcQuantityVolume"s,
    "IfcQuantityWeight"s,
    "IfcRecurrencePattern"s,
    "IfcReference"s,
    "IfcRepresentation"s,
    "IfcRepresentationContext"s,
    "IfcRepresentationItem"s,
    "IfcRepresentationMap"s,
    "IfcResourceLevelRelationship"s,
    "IfcRoot"s,
    "IfcSIUnit"s,
    "IfcSchedulingTime"s,
    "IfcShapeAspect"s,
    "IfcShapeModel"s,
    "IfcShapeRepresentation"s,
    "IfcStructuralConnectionCondition"s,
    "IfcStructuralLoad"s,
    "IfcStructuralLoadConfiguration"s,
    "IfcStructuralLoadOrResult"s,
    "IfcStructuralLoadStatic"s,
    "IfcStructuralLoadTemperature"s,
    "IfcStyleModel"s,
    "IfcStyledItem"s,
    "IfcStyledRepresentation"s,
    "IfcSurfaceReinforcementArea"s,
    "IfcSurfaceStyle"s,
    "IfcSurfaceStyleLighting"s,
    "IfcSurfaceStyleRefraction"s,
    "IfcSurfaceStyleShading"s,
    "IfcSurfaceStyleWithTextures"s,
    "IfcSurfaceTexture"s,
    "IfcTable"s,
    "IfcTableColumn"s,
    "IfcTableRow"s,
    "IfcTaskTime"s,
    "IfcTaskTimeRecurring"s,
    "IfcTelecomAddress"s,
    "IfcTextStyle"s,
    "IfcTextStyleForDefinedFont"s,
    "IfcTextStyleTextModel"s,
    "IfcTextureCoordinate"s,
    "IfcTextureCoordinateGenerator"s,
    "IfcTextureMap"s,
    "IfcTextureVertex"s,
    "IfcTextureVertexList"s,
    "IfcTimePeriod"s,
    "IfcTimeSeries"s,
    "IfcTimeSeriesValue"s,
    "IfcTopologicalRepresentationItem"s,
    "IfcTopologyRepresentation"s,
    "IfcUnitAssignment"s,
    "IfcVertex"s,
    "IfcVertexPoint"s,
    "IfcVirtualGridIntersection"s,
    "IfcWorkTime"s,
    "IfcActorSelect"s,
    "IfcArcIndex"s,
    "IfcBendingParameterSelect"s,
    "IfcBoxAlignment"s,
    "IfcDerivedMeasureValue"s,
    "IfcLayeredItem"s,
    "IfcLibrarySelect"s,
    "IfcLightDistributionDataSourceSelect"s,
    "IfcLineIndex"s,
    "IfcMaterialSelect"s,
    "IfcNormalisedRatioMeasure"s,
    "IfcObjectReferenceSelect"s,
    "IfcPositiveRatioMeasure"s,
    "IfcSegmentIndexSelect"s,
    "IfcSimpleValue"s,
    "IfcSizeSelect"s,
    "IfcSpecularHighlightSelect"s,
    "IfcStyleAssignmentSelect"s,
    "IfcSurfaceStyleElementSelect"s,
    "IfcUnit"s,
    "IfcApprovalRelationship"s,
    "IfcArbitraryClosedProfileDef"s,
    "IfcArbitraryOpenProfileDef"s,
    "IfcArbitraryProfileDefWithVoids"s,
    "IfcBlobTexture"s,
    "IfcCenterLineProfileDef"s,
    "IfcClassification"s,
    "IfcClassificationReference"s,
    "IfcColourRgbList"s,
    "IfcColourSpecification"s,
    "IfcCompositeProfileDef"s,
    "IfcConnectedFaceSet"s,
    "IfcConnectionCurveGeometry"s,
    "IfcConnectionPointEccentricity"s,
    "IfcContextDependentUnit"s,
    "IfcConversionBasedUnit"s,
    "IfcConversionBasedUnitWithOffset"s,
    "IfcCurrencyRelationship"s,
    "IfcCurveStyle"s,
    "IfcCurveStyleFont"s,
    "IfcCurveStyleFontAndScaling"s,
    "IfcCurveStyleFontPattern"s,
    "IfcDerivedProfileDef"s,
    "IfcDocumentInformation"s,
    "IfcDocumentInformationRelationship"s,
    "IfcDocumentReference"s,
    "IfcEdge"s,
    "IfcEdgeCurve"s,
    "IfcEventTime"s,
    "IfcExtendedProperties"s,
    "IfcExternalReferenceRelationship"s,
    "IfcFace"s,
    "IfcFaceBound"s,
    "IfcFaceOuterBound"s,
    "IfcFaceSurface"s,
    "IfcFailureConnectionCondition"s,
    "IfcFillAreaStyle"s,
    "IfcGeometricRepresentationContext"s,
    "IfcGeometricRepresentationItem"s,
    "IfcGeometricRepresentationSubContext"s,
    "IfcGeometricSet"s,
    "IfcGridPlacement"s,
    "IfcHalfSpaceSolid"s,
    "IfcImageTexture"s,
    "IfcIndexedColourMap"s,
    "IfcIndexedTextureMap"s,
    "IfcIndexedTriangleTextureMap"s,
    "IfcIrregularTimeSeries"s,
    "IfcLagTime"s,
    "IfcLightSource"s,
    "IfcLightSourceAmbient"s,
    "IfcLightSourceDirectional"s,
    "IfcLightSourceGoniometric"s,
    "IfcLightSourcePositional"s,
    "IfcLightSourceSpot"s,
    "IfcLocalPlacement"s,
    "IfcLoop"s,
    "IfcMappedItem"s,
    "IfcMaterial"s,
    "IfcMaterialConstituent"s,
    "IfcMaterialConstituentSet"s,
    "IfcMaterialDefinitionRepresentation"s,
    "IfcMaterialLayerSetUsage"s,
    "IfcMaterialProfileSetUsage"s,
    "IfcMaterialProfileSetUsageTapering"s,
    "IfcMaterialProperties"s,
    "IfcMaterialRelationship"s,
    "IfcMirroredProfileDef"s,
    "IfcObjectDefinition"s,
    "IfcOpenShell"s,
    "IfcOrganizationRelationship"s,
    "IfcOrientedEdge"s,
    "IfcParameterizedProfileDef"s,
    "IfcPath"s,
    "IfcPhysicalComplexQuantity"s,
    "IfcPixelTexture"s,
    "IfcPlacement"s,
    "IfcPlanarExtent"s,
    "IfcPoint"s,
    "IfcPointOnCurve"s,
    "IfcPointOnSurface"s,
    "IfcPolyLoop"s,
    "IfcPolygonalBoundedHalfSpace"s,
    "IfcPreDefinedItem"s,
    "IfcPreDefinedProperties"s,
    "IfcPreDefinedTextFont"s,
    "IfcProductDefinitionShape"s,
    "IfcProfileProperties"s,
    "IfcProperty"s,
    "IfcPropertyDefinition"s,
    "IfcPropertyDependencyRelationship"s,
    "IfcPropertySetDefinition"s,
    "IfcPropertyTemplateDefinition"s,
    "IfcQuantitySet"s,
    "IfcRectangleProfileDef"s,
    "IfcRegularTimeSeries"s,
    "IfcReinforcementBarProperties"s,
    "IfcRelationship"s,
    "IfcResourceApprovalRelationship"s,
    "IfcResourceConstraintRelationship"s,
    "IfcResourceTime"s,
    "IfcRoundedRectangleProfileDef"s,
    "IfcSectionProperties"s,
    "IfcSectionReinforcementProperties"s,
    "IfcSectionedSpine"s,
    "IfcShellBasedSurfaceModel"s,
    "IfcSimpleProperty"s,
    "IfcSlippageConnectionCondition"s,
    "IfcSolidModel"s,
    "IfcStructuralLoadLinearForce"s,
    "IfcStructuralLoadPlanarForce"s,
    "IfcStructuralLoadSingleDisplacement"s,
    "IfcStructuralLoadSingleDisplacementDistortion"s,
    "IfcStructuralLoadSingleForce"s,
    "IfcStructuralLoadSingleForceWarping"s,
    "IfcSubedge"s,
    "IfcSurface"s,
    "IfcSurfaceStyleRendering"s,
    "IfcSweptAreaSolid"s,
    "IfcSweptDiskSolid"s,
    "IfcSweptDiskSolidPolygonal"s,
    "IfcSweptSurface"s,
    "IfcTShapeProfileDef"s,
    "IfcTessellatedItem"s,
    "IfcTextLiteral"s,
    "IfcTextLiteralWithExtent"s,
    "IfcTextStyleFontModel"s,
    "IfcTrapeziumProfileDef"s,
    "IfcTypeObject"s,
    "IfcTypeProcess"s,
    "IfcTypeProduct"s,
    "IfcTypeResource"s,
    "IfcUShapeProfileDef"s,
    "IfcVector"s,
    "IfcVertexLoop"s,
    "IfcWindowStyle"s,
    "IfcZShapeProfileDef"s,
    "IfcClassificationReferenceSelect"s,
    "IfcClassificationSelect"s,
    "IfcCoordinateReferenceSystemSelect"s,
    "IfcDefinitionSelect"s,
    "IfcDocumentSelect"s,
    "IfcHatchLineDistanceSelect"s,
    "IfcMeasureValue"s,
    "IfcPointOrVertexPoint"s,
    "IfcPresentationStyleSelect"s,
    "IfcProductRepresentationSelect"s,
    "IfcPropertySetDefinitionSet"s,
    "IfcResourceObjectSelect"s,
    "IfcTextFontSelect"s,
    "IfcValue"s,
    "IfcAdvancedFace"s,
    "IfcAnnotationFillArea"s,
    "IfcAsymmetricIShapeProfileDef"s,
    "IfcAxis1Placement"s,
    "IfcAxis2Placement2D"s,
    "IfcAxis2Placement3D"s,
    "IfcBooleanResult"s,
    "IfcBoundedSurface"s,
    "IfcBoundingBox"s,
    "IfcBoxedHalfSpace"s,
    "IfcCShapeProfileDef"s,
    "IfcCartesianPoint"s,
    "IfcCartesianPointList"s,
    "IfcCartesianPointList2D"s,
    "IfcCartesianPointList3D"s,
    "IfcCartesianTransformationOperator"s,
    "IfcCartesianTransformationOperator2D"s,
    "IfcCartesianTransformationOperator2DnonUniform"s,
    "IfcCartesianTransformationOperator3D"s,
    "IfcCartesianTransformationOperator3DnonUniform"s,
    "IfcCircleProfileDef"s,
    "IfcClosedShell"s,
    "IfcColourRgb"s,
    "IfcComplexProperty"s,
    "IfcCompositeCurveSegment"s,
    "IfcConstructionResourceType"s,
    "IfcContext"s,
    "IfcCrewResourceType"s,
    "IfcCsgPrimitive3D"s,
    "IfcCsgSolid"s,
    "IfcCurve"s,
    "IfcCurveBoundedPlane"s,
    "IfcCurveBoundedSurface"s,
    "IfcDirection"s,
    "IfcDoorStyle"s,
    "IfcEdgeLoop"s,
    "IfcElementQuantity"s,
    "IfcElementType"s,
    "IfcElementarySurface"s,
    "IfcEllipseProfileDef"s,
    "IfcEventType"s,
    "IfcExtrudedAreaSolid"s,
    "IfcExtrudedAreaSolidTapered"s,
    "IfcFaceBasedSurfaceModel"s,
    "IfcFillAreaStyleHatching"s,
    "IfcFillAreaStyleTiles"s,
    "IfcFixedReferenceSweptAreaSolid"s,
    "IfcFurnishingElementType"s,
    "IfcFurnitureType"s,
    "IfcGeographicElementType"s,
    "IfcGeometricCurveSet"s,
    "IfcIShapeProfileDef"s,
    "IfcIndexedPolygonalFace"s,
    "IfcIndexedPolygonalFaceWithVoids"s,
    "IfcLShapeProfileDef"s,
    "IfcLaborResourceType"s,
    "IfcLine"s,
    "IfcManifoldSolidBrep"s,
    "IfcObject"s,
    "IfcOffsetCurve2D"s,
    "IfcOffsetCurve3D"s,
    "IfcPcurve"s,
    "IfcPlanarBox"s,
    "IfcPlane"s,
    "IfcPreDefinedColour"s,
    "IfcPreDefinedCurveFont"s,
    "IfcPreDefinedPropertySet"s,
    "IfcProcedureType"s,
    "IfcProcess"s,
    "IfcProduct"s,
    "IfcProject"s,
    "IfcProjectLibrary"s,
    "IfcPropertyBoundedValue"s,
    "IfcPropertyEnumeratedValue"s,
    "IfcPropertyListValue"s,
    "IfcPropertyReferenceValue"s,
    "IfcPropertySet"s,
    "IfcPropertySetTemplate"s,
    "IfcPropertySingleValue"s,
    "IfcPropertyTableValue"s,
    "IfcPropertyTemplate"s,
    "IfcProxy"s,
    "IfcRectangleHollowProfileDef"s,
    "IfcRectangularPyramid"s,
    "IfcRectangularTrimmedSurface"s,
    "IfcReinforcementDefinitionProperties"s,
    "IfcRelAssigns"s,
    "IfcRelAssignsToActor"s,
    "IfcRelAssignsToControl"s,
    "IfcRelAssignsToGroup"s,
    "IfcRelAssignsToGroupByFactor"s,
    "IfcRelAssignsToProcess"s,
    "IfcRelAssignsToProduct"s,
    "IfcRelAssignsToResource"s,
    "IfcRelAssociates"s,
    "IfcRelAssociatesApproval"s,
    "IfcRelAssociatesClassification"s,
    "IfcRelAssociatesConstraint"s,
    "IfcRelAssociatesDocument"s,
    "IfcRelAssociatesLibrary"s,
    "IfcRelAssociatesMaterial"s,
    "IfcRelConnects"s,
    "IfcRelConnectsElements"s,
    "IfcRelConnectsPathElements"s,
    "IfcRelConnectsPortToElement"s,
    "IfcRelConnectsPorts"s,
    "IfcRelConnectsStructuralActivity"s,
    "IfcRelConnectsStructuralMember"s,
    "IfcRelConnectsWithEccentricity"s,
    "IfcRelConnectsWithRealizingElements"s,
    "IfcRelContainedInSpatialStructure"s,
    "IfcRelCoversBldgElements"s,
    "IfcRelCoversSpaces"s,
    "IfcRelDeclares"s,
    "IfcRelDecomposes"s,
    "IfcRelDefines"s,
    "IfcRelDefinesByObject"s,
    "IfcRelDefinesByProperties"s,
    "IfcRelDefinesByTemplate"s,
    "IfcRelDefinesByType"s,
    "IfcRelFillsElement"s,
    "IfcRelFlowControlElements"s,
    "IfcRelInterferesElements"s,
    "IfcRelNests"s,
    "IfcRelProjectsElement"s,
    "IfcRelReferencedInSpatialStructure"s,
    "IfcRelSequence"s,
    "IfcRelServicesBuildings"s,
    "IfcRelSpaceBoundary"s,
    "IfcRelSpaceBoundary1stLevel"s,
    "IfcRelSpaceBoundary2ndLevel"s,
    "IfcRelVoidsElement"s,
    "IfcReparametrisedCompositeCurveSegment"s,
    "IfcResource"s,
    "IfcRevolvedAreaSolid"s,
    "IfcRevolvedAreaSolidTapered"s,
    "IfcRightCircularCone"s,
    "IfcRightCircularCylinder"s,
    "IfcSimplePropertyTemplate"s,
    "IfcSpatialElement"s,
    "IfcSpatialElementType"s,
    "IfcSpatialStructureElement"s,
    "IfcSpatialStructureElementType"s,
    "IfcSpatialZone"s,
    "IfcSpatialZoneType"s,
    "IfcSphere"s,
    "IfcSphericalSurface"s,
    "IfcStructuralActivity"s,
    "IfcStructuralItem"s,
    "IfcStructuralMember"s,
    "IfcStructuralReaction"s,
    "IfcStructuralSurfaceMember"s,
    "IfcStructuralSurfaceMemberVarying"s,
    "IfcStructuralSurfaceReaction"s,
    "IfcSubContractResourceType"s,
    "IfcSurfaceCurve"s,
    "IfcSurfaceCurveSweptAreaSolid"s,
    "IfcSurfaceOfLinearExtrusion"s,
    "IfcSurfaceOfRevolution"s,
    "IfcSystemFurnitureElementType"s,
    "IfcTask"s,
    "IfcTaskType"s,
    "IfcTessellatedFaceSet"s,
    "IfcToroidalSurface"s,
    "IfcTransportElementType"s,
    "IfcTriangulatedFaceSet"s,
    "IfcWindowLiningProperties"s,
    "IfcWindowPanelProperties"s,
    "IfcAppliedValueSelect"s,
    "IfcAxis2Placement"s,
    "IfcBooleanOperand"s,
    "IfcColour"s,
    "IfcColourOrFactor"s,
    "IfcCsgSelect"s,
    "IfcCurveStyleFontSelect"s,
    "IfcFillStyleSelect"s,
    "IfcGeometricSetSelect"s,
    "IfcGridPlacementDirectionSelect"s,
    "IfcMetricValueSelect"s,
    "IfcProcessSelect"s,
    "IfcProductSelect"s,
    "IfcPropertySetDefinitionSelect"s,
    "IfcResourceSelect"s,
    "IfcShell"s,
    "IfcSolidOrShell"s,
    "IfcSurfaceOrFaceSurface"s,
    "IfcTrimmingSelect"s,
    "IfcVectorOrDirection"s,
    "IfcActor"s,
    "IfcAdvancedBrep"s,
    "IfcAdvancedBrepWithVoids"s,
    "IfcAnnotation"s,
    "IfcBSplineSurface"s,
    "IfcBSplineSurfaceWithKnots"s,
    "IfcBlock"s,
    "IfcBooleanClippingResult"s,
    "IfcBoundedCurve"s,
    "IfcBuilding"s,
    "IfcBuildingElementType"s,
    "IfcBuildingStorey"s,
    "IfcChimneyType"s,
    "IfcCircleHollowProfileDef"s,
    "IfcCivilElementType"s,
    "IfcColumnType"s,
    "IfcComplexPropertyTemplate"s,
    "IfcCompositeCurve"s,
    "IfcCompositeCurveOnSurface"s,
    "IfcConic"s,
    "IfcConstructionEquipmentResourceType"s,
    "IfcConstructionMaterialResourceType"s,
    "IfcConstructionProductResourceType"s,
    "IfcConstructionResource"s,
    "IfcControl"s,
    "IfcCostItem"s,
    "IfcCostSchedule"s,
    "IfcCoveringType"s,
    "IfcCrewResource"s,
    "IfcCurtainWallType"s,
    "IfcCylindricalSurface"s,
    "IfcDistributionElementType"s,
    "IfcDistributionFlowElementType"s,
    "IfcDoorLiningProperties"s,
    "IfcDoorPanelProperties"s,
    "IfcDoorType"s,
    "IfcDraughtingPreDefinedColour"s,
    "IfcDraughtingPreDefinedCurveFont"s,
    "IfcElement"s,
    "IfcElementAssembly"s,
    "IfcElementAssemblyType"s,
    "IfcElementComponent"s,
    "IfcElementComponentType"s,
    "IfcEllipse"s,
    "IfcEnergyConversionDeviceType"s,
    "IfcEngineType"s,
    "IfcEvaporativeCoolerType"s,
    "IfcEvaporatorType"s,
    "IfcEvent"s,
    "IfcExternalSpatialStructureElement"s,
    "IfcFacetedBrep"s,
    "IfcFacetedBrepWithVoids"s,
    "IfcFastener"s,
    "IfcFastenerType"s,
    "IfcFeatureElement"s,
    "IfcFeatureElementAddition"s,
    "IfcFeatureElementSubtraction"s,
    "IfcFlowControllerType"s,
    "IfcFlowFittingType"s,
    "IfcFlowMeterType"s,
    "IfcFlowMovingDeviceType"s,
    "IfcFlowSegmentType"s,
    "IfcFlowStorageDeviceType"s,
    "IfcFlowTerminalType"s,
    "IfcFlowTreatmentDeviceType"s,
    "IfcFootingType"s,
    "IfcFurnishingElement"s,
    "IfcFurniture"s,
    "IfcGeographicElement"s,
    "IfcGrid"s,
    "IfcGroup"s,
    "IfcHeatExchangerType"s,
    "IfcHumidifierType"s,
    "IfcIndexedPolyCurve"s,
    "IfcInterceptorType"s,
    "IfcIntersectionCurve"s,
    "IfcInventory"s,
    "IfcJunctionBoxType"s,
    "IfcLaborResource"s,
    "IfcLampType"s,
    "IfcLightFixtureType"s,
    "IfcMechanicalFastener"s,
    "IfcMechanicalFastenerType"s,
    "IfcMedicalDeviceType"s,
    "IfcMemberType"s,
    "IfcMotorConnectionType"s,
    "IfcOccupant"s,
    "IfcOpeningElement"s,
    "IfcOpeningStandardCase"s,
    "IfcOutletType"s,
    "IfcPerformanceHistory"s,
    "IfcPermeableCoveringProperties"s,
    "IfcPermit"s,
    "IfcPileType"s,
    "IfcPipeFittingType"s,
    "IfcPipeSegmentType"s,
    "IfcPlateType"s,
    "IfcPolygonalFaceSet"s,
    "IfcPolyline"s,
    "IfcPort"s,
    "IfcProcedure"s,
    "IfcProjectOrder"s,
    "IfcProjectionElement"s,
    "IfcProtectiveDeviceType"s,
    "IfcPumpType"s,
    "IfcRailingType"s,
    "IfcRampFlightType"s,
    "IfcRampType"s,
    "IfcRationalBSplineSurfaceWithKnots"s,
    "IfcReinforcingElement"s,
    "IfcReinforcingElementType"s,
    "IfcReinforcingMesh"s,
    "IfcReinforcingMeshType"s,
    "IfcRelAggregates"s,
    "IfcRoofType"s,
    "IfcSanitaryTerminalType"s,
    "IfcSeamCurve"s,
    "IfcShadingDeviceType"s,
    "IfcSite"s,
    "IfcSlabType"s,
    "IfcSolarDeviceType"s,
    "IfcSpace"s,
    "IfcSpaceHeaterType"s,
    "IfcSpaceType"s,
    "IfcStackTerminalType"s,
    "IfcStairFlightType"s,
    "IfcStairType"s,
    "IfcStructuralAction"s,
    "IfcStructuralConnection"s,
    "IfcStructuralCurveAction"s,
    "IfcStructuralCurveConnection"s,
    "IfcStructuralCurveMember"s,
    "IfcStructuralCurveMemberVarying"s,
    "IfcStructuralCurveReaction"s,
    "IfcStructuralLinearAction"s,
    "IfcStructuralLoadGroup"s,
    "IfcStructuralPointAction"s,
    "IfcStructuralPointConnection"s,
    "IfcStructuralPointReaction"s,
    "IfcStructuralResultGroup"s,
    "IfcStructuralSurfaceAction"s,
    "IfcStructuralSurfaceConnection"s,
    "IfcSubContractResource"s,
    "IfcSurfaceFeature"s,
    "IfcSwitchingDeviceType"s,
    "IfcSystem"s,
    "IfcSystemFurnitureElement"s,
    "IfcTankType"s,
    "IfcTendon"s,
    "IfcTendonAnchor"s,
    "IfcTendonAnchorType"s,
    "IfcTendonType"s,
    "IfcTransformerType"s,
    "IfcTransportElement"s,
    "IfcTrimmedCurve"s,
    "IfcTubeBundleType"s,
    "IfcUnitaryEquipmentType"s,
    "IfcValveType"s,
    "IfcVibrationIsolator"s,
    "IfcVibrationIsolatorType"s,
    "IfcVirtualElement"s,
    "IfcVoidingFeature"s,
    "IfcWallType"s,
    "IfcWasteTerminalType"s,
    "IfcWindowType"s,
    "IfcWorkCalendar"s,
    "IfcWorkControl"s,
    "IfcWorkPlan"s,
    "IfcWorkSchedule"s,
    "IfcZone"s,
    "IfcCurveFontOrScaledCurveFontSelect"s,
    "IfcCurveOnSurface"s,
    "IfcCurveOrEdgeCurve"s,
    "IfcStructuralActivityAssignmentSelect"s,
    "IfcActionRequest"s,
    "IfcAirTerminalBoxType"s,
    "IfcAirTerminalType"s,
    "IfcAirToAirHeatRecoveryType"s,
    "IfcAsset"s,
    "IfcAudioVisualApplianceType"s,
    "IfcBSplineCurve"s,
    "IfcBSplineCurveWithKnots"s,
    "IfcBeamType"s,
    "IfcBoilerType"s,
    "IfcBoundaryCurve"s,
    "IfcBuildingElement"s,
    "IfcBuildingElementPart"s,
    "IfcBuildingElementPartType"s,
    "IfcBuildingElementProxy"s,
    "IfcBuildingElementProxyType"s,
    "IfcBuildingSystem"s,
    "IfcBurnerType"s,
    "IfcCableCarrierFittingType"s,
    "IfcCableCarrierSegmentType"s,
    "IfcCableFittingType"s,
    "IfcCableSegmentType"s,
    "IfcChillerType"s,
    "IfcChimney"s,
    "IfcCircle"s,
    "IfcCivilElement"s,
    "IfcCoilType"s,
    "IfcColumn"s,
    "IfcColumnStandardCase"s,
    "IfcCommunicationsApplianceType"s,
    "IfcCompressorType"s,
    "IfcCondenserType"s,
    "IfcConstructionEquipmentResource"s,
    "IfcConstructionMaterialResource"s,
    "IfcConstructionProductResource"s,
    "IfcCooledBeamType"s,
    "IfcCoolingTowerType"s,
    "IfcCovering"s,
    "IfcCurtainWall"s,
    "IfcDamperType"s,
    "IfcDiscreteAccessory"s,
    "IfcDiscreteAccessoryType"s,
    "IfcDistributionChamberElementType"s,
    "IfcDistributionControlElementType"s,
    "IfcDistributionElement"s,
    "IfcDistributionFlowElement"s,
    "IfcDistributionPort"s,
    "IfcDistributionSystem"s,
    "IfcDoor"s,
    "IfcDoorStandardCase"s,
    "IfcDuctFittingType"s,
    "IfcDuctSegmentType"s,
    "IfcDuctSilencerType"s,
    "IfcElectricApplianceType"s,
    "IfcElectricDistributionBoardType"s,
    "IfcElectricFlowStorageDeviceType"s,
    "IfcElectricGeneratorType"s,
    "IfcElectricMotorType"s,
    "IfcElectricTimeControlType"s,
    "IfcEnergyConversionDevice"s,
    "IfcEngine"s,
    "IfcEvaporativeCooler"s,
    "IfcEvaporator"s,
    "IfcExternalSpatialElement"s,
    "IfcFanType"s,
    "IfcFilterType"s,
    "IfcFireSuppressionTerminalType"s,
    "IfcFlowController"s,
    "IfcFlowFitting"s,
    "IfcFlowInstrumentType"s,
    "IfcFlowMeter"s,
    "IfcFlowMovingDevice"s,
    "IfcFlowSegment"s,
    "IfcFlowStorageDevice"s,
    "IfcFlowTerminal"s,
    "IfcFlowTreatmentDevice"s,
    "IfcFooting"s,
    "IfcHeatExchanger"s,
    "IfcHumidifier"s,
    "IfcInterceptor"s,
    "IfcJunctionBox"s,
    "IfcLamp"s,
    "IfcLightFixture"s,
    "IfcMedicalDevice"s,
    "IfcMember"s,
    "IfcMemberStandardCase"s,
    "IfcMotorConnection"s,
    "IfcOuterBoundaryCurve"s,
    "IfcOutlet"s,
    "IfcPile"s,
    "IfcPipeFitting"s,
    "IfcPipeSegment"s,
    "IfcPlate"s,
    "IfcPlateStandardCase"s,
    "IfcProtectiveDevice"s,
    "IfcProtectiveDeviceTrippingUnitType"s,
    "IfcPump"s,
    "IfcRailing"s,
    "IfcRamp"s,
    "IfcRampFlight"s,
    "IfcRationalBSplineCurveWithKnots"s,
    "IfcReinforcingBar"s,
    "IfcReinforcingBarType"s,
    "IfcRoof"s,
    "IfcSanitaryTerminal"s,
    "IfcSensorType"s,
    "IfcShadingDevice"s,
    "IfcSlab"s,
    "IfcSlabElementedCase"s,
    "IfcSlabStandardCase"s,
    "IfcSolarDevice"s,
    "IfcSpaceHeater"s,
    "IfcStackTerminal"s,
    "IfcStair"s,
    "IfcStairFlight"s,
    "IfcStructuralAnalysisModel"s,
    "IfcStructuralLoadCase"s,
    "IfcStructuralPlanarAction"s,
    "IfcSwitchingDevice"s,
    "IfcTank"s,
    "IfcTransformer"s,
    "IfcTubeBundle"s,
    "IfcUnitaryControlElementType"s,
    "IfcUnitaryEquipment"s,
    "IfcValve"s,
    "IfcWall"s,
    "IfcWallElementedCase"s,
    "IfcWallStandardCase"s,
    "IfcWasteTerminal"s,
    "IfcWindow"s,
    "IfcWindowStandardCase"s,
    "IfcSpaceBoundarySelect"s,
    "IfcActuatorType"s,
    "IfcAirTerminal"s,
    "IfcAirTerminalBox"s,
    "IfcAirToAirHeatRecovery"s,
    "IfcAlarmType"s,
    "IfcAudioVisualAppliance"s,
    "IfcBeam"s,
    "IfcBeamStandardCase"s,
    "IfcBoiler"s,
    "IfcBurner"s,
    "IfcCableCarrierFitting"s,
    "IfcCableCarrierSegment"s,
    "IfcCableFitting"s,
    "IfcCableSegment"s,
    "IfcChiller"s,
    "IfcCoil"s,
    "IfcCommunicationsAppliance"s,
    "IfcCompressor"s,
    "IfcCondenser"s,
    "IfcControllerType"s,
    "IfcCooledBeam"s,
    "IfcCoolingTower"s,
    "IfcDamper"s,
    "IfcDistributionChamberElement"s,
    "IfcDistributionCircuit"s,
    "IfcDistributionControlElement"s,
    "IfcDuctFitting"s,
    "IfcDuctSegment"s,
    "IfcDuctSilencer"s,
    "IfcElectricAppliance"s,
    "IfcElectricDistributionBoard"s,
    "IfcElectricFlowStorageDevice"s,
    "IfcElectricGenerator"s,
    "IfcElectricMotor"s,
    "IfcElectricTimeControl"s,
    "IfcFan"s,
    "IfcFilter"s,
    "IfcFireSuppressionTerminal"s,
    "IfcFlowInstrument"s,
    "IfcProtectiveDeviceTrippingUnit"s,
    "IfcSensor"s,
    "IfcUnitaryControlElement"s,
    "IfcActuator"s,
    "IfcAlarm"s,
    "IfcController"s,
    "PredefinedType"s,
    "Status"s,
    "LongDescription"s,
    "TheActor"s,
    "Role"s,
    "UserDefinedRole"s,
    "Description"s,
    "Purpose"s,
    "UserDefinedPurpose"s,
    "Voids"s,
    "OuterBoundary"s,
    "InnerBoundaries"s,
    "ApplicationDeveloper"s,
    "Version"s,
    "ApplicationFullName"s,
    "ApplicationIdentifier"s,
    "Name"s,
    "AppliedValue"s,
    "UnitBasis"s,
    "ApplicableDate"s,
    "FixedUntilDate"s,
    "Category"s,
    "Condition"s,
    "ArithmeticOperator"s,
    "Components"s,
    "Identifier"s,
    "TimeOfApproval"s,
    "Level"s,
    "Qualifier"s,
    "RequestingApproval"s,
    "GivingApproval"s,
    "RelatingApproval"s,
    "RelatedApprovals"s,
    "OuterCurve"s,
    "Curve"s,
    "InnerCurves"s,
    "Identification"s,
    "OriginalValue"s,
    "CurrentValue"s,
    "TotalReplacementCost"s,
    "Owner"s,
    "User"s,
    "ResponsiblePerson"s,
    "IncorporationDate"s,
    "DepreciatedValue"s,
    "BottomFlangeWidth"s,
    "OverallDepth"s,
    "WebThickness"s,
    "BottomFlangeThickness"s,
    "BottomFlangeFilletRadius"s,
    "TopFlangeWidth"s,
    "TopFlangeThickness"s,
    "TopFlangeFilletRadius"s,
    "BottomFlangeEdgeRadius"s,
    "BottomFlangeSlope"s,
    "TopFlangeEdgeRadius"s,
    "TopFlangeSlope"s,
    "Axis"s,
    "RefDirection"s,
    "Degree"s,
    "ControlPointsList"s,
    "CurveForm"s,
    "ClosedCurve"s,
    "SelfIntersect"s,
    "KnotMultiplicities"s,
    "Knots"s,
    "KnotSpec"s,
    "UDegree"s,
    "VDegree"s,
    "SurfaceForm"s,
    "UClosed"s,
    "VClosed"s,
    "UMultiplicities"s,
    "VMultiplicities"s,
    "UKnots"s,
    "VKnots"s,
    "RasterFormat"s,
    "RasterCode"s,
    "XLength"s,
    "YLength"s,
    "ZLength"s,
    "Operator"s,
    "FirstOperand"s,
    "SecondOperand"s,
    "TranslationalStiffnessByLengthX"s,
    "TranslationalStiffnessByLengthY"s,
    "TranslationalStiffnessByLengthZ"s,
    "RotationalStiffnessByLengthX"s,
    "RotationalStiffnessByLengthY"s,
    "RotationalStiffnessByLengthZ"s,
    "TranslationalStiffnessByAreaX"s,
    "TranslationalStiffnessByAreaY"s,
    "TranslationalStiffnessByAreaZ"s,
    "TranslationalStiffnessX"s,
    "TranslationalStiffnessY"s,
    "TranslationalStiffnessZ"s,
    "RotationalStiffnessX"s,
    "RotationalStiffnessY"s,
    "RotationalStiffnessZ"s,
    "WarpingStiffness"s,
    "Corner"s,
    "XDim"s,
    "YDim"s,
    "ZDim"s,
    "Enclosure"s,
    "ElevationOfRefHeight"s,
    "ElevationOfTerrain"s,
    "BuildingAddress"s,
    "Elevation"s,
    "LongName"s,
    "Depth"s,
    "Width"s,
    "WallThickness"s,
    "Girth"s,
    "InternalFilletRadius"s,
    "Coordinates"s,
    "CoordList"s,
    "Axis1"s,
    "Axis2"s,
    "LocalOrigin"s,
    "Scale"s,
    "Scale2"s,
    "Axis3"s,
    "Scale3"s,
    "Thickness"s,
    "Radius"s,
    "Source"s,
    "Edition"s,
    "EditionDate"s,
    "Location"s,
    "ReferenceTokens"s,
    "ReferencedSource"s,
    "Sort"s,
    "Red"s,
    "Green"s,
    "Blue"s,
    "ColourList"s,
    "UsageName"s,
    "HasProperties"s,
    "TemplateType"s,
    "HasPropertyTemplates"s,
    "Segments"s,
    "Transition"s,
    "SameSense"s,
    "ParentCurve"s,
    "Profiles"s,
    "Label"s,
    "Position"s,
    "CfsFaces"s,
    "CurveOnRelatingElement"s,
    "CurveOnRelatedElement"s,
    "EccentricityInX"s,
    "EccentricityInY"s,
    "EccentricityInZ"s,
    "PointOnRelatingElement"s,
    "PointOnRelatedElement"s,
    "SurfaceOnRelatingElement"s,
    "SurfaceOnRelatedElement"s,
    "VolumeOnRelatingElement"s,
    "VolumeOnRelatedElement"s,
    "ConstraintGrade"s,
    "ConstraintSource"s,
    "CreatingActor"s,
    "CreationTime"s,
    "UserDefinedGrade"s,
    "Usage"s,
    "BaseCosts"s,
    "BaseQuantity"s,
    "ObjectType"s,
    "Phase"s,
    "RepresentationContexts"s,
    "UnitsInContext"s,
    "ConversionFactor"s,
    "ConversionOffset"s,
    "SourceCRS"s,
    "TargetCRS"s,
    "GeodeticDatum"s,
    "VerticalDatum"s,
    "CostValues"s,
    "CostQuantities"s,
    "SubmittedOn"s,
    "UpdateDate"s,
    "TreeRootExpression"s,
    "RelatingMonetaryUnit"s,
    "RelatedMonetaryUnit"s,
    "ExchangeRate"s,
    "RateDateTime"s,
    "RateSource"s,
    "BasisSurface"s,
    "Boundaries"s,
    "ImplicitOuter"s,
    "CurveFont"s,
    "CurveWidth"s,
    "CurveColour"s,
    "ModelOrDraughting"s,
    "PatternList"s,
    "CurveFontScaling"s,
    "VisibleSegmentLength"s,
    "InvisibleSegmentLength"s,
    "ParentProfile"s,
    "Elements"s,
    "UnitType"s,
    "UserDefinedType"s,
    "Unit"s,
    "Exponent"s,
    "LengthExponent"s,
    "MassExponent"s,
    "TimeExponent"s,
    "ElectricCurrentExponent"s,
    "ThermodynamicTemperatureExponent"s,
    "AmountOfSubstanceExponent"s,
    "LuminousIntensityExponent"s,
    "DirectionRatios"s,
    "FlowDirection"s,
    "SystemType"s,
    "IntendedUse"s,
    "Scope"s,
    "Revision"s,
    "DocumentOwner"s,
    "Editors"s,
    "LastRevisionTime"s,
    "ElectronicFormat"s,
    "ValidFrom"s,
    "ValidUntil"s,
    "Confidentiality"s,
    "RelatingDocument"s,
    "RelatedDocuments"s,
    "RelationshipType"s,
    "ReferencedDocument"s,
    "OverallHeight"s,
    "OverallWidth"s,
    "OperationType"s,
    "UserDefinedOperationType"s,
    "LiningDepth"s,
    "LiningThickness"s,
    "ThresholdDepth"s,
    "ThresholdThickness"s,
    "TransomThickness"s,
    "TransomOffset"s,
    "LiningOffset"s,
    "ThresholdOffset"s,
    "CasingThickness"s,
    "CasingDepth"s,
    "ShapeAspectStyle"s,
    "LiningToPanelOffsetX"s,
    "LiningToPanelOffsetY"s,
    "PanelDepth"s,
    "PanelOperation"s,
    "PanelWidth"s,
    "PanelPosition"s,
    "ConstructionType"s,
    "ParameterTakesPrecedence"s,
    "Sizeable"s,
    "EdgeStart"s,
    "EdgeEnd"s,
    "EdgeGeometry"s,
    "EdgeList"s,
    "Tag"s,
    "AssemblyPlace"s,
    "MethodOfMeasurement"s,
    "Quantities"s,
    "ElementType"s,
    "SemiAxis1"s,
    "SemiAxis2"s,
    "EventTriggerType"s,
    "UserDefinedEventTriggerType"s,
    "EventOccurenceTime"s,
    "ActualDate"s,
    "EarlyDate"s,
    "LateDate"s,
    "ScheduleDate"s,
    "Properties"s,
    "RelatingReference"s,
    "RelatedResourceObjects"s,
    "ExtrudedDirection"s,
    "EndSweptArea"s,
    "Bounds"s,
    "FbsmFaces"s,
    "Bound"s,
    "Orientation"s,
    "FaceSurface"s,
    "TensionFailureX"s,
    "TensionFailureY"s,
    "TensionFailureZ"s,
    "CompressionFailureX"s,
    "CompressionFailureY"s,
    "CompressionFailureZ"s,
    "FillStyles"s,
    "ModelorDraughting"s,
    "HatchLineAppearance"s,
    "StartOfNextHatchLine"s,
    "PointOfReferenceHatchLine"s,
    "PatternStart"s,
    "HatchLineAngle"s,
    "TilingPattern"s,
    "Tiles"s,
    "TilingScale"s,
    "Directrix"s,
    "StartParam"s,
    "EndParam"s,
    "FixedReference"s,
    "CoordinateSpaceDimension"s,
    "Precision"s,
    "WorldCoordinateSystem"s,
    "TrueNorth"s,
    "ParentContext"s,
    "TargetScale"s,
    "TargetView"s,
    "UserDefinedTargetView"s,
    "UAxes"s,
    "VAxes"s,
    "WAxes"s,
    "AxisTag"s,
    "AxisCurve"s,
    "PlacementLocation"s,
    "PlacementRefDirection"s,
    "BaseSurface"s,
    "AgreementFlag"s,
    "FlangeThickness"s,
    "FilletRadius"s,
    "FlangeEdgeRadius"s,
    "FlangeSlope"s,
    "URLReference"s,
    "MappedTo"s,
    "Opacity"s,
    "Colours"s,
    "ColourIndex"s,
    "Points"s,
    "CoordIndex"s,
    "InnerCoordIndices"s,
    "TexCoords"s,
    "TexCoordIndex"s,
    "Jurisdiction"s,
    "ResponsiblePersons"s,
    "LastUpdateDate"s,
    "Values"s,
    "TimeStamp"s,
    "ListValues"s,
    "EdgeRadius"s,
    "LegSlope"s,
    "LagValue"s,
    "DurationType"s,
    "Publisher"s,
    "VersionDate"s,
    "Language"s,
    "ReferencedLibrary"s,
    "MainPlaneAngle"s,
    "SecondaryPlaneAngle"s,
    "LuminousIntensity"s,
    "LightDistributionCurve"s,
    "DistributionData"s,
    "LightColour"s,
    "AmbientIntensity"s,
    "Intensity"s,
    "ColourAppearance"s,
    "ColourTemperature"s,
    "LuminousFlux"s,
    "LightEmissionSource"s,
    "LightDistributionDataSource"s,
    "ConstantAttenuation"s,
    "DistanceAttenuation"s,
    "QuadricAttenuation"s,
    "ConcentrationExponent"s,
    "SpreadAngle"s,
    "BeamWidthAngle"s,
    "Pnt"s,
    "Dir"s,
    "PlacementRelTo"s,
    "RelativePlacement"s,
    "Outer"s,
    "Eastings"s,
    "Northings"s,
    "OrthogonalHeight"s,
    "XAxisAbscissa"s,
    "XAxisOrdinate"s,
    "MappingSource"s,
    "MappingTarget"s,
    "MaterialClassifications"s,
    "ClassifiedMaterial"s,
    "Material"s,
    "Fraction"s,
    "MaterialConstituents"s,
    "RepresentedMaterial"s,
    "LayerThickness"s,
    "IsVentilated"s,
    "Priority"s,
    "MaterialLayers"s,
    "LayerSetName"s,
    "ForLayerSet"s,
    "LayerSetDirection"s,
    "DirectionSense"s,
    "OffsetFromReferenceLine"s,
    "ReferenceExtent"s,
    "OffsetDirection"s,
    "OffsetValues"s,
    "Materials"s,
    "Profile"s,
    "MaterialProfiles"s,
    "CompositeProfile"s,
    "ForProfileSet"s,
    "CardinalPoint"s,
    "ForProfileEndSet"s,
    "CardinalEndPoint"s,
    "RelatingMaterial"s,
    "RelatedMaterials"s,
    "Expression"s,
    "ValueComponent"s,
    "UnitComponent"s,
    "NominalDiameter"s,
    "NominalLength"s,
    "Benchmark"s,
    "ValueSource"s,
    "DataValue"s,
    "ReferencePath"s,
    "Currency"s,
    "Dimensions"s,
    "BenchmarkValues"s,
    "LogicalAggregator"s,
    "ObjectiveQualifier"s,
    "UserDefinedQualifier"s,
    "BasisCurve"s,
    "Distance"s,
    "Roles"s,
    "Addresses"s,
    "RelatingOrganization"s,
    "RelatedOrganizations"s,
    "EdgeElement"s,
    "OwningUser"s,
    "OwningApplication"s,
    "State"s,
    "ChangeAction"s,
    "LastModifiedDate"s,
    "LastModifyingUser"s,
    "LastModifyingApplication"s,
    "CreationDate"s,
    "ReferenceCurve"s,
    "LifeCyclePhase"s,
    "FrameDepth"s,
    "FrameThickness"s,
    "FamilyName"s,
    "GivenName"s,
    "MiddleNames"s,
    "PrefixTitles"s,
    "SuffixTitles"s,
    "ThePerson"s,
    "TheOrganization"s,
    "HasQuantities"s,
    "Discrimination"s,
    "Quality"s,
    "Height"s,
    "ColourComponents"s,
    "Pixel"s,
    "Placement"s,
    "SizeInX"s,
    "SizeInY"s,
    "PointParameter"s,
    "PointParameterU"s,
    "PointParameterV"s,
    "Polygon"s,
    "PolygonalBoundary"s,
    "Closed"s,
    "Faces"s,
    "PnIndex"s,
    "InternalLocation"s,
    "AddressLines"s,
    "PostalBox"s,
    "Town"s,
    "Region"s,
    "PostalCode"s,
    "Country"s,
    "AssignedItems"s,
    "LayerOn"s,
    "LayerFrozen"s,
    "LayerBlocked"s,
    "LayerStyles"s,
    "Styles"s,
    "ObjectPlacement"s,
    "Representation"s,
    "Representations"s,
    "ProfileType"s,
    "ProfileName"s,
    "ProfileDefinition"s,
    "MapProjection"s,
    "MapZone"s,
    "MapUnit"s,
    "UpperBoundValue"s,
    "LowerBoundValue"s,
    "SetPointValue"s,
    "DependingProperty"s,
    "DependantProperty"s,
    "EnumerationValues"s,
    "EnumerationReference"s,
    "PropertyReference"s,
    "ApplicableEntity"s,
    "NominalValue"s,
    "DefiningValues"s,
    "DefinedValues"s,
    "DefiningUnit"s,
    "DefinedUnit"s,
    "CurveInterpolation"s,
    "ProxyType"s,
    "AreaValue"s,
    "Formula"s,
    "CountValue"s,
    "LengthValue"s,
    "TimeValue"s,
    "VolumeValue"s,
    "WeightValue"s,
    "WeightsData"s,
    "InnerFilletRadius"s,
    "OuterFilletRadius"s,
    "U1"s,
    "V1"s,
    "U2"s,
    "V2"s,
    "Usense"s,
    "Vsense"s,
    "RecurrenceType"s,
    "DayComponent"s,
    "WeekdayComponent"s,
    "MonthComponent"s,
    "Interval"s,
    "Occurrences"s,
    "TimePeriods"s,
    "TypeIdentifier"s,
    "AttributeIdentifier"s,
    "InstanceName"s,
    "ListPositions"s,
    "InnerReference"s,
    "TimeStep"s,
    "TotalCrossSectionArea"s,
    "SteelGrade"s,
    "BarSurface"s,
    "EffectiveDepth"s,
    "NominalBarDiameter"s,
    "BarCount"s,
    "DefinitionType"s,
    "ReinforcementSectionDefinitions"s,
    "CrossSectionArea"s,
    "BarLength"s,
    "BendingShapeCode"s,
    "BendingParameters"s,
    "MeshLength"s,
    "MeshWidth"s,
    "LongitudinalBarNominalDiameter"s,
    "TransverseBarNominalDiameter"s,
    "LongitudinalBarCrossSectionArea"s,
    "TransverseBarCrossSectionArea"s,
    "LongitudinalBarSpacing"s,
    "TransverseBarSpacing"s,
    "RelatingObject"s,
    "RelatedObjects"s,
    "RelatedObjectsType"s,
    "RelatingActor"s,
    "ActingRole"s,
    "RelatingControl"s,
    "RelatingGroup"s,
    "Factor"s,
    "RelatingProcess"s,
    "QuantityInProcess"s,
    "RelatingProduct"s,
    "RelatingResource"s,
    "RelatingClassification"s,
    "Intent"s,
    "RelatingConstraint"s,
    "RelatingLibrary"s,
    "ConnectionGeometry"s,
    "RelatingElement"s,
    "RelatedElement"s,
    "RelatingPriorities"s,
    "RelatedPriorities"s,
    "RelatedConnectionType"s,
    "RelatingConnectionType"s,
    "RelatingPort"s,
    "RelatedPort"s,
    "RealizingElement"s,
    "RelatedStructuralActivity"s,
    "RelatingStructuralMember"s,
    "RelatedStructuralConnection"s,
    "AppliedCondition"s,
    "AdditionalConditions"s,
    "SupportedLength"s,
    "ConditionCoordinateSystem"s,
    "ConnectionConstraint"s,
    "RealizingElements"s,
    "ConnectionType"s,
    "RelatedElements"s,
    "RelatingStructure"s,
    "RelatingBuildingElement"s,
    "RelatedCoverings"s,
    "RelatingSpace"s,
    "RelatingContext"s,
    "RelatedDefinitions"s,
    "RelatingPropertyDefinition"s,
    "RelatedPropertySets"s,
    "RelatingTemplate"s,
    "RelatingType"s,
    "RelatingOpeningElement"s,
    "RelatedBuildingElement"s,
    "RelatedControlElements"s,
    "RelatingFlowElement"s,
    "InterferenceGeometry"s,
    "InterferenceType"s,
    "ImpliedOrder"s,
    "RelatedFeatureElement"s,
    "RelatedProcess"s,
    "TimeLag"s,
    "SequenceType"s,
    "UserDefinedSequenceType"s,
    "RelatingSystem"s,
    "RelatedBuildings"s,
    "PhysicalOrVirtualBoundary"s,
    "InternalOrExternalBoundary"s,
    "ParentBoundary"s,
    "CorrespondingBoundary"s,
    "RelatedOpeningElement"s,
    "ParamLength"s,
    "ContextOfItems"s,
    "RepresentationIdentifier"s,
    "RepresentationType"s,
    "Items"s,
    "ContextIdentifier"s,
    "ContextType"s,
    "MappingOrigin"s,
    "MappedRepresentation"s,
    "ScheduleWork"s,
    "ScheduleUsage"s,
    "ScheduleStart"s,
    "ScheduleFinish"s,
    "ScheduleContour"s,
    "LevelingDelay"s,
    "IsOverAllocated"s,
    "StatusTime"s,
    "ActualWork"s,
    "ActualUsage"s,
    "ActualStart"s,
    "ActualFinish"s,
    "RemainingWork"s,
    "RemainingUsage"s,
    "Completion"s,
    "Angle"s,
    "BottomRadius"s,
    "GlobalId"s,
    "OwnerHistory"s,
    "RoundingRadius"s,
    "Prefix"s,
    "DataOrigin"s,
    "UserDefinedDataOrigin"s,
    "SectionType"s,
    "StartProfile"s,
    "EndProfile"s,
    "LongitudinalStartPosition"s,
    "LongitudinalEndPosition"s,
    "TransversePosition"s,
    "ReinforcementRole"s,
    "SectionDefinition"s,
    "CrossSectionReinforcementDefinitions"s,
    "SpineCurve"s,
    "CrossSections"s,
    "CrossSectionPositions"s,
    "ShapeRepresentations"s,
    "ProductDefinitional"s,
    "PartOfProductDefinitionShape"s,
    "SbsmBoundary"s,
    "PrimaryMeasureType"s,
    "SecondaryMeasureType"s,
    "Enumerators"s,
    "PrimaryUnit"s,
    "SecondaryUnit"s,
    "AccessState"s,
    "RefLatitude"s,
    "RefLongitude"s,
    "RefElevation"s,
    "LandTitleNumber"s,
    "SiteAddress"s,
    "SlippageX"s,
    "SlippageY"s,
    "SlippageZ"s,
    "ElevationWithFlooring"s,
    "CompositionType"s,
    "NumberOfRisers"s,
    "NumberOfTreads"s,
    "RiserHeight"s,
    "TreadLength"s,
    "DestabilizingLoad"s,
    "AppliedLoad"s,
    "GlobalOrLocal"s,
    "OrientationOf2DPlane"s,
    "LoadedBy"s,
    "HasResults"s,
    "SharedPlacement"s,
    "ProjectedOrTrue"s,
    "SelfWeightCoefficients"s,
    "Locations"s,
    "ActionType"s,
    "ActionSource"s,
    "Coefficient"s,
    "LinearForceX"s,
    "LinearForceY"s,
    "LinearForceZ"s,
    "LinearMomentX"s,
    "LinearMomentY"s,
    "LinearMomentZ"s,
    "PlanarForceX"s,
    "PlanarForceY"s,
    "PlanarForceZ"s,
    "DisplacementX"s,
    "DisplacementY"s,
    "DisplacementZ"s,
    "RotationalDisplacementRX"s,
    "RotationalDisplacementRY"s,
    "RotationalDisplacementRZ"s,
    "Distortion"s,
    "ForceX"s,
    "ForceY"s,
    "ForceZ"s,
    "MomentX"s,
    "MomentY"s,
    "MomentZ"s,
    "WarpingMoment"s,
    "DeltaTConstant"s,
    "DeltaTY"s,
    "DeltaTZ"s,
    "TheoryType"s,
    "ResultForLoadGroup"s,
    "IsLinear"s,
    "Item"s,
    "ParentEdge"s,
    "Curve3D"s,
    "AssociatedGeometry"s,
    "MasterRepresentation"s,
    "ReferenceSurface"s,
    "AxisPosition"s,
    "SurfaceReinforcement1"s,
    "SurfaceReinforcement2"s,
    "ShearReinforcement"s,
    "Side"s,
    "DiffuseTransmissionColour"s,
    "DiffuseReflectionColour"s,
    "TransmissionColour"s,
    "ReflectanceColour"s,
    "RefractionIndex"s,
    "DispersionFactor"s,
    "DiffuseColour"s,
    "ReflectionColour"s,
    "SpecularColour"s,
    "SpecularHighlight"s,
    "ReflectanceMethod"s,
    "SurfaceColour"s,
    "Transparency"s,
    "Textures"s,
    "RepeatS"s,
    "RepeatT"s,
    "Mode"s,
    "TextureTransform"s,
    "Parameter"s,
    "SweptArea"s,
    "InnerRadius"s,
    "SweptCurve"s,
    "FlangeWidth"s,
    "WebEdgeRadius"s,
    "WebSlope"s,
    "Rows"s,
    "Columns"s,
    "RowCells"s,
    "IsHeading"s,
    "WorkMethod"s,
    "IsMilestone"s,
    "TaskTime"s,
    "ScheduleDuration"s,
    "EarlyStart"s,
    "EarlyFinish"s,
    "LateStart"s,
    "LateFinish"s,
    "FreeFloat"s,
    "TotalFloat"s,
    "IsCritical"s,
    "ActualDuration"s,
    "RemainingTime"s,
    "Recurrence"s,
    "TelephoneNumbers"s,
    "FacsimileNumbers"s,
    "PagerNumber"s,
    "ElectronicMailAddresses"s,
    "WWWHomePageURL"s,
    "MessagingIDs"s,
    "TensionForce"s,
    "PreStress"s,
    "FrictionCoefficient"s,
    "AnchorageSlip"s,
    "MinCurvatureRadius"s,
    "SheathDiameter"s,
    "Literal"s,
    "Path"s,
    "Extent"s,
    "BoxAlignment"s,
    "TextCharacterAppearance"s,
    "TextStyle"s,
    "TextFontStyle"s,
    "FontFamily"s,
    "FontStyle"s,
    "FontVariant"s,
    "FontWeight"s,
    "FontSize"s,
    "Colour"s,
    "BackgroundColour"s,
    "TextIndent"s,
    "TextAlign"s,
    "TextDecoration"s,
    "LetterSpacing"s,
    "WordSpacing"s,
    "TextTransform"s,
    "LineHeight"s,
    "Maps"s,
    "Vertices"s,
    "TexCoordsList"s,
    "StartTime"s,
    "EndTime"s,
    "TimeSeriesDataType"s,
    "MajorRadius"s,
    "MinorRadius"s,
    "BottomXDim"s,
    "TopXDim"s,
    "TopXOffset"s,
    "Normals"s,
    "Trim1"s,
    "Trim2"s,
    "SenseAgreement"s,
    "ApplicableOccurrence"s,
    "HasPropertySets"s,
    "ProcessType"s,
    "RepresentationMaps"s,
    "ResourceType"s,
    "Units"s,
    "Magnitude"s,
    "LoopVertex"s,
    "VertexGeometry"s,
    "IntersectingAxes"s,
    "OffsetDistances"s,
    "PartitioningType"s,
    "UserDefinedPartitioningType"s,
    "MullionThickness"s,
    "FirstTransomOffset"s,
    "SecondTransomOffset"s,
    "FirstMullionOffset"s,
    "SecondMullionOffset"s,
    "WorkingTimes"s,
    "ExceptionTimes"s,
    "Creators"s,
    "Duration"s,
    "FinishTime"s,
    "RecurrencePattern"s,
    "Start"s,
    "Finish"s,
    "IsActingUpon"s,
    "HasExternalReference"s,
    "OfPerson"s,
    "OfOrganization"s,
    "ContainedInStructure"s,
    "HasExternalReferences"s,
    "ApprovedObjects"s,
    "ApprovedResources"s,
    "IsRelatedWith"s,
    "Relates"s,
    "ClassificationForObjects"s,
    "HasReferences"s,
    "ClassificationRefForObjects"s,
    "UsingCurves"s,
    "PropertiesForConstraint"s,
    "IsDefinedBy"s,
    "Declares"s,
    "Controls"s,
    "HasCoordinateOperation"s,
    "CoversSpaces"s,
    "CoversElements"s,
    "AssignedToFlowElement"s,
    "HasPorts"s,
    "HasControlElements"s,
    "DocumentInfoForObjects"s,
    "HasDocumentReferences"s,
    "IsPointedTo"s,
    "IsPointer"s,
    "DocumentRefForObjects"s,
    "FillsVoids"s,
    "ConnectedTo"s,
    "IsInterferedByElements"s,
    "InterferesElements"s,
    "HasProjections"s,
    "ReferencedInStructures"s,
    "HasOpenings"s,
    "IsConnectionRealization"s,
    "ProvidesBoundaries"s,
    "ConnectedFrom"s,
    "HasCoverings"s,
    "ExternalReferenceForResources"s,
    "BoundedBy"s,
    "HasTextureMaps"s,
    "ProjectsElements"s,
    "VoidsElements"s,
    "HasSubContexts"s,
    "PartOfW"s,
    "PartOfV"s,
    "PartOfU"s,
    "HasIntersections"s,
    "IsGroupedBy"s,
    "ToFaceSet"s,
    "LibraryInfoForObjects"s,
    "HasLibraryReferences"s,
    "LibraryRefForObjects"s,
    "HasRepresentation"s,
    "RelatesTo"s,
    "ToMaterialConstituentSet"s,
    "AssociatedTo"s,
    "ToMaterialLayerSet"s,
    "ToMaterialProfileSet"s,
    "IsDeclaredBy"s,
    "IsTypedBy"s,
    "HasAssignments"s,
    "Nests"s,
    "IsNestedBy"s,
    "HasContext"s,
    "IsDecomposedBy"s,
    "Decomposes"s,
    "HasAssociations"s,
    "PlacesObject"s,
    "ReferencedByPlacements"s,
    "HasFillings"s,
    "IsRelatedBy"s,
    "Engages"s,
    "EngagedIn"s,
    "PartOfComplex"s,
    "ContainedIn"s,
    "IsPredecessorTo"s,
    "IsSuccessorFrom"s,
    "OperatesOn"s,
    "ReferencedBy"s,
    "ShapeOfProduct"s,
    "HasShapeAspects"s,
    "PartOfPset"s,
    "PropertyForDependance"s,
    "PropertyDependsOn"s,
    "HasConstraints"s,
    "HasApprovals"s,
    "DefinesType"s,
    "DefinesOccurrence"s,
    "Defines"s,
    "PartOfComplexTemplate"s,
    "PartOfPsetTemplate"s,
    "Corresponds"s,
    "RepresentationMap"s,
    "LayerAssignments"s,
    "OfProductRepresentation"s,
    "RepresentationsInContext"s,
    "LayerAssignment"s,
    "StyledByItem"s,
    "MapUsage"s,
    "ResourceOf"s,
    "OfShapeAspect"s,
    "ContainsElements"s,
    "ServicedBySystems"s,
    "ReferencesElements"s,
    "AssignedToStructuralItem"s,
    "ConnectsStructuralMembers"s,
    "AssignedStructuralActivity"s,
    "SourceOfResultGroup"s,
    "LoadGroupFor"s,
    "ConnectedBy"s,
    "ResultGroupFor"s,
    "IsMappedBy"s,
    "UsedInStyles"s,
    "ServicesBuildings"s,
    "HasColours"s,
    "HasTextures"s,
    "Types"s,
    "IFC4"s};

class IFC4_instance_factory : public IfcParse::instance_factory {
  virtual IfcUtil::IfcBaseClass *
  operator()(const IfcParse::declaration *decl,
             IfcEntityInstanceData &&data) const {
    switch (decl->index_in_schema()) {
    case 0:
      return new ::Ifc4::IfcAbsorbedDoseMeasure(std::move(data));
    case 1:
      return new ::Ifc4::IfcAccelerationMeasure(std::move(data));
    case 2:
      return new ::Ifc4::IfcActionRequest(std::move(data));
    case 3:
      return new ::Ifc4::IfcActionRequestTypeEnum(std::move(data));
    case 4:
      return new ::Ifc4::IfcActionSourceTypeEnum(std::move(data));
    case 5:
      return new ::Ifc4::IfcActionTypeEnum(std::move(data));
    case 6:
      return new ::Ifc4::IfcActor(std::move(data));
    case 7:
      return new ::Ifc4::IfcActorRole(std::move(data));
    case 9:
      return new ::Ifc4::IfcActuator(std::move(data));
    case 10:
      return new ::Ifc4::IfcActuatorType(std::move(data));
    case 11:
      return new ::Ifc4::IfcActuatorTypeEnum(std::move(data));
    case 12:
      return new ::Ifc4::IfcAddress(std::move(data));
    case 13:
      return new ::Ifc4::IfcAddressTypeEnum(std::move(data));
    case 14:
      return new ::Ifc4::IfcAdvancedBrep(std::move(data));
    case 15:
      return new ::Ifc4::IfcAdvancedBrepWithVoids(std::move(data));
    case 16:
      return new ::Ifc4::IfcAdvancedFace(std::move(data));
    case 17:
      return new ::Ifc4::IfcAirTerminal(std::move(data));
    case 18:
      return new ::Ifc4::IfcAirTerminalBox(std::move(data));
    case 19:
      return new ::Ifc4::IfcAirTerminalBoxType(std::move(data));
    case 20:
      return new ::Ifc4::IfcAirTerminalBoxTypeEnum(std::move(data));
    case 21:
      return new ::Ifc4::IfcAirTerminalType(std::move(data));
    case 22:
      return new ::Ifc4::IfcAirTerminalTypeEnum(std::move(data));
    case 23:
      return new ::Ifc4::IfcAirToAirHeatRecovery(std::move(data));
    case 24:
      return new ::Ifc4::IfcAirToAirHeatRecoveryType(std::move(data));
    case 25:
      return new ::Ifc4::IfcAirToAirHeatRecoveryTypeEnum(std::move(data));
    case 26:
      return new ::Ifc4::IfcAlarm(std::move(data));
    case 27:
      return new ::Ifc4::IfcAlarmType(std::move(data));
    case 28:
      return new ::Ifc4::IfcAlarmTypeEnum(std::move(data));
    case 29:
      return new ::Ifc4::IfcAmountOfSubstanceMeasure(std::move(data));
    case 30:
      return new ::Ifc4::IfcAnalysisModelTypeEnum(std::move(data));
    case 31:
      return new ::Ifc4::IfcAnalysisTheoryTypeEnum(std::move(data));
    case 32:
      return new ::Ifc4::IfcAngularVelocityMeasure(std::move(data));
    case 33:
      return new ::Ifc4::IfcAnnotation(std::move(data));
    case 34:
      return new ::Ifc4::IfcAnnotationFillArea(std::move(data));
    case 35:
      return new ::Ifc4::IfcApplication(std::move(data));
    case 36:
      return new ::Ifc4::IfcAppliedValue(std::move(data));
    case 38:
      return new ::Ifc4::IfcApproval(std::move(data));
    case 39:
      return new ::Ifc4::IfcApprovalRelationship(std::move(data));
    case 40:
      return new ::Ifc4::IfcArbitraryClosedProfileDef(std::move(data));
    case 41:
      return new ::Ifc4::IfcArbitraryOpenProfileDef(std::move(data));
    case 42:
      return new ::Ifc4::IfcArbitraryProfileDefWithVoids(std::move(data));
    case 43:
      return new ::Ifc4::IfcArcIndex(std::move(data));
    case 44:
      return new ::Ifc4::IfcAreaDensityMeasure(std::move(data));
    case 45:
      return new ::Ifc4::IfcAreaMeasure(std::move(data));
    case 46:
      return new ::Ifc4::IfcArithmeticOperatorEnum(std::move(data));
    case 47:
      return new ::Ifc4::IfcAssemblyPlaceEnum(std::move(data));
    case 48:
      return new ::Ifc4::IfcAsset(std::move(data));
    case 49:
      return new ::Ifc4::IfcAsymmetricIShapeProfileDef(std::move(data));
    case 50:
      return new ::Ifc4::IfcAudioVisualAppliance(std::move(data));
    case 51:
      return new ::Ifc4::IfcAudioVisualApplianceType(std::move(data));
    case 52:
      return new ::Ifc4::IfcAudioVisualApplianceTypeEnum(std::move(data));
    case 53:
      return new ::Ifc4::IfcAxis1Placement(std::move(data));
    case 55:
      return new ::Ifc4::IfcAxis2Placement2D(std::move(data));
    case 56:
      return new ::Ifc4::IfcAxis2Placement3D(std::move(data));
    case 57:
      return new ::Ifc4::IfcBeam(std::move(data));
    case 58:
      return new ::Ifc4::IfcBeamStandardCase(std::move(data));
    case 59:
      return new ::Ifc4::IfcBeamType(std::move(data));
    case 60:
      return new ::Ifc4::IfcBeamTypeEnum(std::move(data));
    case 61:
      return new ::Ifc4::IfcBenchmarkEnum(std::move(data));
    case 63:
      return new ::Ifc4::IfcBinary(std::move(data));
    case 64:
      return new ::Ifc4::IfcBlobTexture(std::move(data));
    case 65:
      return new ::Ifc4::IfcBlock(std::move(data));
    case 66:
      return new ::Ifc4::IfcBoiler(std::move(data));
    case 67:
      return new ::Ifc4::IfcBoilerType(std::move(data));
    case 68:
      return new ::Ifc4::IfcBoilerTypeEnum(std::move(data));
    case 69:
      return new ::Ifc4::IfcBoolean(std::move(data));
    case 70:
      return new ::Ifc4::IfcBooleanClippingResult(std::move(data));
    case 72:
      return new ::Ifc4::IfcBooleanOperator(std::move(data));
    case 73:
      return new ::Ifc4::IfcBooleanResult(std::move(data));
    case 74:
      return new ::Ifc4::IfcBoundaryCondition(std::move(data));
    case 75:
      return new ::Ifc4::IfcBoundaryCurve(std::move(data));
    case 76:
      return new ::Ifc4::IfcBoundaryEdgeCondition(std::move(data));
    case 77:
      return new ::Ifc4::IfcBoundaryFaceCondition(std::move(data));
    case 78:
      return new ::Ifc4::IfcBoundaryNodeCondition(std::move(data));
    case 79:
      return new ::Ifc4::IfcBoundaryNodeConditionWarping(std::move(data));
    case 80:
      return new ::Ifc4::IfcBoundedCurve(std::move(data));
    case 81:
      return new ::Ifc4::IfcBoundedSurface(std::move(data));
    case 82:
      return new ::Ifc4::IfcBoundingBox(std::move(data));
    case 83:
      return new ::Ifc4::IfcBoxAlignment(std::move(data));
    case 84:
      return new ::Ifc4::IfcBoxedHalfSpace(std::move(data));
    case 85:
      return new ::Ifc4::IfcBSplineCurve(std::move(data));
    case 86:
      return new ::Ifc4::IfcBSplineCurveForm(std::move(data));
    case 87:
      return new ::Ifc4::IfcBSplineCurveWithKnots(std::move(data));
    case 88:
      return new ::Ifc4::IfcBSplineSurface(std::move(data));
    case 89:
      return new ::Ifc4::IfcBSplineSurfaceForm(std::move(data));
    case 90:
      return new ::Ifc4::IfcBSplineSurfaceWithKnots(std::move(data));
    case 91:
      return new ::Ifc4::IfcBuilding(std::move(data));
    case 92:
      return new ::Ifc4::IfcBuildingElement(std::move(data));
    case 93:
      return new ::Ifc4::IfcBuildingElementPart(std::move(data));
    case 94:
      return new ::Ifc4::IfcBuildingElementPartType(std::move(data));
    case 95:
      return new ::Ifc4::IfcBuildingElementPartTypeEnum(std::move(data));
    case 96:
      return new ::Ifc4::IfcBuildingElementProxy(std::move(data));
    case 97:
      return new ::Ifc4::IfcBuildingElementProxyType(std::move(data));
    case 98:
      return new ::Ifc4::IfcBuildingElementProxyTypeEnum(std::move(data));
    case 99:
      return new ::Ifc4::IfcBuildingElementType(std::move(data));
    case 100:
      return new ::Ifc4::IfcBuildingStorey(std::move(data));
    case 101:
      return new ::Ifc4::IfcBuildingSystem(std::move(data));
    case 102:
      return new ::Ifc4::IfcBuildingSystemTypeEnum(std::move(data));
    case 103:
      return new ::Ifc4::IfcBurner(std::move(data));
    case 104:
      return new ::Ifc4::IfcBurnerType(std::move(data));
    case 105:
      return new ::Ifc4::IfcBurnerTypeEnum(std::move(data));
    case 106:
      return new ::Ifc4::IfcCableCarrierFitting(std::move(data));
    case 107:
      return new ::Ifc4::IfcCableCarrierFittingType(std::move(data));
    case 108:
      return new ::Ifc4::IfcCableCarrierFittingTypeEnum(std::move(data));
    case 109:
      return new ::Ifc4::IfcCableCarrierSegment(std::move(data));
    case 110:
      return new ::Ifc4::IfcCableCarrierSegmentType(std::move(data));
    case 111:
      return new ::Ifc4::IfcCableCarrierSegmentTypeEnum(std::move(data));
    case 112:
      return new ::Ifc4::IfcCableFitting(std::move(data));
    case 113:
      return new ::Ifc4::IfcCableFittingType(std::move(data));
    case 114:
      return new ::Ifc4::IfcCableFittingTypeEnum(std::move(data));
    case 115:
      return new ::Ifc4::IfcCableSegment(std::move(data));
    case 116:
      return new ::Ifc4::IfcCableSegmentType(std::move(data));
    case 117:
      return new ::Ifc4::IfcCableSegmentTypeEnum(std::move(data));
    case 118:
      return new ::Ifc4::IfcCardinalPointReference(std::move(data));
    case 119:
      return new ::Ifc4::IfcCartesianPoint(std::move(data));
    case 120:
      return new ::Ifc4::IfcCartesianPointList(std::move(data));
    case 121:
      return new ::Ifc4::IfcCartesianPointList2D(std::move(data));
    case 122:
      return new ::Ifc4::IfcCartesianPointList3D(std::move(data));
    case 123:
      return new ::Ifc4::IfcCartesianTransformationOperator(std::move(data));
    case 124:
      return new ::Ifc4::IfcCartesianTransformationOperator2D(std::move(data));
    case 125:
      return new ::Ifc4::IfcCartesianTransformationOperator2DnonUniform(
          std::move(data));
    case 126:
      return new ::Ifc4::IfcCartesianTransformationOperator3D(std::move(data));
    case 127:
      return new ::Ifc4::IfcCartesianTransformationOperator3DnonUniform(
          std::move(data));
    case 128:
      return new ::Ifc4::IfcCenterLineProfileDef(std::move(data));
    case 129:
      return new ::Ifc4::IfcChangeActionEnum(std::move(data));
    case 130:
      return new ::Ifc4::IfcChiller(std::move(data));
    case 131:
      return new ::Ifc4::IfcChillerType(std::move(data));
    case 132:
      return new ::Ifc4::IfcChillerTypeEnum(std::move(data));
    case 133:
      return new ::Ifc4::IfcChimney(std::move(data));
    case 134:
      return new ::Ifc4::IfcChimneyType(std::move(data));
    case 135:
      return new ::Ifc4::IfcChimneyTypeEnum(std::move(data));
    case 136:
      return new ::Ifc4::IfcCircle(std::move(data));
    case 137:
      return new ::Ifc4::IfcCircleHollowProfileDef(std::move(data));
    case 138:
      return new ::Ifc4::IfcCircleProfileDef(std::move(data));
    case 139:
      return new ::Ifc4::IfcCivilElement(std::move(data));
    case 140:
      return new ::Ifc4::IfcCivilElementType(std::move(data));
    case 141:
      return new ::Ifc4::IfcClassification(std::move(data));
    case 142:
      return new ::Ifc4::IfcClassificationReference(std::move(data));
    case 145:
      return new ::Ifc4::IfcClosedShell(std::move(data));
    case 146:
      return new ::Ifc4::IfcCoil(std::move(data));
    case 147:
      return new ::Ifc4::IfcCoilType(std::move(data));
    case 148:
      return new ::Ifc4::IfcCoilTypeEnum(std::move(data));
    case 151:
      return new ::Ifc4::IfcColourRgb(std::move(data));
    case 152:
      return new ::Ifc4::IfcColourRgbList(std::move(data));
    case 153:
      return new ::Ifc4::IfcColourSpecification(std::move(data));
    case 154:
      return new ::Ifc4::IfcColumn(std::move(data));
    case 155:
      return new ::Ifc4::IfcColumnStandardCase(std::move(data));
    case 156:
      return new ::Ifc4::IfcColumnType(std::move(data));
    case 157:
      return new ::Ifc4::IfcColumnTypeEnum(std::move(data));
    case 158:
      return new ::Ifc4::IfcCommunicationsAppliance(std::move(data));
    case 159:
      return new ::Ifc4::IfcCommunicationsApplianceType(std::move(data));
    case 160:
      return new ::Ifc4::IfcCommunicationsApplianceTypeEnum(std::move(data));
    case 161:
      return new ::Ifc4::IfcComplexNumber(std::move(data));
    case 162:
      return new ::Ifc4::IfcComplexProperty(std::move(data));
    case 163:
      return new ::Ifc4::IfcComplexPropertyTemplate(std::move(data));
    case 164:
      return new ::Ifc4::IfcComplexPropertyTemplateTypeEnum(std::move(data));
    case 165:
      return new ::Ifc4::IfcCompositeCurve(std::move(data));
    case 166:
      return new ::Ifc4::IfcCompositeCurveOnSurface(std::move(data));
    case 167:
      return new ::Ifc4::IfcCompositeCurveSegment(std::move(data));
    case 168:
      return new ::Ifc4::IfcCompositeProfileDef(std::move(data));
    case 169:
      return new ::Ifc4::IfcCompoundPlaneAngleMeasure(std::move(data));
    case 170:
      return new ::Ifc4::IfcCompressor(std::move(data));
    case 171:
      return new ::Ifc4::IfcCompressorType(std::move(data));
    case 172:
      return new ::Ifc4::IfcCompressorTypeEnum(std::move(data));
    case 173:
      return new ::Ifc4::IfcCondenser(std::move(data));
    case 174:
      return new ::Ifc4::IfcCondenserType(std::move(data));
    case 175:
      return new ::Ifc4::IfcCondenserTypeEnum(std::move(data));
    case 176:
      return new ::Ifc4::IfcConic(std::move(data));
    case 177:
      return new ::Ifc4::IfcConnectedFaceSet(std::move(data));
    case 178:
      return new ::Ifc4::IfcConnectionCurveGeometry(std::move(data));
    case 179:
      return new ::Ifc4::IfcConnectionGeometry(std::move(data));
    case 180:
      return new ::Ifc4::IfcConnectionPointEccentricity(std::move(data));
    case 181:
      return new ::Ifc4::IfcConnectionPointGeometry(std::move(data));
    case 182:
      return new ::Ifc4::IfcConnectionSurfaceGeometry(std::move(data));
    case 183:
      return new ::Ifc4::IfcConnectionTypeEnum(std::move(data));
    case 184:
      return new ::Ifc4::IfcConnectionVolumeGeometry(std::move(data));
    case 185:
      return new ::Ifc4::IfcConstraint(std::move(data));
    case 186:
      return new ::Ifc4::IfcConstraintEnum(std::move(data));
    case 187:
      return new ::Ifc4::IfcConstructionEquipmentResource(std::move(data));
    case 188:
      return new ::Ifc4::IfcConstructionEquipmentResourceType(std::move(data));
    case 189:
      return new ::Ifc4::IfcConstructionEquipmentResourceTypeEnum(
          std::move(data));
    case 190:
      return new ::Ifc4::IfcConstructionMaterialResource(std::move(data));
    case 191:
      return new ::Ifc4::IfcConstructionMaterialResourceType(std::move(data));
    case 192:
      return new ::Ifc4::IfcConstructionMaterialResourceTypeEnum(
          std::move(data));
    case 193:
      return new ::Ifc4::IfcConstructionProductResource(std::move(data));
    case 194:
      return new ::Ifc4::IfcConstructionProductResourceType(std::move(data));
    case 195:
      return new ::Ifc4::IfcConstructionProductResourceTypeEnum(
          std::move(data));
    case 196:
      return new ::Ifc4::IfcConstructionResource(std::move(data));
    case 197:
      return new ::Ifc4::IfcConstructionResourceType(std::move(data));
    case 198:
      return new ::Ifc4::IfcContext(std::move(data));
    case 199:
      return new ::Ifc4::IfcContextDependentMeasure(std::move(data));
    case 200:
      return new ::Ifc4::IfcContextDependentUnit(std::move(data));
    case 201:
      return new ::Ifc4::IfcControl(std::move(data));
    case 202:
      return new ::Ifc4::IfcController(std::move(data));
    case 203:
      return new ::Ifc4::IfcControllerType(std::move(data));
    case 204:
      return new ::Ifc4::IfcControllerTypeEnum(std::move(data));
    case 205:
      return new ::Ifc4::IfcConversionBasedUnit(std::move(data));
    case 206:
      return new ::Ifc4::IfcConversionBasedUnitWithOffset(std::move(data));
    case 207:
      return new ::Ifc4::IfcCooledBeam(std::move(data));
    case 208:
      return new ::Ifc4::IfcCooledBeamType(std::move(data));
    case 209:
      return new ::Ifc4::IfcCooledBeamTypeEnum(std::move(data));
    case 210:
      return new ::Ifc4::IfcCoolingTower(std::move(data));
    case 211:
      return new ::Ifc4::IfcCoolingTowerType(std::move(data));
    case 212:
      return new ::Ifc4::IfcCoolingTowerTypeEnum(std::move(data));
    case 213:
      return new ::Ifc4::IfcCoordinateOperation(std::move(data));
    case 214:
      return new ::Ifc4::IfcCoordinateReferenceSystem(std::move(data));
    case 216:
      return new ::Ifc4::IfcCostItem(std::move(data));
    case 217:
      return new ::Ifc4::IfcCostItemTypeEnum(std::move(data));
    case 218:
      return new ::Ifc4::IfcCostSchedule(std::move(data));
    case 219:
      return new ::Ifc4::IfcCostScheduleTypeEnum(std::move(data));
    case 220:
      return new ::Ifc4::IfcCostValue(std::move(data));
    case 221:
      return new ::Ifc4::IfcCountMeasure(std::move(data));
    case 222:
      return new ::Ifc4::IfcCovering(std::move(data));
    case 223:
      return new ::Ifc4::IfcCoveringType(std::move(data));
    case 224:
      return new ::Ifc4::IfcCoveringTypeEnum(std::move(data));
    case 225:
      return new ::Ifc4::IfcCrewResource(std::move(data));
    case 226:
      return new ::Ifc4::IfcCrewResourceType(std::move(data));
    case 227:
      return new ::Ifc4::IfcCrewResourceTypeEnum(std::move(data));
    case 228:
      return new ::Ifc4::IfcCsgPrimitive3D(std::move(data));
    case 230:
      return new ::Ifc4::IfcCsgSolid(std::move(data));
    case 231:
      return new ::Ifc4::IfcCShapeProfileDef(std::move(data));
    case 232:
      return new ::Ifc4::IfcCurrencyRelationship(std::move(data));
    case 233:
      return new ::Ifc4::IfcCurtainWall(std::move(data));
    case 234:
      return new ::Ifc4::IfcCurtainWallType(std::move(data));
    case 235:
      return new ::Ifc4::IfcCurtainWallTypeEnum(std::move(data));
    case 236:
      return new ::Ifc4::IfcCurvatureMeasure(std::move(data));
    case 237:
      return new ::Ifc4::IfcCurve(std::move(data));
    case 238:
      return new ::Ifc4::IfcCurveBoundedPlane(std::move(data));
    case 239:
      return new ::Ifc4::IfcCurveBoundedSurface(std::move(data));
    case 241:
      return new ::Ifc4::IfcCurveInterpolationEnum(std::move(data));
    case 244:
      return new ::Ifc4::IfcCurveStyle(std::move(data));
    case 245:
      return new ::Ifc4::IfcCurveStyleFont(std::move(data));
    case 246:
      return new ::Ifc4::IfcCurveStyleFontAndScaling(std::move(data));
    case 247:
      return new ::Ifc4::IfcCurveStyleFontPattern(std::move(data));
    case 249:
      return new ::Ifc4::IfcCylindricalSurface(std::move(data));
    case 250:
      return new ::Ifc4::IfcDamper(std::move(data));
    case 251:
      return new ::Ifc4::IfcDamperType(std::move(data));
    case 252:
      return new ::Ifc4::IfcDamperTypeEnum(std::move(data));
    case 253:
      return new ::Ifc4::IfcDataOriginEnum(std::move(data));
    case 254:
      return new ::Ifc4::IfcDate(std::move(data));
    case 255:
      return new ::Ifc4::IfcDateTime(std::move(data));
    case 256:
      return new ::Ifc4::IfcDayInMonthNumber(std::move(data));
    case 257:
      return new ::Ifc4::IfcDayInWeekNumber(std::move(data));
    case 260:
      return new ::Ifc4::IfcDerivedProfileDef(std::move(data));
    case 261:
      return new ::Ifc4::IfcDerivedUnit(std::move(data));
    case 262:
      return new ::Ifc4::IfcDerivedUnitElement(std::move(data));
    case 263:
      return new ::Ifc4::IfcDerivedUnitEnum(std::move(data));
    case 264:
      return new ::Ifc4::IfcDescriptiveMeasure(std::move(data));
    case 265:
      return new ::Ifc4::IfcDimensionalExponents(std::move(data));
    case 266:
      return new ::Ifc4::IfcDimensionCount(std::move(data));
    case 267:
      return new ::Ifc4::IfcDirection(std::move(data));
    case 268:
      return new ::Ifc4::IfcDirectionSenseEnum(std::move(data));
    case 269:
      return new ::Ifc4::IfcDiscreteAccessory(std::move(data));
    case 270:
      return new ::Ifc4::IfcDiscreteAccessoryType(std::move(data));
    case 271:
      return new ::Ifc4::IfcDiscreteAccessoryTypeEnum(std::move(data));
    case 272:
      return new ::Ifc4::IfcDistributionChamberElement(std::move(data));
    case 273:
      return new ::Ifc4::IfcDistributionChamberElementType(std::move(data));
    case 274:
      return new ::Ifc4::IfcDistributionChamberElementTypeEnum(std::move(data));
    case 275:
      return new ::Ifc4::IfcDistributionCircuit(std::move(data));
    case 276:
      return new ::Ifc4::IfcDistributionControlElement(std::move(data));
    case 277:
      return new ::Ifc4::IfcDistributionControlElementType(std::move(data));
    case 278:
      return new ::Ifc4::IfcDistributionElement(std::move(data));
    case 279:
      return new ::Ifc4::IfcDistributionElementType(std::move(data));
    case 280:
      return new ::Ifc4::IfcDistributionFlowElement(std::move(data));
    case 281:
      return new ::Ifc4::IfcDistributionFlowElementType(std::move(data));
    case 282:
      return new ::Ifc4::IfcDistributionPort(std::move(data));
    case 283:
      return new ::Ifc4::IfcDistributionPortTypeEnum(std::move(data));
    case 284:
      return new ::Ifc4::IfcDistributionSystem(std::move(data));
    case 285:
      return new ::Ifc4::IfcDistributionSystemEnum(std::move(data));
    case 286:
      return new ::Ifc4::IfcDocumentConfidentialityEnum(std::move(data));
    case 287:
      return new ::Ifc4::IfcDocumentInformation(std::move(data));
    case 288:
      return new ::Ifc4::IfcDocumentInformationRelationship(std::move(data));
    case 289:
      return new ::Ifc4::IfcDocumentReference(std::move(data));
    case 291:
      return new ::Ifc4::IfcDocumentStatusEnum(std::move(data));
    case 292:
      return new ::Ifc4::IfcDoor(std::move(data));
    case 293:
      return new ::Ifc4::IfcDoorLiningProperties(std::move(data));
    case 294:
      return new ::Ifc4::IfcDoorPanelOperationEnum(std::move(data));
    case 295:
      return new ::Ifc4::IfcDoorPanelPositionEnum(std::move(data));
    case 296:
      return new ::Ifc4::IfcDoorPanelProperties(std::move(data));
    case 297:
      return new ::Ifc4::IfcDoorStandardCase(std::move(data));
    case 298:
      return new ::Ifc4::IfcDoorStyle(std::move(data));
    case 299:
      return new ::Ifc4::IfcDoorStyleConstructionEnum(std::move(data));
    case 300:
      return new ::Ifc4::IfcDoorStyleOperationEnum(std::move(data));
    case 301:
      return new ::Ifc4::IfcDoorType(std::move(data));
    case 302:
      return new ::Ifc4::IfcDoorTypeEnum(std::move(data));
    case 303:
      return new ::Ifc4::IfcDoorTypeOperationEnum(std::move(data));
    case 304:
      return new ::Ifc4::IfcDoseEquivalentMeasure(std::move(data));
    case 305:
      return new ::Ifc4::IfcDraughtingPreDefinedColour(std::move(data));
    case 306:
      return new ::Ifc4::IfcDraughtingPreDefinedCurveFont(std::move(data));
    case 307:
      return new ::Ifc4::IfcDuctFitting(std::move(data));
    case 308:
      return new ::Ifc4::IfcDuctFittingType(std::move(data));
    case 309:
      return new ::Ifc4::IfcDuctFittingTypeEnum(std::move(data));
    case 310:
      return new ::Ifc4::IfcDuctSegment(std::move(data));
    case 311:
      return new ::Ifc4::IfcDuctSegmentType(std::move(data));
    case 312:
      return new ::Ifc4::IfcDuctSegmentTypeEnum(std::move(data));
    case 313:
      return new ::Ifc4::IfcDuctSilencer(std::move(data));
    case 314:
      return new ::Ifc4::IfcDuctSilencerType(std::move(data));
    case 315:
      return new ::Ifc4::IfcDuctSilencerTypeEnum(std::move(data));
    case 316:
      return new ::Ifc4::IfcDuration(std::move(data));
    case 317:
      return new ::Ifc4::IfcDynamicViscosityMeasure(std::move(data));
    case 318:
      return new ::Ifc4::IfcEdge(std::move(data));
    case 319:
      return new ::Ifc4::IfcEdgeCurve(std::move(data));
    case 320:
      return new ::Ifc4::IfcEdgeLoop(std::move(data));
    case 321:
      return new ::Ifc4::IfcElectricAppliance(std::move(data));
    case 322:
      return new ::Ifc4::IfcElectricApplianceType(std::move(data));
    case 323:
      return new ::Ifc4::IfcElectricApplianceTypeEnum(std::move(data));
    case 324:
      return new ::Ifc4::IfcElectricCapacitanceMeasure(std::move(data));
    case 325:
      return new ::Ifc4::IfcElectricChargeMeasure(std::move(data));
    case 326:
      return new ::Ifc4::IfcElectricConductanceMeasure(std::move(data));
    case 327:
      return new ::Ifc4::IfcElectricCurrentMeasure(std::move(data));
    case 328:
      return new ::Ifc4::IfcElectricDistributionBoard(std::move(data));
    case 329:
      return new ::Ifc4::IfcElectricDistributionBoardType(std::move(data));
    case 330:
      return new ::Ifc4::IfcElectricDistributionBoardTypeEnum(std::move(data));
    case 331:
      return new ::Ifc4::IfcElectricFlowStorageDevice(std::move(data));
    case 332:
      return new ::Ifc4::IfcElectricFlowStorageDeviceType(std::move(data));
    case 333:
      return new ::Ifc4::IfcElectricFlowStorageDeviceTypeEnum(std::move(data));
    case 334:
      return new ::Ifc4::IfcElectricGenerator(std::move(data));
    case 335:
      return new ::Ifc4::IfcElectricGeneratorType(std::move(data));
    case 336:
      return new ::Ifc4::IfcElectricGeneratorTypeEnum(std::move(data));
    case 337:
      return new ::Ifc4::IfcElectricMotor(std::move(data));
    case 338:
      return new ::Ifc4::IfcElectricMotorType(std::move(data));
    case 339:
      return new ::Ifc4::IfcElectricMotorTypeEnum(std::move(data));
    case 340:
      return new ::Ifc4::IfcElectricResistanceMeasure(std::move(data));
    case 341:
      return new ::Ifc4::IfcElectricTimeControl(std::move(data));
    case 342:
      return new ::Ifc4::IfcElectricTimeControlType(std::move(data));
    case 343:
      return new ::Ifc4::IfcElectricTimeControlTypeEnum(std::move(data));
    case 344:
      return new ::Ifc4::IfcElectricVoltageMeasure(std::move(data));
    case 345:
      return new ::Ifc4::IfcElement(std::move(data));
    case 346:
      return new ::Ifc4::IfcElementarySurface(std::move(data));
    case 347:
      return new ::Ifc4::IfcElementAssembly(std::move(data));
    case 348:
      return new ::Ifc4::IfcElementAssemblyType(std::move(data));
    case 349:
      return new ::Ifc4::IfcElementAssemblyTypeEnum(std::move(data));
    case 350:
      return new ::Ifc4::IfcElementComponent(std::move(data));
    case 351:
      return new ::Ifc4::IfcElementComponentType(std::move(data));
    case 352:
      return new ::Ifc4::IfcElementCompositionEnum(std::move(data));
    case 353:
      return new ::Ifc4::IfcElementQuantity(std::move(data));
    case 354:
      return new ::Ifc4::IfcElementType(std::move(data));
    case 355:
      return new ::Ifc4::IfcEllipse(std::move(data));
    case 356:
      return new ::Ifc4::IfcEllipseProfileDef(std::move(data));
    case 357:
      return new ::Ifc4::IfcEnergyConversionDevice(std::move(data));
    case 358:
      return new ::Ifc4::IfcEnergyConversionDeviceType(std::move(data));
    case 359:
      return new ::Ifc4::IfcEnergyMeasure(std::move(data));
    case 360:
      return new ::Ifc4::IfcEngine(std::move(data));
    case 361:
      return new ::Ifc4::IfcEngineType(std::move(data));
    case 362:
      return new ::Ifc4::IfcEngineTypeEnum(std::move(data));
    case 363:
      return new ::Ifc4::IfcEvaporativeCooler(std::move(data));
    case 364:
      return new ::Ifc4::IfcEvaporativeCoolerType(std::move(data));
    case 365:
      return new ::Ifc4::IfcEvaporativeCoolerTypeEnum(std::move(data));
    case 366:
      return new ::Ifc4::IfcEvaporator(std::move(data));
    case 367:
      return new ::Ifc4::IfcEvaporatorType(std::move(data));
    case 368:
      return new ::Ifc4::IfcEvaporatorTypeEnum(std::move(data));
    case 369:
      return new ::Ifc4::IfcEvent(std::move(data));
    case 370:
      return new ::Ifc4::IfcEventTime(std::move(data));
    case 371:
      return new ::Ifc4::IfcEventTriggerTypeEnum(std::move(data));
    case 372:
      return new ::Ifc4::IfcEventType(std::move(data));
    case 373:
      return new ::Ifc4::IfcEventTypeEnum(std::move(data));
    case 374:
      return new ::Ifc4::IfcExtendedProperties(std::move(data));
    case 375:
      return new ::Ifc4::IfcExternalInformation(std::move(data));
    case 376:
      return new ::Ifc4::IfcExternallyDefinedHatchStyle(std::move(data));
    case 377:
      return new ::Ifc4::IfcExternallyDefinedSurfaceStyle(std::move(data));
    case 378:
      return new ::Ifc4::IfcExternallyDefinedTextFont(std::move(data));
    case 379:
      return new ::Ifc4::IfcExternalReference(std::move(data));
    case 380:
      return new ::Ifc4::IfcExternalReferenceRelationship(std::move(data));
    case 381:
      return new ::Ifc4::IfcExternalSpatialElement(std::move(data));
    case 382:
      return new ::Ifc4::IfcExternalSpatialElementTypeEnum(std::move(data));
    case 383:
      return new ::Ifc4::IfcExternalSpatialStructureElement(std::move(data));
    case 384:
      return new ::Ifc4::IfcExtrudedAreaSolid(std::move(data));
    case 385:
      return new ::Ifc4::IfcExtrudedAreaSolidTapered(std::move(data));
    case 386:
      return new ::Ifc4::IfcFace(std::move(data));
    case 387:
      return new ::Ifc4::IfcFaceBasedSurfaceModel(std::move(data));
    case 388:
      return new ::Ifc4::IfcFaceBound(std::move(data));
    case 389:
      return new ::Ifc4::IfcFaceOuterBound(std::move(data));
    case 390:
      return new ::Ifc4::IfcFaceSurface(std::move(data));
    case 391:
      return new ::Ifc4::IfcFacetedBrep(std::move(data));
    case 392:
      return new ::Ifc4::IfcFacetedBrepWithVoids(std::move(data));
    case 393:
      return new ::Ifc4::IfcFailureConnectionCondition(std::move(data));
    case 394:
      return new ::Ifc4::IfcFan(std::move(data));
    case 395:
      return new ::Ifc4::IfcFanType(std::move(data));
    case 396:
      return new ::Ifc4::IfcFanTypeEnum(std::move(data));
    case 397:
      return new ::Ifc4::IfcFastener(std::move(data));
    case 398:
      return new ::Ifc4::IfcFastenerType(std::move(data));
    case 399:
      return new ::Ifc4::IfcFastenerTypeEnum(std::move(data));
    case 400:
      return new ::Ifc4::IfcFeatureElement(std::move(data));
    case 401:
      return new ::Ifc4::IfcFeatureElementAddition(std::move(data));
    case 402:
      return new ::Ifc4::IfcFeatureElementSubtraction(std::move(data));
    case 403:
      return new ::Ifc4::IfcFillAreaStyle(std::move(data));
    case 404:
      return new ::Ifc4::IfcFillAreaStyleHatching(std::move(data));
    case 405:
      return new ::Ifc4::IfcFillAreaStyleTiles(std::move(data));
    case 407:
      return new ::Ifc4::IfcFilter(std::move(data));
    case 408:
      return new ::Ifc4::IfcFilterType(std::move(data));
    case 409:
      return new ::Ifc4::IfcFilterTypeEnum(std::move(data));
    case 410:
      return new ::Ifc4::IfcFireSuppressionTerminal(std::move(data));
    case 411:
      return new ::Ifc4::IfcFireSuppressionTerminalType(std::move(data));
    case 412:
      return new ::Ifc4::IfcFireSuppressionTerminalTypeEnum(std::move(data));
    case 413:
      return new ::Ifc4::IfcFixedReferenceSweptAreaSolid(std::move(data));
    case 414:
      return new ::Ifc4::IfcFlowController(std::move(data));
    case 415:
      return new ::Ifc4::IfcFlowControllerType(std::move(data));
    case 416:
      return new ::Ifc4::IfcFlowDirectionEnum(std::move(data));
    case 417:
      return new ::Ifc4::IfcFlowFitting(std::move(data));
    case 418:
      return new ::Ifc4::IfcFlowFittingType(std::move(data));
    case 419:
      return new ::Ifc4::IfcFlowInstrument(std::move(data));
    case 420:
      return new ::Ifc4::IfcFlowInstrumentType(std::move(data));
    case 421:
      return new ::Ifc4::IfcFlowInstrumentTypeEnum(std::move(data));
    case 422:
      return new ::Ifc4::IfcFlowMeter(std::move(data));
    case 423:
      return new ::Ifc4::IfcFlowMeterType(std::move(data));
    case 424:
      return new ::Ifc4::IfcFlowMeterTypeEnum(std::move(data));
    case 425:
      return new ::Ifc4::IfcFlowMovingDevice(std::move(data));
    case 426:
      return new ::Ifc4::IfcFlowMovingDeviceType(std::move(data));
    case 427:
      return new ::Ifc4::IfcFlowSegment(std::move(data));
    case 428:
      return new ::Ifc4::IfcFlowSegmentType(std::move(data));
    case 429:
      return new ::Ifc4::IfcFlowStorageDevice(std::move(data));
    case 430:
      return new ::Ifc4::IfcFlowStorageDeviceType(std::move(data));
    case 431:
      return new ::Ifc4::IfcFlowTerminal(std::move(data));
    case 432:
      return new ::Ifc4::IfcFlowTerminalType(std::move(data));
    case 433:
      return new ::Ifc4::IfcFlowTreatmentDevice(std::move(data));
    case 434:
      return new ::Ifc4::IfcFlowTreatmentDeviceType(std::move(data));
    case 435:
      return new ::Ifc4::IfcFontStyle(std::move(data));
    case 436:
      return new ::Ifc4::IfcFontVariant(std::move(data));
    case 437:
      return new ::Ifc4::IfcFontWeight(std::move(data));
    case 438:
      return new ::Ifc4::IfcFooting(std::move(data));
    case 439:
      return new ::Ifc4::IfcFootingType(std::move(data));
    case 440:
      return new ::Ifc4::IfcFootingTypeEnum(std::move(data));
    case 441:
      return new ::Ifc4::IfcForceMeasure(std::move(data));
    case 442:
      return new ::Ifc4::IfcFrequencyMeasure(std::move(data));
    case 443:
      return new ::Ifc4::IfcFurnishingElement(std::move(data));
    case 444:
      return new ::Ifc4::IfcFurnishingElementType(std::move(data));
    case 445:
      return new ::Ifc4::IfcFurniture(std::move(data));
    case 446:
      return new ::Ifc4::IfcFurnitureType(std::move(data));
    case 447:
      return new ::Ifc4::IfcFurnitureTypeEnum(std::move(data));
    case 448:
      return new ::Ifc4::IfcGeographicElement(std::move(data));
    case 449:
      return new ::Ifc4::IfcGeographicElementType(std::move(data));
    case 450:
      return new ::Ifc4::IfcGeographicElementTypeEnum(std::move(data));
    case 451:
      return new ::Ifc4::IfcGeometricCurveSet(std::move(data));
    case 452:
      return new ::Ifc4::IfcGeometricProjectionEnum(std::move(data));
    case 453:
      return new ::Ifc4::IfcGeometricRepresentationContext(std::move(data));
    case 454:
      return new ::Ifc4::IfcGeometricRepresentationItem(std::move(data));
    case 455:
      return new ::Ifc4::IfcGeometricRepresentationSubContext(std::move(data));
    case 456:
      return new ::Ifc4::IfcGeometricSet(std::move(data));
    case 458:
      return new ::Ifc4::IfcGloballyUniqueId(std::move(data));
    case 459:
      return new ::Ifc4::IfcGlobalOrLocalEnum(std::move(data));
    case 460:
      return new ::Ifc4::IfcGrid(std::move(data));
    case 461:
      return new ::Ifc4::IfcGridAxis(std::move(data));
    case 462:
      return new ::Ifc4::IfcGridPlacement(std::move(data));
    case 464:
      return new ::Ifc4::IfcGridTypeEnum(std::move(data));
    case 465:
      return new ::Ifc4::IfcGroup(std::move(data));
    case 466:
      return new ::Ifc4::IfcHalfSpaceSolid(std::move(data));
    case 468:
      return new ::Ifc4::IfcHeatExchanger(std::move(data));
    case 469:
      return new ::Ifc4::IfcHeatExchangerType(std::move(data));
    case 470:
      return new ::Ifc4::IfcHeatExchangerTypeEnum(std::move(data));
    case 471:
      return new ::Ifc4::IfcHeatFluxDensityMeasure(std::move(data));
    case 472:
      return new ::Ifc4::IfcHeatingValueMeasure(std::move(data));
    case 473:
      return new ::Ifc4::IfcHumidifier(std::move(data));
    case 474:
      return new ::Ifc4::IfcHumidifierType(std::move(data));
    case 475:
      return new ::Ifc4::IfcHumidifierTypeEnum(std::move(data));
    case 476:
      return new ::Ifc4::IfcIdentifier(std::move(data));
    case 477:
      return new ::Ifc4::IfcIlluminanceMeasure(std::move(data));
    case 478:
      return new ::Ifc4::IfcImageTexture(std::move(data));
    case 479:
      return new ::Ifc4::IfcIndexedColourMap(std::move(data));
    case 480:
      return new ::Ifc4::IfcIndexedPolyCurve(std::move(data));
    case 481:
      return new ::Ifc4::IfcIndexedPolygonalFace(std::move(data));
    case 482:
      return new ::Ifc4::IfcIndexedPolygonalFaceWithVoids(std::move(data));
    case 483:
      return new ::Ifc4::IfcIndexedTextureMap(std::move(data));
    case 484:
      return new ::Ifc4::IfcIndexedTriangleTextureMap(std::move(data));
    case 485:
      return new ::Ifc4::IfcInductanceMeasure(std::move(data));
    case 486:
      return new ::Ifc4::IfcInteger(std::move(data));
    case 487:
      return new ::Ifc4::IfcIntegerCountRateMeasure(std::move(data));
    case 488:
      return new ::Ifc4::IfcInterceptor(std::move(data));
    case 489:
      return new ::Ifc4::IfcInterceptorType(std::move(data));
    case 490:
      return new ::Ifc4::IfcInterceptorTypeEnum(std::move(data));
    case 491:
      return new ::Ifc4::IfcInternalOrExternalEnum(std::move(data));
    case 492:
      return new ::Ifc4::IfcIntersectionCurve(std::move(data));
    case 493:
      return new ::Ifc4::IfcInventory(std::move(data));
    case 494:
      return new ::Ifc4::IfcInventoryTypeEnum(std::move(data));
    case 495:
      return new ::Ifc4::IfcIonConcentrationMeasure(std::move(data));
    case 496:
      return new ::Ifc4::IfcIrregularTimeSeries(std::move(data));
    case 497:
      return new ::Ifc4::IfcIrregularTimeSeriesValue(std::move(data));
    case 498:
      return new ::Ifc4::IfcIShapeProfileDef(std::move(data));
    case 499:
      return new ::Ifc4::IfcIsothermalMoistureCapacityMeasure(std::move(data));
    case 500:
      return new ::Ifc4::IfcJunctionBox(std::move(data));
    case 501:
      return new ::Ifc4::IfcJunctionBoxType(std::move(data));
    case 502:
      return new ::Ifc4::IfcJunctionBoxTypeEnum(std::move(data));
    case 503:
      return new ::Ifc4::IfcKinematicViscosityMeasure(std::move(data));
    case 504:
      return new ::Ifc4::IfcKnotType(std::move(data));
    case 505:
      return new ::Ifc4::IfcLabel(std::move(data));
    case 506:
      return new ::Ifc4::IfcLaborResource(std::move(data));
    case 507:
      return new ::Ifc4::IfcLaborResourceType(std::move(data));
    case 508:
      return new ::Ifc4::IfcLaborResourceTypeEnum(std::move(data));
    case 509:
      return new ::Ifc4::IfcLagTime(std::move(data));
    case 510:
      return new ::Ifc4::IfcLamp(std::move(data));
    case 511:
      return new ::Ifc4::IfcLampType(std::move(data));
    case 512:
      return new ::Ifc4::IfcLampTypeEnum(std::move(data));
    case 513:
      return new ::Ifc4::IfcLanguageId(std::move(data));
    case 515:
      return new ::Ifc4::IfcLayerSetDirectionEnum(std::move(data));
    case 516:
      return new ::Ifc4::IfcLengthMeasure(std::move(data));
    case 517:
      return new ::Ifc4::IfcLibraryInformation(std::move(data));
    case 518:
      return new ::Ifc4::IfcLibraryReference(std::move(data));
    case 520:
      return new ::Ifc4::IfcLightDistributionCurveEnum(std::move(data));
    case 521:
      return new ::Ifc4::IfcLightDistributionData(std::move(data));
    case 523:
      return new ::Ifc4::IfcLightEmissionSourceEnum(std::move(data));
    case 524:
      return new ::Ifc4::IfcLightFixture(std::move(data));
    case 525:
      return new ::Ifc4::IfcLightFixtureType(std::move(data));
    case 526:
      return new ::Ifc4::IfcLightFixtureTypeEnum(std::move(data));
    case 527:
      return new ::Ifc4::IfcLightIntensityDistribution(std::move(data));
    case 528:
      return new ::Ifc4::IfcLightSource(std::move(data));
    case 529:
      return new ::Ifc4::IfcLightSourceAmbient(std::move(data));
    case 530:
      return new ::Ifc4::IfcLightSourceDirectional(std::move(data));
    case 531:
      return new ::Ifc4::IfcLightSourceGoniometric(std::move(data));
    case 532:
      return new ::Ifc4::IfcLightSourcePositional(std::move(data));
    case 533:
      return new ::Ifc4::IfcLightSourceSpot(std::move(data));
    case 534:
      return new ::Ifc4::IfcLine(std::move(data));
    case 535:
      return new ::Ifc4::IfcLinearForceMeasure(std::move(data));
    case 536:
      return new ::Ifc4::IfcLinearMomentMeasure(std::move(data));
    case 537:
      return new ::Ifc4::IfcLinearStiffnessMeasure(std::move(data));
    case 538:
      return new ::Ifc4::IfcLinearVelocityMeasure(std::move(data));
    case 539:
      return new ::Ifc4::IfcLineIndex(std::move(data));
    case 540:
      return new ::Ifc4::IfcLoadGroupTypeEnum(std::move(data));
    case 541:
      return new ::Ifc4::IfcLocalPlacement(std::move(data));
    case 542:
      return new ::Ifc4::IfcLogical(std::move(data));
    case 543:
      return new ::Ifc4::IfcLogicalOperatorEnum(std::move(data));
    case 544:
      return new ::Ifc4::IfcLoop(std::move(data));
    case 545:
      return new ::Ifc4::IfcLShapeProfileDef(std::move(data));
    case 546:
      return new ::Ifc4::IfcLuminousFluxMeasure(std::move(data));
    case 547:
      return new ::Ifc4::IfcLuminousIntensityDistributionMeasure(
          std::move(data));
    case 548:
      return new ::Ifc4::IfcLuminousIntensityMeasure(std::move(data));
    case 549:
      return new ::Ifc4::IfcMagneticFluxDensityMeasure(std::move(data));
    case 550:
      return new ::Ifc4::IfcMagneticFluxMeasure(std::move(data));
    case 551:
      return new ::Ifc4::IfcManifoldSolidBrep(std::move(data));
    case 552:
      return new ::Ifc4::IfcMapConversion(std::move(data));
    case 553:
      return new ::Ifc4::IfcMappedItem(std::move(data));
    case 554:
      return new ::Ifc4::IfcMassDensityMeasure(std::move(data));
    case 555:
      return new ::Ifc4::IfcMassFlowRateMeasure(std::move(data));
    case 556:
      return new ::Ifc4::IfcMassMeasure(std::move(data));
    case 557:
      return new ::Ifc4::IfcMassPerLengthMeasure(std::move(data));
    case 558:
      return new ::Ifc4::IfcMaterial(std::move(data));
    case 559:
      return new ::Ifc4::IfcMaterialClassificationRelationship(std::move(data));
    case 560:
      return new ::Ifc4::IfcMaterialConstituent(std::move(data));
    case 561:
      return new ::Ifc4::IfcMaterialConstituentSet(std::move(data));
    case 562:
      return new ::Ifc4::IfcMaterialDefinition(std::move(data));
    case 563:
      return new ::Ifc4::IfcMaterialDefinitionRepresentation(std::move(data));
    case 564:
      return new ::Ifc4::IfcMaterialLayer(std::move(data));
    case 565:
      return new ::Ifc4::IfcMaterialLayerSet(std::move(data));
    case 566:
      return new ::Ifc4::IfcMaterialLayerSetUsage(std::move(data));
    case 567:
      return new ::Ifc4::IfcMaterialLayerWithOffsets(std::move(data));
    case 568:
      return new ::Ifc4::IfcMaterialList(std::move(data));
    case 569:
      return new ::Ifc4::IfcMaterialProfile(std::move(data));
    case 570:
      return new ::Ifc4::IfcMaterialProfileSet(std::move(data));
    case 571:
      return new ::Ifc4::IfcMaterialProfileSetUsage(std::move(data));
    case 572:
      return new ::Ifc4::IfcMaterialProfileSetUsageTapering(std::move(data));
    case 573:
      return new ::Ifc4::IfcMaterialProfileWithOffsets(std::move(data));
    case 574:
      return new ::Ifc4::IfcMaterialProperties(std::move(data));
    case 575:
      return new ::Ifc4::IfcMaterialRelationship(std::move(data));
    case 577:
      return new ::Ifc4::IfcMaterialUsageDefinition(std::move(data));
    case 579:
      return new ::Ifc4::IfcMeasureWithUnit(std::move(data));
    case 580:
      return new ::Ifc4::IfcMechanicalFastener(std::move(data));
    case 581:
      return new ::Ifc4::IfcMechanicalFastenerType(std::move(data));
    case 582:
      return new ::Ifc4::IfcMechanicalFastenerTypeEnum(std::move(data));
    case 583:
      return new ::Ifc4::IfcMedicalDevice(std::move(data));
    case 584:
      return new ::Ifc4::IfcMedicalDeviceType(std::move(data));
    case 585:
      return new ::Ifc4::IfcMedicalDeviceTypeEnum(std::move(data));
    case 586:
      return new ::Ifc4::IfcMember(std::move(data));
    case 587:
      return new ::Ifc4::IfcMemberStandardCase(std::move(data));
    case 588:
      return new ::Ifc4::IfcMemberType(std::move(data));
    case 589:
      return new ::Ifc4::IfcMemberTypeEnum(std::move(data));
    case 590:
      return new ::Ifc4::IfcMetric(std::move(data));
    case 592:
      return new ::Ifc4::IfcMirroredProfileDef(std::move(data));
    case 593:
      return new ::Ifc4::IfcModulusOfElasticityMeasure(std::move(data));
    case 594:
      return new ::Ifc4::IfcModulusOfLinearSubgradeReactionMeasure(
          std::move(data));
    case 595:
      return new ::Ifc4::IfcModulusOfRotationalSubgradeReactionMeasure(
          std::move(data));
    case 597:
      return new ::Ifc4::IfcModulusOfSubgradeReactionMeasure(std::move(data));
    case 600:
      return new ::Ifc4::IfcMoistureDiffusivityMeasure(std::move(data));
    case 601:
      return new ::Ifc4::IfcMolecularWeightMeasure(std::move(data));
    case 602:
      return new ::Ifc4::IfcMomentOfInertiaMeasure(std::move(data));
    case 603:
      return new ::Ifc4::IfcMonetaryMeasure(std::move(data));
    case 604:
      return new ::Ifc4::IfcMonetaryUnit(std::move(data));
    case 605:
      return new ::Ifc4::IfcMonthInYearNumber(std::move(data));
    case 606:
      return new ::Ifc4::IfcMotorConnection(std::move(data));
    case 607:
      return new ::Ifc4::IfcMotorConnectionType(std::move(data));
    case 608:
      return new ::Ifc4::IfcMotorConnectionTypeEnum(std::move(data));
    case 609:
      return new ::Ifc4::IfcNamedUnit(std::move(data));
    case 610:
      return new ::Ifc4::IfcNonNegativeLengthMeasure(std::move(data));
    case 611:
      return new ::Ifc4::IfcNormalisedRatioMeasure(std::move(data));
    case 612:
      return new ::Ifc4::IfcNullStyle(std::move(data));
    case 613:
      return new ::Ifc4::IfcNumericMeasure(std::move(data));
    case 614:
      return new ::Ifc4::IfcObject(std::move(data));
    case 615:
      return new ::Ifc4::IfcObjectDefinition(std::move(data));
    case 616:
      return new ::Ifc4::IfcObjective(std::move(data));
    case 617:
      return new ::Ifc4::IfcObjectiveEnum(std::move(data));
    case 618:
      return new ::Ifc4::IfcObjectPlacement(std::move(data));
    case 620:
      return new ::Ifc4::IfcObjectTypeEnum(std::move(data));
    case 621:
      return new ::Ifc4::IfcOccupant(std::move(data));
    case 622:
      return new ::Ifc4::IfcOccupantTypeEnum(std::move(data));
    case 623:
      return new ::Ifc4::IfcOffsetCurve2D(std::move(data));
    case 624:
      return new ::Ifc4::IfcOffsetCurve3D(std::move(data));
    case 625:
      return new ::Ifc4::IfcOpeningElement(std::move(data));
    case 626:
      return new ::Ifc4::IfcOpeningElementTypeEnum(std::move(data));
    case 627:
      return new ::Ifc4::IfcOpeningStandardCase(std::move(data));
    case 628:
      return new ::Ifc4::IfcOpenShell(std::move(data));
    case 629:
      return new ::Ifc4::IfcOrganization(std::move(data));
    case 630:
      return new ::Ifc4::IfcOrganizationRelationship(std::move(data));
    case 631:
      return new ::Ifc4::IfcOrientedEdge(std::move(data));
    case 632:
      return new ::Ifc4::IfcOuterBoundaryCurve(std::move(data));
    case 633:
      return new ::Ifc4::IfcOutlet(std::move(data));
    case 634:
      return new ::Ifc4::IfcOutletType(std::move(data));
    case 635:
      return new ::Ifc4::IfcOutletTypeEnum(std::move(data));
    case 636:
      return new ::Ifc4::IfcOwnerHistory(std::move(data));
    case 637:
      return new ::Ifc4::IfcParameterizedProfileDef(std::move(data));
    case 638:
      return new ::Ifc4::IfcParameterValue(std::move(data));
    case 639:
      return new ::Ifc4::IfcPath(std::move(data));
    case 640:
      return new ::Ifc4::IfcPcurve(std::move(data));
    case 641:
      return new ::Ifc4::IfcPerformanceHistory(std::move(data));
    case 642:
      return new ::Ifc4::IfcPerformanceHistoryTypeEnum(std::move(data));
    case 643:
      return new ::Ifc4::IfcPermeableCoveringOperationEnum(std::move(data));
    case 644:
      return new ::Ifc4::IfcPermeableCoveringProperties(std::move(data));
    case 645:
      return new ::Ifc4::IfcPermit(std::move(data));
    case 646:
      return new ::Ifc4::IfcPermitTypeEnum(std::move(data));
    case 647:
      return new ::Ifc4::IfcPerson(std::move(data));
    case 648:
      return new ::Ifc4::IfcPersonAndOrganization(std::move(data));
    case 649:
      return new ::Ifc4::IfcPHMeasure(std::move(data));
    case 650:
      return new ::Ifc4::IfcPhysicalComplexQuantity(std::move(data));
    case 651:
      return new ::Ifc4::IfcPhysicalOrVirtualEnum(std::move(data));
    case 652:
      return new ::Ifc4::IfcPhysicalQuantity(std::move(data));
    case 653:
      return new ::Ifc4::IfcPhysicalSimpleQuantity(std::move(data));
    case 654:
      return new ::Ifc4::IfcPile(std::move(data));
    case 655:
      return new ::Ifc4::IfcPileConstructionEnum(std::move(data));
    case 656:
      return new ::Ifc4::IfcPileType(std::move(data));
    case 657:
      return new ::Ifc4::IfcPileTypeEnum(std::move(data));
    case 658:
      return new ::Ifc4::IfcPipeFitting(std::move(data));
    case 659:
      return new ::Ifc4::IfcPipeFittingType(std::move(data));
    case 660:
      return new ::Ifc4::IfcPipeFittingTypeEnum(std::move(data));
    case 661:
      return new ::Ifc4::IfcPipeSegment(std::move(data));
    case 662:
      return new ::Ifc4::IfcPipeSegmentType(std::move(data));
    case 663:
      return new ::Ifc4::IfcPipeSegmentTypeEnum(std::move(data));
    case 664:
      return new ::Ifc4::IfcPixelTexture(std::move(data));
    case 665:
      return new ::Ifc4::IfcPlacement(std::move(data));
    case 666:
      return new ::Ifc4::IfcPlanarBox(std::move(data));
    case 667:
      return new ::Ifc4::IfcPlanarExtent(std::move(data));
    case 668:
      return new ::Ifc4::IfcPlanarForceMeasure(std::move(data));
    case 669:
      return new ::Ifc4::IfcPlane(std::move(data));
    case 670:
      return new ::Ifc4::IfcPlaneAngleMeasure(std::move(data));
    case 671:
      return new ::Ifc4::IfcPlate(std::move(data));
    case 672:
      return new ::Ifc4::IfcPlateStandardCase(std::move(data));
    case 673:
      return new ::Ifc4::IfcPlateType(std::move(data));
    case 674:
      return new ::Ifc4::IfcPlateTypeEnum(std::move(data));
    case 675:
      return new ::Ifc4::IfcPoint(std::move(data));
    case 676:
      return new ::Ifc4::IfcPointOnCurve(std::move(data));
    case 677:
      return new ::Ifc4::IfcPointOnSurface(std::move(data));
    case 679:
      return new ::Ifc4::IfcPolygonalBoundedHalfSpace(std::move(data));
    case 680:
      return new ::Ifc4::IfcPolygonalFaceSet(std::move(data));
    case 681:
      return new ::Ifc4::IfcPolyline(std::move(data));
    case 682:
      return new ::Ifc4::IfcPolyLoop(std::move(data));
    case 683:
      return new ::Ifc4::IfcPort(std::move(data));
    case 684:
      return new ::Ifc4::IfcPositiveInteger(std::move(data));
    case 685:
      return new ::Ifc4::IfcPositiveLengthMeasure(std::move(data));
    case 686:
      return new ::Ifc4::IfcPositivePlaneAngleMeasure(std::move(data));
    case 687:
      return new ::Ifc4::IfcPositiveRatioMeasure(std::move(data));
    case 688:
      return new ::Ifc4::IfcPostalAddress(std::move(data));
    case 689:
      return new ::Ifc4::IfcPowerMeasure(std::move(data));
    case 690:
      return new ::Ifc4::IfcPreDefinedColour(std::move(data));
    case 691:
      return new ::Ifc4::IfcPreDefinedCurveFont(std::move(data));
    case 692:
      return new ::Ifc4::IfcPreDefinedItem(std::move(data));
    case 693:
      return new ::Ifc4::IfcPreDefinedProperties(std::move(data));
    case 694:
      return new ::Ifc4::IfcPreDefinedPropertySet(std::move(data));
    case 695:
      return new ::Ifc4::IfcPreDefinedTextFont(std::move(data));
    case 696:
      return new ::Ifc4::IfcPreferredSurfaceCurveRepresentation(
          std::move(data));
    case 697:
      return new ::Ifc4::IfcPresentableText(std::move(data));
    case 698:
      return new ::Ifc4::IfcPresentationItem(std::move(data));
    case 699:
      return new ::Ifc4::IfcPresentationLayerAssignment(std::move(data));
    case 700:
      return new ::Ifc4::IfcPresentationLayerWithStyle(std::move(data));
    case 701:
      return new ::Ifc4::IfcPresentationStyle(std::move(data));
    case 702:
      return new ::Ifc4::IfcPresentationStyleAssignment(std::move(data));
    case 704:
      return new ::Ifc4::IfcPressureMeasure(std::move(data));
    case 705:
      return new ::Ifc4::IfcProcedure(std::move(data));
    case 706:
      return new ::Ifc4::IfcProcedureType(std::move(data));
    case 707:
      return new ::Ifc4::IfcProcedureTypeEnum(std::move(data));
    case 708:
      return new ::Ifc4::IfcProcess(std::move(data));
    case 710:
      return new ::Ifc4::IfcProduct(std::move(data));
    case 711:
      return new ::Ifc4::IfcProductDefinitionShape(std::move(data));
    case 712:
      return new ::Ifc4::IfcProductRepresentation(std::move(data));
    case 715:
      return new ::Ifc4::IfcProfileDef(std::move(data));
    case 716:
      return new ::Ifc4::IfcProfileProperties(std::move(data));
    case 717:
      return new ::Ifc4::IfcProfileTypeEnum(std::move(data));
    case 718:
      return new ::Ifc4::IfcProject(std::move(data));
    case 719:
      return new ::Ifc4::IfcProjectedCRS(std::move(data));
    case 720:
      return new ::Ifc4::IfcProjectedOrTrueLengthEnum(std::move(data));
    case 721:
      return new ::Ifc4::IfcProjectionElement(std::move(data));
    case 722:
      return new ::Ifc4::IfcProjectionElementTypeEnum(std::move(data));
    case 723:
      return new ::Ifc4::IfcProjectLibrary(std::move(data));
    case 724:
      return new ::Ifc4::IfcProjectOrder(std::move(data));
    case 725:
      return new ::Ifc4::IfcProjectOrderTypeEnum(std::move(data));
    case 726:
      return new ::Ifc4::IfcProperty(std::move(data));
    case 727:
      return new ::Ifc4::IfcPropertyAbstraction(std::move(data));
    case 728:
      return new ::Ifc4::IfcPropertyBoundedValue(std::move(data));
    case 729:
      return new ::Ifc4::IfcPropertyDefinition(std::move(data));
    case 730:
      return new ::Ifc4::IfcPropertyDependencyRelationship(std::move(data));
    case 731:
      return new ::Ifc4::IfcPropertyEnumeratedValue(std::move(data));
    case 732:
      return new ::Ifc4::IfcPropertyEnumeration(std::move(data));
    case 733:
      return new ::Ifc4::IfcPropertyListValue(std::move(data));
    case 734:
      return new ::Ifc4::IfcPropertyReferenceValue(std::move(data));
    case 735:
      return new ::Ifc4::IfcPropertySet(std::move(data));
    case 736:
      return new ::Ifc4::IfcPropertySetDefinition(std::move(data));
    case 738:
      return new ::Ifc4::IfcPropertySetDefinitionSet(std::move(data));
    case 739:
      return new ::Ifc4::IfcPropertySetTemplate(std::move(data));
    case 740:
      return new ::Ifc4::IfcPropertySetTemplateTypeEnum(std::move(data));
    case 741:
      return new ::Ifc4::IfcPropertySingleValue(std::move(data));
    case 742:
      return new ::Ifc4::IfcPropertyTableValue(std::move(data));
    case 743:
      return new ::Ifc4::IfcPropertyTemplate(std::move(data));
    case 744:
      return new ::Ifc4::IfcPropertyTemplateDefinition(std::move(data));
    case 745:
      return new ::Ifc4::IfcProtectiveDevice(std::move(data));
    case 746:
      return new ::Ifc4::IfcProtectiveDeviceTrippingUnit(std::move(data));
    case 747:
      return new ::Ifc4::IfcProtectiveDeviceTrippingUnitType(std::move(data));
    case 748:
      return new ::Ifc4::IfcProtectiveDeviceTrippingUnitTypeEnum(
          std::move(data));
    case 749:
      return new ::Ifc4::IfcProtectiveDeviceType(std::move(data));
    case 750:
      return new ::Ifc4::IfcProtectiveDeviceTypeEnum(std::move(data));
    case 751:
      return new ::Ifc4::IfcProxy(std::move(data));
    case 752:
      return new ::Ifc4::IfcPump(std::move(data));
    case 753:
      return new ::Ifc4::IfcPumpType(std::move(data));
    case 754:
      return new ::Ifc4::IfcPumpTypeEnum(std::move(data));
    case 755:
      return new ::Ifc4::IfcQuantityArea(std::move(data));
    case 756:
      return new ::Ifc4::IfcQuantityCount(std::move(data));
    case 757:
      return new ::Ifc4::IfcQuantityLength(std::move(data));
    case 758:
      return new ::Ifc4::IfcQuantitySet(std::move(data));
    case 759:
      return new ::Ifc4::IfcQuantityTime(std::move(data));
    case 760:
      return new ::Ifc4::IfcQuantityVolume(std::move(data));
    case 761:
      return new ::Ifc4::IfcQuantityWeight(std::move(data));
    case 762:
      return new ::Ifc4::IfcRadioActivityMeasure(std::move(data));
    case 763:
      return new ::Ifc4::IfcRailing(std::move(data));
    case 764:
      return new ::Ifc4::IfcRailingType(std::move(data));
    case 765:
      return new ::Ifc4::IfcRailingTypeEnum(std::move(data));
    case 766:
      return new ::Ifc4::IfcRamp(std::move(data));
    case 767:
      return new ::Ifc4::IfcRampFlight(std::move(data));
    case 768:
      return new ::Ifc4::IfcRampFlightType(std::move(data));
    case 769:
      return new ::Ifc4::IfcRampFlightTypeEnum(std::move(data));
    case 770:
      return new ::Ifc4::IfcRampType(std::move(data));
    case 771:
      return new ::Ifc4::IfcRampTypeEnum(std::move(data));
    case 772:
      return new ::Ifc4::IfcRatioMeasure(std::move(data));
    case 773:
      return new ::Ifc4::IfcRationalBSplineCurveWithKnots(std::move(data));
    case 774:
      return new ::Ifc4::IfcRationalBSplineSurfaceWithKnots(std::move(data));
    case 775:
      return new ::Ifc4::IfcReal(std::move(data));
    case 776:
      return new ::Ifc4::IfcRectangleHollowProfileDef(std::move(data));
    case 777:
      return new ::Ifc4::IfcRectangleProfileDef(std::move(data));
    case 778:
      return new ::Ifc4::IfcRectangularPyramid(std::move(data));
    case 779:
      return new ::Ifc4::IfcRectangularTrimmedSurface(std::move(data));
    case 780:
      return new ::Ifc4::IfcRecurrencePattern(std::move(data));
    case 781:
      return new ::Ifc4::IfcRecurrenceTypeEnum(std::move(data));
    case 782:
      return new ::Ifc4::IfcReference(std::move(data));
    case 783:
      return new ::Ifc4::IfcReflectanceMethodEnum(std::move(data));
    case 784:
      return new ::Ifc4::IfcRegularTimeSeries(std::move(data));
    case 785:
      return new ::Ifc4::IfcReinforcementBarProperties(std::move(data));
    case 786:
      return new ::Ifc4::IfcReinforcementDefinitionProperties(std::move(data));
    case 787:
      return new ::Ifc4::IfcReinforcingBar(std::move(data));
    case 788:
      return new ::Ifc4::IfcReinforcingBarRoleEnum(std::move(data));
    case 789:
      return new ::Ifc4::IfcReinforcingBarSurfaceEnum(std::move(data));
    case 790:
      return new ::Ifc4::IfcReinforcingBarType(std::move(data));
    case 791:
      return new ::Ifc4::IfcReinforcingBarTypeEnum(std::move(data));
    case 792:
      return new ::Ifc4::IfcReinforcingElement(std::move(data));
    case 793:
      return new ::Ifc4::IfcReinforcingElementType(std::move(data));
    case 794:
      return new ::Ifc4::IfcReinforcingMesh(std::move(data));
    case 795:
      return new ::Ifc4::IfcReinforcingMeshType(std::move(data));
    case 796:
      return new ::Ifc4::IfcReinforcingMeshTypeEnum(std::move(data));
    case 797:
      return new ::Ifc4::IfcRelAggregates(std::move(data));
    case 798:
      return new ::Ifc4::IfcRelAssigns(std::move(data));
    case 799:
      return new ::Ifc4::IfcRelAssignsToActor(std::move(data));
    case 800:
      return new ::Ifc4::IfcRelAssignsToControl(std::move(data));
    case 801:
      return new ::Ifc4::IfcRelAssignsToGroup(std::move(data));
    case 802:
      return new ::Ifc4::IfcRelAssignsToGroupByFactor(std::move(data));
    case 803:
      return new ::Ifc4::IfcRelAssignsToProcess(std::move(data));
    case 804:
      return new ::Ifc4::IfcRelAssignsToProduct(std::move(data));
    case 805:
      return new ::Ifc4::IfcRelAssignsToResource(std::move(data));
    case 806:
      return new ::Ifc4::IfcRelAssociates(std::move(data));
    case 807:
      return new ::Ifc4::IfcRelAssociatesApproval(std::move(data));
    case 808:
      return new ::Ifc4::IfcRelAssociatesClassification(std::move(data));
    case 809:
      return new ::Ifc4::IfcRelAssociatesConstraint(std::move(data));
    case 810:
      return new ::Ifc4::IfcRelAssociatesDocument(std::move(data));
    case 811:
      return new ::Ifc4::IfcRelAssociatesLibrary(std::move(data));
    case 812:
      return new ::Ifc4::IfcRelAssociatesMaterial(std::move(data));
    case 813:
      return new ::Ifc4::IfcRelationship(std::move(data));
    case 814:
      return new ::Ifc4::IfcRelConnects(std::move(data));
    case 815:
      return new ::Ifc4::IfcRelConnectsElements(std::move(data));
    case 816:
      return new ::Ifc4::IfcRelConnectsPathElements(std::move(data));
    case 817:
      return new ::Ifc4::IfcRelConnectsPorts(std::move(data));
    case 818:
      return new ::Ifc4::IfcRelConnectsPortToElement(std::move(data));
    case 819:
      return new ::Ifc4::IfcRelConnectsStructuralActivity(std::move(data));
    case 820:
      return new ::Ifc4::IfcRelConnectsStructuralMember(std::move(data));
    case 821:
      return new ::Ifc4::IfcRelConnectsWithEccentricity(std::move(data));
    case 822:
      return new ::Ifc4::IfcRelConnectsWithRealizingElements(std::move(data));
    case 823:
      return new ::Ifc4::IfcRelContainedInSpatialStructure(std::move(data));
    case 824:
      return new ::Ifc4::IfcRelCoversBldgElements(std::move(data));
    case 825:
      return new ::Ifc4::IfcRelCoversSpaces(std::move(data));
    case 826:
      return new ::Ifc4::IfcRelDeclares(std::move(data));
    case 827:
      return new ::Ifc4::IfcRelDecomposes(std::move(data));
    case 828:
      return new ::Ifc4::IfcRelDefines(std::move(data));
    case 829:
      return new ::Ifc4::IfcRelDefinesByObject(std::move(data));
    case 830:
      return new ::Ifc4::IfcRelDefinesByProperties(std::move(data));
    case 831:
      return new ::Ifc4::IfcRelDefinesByTemplate(std::move(data));
    case 832:
      return new ::Ifc4::IfcRelDefinesByType(std::move(data));
    case 833:
      return new ::Ifc4::IfcRelFillsElement(std::move(data));
    case 834:
      return new ::Ifc4::IfcRelFlowControlElements(std::move(data));
    case 835:
      return new ::Ifc4::IfcRelInterferesElements(std::move(data));
    case 836:
      return new ::Ifc4::IfcRelNests(std::move(data));
    case 837:
      return new ::Ifc4::IfcRelProjectsElement(std::move(data));
    case 838:
      return new ::Ifc4::IfcRelReferencedInSpatialStructure(std::move(data));
    case 839:
      return new ::Ifc4::IfcRelSequence(std::move(data));
    case 840:
      return new ::Ifc4::IfcRelServicesBuildings(std::move(data));
    case 841:
      return new ::Ifc4::IfcRelSpaceBoundary(std::move(data));
    case 842:
      return new ::Ifc4::IfcRelSpaceBoundary1stLevel(std::move(data));
    case 843:
      return new ::Ifc4::IfcRelSpaceBoundary2ndLevel(std::move(data));
    case 844:
      return new ::Ifc4::IfcRelVoidsElement(std::move(data));
    case 845:
      return new ::Ifc4::IfcReparametrisedCompositeCurveSegment(
          std::move(data));
    case 846:
      return new ::Ifc4::IfcRepresentation(std::move(data));
    case 847:
      return new ::Ifc4::IfcRepresentationContext(std::move(data));
    case 848:
      return new ::Ifc4::IfcRepresentationItem(std::move(data));
    case 849:
      return new ::Ifc4::IfcRepresentationMap(std::move(data));
    case 850:
      return new ::Ifc4::IfcResource(std::move(data));
    case 851:
      return new ::Ifc4::IfcResourceApprovalRelationship(std::move(data));
    case 852:
      return new ::Ifc4::IfcResourceConstraintRelationship(std::move(data));
    case 853:
      return new ::Ifc4::IfcResourceLevelRelationship(std::move(data));
    case 856:
      return new ::Ifc4::IfcResourceTime(std::move(data));
    case 857:
      return new ::Ifc4::IfcRevolvedAreaSolid(std::move(data));
    case 858:
      return new ::Ifc4::IfcRevolvedAreaSolidTapered(std::move(data));
    case 859:
      return new ::Ifc4::IfcRightCircularCone(std::move(data));
    case 860:
      return new ::Ifc4::IfcRightCircularCylinder(std::move(data));
    case 861:
      return new ::Ifc4::IfcRoleEnum(std::move(data));
    case 862:
      return new ::Ifc4::IfcRoof(std::move(data));
    case 863:
      return new ::Ifc4::IfcRoofType(std::move(data));
    case 864:
      return new ::Ifc4::IfcRoofTypeEnum(std::move(data));
    case 865:
      return new ::Ifc4::IfcRoot(std::move(data));
    case 866:
      return new ::Ifc4::IfcRotationalFrequencyMeasure(std::move(data));
    case 867:
      return new ::Ifc4::IfcRotationalMassMeasure(std::move(data));
    case 868:
      return new ::Ifc4::IfcRotationalStiffnessMeasure(std::move(data));
    case 870:
      return new ::Ifc4::IfcRoundedRectangleProfileDef(std::move(data));
    case 871:
      return new ::Ifc4::IfcSanitaryTerminal(std::move(data));
    case 872:
      return new ::Ifc4::IfcSanitaryTerminalType(std::move(data));
    case 873:
      return new ::Ifc4::IfcSanitaryTerminalTypeEnum(std::move(data));
    case 874:
      return new ::Ifc4::IfcSchedulingTime(std::move(data));
    case 875:
      return new ::Ifc4::IfcSeamCurve(std::move(data));
    case 876:
      return new ::Ifc4::IfcSectionalAreaIntegralMeasure(std::move(data));
    case 877:
      return new ::Ifc4::IfcSectionedSpine(std::move(data));
    case 878:
      return new ::Ifc4::IfcSectionModulusMeasure(std::move(data));
    case 879:
      return new ::Ifc4::IfcSectionProperties(std::move(data));
    case 880:
      return new ::Ifc4::IfcSectionReinforcementProperties(std::move(data));
    case 881:
      return new ::Ifc4::IfcSectionTypeEnum(std::move(data));
    case 883:
      return new ::Ifc4::IfcSensor(std::move(data));
    case 884:
      return new ::Ifc4::IfcSensorType(std::move(data));
    case 885:
      return new ::Ifc4::IfcSensorTypeEnum(std::move(data));
    case 886:
      return new ::Ifc4::IfcSequenceEnum(std::move(data));
    case 887:
      return new ::Ifc4::IfcShadingDevice(std::move(data));
    case 888:
      return new ::Ifc4::IfcShadingDeviceType(std::move(data));
    case 889:
      return new ::Ifc4::IfcShadingDeviceTypeEnum(std::move(data));
    case 890:
      return new ::Ifc4::IfcShapeAspect(std::move(data));
    case 891:
      return new ::Ifc4::IfcShapeModel(std::move(data));
    case 892:
      return new ::Ifc4::IfcShapeRepresentation(std::move(data));
    case 893:
      return new ::Ifc4::IfcShearModulusMeasure(std::move(data));
    case 895:
      return new ::Ifc4::IfcShellBasedSurfaceModel(std::move(data));
    case 896:
      return new ::Ifc4::IfcSimpleProperty(std::move(data));
    case 897:
      return new ::Ifc4::IfcSimplePropertyTemplate(std::move(data));
    case 898:
      return new ::Ifc4::IfcSimplePropertyTemplateTypeEnum(std::move(data));
    case 900:
      return new ::Ifc4::IfcSIPrefix(std::move(data));
    case 901:
      return new ::Ifc4::IfcSite(std::move(data));
    case 902:
      return new ::Ifc4::IfcSIUnit(std::move(data));
    case 903:
      return new ::Ifc4::IfcSIUnitName(std::move(data));
    case 905:
      return new ::Ifc4::IfcSlab(std::move(data));
    case 906:
      return new ::Ifc4::IfcSlabElementedCase(std::move(data));
    case 907:
      return new ::Ifc4::IfcSlabStandardCase(std::move(data));
    case 908:
      return new ::Ifc4::IfcSlabType(std::move(data));
    case 909:
      return new ::Ifc4::IfcSlabTypeEnum(std::move(data));
    case 910:
      return new ::Ifc4::IfcSlippageConnectionCondition(std::move(data));
    case 911:
      return new ::Ifc4::IfcSolarDevice(std::move(data));
    case 912:
      return new ::Ifc4::IfcSolarDeviceType(std::move(data));
    case 913:
      return new ::Ifc4::IfcSolarDeviceTypeEnum(std::move(data));
    case 914:
      return new ::Ifc4::IfcSolidAngleMeasure(std::move(data));
    case 915:
      return new ::Ifc4::IfcSolidModel(std::move(data));
    case 917:
      return new ::Ifc4::IfcSoundPowerLevelMeasure(std::move(data));
    case 918:
      return new ::Ifc4::IfcSoundPowerMeasure(std::move(data));
    case 919:
      return new ::Ifc4::IfcSoundPressureLevelMeasure(std::move(data));
    case 920:
      return new ::Ifc4::IfcSoundPressureMeasure(std::move(data));
    case 921:
      return new ::Ifc4::IfcSpace(std::move(data));
    case 923:
      return new ::Ifc4::IfcSpaceHeater(std::move(data));
    case 924:
      return new ::Ifc4::IfcSpaceHeaterType(std::move(data));
    case 925:
      return new ::Ifc4::IfcSpaceHeaterTypeEnum(std::move(data));
    case 926:
      return new ::Ifc4::IfcSpaceType(std::move(data));
    case 927:
      return new ::Ifc4::IfcSpaceTypeEnum(std::move(data));
    case 928:
      return new ::Ifc4::IfcSpatialElement(std::move(data));
    case 929:
      return new ::Ifc4::IfcSpatialElementType(std::move(data));
    case 930:
      return new ::Ifc4::IfcSpatialStructureElement(std::move(data));
    case 931:
      return new ::Ifc4::IfcSpatialStructureElementType(std::move(data));
    case 932:
      return new ::Ifc4::IfcSpatialZone(std::move(data));
    case 933:
      return new ::Ifc4::IfcSpatialZoneType(std::move(data));
    case 934:
      return new ::Ifc4::IfcSpatialZoneTypeEnum(std::move(data));
    case 935:
      return new ::Ifc4::IfcSpecificHeatCapacityMeasure(std::move(data));
    case 936:
      return new ::Ifc4::IfcSpecularExponent(std::move(data));
    case 938:
      return new ::Ifc4::IfcSpecularRoughness(std::move(data));
    case 939:
      return new ::Ifc4::IfcSphere(std::move(data));
    case 940:
      return new ::Ifc4::IfcSphericalSurface(std::move(data));
    case 941:
      return new ::Ifc4::IfcStackTerminal(std::move(data));
    case 942:
      return new ::Ifc4::IfcStackTerminalType(std::move(data));
    case 943:
      return new ::Ifc4::IfcStackTerminalTypeEnum(std::move(data));
    case 944:
      return new ::Ifc4::IfcStair(std::move(data));
    case 945:
      return new ::Ifc4::IfcStairFlight(std::move(data));
    case 946:
      return new ::Ifc4::IfcStairFlightType(std::move(data));
    case 947:
      return new ::Ifc4::IfcStairFlightTypeEnum(std::move(data));
    case 948:
      return new ::Ifc4::IfcStairType(std::move(data));
    case 949:
      return new ::Ifc4::IfcStairTypeEnum(std::move(data));
    case 950:
      return new ::Ifc4::IfcStateEnum(std::move(data));
    case 951:
      return new ::Ifc4::IfcStructuralAction(std::move(data));
    case 952:
      return new ::Ifc4::IfcStructuralActivity(std::move(data));
    case 954:
      return new ::Ifc4::IfcStructuralAnalysisModel(std::move(data));
    case 955:
      return new ::Ifc4::IfcStructuralConnection(std::move(data));
    case 956:
      return new ::Ifc4::IfcStructuralConnectionCondition(std::move(data));
    case 957:
      return new ::Ifc4::IfcStructuralCurveAction(std::move(data));
    case 958:
      return new ::Ifc4::IfcStructuralCurveActivityTypeEnum(std::move(data));
    case 959:
      return new ::Ifc4::IfcStructuralCurveConnection(std::move(data));
    case 960:
      return new ::Ifc4::IfcStructuralCurveMember(std::move(data));
    case 961:
      return new ::Ifc4::IfcStructuralCurveMemberTypeEnum(std::move(data));
    case 962:
      return new ::Ifc4::IfcStructuralCurveMemberVarying(std::move(data));
    case 963:
      return new ::Ifc4::IfcStructuralCurveReaction(std::move(data));
    case 964:
      return new ::Ifc4::IfcStructuralItem(std::move(data));
    case 965:
      return new ::Ifc4::IfcStructuralLinearAction(std::move(data));
    case 966:
      return new ::Ifc4::IfcStructuralLoad(std::move(data));
    case 967:
      return new ::Ifc4::IfcStructuralLoadCase(std::move(data));
    case 968:
      return new ::Ifc4::IfcStructuralLoadConfiguration(std::move(data));
    case 969:
      return new ::Ifc4::IfcStructuralLoadGroup(std::move(data));
    case 970:
      return new ::Ifc4::IfcStructuralLoadLinearForce(std::move(data));
    case 971:
      return new ::Ifc4::IfcStructuralLoadOrResult(std::move(data));
    case 972:
      return new ::Ifc4::IfcStructuralLoadPlanarForce(std::move(data));
    case 973:
      return new ::Ifc4::IfcStructuralLoadSingleDisplacement(std::move(data));
    case 974:
      return new ::Ifc4::IfcStructuralLoadSingleDisplacementDistortion(
          std::move(data));
    case 975:
      return new ::Ifc4::IfcStructuralLoadSingleForce(std::move(data));
    case 976:
      return new ::Ifc4::IfcStructuralLoadSingleForceWarping(std::move(data));
    case 977:
      return new ::Ifc4::IfcStructuralLoadStatic(std::move(data));
    case 978:
      return new ::Ifc4::IfcStructuralLoadTemperature(std::move(data));
    case 979:
      return new ::Ifc4::IfcStructuralMember(std::move(data));
    case 980:
      return new ::Ifc4::IfcStructuralPlanarAction(std::move(data));
    case 981:
      return new ::Ifc4::IfcStructuralPointAction(std::move(data));
    case 982:
      return new ::Ifc4::IfcStructuralPointConnection(std::move(data));
    case 983:
      return new ::Ifc4::IfcStructuralPointReaction(std::move(data));
    case 984:
      return new ::Ifc4::IfcStructuralReaction(std::move(data));
    case 985:
      return new ::Ifc4::IfcStructuralResultGroup(std::move(data));
    case 986:
      return new ::Ifc4::IfcStructuralSurfaceAction(std::move(data));
    case 987:
      return new ::Ifc4::IfcStructuralSurfaceActivityTypeEnum(std::move(data));
    case 988:
      return new ::Ifc4::IfcStructuralSurfaceConnection(std::move(data));
    case 989:
      return new ::Ifc4::IfcStructuralSurfaceMember(std::move(data));
    case 990:
      return new ::Ifc4::IfcStructuralSurfaceMemberTypeEnum(std::move(data));
    case 991:
      return new ::Ifc4::IfcStructuralSurfaceMemberVarying(std::move(data));
    case 992:
      return new ::Ifc4::IfcStructuralSurfaceReaction(std::move(data));
    case 994:
      return new ::Ifc4::IfcStyledItem(std::move(data));
    case 995:
      return new ::Ifc4::IfcStyledRepresentation(std::move(data));
    case 996:
      return new ::Ifc4::IfcStyleModel(std::move(data));
    case 997:
      return new ::Ifc4::IfcSubContractResource(std::move(data));
    case 998:
      return new ::Ifc4::IfcSubContractResourceType(std::move(data));
    case 999:
      return new ::Ifc4::IfcSubContractResourceTypeEnum(std::move(data));
    case 1000:
      return new ::Ifc4::IfcSubedge(std::move(data));
    case 1001:
      return new ::Ifc4::IfcSurface(std::move(data));
    case 1002:
      return new ::Ifc4::IfcSurfaceCurve(std::move(data));
    case 1003:
      return new ::Ifc4::IfcSurfaceCurveSweptAreaSolid(std::move(data));
    case 1004:
      return new ::Ifc4::IfcSurfaceFeature(std::move(data));
    case 1005:
      return new ::Ifc4::IfcSurfaceFeatureTypeEnum(std::move(data));
    case 1006:
      return new ::Ifc4::IfcSurfaceOfLinearExtrusion(std::move(data));
    case 1007:
      return new ::Ifc4::IfcSurfaceOfRevolution(std::move(data));
    case 1009:
      return new ::Ifc4::IfcSurfaceReinforcementArea(std::move(data));
    case 1010:
      return new ::Ifc4::IfcSurfaceSide(std::move(data));
    case 1011:
      return new ::Ifc4::IfcSurfaceStyle(std::move(data));
    case 1013:
      return new ::Ifc4::IfcSurfaceStyleLighting(std::move(data));
    case 1014:
      return new ::Ifc4::IfcSurfaceStyleRefraction(std::move(data));
    case 1015:
      return new ::Ifc4::IfcSurfaceStyleRendering(std::move(data));
    case 1016:
      return new ::Ifc4::IfcSurfaceStyleShading(std::move(data));
    case 1017:
      return new ::Ifc4::IfcSurfaceStyleWithTextures(std::move(data));
    case 1018:
      return new ::Ifc4::IfcSurfaceTexture(std::move(data));
    case 1019:
      return new ::Ifc4::IfcSweptAreaSolid(std::move(data));
    case 1020:
      return new ::Ifc4::IfcSweptDiskSolid(std::move(data));
    case 1021:
      return new ::Ifc4::IfcSweptDiskSolidPolygonal(std::move(data));
    case 1022:
      return new ::Ifc4::IfcSweptSurface(std::move(data));
    case 1023:
      return new ::Ifc4::IfcSwitchingDevice(std::move(data));
    case 1024:
      return new ::Ifc4::IfcSwitchingDeviceType(std::move(data));
    case 1025:
      return new ::Ifc4::IfcSwitchingDeviceTypeEnum(std::move(data));
    case 1026:
      return new ::Ifc4::IfcSystem(std::move(data));
    case 1027:
      return new ::Ifc4::IfcSystemFurnitureElement(std::move(data));
    case 1028:
      return new ::Ifc4::IfcSystemFurnitureElementType(std::move(data));
    case 1029:
      return new ::Ifc4::IfcSystemFurnitureElementTypeEnum(std::move(data));
    case 1030:
      return new ::Ifc4::IfcTable(std::move(data));
    case 1031:
      return new ::Ifc4::IfcTableColumn(std::move(data));
    case 1032:
      return new ::Ifc4::IfcTableRow(std::move(data));
    case 1033:
      return new ::Ifc4::IfcTank(std::move(data));
    case 1034:
      return new ::Ifc4::IfcTankType(std::move(data));
    case 1035:
      return new ::Ifc4::IfcTankTypeEnum(std::move(data));
    case 1036:
      return new ::Ifc4::IfcTask(std::move(data));
    case 1037:
      return new ::Ifc4::IfcTaskDurationEnum(std::move(data));
    case 1038:
      return new ::Ifc4::IfcTaskTime(std::move(data));
    case 1039:
      return new ::Ifc4::IfcTaskTimeRecurring(std::move(data));
    case 1040:
      return new ::Ifc4::IfcTaskType(std::move(data));
    case 1041:
      return new ::Ifc4::IfcTaskTypeEnum(std::move(data));
    case 1042:
      return new ::Ifc4::IfcTelecomAddress(std::move(data));
    case 1043:
      return new ::Ifc4::IfcTemperatureGradientMeasure(std::move(data));
    case 1044:
      return new ::Ifc4::IfcTemperatureRateOfChangeMeasure(std::move(data));
    case 1045:
      return new ::Ifc4::IfcTendon(std::move(data));
    case 1046:
      return new ::Ifc4::IfcTendonAnchor(std::move(data));
    case 1047:
      return new ::Ifc4::IfcTendonAnchorType(std::move(data));
    case 1048:
      return new ::Ifc4::IfcTendonAnchorTypeEnum(std::move(data));
    case 1049:
      return new ::Ifc4::IfcTendonType(std::move(data));
    case 1050:
      return new ::Ifc4::IfcTendonTypeEnum(std::move(data));
    case 1051:
      return new ::Ifc4::IfcTessellatedFaceSet(std::move(data));
    case 1052:
      return new ::Ifc4::IfcTessellatedItem(std::move(data));
    case 1053:
      return new ::Ifc4::IfcText(std::move(data));
    case 1054:
      return new ::Ifc4::IfcTextAlignment(std::move(data));
    case 1055:
      return new ::Ifc4::IfcTextDecoration(std::move(data));
    case 1056:
      return new ::Ifc4::IfcTextFontName(std::move(data));
    case 1058:
      return new ::Ifc4::IfcTextLiteral(std::move(data));
    case 1059:
      return new ::Ifc4::IfcTextLiteralWithExtent(std::move(data));
    case 1060:
      return new ::Ifc4::IfcTextPath(std::move(data));
    case 1061:
      return new ::Ifc4::IfcTextStyle(std::move(data));
    case 1062:
      return new ::Ifc4::IfcTextStyleFontModel(std::move(data));
    case 1063:
      return new ::Ifc4::IfcTextStyleForDefinedFont(std::move(data));
    case 1064:
      return new ::Ifc4::IfcTextStyleTextModel(std::move(data));
    case 1065:
      return new ::Ifc4::IfcTextTransformation(std::move(data));
    case 1066:
      return new ::Ifc4::IfcTextureCoordinate(std::move(data));
    case 1067:
      return new ::Ifc4::IfcTextureCoordinateGenerator(std::move(data));
    case 1068:
      return new ::Ifc4::IfcTextureMap(std::move(data));
    case 1069:
      return new ::Ifc4::IfcTextureVertex(std::move(data));
    case 1070:
      return new ::Ifc4::IfcTextureVertexList(std::move(data));
    case 1071:
      return new ::Ifc4::IfcThermalAdmittanceMeasure(std::move(data));
    case 1072:
      return new ::Ifc4::IfcThermalConductivityMeasure(std::move(data));
    case 1073:
      return new ::Ifc4::IfcThermalExpansionCoefficientMeasure(std::move(data));
    case 1074:
      return new ::Ifc4::IfcThermalResistanceMeasure(std::move(data));
    case 1075:
      return new ::Ifc4::IfcThermalTransmittanceMeasure(std::move(data));
    case 1076:
      return new ::Ifc4::IfcThermodynamicTemperatureMeasure(std::move(data));
    case 1077:
      return new ::Ifc4::IfcTime(std::move(data));
    case 1078:
      return new ::Ifc4::IfcTimeMeasure(std::move(data));
    case 1080:
      return new ::Ifc4::IfcTimePeriod(std::move(data));
    case 1081:
      return new ::Ifc4::IfcTimeSeries(std::move(data));
    case 1082:
      return new ::Ifc4::IfcTimeSeriesDataTypeEnum(std::move(data));
    case 1083:
      return new ::Ifc4::IfcTimeSeriesValue(std::move(data));
    case 1084:
      return new ::Ifc4::IfcTimeStamp(std::move(data));
    case 1085:
      return new ::Ifc4::IfcTopologicalRepresentationItem(std::move(data));
    case 1086:
      return new ::Ifc4::IfcTopologyRepresentation(std::move(data));
    case 1087:
      return new ::Ifc4::IfcToroidalSurface(std::move(data));
    case 1088:
      return new ::Ifc4::IfcTorqueMeasure(std::move(data));
    case 1089:
      return new ::Ifc4::IfcTransformer(std::move(data));
    case 1090:
      return new ::Ifc4::IfcTransformerType(std::move(data));
    case 1091:
      return new ::Ifc4::IfcTransformerTypeEnum(std::move(data));
    case 1092:
      return new ::Ifc4::IfcTransitionCode(std::move(data));
    case 1094:
      return new ::Ifc4::IfcTransportElement(std::move(data));
    case 1095:
      return new ::Ifc4::IfcTransportElementType(std::move(data));
    case 1096:
      return new ::Ifc4::IfcTransportElementTypeEnum(std::move(data));
    case 1097:
      return new ::Ifc4::IfcTrapeziumProfileDef(std::move(data));
    case 1098:
      return new ::Ifc4::IfcTriangulatedFaceSet(std::move(data));
    case 1099:
      return new ::Ifc4::IfcTrimmedCurve(std::move(data));
    case 1100:
      return new ::Ifc4::IfcTrimmingPreference(std::move(data));
    case 1102:
      return new ::Ifc4::IfcTShapeProfileDef(std::move(data));
    case 1103:
      return new ::Ifc4::IfcTubeBundle(std::move(data));
    case 1104:
      return new ::Ifc4::IfcTubeBundleType(std::move(data));
    case 1105:
      return new ::Ifc4::IfcTubeBundleTypeEnum(std::move(data));
    case 1106:
      return new ::Ifc4::IfcTypeObject(std::move(data));
    case 1107:
      return new ::Ifc4::IfcTypeProcess(std::move(data));
    case 1108:
      return new ::Ifc4::IfcTypeProduct(std::move(data));
    case 1109:
      return new ::Ifc4::IfcTypeResource(std::move(data));
    case 1111:
      return new ::Ifc4::IfcUnitaryControlElement(std::move(data));
    case 1112:
      return new ::Ifc4::IfcUnitaryControlElementType(std::move(data));
    case 1113:
      return new ::Ifc4::IfcUnitaryControlElementTypeEnum(std::move(data));
    case 1114:
      return new ::Ifc4::IfcUnitaryEquipment(std::move(data));
    case 1115:
      return new ::Ifc4::IfcUnitaryEquipmentType(std::move(data));
    case 1116:
      return new ::Ifc4::IfcUnitaryEquipmentTypeEnum(std::move(data));
    case 1117:
      return new ::Ifc4::IfcUnitAssignment(std::move(data));
    case 1118:
      return new ::Ifc4::IfcUnitEnum(std::move(data));
    case 1119:
      return new ::Ifc4::IfcURIReference(std::move(data));
    case 1120:
      return new ::Ifc4::IfcUShapeProfileDef(std::move(data));
    case 1122:
      return new ::Ifc4::IfcValve(std::move(data));
    case 1123:
      return new ::Ifc4::IfcValveType(std::move(data));
    case 1124:
      return new ::Ifc4::IfcValveTypeEnum(std::move(data));
    case 1125:
      return new ::Ifc4::IfcVaporPermeabilityMeasure(std::move(data));
    case 1126:
      return new ::Ifc4::IfcVector(std::move(data));
    case 1128:
      return new ::Ifc4::IfcVertex(std::move(data));
    case 1129:
      return new ::Ifc4::IfcVertexLoop(std::move(data));
    case 1130:
      return new ::Ifc4::IfcVertexPoint(std::move(data));
    case 1131:
      return new ::Ifc4::IfcVibrationIsolator(std::move(data));
    case 1132:
      return new ::Ifc4::IfcVibrationIsolatorType(std::move(data));
    case 1133:
      return new ::Ifc4::IfcVibrationIsolatorTypeEnum(std::move(data));
    case 1134:
      return new ::Ifc4::IfcVirtualElement(std::move(data));
    case 1135:
      return new ::Ifc4::IfcVirtualGridIntersection(std::move(data));
    case 1136:
      return new ::Ifc4::IfcVoidingFeature(std::move(data));
    case 1137:
      return new ::Ifc4::IfcVoidingFeatureTypeEnum(std::move(data));
    case 1138:
      return new ::Ifc4::IfcVolumeMeasure(std::move(data));
    case 1139:
      return new ::Ifc4::IfcVolumetricFlowRateMeasure(std::move(data));
    case 1140:
      return new ::Ifc4::IfcWall(std::move(data));
    case 1141:
      return new ::Ifc4::IfcWallElementedCase(std::move(data));
    case 1142:
      return new ::Ifc4::IfcWallStandardCase(std::move(data));
    case 1143:
      return new ::Ifc4::IfcWallType(std::move(data));
    case 1144:
      return new ::Ifc4::IfcWallTypeEnum(std::move(data));
    case 1145:
      return new ::Ifc4::IfcWarpingConstantMeasure(std::move(data));
    case 1146:
      return new ::Ifc4::IfcWarpingMomentMeasure(std::move(data));
    case 1148:
      return new ::Ifc4::IfcWasteTerminal(std::move(data));
    case 1149:
      return new ::Ifc4::IfcWasteTerminalType(std::move(data));
    case 1150:
      return new ::Ifc4::IfcWasteTerminalTypeEnum(std::move(data));
    case 1151:
      return new ::Ifc4::IfcWindow(std::move(data));
    case 1152:
      return new ::Ifc4::IfcWindowLiningProperties(std::move(data));
    case 1153:
      return new ::Ifc4::IfcWindowPanelOperationEnum(std::move(data));
    case 1154:
      return new ::Ifc4::IfcWindowPanelPositionEnum(std::move(data));
    case 1155:
      return new ::Ifc4::IfcWindowPanelProperties(std::move(data));
    case 1156:
      return new ::Ifc4::IfcWindowStandardCase(std::move(data));
    case 1157:
      return new ::Ifc4::IfcWindowStyle(std::move(data));
    case 1158:
      return new ::Ifc4::IfcWindowStyleConstructionEnum(std::move(data));
    case 1159:
      return new ::Ifc4::IfcWindowStyleOperationEnum(std::move(data));
    case 1160:
      return new ::Ifc4::IfcWindowType(std::move(data));
    case 1161:
      return new ::Ifc4::IfcWindowTypeEnum(std::move(data));
    case 1162:
      return new ::Ifc4::IfcWindowTypePartitioningEnum(std::move(data));
    case 1163:
      return new ::Ifc4::IfcWorkCalendar(std::move(data));
    case 1164:
      return new ::Ifc4::IfcWorkCalendarTypeEnum(std::move(data));
    case 1165:
      return new ::Ifc4::IfcWorkControl(std::move(data));
    case 1166:
      return new ::Ifc4::IfcWorkPlan(std::move(data));
    case 1167:
      return new ::Ifc4::IfcWorkPlanTypeEnum(std::move(data));
    case 1168:
      return new ::Ifc4::IfcWorkSchedule(std::move(data));
    case 1169:
      return new ::Ifc4::IfcWorkScheduleTypeEnum(std::move(data));
    case 1170:
      return new ::Ifc4::IfcWorkTime(std::move(data));
    case 1171:
      return new ::Ifc4::IfcZone(std::move(data));
    case 1172:
      return new ::Ifc4::IfcZShapeProfileDef(std::move(data));
    default:
      throw IfcParse::IfcException(decl->name() + " cannot be instantiated");
    }
  }
};

IfcParse::schema_definition *IFC4_populate_schema() {
  IFC4_types[0] = new type_declaration(strings[0], 0,
                                       new simple_type(simple_type::real_type));
  IFC4_types[1] = new type_declaration(strings[1], 1,
                                       new simple_type(simple_type::real_type));
  IFC4_types[3] =
      new enumeration_type(strings[2], 3,
                           {strings[3], strings[4], strings[5], strings[6],
                            strings[7], strings[8], strings[9]});
  IFC4_types[4] = new enumeration_type(
      strings[10], 4,
      {strings[11], strings[12], strings[13], strings[14], strings[15],
       strings[16], strings[17], strings[18], strings[19], strings[20],
       strings[21], strings[22], strings[23], strings[24], strings[25],
       strings[26], strings[27], strings[28], strings[29], strings[30],
       strings[31], strings[32], strings[33], strings[34], strings[35],
       strings[8],  strings[9]});
  IFC4_types[5] = new enumeration_type(
      strings[36], 5,
      {strings[37], strings[38], strings[39], strings[8], strings[9]});
  IFC4_types[11] =
      new enumeration_type(strings[40], 11,
                           {strings[41], strings[42], strings[43], strings[44],
                            strings[45], strings[8], strings[9]});
  IFC4_types[13] = new enumeration_type(
      strings[46], 13,
      {strings[47], strings[48], strings[49], strings[50], strings[8]});
  IFC4_types[20] = new enumeration_type(
      strings[51], 20,
      {strings[52], strings[53], strings[54], strings[8], strings[9]});
  IFC4_types[22] = new enumeration_type(strings[55], 22,
                                        {strings[56], strings[57], strings[58],
                                         strings[59], strings[8], strings[9]});
  IFC4_types[25] =
      new enumeration_type(strings[60], 25,
                           {strings[61], strings[62], strings[63], strings[64],
                            strings[65], strings[66], strings[67], strings[68],
                            strings[69], strings[8], strings[9]});
  IFC4_types[28] =
      new enumeration_type(strings[70], 28,
                           {strings[71], strings[72], strings[73], strings[74],
                            strings[75], strings[76], strings[8], strings[9]});
  IFC4_types[29] = new type_declaration(
      strings[77], 29, new simple_type(simple_type::real_type));
  IFC4_types[30] = new enumeration_type(
      strings[78], 30,
      {strings[79], strings[80], strings[81], strings[8], strings[9]});
  IFC4_types[31] = new enumeration_type(strings[82], 31,
                                        {strings[83], strings[84], strings[85],
                                         strings[86], strings[8], strings[9]});
  IFC4_types[32] = new type_declaration(
      strings[87], 32, new simple_type(simple_type::real_type));
  IFC4_types[44] = new type_declaration(
      strings[88], 44, new simple_type(simple_type::real_type));
  IFC4_types[45] = new type_declaration(
      strings[89], 45, new simple_type(simple_type::real_type));
  IFC4_types[46] = new enumeration_type(
      strings[90], 46, {strings[91], strings[92], strings[93], strings[94]});
  IFC4_types[47] = new enumeration_type(strings[95], 47,
                                        {strings[48], strings[96], strings[9]});
  IFC4_types[52] = new enumeration_type(
      strings[97], 52,
      {strings[98], strings[99], strings[100], strings[101], strings[102],
       strings[103], strings[104], strings[105], strings[106], strings[107],
       strings[108], strings[8], strings[9]});
  IFC4_types[86] =
      new enumeration_type(strings[109], 86,
                           {strings[110], strings[111], strings[112],
                            strings[113], strings[114], strings[115]});
  IFC4_types[89] = new enumeration_type(
      strings[116], 89,
      {strings[117], strings[118], strings[119], strings[120], strings[121],
       strings[122], strings[123], strings[124], strings[125], strings[126],
       strings[115]});
  IFC4_types[60] = new enumeration_type(
      strings[127], 60,
      {strings[128], strings[129], strings[130], strings[131], strings[132],
       strings[133], strings[8], strings[9]});
  IFC4_types[61] = new enumeration_type(
      strings[134], 61,
      {strings[135], strings[136], strings[137], strings[138], strings[139],
       strings[140], strings[141], strings[142], strings[143], strings[144]});
  IFC4_types[63] = new type_declaration(
      strings[145], 63, new simple_type(simple_type::binary_type));
  IFC4_types[68] = new enumeration_type(
      strings[146], 68, {strings[147], strings[148], strings[8], strings[9]});
  IFC4_types[69] = new type_declaration(
      strings[149], 69, new simple_type(simple_type::boolean_type));
  IFC4_types[72] = new enumeration_type(
      strings[150], 72, {strings[151], strings[152], strings[153]});
  IFC4_types[95] = new enumeration_type(
      strings[154], 95, {strings[155], strings[156], strings[8], strings[9]});
  IFC4_types[98] = new enumeration_type(strings[157], 98,
                                        {strings[158], strings[159],
                                         strings[160], strings[161],
                                         strings[162], strings[8], strings[9]});
  IFC4_types[102] = new enumeration_type(
      strings[163], 102,
      {strings[164], strings[165], strings[166], strings[167], strings[168],
       strings[23], strings[8], strings[9]});
  IFC4_types[105] =
      new enumeration_type(strings[169], 105, {strings[8], strings[9]});
  IFC4_types[108] =
      new enumeration_type(strings[170], 108,
                           {strings[171], strings[172], strings[173],
                            strings[174], strings[8], strings[9]});
  IFC4_types[111] =
      new enumeration_type(strings[175], 111,
                           {strings[176], strings[177], strings[178],
                            strings[179], strings[8], strings[9]});
  IFC4_types[114] = new enumeration_type(
      strings[180], 114,
      {strings[181], strings[182], strings[183], strings[184], strings[185],
       strings[8], strings[9]});
  IFC4_types[117] =
      new enumeration_type(strings[186], 117,
                           {strings[187], strings[188], strings[189],
                            strings[190], strings[8], strings[9]});
  IFC4_types[118] = new type_declaration(
      strings[191], 118, new simple_type(simple_type::integer_type));
  IFC4_types[129] = new enumeration_type(
      strings[192], 129,
      {strings[193], strings[194], strings[195], strings[196], strings[9]});
  IFC4_types[132] = new enumeration_type(
      strings[197], 132,
      {strings[198], strings[199], strings[200], strings[8], strings[9]});
  IFC4_types[135] =
      new enumeration_type(strings[201], 135, {strings[8], strings[9]});
  IFC4_types[148] = new enumeration_type(
      strings[202], 148,
      {strings[203], strings[204], strings[205], strings[206], strings[207],
       strings[208], strings[209], strings[8], strings[9]});
  IFC4_types[157] = new enumeration_type(
      strings[210], 157, {strings[211], strings[212], strings[8], strings[9]});
  IFC4_types[160] = new enumeration_type(
      strings[213], 160,
      {strings[214], strings[215], strings[4], strings[216], strings[217],
       strings[218], strings[219], strings[220], strings[221], strings[222],
       strings[223], strings[224], strings[8], strings[9]});
  IFC4_types[161] = new type_declaration(
      strings[225], 161,
      new aggregation_type(aggregation_type::array_type, 1, 2,
                           new simple_type(simple_type::real_type)));
  IFC4_types[164] =
      new enumeration_type(strings[226], 164, {strings[227], strings[228]});
  IFC4_types[169] = new type_declaration(
      strings[229], 169,
      new aggregation_type(aggregation_type::list_type, 3, 4,
                           new simple_type(simple_type::integer_type)));
  IFC4_types[172] = new enumeration_type(
      strings[230], 172,
      {strings[231], strings[232], strings[233], strings[234], strings[235],
       strings[236], strings[237], strings[238], strings[239], strings[240],
       strings[241], strings[242], strings[243], strings[244], strings[245],
       strings[8], strings[9]});
  IFC4_types[175] = new enumeration_type(
      strings[246], 175,
      {strings[198], strings[247], strings[199], strings[248], strings[249],
       strings[250], strings[251], strings[8], strings[9]});
  IFC4_types[183] = new enumeration_type(
      strings[252], 183,
      {strings[253], strings[254], strings[255], strings[9]});
  IFC4_types[186] = new enumeration_type(
      strings[256], 186,
      {strings[257], strings[258], strings[259], strings[8], strings[9]});
  IFC4_types[189] = new enumeration_type(
      strings[260], 189,
      {strings[261], strings[262], strings[263], strings[264], strings[265],
       strings[266], strings[267], strings[268], strings[8], strings[9]});
  IFC4_types[192] = new enumeration_type(
      strings[269], 192,
      {strings[270], strings[271], strings[272], strings[273], strings[274],
       strings[275], strings[276], strings[277], strings[278], strings[9],
       strings[8]});
  IFC4_types[195] = new enumeration_type(
      strings[279], 195, {strings[280], strings[281], strings[8], strings[9]});
  IFC4_types[199] = new type_declaration(
      strings[282], 199, new simple_type(simple_type::real_type));
  IFC4_types[204] = new enumeration_type(
      strings[283], 204,
      {strings[284], strings[285], strings[286], strings[287], strings[288],
       strings[8], strings[9]});
  IFC4_types[209] = new enumeration_type(
      strings[289], 209, {strings[290], strings[291], strings[8], strings[9]});
  IFC4_types[212] = new enumeration_type(
      strings[292], 212,
      {strings[293], strings[294], strings[295], strings[8], strings[9]});
  IFC4_types[217] =
      new enumeration_type(strings[296], 217, {strings[8], strings[9]});
  IFC4_types[219] = new enumeration_type(
      strings[297], 219,
      {strings[298], strings[299], strings[300], strings[301], strings[302],
       strings[303], strings[304], strings[8], strings[9]});
  IFC4_types[221] = new type_declaration(
      strings[305], 221, new simple_type(simple_type::number_type));
  IFC4_types[224] = new enumeration_type(
      strings[306], 224,
      {strings[307], strings[308], strings[309], strings[310], strings[311],
       strings[312], strings[155], strings[313], strings[314], strings[315],
       strings[8], strings[9]});
  IFC4_types[227] = new enumeration_type(
      strings[316], 227, {strings[47], strings[48], strings[8], strings[9]});
  IFC4_types[235] =
      new enumeration_type(strings[317], 235, {strings[8], strings[9]});
  IFC4_types[236] = new type_declaration(
      strings[318], 236, new simple_type(simple_type::real_type));
  IFC4_types[241] = new enumeration_type(
      strings[319], 241,
      {strings[320], strings[321], strings[322], strings[9]});
  IFC4_types[252] = new enumeration_type(
      strings[323], 252,
      {strings[324], strings[325], strings[326], strings[327], strings[328],
       strings[329], strings[330], strings[331], strings[332], strings[333],
       strings[334], strings[8], strings[9]});
  IFC4_types[253] = new enumeration_type(
      strings[335], 253,
      {strings[336], strings[337], strings[338], strings[8], strings[9]});
  IFC4_types[254] = new type_declaration(
      strings[339], 254, new simple_type(simple_type::string_type));
  IFC4_types[255] = new type_declaration(
      strings[340], 255, new simple_type(simple_type::string_type));
  IFC4_types[256] = new type_declaration(
      strings[341], 256, new simple_type(simple_type::integer_type));
  IFC4_types[257] = new type_declaration(
      strings[342], 257, new simple_type(simple_type::integer_type));
  IFC4_types[263] = new enumeration_type(
      strings[343], 263,
      {strings[344], strings[345], strings[346], strings[347], strings[348],
       strings[349], strings[350], strings[351], strings[352], strings[353],
       strings[354], strings[355], strings[356], strings[357], strings[358],
       strings[359], strings[360], strings[361], strings[362], strings[363],
       strings[364], strings[365], strings[366], strings[367], strings[368],
       strings[369], strings[370], strings[371], strings[372], strings[373],
       strings[374], strings[375], strings[376], strings[377], strings[378],
       strings[379], strings[380], strings[381], strings[382], strings[383],
       strings[384], strings[385], strings[386], strings[387], strings[388],
       strings[389], strings[390], strings[391], strings[392], strings[393],
       strings[394], strings[395], strings[8]});
  IFC4_types[264] = new type_declaration(
      strings[396], 264, new simple_type(simple_type::string_type));
  IFC4_types[266] = new type_declaration(
      strings[397], 266, new simple_type(simple_type::integer_type));
  IFC4_types[268] =
      new enumeration_type(strings[398], 268, {strings[399], strings[400]});
  IFC4_types[271] = new enumeration_type(
      strings[401], 271,
      {strings[402], strings[403], strings[404], strings[8], strings[9]});
  IFC4_types[274] = new enumeration_type(
      strings[405], 274,
      {strings[406], strings[407], strings[408], strings[409], strings[410],
       strings[411], strings[412], strings[413], strings[8], strings[9]});
  IFC4_types[283] =
      new enumeration_type(strings[414], 283,
                           {strings[415], strings[416], strings[417],
                            strings[418], strings[8], strings[9]});
  IFC4_types[285] = new enumeration_type(
      strings[419], 285,
      {strings[420], strings[421], strings[422], strings[423], strings[424],
       strings[425], strings[426], strings[427], strings[428], strings[429],
       strings[430], strings[431], strings[432], strings[433], strings[434],
       strings[435], strings[436], strings[437], strings[438], strings[273],
       strings[439], strings[440], strings[264], strings[265], strings[441],
       strings[442], strings[443], strings[444], strings[445], strings[446],
       strings[447], strings[448], strings[449], strings[450], strings[451],
       strings[107], strings[452], strings[453], strings[454], strings[455],
       strings[456], strings[457], strings[8],   strings[9]});
  IFC4_types[286] =
      new enumeration_type(strings[458], 286,
                           {strings[459], strings[460], strings[461],
                            strings[462], strings[8], strings[9]});
  IFC4_types[291] = new enumeration_type(
      strings[463], 291,
      {strings[464], strings[465], strings[466], strings[467], strings[9]});
  IFC4_types[294] = new enumeration_type(
      strings[468], 294,
      {strings[469], strings[470], strings[471], strings[472], strings[473],
       strings[474], strings[475], strings[8], strings[9]});
  IFC4_types[295] = new enumeration_type(
      strings[476], 295,
      {strings[477], strings[478], strings[479], strings[9]});
  IFC4_types[299] = new enumeration_type(
      strings[480], 299,
      {strings[481], strings[482], strings[483], strings[278], strings[484],
       strings[485], strings[277], strings[8], strings[9]});
  IFC4_types[300] = new enumeration_type(
      strings[486], 300,
      {strings[487], strings[488], strings[489], strings[490], strings[491],
       strings[492], strings[493], strings[494], strings[495], strings[496],
       strings[497], strings[498], strings[499], strings[500], strings[473],
       strings[474], strings[8], strings[9]});
  IFC4_types[302] = new enumeration_type(
      strings[501], 302,
      {strings[502], strings[503], strings[504], strings[8], strings[9]});
  IFC4_types[303] = new enumeration_type(
      strings[505], 303,
      {strings[487], strings[488], strings[489], strings[490], strings[491],
       strings[492], strings[493], strings[494], strings[495], strings[496],
       strings[497], strings[498], strings[499], strings[500], strings[473],
       strings[474], strings[506], strings[507], strings[8],   strings[9]});
  IFC4_types[304] = new type_declaration(
      strings[508], 304, new simple_type(simple_type::real_type));
  IFC4_types[309] = new enumeration_type(
      strings[509], 309,
      {strings[171], strings[181], strings[182], strings[183], strings[184],
       strings[510], strings[185], strings[8], strings[9]});
  IFC4_types[312] = new enumeration_type(
      strings[511], 312, {strings[512], strings[513], strings[8], strings[9]});
  IFC4_types[315] = new enumeration_type(
      strings[514], 315,
      {strings[515], strings[516], strings[517], strings[8], strings[9]});
  IFC4_types[316] = new type_declaration(
      strings[518], 316, new simple_type(simple_type::string_type));
  IFC4_types[317] = new type_declaration(
      strings[519], 317, new simple_type(simple_type::real_type));
  IFC4_types[323] = new enumeration_type(
      strings[520], 323,
      {strings[521], strings[522], strings[523], strings[524], strings[525],
       strings[526], strings[527], strings[528], strings[529], strings[530],
       strings[531], strings[532], strings[533], strings[534], strings[535],
       strings[536], strings[8], strings[9]});
  IFC4_types[324] = new type_declaration(
      strings[537], 324, new simple_type(simple_type::real_type));
  IFC4_types[325] = new type_declaration(
      strings[538], 325, new simple_type(simple_type::real_type));
  IFC4_types[326] = new type_declaration(
      strings[539], 326, new simple_type(simple_type::real_type));
  IFC4_types[327] = new type_declaration(
      strings[540], 327, new simple_type(simple_type::real_type));
  IFC4_types[330] =
      new enumeration_type(strings[541], 330,
                           {strings[542], strings[543], strings[544],
                            strings[545], strings[8], strings[9]});
  IFC4_types[333] = new enumeration_type(
      strings[546], 333,
      {strings[547], strings[548], strings[549], strings[550], strings[551],
       strings[8], strings[9]});
  IFC4_types[336] = new enumeration_type(
      strings[552], 336,
      {strings[553], strings[554], strings[555], strings[8], strings[9]});
  IFC4_types[339] = new enumeration_type(
      strings[556], 339,
      {strings[557], strings[558], strings[559], strings[560], strings[561],
       strings[8], strings[9]});
  IFC4_types[340] = new type_declaration(
      strings[562], 340, new simple_type(simple_type::real_type));
  IFC4_types[343] = new enumeration_type(
      strings[563], 343,
      {strings[564], strings[565], strings[566], strings[8], strings[9]});
  IFC4_types[344] = new type_declaration(
      strings[567], 344, new simple_type(simple_type::real_type));
  IFC4_types[349] = new enumeration_type(
      strings[568], 349,
      {strings[569], strings[570], strings[571], strings[572], strings[573],
       strings[574], strings[575], strings[576], strings[577], strings[8],
       strings[9]});
  IFC4_types[352] = new enumeration_type(
      strings[578], 352, {strings[158], strings[159], strings[160]});
  IFC4_types[359] = new type_declaration(
      strings[579], 359, new simple_type(simple_type::real_type));
  IFC4_types[362] = new enumeration_type(
      strings[580], 362, {strings[581], strings[582], strings[8], strings[9]});
  IFC4_types[365] = new enumeration_type(
      strings[583], 365,
      {strings[584], strings[585], strings[586], strings[587], strings[588],
       strings[589], strings[590], strings[591], strings[592], strings[8],
       strings[9]});
  IFC4_types[368] = new enumeration_type(
      strings[593], 368,
      {strings[594], strings[595], strings[596], strings[597], strings[598],
       strings[599], strings[8], strings[9]});
  IFC4_types[371] =
      new enumeration_type(strings[600], 371,
                           {strings[601], strings[602], strings[603],
                            strings[604], strings[8], strings[9]});
  IFC4_types[373] = new enumeration_type(
      strings[605], 373,
      {strings[606], strings[607], strings[608], strings[8], strings[9]});
  IFC4_types[382] =
      new enumeration_type(strings[609], 382,
                           {strings[610], strings[611], strings[612],
                            strings[613], strings[8], strings[9]});
  IFC4_types[396] = new enumeration_type(
      strings[614], 396,
      {strings[615], strings[616], strings[617], strings[618], strings[619],
       strings[620], strings[621], strings[8], strings[9]});
  IFC4_types[399] = new enumeration_type(
      strings[622], 399,
      {strings[623], strings[624], strings[625], strings[8], strings[9]});
  IFC4_types[409] = new enumeration_type(
      strings[626], 409,
      {strings[627], strings[628], strings[629], strings[630], strings[631],
       strings[632], strings[8], strings[9]});
  IFC4_types[412] = new enumeration_type(
      strings[633], 412,
      {strings[634], strings[635], strings[636], strings[637], strings[638],
       strings[8], strings[9]});
  IFC4_types[416] = new enumeration_type(
      strings[639], 416,
      {strings[640], strings[641], strings[642], strings[9]});
  IFC4_types[421] = new enumeration_type(
      strings[643], 421,
      {strings[644], strings[645], strings[646], strings[647], strings[648],
       strings[649], strings[650], strings[651], strings[8], strings[9]});
  IFC4_types[424] =
      new enumeration_type(strings[652], 424,
                           {strings[653], strings[654], strings[655],
                            strings[656], strings[8], strings[9]});
  IFC4_types[435] = new type_declaration(
      strings[657], 435, new simple_type(simple_type::string_type));
  IFC4_types[436] = new type_declaration(
      strings[658], 436, new simple_type(simple_type::string_type));
  IFC4_types[437] = new type_declaration(
      strings[659], 437, new simple_type(simple_type::string_type));
  IFC4_types[440] = new enumeration_type(
      strings[660], 440,
      {strings[661], strings[662], strings[663], strings[664], strings[665],
       strings[8], strings[9]});
  IFC4_types[441] = new type_declaration(
      strings[666], 441, new simple_type(simple_type::real_type));
  IFC4_types[442] = new type_declaration(
      strings[667], 442, new simple_type(simple_type::real_type));
  IFC4_types[447] = new enumeration_type(
      strings[668], 447,
      {strings[669], strings[670], strings[671], strings[672], strings[673],
       strings[674], strings[675], strings[8], strings[9]});
  IFC4_types[450] = new enumeration_type(
      strings[676], 450, {strings[677], strings[8], strings[9]});
  IFC4_types[452] = new enumeration_type(
      strings[678], 452,
      {strings[679], strings[680], strings[681], strings[682], strings[683],
       strings[684], strings[685], strings[8], strings[9]});
  IFC4_types[459] =
      new enumeration_type(strings[686], 459, {strings[687], strings[688]});
  IFC4_types[458] = new type_declaration(
      strings[689], 458, new simple_type(simple_type::string_type));
  IFC4_types[464] =
      new enumeration_type(strings[690], 464,
                           {strings[516], strings[691], strings[692],
                            strings[693], strings[8], strings[9]});
  IFC4_types[470] = new enumeration_type(
      strings[694], 470, {strings[695], strings[696], strings[8], strings[9]});
  IFC4_types[471] = new type_declaration(
      strings[697], 471, new simple_type(simple_type::real_type));
  IFC4_types[472] = new type_declaration(
      strings[698], 472, new simple_type(simple_type::real_type));
  IFC4_types[475] = new enumeration_type(
      strings[699], 475,
      {strings[700], strings[701], strings[702], strings[703], strings[704],
       strings[705], strings[706], strings[707], strings[708], strings[709],
       strings[710], strings[711], strings[712], strings[8], strings[9]});
  IFC4_types[476] = new type_declaration(
      strings[713], 476, new simple_type(simple_type::string_type));
  IFC4_types[477] = new type_declaration(
      strings[714], 477, new simple_type(simple_type::real_type));
  IFC4_types[485] = new type_declaration(
      strings[715], 485, new simple_type(simple_type::real_type));
  IFC4_types[486] = new type_declaration(
      strings[716], 486, new simple_type(simple_type::integer_type));
  IFC4_types[487] = new type_declaration(
      strings[717], 487, new simple_type(simple_type::integer_type));
  IFC4_types[490] =
      new enumeration_type(strings[718], 490,
                           {strings[719], strings[720], strings[443],
                            strings[721], strings[8], strings[9]});
  IFC4_types[491] =
      new enumeration_type(strings[722], 491,
                           {strings[723], strings[610], strings[611],
                            strings[612], strings[613], strings[9]});
  IFC4_types[494] = new enumeration_type(
      strings[724], 494,
      {strings[725], strings[726], strings[727], strings[8], strings[9]});
  IFC4_types[495] = new type_declaration(
      strings[728], 495, new simple_type(simple_type::real_type));
  IFC4_types[499] = new type_declaration(
      strings[729], 499, new simple_type(simple_type::real_type));
  IFC4_types[502] = new enumeration_type(
      strings[730], 502, {strings[429], strings[731], strings[8], strings[9]});
  IFC4_types[503] = new type_declaration(
      strings[732], 503, new simple_type(simple_type::real_type));
  IFC4_types[504] = new enumeration_type(
      strings[733], 504,
      {strings[734], strings[735], strings[736], strings[115]});
  IFC4_types[505] = new type_declaration(
      strings[737], 505, new simple_type(simple_type::string_type));
  IFC4_types[508] = new enumeration_type(
      strings[738], 508,
      {strings[739], strings[740], strings[741], strings[271], strings[272],
       strings[742], strings[743], strings[308], strings[744], strings[745],
       strings[746], strings[275], strings[747], strings[266], strings[748],
       strings[310], strings[749], strings[750], strings[751], strings[8],
       strings[9]});
  IFC4_types[512] = new enumeration_type(
      strings[752], 512,
      {strings[753], strings[754], strings[755], strings[756], strings[757],
       strings[758], strings[759], strings[760], strings[761], strings[8],
       strings[9]});
  IFC4_types[513] =
      new type_declaration(strings[762], 513, new named_type(IFC4_types[476]));
  IFC4_types[515] = new enumeration_type(
      strings[763], 515, {strings[764], strings[765], strings[766]});
  IFC4_types[516] = new type_declaration(
      strings[767], 516, new simple_type(simple_type::real_type));
  IFC4_types[520] = new enumeration_type(
      strings[768], 520,
      {strings[769], strings[770], strings[771], strings[9]});
  IFC4_types[523] = new enumeration_type(
      strings[772], 523,
      {strings[753], strings[754], strings[756], strings[757], strings[773],
       strings[774], strings[775], strings[776], strings[759], strings[761],
       strings[9]});
  IFC4_types[526] = new enumeration_type(
      strings[777], 526,
      {strings[778], strings[779], strings[780], strings[8], strings[9]});
  IFC4_types[535] = new type_declaration(
      strings[781], 535, new simple_type(simple_type::real_type));
  IFC4_types[536] = new type_declaration(
      strings[782], 536, new simple_type(simple_type::real_type));
  IFC4_types[537] = new type_declaration(
      strings[783], 537, new simple_type(simple_type::real_type));
  IFC4_types[538] = new type_declaration(
      strings[784], 538, new simple_type(simple_type::real_type));
  IFC4_types[540] = new enumeration_type(
      strings[785], 540,
      {strings[786], strings[787], strings[788], strings[8], strings[9]});
  IFC4_types[542] = new type_declaration(
      strings[789], 542, new simple_type(simple_type::logical_type));
  IFC4_types[543] = new enumeration_type(
      strings[790], 543,
      {strings[791], strings[792], strings[793], strings[794], strings[795]});
  IFC4_types[546] = new type_declaration(
      strings[796], 546, new simple_type(simple_type::real_type));
  IFC4_types[547] = new type_declaration(
      strings[797], 547, new simple_type(simple_type::real_type));
  IFC4_types[548] = new type_declaration(
      strings[798], 548, new simple_type(simple_type::real_type));
  IFC4_types[549] = new type_declaration(
      strings[799], 549, new simple_type(simple_type::real_type));
  IFC4_types[550] = new type_declaration(
      strings[800], 550, new simple_type(simple_type::real_type));
  IFC4_types[554] = new type_declaration(
      strings[801], 554, new simple_type(simple_type::real_type));
  IFC4_types[555] = new type_declaration(
      strings[802], 555, new simple_type(simple_type::real_type));
  IFC4_types[556] = new type_declaration(
      strings[803], 556, new simple_type(simple_type::real_type));
  IFC4_types[557] = new type_declaration(
      strings[804], 557, new simple_type(simple_type::real_type));
  IFC4_types[582] = new enumeration_type(
      strings[805], 582,
      {strings[806], strings[807], strings[808], strings[809], strings[810],
       strings[811], strings[812], strings[813], strings[814], strings[815],
       strings[8], strings[9]});
  IFC4_types[585] = new enumeration_type(
      strings[816], 585,
      {strings[817], strings[818], strings[819], strings[820], strings[821],
       strings[8], strings[9]});
  IFC4_types[589] = new enumeration_type(
      strings[822], 589,
      {strings[823], strings[824], strings[825], strings[826], strings[827],
       strings[695], strings[6], strings[828], strings[829], strings[830],
       strings[831], strings[832], strings[8], strings[9]});
  IFC4_types[593] = new type_declaration(
      strings[833], 593, new simple_type(simple_type::real_type));
  IFC4_types[594] = new type_declaration(
      strings[834], 594, new simple_type(simple_type::real_type));
  IFC4_types[595] = new type_declaration(
      strings[835], 595, new simple_type(simple_type::real_type));
  IFC4_types[596] =
      new select_type(strings[836], 596, {IFC4_types[69], IFC4_types[595]});
  IFC4_types[597] = new type_declaration(
      strings[837], 597, new simple_type(simple_type::real_type));
  IFC4_types[598] =
      new select_type(strings[838], 598, {IFC4_types[69], IFC4_types[597]});
  IFC4_types[599] =
      new select_type(strings[839], 599, {IFC4_types[69], IFC4_types[594]});
  IFC4_types[600] = new type_declaration(
      strings[840], 600, new simple_type(simple_type::real_type));
  IFC4_types[601] = new type_declaration(
      strings[841], 601, new simple_type(simple_type::real_type));
  IFC4_types[602] = new type_declaration(
      strings[842], 602, new simple_type(simple_type::real_type));
  IFC4_types[603] = new type_declaration(
      strings[843], 603, new simple_type(simple_type::real_type));
  IFC4_types[605] = new type_declaration(
      strings[844], 605, new simple_type(simple_type::integer_type));
  IFC4_types[608] = new enumeration_type(
      strings[845], 608,
      {strings[846], strings[847], strings[848], strings[8], strings[9]});
  IFC4_types[610] =
      new type_declaration(strings[849], 610, new named_type(IFC4_types[516]));
  IFC4_types[612] = new enumeration_type(strings[850], 612, {strings[851]});
  IFC4_types[613] = new type_declaration(
      strings[852], 613, new simple_type(simple_type::number_type));
  IFC4_types[620] = new enumeration_type(
      strings[853], 620,
      {strings[854], strings[855], strings[427], strings[856], strings[857],
       strings[858], strings[859], strings[9]});
  IFC4_types[617] = new enumeration_type(
      strings[860], 617,
      {strings[861], strings[862], strings[863], strings[610], strings[864],
       strings[865], strings[866], strings[867], strings[868], strings[869],
       strings[870], strings[8], strings[9]});
  IFC4_types[622] = new enumeration_type(
      strings[871], 622,
      {strings[872], strings[873], strings[874], strings[875], strings[876],
       strings[877], strings[878], strings[8], strings[9]});
  IFC4_types[626] = new enumeration_type(
      strings[879], 626, {strings[880], strings[881], strings[8], strings[9]});
  IFC4_types[635] = new enumeration_type(
      strings[882], 635,
      {strings[883], strings[884], strings[885], strings[886], strings[887],
       strings[8], strings[9]});
  IFC4_types[649] = new type_declaration(
      strings[888], 649, new simple_type(simple_type::real_type));
  IFC4_types[638] = new type_declaration(
      strings[889], 638, new simple_type(simple_type::real_type));
  IFC4_types[642] =
      new enumeration_type(strings[890], 642, {strings[8], strings[9]});
  IFC4_types[643] = new enumeration_type(
      strings[891], 643,
      {strings[892], strings[893], strings[894], strings[8], strings[9]});
  IFC4_types[646] = new enumeration_type(
      strings[895], 646,
      {strings[896], strings[897], strings[898], strings[8], strings[9]});
  IFC4_types[651] = new enumeration_type(
      strings[899], 651, {strings[900], strings[901], strings[9]});
  IFC4_types[655] =
      new enumeration_type(strings[902], 655,
                           {strings[903], strings[904], strings[905],
                            strings[906], strings[8], strings[9]});
  IFC4_types[657] = new enumeration_type(
      strings[907], 657,
      {strings[908], strings[909], strings[910], strings[911], strings[912],
       strings[913], strings[8], strings[9]});
  IFC4_types[660] = new enumeration_type(
      strings[914], 660,
      {strings[171], strings[181], strings[182], strings[183], strings[184],
       strings[510], strings[185], strings[8], strings[9]});
  IFC4_types[663] = new enumeration_type(
      strings[915], 663,
      {strings[916], strings[513], strings[512], strings[917], strings[918],
       strings[8], strings[9]});
  IFC4_types[668] = new type_declaration(
      strings[919], 668, new simple_type(simple_type::real_type));
  IFC4_types[670] = new type_declaration(
      strings[920], 670, new simple_type(simple_type::real_type));
  IFC4_types[674] = new enumeration_type(
      strings[921], 674, {strings[922], strings[923], strings[8], strings[9]});
  IFC4_types[684] =
      new type_declaration(strings[924], 684, new named_type(IFC4_types[486]));
  IFC4_types[685] =
      new type_declaration(strings[925], 685, new named_type(IFC4_types[516]));
  IFC4_types[686] =
      new type_declaration(strings[926], 686, new named_type(IFC4_types[670]));
  IFC4_types[689] = new type_declaration(
      strings[927], 689, new simple_type(simple_type::real_type));
  IFC4_types[696] = new enumeration_type(
      strings[928], 696, {strings[929], strings[930], strings[931]});
  IFC4_types[697] = new type_declaration(
      strings[932], 697, new simple_type(simple_type::string_type));
  IFC4_types[704] = new type_declaration(
      strings[933], 704, new simple_type(simple_type::real_type));
  IFC4_types[707] = new enumeration_type(
      strings[934], 707,
      {strings[935], strings[936], strings[937], strings[938], strings[939],
       strings[940], strings[941], strings[8], strings[9]});
  IFC4_types[717] =
      new enumeration_type(strings[942], 717, {strings[943], strings[944]});
  IFC4_types[725] = new enumeration_type(
      strings[945], 725,
      {strings[946], strings[947], strings[948], strings[949], strings[950],
       strings[8], strings[9]});
  IFC4_types[720] =
      new enumeration_type(strings[951], 720, {strings[952], strings[953]});
  IFC4_types[722] =
      new enumeration_type(strings[954], 722, {strings[8], strings[9]});
  IFC4_types[740] = new enumeration_type(
      strings[955], 740,
      {strings[956], strings[957], strings[958], strings[959], strings[960],
       strings[961], strings[962], strings[9]});
  IFC4_types[748] =
      new enumeration_type(strings[963], 748,
                           {strings[964], strings[965], strings[966],
                            strings[967], strings[8], strings[9]});
  IFC4_types[750] = new enumeration_type(
      strings[968], 750,
      {strings[969], strings[970], strings[971], strings[972], strings[973],
       strings[974], strings[975], strings[8], strings[9]});
  IFC4_types[754] = new enumeration_type(
      strings[976], 754,
      {strings[977], strings[978], strings[979], strings[980], strings[981],
       strings[982], strings[983], strings[8], strings[9]});
  IFC4_types[762] = new type_declaration(
      strings[984], 762, new simple_type(simple_type::real_type));
  IFC4_types[765] = new enumeration_type(
      strings[985], 765,
      {strings[986], strings[987], strings[988], strings[8], strings[9]});
  IFC4_types[769] = new enumeration_type(
      strings[989], 769, {strings[990], strings[991], strings[8], strings[9]});
  IFC4_types[771] = new enumeration_type(
      strings[992], 771,
      {strings[993], strings[994], strings[995], strings[996], strings[997],
       strings[998], strings[8], strings[9]});
  IFC4_types[772] = new type_declaration(
      strings[999], 772, new simple_type(simple_type::real_type));
  IFC4_types[775] = new type_declaration(
      strings[1000], 775, new simple_type(simple_type::real_type));
  IFC4_types[781] = new enumeration_type(
      strings[1001], 781,
      {strings[1002], strings[1003], strings[1004], strings[1005],
       strings[1006], strings[1007], strings[1008], strings[1009]});
  IFC4_types[783] = new enumeration_type(
      strings[1010], 783,
      {strings[1011], strings[1012], strings[1013], strings[1014], strings[276],
       strings[1015], strings[1016], strings[277], strings[1017], strings[9]});
  IFC4_types[788] = new enumeration_type(
      strings[1018], 788,
      {strings[1019], strings[1020], strings[1021], strings[832], strings[1022],
       strings[1023], strings[1024], strings[1025], strings[8], strings[9]});
  IFC4_types[789] =
      new enumeration_type(strings[1026], 789, {strings[1027], strings[1028]});
  IFC4_types[791] = new enumeration_type(
      strings[1029], 791,
      {strings[1025], strings[1023], strings[1021], strings[1019],
       strings[1022], strings[1024], strings[1020], strings[832], strings[8],
       strings[9]});
  IFC4_types[796] =
      new enumeration_type(strings[1030], 796, {strings[8], strings[9]});
  IFC4_types[861] = new enumeration_type(
      strings[1031], 861,
      {strings[1032], strings[1033], strings[1034], strings[1035],
       strings[1036], strings[1037], strings[1038], strings[1039],
       strings[1040], strings[1041], strings[1042], strings[1043],
       strings[1044], strings[1045], strings[1046], strings[1047],
       strings[1048], strings[877],  strings[1049], strings[1050],
       strings[1051], strings[1052], strings[8]});
  IFC4_types[864] = new enumeration_type(
      strings[1053], 864,
      {strings[1054], strings[1055], strings[1056], strings[1057],
       strings[1058], strings[1059], strings[1060], strings[1061],
       strings[1062], strings[1063], strings[1064], strings[1065],
       strings[1066], strings[8], strings[9]});
  IFC4_types[866] = new type_declaration(
      strings[1067], 866, new simple_type(simple_type::real_type));
  IFC4_types[867] = new type_declaration(
      strings[1068], 867, new simple_type(simple_type::real_type));
  IFC4_types[868] = new type_declaration(
      strings[1069], 868, new simple_type(simple_type::real_type));
  IFC4_types[869] =
      new select_type(strings[1070], 869, {IFC4_types[69], IFC4_types[868]});
  IFC4_types[900] = new enumeration_type(
      strings[1071], 900,
      {strings[1072], strings[1073], strings[1074], strings[1075],
       strings[1076], strings[1077], strings[1078], strings[1079],
       strings[1080], strings[1081], strings[1082], strings[1083],
       strings[1084], strings[1085], strings[1086], strings[1087]});
  IFC4_types[903] = new enumeration_type(
      strings[1088], 903,
      {strings[1089], strings[1090], strings[1091], strings[1092],
       strings[1093], strings[1094], strings[1095], strings[1096],
       strings[1097], strings[1098], strings[1099], strings[1100],
       strings[1101], strings[1102], strings[1103], strings[1104],
       strings[1105], strings[1106], strings[1107], strings[1108],
       strings[1109], strings[1110], strings[1111], strings[1112],
       strings[1113], strings[1114], strings[1115], strings[1116],
       strings[1117], strings[1118]});
  IFC4_types[873] = new enumeration_type(
      strings[1119], 873,
      {strings[1120], strings[1121], strings[1122], strings[1123], strings[641],
       strings[1124], strings[1125], strings[1126], strings[1127],
       strings[1128], strings[8], strings[9]});
  IFC4_types[878] = new type_declaration(
      strings[1129], 878, new simple_type(simple_type::real_type));
  IFC4_types[881] =
      new enumeration_type(strings[1130], 881, {strings[1131], strings[1132]});
  IFC4_types[876] = new type_declaration(
      strings[1133], 876, new simple_type(simple_type::real_type));
  IFC4_types[885] = new enumeration_type(
      strings[1134], 885,
      {strings[1135], strings[1136], strings[1137], strings[1138],
       strings[1139], strings[1140], strings[1141], strings[1142],
       strings[1143], strings[1144], strings[1145], strings[1146],
       strings[1147], strings[1148], strings[1149], strings[1150],
       strings[1151], strings[1152], strings[1153], strings[1154],
       strings[1155], strings[1156], strings[1157], strings[1158],
       strings[8],    strings[9]});
  IFC4_types[886] =
      new enumeration_type(strings[1159], 886,
                           {strings[1160], strings[1161], strings[1162],
                            strings[1163], strings[8], strings[9]});
  IFC4_types[889] = new enumeration_type(
      strings[1164], 889,
      {strings[1165], strings[1166], strings[1167], strings[8], strings[9]});
  IFC4_types[893] = new type_declaration(
      strings[1168], 893, new simple_type(simple_type::real_type));
  IFC4_types[898] = new enumeration_type(
      strings[1169], 898,
      {strings[1170], strings[1171], strings[1172], strings[1173],
       strings[1174], strings[1175], strings[1176], strings[1177],
       strings[1178], strings[1179], strings[1180], strings[1181]});
  IFC4_types[909] =
      new enumeration_type(strings[1182], 909,
                           {strings[1183], strings[1184], strings[1185],
                            strings[1186], strings[8], strings[9]});
  IFC4_types[913] = new enumeration_type(
      strings[1187], 913,
      {strings[1188], strings[1189], strings[8], strings[9]});
  IFC4_types[914] = new type_declaration(
      strings[1190], 914, new simple_type(simple_type::real_type));
  IFC4_types[917] = new type_declaration(
      strings[1191], 917, new simple_type(simple_type::real_type));
  IFC4_types[918] = new type_declaration(
      strings[1192], 918, new simple_type(simple_type::real_type));
  IFC4_types[919] = new type_declaration(
      strings[1193], 919, new simple_type(simple_type::real_type));
  IFC4_types[920] = new type_declaration(
      strings[1194], 920, new simple_type(simple_type::real_type));
  IFC4_types[925] = new enumeration_type(
      strings[1195], 925,
      {strings[1196], strings[1197], strings[8], strings[9]});
  IFC4_types[927] = new enumeration_type(
      strings[1198], 927,
      {strings[1199], strings[1200], strings[1201], strings[723], strings[610],
       strings[8], strings[9]});
  IFC4_types[934] = new enumeration_type(
      strings[1202], 934,
      {strings[1203], strings[1204], strings[265], strings[1205], strings[448],
       strings[967], strings[23], strings[455], strings[8], strings[9]});
  IFC4_types[935] = new type_declaration(
      strings[1206], 935, new simple_type(simple_type::real_type));
  IFC4_types[936] = new type_declaration(
      strings[1207], 936, new simple_type(simple_type::real_type));
  IFC4_types[938] = new type_declaration(
      strings[1208], 938, new simple_type(simple_type::real_type));
  IFC4_types[943] = new enumeration_type(
      strings[1209], 943,
      {strings[1210], strings[1211], strings[1212], strings[8], strings[9]});
  IFC4_types[947] = new enumeration_type(
      strings[1213], 947,
      {strings[990], strings[1214], strings[991], strings[1215], strings[1066],
       strings[8], strings[9]});
  IFC4_types[949] = new enumeration_type(
      strings[1216], 949,
      {strings[1217], strings[1218], strings[1219], strings[1220],
       strings[1221], strings[1222], strings[1223], strings[1224],
       strings[1225], strings[1226], strings[1227], strings[1228],
       strings[1229], strings[1230], strings[8], strings[9]});
  IFC4_types[950] =
      new enumeration_type(strings[1231], 950,
                           {strings[1232], strings[1233], strings[1234],
                            strings[1235], strings[1236]});
  IFC4_types[958] = new enumeration_type(
      strings[1237], 958,
      {strings[1238], strings[320], strings[1239], strings[1240], strings[1241],
       strings[1242], strings[1243], strings[8], strings[9]});
  IFC4_types[961] = new enumeration_type(
      strings[1244], 961,
      {strings[1245], strings[1246], strings[415], strings[1247], strings[1248],
       strings[8], strings[9]});
  IFC4_types[987] =
      new enumeration_type(strings[1249], 987,
                           {strings[1238], strings[1250], strings[1243],
                            strings[1251], strings[8], strings[9]});
  IFC4_types[990] = new enumeration_type(
      strings[1252], 990,
      {strings[1253], strings[1254], strings[1255], strings[8], strings[9]});
  IFC4_types[999] = new enumeration_type(
      strings[1256], 999,
      {strings[1257], strings[898], strings[8], strings[9]});
  IFC4_types[1005] = new enumeration_type(
      strings[1258], 1005,
      {strings[1259], strings[1260], strings[1261], strings[8], strings[9]});
  IFC4_types[1010] = new enumeration_type(
      strings[1262], 1010, {strings[399], strings[400], strings[1263]});
  IFC4_types[1025] = new enumeration_type(
      strings[1264], 1025,
      {strings[1265], strings[1266], strings[1267], strings[1268],
       strings[1269], strings[1270], strings[1271], strings[1272],
       strings[1273], strings[8], strings[9]});
  IFC4_types[1029] = new enumeration_type(
      strings[1274], 1029,
      {strings[1275], strings[1276], strings[8], strings[9]});
  IFC4_types[1035] = new enumeration_type(
      strings[1277], 1035,
      {strings[1278], strings[1279], strings[1280], strings[1281],
       strings[1282], strings[1283], strings[1284], strings[8], strings[9]});
  IFC4_types[1037] = new enumeration_type(
      strings[1285], 1037, {strings[1286], strings[1287], strings[9]});
  IFC4_types[1041] = new enumeration_type(
      strings[1288], 1041,
      {strings[1289], strings[1203], strings[1290], strings[1291], strings[430],
       strings[1292], strings[1293], strings[1294], strings[1295],
       strings[1296], strings[1297], strings[1298], strings[8], strings[9]});
  IFC4_types[1043] = new type_declaration(
      strings[1299], 1043, new simple_type(simple_type::real_type));
  IFC4_types[1044] = new type_declaration(
      strings[1300], 1044, new simple_type(simple_type::real_type));
  IFC4_types[1048] = new enumeration_type(
      strings[1301], 1048,
      {strings[1302], strings[1303], strings[1304], strings[8], strings[9]});
  IFC4_types[1050] =
      new enumeration_type(strings[1305], 1050,
                           {strings[1306], strings[1307], strings[1308],
                            strings[1309], strings[8], strings[9]});
  IFC4_types[1053] = new type_declaration(
      strings[1310], 1053, new simple_type(simple_type::string_type));
  IFC4_types[1054] = new type_declaration(
      strings[1311], 1054, new simple_type(simple_type::string_type));
  IFC4_types[1055] = new type_declaration(
      strings[1312], 1055, new simple_type(simple_type::string_type));
  IFC4_types[1056] = new type_declaration(
      strings[1313], 1056, new simple_type(simple_type::string_type));
  IFC4_types[1060] = new enumeration_type(
      strings[1314], 1060,
      {strings[477], strings[479], strings[1315], strings[1316]});
  IFC4_types[1065] = new type_declaration(
      strings[1317], 1065, new simple_type(simple_type::string_type));
  IFC4_types[1071] = new type_declaration(
      strings[1318], 1071, new simple_type(simple_type::real_type));
  IFC4_types[1072] = new type_declaration(
      strings[1319], 1072, new simple_type(simple_type::real_type));
  IFC4_types[1073] = new type_declaration(
      strings[1320], 1073, new simple_type(simple_type::real_type));
  IFC4_types[1074] = new type_declaration(
      strings[1321], 1074, new simple_type(simple_type::real_type));
  IFC4_types[1075] = new type_declaration(
      strings[1322], 1075, new simple_type(simple_type::real_type));
  IFC4_types[1076] = new type_declaration(
      strings[1323], 1076, new simple_type(simple_type::real_type));
  IFC4_types[1077] = new type_declaration(
      strings[1324], 1077, new simple_type(simple_type::string_type));
  IFC4_types[1078] = new type_declaration(
      strings[1325], 1078, new simple_type(simple_type::real_type));
  IFC4_types[1079] =
      new select_type(strings[1326], 1079, {IFC4_types[316], IFC4_types[772]});
  IFC4_types[1082] = new enumeration_type(
      strings[1327], 1082,
      {strings[1328], strings[1243], strings[1329], strings[1330],
       strings[1331], strings[1332], strings[9]});
  IFC4_types[1084] = new type_declaration(
      strings[1333], 1084, new simple_type(simple_type::integer_type));
  IFC4_types[1088] = new type_declaration(
      strings[1334], 1088, new simple_type(simple_type::real_type));
  IFC4_types[1091] = new enumeration_type(
      strings[1335], 1091,
      {strings[32], strings[1336], strings[1337], strings[1338], strings[1339],
       strings[8], strings[9]});
  IFC4_types[1092] = new enumeration_type(
      strings[1340], 1092,
      {strings[1341], strings[1328], strings[1342], strings[1343]});
  IFC4_types[1093] =
      new select_type(strings[1344], 1093, {IFC4_types[69], IFC4_types[537]});
  IFC4_types[1096] = new enumeration_type(
      strings[1345], 1096,
      {strings[1346], strings[1347], strings[1348], strings[1349],
       strings[1350], strings[8], strings[9]});
  IFC4_types[1100] = new enumeration_type(
      strings[1351], 1100, {strings[1352], strings[867], strings[115]});
  IFC4_types[1105] = new enumeration_type(
      strings[1353], 1105, {strings[1354], strings[8], strings[9]});
  IFC4_types[1119] = new type_declaration(
      strings[1355], 1119, new simple_type(simple_type::string_type));
  IFC4_types[1118] = new enumeration_type(
      strings[1356], 1118,
      {strings[1357], strings[1358], strings[1359], strings[1360],
       strings[1361], strings[1362], strings[1363], strings[1364],
       strings[1365], strings[1366], strings[1367], strings[1368],
       strings[1369], strings[1370], strings[1371], strings[1372],
       strings[1373], strings[1374], strings[1375], strings[1376],
       strings[1377], strings[1378], strings[1379], strings[1380],
       strings[1381], strings[1382], strings[1383], strings[1384],
       strings[1385], strings[8]});
  IFC4_types[1113] = new enumeration_type(
      strings[1386], 1113,
      {strings[1387], strings[1388], strings[1389], strings[1390],
       strings[1391], strings[1392], strings[1393], strings[1394], strings[8],
       strings[9]});
  IFC4_types[1116] = new enumeration_type(
      strings[1395], 1116,
      {strings[1396], strings[1397], strings[1398], strings[1399],
       strings[1400], strings[8], strings[9]});
  IFC4_types[1124] = new enumeration_type(
      strings[1401], 1124,
      {strings[1402], strings[1403], strings[1404], strings[1405],
       strings[1406], strings[1407], strings[1408], strings[1409],
       strings[1410], strings[1411], strings[1412], strings[1413],
       strings[1414], strings[1415], strings[1416], strings[1417],
       strings[1418], strings[1419], strings[1420], strings[1421],
       strings[1422], strings[8],    strings[9]});
  IFC4_types[1125] = new type_declaration(
      strings[1423], 1125, new simple_type(simple_type::real_type));
  IFC4_types[1133] = new enumeration_type(
      strings[1424], 1133,
      {strings[1425], strings[1426], strings[8], strings[9]});
  IFC4_types[1137] = new enumeration_type(
      strings[1427], 1137,
      {strings[1428], strings[1429], strings[1430], strings[1431],
       strings[1432], strings[1023], strings[8], strings[9]});
  IFC4_types[1138] = new type_declaration(
      strings[1433], 1138, new simple_type(simple_type::real_type));
  IFC4_types[1139] = new type_declaration(
      strings[1434], 1139, new simple_type(simple_type::real_type));
  IFC4_types[1144] = new enumeration_type(
      strings[1435], 1144,
      {strings[1436], strings[1437], strings[1438], strings[1439],
       strings[1020], strings[1440], strings[1441], strings[1239],
       strings[1442], strings[8], strings[9]});
  IFC4_types[1145] = new type_declaration(
      strings[1443], 1145, new simple_type(simple_type::real_type));
  IFC4_types[1146] = new type_declaration(
      strings[1444], 1146, new simple_type(simple_type::real_type));
  IFC4_types[1147] =
      new select_type(strings[1445], 1147, {IFC4_types[69], IFC4_types[1146]});
  IFC4_types[1150] = new enumeration_type(
      strings[1446], 1150,
      {strings[1447], strings[1448], strings[1449], strings[1450],
       strings[1451], strings[1452], strings[1453], strings[8], strings[9]});
  IFC4_types[1153] = new enumeration_type(
      strings[1454], 1153,
      {strings[1455], strings[1456], strings[1457], strings[1458],
       strings[1459], strings[1460], strings[1461], strings[1462],
       strings[1463], strings[1464], strings[1465], strings[1466],
       strings[1467], strings[9]});
  IFC4_types[1154] =
      new enumeration_type(strings[1468], 1154,
                           {strings[477], strings[478], strings[479],
                            strings[1469], strings[1470], strings[9]});
  IFC4_types[1158] = new enumeration_type(
      strings[1471], 1158,
      {strings[481], strings[482], strings[483], strings[278], strings[484],
       strings[277], strings[1472], strings[9]});
  IFC4_types[1159] = new enumeration_type(
      strings[1473], 1159,
      {strings[1474], strings[1475], strings[1476], strings[1477],
       strings[1478], strings[1479], strings[1480], strings[1481],
       strings[1482], strings[8], strings[9]});
  IFC4_types[1161] = new enumeration_type(
      strings[1483], 1161,
      {strings[1484], strings[1485], strings[1486], strings[8], strings[9]});
  IFC4_types[1162] = new enumeration_type(
      strings[1487], 1162,
      {strings[1474], strings[1475], strings[1476], strings[1477],
       strings[1478], strings[1479], strings[1480], strings[1481],
       strings[1482], strings[8], strings[9]});
  IFC4_types[1164] = new enumeration_type(
      strings[1488], 1164,
      {strings[1489], strings[1490], strings[1491], strings[8], strings[9]});
  IFC4_types[1167] = new enumeration_type(
      strings[1492], 1167,
      {strings[1493], strings[1494], strings[1495], strings[8], strings[9]});
  IFC4_types[1169] = new enumeration_type(
      strings[1496], 1169,
      {strings[1493], strings[1494], strings[1495], strings[8], strings[9]});
  IFC4_types[7] = new entity(strings[1497], false, 7, (entity *)0);
  IFC4_types[12] = new entity(strings[1498], true, 12, (entity *)0);
  IFC4_types[35] = new entity(strings[1499], false, 35, (entity *)0);
  IFC4_types[36] = new entity(strings[1500], false, 36, (entity *)0);
  IFC4_types[38] = new entity(strings[1501], false, 38, (entity *)0);
  IFC4_types[74] = new entity(strings[1502], true, 74, (entity *)0);
  IFC4_types[76] =
      new entity(strings[1503], false, 76, (entity *)IFC4_types[74]);
  IFC4_types[77] =
      new entity(strings[1504], false, 77, (entity *)IFC4_types[74]);
  IFC4_types[78] =
      new entity(strings[1505], false, 78, (entity *)IFC4_types[74]);
  IFC4_types[79] =
      new entity(strings[1506], false, 79, (entity *)IFC4_types[78]);
  IFC4_types[179] = new entity(strings[1507], true, 179, (entity *)0);
  IFC4_types[181] =
      new entity(strings[1508], false, 181, (entity *)IFC4_types[179]);
  IFC4_types[182] =
      new entity(strings[1509], false, 182, (entity *)IFC4_types[179]);
  IFC4_types[184] =
      new entity(strings[1510], false, 184, (entity *)IFC4_types[179]);
  IFC4_types[185] = new entity(strings[1511], true, 185, (entity *)0);
  IFC4_types[213] = new entity(strings[1512], true, 213, (entity *)0);
  IFC4_types[214] = new entity(strings[1513], true, 214, (entity *)0);
  IFC4_types[220] =
      new entity(strings[1514], false, 220, (entity *)IFC4_types[36]);
  IFC4_types[261] = new entity(strings[1515], false, 261, (entity *)0);
  IFC4_types[262] = new entity(strings[1516], false, 262, (entity *)0);
  IFC4_types[265] = new entity(strings[1517], false, 265, (entity *)0);
  IFC4_types[375] = new entity(strings[1518], true, 375, (entity *)0);
  IFC4_types[379] = new entity(strings[1519], true, 379, (entity *)0);
  IFC4_types[376] =
      new entity(strings[1520], false, 376, (entity *)IFC4_types[379]);
  IFC4_types[377] =
      new entity(strings[1521], false, 377, (entity *)IFC4_types[379]);
  IFC4_types[378] =
      new entity(strings[1522], false, 378, (entity *)IFC4_types[379]);
  IFC4_types[461] = new entity(strings[1523], false, 461, (entity *)0);
  IFC4_types[497] = new entity(strings[1524], false, 497, (entity *)0);
  IFC4_types[517] =
      new entity(strings[1525], false, 517, (entity *)IFC4_types[375]);
  IFC4_types[518] =
      new entity(strings[1526], false, 518, (entity *)IFC4_types[379]);
  IFC4_types[521] = new entity(strings[1527], false, 521, (entity *)0);
  IFC4_types[527] = new entity(strings[1528], false, 527, (entity *)0);
  IFC4_types[552] =
      new entity(strings[1529], false, 552, (entity *)IFC4_types[213]);
  IFC4_types[559] = new entity(strings[1530], false, 559, (entity *)0);
  IFC4_types[562] = new entity(strings[1531], true, 562, (entity *)0);
  IFC4_types[564] =
      new entity(strings[1532], false, 564, (entity *)IFC4_types[562]);
  IFC4_types[565] =
      new entity(strings[1533], false, 565, (entity *)IFC4_types[562]);
  IFC4_types[567] =
      new entity(strings[1534], false, 567, (entity *)IFC4_types[564]);
  IFC4_types[568] = new entity(strings[1535], false, 568, (entity *)0);
  IFC4_types[569] =
      new entity(strings[1536], false, 569, (entity *)IFC4_types[562]);
  IFC4_types[570] =
      new entity(strings[1537], false, 570, (entity *)IFC4_types[562]);
  IFC4_types[573] =
      new entity(strings[1538], false, 573, (entity *)IFC4_types[569]);
  IFC4_types[577] = new entity(strings[1539], true, 577, (entity *)0);
  IFC4_types[579] = new entity(strings[1540], false, 579, (entity *)0);
  IFC4_types[590] =
      new entity(strings[1541], false, 590, (entity *)IFC4_types[185]);
  IFC4_types[604] = new entity(strings[1542], false, 604, (entity *)0);
  IFC4_types[609] = new entity(strings[1543], true, 609, (entity *)0);
  IFC4_types[618] = new entity(strings[1544], true, 618, (entity *)0);
  IFC4_types[616] =
      new entity(strings[1545], false, 616, (entity *)IFC4_types[185]);
  IFC4_types[629] = new entity(strings[1546], false, 629, (entity *)0);
  IFC4_types[636] = new entity(strings[1547], false, 636, (entity *)0);
  IFC4_types[647] = new entity(strings[1548], false, 647, (entity *)0);
  IFC4_types[648] = new entity(strings[1549], false, 648, (entity *)0);
  IFC4_types[652] = new entity(strings[1550], true, 652, (entity *)0);
  IFC4_types[653] =
      new entity(strings[1551], true, 653, (entity *)IFC4_types[652]);
  IFC4_types[688] =
      new entity(strings[1552], false, 688, (entity *)IFC4_types[12]);
  IFC4_types[698] = new entity(strings[1553], true, 698, (entity *)0);
  IFC4_types[699] = new entity(strings[1554], false, 699, (entity *)0);
  IFC4_types[700] =
      new entity(strings[1555], false, 700, (entity *)IFC4_types[699]);
  IFC4_types[701] = new entity(strings[1556], true, 701, (entity *)0);
  IFC4_types[702] = new entity(strings[1557], false, 702, (entity *)0);
  IFC4_types[712] = new entity(strings[1558], true, 712, (entity *)0);
  IFC4_types[715] = new entity(strings[1559], false, 715, (entity *)0);
  IFC4_types[719] =
      new entity(strings[1560], false, 719, (entity *)IFC4_types[214]);
  IFC4_types[727] = new entity(strings[1561], true, 727, (entity *)0);
  IFC4_types[732] =
      new entity(strings[1562], false, 732, (entity *)IFC4_types[727]);
  IFC4_types[755] =
      new entity(strings[1563], false, 755, (entity *)IFC4_types[653]);
  IFC4_types[756] =
      new entity(strings[1564], false, 756, (entity *)IFC4_types[653]);
  IFC4_types[757] =
      new entity(strings[1565], false, 757, (entity *)IFC4_types[653]);
  IFC4_types[759] =
      new entity(strings[1566], false, 759, (entity *)IFC4_types[653]);
  IFC4_types[760] =
      new entity(strings[1567], false, 760, (entity *)IFC4_types[653]);
  IFC4_types[761] =
      new entity(strings[1568], false, 761, (entity *)IFC4_types[653]);
  IFC4_types[780] = new entity(strings[1569], false, 780, (entity *)0);
  IFC4_types[782] = new entity(strings[1570], false, 782, (entity *)0);
  IFC4_types[846] = new entity(strings[1571], true, 846, (entity *)0);
  IFC4_types[847] = new entity(strings[1572], true, 847, (entity *)0);
  IFC4_types[848] = new entity(strings[1573], true, 848, (entity *)0);
  IFC4_types[849] = new entity(strings[1574], false, 849, (entity *)0);
  IFC4_types[853] = new entity(strings[1575], true, 853, (entity *)0);
  IFC4_types[865] = new entity(strings[1576], true, 865, (entity *)0);
  IFC4_types[902] =
      new entity(strings[1577], false, 902, (entity *)IFC4_types[609]);
  IFC4_types[874] = new entity(strings[1578], true, 874, (entity *)0);
  IFC4_types[890] = new entity(strings[1579], false, 890, (entity *)0);
  IFC4_types[891] =
      new entity(strings[1580], true, 891, (entity *)IFC4_types[846]);
  IFC4_types[892] =
      new entity(strings[1581], false, 892, (entity *)IFC4_types[891]);
  IFC4_types[956] = new entity(strings[1582], true, 956, (entity *)0);
  IFC4_types[966] = new entity(strings[1583], true, 966, (entity *)0);
  IFC4_types[968] =
      new entity(strings[1584], false, 968, (entity *)IFC4_types[966]);
  IFC4_types[971] =
      new entity(strings[1585], true, 971, (entity *)IFC4_types[966]);
  IFC4_types[977] =
      new entity(strings[1586], true, 977, (entity *)IFC4_types[971]);
  IFC4_types[978] =
      new entity(strings[1587], false, 978, (entity *)IFC4_types[977]);
  IFC4_types[996] =
      new entity(strings[1588], true, 996, (entity *)IFC4_types[846]);
  IFC4_types[994] =
      new entity(strings[1589], false, 994, (entity *)IFC4_types[848]);
  IFC4_types[995] =
      new entity(strings[1590], false, 995, (entity *)IFC4_types[996]);
  IFC4_types[1009] =
      new entity(strings[1591], false, 1009, (entity *)IFC4_types[971]);
  IFC4_types[1011] =
      new entity(strings[1592], false, 1011, (entity *)IFC4_types[701]);
  IFC4_types[1013] =
      new entity(strings[1593], false, 1013, (entity *)IFC4_types[698]);
  IFC4_types[1014] =
      new entity(strings[1594], false, 1014, (entity *)IFC4_types[698]);
  IFC4_types[1016] =
      new entity(strings[1595], false, 1016, (entity *)IFC4_types[698]);
  IFC4_types[1017] =
      new entity(strings[1596], false, 1017, (entity *)IFC4_types[698]);
  IFC4_types[1018] =
      new entity(strings[1597], true, 1018, (entity *)IFC4_types[698]);
  IFC4_types[1030] = new entity(strings[1598], false, 1030, (entity *)0);
  IFC4_types[1031] = new entity(strings[1599], false, 1031, (entity *)0);
  IFC4_types[1032] = new entity(strings[1600], false, 1032, (entity *)0);
  IFC4_types[1038] =
      new entity(strings[1601], false, 1038, (entity *)IFC4_types[874]);
  IFC4_types[1039] =
      new entity(strings[1602], false, 1039, (entity *)IFC4_types[1038]);
  IFC4_types[1042] =
      new entity(strings[1603], false, 1042, (entity *)IFC4_types[12]);
  IFC4_types[1061] =
      new entity(strings[1604], false, 1061, (entity *)IFC4_types[701]);
  IFC4_types[1063] =
      new entity(strings[1605], false, 1063, (entity *)IFC4_types[698]);
  IFC4_types[1064] =
      new entity(strings[1606], false, 1064, (entity *)IFC4_types[698]);
  IFC4_types[1066] =
      new entity(strings[1607], true, 1066, (entity *)IFC4_types[698]);
  IFC4_types[1067] =
      new entity(strings[1608], false, 1067, (entity *)IFC4_types[1066]);
  IFC4_types[1068] =
      new entity(strings[1609], false, 1068, (entity *)IFC4_types[1066]);
  IFC4_types[1069] =
      new entity(strings[1610], false, 1069, (entity *)IFC4_types[698]);
  IFC4_types[1070] =
      new entity(strings[1611], false, 1070, (entity *)IFC4_types[698]);
  IFC4_types[1080] = new entity(strings[1612], false, 1080, (entity *)0);
  IFC4_types[1081] = new entity(strings[1613], true, 1081, (entity *)0);
  IFC4_types[1083] = new entity(strings[1614], false, 1083, (entity *)0);
  IFC4_types[1085] =
      new entity(strings[1615], true, 1085, (entity *)IFC4_types[848]);
  IFC4_types[1086] =
      new entity(strings[1616], false, 1086, (entity *)IFC4_types[891]);
  IFC4_types[1117] = new entity(strings[1617], false, 1117, (entity *)0);
  IFC4_types[1128] =
      new entity(strings[1618], false, 1128, (entity *)IFC4_types[1085]);
  IFC4_types[1130] =
      new entity(strings[1619], false, 1130, (entity *)IFC4_types[1128]);
  IFC4_types[1135] = new entity(strings[1620], false, 1135, (entity *)0);
  IFC4_types[1170] =
      new entity(strings[1621], false, 1170, (entity *)IFC4_types[874]);
  IFC4_types[8] = new select_type(
      strings[1622], 8, {IFC4_types[629], IFC4_types[647], IFC4_types[648]});
  IFC4_types[43] = new type_declaration(
      strings[1623], 43,
      new aggregation_type(aggregation_type::list_type, 3, 3,
                           new named_type(IFC4_types[684])));
  IFC4_types[62] =
      new select_type(strings[1624], 62, {IFC4_types[516], IFC4_types[670]});
  IFC4_types[83] =
      new type_declaration(strings[1625], 83, new named_type(IFC4_types[505]));
  IFC4_types[259] = new select_type(
      strings[1626], 259,
      {IFC4_types[0],    IFC4_types[1],    IFC4_types[32],   IFC4_types[44],
       IFC4_types[169],  IFC4_types[236],  IFC4_types[304],  IFC4_types[317],
       IFC4_types[324],  IFC4_types[325],  IFC4_types[326],  IFC4_types[340],
       IFC4_types[344],  IFC4_types[359],  IFC4_types[441],  IFC4_types[442],
       IFC4_types[471],  IFC4_types[472],  IFC4_types[477],  IFC4_types[485],
       IFC4_types[487],  IFC4_types[495],  IFC4_types[499],  IFC4_types[503],
       IFC4_types[535],  IFC4_types[536],  IFC4_types[537],  IFC4_types[538],
       IFC4_types[546],  IFC4_types[547],  IFC4_types[549],  IFC4_types[550],
       IFC4_types[554],  IFC4_types[555],  IFC4_types[557],  IFC4_types[593],
       IFC4_types[594],  IFC4_types[595],  IFC4_types[597],  IFC4_types[600],
       IFC4_types[601],  IFC4_types[602],  IFC4_types[603],  IFC4_types[649],
       IFC4_types[668],  IFC4_types[689],  IFC4_types[704],  IFC4_types[762],
       IFC4_types[866],  IFC4_types[867],  IFC4_types[868],  IFC4_types[878],
       IFC4_types[876],  IFC4_types[893],  IFC4_types[917],  IFC4_types[918],
       IFC4_types[919],  IFC4_types[920],  IFC4_types[935],  IFC4_types[1043],
       IFC4_types[1044], IFC4_types[1071], IFC4_types[1072], IFC4_types[1073],
       IFC4_types[1074], IFC4_types[1075], IFC4_types[1088], IFC4_types[1125],
       IFC4_types[1139], IFC4_types[1145], IFC4_types[1146]});
  IFC4_types[514] =
      new select_type(strings[1627], 514, {IFC4_types[846], IFC4_types[848]});
  IFC4_types[519] =
      new select_type(strings[1628], 519, {IFC4_types[517], IFC4_types[518]});
  IFC4_types[522] =
      new select_type(strings[1629], 522, {IFC4_types[379], IFC4_types[527]});
  IFC4_types[539] = new type_declaration(
      strings[1630], 539,
      new aggregation_type(aggregation_type::list_type, 2, -1,
                           new named_type(IFC4_types[684])));
  IFC4_types[576] = new select_type(
      strings[1631], 576, {IFC4_types[562], IFC4_types[568], IFC4_types[577]});
  IFC4_types[611] =
      new type_declaration(strings[1632], 611, new named_type(IFC4_types[772]));
  IFC4_types[619] =
      new select_type(strings[1633], 619,
                      {IFC4_types[12], IFC4_types[36], IFC4_types[379],
                       IFC4_types[562], IFC4_types[629], IFC4_types[647],
                       IFC4_types[648], IFC4_types[1030], IFC4_types[1081]});
  IFC4_types[687] =
      new type_declaration(strings[1634], 687, new named_type(IFC4_types[772]));
  IFC4_types[882] =
      new select_type(strings[1635], 882, {IFC4_types[43], IFC4_types[539]});
  IFC4_types[899] = new select_type(
      strings[1636], 899,
      {IFC4_types[63], IFC4_types[69], IFC4_types[254], IFC4_types[255],
       IFC4_types[316], IFC4_types[476], IFC4_types[486], IFC4_types[505],
       IFC4_types[542], IFC4_types[684], IFC4_types[775], IFC4_types[1053],
       IFC4_types[1077], IFC4_types[1084]});
  IFC4_types[904] =
      new select_type(strings[1637], 904,
                      {IFC4_types[264], IFC4_types[516], IFC4_types[611],
                       IFC4_types[685], IFC4_types[687], IFC4_types[772]});
  IFC4_types[937] =
      new select_type(strings[1638], 937, {IFC4_types[936], IFC4_types[938]});
  IFC4_types[993] =
      new select_type(strings[1639], 993, {IFC4_types[701], IFC4_types[702]});
  IFC4_types[1012] =
      new select_type(strings[1640], 1012,
                      {IFC4_types[377], IFC4_types[1013], IFC4_types[1014],
                       IFC4_types[1016], IFC4_types[1017]});
  IFC4_types[1110] = new select_type(
      strings[1641], 1110, {IFC4_types[261], IFC4_types[604], IFC4_types[609]});
  IFC4_types[39] =
      new entity(strings[1642], false, 39, (entity *)IFC4_types[853]);
  IFC4_types[40] =
      new entity(strings[1643], false, 40, (entity *)IFC4_types[715]);
  IFC4_types[41] =
      new entity(strings[1644], false, 41, (entity *)IFC4_types[715]);
  IFC4_types[42] =
      new entity(strings[1645], false, 42, (entity *)IFC4_types[40]);
  IFC4_types[64] =
      new entity(strings[1646], false, 64, (entity *)IFC4_types[1018]);
  IFC4_types[128] =
      new entity(strings[1647], false, 128, (entity *)IFC4_types[41]);
  IFC4_types[141] =
      new entity(strings[1648], false, 141, (entity *)IFC4_types[375]);
  IFC4_types[142] =
      new entity(strings[1649], false, 142, (entity *)IFC4_types[379]);
  IFC4_types[152] =
      new entity(strings[1650], false, 152, (entity *)IFC4_types[698]);
  IFC4_types[153] =
      new entity(strings[1651], true, 153, (entity *)IFC4_types[698]);
  IFC4_types[168] =
      new entity(strings[1652], false, 168, (entity *)IFC4_types[715]);
  IFC4_types[177] =
      new entity(strings[1653], false, 177, (entity *)IFC4_types[1085]);
  IFC4_types[178] =
      new entity(strings[1654], false, 178, (entity *)IFC4_types[179]);
  IFC4_types[180] =
      new entity(strings[1655], false, 180, (entity *)IFC4_types[181]);
  IFC4_types[200] =
      new entity(strings[1656], false, 200, (entity *)IFC4_types[609]);
  IFC4_types[205] =
      new entity(strings[1657], false, 205, (entity *)IFC4_types[609]);
  IFC4_types[206] =
      new entity(strings[1658], false, 206, (entity *)IFC4_types[205]);
  IFC4_types[232] =
      new entity(strings[1659], false, 232, (entity *)IFC4_types[853]);
  IFC4_types[244] =
      new entity(strings[1660], false, 244, (entity *)IFC4_types[701]);
  IFC4_types[245] =
      new entity(strings[1661], false, 245, (entity *)IFC4_types[698]);
  IFC4_types[246] =
      new entity(strings[1662], false, 246, (entity *)IFC4_types[698]);
  IFC4_types[247] =
      new entity(strings[1663], false, 247, (entity *)IFC4_types[698]);
  IFC4_types[260] =
      new entity(strings[1664], false, 260, (entity *)IFC4_types[715]);
  IFC4_types[287] =
      new entity(strings[1665], false, 287, (entity *)IFC4_types[375]);
  IFC4_types[288] =
      new entity(strings[1666], false, 288, (entity *)IFC4_types[853]);
  IFC4_types[289] =
      new entity(strings[1667], false, 289, (entity *)IFC4_types[379]);
  IFC4_types[318] =
      new entity(strings[1668], false, 318, (entity *)IFC4_types[1085]);
  IFC4_types[319] =
      new entity(strings[1669], false, 319, (entity *)IFC4_types[318]);
  IFC4_types[370] =
      new entity(strings[1670], false, 370, (entity *)IFC4_types[874]);
  IFC4_types[374] =
      new entity(strings[1671], true, 374, (entity *)IFC4_types[727]);
  IFC4_types[380] =
      new entity(strings[1672], false, 380, (entity *)IFC4_types[853]);
  IFC4_types[386] =
      new entity(strings[1673], false, 386, (entity *)IFC4_types[1085]);
  IFC4_types[388] =
      new entity(strings[1674], false, 388, (entity *)IFC4_types[1085]);
  IFC4_types[389] =
      new entity(strings[1675], false, 389, (entity *)IFC4_types[388]);
  IFC4_types[390] =
      new entity(strings[1676], false, 390, (entity *)IFC4_types[386]);
  IFC4_types[393] =
      new entity(strings[1677], false, 393, (entity *)IFC4_types[956]);
  IFC4_types[403] =
      new entity(strings[1678], false, 403, (entity *)IFC4_types[701]);
  IFC4_types[453] =
      new entity(strings[1679], false, 453, (entity *)IFC4_types[847]);
  IFC4_types[454] =
      new entity(strings[1680], true, 454, (entity *)IFC4_types[848]);
  IFC4_types[455] =
      new entity(strings[1681], false, 455, (entity *)IFC4_types[453]);
  IFC4_types[456] =
      new entity(strings[1682], false, 456, (entity *)IFC4_types[454]);
  IFC4_types[462] =
      new entity(strings[1683], false, 462, (entity *)IFC4_types[618]);
  IFC4_types[466] =
      new entity(strings[1684], false, 466, (entity *)IFC4_types[454]);
  IFC4_types[478] =
      new entity(strings[1685], false, 478, (entity *)IFC4_types[1018]);
  IFC4_types[479] =
      new entity(strings[1686], false, 479, (entity *)IFC4_types[698]);
  IFC4_types[483] =
      new entity(strings[1687], true, 483, (entity *)IFC4_types[1066]);
  IFC4_types[484] =
      new entity(strings[1688], false, 484, (entity *)IFC4_types[483]);
  IFC4_types[496] =
      new entity(strings[1689], false, 496, (entity *)IFC4_types[1081]);
  IFC4_types[509] =
      new entity(strings[1690], false, 509, (entity *)IFC4_types[874]);
  IFC4_types[528] =
      new entity(strings[1691], true, 528, (entity *)IFC4_types[454]);
  IFC4_types[529] =
      new entity(strings[1692], false, 529, (entity *)IFC4_types[528]);
  IFC4_types[530] =
      new entity(strings[1693], false, 530, (entity *)IFC4_types[528]);
  IFC4_types[531] =
      new entity(strings[1694], false, 531, (entity *)IFC4_types[528]);
  IFC4_types[532] =
      new entity(strings[1695], false, 532, (entity *)IFC4_types[528]);
  IFC4_types[533] =
      new entity(strings[1696], false, 533, (entity *)IFC4_types[532]);
  IFC4_types[541] =
      new entity(strings[1697], false, 541, (entity *)IFC4_types[618]);
  IFC4_types[544] =
      new entity(strings[1698], false, 544, (entity *)IFC4_types[1085]);
  IFC4_types[553] =
      new entity(strings[1699], false, 553, (entity *)IFC4_types[848]);
  IFC4_types[558] =
      new entity(strings[1700], false, 558, (entity *)IFC4_types[562]);
  IFC4_types[560] =
      new entity(strings[1701], false, 560, (entity *)IFC4_types[562]);
  IFC4_types[561] =
      new entity(strings[1702], false, 561, (entity *)IFC4_types[562]);
  IFC4_types[563] =
      new entity(strings[1703], false, 563, (entity *)IFC4_types[712]);
  IFC4_types[566] =
      new entity(strings[1704], false, 566, (entity *)IFC4_types[577]);
  IFC4_types[571] =
      new entity(strings[1705], false, 571, (entity *)IFC4_types[577]);
  IFC4_types[572] =
      new entity(strings[1706], false, 572, (entity *)IFC4_types[571]);
  IFC4_types[574] =
      new entity(strings[1707], false, 574, (entity *)IFC4_types[374]);
  IFC4_types[575] =
      new entity(strings[1708], false, 575, (entity *)IFC4_types[853]);
  IFC4_types[592] =
      new entity(strings[1709], false, 592, (entity *)IFC4_types[260]);
  IFC4_types[615] =
      new entity(strings[1710], true, 615, (entity *)IFC4_types[865]);
  IFC4_types[628] =
      new entity(strings[1711], false, 628, (entity *)IFC4_types[177]);
  IFC4_types[630] =
      new entity(strings[1712], false, 630, (entity *)IFC4_types[853]);
  IFC4_types[631] =
      new entity(strings[1713], false, 631, (entity *)IFC4_types[318]);
  IFC4_types[637] =
      new entity(strings[1714], true, 637, (entity *)IFC4_types[715]);
  IFC4_types[639] =
      new entity(strings[1715], false, 639, (entity *)IFC4_types[1085]);
  IFC4_types[650] =
      new entity(strings[1716], false, 650, (entity *)IFC4_types[652]);
  IFC4_types[664] =
      new entity(strings[1717], false, 664, (entity *)IFC4_types[1018]);
  IFC4_types[665] =
      new entity(strings[1718], true, 665, (entity *)IFC4_types[454]);
  IFC4_types[667] =
      new entity(strings[1719], false, 667, (entity *)IFC4_types[454]);
  IFC4_types[675] =
      new entity(strings[1720], true, 675, (entity *)IFC4_types[454]);
  IFC4_types[676] =
      new entity(strings[1721], false, 676, (entity *)IFC4_types[675]);
  IFC4_types[677] =
      new entity(strings[1722], false, 677, (entity *)IFC4_types[675]);
  IFC4_types[682] =
      new entity(strings[1723], false, 682, (entity *)IFC4_types[544]);
  IFC4_types[679] =
      new entity(strings[1724], false, 679, (entity *)IFC4_types[466]);
  IFC4_types[692] =
      new entity(strings[1725], true, 692, (entity *)IFC4_types[698]);
  IFC4_types[693] =
      new entity(strings[1726], true, 693, (entity *)IFC4_types[727]);
  IFC4_types[695] =
      new entity(strings[1727], true, 695, (entity *)IFC4_types[692]);
  IFC4_types[711] =
      new entity(strings[1728], false, 711, (entity *)IFC4_types[712]);
  IFC4_types[716] =
      new entity(strings[1729], false, 716, (entity *)IFC4_types[374]);
  IFC4_types[726] =
      new entity(strings[1730], true, 726, (entity *)IFC4_types[727]);
  IFC4_types[729] =
      new entity(strings[1731], true, 729, (entity *)IFC4_types[865]);
  IFC4_types[730] =
      new entity(strings[1732], false, 730, (entity *)IFC4_types[853]);
  IFC4_types[736] =
      new entity(strings[1733], true, 736, (entity *)IFC4_types[729]);
  IFC4_types[744] =
      new entity(strings[1734], true, 744, (entity *)IFC4_types[729]);
  IFC4_types[758] =
      new entity(strings[1735], true, 758, (entity *)IFC4_types[736]);
  IFC4_types[777] =
      new entity(strings[1736], false, 777, (entity *)IFC4_types[637]);
  IFC4_types[784] =
      new entity(strings[1737], false, 784, (entity *)IFC4_types[1081]);
  IFC4_types[785] =
      new entity(strings[1738], false, 785, (entity *)IFC4_types[693]);
  IFC4_types[813] =
      new entity(strings[1739], true, 813, (entity *)IFC4_types[865]);
  IFC4_types[851] =
      new entity(strings[1740], false, 851, (entity *)IFC4_types[853]);
  IFC4_types[852] =
      new entity(strings[1741], false, 852, (entity *)IFC4_types[853]);
  IFC4_types[856] =
      new entity(strings[1742], false, 856, (entity *)IFC4_types[874]);
  IFC4_types[870] =
      new entity(strings[1743], false, 870, (entity *)IFC4_types[777]);
  IFC4_types[879] =
      new entity(strings[1744], false, 879, (entity *)IFC4_types[693]);
  IFC4_types[880] =
      new entity(strings[1745], false, 880, (entity *)IFC4_types[693]);
  IFC4_types[877] =
      new entity(strings[1746], false, 877, (entity *)IFC4_types[454]);
  IFC4_types[895] =
      new entity(strings[1747], false, 895, (entity *)IFC4_types[454]);
  IFC4_types[896] =
      new entity(strings[1748], true, 896, (entity *)IFC4_types[726]);
  IFC4_types[910] =
      new entity(strings[1749], false, 910, (entity *)IFC4_types[956]);
  IFC4_types[915] =
      new entity(strings[1750], true, 915, (entity *)IFC4_types[454]);
  IFC4_types[970] =
      new entity(strings[1751], false, 970, (entity *)IFC4_types[977]);
  IFC4_types[972] =
      new entity(strings[1752], false, 972, (entity *)IFC4_types[977]);
  IFC4_types[973] =
      new entity(strings[1753], false, 973, (entity *)IFC4_types[977]);
  IFC4_types[974] =
      new entity(strings[1754], false, 974, (entity *)IFC4_types[973]);
  IFC4_types[975] =
      new entity(strings[1755], false, 975, (entity *)IFC4_types[977]);
  IFC4_types[976] =
      new entity(strings[1756], false, 976, (entity *)IFC4_types[975]);
  IFC4_types[1000] =
      new entity(strings[1757], false, 1000, (entity *)IFC4_types[318]);
  IFC4_types[1001] =
      new entity(strings[1758], true, 1001, (entity *)IFC4_types[454]);
  IFC4_types[1015] =
      new entity(strings[1759], false, 1015, (entity *)IFC4_types[1016]);
  IFC4_types[1019] =
      new entity(strings[1760], true, 1019, (entity *)IFC4_types[915]);
  IFC4_types[1020] =
      new entity(strings[1761], false, 1020, (entity *)IFC4_types[915]);
  IFC4_types[1021] =
      new entity(strings[1762], false, 1021, (entity *)IFC4_types[1020]);
  IFC4_types[1022] =
      new entity(strings[1763], true, 1022, (entity *)IFC4_types[1001]);
  IFC4_types[1102] =
      new entity(strings[1764], false, 1102, (entity *)IFC4_types[637]);
  IFC4_types[1052] =
      new entity(strings[1765], true, 1052, (entity *)IFC4_types[454]);
  IFC4_types[1058] =
      new entity(strings[1766], false, 1058, (entity *)IFC4_types[454]);
  IFC4_types[1059] =
      new entity(strings[1767], false, 1059, (entity *)IFC4_types[1058]);
  IFC4_types[1062] =
      new entity(strings[1768], false, 1062, (entity *)IFC4_types[695]);
  IFC4_types[1097] =
      new entity(strings[1769], false, 1097, (entity *)IFC4_types[637]);
  IFC4_types[1106] =
      new entity(strings[1770], false, 1106, (entity *)IFC4_types[615]);
  IFC4_types[1107] =
      new entity(strings[1771], true, 1107, (entity *)IFC4_types[1106]);
  IFC4_types[1108] =
      new entity(strings[1772], false, 1108, (entity *)IFC4_types[1106]);
  IFC4_types[1109] =
      new entity(strings[1773], true, 1109, (entity *)IFC4_types[1106]);
  IFC4_types[1120] =
      new entity(strings[1774], false, 1120, (entity *)IFC4_types[637]);
  IFC4_types[1126] =
      new entity(strings[1775], false, 1126, (entity *)IFC4_types[454]);
  IFC4_types[1129] =
      new entity(strings[1776], false, 1129, (entity *)IFC4_types[544]);
  IFC4_types[1157] =
      new entity(strings[1777], false, 1157, (entity *)IFC4_types[1108]);
  IFC4_types[1172] =
      new entity(strings[1778], false, 1172, (entity *)IFC4_types[637]);
  IFC4_types[143] =
      new select_type(strings[1779], 143, {IFC4_types[141], IFC4_types[142]});
  IFC4_types[144] =
      new select_type(strings[1780], 144, {IFC4_types[141], IFC4_types[142]});
  IFC4_types[215] =
      new select_type(strings[1781], 215, {IFC4_types[214], IFC4_types[453]});
  IFC4_types[258] =
      new select_type(strings[1782], 258, {IFC4_types[615], IFC4_types[729]});
  IFC4_types[290] =
      new select_type(strings[1783], 290, {IFC4_types[287], IFC4_types[289]});
  IFC4_types[467] =
      new select_type(strings[1784], 467, {IFC4_types[685], IFC4_types[1126]});
  IFC4_types[578] = new select_type(
      strings[1785], 578,
      {IFC4_types[29],   IFC4_types[45],   IFC4_types[161], IFC4_types[199],
       IFC4_types[221],  IFC4_types[264],  IFC4_types[327], IFC4_types[516],
       IFC4_types[548],  IFC4_types[556],  IFC4_types[610], IFC4_types[611],
       IFC4_types[613],  IFC4_types[638],  IFC4_types[670], IFC4_types[685],
       IFC4_types[686],  IFC4_types[687],  IFC4_types[772], IFC4_types[914],
       IFC4_types[1076], IFC4_types[1078], IFC4_types[1138]});
  IFC4_types[678] =
      new select_type(strings[1786], 678, {IFC4_types[675], IFC4_types[1130]});
  IFC4_types[703] =
      new select_type(strings[1787], 703,
                      {IFC4_types[244], IFC4_types[403], IFC4_types[612],
                       IFC4_types[1011], IFC4_types[1061]});
  IFC4_types[713] =
      new select_type(strings[1788], 713, {IFC4_types[711], IFC4_types[849]});
  IFC4_types[738] = new type_declaration(
      strings[1789], 738,
      new aggregation_type(aggregation_type::set_type, 1, -1,
                           new named_type(IFC4_types[736])));
  IFC4_types[854] = new select_type(
      strings[1790], 854,
      {IFC4_types[7], IFC4_types[36], IFC4_types[38], IFC4_types[185],
       IFC4_types[200], IFC4_types[205], IFC4_types[375], IFC4_types[379],
       IFC4_types[562], IFC4_types[629], IFC4_types[647], IFC4_types[648],
       IFC4_types[652], IFC4_types[715], IFC4_types[727], IFC4_types[1081]});
  IFC4_types[1057] =
      new select_type(strings[1791], 1057, {IFC4_types[378], IFC4_types[695]});
  IFC4_types[1121] = new select_type(
      strings[1792], 1121, {IFC4_types[259], IFC4_types[578], IFC4_types[899]});
  IFC4_types[16] =
      new entity(strings[1793], false, 16, (entity *)IFC4_types[390]);
  IFC4_types[34] =
      new entity(strings[1794], false, 34, (entity *)IFC4_types[454]);
  IFC4_types[49] =
      new entity(strings[1795], false, 49, (entity *)IFC4_types[637]);
  IFC4_types[53] =
      new entity(strings[1796], false, 53, (entity *)IFC4_types[665]);
  IFC4_types[55] =
      new entity(strings[1797], false, 55, (entity *)IFC4_types[665]);
  IFC4_types[56] =
      new entity(strings[1798], false, 56, (entity *)IFC4_types[665]);
  IFC4_types[73] =
      new entity(strings[1799], false, 73, (entity *)IFC4_types[454]);
  IFC4_types[81] =
      new entity(strings[1800], true, 81, (entity *)IFC4_types[1001]);
  IFC4_types[82] =
      new entity(strings[1801], false, 82, (entity *)IFC4_types[454]);
  IFC4_types[84] =
      new entity(strings[1802], false, 84, (entity *)IFC4_types[466]);
  IFC4_types[231] =
      new entity(strings[1803], false, 231, (entity *)IFC4_types[637]);
  IFC4_types[119] =
      new entity(strings[1804], false, 119, (entity *)IFC4_types[675]);
  IFC4_types[120] =
      new entity(strings[1805], true, 120, (entity *)IFC4_types[454]);
  IFC4_types[121] =
      new entity(strings[1806], false, 121, (entity *)IFC4_types[120]);
  IFC4_types[122] =
      new entity(strings[1807], false, 122, (entity *)IFC4_types[120]);
  IFC4_types[123] =
      new entity(strings[1808], true, 123, (entity *)IFC4_types[454]);
  IFC4_types[124] =
      new entity(strings[1809], false, 124, (entity *)IFC4_types[123]);
  IFC4_types[125] =
      new entity(strings[1810], false, 125, (entity *)IFC4_types[124]);
  IFC4_types[126] =
      new entity(strings[1811], false, 126, (entity *)IFC4_types[123]);
  IFC4_types[127] =
      new entity(strings[1812], false, 127, (entity *)IFC4_types[126]);
  IFC4_types[138] =
      new entity(strings[1813], false, 138, (entity *)IFC4_types[637]);
  IFC4_types[145] =
      new entity(strings[1814], false, 145, (entity *)IFC4_types[177]);
  IFC4_types[151] =
      new entity(strings[1815], false, 151, (entity *)IFC4_types[153]);
  IFC4_types[162] =
      new entity(strings[1816], false, 162, (entity *)IFC4_types[726]);
  IFC4_types[167] =
      new entity(strings[1817], false, 167, (entity *)IFC4_types[454]);
  IFC4_types[197] =
      new entity(strings[1818], true, 197, (entity *)IFC4_types[1109]);
  IFC4_types[198] =
      new entity(strings[1819], true, 198, (entity *)IFC4_types[615]);
  IFC4_types[226] =
      new entity(strings[1820], false, 226, (entity *)IFC4_types[197]);
  IFC4_types[228] =
      new entity(strings[1821], true, 228, (entity *)IFC4_types[454]);
  IFC4_types[230] =
      new entity(strings[1822], false, 230, (entity *)IFC4_types[915]);
  IFC4_types[237] =
      new entity(strings[1823], true, 237, (entity *)IFC4_types[454]);
  IFC4_types[238] =
      new entity(strings[1824], false, 238, (entity *)IFC4_types[81]);
  IFC4_types[239] =
      new entity(strings[1825], false, 239, (entity *)IFC4_types[81]);
  IFC4_types[267] =
      new entity(strings[1826], false, 267, (entity *)IFC4_types[454]);
  IFC4_types[298] =
      new entity(strings[1827], false, 298, (entity *)IFC4_types[1108]);
  IFC4_types[320] =
      new entity(strings[1828], false, 320, (entity *)IFC4_types[544]);
  IFC4_types[353] =
      new entity(strings[1829], false, 353, (entity *)IFC4_types[758]);
  IFC4_types[354] =
      new entity(strings[1830], true, 354, (entity *)IFC4_types[1108]);
  IFC4_types[346] =
      new entity(strings[1831], true, 346, (entity *)IFC4_types[1001]);
  IFC4_types[356] =
      new entity(strings[1832], false, 356, (entity *)IFC4_types[637]);
  IFC4_types[372] =
      new entity(strings[1833], false, 372, (entity *)IFC4_types[1107]);
  IFC4_types[384] =
      new entity(strings[1834], false, 384, (entity *)IFC4_types[1019]);
  IFC4_types[385] =
      new entity(strings[1835], false, 385, (entity *)IFC4_types[384]);
  IFC4_types[387] =
      new entity(strings[1836], false, 387, (entity *)IFC4_types[454]);
  IFC4_types[404] =
      new entity(strings[1837], false, 404, (entity *)IFC4_types[454]);
  IFC4_types[405] =
      new entity(strings[1838], false, 405, (entity *)IFC4_types[454]);
  IFC4_types[413] =
      new entity(strings[1839], false, 413, (entity *)IFC4_types[1019]);
  IFC4_types[444] =
      new entity(strings[1840], false, 444, (entity *)IFC4_types[354]);
  IFC4_types[446] =
      new entity(strings[1841], false, 446, (entity *)IFC4_types[444]);
  IFC4_types[449] =
      new entity(strings[1842], false, 449, (entity *)IFC4_types[354]);
  IFC4_types[451] =
      new entity(strings[1843], false, 451, (entity *)IFC4_types[456]);
  IFC4_types[498] =
      new entity(strings[1844], false, 498, (entity *)IFC4_types[637]);
  IFC4_types[481] =
      new entity(strings[1845], false, 481, (entity *)IFC4_types[1052]);
  IFC4_types[482] =
      new entity(strings[1846], false, 482, (entity *)IFC4_types[481]);
  IFC4_types[545] =
      new entity(strings[1847], false, 545, (entity *)IFC4_types[637]);
  IFC4_types[507] =
      new entity(strings[1848], false, 507, (entity *)IFC4_types[197]);
  IFC4_types[534] =
      new entity(strings[1849], false, 534, (entity *)IFC4_types[237]);
  IFC4_types[551] =
      new entity(strings[1850], true, 551, (entity *)IFC4_types[915]);
  IFC4_types[614] =
      new entity(strings[1851], true, 614, (entity *)IFC4_types[615]);
  IFC4_types[623] =
      new entity(strings[1852], false, 623, (entity *)IFC4_types[237]);
  IFC4_types[624] =
      new entity(strings[1853], false, 624, (entity *)IFC4_types[237]);
  IFC4_types[640] =
      new entity(strings[1854], false, 640, (entity *)IFC4_types[237]);
  IFC4_types[666] =
      new entity(strings[1855], false, 666, (entity *)IFC4_types[667]);
  IFC4_types[669] =
      new entity(strings[1856], false, 669, (entity *)IFC4_types[346]);
  IFC4_types[690] =
      new entity(strings[1857], true, 690, (entity *)IFC4_types[692]);
  IFC4_types[691] =
      new entity(strings[1858], true, 691, (entity *)IFC4_types[692]);
  IFC4_types[694] =
      new entity(strings[1859], true, 694, (entity *)IFC4_types[736]);
  IFC4_types[706] =
      new entity(strings[1860], false, 706, (entity *)IFC4_types[1107]);
  IFC4_types[708] =
      new entity(strings[1861], true, 708, (entity *)IFC4_types[614]);
  IFC4_types[710] =
      new entity(strings[1862], true, 710, (entity *)IFC4_types[614]);
  IFC4_types[718] =
      new entity(strings[1863], false, 718, (entity *)IFC4_types[198]);
  IFC4_types[723] =
      new entity(strings[1864], false, 723, (entity *)IFC4_types[198]);
  IFC4_types[728] =
      new entity(strings[1865], false, 728, (entity *)IFC4_types[896]);
  IFC4_types[731] =
      new entity(strings[1866], false, 731, (entity *)IFC4_types[896]);
  IFC4_types[733] =
      new entity(strings[1867], false, 733, (entity *)IFC4_types[896]);
  IFC4_types[734] =
      new entity(strings[1868], false, 734, (entity *)IFC4_types[896]);
  IFC4_types[735] =
      new entity(strings[1869], false, 735, (entity *)IFC4_types[736]);
  IFC4_types[739] =
      new entity(strings[1870], false, 739, (entity *)IFC4_types[744]);
  IFC4_types[741] =
      new entity(strings[1871], false, 741, (entity *)IFC4_types[896]);
  IFC4_types[742] =
      new entity(strings[1872], false, 742, (entity *)IFC4_types[896]);
  IFC4_types[743] =
      new entity(strings[1873], true, 743, (entity *)IFC4_types[744]);
  IFC4_types[751] =
      new entity(strings[1874], false, 751, (entity *)IFC4_types[710]);
  IFC4_types[776] =
      new entity(strings[1875], false, 776, (entity *)IFC4_types[777]);
  IFC4_types[778] =
      new entity(strings[1876], false, 778, (entity *)IFC4_types[228]);
  IFC4_types[779] =
      new entity(strings[1877], false, 779, (entity *)IFC4_types[81]);
  IFC4_types[786] =
      new entity(strings[1878], false, 786, (entity *)IFC4_types[694]);
  IFC4_types[798] =
      new entity(strings[1879], true, 798, (entity *)IFC4_types[813]);
  IFC4_types[799] =
      new entity(strings[1880], false, 799, (entity *)IFC4_types[798]);
  IFC4_types[800] =
      new entity(strings[1881], false, 800, (entity *)IFC4_types[798]);
  IFC4_types[801] =
      new entity(strings[1882], false, 801, (entity *)IFC4_types[798]);
  IFC4_types[802] =
      new entity(strings[1883], false, 802, (entity *)IFC4_types[801]);
  IFC4_types[803] =
      new entity(strings[1884], false, 803, (entity *)IFC4_types[798]);
  IFC4_types[804] =
      new entity(strings[1885], false, 804, (entity *)IFC4_types[798]);
  IFC4_types[805] =
      new entity(strings[1886], false, 805, (entity *)IFC4_types[798]);
  IFC4_types[806] =
      new entity(strings[1887], true, 806, (entity *)IFC4_types[813]);
  IFC4_types[807] =
      new entity(strings[1888], false, 807, (entity *)IFC4_types[806]);
  IFC4_types[808] =
      new entity(strings[1889], false, 808, (entity *)IFC4_types[806]);
  IFC4_types[809] =
      new entity(strings[1890], false, 809, (entity *)IFC4_types[806]);
  IFC4_types[810] =
      new entity(strings[1891], false, 810, (entity *)IFC4_types[806]);
  IFC4_types[811] =
      new entity(strings[1892], false, 811, (entity *)IFC4_types[806]);
  IFC4_types[812] =
      new entity(strings[1893], false, 812, (entity *)IFC4_types[806]);
  IFC4_types[814] =
      new entity(strings[1894], true, 814, (entity *)IFC4_types[813]);
  IFC4_types[815] =
      new entity(strings[1895], false, 815, (entity *)IFC4_types[814]);
  IFC4_types[816] =
      new entity(strings[1896], false, 816, (entity *)IFC4_types[815]);
  IFC4_types[818] =
      new entity(strings[1897], false, 818, (entity *)IFC4_types[814]);
  IFC4_types[817] =
      new entity(strings[1898], false, 817, (entity *)IFC4_types[814]);
  IFC4_types[819] =
      new entity(strings[1899], false, 819, (entity *)IFC4_types[814]);
  IFC4_types[820] =
      new entity(strings[1900], false, 820, (entity *)IFC4_types[814]);
  IFC4_types[821] =
      new entity(strings[1901], false, 821, (entity *)IFC4_types[820]);
  IFC4_types[822] =
      new entity(strings[1902], false, 822, (entity *)IFC4_types[815]);
  IFC4_types[823] =
      new entity(strings[1903], false, 823, (entity *)IFC4_types[814]);
  IFC4_types[824] =
      new entity(strings[1904], false, 824, (entity *)IFC4_types[814]);
  IFC4_types[825] =
      new entity(strings[1905], false, 825, (entity *)IFC4_types[814]);
  IFC4_types[826] =
      new entity(strings[1906], false, 826, (entity *)IFC4_types[813]);
  IFC4_types[827] =
      new entity(strings[1907], true, 827, (entity *)IFC4_types[813]);
  IFC4_types[828] =
      new entity(strings[1908], true, 828, (entity *)IFC4_types[813]);
  IFC4_types[829] =
      new entity(strings[1909], false, 829, (entity *)IFC4_types[828]);
  IFC4_types[830] =
      new entity(strings[1910], false, 830, (entity *)IFC4_types[828]);
  IFC4_types[831] =
      new entity(strings[1911], false, 831, (entity *)IFC4_types[828]);
  IFC4_types[832] =
      new entity(strings[1912], false, 832, (entity *)IFC4_types[828]);
  IFC4_types[833] =
      new entity(strings[1913], false, 833, (entity *)IFC4_types[814]);
  IFC4_types[834] =
      new entity(strings[1914], false, 834, (entity *)IFC4_types[814]);
  IFC4_types[835] =
      new entity(strings[1915], false, 835, (entity *)IFC4_types[814]);
  IFC4_types[836] =
      new entity(strings[1916], false, 836, (entity *)IFC4_types[827]);
  IFC4_types[837] =
      new entity(strings[1917], false, 837, (entity *)IFC4_types[827]);
  IFC4_types[838] =
      new entity(strings[1918], false, 838, (entity *)IFC4_types[814]);
  IFC4_types[839] =
      new entity(strings[1919], false, 839, (entity *)IFC4_types[814]);
  IFC4_types[840] =
      new entity(strings[1920], false, 840, (entity *)IFC4_types[814]);
  IFC4_types[841] =
      new entity(strings[1921], false, 841, (entity *)IFC4_types[814]);
  IFC4_types[842] =
      new entity(strings[1922], false, 842, (entity *)IFC4_types[841]);
  IFC4_types[843] =
      new entity(strings[1923], false, 843, (entity *)IFC4_types[842]);
  IFC4_types[844] =
      new entity(strings[1924], false, 844, (entity *)IFC4_types[827]);
  IFC4_types[845] =
      new entity(strings[1925], false, 845, (entity *)IFC4_types[167]);
  IFC4_types[850] =
      new entity(strings[1926], true, 850, (entity *)IFC4_types[614]);
  IFC4_types[857] =
      new entity(strings[1927], false, 857, (entity *)IFC4_types[1019]);
  IFC4_types[858] =
      new entity(strings[1928], false, 858, (entity *)IFC4_types[857]);
  IFC4_types[859] =
      new entity(strings[1929], false, 859, (entity *)IFC4_types[228]);
  IFC4_types[860] =
      new entity(strings[1930], false, 860, (entity *)IFC4_types[228]);
  IFC4_types[897] =
      new entity(strings[1931], false, 897, (entity *)IFC4_types[743]);
  IFC4_types[928] =
      new entity(strings[1932], true, 928, (entity *)IFC4_types[710]);
  IFC4_types[929] =
      new entity(strings[1933], true, 929, (entity *)IFC4_types[1108]);
  IFC4_types[930] =
      new entity(strings[1934], true, 930, (entity *)IFC4_types[928]);
  IFC4_types[931] =
      new entity(strings[1935], true, 931, (entity *)IFC4_types[929]);
  IFC4_types[932] =
      new entity(strings[1936], false, 932, (entity *)IFC4_types[928]);
  IFC4_types[933] =
      new entity(strings[1937], false, 933, (entity *)IFC4_types[929]);
  IFC4_types[939] =
      new entity(strings[1938], false, 939, (entity *)IFC4_types[228]);
  IFC4_types[940] =
      new entity(strings[1939], false, 940, (entity *)IFC4_types[346]);
  IFC4_types[952] =
      new entity(strings[1940], true, 952, (entity *)IFC4_types[710]);
  IFC4_types[964] =
      new entity(strings[1941], true, 964, (entity *)IFC4_types[710]);
  IFC4_types[979] =
      new entity(strings[1942], true, 979, (entity *)IFC4_types[964]);
  IFC4_types[984] =
      new entity(strings[1943], true, 984, (entity *)IFC4_types[952]);
  IFC4_types[989] =
      new entity(strings[1944], false, 989, (entity *)IFC4_types[979]);
  IFC4_types[991] =
      new entity(strings[1945], false, 991, (entity *)IFC4_types[989]);
  IFC4_types[992] =
      new entity(strings[1946], false, 992, (entity *)IFC4_types[984]);
  IFC4_types[998] =
      new entity(strings[1947], false, 998, (entity *)IFC4_types[197]);
  IFC4_types[1002] =
      new entity(strings[1948], false, 1002, (entity *)IFC4_types[237]);
  IFC4_types[1003] =
      new entity(strings[1949], false, 1003, (entity *)IFC4_types[1019]);
  IFC4_types[1006] =
      new entity(strings[1950], false, 1006, (entity *)IFC4_types[1022]);
  IFC4_types[1007] =
      new entity(strings[1951], false, 1007, (entity *)IFC4_types[1022]);
  IFC4_types[1028] =
      new entity(strings[1952], false, 1028, (entity *)IFC4_types[444]);
  IFC4_types[1036] =
      new entity(strings[1953], false, 1036, (entity *)IFC4_types[708]);
  IFC4_types[1040] =
      new entity(strings[1954], false, 1040, (entity *)IFC4_types[1107]);
  IFC4_types[1051] =
      new entity(strings[1955], true, 1051, (entity *)IFC4_types[1052]);
  IFC4_types[1087] =
      new entity(strings[1956], false, 1087, (entity *)IFC4_types[346]);
  IFC4_types[1095] =
      new entity(strings[1957], false, 1095, (entity *)IFC4_types[354]);
  IFC4_types[1098] =
      new entity(strings[1958], false, 1098, (entity *)IFC4_types[1051]);
  IFC4_types[1152] =
      new entity(strings[1959], false, 1152, (entity *)IFC4_types[694]);
  IFC4_types[1155] =
      new entity(strings[1960], false, 1155, (entity *)IFC4_types[694]);
  IFC4_types[37] = new select_type(
      strings[1961], 37, {IFC4_types[579], IFC4_types[782], IFC4_types[1121]});
  IFC4_types[54] =
      new select_type(strings[1962], 54, {IFC4_types[55], IFC4_types[56]});
  IFC4_types[71] =
      new select_type(strings[1963], 71,
                      {IFC4_types[73], IFC4_types[228], IFC4_types[466],
                       IFC4_types[915], IFC4_types[1051]});
  IFC4_types[149] =
      new select_type(strings[1964], 149, {IFC4_types[153], IFC4_types[690]});
  IFC4_types[150] =
      new select_type(strings[1965], 150, {IFC4_types[151], IFC4_types[611]});
  IFC4_types[229] =
      new select_type(strings[1966], 229, {IFC4_types[73], IFC4_types[228]});
  IFC4_types[248] =
      new select_type(strings[1967], 248, {IFC4_types[245], IFC4_types[691]});
  IFC4_types[406] = new select_type(
      strings[1968], 406,
      {IFC4_types[149], IFC4_types[376], IFC4_types[404], IFC4_types[405]});
  IFC4_types[457] = new select_type(
      strings[1969], 457, {IFC4_types[237], IFC4_types[675], IFC4_types[1001]});
  IFC4_types[463] =
      new select_type(strings[1970], 463, {IFC4_types[267], IFC4_types[1135]});
  IFC4_types[591] =
      new select_type(strings[1971], 591,
                      {IFC4_types[36], IFC4_types[579], IFC4_types[782],
                       IFC4_types[1030], IFC4_types[1081], IFC4_types[1121]});
  IFC4_types[709] =
      new select_type(strings[1972], 709, {IFC4_types[708], IFC4_types[1107]});
  IFC4_types[714] =
      new select_type(strings[1973], 714, {IFC4_types[710], IFC4_types[1108]});
  IFC4_types[737] =
      new select_type(strings[1974], 737, {IFC4_types[736], IFC4_types[738]});
  IFC4_types[855] =
      new select_type(strings[1975], 855, {IFC4_types[850], IFC4_types[1109]});
  IFC4_types[894] =
      new select_type(strings[1976], 894, {IFC4_types[145], IFC4_types[628]});
  IFC4_types[916] =
      new select_type(strings[1977], 916, {IFC4_types[145], IFC4_types[915]});
  IFC4_types[1008] =
      new select_type(strings[1978], 1008,
                      {IFC4_types[387], IFC4_types[390], IFC4_types[1001]});
  IFC4_types[1101] =
      new select_type(strings[1979], 1101, {IFC4_types[119], IFC4_types[638]});
  IFC4_types[1127] =
      new select_type(strings[1980], 1127, {IFC4_types[267], IFC4_types[1126]});
  IFC4_types[6] =
      new entity(strings[1981], false, 6, (entity *)IFC4_types[614]);
  IFC4_types[14] =
      new entity(strings[1982], false, 14, (entity *)IFC4_types[551]);
  IFC4_types[15] =
      new entity(strings[1983], false, 15, (entity *)IFC4_types[14]);
  IFC4_types[33] =
      new entity(strings[1984], false, 33, (entity *)IFC4_types[710]);
  IFC4_types[88] =
      new entity(strings[1985], true, 88, (entity *)IFC4_types[81]);
  IFC4_types[90] =
      new entity(strings[1986], false, 90, (entity *)IFC4_types[88]);
  IFC4_types[65] =
      new entity(strings[1987], false, 65, (entity *)IFC4_types[228]);
  IFC4_types[70] =
      new entity(strings[1988], false, 70, (entity *)IFC4_types[73]);
  IFC4_types[80] =
      new entity(strings[1989], true, 80, (entity *)IFC4_types[237]);
  IFC4_types[91] =
      new entity(strings[1990], false, 91, (entity *)IFC4_types[930]);
  IFC4_types[99] =
      new entity(strings[1991], true, 99, (entity *)IFC4_types[354]);
  IFC4_types[100] =
      new entity(strings[1992], false, 100, (entity *)IFC4_types[930]);
  IFC4_types[134] =
      new entity(strings[1993], false, 134, (entity *)IFC4_types[99]);
  IFC4_types[137] =
      new entity(strings[1994], false, 137, (entity *)IFC4_types[138]);
  IFC4_types[140] =
      new entity(strings[1995], false, 140, (entity *)IFC4_types[354]);
  IFC4_types[156] =
      new entity(strings[1996], false, 156, (entity *)IFC4_types[99]);
  IFC4_types[163] =
      new entity(strings[1997], false, 163, (entity *)IFC4_types[743]);
  IFC4_types[165] =
      new entity(strings[1998], false, 165, (entity *)IFC4_types[80]);
  IFC4_types[166] =
      new entity(strings[1999], false, 166, (entity *)IFC4_types[165]);
  IFC4_types[176] =
      new entity(strings[2000], true, 176, (entity *)IFC4_types[237]);
  IFC4_types[188] =
      new entity(strings[2001], false, 188, (entity *)IFC4_types[197]);
  IFC4_types[191] =
      new entity(strings[2002], false, 191, (entity *)IFC4_types[197]);
  IFC4_types[194] =
      new entity(strings[2003], false, 194, (entity *)IFC4_types[197]);
  IFC4_types[196] =
      new entity(strings[2004], true, 196, (entity *)IFC4_types[850]);
  IFC4_types[201] =
      new entity(strings[2005], true, 201, (entity *)IFC4_types[614]);
  IFC4_types[216] =
      new entity(strings[2006], false, 216, (entity *)IFC4_types[201]);
  IFC4_types[218] =
      new entity(strings[2007], false, 218, (entity *)IFC4_types[201]);
  IFC4_types[223] =
      new entity(strings[2008], false, 223, (entity *)IFC4_types[99]);
  IFC4_types[225] =
      new entity(strings[2009], false, 225, (entity *)IFC4_types[196]);
  IFC4_types[234] =
      new entity(strings[2010], false, 234, (entity *)IFC4_types[99]);
  IFC4_types[249] =
      new entity(strings[2011], false, 249, (entity *)IFC4_types[346]);
  IFC4_types[279] =
      new entity(strings[2012], false, 279, (entity *)IFC4_types[354]);
  IFC4_types[281] =
      new entity(strings[2013], true, 281, (entity *)IFC4_types[279]);
  IFC4_types[293] =
      new entity(strings[2014], false, 293, (entity *)IFC4_types[694]);
  IFC4_types[296] =
      new entity(strings[2015], false, 296, (entity *)IFC4_types[694]);
  IFC4_types[301] =
      new entity(strings[2016], false, 301, (entity *)IFC4_types[99]);
  IFC4_types[305] =
      new entity(strings[2017], false, 305, (entity *)IFC4_types[690]);
  IFC4_types[306] =
      new entity(strings[2018], false, 306, (entity *)IFC4_types[691]);
  IFC4_types[345] =
      new entity(strings[2019], true, 345, (entity *)IFC4_types[710]);
  IFC4_types[347] =
      new entity(strings[2020], false, 347, (entity *)IFC4_types[345]);
  IFC4_types[348] =
      new entity(strings[2021], false, 348, (entity *)IFC4_types[354]);
  IFC4_types[350] =
      new entity(strings[2022], true, 350, (entity *)IFC4_types[345]);
  IFC4_types[351] =
      new entity(strings[2023], true, 351, (entity *)IFC4_types[354]);
  IFC4_types[355] =
      new entity(strings[2024], false, 355, (entity *)IFC4_types[176]);
  IFC4_types[358] =
      new entity(strings[2025], true, 358, (entity *)IFC4_types[281]);
  IFC4_types[361] =
      new entity(strings[2026], false, 361, (entity *)IFC4_types[358]);
  IFC4_types[364] =
      new entity(strings[2027], false, 364, (entity *)IFC4_types[358]);
  IFC4_types[367] =
      new entity(strings[2028], false, 367, (entity *)IFC4_types[358]);
  IFC4_types[369] =
      new entity(strings[2029], false, 369, (entity *)IFC4_types[708]);
  IFC4_types[383] =
      new entity(strings[2030], true, 383, (entity *)IFC4_types[928]);
  IFC4_types[391] =
      new entity(strings[2031], false, 391, (entity *)IFC4_types[551]);
  IFC4_types[392] =
      new entity(strings[2032], false, 392, (entity *)IFC4_types[391]);
  IFC4_types[397] =
      new entity(strings[2033], false, 397, (entity *)IFC4_types[350]);
  IFC4_types[398] =
      new entity(strings[2034], false, 398, (entity *)IFC4_types[351]);
  IFC4_types[400] =
      new entity(strings[2035], true, 400, (entity *)IFC4_types[345]);
  IFC4_types[401] =
      new entity(strings[2036], true, 401, (entity *)IFC4_types[400]);
  IFC4_types[402] =
      new entity(strings[2037], true, 402, (entity *)IFC4_types[400]);
  IFC4_types[415] =
      new entity(strings[2038], true, 415, (entity *)IFC4_types[281]);
  IFC4_types[418] =
      new entity(strings[2039], true, 418, (entity *)IFC4_types[281]);
  IFC4_types[423] =
      new entity(strings[2040], false, 423, (entity *)IFC4_types[415]);
  IFC4_types[426] =
      new entity(strings[2041], true, 426, (entity *)IFC4_types[281]);
  IFC4_types[428] =
      new entity(strings[2042], true, 428, (entity *)IFC4_types[281]);
  IFC4_types[430] =
      new entity(strings[2043], true, 430, (entity *)IFC4_types[281]);
  IFC4_types[432] =
      new entity(strings[2044], true, 432, (entity *)IFC4_types[281]);
  IFC4_types[434] =
      new entity(strings[2045], true, 434, (entity *)IFC4_types[281]);
  IFC4_types[439] =
      new entity(strings[2046], false, 439, (entity *)IFC4_types[99]);
  IFC4_types[443] =
      new entity(strings[2047], false, 443, (entity *)IFC4_types[345]);
  IFC4_types[445] =
      new entity(strings[2048], false, 445, (entity *)IFC4_types[443]);
  IFC4_types[448] =
      new entity(strings[2049], false, 448, (entity *)IFC4_types[345]);
  IFC4_types[460] =
      new entity(strings[2050], false, 460, (entity *)IFC4_types[710]);
  IFC4_types[465] =
      new entity(strings[2051], false, 465, (entity *)IFC4_types[614]);
  IFC4_types[469] =
      new entity(strings[2052], false, 469, (entity *)IFC4_types[358]);
  IFC4_types[474] =
      new entity(strings[2053], false, 474, (entity *)IFC4_types[358]);
  IFC4_types[480] =
      new entity(strings[2054], false, 480, (entity *)IFC4_types[80]);
  IFC4_types[489] =
      new entity(strings[2055], false, 489, (entity *)IFC4_types[434]);
  IFC4_types[492] =
      new entity(strings[2056], false, 492, (entity *)IFC4_types[1002]);
  IFC4_types[493] =
      new entity(strings[2057], false, 493, (entity *)IFC4_types[465]);
  IFC4_types[501] =
      new entity(strings[2058], false, 501, (entity *)IFC4_types[418]);
  IFC4_types[506] =
      new entity(strings[2059], false, 506, (entity *)IFC4_types[196]);
  IFC4_types[511] =
      new entity(strings[2060], false, 511, (entity *)IFC4_types[432]);
  IFC4_types[525] =
      new entity(strings[2061], false, 525, (entity *)IFC4_types[432]);
  IFC4_types[580] =
      new entity(strings[2062], false, 580, (entity *)IFC4_types[350]);
  IFC4_types[581] =
      new entity(strings[2063], false, 581, (entity *)IFC4_types[351]);
  IFC4_types[584] =
      new entity(strings[2064], false, 584, (entity *)IFC4_types[432]);
  IFC4_types[588] =
      new entity(strings[2065], false, 588, (entity *)IFC4_types[99]);
  IFC4_types[607] =
      new entity(strings[2066], false, 607, (entity *)IFC4_types[358]);
  IFC4_types[621] =
      new entity(strings[2067], false, 621, (entity *)IFC4_types[6]);
  IFC4_types[625] =
      new entity(strings[2068], false, 625, (entity *)IFC4_types[402]);
  IFC4_types[627] =
      new entity(strings[2069], false, 627, (entity *)IFC4_types[625]);
  IFC4_types[634] =
      new entity(strings[2070], false, 634, (entity *)IFC4_types[432]);
  IFC4_types[641] =
      new entity(strings[2071], false, 641, (entity *)IFC4_types[201]);
  IFC4_types[644] =
      new entity(strings[2072], false, 644, (entity *)IFC4_types[694]);
  IFC4_types[645] =
      new entity(strings[2073], false, 645, (entity *)IFC4_types[201]);
  IFC4_types[656] =
      new entity(strings[2074], false, 656, (entity *)IFC4_types[99]);
  IFC4_types[659] =
      new entity(strings[2075], false, 659, (entity *)IFC4_types[418]);
  IFC4_types[662] =
      new entity(strings[2076], false, 662, (entity *)IFC4_types[428]);
  IFC4_types[673] =
      new entity(strings[2077], false, 673, (entity *)IFC4_types[99]);
  IFC4_types[680] =
      new entity(strings[2078], false, 680, (entity *)IFC4_types[1051]);
  IFC4_types[681] =
      new entity(strings[2079], false, 681, (entity *)IFC4_types[80]);
  IFC4_types[683] =
      new entity(strings[2080], true, 683, (entity *)IFC4_types[710]);
  IFC4_types[705] =
      new entity(strings[2081], false, 705, (entity *)IFC4_types[708]);
  IFC4_types[724] =
      new entity(strings[2082], false, 724, (entity *)IFC4_types[201]);
  IFC4_types[721] =
      new entity(strings[2083], false, 721, (entity *)IFC4_types[401]);
  IFC4_types[749] =
      new entity(strings[2084], false, 749, (entity *)IFC4_types[415]);
  IFC4_types[753] =
      new entity(strings[2085], false, 753, (entity *)IFC4_types[426]);
  IFC4_types[764] =
      new entity(strings[2086], false, 764, (entity *)IFC4_types[99]);
  IFC4_types[768] =
      new entity(strings[2087], false, 768, (entity *)IFC4_types[99]);
  IFC4_types[770] =
      new entity(strings[2088], false, 770, (entity *)IFC4_types[99]);
  IFC4_types[774] =
      new entity(strings[2089], false, 774, (entity *)IFC4_types[90]);
  IFC4_types[792] =
      new entity(strings[2090], true, 792, (entity *)IFC4_types[350]);
  IFC4_types[793] =
      new entity(strings[2091], true, 793, (entity *)IFC4_types[351]);
  IFC4_types[794] =
      new entity(strings[2092], false, 794, (entity *)IFC4_types[792]);
  IFC4_types[795] =
      new entity(strings[2093], false, 795, (entity *)IFC4_types[793]);
  IFC4_types[797] =
      new entity(strings[2094], false, 797, (entity *)IFC4_types[827]);
  IFC4_types[863] =
      new entity(strings[2095], false, 863, (entity *)IFC4_types[99]);
  IFC4_types[872] =
      new entity(strings[2096], false, 872, (entity *)IFC4_types[432]);
  IFC4_types[875] =
      new entity(strings[2097], false, 875, (entity *)IFC4_types[1002]);
  IFC4_types[888] =
      new entity(strings[2098], false, 888, (entity *)IFC4_types[99]);
  IFC4_types[901] =
      new entity(strings[2099], false, 901, (entity *)IFC4_types[930]);
  IFC4_types[908] =
      new entity(strings[2100], false, 908, (entity *)IFC4_types[99]);
  IFC4_types[912] =
      new entity(strings[2101], false, 912, (entity *)IFC4_types[358]);
  IFC4_types[921] =
      new entity(strings[2102], false, 921, (entity *)IFC4_types[930]);
  IFC4_types[924] =
      new entity(strings[2103], false, 924, (entity *)IFC4_types[432]);
  IFC4_types[926] =
      new entity(strings[2104], false, 926, (entity *)IFC4_types[931]);
  IFC4_types[942] =
      new entity(strings[2105], false, 942, (entity *)IFC4_types[432]);
  IFC4_types[946] =
      new entity(strings[2106], false, 946, (entity *)IFC4_types[99]);
  IFC4_types[948] =
      new entity(strings[2107], false, 948, (entity *)IFC4_types[99]);
  IFC4_types[951] =
      new entity(strings[2108], true, 951, (entity *)IFC4_types[952]);
  IFC4_types[955] =
      new entity(strings[2109], true, 955, (entity *)IFC4_types[964]);
  IFC4_types[957] =
      new entity(strings[2110], false, 957, (entity *)IFC4_types[951]);
  IFC4_types[959] =
      new entity(strings[2111], false, 959, (entity *)IFC4_types[955]);
  IFC4_types[960] =
      new entity(strings[2112], false, 960, (entity *)IFC4_types[979]);
  IFC4_types[962] =
      new entity(strings[2113], false, 962, (entity *)IFC4_types[960]);
  IFC4_types[963] =
      new entity(strings[2114], false, 963, (entity *)IFC4_types[984]);
  IFC4_types[965] =
      new entity(strings[2115], false, 965, (entity *)IFC4_types[957]);
  IFC4_types[969] =
      new entity(strings[2116], false, 969, (entity *)IFC4_types[465]);
  IFC4_types[981] =
      new entity(strings[2117], false, 981, (entity *)IFC4_types[951]);
  IFC4_types[982] =
      new entity(strings[2118], false, 982, (entity *)IFC4_types[955]);
  IFC4_types[983] =
      new entity(strings[2119], false, 983, (entity *)IFC4_types[984]);
  IFC4_types[985] =
      new entity(strings[2120], false, 985, (entity *)IFC4_types[465]);
  IFC4_types[986] =
      new entity(strings[2121], false, 986, (entity *)IFC4_types[951]);
  IFC4_types[988] =
      new entity(strings[2122], false, 988, (entity *)IFC4_types[955]);
  IFC4_types[997] =
      new entity(strings[2123], false, 997, (entity *)IFC4_types[196]);
  IFC4_types[1004] =
      new entity(strings[2124], false, 1004, (entity *)IFC4_types[400]);
  IFC4_types[1024] =
      new entity(strings[2125], false, 1024, (entity *)IFC4_types[415]);
  IFC4_types[1026] =
      new entity(strings[2126], false, 1026, (entity *)IFC4_types[465]);
  IFC4_types[1027] =
      new entity(strings[2127], false, 1027, (entity *)IFC4_types[443]);
  IFC4_types[1034] =
      new entity(strings[2128], false, 1034, (entity *)IFC4_types[430]);
  IFC4_types[1045] =
      new entity(strings[2129], false, 1045, (entity *)IFC4_types[792]);
  IFC4_types[1046] =
      new entity(strings[2130], false, 1046, (entity *)IFC4_types[792]);
  IFC4_types[1047] =
      new entity(strings[2131], false, 1047, (entity *)IFC4_types[793]);
  IFC4_types[1049] =
      new entity(strings[2132], false, 1049, (entity *)IFC4_types[793]);
  IFC4_types[1090] =
      new entity(strings[2133], false, 1090, (entity *)IFC4_types[358]);
  IFC4_types[1094] =
      new entity(strings[2134], false, 1094, (entity *)IFC4_types[345]);
  IFC4_types[1099] =
      new entity(strings[2135], false, 1099, (entity *)IFC4_types[80]);
  IFC4_types[1104] =
      new entity(strings[2136], false, 1104, (entity *)IFC4_types[358]);
  IFC4_types[1115] =
      new entity(strings[2137], false, 1115, (entity *)IFC4_types[358]);
  IFC4_types[1123] =
      new entity(strings[2138], false, 1123, (entity *)IFC4_types[415]);
  IFC4_types[1131] =
      new entity(strings[2139], false, 1131, (entity *)IFC4_types[350]);
  IFC4_types[1132] =
      new entity(strings[2140], false, 1132, (entity *)IFC4_types[351]);
  IFC4_types[1134] =
      new entity(strings[2141], false, 1134, (entity *)IFC4_types[345]);
  IFC4_types[1136] =
      new entity(strings[2142], false, 1136, (entity *)IFC4_types[402]);
  IFC4_types[1143] =
      new entity(strings[2143], false, 1143, (entity *)IFC4_types[99]);
  IFC4_types[1149] =
      new entity(strings[2144], false, 1149, (entity *)IFC4_types[432]);
  IFC4_types[1160] =
      new entity(strings[2145], false, 1160, (entity *)IFC4_types[99]);
  IFC4_types[1163] =
      new entity(strings[2146], false, 1163, (entity *)IFC4_types[201]);
  IFC4_types[1165] =
      new entity(strings[2147], true, 1165, (entity *)IFC4_types[201]);
  IFC4_types[1166] =
      new entity(strings[2148], false, 1166, (entity *)IFC4_types[1165]);
  IFC4_types[1168] =
      new entity(strings[2149], false, 1168, (entity *)IFC4_types[1165]);
  IFC4_types[1171] =
      new entity(strings[2150], false, 1171, (entity *)IFC4_types[1026]);
  IFC4_types[240] =
      new select_type(strings[2151], 240, {IFC4_types[246], IFC4_types[248]});
  IFC4_types[242] = new select_type(
      strings[2152], 242, {IFC4_types[166], IFC4_types[640], IFC4_types[1002]});
  IFC4_types[243] =
      new select_type(strings[2153], 243, {IFC4_types[80], IFC4_types[319]});
  IFC4_types[953] =
      new select_type(strings[2154], 953, {IFC4_types[345], IFC4_types[964]});
  IFC4_types[2] =
      new entity(strings[2155], false, 2, (entity *)IFC4_types[201]);
  IFC4_types[19] =
      new entity(strings[2156], false, 19, (entity *)IFC4_types[415]);
  IFC4_types[21] =
      new entity(strings[2157], false, 21, (entity *)IFC4_types[432]);
  IFC4_types[24] =
      new entity(strings[2158], false, 24, (entity *)IFC4_types[358]);
  IFC4_types[48] =
      new entity(strings[2159], false, 48, (entity *)IFC4_types[465]);
  IFC4_types[51] =
      new entity(strings[2160], false, 51, (entity *)IFC4_types[432]);
  IFC4_types[85] =
      new entity(strings[2161], true, 85, (entity *)IFC4_types[80]);
  IFC4_types[87] =
      new entity(strings[2162], false, 87, (entity *)IFC4_types[85]);
  IFC4_types[59] =
      new entity(strings[2163], false, 59, (entity *)IFC4_types[99]);
  IFC4_types[67] =
      new entity(strings[2164], false, 67, (entity *)IFC4_types[358]);
  IFC4_types[75] =
      new entity(strings[2165], false, 75, (entity *)IFC4_types[166]);
  IFC4_types[92] =
      new entity(strings[2166], true, 92, (entity *)IFC4_types[345]);
  IFC4_types[93] =
      new entity(strings[2167], false, 93, (entity *)IFC4_types[350]);
  IFC4_types[94] =
      new entity(strings[2168], false, 94, (entity *)IFC4_types[351]);
  IFC4_types[96] =
      new entity(strings[2169], false, 96, (entity *)IFC4_types[92]);
  IFC4_types[97] =
      new entity(strings[2170], false, 97, (entity *)IFC4_types[99]);
  IFC4_types[101] =
      new entity(strings[2171], false, 101, (entity *)IFC4_types[1026]);
  IFC4_types[104] =
      new entity(strings[2172], false, 104, (entity *)IFC4_types[358]);
  IFC4_types[107] =
      new entity(strings[2173], false, 107, (entity *)IFC4_types[418]);
  IFC4_types[110] =
      new entity(strings[2174], false, 110, (entity *)IFC4_types[428]);
  IFC4_types[113] =
      new entity(strings[2175], false, 113, (entity *)IFC4_types[418]);
  IFC4_types[116] =
      new entity(strings[2176], false, 116, (entity *)IFC4_types[428]);
  IFC4_types[131] =
      new entity(strings[2177], false, 131, (entity *)IFC4_types[358]);
  IFC4_types[133] =
      new entity(strings[2178], false, 133, (entity *)IFC4_types[92]);
  IFC4_types[136] =
      new entity(strings[2179], false, 136, (entity *)IFC4_types[176]);
  IFC4_types[139] =
      new entity(strings[2180], false, 139, (entity *)IFC4_types[345]);
  IFC4_types[147] =
      new entity(strings[2181], false, 147, (entity *)IFC4_types[358]);
  IFC4_types[154] =
      new entity(strings[2182], false, 154, (entity *)IFC4_types[92]);
  IFC4_types[155] =
      new entity(strings[2183], false, 155, (entity *)IFC4_types[154]);
  IFC4_types[159] =
      new entity(strings[2184], false, 159, (entity *)IFC4_types[432]);
  IFC4_types[171] =
      new entity(strings[2185], false, 171, (entity *)IFC4_types[426]);
  IFC4_types[174] =
      new entity(strings[2186], false, 174, (entity *)IFC4_types[358]);
  IFC4_types[187] =
      new entity(strings[2187], false, 187, (entity *)IFC4_types[196]);
  IFC4_types[190] =
      new entity(strings[2188], false, 190, (entity *)IFC4_types[196]);
  IFC4_types[193] =
      new entity(strings[2189], false, 193, (entity *)IFC4_types[196]);
  IFC4_types[208] =
      new entity(strings[2190], false, 208, (entity *)IFC4_types[358]);
  IFC4_types[211] =
      new entity(strings[2191], false, 211, (entity *)IFC4_types[358]);
  IFC4_types[222] =
      new entity(strings[2192], false, 222, (entity *)IFC4_types[92]);
  IFC4_types[233] =
      new entity(strings[2193], false, 233, (entity *)IFC4_types[92]);
  IFC4_types[251] =
      new entity(strings[2194], false, 251, (entity *)IFC4_types[415]);
  IFC4_types[269] =
      new entity(strings[2195], false, 269, (entity *)IFC4_types[350]);
  IFC4_types[270] =
      new entity(strings[2196], false, 270, (entity *)IFC4_types[351]);
  IFC4_types[273] =
      new entity(strings[2197], false, 273, (entity *)IFC4_types[281]);
  IFC4_types[277] =
      new entity(strings[2198], true, 277, (entity *)IFC4_types[279]);
  IFC4_types[278] =
      new entity(strings[2199], false, 278, (entity *)IFC4_types[345]);
  IFC4_types[280] =
      new entity(strings[2200], false, 280, (entity *)IFC4_types[278]);
  IFC4_types[282] =
      new entity(strings[2201], false, 282, (entity *)IFC4_types[683]);
  IFC4_types[284] =
      new entity(strings[2202], false, 284, (entity *)IFC4_types[1026]);
  IFC4_types[292] =
      new entity(strings[2203], false, 292, (entity *)IFC4_types[92]);
  IFC4_types[297] =
      new entity(strings[2204], false, 297, (entity *)IFC4_types[292]);
  IFC4_types[308] =
      new entity(strings[2205], false, 308, (entity *)IFC4_types[418]);
  IFC4_types[311] =
      new entity(strings[2206], false, 311, (entity *)IFC4_types[428]);
  IFC4_types[314] =
      new entity(strings[2207], false, 314, (entity *)IFC4_types[434]);
  IFC4_types[322] =
      new entity(strings[2208], false, 322, (entity *)IFC4_types[432]);
  IFC4_types[329] =
      new entity(strings[2209], false, 329, (entity *)IFC4_types[415]);
  IFC4_types[332] =
      new entity(strings[2210], false, 332, (entity *)IFC4_types[430]);
  IFC4_types[335] =
      new entity(strings[2211], false, 335, (entity *)IFC4_types[358]);
  IFC4_types[338] =
      new entity(strings[2212], false, 338, (entity *)IFC4_types[358]);
  IFC4_types[342] =
      new entity(strings[2213], false, 342, (entity *)IFC4_types[415]);
  IFC4_types[357] =
      new entity(strings[2214], false, 357, (entity *)IFC4_types[280]);
  IFC4_types[360] =
      new entity(strings[2215], false, 360, (entity *)IFC4_types[357]);
  IFC4_types[363] =
      new entity(strings[2216], false, 363, (entity *)IFC4_types[357]);
  IFC4_types[366] =
      new entity(strings[2217], false, 366, (entity *)IFC4_types[357]);
  IFC4_types[381] =
      new entity(strings[2218], false, 381, (entity *)IFC4_types[383]);
  IFC4_types[395] =
      new entity(strings[2219], false, 395, (entity *)IFC4_types[426]);
  IFC4_types[408] =
      new entity(strings[2220], false, 408, (entity *)IFC4_types[434]);
  IFC4_types[411] =
      new entity(strings[2221], false, 411, (entity *)IFC4_types[432]);
  IFC4_types[414] =
      new entity(strings[2222], false, 414, (entity *)IFC4_types[280]);
  IFC4_types[417] =
      new entity(strings[2223], false, 417, (entity *)IFC4_types[280]);
  IFC4_types[420] =
      new entity(strings[2224], false, 420, (entity *)IFC4_types[277]);
  IFC4_types[422] =
      new entity(strings[2225], false, 422, (entity *)IFC4_types[414]);
  IFC4_types[425] =
      new entity(strings[2226], false, 425, (entity *)IFC4_types[280]);
  IFC4_types[427] =
      new entity(strings[2227], false, 427, (entity *)IFC4_types[280]);
  IFC4_types[429] =
      new entity(strings[2228], false, 429, (entity *)IFC4_types[280]);
  IFC4_types[431] =
      new entity(strings[2229], false, 431, (entity *)IFC4_types[280]);
  IFC4_types[433] =
      new entity(strings[2230], false, 433, (entity *)IFC4_types[280]);
  IFC4_types[438] =
      new entity(strings[2231], false, 438, (entity *)IFC4_types[92]);
  IFC4_types[468] =
      new entity(strings[2232], false, 468, (entity *)IFC4_types[357]);
  IFC4_types[473] =
      new entity(strings[2233], false, 473, (entity *)IFC4_types[357]);
  IFC4_types[488] =
      new entity(strings[2234], false, 488, (entity *)IFC4_types[433]);
  IFC4_types[500] =
      new entity(strings[2235], false, 500, (entity *)IFC4_types[417]);
  IFC4_types[510] =
      new entity(strings[2236], false, 510, (entity *)IFC4_types[431]);
  IFC4_types[524] =
      new entity(strings[2237], false, 524, (entity *)IFC4_types[431]);
  IFC4_types[583] =
      new entity(strings[2238], false, 583, (entity *)IFC4_types[431]);
  IFC4_types[586] =
      new entity(strings[2239], false, 586, (entity *)IFC4_types[92]);
  IFC4_types[587] =
      new entity(strings[2240], false, 587, (entity *)IFC4_types[586]);
  IFC4_types[606] =
      new entity(strings[2241], false, 606, (entity *)IFC4_types[357]);
  IFC4_types[632] =
      new entity(strings[2242], false, 632, (entity *)IFC4_types[75]);
  IFC4_types[633] =
      new entity(strings[2243], false, 633, (entity *)IFC4_types[431]);
  IFC4_types[654] =
      new entity(strings[2244], false, 654, (entity *)IFC4_types[92]);
  IFC4_types[658] =
      new entity(strings[2245], false, 658, (entity *)IFC4_types[417]);
  IFC4_types[661] =
      new entity(strings[2246], false, 661, (entity *)IFC4_types[427]);
  IFC4_types[671] =
      new entity(strings[2247], false, 671, (entity *)IFC4_types[92]);
  IFC4_types[672] =
      new entity(strings[2248], false, 672, (entity *)IFC4_types[671]);
  IFC4_types[745] =
      new entity(strings[2249], false, 745, (entity *)IFC4_types[414]);
  IFC4_types[747] =
      new entity(strings[2250], false, 747, (entity *)IFC4_types[277]);
  IFC4_types[752] =
      new entity(strings[2251], false, 752, (entity *)IFC4_types[425]);
  IFC4_types[763] =
      new entity(strings[2252], false, 763, (entity *)IFC4_types[92]);
  IFC4_types[766] =
      new entity(strings[2253], false, 766, (entity *)IFC4_types[92]);
  IFC4_types[767] =
      new entity(strings[2254], false, 767, (entity *)IFC4_types[92]);
  IFC4_types[773] =
      new entity(strings[2255], false, 773, (entity *)IFC4_types[87]);
  IFC4_types[787] =
      new entity(strings[2256], false, 787, (entity *)IFC4_types[792]);
  IFC4_types[790] =
      new entity(strings[2257], false, 790, (entity *)IFC4_types[793]);
  IFC4_types[862] =
      new entity(strings[2258], false, 862, (entity *)IFC4_types[92]);
  IFC4_types[871] =
      new entity(strings[2259], false, 871, (entity *)IFC4_types[431]);
  IFC4_types[884] =
      new entity(strings[2260], false, 884, (entity *)IFC4_types[277]);
  IFC4_types[887] =
      new entity(strings[2261], false, 887, (entity *)IFC4_types[92]);
  IFC4_types[905] =
      new entity(strings[2262], false, 905, (entity *)IFC4_types[92]);
  IFC4_types[906] =
      new entity(strings[2263], false, 906, (entity *)IFC4_types[905]);
  IFC4_types[907] =
      new entity(strings[2264], false, 907, (entity *)IFC4_types[905]);
  IFC4_types[911] =
      new entity(strings[2265], false, 911, (entity *)IFC4_types[357]);
  IFC4_types[923] =
      new entity(strings[2266], false, 923, (entity *)IFC4_types[431]);
  IFC4_types[941] =
      new entity(strings[2267], false, 941, (entity *)IFC4_types[431]);
  IFC4_types[944] =
      new entity(strings[2268], false, 944, (entity *)IFC4_types[92]);
  IFC4_types[945] =
      new entity(strings[2269], false, 945, (entity *)IFC4_types[92]);
  IFC4_types[954] =
      new entity(strings[2270], false, 954, (entity *)IFC4_types[1026]);
  IFC4_types[967] =
      new entity(strings[2271], false, 967, (entity *)IFC4_types[969]);
  IFC4_types[980] =
      new entity(strings[2272], false, 980, (entity *)IFC4_types[986]);
  IFC4_types[1023] =
      new entity(strings[2273], false, 1023, (entity *)IFC4_types[414]);
  IFC4_types[1033] =
      new entity(strings[2274], false, 1033, (entity *)IFC4_types[429]);
  IFC4_types[1089] =
      new entity(strings[2275], false, 1089, (entity *)IFC4_types[357]);
  IFC4_types[1103] =
      new entity(strings[2276], false, 1103, (entity *)IFC4_types[357]);
  IFC4_types[1112] =
      new entity(strings[2277], false, 1112, (entity *)IFC4_types[277]);
  IFC4_types[1114] =
      new entity(strings[2278], false, 1114, (entity *)IFC4_types[357]);
  IFC4_types[1122] =
      new entity(strings[2279], false, 1122, (entity *)IFC4_types[414]);
  IFC4_types[1140] =
      new entity(strings[2280], false, 1140, (entity *)IFC4_types[92]);
  IFC4_types[1141] =
      new entity(strings[2281], false, 1141, (entity *)IFC4_types[1140]);
  IFC4_types[1142] =
      new entity(strings[2282], false, 1142, (entity *)IFC4_types[1140]);
  IFC4_types[1148] =
      new entity(strings[2283], false, 1148, (entity *)IFC4_types[431]);
  IFC4_types[1151] =
      new entity(strings[2284], false, 1151, (entity *)IFC4_types[92]);
  IFC4_types[1156] =
      new entity(strings[2285], false, 1156, (entity *)IFC4_types[1151]);
  IFC4_types[922] =
      new select_type(strings[2286], 922, {IFC4_types[381], IFC4_types[921]});
  IFC4_types[10] =
      new entity(strings[2287], false, 10, (entity *)IFC4_types[277]);
  IFC4_types[17] =
      new entity(strings[2288], false, 17, (entity *)IFC4_types[431]);
  IFC4_types[18] =
      new entity(strings[2289], false, 18, (entity *)IFC4_types[414]);
  IFC4_types[23] =
      new entity(strings[2290], false, 23, (entity *)IFC4_types[357]);
  IFC4_types[27] =
      new entity(strings[2291], false, 27, (entity *)IFC4_types[277]);
  IFC4_types[50] =
      new entity(strings[2292], false, 50, (entity *)IFC4_types[431]);
  IFC4_types[57] =
      new entity(strings[2293], false, 57, (entity *)IFC4_types[92]);
  IFC4_types[58] =
      new entity(strings[2294], false, 58, (entity *)IFC4_types[57]);
  IFC4_types[66] =
      new entity(strings[2295], false, 66, (entity *)IFC4_types[357]);
  IFC4_types[103] =
      new entity(strings[2296], false, 103, (entity *)IFC4_types[357]);
  IFC4_types[106] =
      new entity(strings[2297], false, 106, (entity *)IFC4_types[417]);
  IFC4_types[109] =
      new entity(strings[2298], false, 109, (entity *)IFC4_types[427]);
  IFC4_types[112] =
      new entity(strings[2299], false, 112, (entity *)IFC4_types[417]);
  IFC4_types[115] =
      new entity(strings[2300], false, 115, (entity *)IFC4_types[427]);
  IFC4_types[130] =
      new entity(strings[2301], false, 130, (entity *)IFC4_types[357]);
  IFC4_types[146] =
      new entity(strings[2302], false, 146, (entity *)IFC4_types[357]);
  IFC4_types[158] =
      new entity(strings[2303], false, 158, (entity *)IFC4_types[431]);
  IFC4_types[170] =
      new entity(strings[2304], false, 170, (entity *)IFC4_types[425]);
  IFC4_types[173] =
      new entity(strings[2305], false, 173, (entity *)IFC4_types[357]);
  IFC4_types[203] =
      new entity(strings[2306], false, 203, (entity *)IFC4_types[277]);
  IFC4_types[207] =
      new entity(strings[2307], false, 207, (entity *)IFC4_types[357]);
  IFC4_types[210] =
      new entity(strings[2308], false, 210, (entity *)IFC4_types[357]);
  IFC4_types[250] =
      new entity(strings[2309], false, 250, (entity *)IFC4_types[414]);
  IFC4_types[272] =
      new entity(strings[2310], false, 272, (entity *)IFC4_types[280]);
  IFC4_types[275] =
      new entity(strings[2311], false, 275, (entity *)IFC4_types[284]);
  IFC4_types[276] =
      new entity(strings[2312], false, 276, (entity *)IFC4_types[278]);
  IFC4_types[307] =
      new entity(strings[2313], false, 307, (entity *)IFC4_types[417]);
  IFC4_types[310] =
      new entity(strings[2314], false, 310, (entity *)IFC4_types[427]);
  IFC4_types[313] =
      new entity(strings[2315], false, 313, (entity *)IFC4_types[433]);
  IFC4_types[321] =
      new entity(strings[2316], false, 321, (entity *)IFC4_types[431]);
  IFC4_types[328] =
      new entity(strings[2317], false, 328, (entity *)IFC4_types[414]);
  IFC4_types[331] =
      new entity(strings[2318], false, 331, (entity *)IFC4_types[429]);
  IFC4_types[334] =
      new entity(strings[2319], false, 334, (entity *)IFC4_types[357]);
  IFC4_types[337] =
      new entity(strings[2320], false, 337, (entity *)IFC4_types[357]);
  IFC4_types[341] =
      new entity(strings[2321], false, 341, (entity *)IFC4_types[414]);
  IFC4_types[394] =
      new entity(strings[2322], false, 394, (entity *)IFC4_types[425]);
  IFC4_types[407] =
      new entity(strings[2323], false, 407, (entity *)IFC4_types[433]);
  IFC4_types[410] =
      new entity(strings[2324], false, 410, (entity *)IFC4_types[431]);
  IFC4_types[419] =
      new entity(strings[2325], false, 419, (entity *)IFC4_types[276]);
  IFC4_types[746] =
      new entity(strings[2326], false, 746, (entity *)IFC4_types[276]);
  IFC4_types[883] =
      new entity(strings[2327], false, 883, (entity *)IFC4_types[276]);
  IFC4_types[1111] =
      new entity(strings[2328], false, 1111, (entity *)IFC4_types[276]);
  IFC4_types[9] =
      new entity(strings[2329], false, 9, (entity *)IFC4_types[276]);
  IFC4_types[26] =
      new entity(strings[2330], false, 26, (entity *)IFC4_types[276]);
  IFC4_types[202] =
      new entity(strings[2331], false, 202, (entity *)IFC4_types[276]);
  ((entity *)IFC4_types[2])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[3]), true),
           new attribute(strings[2333], new named_type(IFC4_types[505]), true),
           new attribute(strings[2334], new named_type(IFC4_types[1053]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[6])
      ->set_attributes(
          {new attribute(strings[2335], new named_type(IFC4_types[8]), false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[7])
      ->set_attributes(
          {new attribute(strings[2336], new named_type(IFC4_types[861]), false),
           new attribute(strings[2337], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]),
                         true)},
          {false, false, false});
  ((entity *)IFC4_types[9])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[11]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[10])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[11]), false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[12])
      ->set_attributes(
          {new attribute(strings[2339], new named_type(IFC4_types[13]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2340], new named_type(IFC4_types[505]), true)},
          {false, false, false});
  ((entity *)IFC4_types[14])->set_attributes({}, {false});
  ((entity *)IFC4_types[15])
      ->set_attributes(
          {new attribute(strings[2341],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[145])),
                         false)},
          {false, false});
  ((entity *)IFC4_types[16])->set_attributes({}, {false, false, false});
  ((entity *)IFC4_types[17])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[22]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[18])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[20]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[19])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[20]), false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[21])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[22]), false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[23])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[25]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[24])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[25]), false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[26])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[28]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[27])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[28]), false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[33])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[34])
      ->set_attributes(
          {new attribute(strings[2342], new named_type(IFC4_types[237]), false),
           new attribute(strings[2343],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[237])),
                         true)},
          {false, false});
  ((entity *)IFC4_types[35])
      ->set_attributes(
          {new attribute(strings[2344], new named_type(IFC4_types[629]), false),
           new attribute(strings[2345], new named_type(IFC4_types[505]), false),
           new attribute(strings[2346], new named_type(IFC4_types[505]), false),
           new attribute(strings[2347], new named_type(IFC4_types[476]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[36])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2349], new named_type(IFC4_types[37]), true),
           new attribute(strings[2350], new named_type(IFC4_types[579]), true),
           new attribute(strings[2351], new named_type(IFC4_types[254]), true),
           new attribute(strings[2352], new named_type(IFC4_types[254]), true),
           new attribute(strings[2353], new named_type(IFC4_types[505]), true),
           new attribute(strings[2354], new named_type(IFC4_types[505]), true),
           new attribute(strings[2355], new named_type(IFC4_types[46]), true),
           new attribute(strings[2356],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[36])),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[38])
      ->set_attributes(
          {new attribute(strings[2357], new named_type(IFC4_types[476]), true),
           new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2358], new named_type(IFC4_types[255]), true),
           new attribute(strings[2333], new named_type(IFC4_types[505]), true),
           new attribute(strings[2359], new named_type(IFC4_types[505]), true),
           new attribute(strings[2360], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2361], new named_type(IFC4_types[8]), true),
           new attribute(strings[2362], new named_type(IFC4_types[8]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[39])
      ->set_attributes(
          {new attribute(strings[2363], new named_type(IFC4_types[38]), false),
           new attribute(strings[2364],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[38])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[40])
      ->set_attributes({new attribute(strings[2365],
                                      new named_type(IFC4_types[237]), false)},
                       {false, false, false});
  ((entity *)IFC4_types[41])
      ->set_attributes(
          {new attribute(strings[2366], new named_type(IFC4_types[80]), false)},
          {false, false, false});
  ((entity *)IFC4_types[42])
      ->set_attributes(
          {new attribute(strings[2367],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[237])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[48])
      ->set_attributes(
          {new attribute(strings[2368], new named_type(IFC4_types[476]), true),
           new attribute(strings[2369], new named_type(IFC4_types[220]), true),
           new attribute(strings[2370], new named_type(IFC4_types[220]), true),
           new attribute(strings[2371], new named_type(IFC4_types[220]), true),
           new attribute(strings[2372], new named_type(IFC4_types[8]), true),
           new attribute(strings[2373], new named_type(IFC4_types[8]), true),
           new attribute(strings[2374], new named_type(IFC4_types[647]), true),
           new attribute(strings[2375], new named_type(IFC4_types[254]), true),
           new attribute(strings[2376], new named_type(IFC4_types[220]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4_types[49])
      ->set_attributes(
          {new attribute(strings[2377], new named_type(IFC4_types[685]), false),
           new attribute(strings[2378], new named_type(IFC4_types[685]), false),
           new attribute(strings[2379], new named_type(IFC4_types[685]), false),
           new attribute(strings[2380], new named_type(IFC4_types[685]), false),
           new attribute(strings[2381], new named_type(IFC4_types[610]), true),
           new attribute(strings[2382], new named_type(IFC4_types[685]), false),
           new attribute(strings[2383], new named_type(IFC4_types[685]), true),
           new attribute(strings[2384], new named_type(IFC4_types[610]), true),
           new attribute(strings[2385], new named_type(IFC4_types[610]), true),
           new attribute(strings[2386], new named_type(IFC4_types[670]), true),
           new attribute(strings[2387], new named_type(IFC4_types[610]), true),
           new attribute(strings[2388], new named_type(IFC4_types[670]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false});
  ((entity *)IFC4_types[50])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[52]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[51])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[52]), false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[53])
      ->set_attributes(
          {new attribute(strings[2389], new named_type(IFC4_types[267]), true)},
          {false, false});
  ((entity *)IFC4_types[55])
      ->set_attributes(
          {new attribute(strings[2390], new named_type(IFC4_types[267]), true)},
          {false, false});
  ((entity *)IFC4_types[56])
      ->set_attributes(
          {new attribute(strings[2389], new named_type(IFC4_types[267]), true),
           new attribute(strings[2390], new named_type(IFC4_types[267]), true)},
          {false, false, false});
  ((entity *)IFC4_types[85])
      ->set_attributes(
          {new attribute(strings[2391], new named_type(IFC4_types[486]), false),
           new attribute(strings[2392],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC4_types[119])),
                         false),
           new attribute(strings[2393], new named_type(IFC4_types[86]), false),
           new attribute(strings[2394], new named_type(IFC4_types[542]), false),
           new attribute(strings[2395], new named_type(IFC4_types[542]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[87])
      ->set_attributes(
          {new attribute(strings[2396],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC4_types[486])),
                         false),
           new attribute(strings[2397],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC4_types[638])),
                         false),
           new attribute(strings[2398], new named_type(IFC4_types[504]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[88])
      ->set_attributes(
          {new attribute(strings[2399], new named_type(IFC4_types[486]), false),
           new attribute(strings[2400], new named_type(IFC4_types[486]), false),
           new attribute(
               strings[2392],
               new aggregation_type(
                   aggregation_type::list_type, 2, -1,
                   new aggregation_type(aggregation_type::list_type, 2, -1,
                                        new named_type(IFC4_types[119]))),
               false),
           new attribute(strings[2401], new named_type(IFC4_types[89]), false),
           new attribute(strings[2402], new named_type(IFC4_types[542]), false),
           new attribute(strings[2403], new named_type(IFC4_types[542]), false),
           new attribute(strings[2395], new named_type(IFC4_types[542]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[90])
      ->set_attributes(
          {new attribute(strings[2404],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC4_types[486])),
                         false),
           new attribute(strings[2405],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC4_types[486])),
                         false),
           new attribute(strings[2406],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC4_types[638])),
                         false),
           new attribute(strings[2407],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC4_types[638])),
                         false),
           new attribute(strings[2398], new named_type(IFC4_types[504]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4_types[57])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[60]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[58])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[59])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[60]), false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[64])
      ->set_attributes(
          {new attribute(strings[2408], new named_type(IFC4_types[476]), false),
           new attribute(strings[2409], new named_type(IFC4_types[63]), false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[65])
      ->set_attributes(
          {new attribute(strings[2410], new named_type(IFC4_types[685]), false),
           new attribute(strings[2411], new named_type(IFC4_types[685]), false),
           new attribute(strings[2412], new named_type(IFC4_types[685]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[66])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[68]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[67])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[68]), false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[70])->set_attributes({}, {false, false, false});
  ((entity *)IFC4_types[73])
      ->set_attributes(
          {new attribute(strings[2413], new named_type(IFC4_types[72]), false),
           new attribute(strings[2414], new named_type(IFC4_types[71]), false),
           new attribute(strings[2415], new named_type(IFC4_types[71]), false)},
          {false, false, false});
  ((entity *)IFC4_types[74])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true)},
          {false});
  ((entity *)IFC4_types[75])->set_attributes({}, {false, false});
  ((entity *)IFC4_types[76])
      ->set_attributes(
          {new attribute(strings[2416], new named_type(IFC4_types[599]), true),
           new attribute(strings[2417], new named_type(IFC4_types[599]), true),
           new attribute(strings[2418], new named_type(IFC4_types[599]), true),
           new attribute(strings[2419], new named_type(IFC4_types[596]), true),
           new attribute(strings[2420], new named_type(IFC4_types[596]), true),
           new attribute(strings[2421], new named_type(IFC4_types[596]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[77])
      ->set_attributes(
          {new attribute(strings[2422], new named_type(IFC4_types[598]), true),
           new attribute(strings[2423], new named_type(IFC4_types[598]), true),
           new attribute(strings[2424], new named_type(IFC4_types[598]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[78])
      ->set_attributes(
          {new attribute(strings[2425], new named_type(IFC4_types[1093]), true),
           new attribute(strings[2426], new named_type(IFC4_types[1093]), true),
           new attribute(strings[2427], new named_type(IFC4_types[1093]), true),
           new attribute(strings[2428], new named_type(IFC4_types[869]), true),
           new attribute(strings[2429], new named_type(IFC4_types[869]), true),
           new attribute(strings[2430], new named_type(IFC4_types[869]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[79])
      ->set_attributes(
          {new attribute(strings[2431], new named_type(IFC4_types[1147]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[80])->set_attributes({}, {});
  ((entity *)IFC4_types[81])->set_attributes({}, {});
  ((entity *)IFC4_types[82])
      ->set_attributes(
          {new attribute(strings[2432], new named_type(IFC4_types[119]), false),
           new attribute(strings[2433], new named_type(IFC4_types[685]), false),
           new attribute(strings[2434], new named_type(IFC4_types[685]), false),
           new attribute(strings[2435], new named_type(IFC4_types[685]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[84])
      ->set_attributes(
          {new attribute(strings[2436], new named_type(IFC4_types[82]), false)},
          {false, false, false});
  ((entity *)IFC4_types[91])
      ->set_attributes(
          {new attribute(strings[2437], new named_type(IFC4_types[516]), true),
           new attribute(strings[2438], new named_type(IFC4_types[516]), true),
           new attribute(strings[2439], new named_type(IFC4_types[688]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4_types[92])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[93])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[95]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[94])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[95]), false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[96])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[98]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[97])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[98]), false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[99])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[100])
      ->set_attributes(
          {new attribute(strings[2440], new named_type(IFC4_types[516]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[101])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[102]), true),
           new attribute(strings[2441], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[103])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[105]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[104])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[105]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[231])
      ->set_attributes(
          {new attribute(strings[2442], new named_type(IFC4_types[685]), false),
           new attribute(strings[2443], new named_type(IFC4_types[685]), false),
           new attribute(strings[2444], new named_type(IFC4_types[685]), false),
           new attribute(strings[2445], new named_type(IFC4_types[685]), false),
           new attribute(strings[2446], new named_type(IFC4_types[610]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[106])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[108]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[107])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[108]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[109])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[111]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[110])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[111]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[112])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[114]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[113])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[114]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[115])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[117]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[116])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[117]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[119])
      ->set_attributes(
          {new attribute(strings[2447],
                         new aggregation_type(aggregation_type::list_type, 1, 3,
                                              new named_type(IFC4_types[516])),
                         false)},
          {false});
  ((entity *)IFC4_types[120])->set_attributes({}, {});
  ((entity *)IFC4_types[121])
      ->set_attributes({new attribute(strings[2448],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new aggregation_type(
                                              aggregation_type::list_type, 2, 2,
                                              new named_type(IFC4_types[516]))),
                                      false)},
                       {false});
  ((entity *)IFC4_types[122])
      ->set_attributes({new attribute(strings[2448],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new aggregation_type(
                                              aggregation_type::list_type, 3, 3,
                                              new named_type(IFC4_types[516]))),
                                      false)},
                       {false});
  ((entity *)IFC4_types[123])
      ->set_attributes(
          {new attribute(strings[2449], new named_type(IFC4_types[267]), true),
           new attribute(strings[2450], new named_type(IFC4_types[267]), true),
           new attribute(strings[2451], new named_type(IFC4_types[119]), false),
           new attribute(strings[2452], new named_type(IFC4_types[775]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[124])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[125])
      ->set_attributes(
          {new attribute(strings[2453], new named_type(IFC4_types[775]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[126])
      ->set_attributes(
          {new attribute(strings[2454], new named_type(IFC4_types[267]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[127])
      ->set_attributes(
          {new attribute(strings[2453], new named_type(IFC4_types[775]), true),
           new attribute(strings[2455], new named_type(IFC4_types[775]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[128])
      ->set_attributes({new attribute(strings[2456],
                                      new named_type(IFC4_types[685]), false)},
                       {false, false, false, false});
  ((entity *)IFC4_types[130])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[132]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[131])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[132]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[133])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[135]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[134])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[135]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[136])
      ->set_attributes({new attribute(strings[2457],
                                      new named_type(IFC4_types[685]), false)},
                       {false, false});
  ((entity *)IFC4_types[137])
      ->set_attributes({new attribute(strings[2444],
                                      new named_type(IFC4_types[685]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC4_types[138])
      ->set_attributes({new attribute(strings[2457],
                                      new named_type(IFC4_types[685]), false)},
                       {false, false, false, false});
  ((entity *)IFC4_types[139])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[140])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[141])
      ->set_attributes(
          {new attribute(strings[2458], new named_type(IFC4_types[505]), true),
           new attribute(strings[2459], new named_type(IFC4_types[505]), true),
           new attribute(strings[2460], new named_type(IFC4_types[254]), true),
           new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2461], new named_type(IFC4_types[1119]), true),
           new attribute(strings[2462],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[476])),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[142])
      ->set_attributes(
          {new attribute(strings[2463], new named_type(IFC4_types[143]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2464], new named_type(IFC4_types[476]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[145])->set_attributes({}, {false});
  ((entity *)IFC4_types[146])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[148]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[147])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[148]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[151])
      ->set_attributes(
          {new attribute(strings[2465], new named_type(IFC4_types[611]), false),
           new attribute(strings[2466], new named_type(IFC4_types[611]), false),
           new attribute(strings[2467], new named_type(IFC4_types[611]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[152])
      ->set_attributes({new attribute(strings[2468],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new aggregation_type(
                                              aggregation_type::list_type, 3, 3,
                                              new named_type(IFC4_types[611]))),
                                      false)},
                       {false});
  ((entity *)IFC4_types[153])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true)},
          {false});
  ((entity *)IFC4_types[154])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[157]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[155])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[156])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[157]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[158])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[160]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[159])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[160]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[162])
      ->set_attributes(
          {new attribute(strings[2469], new named_type(IFC4_types[476]), false),
           new attribute(strings[2470],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[726])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[163])
      ->set_attributes(
          {new attribute(strings[2469], new named_type(IFC4_types[505]), true),
           new attribute(strings[2471], new named_type(IFC4_types[164]), true),
           new attribute(strings[2472],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[743])),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[165])
      ->set_attributes({new attribute(strings[2473],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4_types[167])),
                                      false),
                        new attribute(strings[2395],
                                      new named_type(IFC4_types[542]), false)},
                       {false, false});
  ((entity *)IFC4_types[166])->set_attributes({}, {false, false});
  ((entity *)IFC4_types[167])
      ->set_attributes(
          {new attribute(strings[2474], new named_type(IFC4_types[1092]),
                         false),
           new attribute(strings[2475], new named_type(IFC4_types[69]), false),
           new attribute(strings[2476], new named_type(IFC4_types[237]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[168])
      ->set_attributes(
          {new attribute(strings[2477],
                         new aggregation_type(aggregation_type::set_type, 2, -1,
                                              new named_type(IFC4_types[715])),
                         false),
           new attribute(strings[2478], new named_type(IFC4_types[505]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[170])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[172]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[171])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[172]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[173])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[175]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[174])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[175]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[176])
      ->set_attributes(
          {new attribute(strings[2479], new named_type(IFC4_types[54]), false)},
          {false});
  ((entity *)IFC4_types[177])
      ->set_attributes(
          {new attribute(strings[2480],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[386])),
                         false)},
          {false});
  ((entity *)IFC4_types[178])
      ->set_attributes(
          {new attribute(strings[2481], new named_type(IFC4_types[243]), false),
           new attribute(strings[2482], new named_type(IFC4_types[243]), true)},
          {false, false});
  ((entity *)IFC4_types[179])->set_attributes({}, {});
  ((entity *)IFC4_types[180])
      ->set_attributes(
          {new attribute(strings[2483], new named_type(IFC4_types[516]), true),
           new attribute(strings[2484], new named_type(IFC4_types[516]), true),
           new attribute(strings[2485], new named_type(IFC4_types[516]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[181])
      ->set_attributes(
          {new attribute(strings[2486], new named_type(IFC4_types[678]), false),
           new attribute(strings[2487], new named_type(IFC4_types[678]), true)},
          {false, false});
  ((entity *)IFC4_types[182])
      ->set_attributes({new attribute(strings[2488],
                                      new named_type(IFC4_types[1008]), false),
                        new attribute(strings[2489],
                                      new named_type(IFC4_types[1008]), true)},
                       {false, false});
  ((entity *)IFC4_types[184])
      ->set_attributes(
          {new attribute(strings[2490], new named_type(IFC4_types[916]), false),
           new attribute(strings[2491], new named_type(IFC4_types[916]), true)},
          {false, false});
  ((entity *)IFC4_types[185])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2492], new named_type(IFC4_types[186]), false),
           new attribute(strings[2493], new named_type(IFC4_types[505]), true),
           new attribute(strings[2494], new named_type(IFC4_types[8]), true),
           new attribute(strings[2495], new named_type(IFC4_types[255]), true),
           new attribute(strings[2496], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[187])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[189]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[188])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[189]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4_types[190])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[192]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[191])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[192]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4_types[193])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[195]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[194])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[195]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4_types[196])
      ->set_attributes(
          {new attribute(strings[2497], new named_type(IFC4_types[856]), true),
           new attribute(strings[2498],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[36])),
                         true),
           new attribute(strings[2499], new named_type(IFC4_types[652]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[197])
      ->set_attributes(
          {new attribute(strings[2498],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[36])),
                         true),
           new attribute(strings[2499], new named_type(IFC4_types[652]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[198])
      ->set_attributes(
          {new attribute(strings[2500], new named_type(IFC4_types[505]), true),
           new attribute(strings[2441], new named_type(IFC4_types[505]), true),
           new attribute(strings[2501], new named_type(IFC4_types[505]), true),
           new attribute(strings[2502],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[847])),
                         true),
           new attribute(strings[2503], new named_type(IFC4_types[1117]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[200])
      ->set_attributes({new attribute(strings[2348],
                                      new named_type(IFC4_types[505]), false)},
                       {false, false, false});
  ((entity *)IFC4_types[201])
      ->set_attributes(
          {new attribute(strings[2368], new named_type(IFC4_types[476]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[202])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[204]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[203])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[204]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[205])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2504], new named_type(IFC4_types[579]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[206])
      ->set_attributes({new attribute(strings[2505],
                                      new named_type(IFC4_types[775]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC4_types[207])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[209]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[208])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[209]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[210])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[212]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[211])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[212]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[213])
      ->set_attributes(
          {new attribute(strings[2506], new named_type(IFC4_types[215]), false),
           new attribute(strings[2507], new named_type(IFC4_types[214]),
                         false)},
          {false, false});
  ((entity *)IFC4_types[214])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2508], new named_type(IFC4_types[476]), true),
           new attribute(strings[2509], new named_type(IFC4_types[476]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[216])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[217]), true),
           new attribute(strings[2510],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[220])),
                         true),
           new attribute(strings[2511],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[652])),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[218])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[219]), true),
           new attribute(strings[2333], new named_type(IFC4_types[505]), true),
           new attribute(strings[2512], new named_type(IFC4_types[255]), true),
           new attribute(strings[2513], new named_type(IFC4_types[255]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[220])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false});
  ((entity *)IFC4_types[222])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[224]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[223])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[224]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[225])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[227]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[226])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[227]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4_types[228])
      ->set_attributes(
          {new attribute(strings[2479], new named_type(IFC4_types[56]), false)},
          {false});
  ((entity *)IFC4_types[230])
      ->set_attributes({new attribute(strings[2514],
                                      new named_type(IFC4_types[229]), false)},
                       {false});
  ((entity *)IFC4_types[232])
      ->set_attributes(
          {new attribute(strings[2515], new named_type(IFC4_types[604]), false),
           new attribute(strings[2516], new named_type(IFC4_types[604]), false),
           new attribute(strings[2517], new named_type(IFC4_types[687]), false),
           new attribute(strings[2518], new named_type(IFC4_types[255]), true),
           new attribute(strings[2519], new named_type(IFC4_types[517]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[233])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[235]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[234])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[235]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[237])->set_attributes({}, {});
  ((entity *)IFC4_types[238])
      ->set_attributes(
          {new attribute(strings[2520], new named_type(IFC4_types[669]), false),
           new attribute(strings[2342], new named_type(IFC4_types[237]), false),
           new attribute(strings[2343],
                         new aggregation_type(aggregation_type::set_type, 0, -1,
                                              new named_type(IFC4_types[237])),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[239])
      ->set_attributes(
          {new attribute(strings[2520], new named_type(IFC4_types[1001]),
                         false),
           new attribute(strings[2521],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[75])),
                         false),
           new attribute(strings[2522], new named_type(IFC4_types[69]), false)},
          {false, false, false});
  ((entity *)IFC4_types[244])
      ->set_attributes(
          {new attribute(strings[2523], new named_type(IFC4_types[240]), true),
           new attribute(strings[2524], new named_type(IFC4_types[904]), true),
           new attribute(strings[2525], new named_type(IFC4_types[149]), true),
           new attribute(strings[2526], new named_type(IFC4_types[69]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[245])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2527],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[247])),
                         false)},
          {false, false});
  ((entity *)IFC4_types[246])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2523], new named_type(IFC4_types[248]), false),
           new attribute(strings[2528], new named_type(IFC4_types[687]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[247])
      ->set_attributes(
          {new attribute(strings[2529], new named_type(IFC4_types[516]), false),
           new attribute(strings[2530], new named_type(IFC4_types[685]),
                         false)},
          {false, false});
  ((entity *)IFC4_types[249])
      ->set_attributes({new attribute(strings[2457],
                                      new named_type(IFC4_types[685]), false)},
                       {false, false});
  ((entity *)IFC4_types[250])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[252]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[251])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[252]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[260])
      ->set_attributes(
          {new attribute(strings[2531], new named_type(IFC4_types[715]), false),
           new attribute(strings[2413], new named_type(IFC4_types[124]), false),
           new attribute(strings[2478], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[261])
      ->set_attributes(
          {new attribute(strings[2532],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[262])),
                         false),
           new attribute(strings[2533], new named_type(IFC4_types[263]), false),
           new attribute(strings[2534], new named_type(IFC4_types[505]), true)},
          {false, false, false});
  ((entity *)IFC4_types[262])
      ->set_attributes(
          {new attribute(strings[2535], new named_type(IFC4_types[609]), false),
           new attribute(strings[2536],
                         new simple_type(simple_type::integer_type), false)},
          {false, false});
  ((entity *)IFC4_types[265])
      ->set_attributes(
          {new attribute(strings[2537],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2538],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2539],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2540],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2541],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2542],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2543],
                         new simple_type(simple_type::integer_type), false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[267])
      ->set_attributes(
          {new attribute(strings[2544],
                         new aggregation_type(aggregation_type::list_type, 2, 3,
                                              new named_type(IFC4_types[775])),
                         false)},
          {false});
  ((entity *)IFC4_types[269])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[271]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[270])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[271]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[272])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[274]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[273])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[274]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[275])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[276])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[277])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[278])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[279])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[280])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[281])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[282])
      ->set_attributes(
          {new attribute(strings[2545], new named_type(IFC4_types[416]), true),
           new attribute(strings[2332], new named_type(IFC4_types[283]), true),
           new attribute(strings[2546], new named_type(IFC4_types[285]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[284])
      ->set_attributes(
          {new attribute(strings[2441], new named_type(IFC4_types[505]), true),
           new attribute(strings[2332], new named_type(IFC4_types[285]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[287])
      ->set_attributes(
          {new attribute(strings[2368], new named_type(IFC4_types[476]), false),
           new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2461], new named_type(IFC4_types[1119]), true),
           new attribute(strings[2339], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2547], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2548], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2549], new named_type(IFC4_types[505]), true),
           new attribute(strings[2550], new named_type(IFC4_types[8]), true),
           new attribute(strings[2551],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[8])),
                         true),
           new attribute(strings[2495], new named_type(IFC4_types[255]), true),
           new attribute(strings[2552], new named_type(IFC4_types[255]), true),
           new attribute(strings[2553], new named_type(IFC4_types[476]), true),
           new attribute(strings[2554], new named_type(IFC4_types[254]), true),
           new attribute(strings[2555], new named_type(IFC4_types[254]), true),
           new attribute(strings[2556], new named_type(IFC4_types[286]), true),
           new attribute(strings[2333], new named_type(IFC4_types[291]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4_types[288])
      ->set_attributes(
          {new attribute(strings[2557], new named_type(IFC4_types[287]), false),
           new attribute(strings[2558],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[287])),
                         false),
           new attribute(strings[2559], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[289])
      ->set_attributes(
          {new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2560], new named_type(IFC4_types[287]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[292])
      ->set_attributes(
          {new attribute(strings[2561], new named_type(IFC4_types[685]), true),
           new attribute(strings[2562], new named_type(IFC4_types[685]), true),
           new attribute(strings[2332], new named_type(IFC4_types[302]), true),
           new attribute(strings[2563], new named_type(IFC4_types[303]), true),
           new attribute(strings[2564], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4_types[293])
      ->set_attributes(
          {new attribute(strings[2565], new named_type(IFC4_types[685]), true),
           new attribute(strings[2566], new named_type(IFC4_types[610]), true),
           new attribute(strings[2567], new named_type(IFC4_types[685]), true),
           new attribute(strings[2568], new named_type(IFC4_types[610]), true),
           new attribute(strings[2569], new named_type(IFC4_types[610]), true),
           new attribute(strings[2570], new named_type(IFC4_types[516]), true),
           new attribute(strings[2571], new named_type(IFC4_types[516]), true),
           new attribute(strings[2572], new named_type(IFC4_types[516]), true),
           new attribute(strings[2573], new named_type(IFC4_types[685]), true),
           new attribute(strings[2574], new named_type(IFC4_types[685]), true),
           new attribute(strings[2575], new named_type(IFC4_types[890]), true),
           new attribute(strings[2576], new named_type(IFC4_types[516]), true),
           new attribute(strings[2577], new named_type(IFC4_types[516]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4_types[296])
      ->set_attributes(
          {new attribute(strings[2578], new named_type(IFC4_types[685]), true),
           new attribute(strings[2579], new named_type(IFC4_types[294]), false),
           new attribute(strings[2580], new named_type(IFC4_types[611]), true),
           new attribute(strings[2581], new named_type(IFC4_types[295]), false),
           new attribute(strings[2575], new named_type(IFC4_types[890]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[297])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false, false});
  ((entity *)IFC4_types[298])
      ->set_attributes(
          {new attribute(strings[2563], new named_type(IFC4_types[300]), false),
           new attribute(strings[2582], new named_type(IFC4_types[299]), false),
           new attribute(strings[2583], new named_type(IFC4_types[69]), false),
           new attribute(strings[2584], new named_type(IFC4_types[69]), false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4_types[301])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[302]), false),
           new attribute(strings[2563], new named_type(IFC4_types[303]), false),
           new attribute(strings[2583], new named_type(IFC4_types[69]), true),
           new attribute(strings[2564], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4_types[305])->set_attributes({}, {false});
  ((entity *)IFC4_types[306])->set_attributes({}, {false});
  ((entity *)IFC4_types[307])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[309]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[308])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[309]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[310])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[312]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[311])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[312]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[313])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[315]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[314])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[315]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[318])
      ->set_attributes({new attribute(strings[2585],
                                      new named_type(IFC4_types[1128]), false),
                        new attribute(strings[2586],
                                      new named_type(IFC4_types[1128]), false)},
                       {false, false});
  ((entity *)IFC4_types[319])
      ->set_attributes(
          {new attribute(strings[2587], new named_type(IFC4_types[237]), false),
           new attribute(strings[2475], new named_type(IFC4_types[69]), false)},
          {false, false, false, false});
  ((entity *)IFC4_types[320])
      ->set_attributes({new attribute(strings[2588],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4_types[631])),
                                      false)},
                       {false});
  ((entity *)IFC4_types[321])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[323]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[322])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[323]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[328])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[330]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[329])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[330]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[331])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[333]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[332])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[333]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[334])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[336]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[335])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[336]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[337])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[339]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[338])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[339]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[341])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[343]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[342])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[343]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[345])
      ->set_attributes(
          {new attribute(strings[2589], new named_type(IFC4_types[476]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[347])
      ->set_attributes(
          {new attribute(strings[2590], new named_type(IFC4_types[47]), true),
           new attribute(strings[2332], new named_type(IFC4_types[349]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[348])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[349]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[350])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[351])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[353])
      ->set_attributes(
          {new attribute(strings[2591], new named_type(IFC4_types[505]), true),
           new attribute(strings[2592],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[652])),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[354])
      ->set_attributes(
          {new attribute(strings[2593], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[346])
      ->set_attributes(
          {new attribute(strings[2479], new named_type(IFC4_types[56]), false)},
          {false});
  ((entity *)IFC4_types[355])
      ->set_attributes(
          {new attribute(strings[2594], new named_type(IFC4_types[685]), false),
           new attribute(strings[2595], new named_type(IFC4_types[685]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[356])
      ->set_attributes(
          {new attribute(strings[2594], new named_type(IFC4_types[685]), false),
           new attribute(strings[2595], new named_type(IFC4_types[685]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[357])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[358])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[360])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[362]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[361])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[362]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[363])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[365]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[364])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[365]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[366])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[368]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[367])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[368]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[369])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[373]), true),
           new attribute(strings[2596], new named_type(IFC4_types[371]), true),
           new attribute(strings[2597], new named_type(IFC4_types[505]), true),
           new attribute(strings[2598], new named_type(IFC4_types[370]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[370])
      ->set_attributes(
          {new attribute(strings[2599], new named_type(IFC4_types[255]), true),
           new attribute(strings[2600], new named_type(IFC4_types[255]), true),
           new attribute(strings[2601], new named_type(IFC4_types[255]), true),
           new attribute(strings[2602], new named_type(IFC4_types[255]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[372])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[373]), false),
           new attribute(strings[2596], new named_type(IFC4_types[371]), false),
           new attribute(strings[2597], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4_types[374])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[476]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2603],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[726])),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[375])->set_attributes({}, {});
  ((entity *)IFC4_types[379])
      ->set_attributes(
          {new attribute(strings[2461], new named_type(IFC4_types[1119]), true),
           new attribute(strings[2368], new named_type(IFC4_types[476]), true),
           new attribute(strings[2348], new named_type(IFC4_types[505]), true)},
          {false, false, false});
  ((entity *)IFC4_types[380])
      ->set_attributes(
          {new attribute(strings[2604], new named_type(IFC4_types[379]), false),
           new attribute(strings[2605],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[854])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[381])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[382]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[383])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[376])->set_attributes({}, {false, false, false});
  ((entity *)IFC4_types[377])->set_attributes({}, {false, false, false});
  ((entity *)IFC4_types[378])->set_attributes({}, {false, false, false});
  ((entity *)IFC4_types[384])
      ->set_attributes(
          {new attribute(strings[2606], new named_type(IFC4_types[267]), false),
           new attribute(strings[2442], new named_type(IFC4_types[685]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[385])
      ->set_attributes({new attribute(strings[2607],
                                      new named_type(IFC4_types[715]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC4_types[386])
      ->set_attributes(
          {new attribute(strings[2608],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[388])),
                         false)},
          {false});
  ((entity *)IFC4_types[387])
      ->set_attributes(
          {new attribute(strings[2609],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[177])),
                         false)},
          {false});
  ((entity *)IFC4_types[388])
      ->set_attributes(
          {new attribute(strings[2610], new named_type(IFC4_types[544]), false),
           new attribute(strings[2611], new named_type(IFC4_types[69]), false)},
          {false, false});
  ((entity *)IFC4_types[389])->set_attributes({}, {false, false});
  ((entity *)IFC4_types[390])
      ->set_attributes(
          {new attribute(strings[2612], new named_type(IFC4_types[1001]),
                         false),
           new attribute(strings[2475], new named_type(IFC4_types[69]), false)},
          {false, false, false});
  ((entity *)IFC4_types[391])->set_attributes({}, {false});
  ((entity *)IFC4_types[392])
      ->set_attributes(
          {new attribute(strings[2341],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[145])),
                         false)},
          {false, false});
  ((entity *)IFC4_types[393])
      ->set_attributes(
          {new attribute(strings[2613], new named_type(IFC4_types[441]), true),
           new attribute(strings[2614], new named_type(IFC4_types[441]), true),
           new attribute(strings[2615], new named_type(IFC4_types[441]), true),
           new attribute(strings[2616], new named_type(IFC4_types[441]), true),
           new attribute(strings[2617], new named_type(IFC4_types[441]), true),
           new attribute(strings[2618], new named_type(IFC4_types[441]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[394])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[396]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[395])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[396]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[397])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[399]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[398])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[399]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[400])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[401])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[402])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[403])
      ->set_attributes(
          {new attribute(strings[2619],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[406])),
                         false),
           new attribute(strings[2620], new named_type(IFC4_types[69]), true)},
          {false, false, false});
  ((entity *)IFC4_types[404])
      ->set_attributes(
          {new attribute(strings[2621], new named_type(IFC4_types[244]), false),
           new attribute(strings[2622], new named_type(IFC4_types[467]), false),
           new attribute(strings[2623], new named_type(IFC4_types[119]), true),
           new attribute(strings[2624], new named_type(IFC4_types[119]), true),
           new attribute(strings[2625], new named_type(IFC4_types[670]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[405])
      ->set_attributes(
          {new attribute(strings[2626],
                         new aggregation_type(aggregation_type::list_type, 2, 2,
                                              new named_type(IFC4_types[1126])),
                         false),
           new attribute(strings[2627],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[994])),
                         false),
           new attribute(strings[2628], new named_type(IFC4_types[687]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[407])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[409]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[408])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[409]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[410])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[412]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[411])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[412]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[413])
      ->set_attributes(
          {new attribute(strings[2629], new named_type(IFC4_types[237]), false),
           new attribute(strings[2630], new named_type(IFC4_types[638]), true),
           new attribute(strings[2631], new named_type(IFC4_types[638]), true),
           new attribute(strings[2632], new named_type(IFC4_types[267]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[414])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[415])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[417])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[418])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[419])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[421]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[420])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[421]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[422])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[424]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[423])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[424]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[425])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[426])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[427])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[428])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[429])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[430])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[431])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[432])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[433])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[434])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[438])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[440]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[439])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[440]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[443])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[444])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[445])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[447]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[446])
      ->set_attributes(
          {new attribute(strings[2590], new named_type(IFC4_types[47]), false),
           new attribute(strings[2332], new named_type(IFC4_types[447]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[448])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[450]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[449])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[450]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[451])->set_attributes({}, {false});
  ((entity *)IFC4_types[453])
      ->set_attributes(
          {new attribute(strings[2633], new named_type(IFC4_types[266]), false),
           new attribute(strings[2634], new named_type(IFC4_types[775]), true),
           new attribute(strings[2635], new named_type(IFC4_types[54]), false),
           new attribute(strings[2636], new named_type(IFC4_types[267]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[454])->set_attributes({}, {});
  ((entity *)IFC4_types[455])
      ->set_attributes(
          {new attribute(strings[2637], new named_type(IFC4_types[453]), false),
           new attribute(strings[2638], new named_type(IFC4_types[687]), true),
           new attribute(strings[2639], new named_type(IFC4_types[452]), false),
           new attribute(strings[2640], new named_type(IFC4_types[505]), true)},
          {false, false, true, true, true, true, false, false, false, false});
  ((entity *)IFC4_types[456])
      ->set_attributes(
          {new attribute(strings[2532],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[457])),
                         false)},
          {false});
  ((entity *)IFC4_types[460])
      ->set_attributes(
          {new attribute(strings[2641],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[461])),
                         false),
           new attribute(strings[2642],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[461])),
                         false),
           new attribute(strings[2643],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[461])),
                         true),
           new attribute(strings[2332], new named_type(IFC4_types[464]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[461])
      ->set_attributes(
          {new attribute(strings[2644], new named_type(IFC4_types[505]), true),
           new attribute(strings[2645], new named_type(IFC4_types[237]), false),
           new attribute(strings[2475], new named_type(IFC4_types[69]), false)},
          {false, false, false});
  ((entity *)IFC4_types[462])
      ->set_attributes(
          {new attribute(strings[2646], new named_type(IFC4_types[1135]),
                         false),
           new attribute(strings[2647], new named_type(IFC4_types[463]), true)},
          {false, false});
  ((entity *)IFC4_types[465])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC4_types[466])
      ->set_attributes(
          {new attribute(strings[2648], new named_type(IFC4_types[1001]),
                         false),
           new attribute(strings[2649], new named_type(IFC4_types[69]), false)},
          {false, false});
  ((entity *)IFC4_types[468])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[470]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[469])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[470]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[473])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[475]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[474])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[475]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[498])
      ->set_attributes(
          {new attribute(strings[2562], new named_type(IFC4_types[685]), false),
           new attribute(strings[2378], new named_type(IFC4_types[685]), false),
           new attribute(strings[2379], new named_type(IFC4_types[685]), false),
           new attribute(strings[2650], new named_type(IFC4_types[685]), false),
           new attribute(strings[2651], new named_type(IFC4_types[610]), true),
           new attribute(strings[2652], new named_type(IFC4_types[610]), true),
           new attribute(strings[2653], new named_type(IFC4_types[670]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[478])
      ->set_attributes({new attribute(strings[2654],
                                      new named_type(IFC4_types[1119]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4_types[479])
      ->set_attributes(
          {new attribute(strings[2655], new named_type(IFC4_types[1051]),
                         false),
           new attribute(strings[2656], new named_type(IFC4_types[611]), true),
           new attribute(strings[2657], new named_type(IFC4_types[152]), false),
           new attribute(strings[2658],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[684])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[480])
      ->set_attributes(
          {new attribute(strings[2659], new named_type(IFC4_types[120]), false),
           new attribute(strings[2473],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[882])),
                         true),
           new attribute(strings[2395], new named_type(IFC4_types[69]), true)},
          {false, false, false});
  ((entity *)IFC4_types[481])
      ->set_attributes({new attribute(strings[2660],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC4_types[684])),
                                      false)},
                       {false});
  ((entity *)IFC4_types[482])
      ->set_attributes(
          {new attribute(
              strings[2661],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, -1,
                                       new named_type(IFC4_types[684]))),
              false)},
          {false, false});
  ((entity *)IFC4_types[483])
      ->set_attributes({new attribute(strings[2655],
                                      new named_type(IFC4_types[1051]), false),
                        new attribute(strings[2662],
                                      new named_type(IFC4_types[1070]), false)},
                       {false, false, false});
  ((entity *)IFC4_types[484])
      ->set_attributes({new attribute(strings[2663],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new aggregation_type(
                                              aggregation_type::list_type, 3, 3,
                                              new named_type(IFC4_types[684]))),
                                      true)},
                       {false, false, false, false});
  ((entity *)IFC4_types[488])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[490]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[489])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[490]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[492])->set_attributes({}, {false, false, false});
  ((entity *)IFC4_types[493])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[494]), true),
           new attribute(strings[2664], new named_type(IFC4_types[8]), true),
           new attribute(strings[2665],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[647])),
                         true),
           new attribute(strings[2666], new named_type(IFC4_types[254]), true),
           new attribute(strings[2370], new named_type(IFC4_types[220]), true),
           new attribute(strings[2369], new named_type(IFC4_types[220]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[496])
      ->set_attributes(
          {new attribute(strings[2667],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[497])),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[497])
      ->set_attributes(
          {new attribute(strings[2668], new named_type(IFC4_types[255]), false),
           new attribute(strings[2669],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1121])),
                         false)},
          {false, false});
  ((entity *)IFC4_types[500])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[502]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[501])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[502]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[545])
      ->set_attributes(
          {new attribute(strings[2442], new named_type(IFC4_types[685]), false),
           new attribute(strings[2443], new named_type(IFC4_types[685]), true),
           new attribute(strings[2456], new named_type(IFC4_types[685]), false),
           new attribute(strings[2651], new named_type(IFC4_types[610]), true),
           new attribute(strings[2670], new named_type(IFC4_types[610]), true),
           new attribute(strings[2671], new named_type(IFC4_types[670]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[506])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[508]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[507])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[508]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4_types[509])
      ->set_attributes({new attribute(strings[2672],
                                      new named_type(IFC4_types[1079]), false),
                        new attribute(strings[2673],
                                      new named_type(IFC4_types[1037]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC4_types[510])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[512]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[511])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[512]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[517])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2345], new named_type(IFC4_types[505]), true),
           new attribute(strings[2674], new named_type(IFC4_types[8]), true),
           new attribute(strings[2675], new named_type(IFC4_types[255]), true),
           new attribute(strings[2461], new named_type(IFC4_types[1119]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[518])
      ->set_attributes(
          {new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2676], new named_type(IFC4_types[513]), true),
           new attribute(strings[2677], new named_type(IFC4_types[517]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[521])
      ->set_attributes(
          {new attribute(strings[2678], new named_type(IFC4_types[670]), false),
           new attribute(strings[2679],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[670])),
                         false),
           new attribute(strings[2680],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[547])),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[524])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[526]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[525])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[526]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[527])
      ->set_attributes(
          {new attribute(strings[2681], new named_type(IFC4_types[520]), false),
           new attribute(strings[2682],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[521])),
                         false)},
          {false, false});
  ((entity *)IFC4_types[528])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2683], new named_type(IFC4_types[151]), false),
           new attribute(strings[2684], new named_type(IFC4_types[611]), true),
           new attribute(strings[2685], new named_type(IFC4_types[611]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[529])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[530])
      ->set_attributes({new attribute(strings[2611],
                                      new named_type(IFC4_types[267]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC4_types[531])
      ->set_attributes(
          {new attribute(strings[2479], new named_type(IFC4_types[56]), false),
           new attribute(strings[2686], new named_type(IFC4_types[151]), true),
           new attribute(strings[2687], new named_type(IFC4_types[1076]),
                         false),
           new attribute(strings[2688], new named_type(IFC4_types[546]), false),
           new attribute(strings[2689], new named_type(IFC4_types[523]), false),
           new attribute(strings[2690], new named_type(IFC4_types[522]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[532])
      ->set_attributes(
          {new attribute(strings[2479], new named_type(IFC4_types[119]), false),
           new attribute(strings[2457], new named_type(IFC4_types[685]), false),
           new attribute(strings[2691], new named_type(IFC4_types[775]), false),
           new attribute(strings[2692], new named_type(IFC4_types[775]), false),
           new attribute(strings[2693], new named_type(IFC4_types[775]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[533])
      ->set_attributes(
          {new attribute(strings[2611], new named_type(IFC4_types[267]), false),
           new attribute(strings[2694], new named_type(IFC4_types[775]), true),
           new attribute(strings[2695], new named_type(IFC4_types[686]), false),
           new attribute(strings[2696], new named_type(IFC4_types[686]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4_types[534])
      ->set_attributes(
          {new attribute(strings[2697], new named_type(IFC4_types[119]), false),
           new attribute(strings[2698], new named_type(IFC4_types[1126]),
                         false)},
          {false, false});
  ((entity *)IFC4_types[541])
      ->set_attributes(
          {new attribute(strings[2699], new named_type(IFC4_types[618]), true),
           new attribute(strings[2700], new named_type(IFC4_types[54]), false)},
          {false, false});
  ((entity *)IFC4_types[544])->set_attributes({}, {});
  ((entity *)IFC4_types[551])
      ->set_attributes({new attribute(strings[2701],
                                      new named_type(IFC4_types[145]), false)},
                       {false});
  ((entity *)IFC4_types[552])
      ->set_attributes(
          {new attribute(strings[2702], new named_type(IFC4_types[516]), false),
           new attribute(strings[2703], new named_type(IFC4_types[516]), false),
           new attribute(strings[2704], new named_type(IFC4_types[516]), false),
           new attribute(strings[2705], new named_type(IFC4_types[775]), true),
           new attribute(strings[2706], new named_type(IFC4_types[775]), true),
           new attribute(strings[2452], new named_type(IFC4_types[775]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[553])
      ->set_attributes(
          {new attribute(strings[2707], new named_type(IFC4_types[849]), false),
           new attribute(strings[2708], new named_type(IFC4_types[123]),
                         false)},
          {false, false});
  ((entity *)IFC4_types[558])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2353], new named_type(IFC4_types[505]), true)},
          {false, false, false});
  ((entity *)IFC4_types[559])
      ->set_attributes(
          {new attribute(strings[2709],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[144])),
                         false),
           new attribute(strings[2710], new named_type(IFC4_types[558]),
                         false)},
          {false, false});
  ((entity *)IFC4_types[560])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2711], new named_type(IFC4_types[558]), false),
           new attribute(strings[2712], new named_type(IFC4_types[611]), true),
           new attribute(strings[2353], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[561])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2713],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[560])),
                         true)},
          {false, false, false});
  ((entity *)IFC4_types[562])->set_attributes({}, {});
  ((entity *)IFC4_types[563])
      ->set_attributes({new attribute(strings[2714],
                                      new named_type(IFC4_types[558]), false)},
                       {false, false, false, false});
  ((entity *)IFC4_types[564])
      ->set_attributes(
          {new attribute(strings[2711], new named_type(IFC4_types[558]), true),
           new attribute(strings[2715], new named_type(IFC4_types[610]), false),
           new attribute(strings[2716], new named_type(IFC4_types[542]), true),
           new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2353], new named_type(IFC4_types[505]), true),
           new attribute(strings[2717], new named_type(IFC4_types[486]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[565])
      ->set_attributes(
          {new attribute(strings[2718],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[564])),
                         false),
           new attribute(strings[2719], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]),
                         true)},
          {false, false, false});
  ((entity *)IFC4_types[566])
      ->set_attributes(
          {new attribute(strings[2720], new named_type(IFC4_types[565]), false),
           new attribute(strings[2721], new named_type(IFC4_types[515]), false),
           new attribute(strings[2722], new named_type(IFC4_types[268]), false),
           new attribute(strings[2723], new named_type(IFC4_types[516]), false),
           new attribute(strings[2724], new named_type(IFC4_types[685]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[567])
      ->set_attributes(
          {new attribute(strings[2725], new named_type(IFC4_types[515]), false),
           new attribute(strings[2726],
                         new aggregation_type(aggregation_type::array_type, 1,
                                              2,
                                              new named_type(IFC4_types[516])),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[568])
      ->set_attributes({new attribute(strings[2727],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4_types[558])),
                                      false)},
                       {false});
  ((entity *)IFC4_types[569])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2711], new named_type(IFC4_types[558]), true),
           new attribute(strings[2728], new named_type(IFC4_types[715]), false),
           new attribute(strings[2717], new named_type(IFC4_types[486]), true),
           new attribute(strings[2353], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[570])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2729],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[569])),
                         false),
           new attribute(strings[2730], new named_type(IFC4_types[168]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[571])
      ->set_attributes(
          {new attribute(strings[2731], new named_type(IFC4_types[570]), false),
           new attribute(strings[2732], new named_type(IFC4_types[118]), true),
           new attribute(strings[2724], new named_type(IFC4_types[685]), true)},
          {false, false, false});
  ((entity *)IFC4_types[572])
      ->set_attributes(
          {new attribute(strings[2733], new named_type(IFC4_types[570]), false),
           new attribute(strings[2734], new named_type(IFC4_types[118]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[573])
      ->set_attributes({new attribute(strings[2726],
                                      new aggregation_type(
                                          aggregation_type::array_type, 1, 2,
                                          new named_type(IFC4_types[516])),
                                      false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[574])
      ->set_attributes({new attribute(strings[2711],
                                      new named_type(IFC4_types[562]), false)},
                       {false, false, false, false});
  ((entity *)IFC4_types[575])
      ->set_attributes(
          {new attribute(strings[2735], new named_type(IFC4_types[558]), false),
           new attribute(strings[2736],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[558])),
                         false),
           new attribute(strings[2737], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[577])->set_attributes({}, {});
  ((entity *)IFC4_types[579])
      ->set_attributes({new attribute(strings[2738],
                                      new named_type(IFC4_types[1121]), false),
                        new attribute(strings[2739],
                                      new named_type(IFC4_types[1110]), false)},
                       {false, false});
  ((entity *)IFC4_types[580])
      ->set_attributes(
          {new attribute(strings[2740], new named_type(IFC4_types[685]), true),
           new attribute(strings[2741], new named_type(IFC4_types[685]), true),
           new attribute(strings[2332], new named_type(IFC4_types[582]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[581])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[582]), false),
           new attribute(strings[2740], new named_type(IFC4_types[685]), true),
           new attribute(strings[2741], new named_type(IFC4_types[685]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4_types[583])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[585]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[584])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[585]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[586])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[589]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[587])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[588])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[589]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[590])
      ->set_attributes(
          {new attribute(strings[2742], new named_type(IFC4_types[61]), false),
           new attribute(strings[2743], new named_type(IFC4_types[505]), true),
           new attribute(strings[2744], new named_type(IFC4_types[591]), true),
           new attribute(strings[2745], new named_type(IFC4_types[782]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[592])
      ->set_attributes({}, {false, false, false, true, false});
  ((entity *)IFC4_types[604])
      ->set_attributes({new attribute(strings[2746],
                                      new named_type(IFC4_types[505]), false)},
                       {false});
  ((entity *)IFC4_types[606])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[608]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[607])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[608]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[609])
      ->set_attributes(
          {new attribute(strings[2747], new named_type(IFC4_types[265]), false),
           new attribute(strings[2533], new named_type(IFC4_types[1118]),
                         false)},
          {false, false});
  ((entity *)IFC4_types[614])
      ->set_attributes(
          {new attribute(strings[2500], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[615])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[618])->set_attributes({}, {});
  ((entity *)IFC4_types[616])
      ->set_attributes(
          {new attribute(strings[2748],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[185])),
                         true),
           new attribute(strings[2749], new named_type(IFC4_types[543]), true),
           new attribute(strings[2750], new named_type(IFC4_types[617]), false),
           new attribute(strings[2751], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[621])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[622]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[623])
      ->set_attributes(
          {new attribute(strings[2752], new named_type(IFC4_types[237]), false),
           new attribute(strings[2753], new named_type(IFC4_types[516]), false),
           new attribute(strings[2395], new named_type(IFC4_types[542]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[624])
      ->set_attributes(
          {new attribute(strings[2752], new named_type(IFC4_types[237]), false),
           new attribute(strings[2753], new named_type(IFC4_types[516]), false),
           new attribute(strings[2395], new named_type(IFC4_types[542]), false),
           new attribute(strings[2390], new named_type(IFC4_types[267]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[628])->set_attributes({}, {false});
  ((entity *)IFC4_types[625])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[626]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[627])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[629])
      ->set_attributes(
          {new attribute(strings[2368], new named_type(IFC4_types[476]), true),
           new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2754],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[7])),
                         true),
           new attribute(strings[2755],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[12])),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[630])
      ->set_attributes(
          {new attribute(strings[2756], new named_type(IFC4_types[629]), false),
           new attribute(strings[2757],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[629])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[631])
      ->set_attributes(
          {new attribute(strings[2758], new named_type(IFC4_types[318]), false),
           new attribute(strings[2611], new named_type(IFC4_types[69]), false)},
          {true, true, false, false});
  ((entity *)IFC4_types[632])->set_attributes({}, {false, false});
  ((entity *)IFC4_types[633])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[635]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[634])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[635]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[636])
      ->set_attributes(
          {new attribute(strings[2759], new named_type(IFC4_types[648]), false),
           new attribute(strings[2760], new named_type(IFC4_types[35]), false),
           new attribute(strings[2761], new named_type(IFC4_types[950]), true),
           new attribute(strings[2762], new named_type(IFC4_types[129]), true),
           new attribute(strings[2763], new named_type(IFC4_types[1084]), true),
           new attribute(strings[2764], new named_type(IFC4_types[648]), true),
           new attribute(strings[2765], new named_type(IFC4_types[35]), true),
           new attribute(strings[2766], new named_type(IFC4_types[1084]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[637])
      ->set_attributes(
          {new attribute(strings[2479], new named_type(IFC4_types[55]), true)},
          {false, false, false});
  ((entity *)IFC4_types[639])
      ->set_attributes({new attribute(strings[2588],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4_types[631])),
                                      false)},
                       {false});
  ((entity *)IFC4_types[640])
      ->set_attributes({new attribute(strings[2520],
                                      new named_type(IFC4_types[1001]), false),
                        new attribute(strings[2767],
                                      new named_type(IFC4_types[237]), false)},
                       {false, false});
  ((entity *)IFC4_types[641])
      ->set_attributes(
          {new attribute(strings[2768], new named_type(IFC4_types[505]), false),
           new attribute(strings[2332], new named_type(IFC4_types[642]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[644])
      ->set_attributes(
          {new attribute(strings[2563], new named_type(IFC4_types[643]), false),
           new attribute(strings[2581], new named_type(IFC4_types[1154]),
                         false),
           new attribute(strings[2769], new named_type(IFC4_types[685]), true),
           new attribute(strings[2770], new named_type(IFC4_types[685]), true),
           new attribute(strings[2575], new named_type(IFC4_types[890]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[645])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[646]), true),
           new attribute(strings[2333], new named_type(IFC4_types[505]), true),
           new attribute(strings[2334], new named_type(IFC4_types[1053]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[647])
      ->set_attributes(
          {new attribute(strings[2368], new named_type(IFC4_types[476]), true),
           new attribute(strings[2771], new named_type(IFC4_types[505]), true),
           new attribute(strings[2772], new named_type(IFC4_types[505]), true),
           new attribute(strings[2773],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[505])),
                         true),
           new attribute(strings[2774],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[505])),
                         true),
           new attribute(strings[2775],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[505])),
                         true),
           new attribute(strings[2754],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[7])),
                         true),
           new attribute(strings[2755],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[12])),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[648])
      ->set_attributes(
          {new attribute(strings[2776], new named_type(IFC4_types[647]), false),
           new attribute(strings[2777], new named_type(IFC4_types[629]), false),
           new attribute(strings[2754],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[7])),
                         true)},
          {false, false, false});
  ((entity *)IFC4_types[650])
      ->set_attributes(
          {new attribute(strings[2778],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[652])),
                         false),
           new attribute(strings[2779], new named_type(IFC4_types[505]), false),
           new attribute(strings[2780], new named_type(IFC4_types[505]), true),
           new attribute(strings[2497], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[652])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2338], new named_type(IFC4_types[1053]),
                         true)},
          {false, false});
  ((entity *)IFC4_types[653])
      ->set_attributes(
          {new attribute(strings[2535], new named_type(IFC4_types[609]), true)},
          {false, false, false});
  ((entity *)IFC4_types[654])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[657]), true),
           new attribute(strings[2582], new named_type(IFC4_types[655]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[656])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[657]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[658])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[660]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[659])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[660]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[661])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[663]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[662])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[663]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[664])
      ->set_attributes(
          {new attribute(strings[2443], new named_type(IFC4_types[486]), false),
           new attribute(strings[2781], new named_type(IFC4_types[486]), false),
           new attribute(strings[2782], new named_type(IFC4_types[486]), false),
           new attribute(strings[2783],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[63])),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[665])
      ->set_attributes({new attribute(strings[2461],
                                      new named_type(IFC4_types[119]), false)},
                       {false});
  ((entity *)IFC4_types[666])
      ->set_attributes(
          {new attribute(strings[2784], new named_type(IFC4_types[54]), false)},
          {false, false, false});
  ((entity *)IFC4_types[667])
      ->set_attributes(
          {new attribute(strings[2785], new named_type(IFC4_types[516]), false),
           new attribute(strings[2786], new named_type(IFC4_types[516]),
                         false)},
          {false, false});
  ((entity *)IFC4_types[669])->set_attributes({}, {false});
  ((entity *)IFC4_types[671])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[674]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[672])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[673])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[674]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[675])->set_attributes({}, {});
  ((entity *)IFC4_types[676])
      ->set_attributes(
          {new attribute(strings[2752], new named_type(IFC4_types[237]), false),
           new attribute(strings[2787], new named_type(IFC4_types[638]),
                         false)},
          {false, false});
  ((entity *)IFC4_types[677])
      ->set_attributes(
          {new attribute(strings[2520], new named_type(IFC4_types[1001]),
                         false),
           new attribute(strings[2788], new named_type(IFC4_types[638]), false),
           new attribute(strings[2789], new named_type(IFC4_types[638]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[682])
      ->set_attributes({new attribute(strings[2790],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC4_types[119])),
                                      false)},
                       {false});
  ((entity *)IFC4_types[679])
      ->set_attributes(
          {new attribute(strings[2479], new named_type(IFC4_types[56]), false),
           new attribute(strings[2791], new named_type(IFC4_types[80]), false)},
          {false, false, false, false});
  ((entity *)IFC4_types[680])
      ->set_attributes(
          {new attribute(strings[2792], new named_type(IFC4_types[69]), true),
           new attribute(strings[2793],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[481])),
                         false),
           new attribute(strings[2794],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[684])),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4_types[681])
      ->set_attributes({new attribute(strings[2659],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4_types[119])),
                                      false)},
                       {false});
  ((entity *)IFC4_types[683])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[688])
      ->set_attributes(
          {new attribute(strings[2795], new named_type(IFC4_types[505]), true),
           new attribute(strings[2796],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[505])),
                         true),
           new attribute(strings[2797], new named_type(IFC4_types[505]), true),
           new attribute(strings[2798], new named_type(IFC4_types[505]), true),
           new attribute(strings[2799], new named_type(IFC4_types[505]), true),
           new attribute(strings[2800], new named_type(IFC4_types[505]), true),
           new attribute(strings[2801], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[690])->set_attributes({}, {false});
  ((entity *)IFC4_types[691])->set_attributes({}, {false});
  ((entity *)IFC4_types[692])
      ->set_attributes({new attribute(strings[2348],
                                      new named_type(IFC4_types[505]), false)},
                       {false});
  ((entity *)IFC4_types[693])->set_attributes({}, {});
  ((entity *)IFC4_types[694])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[695])->set_attributes({}, {false});
  ((entity *)IFC4_types[698])->set_attributes({}, {});
  ((entity *)IFC4_types[699])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2802],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[514])),
                         false),
           new attribute(strings[2357], new named_type(IFC4_types[476]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[700])
      ->set_attributes(
          {new attribute(strings[2803], new named_type(IFC4_types[542]), false),
           new attribute(strings[2804], new named_type(IFC4_types[542]), false),
           new attribute(strings[2805], new named_type(IFC4_types[542]), false),
           new attribute(strings[2806],
                         new aggregation_type(aggregation_type::set_type, 0, -1,
                                              new named_type(IFC4_types[701])),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[701])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true)},
          {false});
  ((entity *)IFC4_types[702])
      ->set_attributes(
          {new attribute(strings[2807],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[703])),
                         false)},
          {false});
  ((entity *)IFC4_types[705])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[707]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[706])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[707]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[708])
      ->set_attributes(
          {new attribute(strings[2368], new named_type(IFC4_types[476]), true),
           new attribute(strings[2334], new named_type(IFC4_types[1053]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[710])
      ->set_attributes(
          {new attribute(strings[2808], new named_type(IFC4_types[618]), true),
           new attribute(strings[2809], new named_type(IFC4_types[712]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[711])->set_attributes({}, {false, false, false});
  ((entity *)IFC4_types[712])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2810],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[846])),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[715])
      ->set_attributes(
          {new attribute(strings[2811], new named_type(IFC4_types[717]), false),
           new attribute(strings[2812], new named_type(IFC4_types[505]), true)},
          {false, false});
  ((entity *)IFC4_types[716])
      ->set_attributes({new attribute(strings[2813],
                                      new named_type(IFC4_types[715]), false)},
                       {false, false, false, false});
  ((entity *)IFC4_types[718])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[723])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[724])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[725]), true),
           new attribute(strings[2333], new named_type(IFC4_types[505]), true),
           new attribute(strings[2334], new named_type(IFC4_types[1053]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[719])
      ->set_attributes(
          {new attribute(strings[2814], new named_type(IFC4_types[476]), true),
           new attribute(strings[2815], new named_type(IFC4_types[476]), true),
           new attribute(strings[2816], new named_type(IFC4_types[609]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[721])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[722]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[726])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[476]), false),
           new attribute(strings[2338], new named_type(IFC4_types[1053]),
                         true)},
          {false, false});
  ((entity *)IFC4_types[727])->set_attributes({}, {});
  ((entity *)IFC4_types[728])
      ->set_attributes(
          {new attribute(strings[2817], new named_type(IFC4_types[1121]), true),
           new attribute(strings[2818], new named_type(IFC4_types[1121]), true),
           new attribute(strings[2535], new named_type(IFC4_types[1110]), true),
           new attribute(strings[2819], new named_type(IFC4_types[1121]),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[729])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[730])
      ->set_attributes(
          {new attribute(strings[2820], new named_type(IFC4_types[726]), false),
           new attribute(strings[2821], new named_type(IFC4_types[726]), false),
           new attribute(strings[2737], new named_type(IFC4_types[1053]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[731])
      ->set_attributes(
          {new attribute(strings[2822],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1121])),
                         true),
           new attribute(strings[2823], new named_type(IFC4_types[732]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[732])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2822],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1121])),
                         false),
           new attribute(strings[2535], new named_type(IFC4_types[1110]),
                         true)},
          {false, false, false});
  ((entity *)IFC4_types[733])
      ->set_attributes({new attribute(strings[2669],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4_types[1121])),
                                      true),
                        new attribute(strings[2535],
                                      new named_type(IFC4_types[1110]), true)},
                       {false, false, false, false});
  ((entity *)IFC4_types[734])
      ->set_attributes(
          {new attribute(strings[2469], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2824], new named_type(IFC4_types[619]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[735])
      ->set_attributes(
          {new attribute(strings[2470],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[726])),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[736])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[739])
      ->set_attributes(
          {new attribute(strings[2471], new named_type(IFC4_types[740]), true),
           new attribute(strings[2825], new named_type(IFC4_types[476]), true),
           new attribute(strings[2472],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[743])),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[741])
      ->set_attributes(
          {new attribute(strings[2826], new named_type(IFC4_types[1121]), true),
           new attribute(strings[2535], new named_type(IFC4_types[1110]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4_types[742])
      ->set_attributes(
          {new attribute(strings[2827],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1121])),
                         true),
           new attribute(strings[2828],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1121])),
                         true),
           new attribute(strings[2737], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2829], new named_type(IFC4_types[1110]), true),
           new attribute(strings[2830], new named_type(IFC4_types[1110]), true),
           new attribute(strings[2831], new named_type(IFC4_types[241]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[743])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[744])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[745])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[750]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[746])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[748]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[747])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[748]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[749])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[750]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[751])
      ->set_attributes(
          {new attribute(strings[2832], new named_type(IFC4_types[620]), false),
           new attribute(strings[2589], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[752])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[754]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[753])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[754]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[755])
      ->set_attributes(
          {new attribute(strings[2833], new named_type(IFC4_types[45]), false),
           new attribute(strings[2834], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[756])
      ->set_attributes(
          {new attribute(strings[2835], new named_type(IFC4_types[221]), false),
           new attribute(strings[2834], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[757])
      ->set_attributes(
          {new attribute(strings[2836], new named_type(IFC4_types[516]), false),
           new attribute(strings[2834], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[758])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[759])
      ->set_attributes(
          {new attribute(strings[2837], new named_type(IFC4_types[1078]),
                         false),
           new attribute(strings[2834], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[760])
      ->set_attributes(
          {new attribute(strings[2838], new named_type(IFC4_types[1138]),
                         false),
           new attribute(strings[2834], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[761])
      ->set_attributes(
          {new attribute(strings[2839], new named_type(IFC4_types[556]), false),
           new attribute(strings[2834], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[763])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[765]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[764])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[765]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[766])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[771]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[767])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[769]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[768])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[769]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[770])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[771]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[773])
      ->set_attributes(
          {new attribute(strings[2840],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC4_types[775])),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[774])
      ->set_attributes(
          {new attribute(
              strings[2840],
              new aggregation_type(
                  aggregation_type::list_type, 2, -1,
                  new aggregation_type(aggregation_type::list_type, 2, -1,
                                       new named_type(IFC4_types[775]))),
              false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4_types[776])
      ->set_attributes(
          {new attribute(strings[2444], new named_type(IFC4_types[685]), false),
           new attribute(strings[2841], new named_type(IFC4_types[610]), true),
           new attribute(strings[2842], new named_type(IFC4_types[610]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[777])
      ->set_attributes(
          {new attribute(strings[2433], new named_type(IFC4_types[685]), false),
           new attribute(strings[2434], new named_type(IFC4_types[685]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[778])
      ->set_attributes(
          {new attribute(strings[2410], new named_type(IFC4_types[685]), false),
           new attribute(strings[2411], new named_type(IFC4_types[685]), false),
           new attribute(strings[2781], new named_type(IFC4_types[685]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[779])
      ->set_attributes(
          {new attribute(strings[2520], new named_type(IFC4_types[1001]),
                         false),
           new attribute(strings[2843], new named_type(IFC4_types[638]), false),
           new attribute(strings[2844], new named_type(IFC4_types[638]), false),
           new attribute(strings[2845], new named_type(IFC4_types[638]), false),
           new attribute(strings[2846], new named_type(IFC4_types[638]), false),
           new attribute(strings[2847], new named_type(IFC4_types[69]), false),
           new attribute(strings[2848], new named_type(IFC4_types[69]), false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[780])
      ->set_attributes(
          {new attribute(strings[2849], new named_type(IFC4_types[781]), false),
           new attribute(strings[2850],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[256])),
                         true),
           new attribute(strings[2851],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[257])),
                         true),
           new attribute(strings[2852],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[605])),
                         true),
           new attribute(strings[2479], new named_type(IFC4_types[486]), true),
           new attribute(strings[2853], new named_type(IFC4_types[486]), true),
           new attribute(strings[2854], new named_type(IFC4_types[486]), true),
           new attribute(strings[2855],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1080])),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[782])
      ->set_attributes(
          {new attribute(strings[2856], new named_type(IFC4_types[476]), true),
           new attribute(strings[2857], new named_type(IFC4_types[476]), true),
           new attribute(strings[2858], new named_type(IFC4_types[505]), true),
           new attribute(strings[2859],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[486])),
                         true),
           new attribute(strings[2860], new named_type(IFC4_types[782]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[784])
      ->set_attributes({new attribute(strings[2861],
                                      new named_type(IFC4_types[1078]), false),
                        new attribute(strings[2667],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4_types[1083])),
                                      false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[785])
      ->set_attributes(
          {new attribute(strings[2862], new named_type(IFC4_types[45]), false),
           new attribute(strings[2863], new named_type(IFC4_types[505]), false),
           new attribute(strings[2864], new named_type(IFC4_types[789]), true),
           new attribute(strings[2865], new named_type(IFC4_types[516]), true),
           new attribute(strings[2866], new named_type(IFC4_types[685]), true),
           new attribute(strings[2867], new named_type(IFC4_types[221]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[786])
      ->set_attributes(
          {new attribute(strings[2868], new named_type(IFC4_types[505]), true),
           new attribute(strings[2869],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[880])),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[787])
      ->set_attributes(
          {new attribute(strings[2740], new named_type(IFC4_types[685]), true),
           new attribute(strings[2870], new named_type(IFC4_types[45]), true),
           new attribute(strings[2871], new named_type(IFC4_types[685]), true),
           new attribute(strings[2332], new named_type(IFC4_types[791]), true),
           new attribute(strings[2864], new named_type(IFC4_types[789]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4_types[790])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[791]), false),
           new attribute(strings[2740], new named_type(IFC4_types[685]), true),
           new attribute(strings[2870], new named_type(IFC4_types[45]), true),
           new attribute(strings[2871], new named_type(IFC4_types[685]), true),
           new attribute(strings[2864], new named_type(IFC4_types[789]), true),
           new attribute(strings[2872], new named_type(IFC4_types[505]), true),
           new attribute(strings[2873],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[62])),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4_types[792])
      ->set_attributes(
          {new attribute(strings[2863], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[793])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[794])
      ->set_attributes(
          {new attribute(strings[2874], new named_type(IFC4_types[685]), true),
           new attribute(strings[2875], new named_type(IFC4_types[685]), true),
           new attribute(strings[2876], new named_type(IFC4_types[685]), true),
           new attribute(strings[2877], new named_type(IFC4_types[685]), true),
           new attribute(strings[2878], new named_type(IFC4_types[45]), true),
           new attribute(strings[2879], new named_type(IFC4_types[45]), true),
           new attribute(strings[2880], new named_type(IFC4_types[685]), true),
           new attribute(strings[2881], new named_type(IFC4_types[685]), true),
           new attribute(strings[2332], new named_type(IFC4_types[796]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[795])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[796]), false),
           new attribute(strings[2874], new named_type(IFC4_types[685]), true),
           new attribute(strings[2875], new named_type(IFC4_types[685]), true),
           new attribute(strings[2876], new named_type(IFC4_types[685]), true),
           new attribute(strings[2877], new named_type(IFC4_types[685]), true),
           new attribute(strings[2878], new named_type(IFC4_types[45]), true),
           new attribute(strings[2879], new named_type(IFC4_types[45]), true),
           new attribute(strings[2880], new named_type(IFC4_types[685]), true),
           new attribute(strings[2881], new named_type(IFC4_types[685]), true),
           new attribute(strings[2872], new named_type(IFC4_types[505]), true),
           new attribute(strings[2873],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[62])),
                         true)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4_types[797])
      ->set_attributes(
          {new attribute(strings[2882], new named_type(IFC4_types[615]), false),
           new attribute(strings[2883],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[615])),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[798])
      ->set_attributes(
          {new attribute(strings[2883],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[615])),
                         false),
           new attribute(strings[2884], new named_type(IFC4_types[620]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[799])
      ->set_attributes(
          {new attribute(strings[2885], new named_type(IFC4_types[6]), false),
           new attribute(strings[2886], new named_type(IFC4_types[7]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[800])
      ->set_attributes({new attribute(strings[2887],
                                      new named_type(IFC4_types[201]), false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[801])
      ->set_attributes({new attribute(strings[2888],
                                      new named_type(IFC4_types[465]), false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[802])
      ->set_attributes(
          {new attribute(strings[2889], new named_type(IFC4_types[772]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[803])
      ->set_attributes(
          {new attribute(strings[2890], new named_type(IFC4_types[709]), false),
           new attribute(strings[2891], new named_type(IFC4_types[579]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[804])
      ->set_attributes({new attribute(strings[2892],
                                      new named_type(IFC4_types[714]), false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[805])
      ->set_attributes({new attribute(strings[2893],
                                      new named_type(IFC4_types[855]), false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[806])
      ->set_attributes(
          {new attribute(strings[2883],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[258])),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[807])
      ->set_attributes(
          {new attribute(strings[2363], new named_type(IFC4_types[38]), false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[808])
      ->set_attributes({new attribute(strings[2894],
                                      new named_type(IFC4_types[144]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4_types[809])
      ->set_attributes(
          {new attribute(strings[2895], new named_type(IFC4_types[505]), true),
           new attribute(strings[2896], new named_type(IFC4_types[185]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[810])
      ->set_attributes({new attribute(strings[2557],
                                      new named_type(IFC4_types[290]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4_types[811])
      ->set_attributes({new attribute(strings[2897],
                                      new named_type(IFC4_types[519]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4_types[812])
      ->set_attributes({new attribute(strings[2735],
                                      new named_type(IFC4_types[576]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4_types[814])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[815])
      ->set_attributes(
          {new attribute(strings[2898], new named_type(IFC4_types[179]), true),
           new attribute(strings[2899], new named_type(IFC4_types[345]), false),
           new attribute(strings[2900], new named_type(IFC4_types[345]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[816])
      ->set_attributes(
          {new attribute(strings[2901],
                         new aggregation_type(aggregation_type::list_type, 0,
                                              -1,
                                              new named_type(IFC4_types[486])),
                         false),
           new attribute(strings[2902],
                         new aggregation_type(aggregation_type::list_type, 0,
                                              -1,
                                              new named_type(IFC4_types[486])),
                         false),
           new attribute(strings[2903], new named_type(IFC4_types[183]), false),
           new attribute(strings[2904], new named_type(IFC4_types[183]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[818])
      ->set_attributes(
          {new attribute(strings[2905], new named_type(IFC4_types[683]), false),
           new attribute(strings[2900], new named_type(IFC4_types[278]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[817])
      ->set_attributes(
          {new attribute(strings[2905], new named_type(IFC4_types[683]), false),
           new attribute(strings[2906], new named_type(IFC4_types[683]), false),
           new attribute(strings[2907], new named_type(IFC4_types[345]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[819])
      ->set_attributes(
          {new attribute(strings[2899], new named_type(IFC4_types[953]), false),
           new attribute(strings[2908], new named_type(IFC4_types[952]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[820])
      ->set_attributes(
          {new attribute(strings[2909], new named_type(IFC4_types[979]), false),
           new attribute(strings[2910], new named_type(IFC4_types[955]), false),
           new attribute(strings[2911], new named_type(IFC4_types[74]), true),
           new attribute(strings[2912], new named_type(IFC4_types[956]), true),
           new attribute(strings[2913], new named_type(IFC4_types[516]), true),
           new attribute(strings[2914], new named_type(IFC4_types[56]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[821])
      ->set_attributes({new attribute(strings[2915],
                                      new named_type(IFC4_types[179]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4_types[822])
      ->set_attributes(
          {new attribute(strings[2916],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[345])),
                         false),
           new attribute(strings[2917], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[823])
      ->set_attributes(
          {new attribute(strings[2918],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[710])),
                         false),
           new attribute(strings[2919], new named_type(IFC4_types[928]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[824])
      ->set_attributes(
          {new attribute(strings[2920], new named_type(IFC4_types[345]), false),
           new attribute(strings[2921],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[222])),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[825])
      ->set_attributes(
          {new attribute(strings[2922], new named_type(IFC4_types[921]), false),
           new attribute(strings[2921],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[222])),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[826])
      ->set_attributes(
          {new attribute(strings[2923], new named_type(IFC4_types[198]), false),
           new attribute(strings[2924],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[258])),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[827])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[828])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[829])
      ->set_attributes(
          {new attribute(strings[2883],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[614])),
                         false),
           new attribute(strings[2882], new named_type(IFC4_types[614]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[830])
      ->set_attributes(
          {new attribute(strings[2883],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[615])),
                         false),
           new attribute(strings[2925], new named_type(IFC4_types[737]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[831])
      ->set_attributes(
          {new attribute(strings[2926],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[736])),
                         false),
           new attribute(strings[2927], new named_type(IFC4_types[739]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[832])
      ->set_attributes(
          {new attribute(strings[2883],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[614])),
                         false),
           new attribute(strings[2928], new named_type(IFC4_types[1106]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[833])
      ->set_attributes(
          {new attribute(strings[2929], new named_type(IFC4_types[625]), false),
           new attribute(strings[2930], new named_type(IFC4_types[345]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[834])
      ->set_attributes(
          {new attribute(strings[2931],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[276])),
                         false),
           new attribute(strings[2932], new named_type(IFC4_types[280]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[835])
      ->set_attributes(
          {new attribute(strings[2899], new named_type(IFC4_types[345]), false),
           new attribute(strings[2900], new named_type(IFC4_types[345]), false),
           new attribute(strings[2933], new named_type(IFC4_types[179]), true),
           new attribute(strings[2934], new named_type(IFC4_types[476]), true),
           new attribute(strings[2935],
                         new simple_type(simple_type::logical_type), false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[836])
      ->set_attributes(
          {new attribute(strings[2882], new named_type(IFC4_types[615]), false),
           new attribute(strings[2883],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[615])),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[837])
      ->set_attributes(
          {new attribute(strings[2899], new named_type(IFC4_types[345]), false),
           new attribute(strings[2936], new named_type(IFC4_types[401]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[838])
      ->set_attributes(
          {new attribute(strings[2918],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[710])),
                         false),
           new attribute(strings[2919], new named_type(IFC4_types[928]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[839])
      ->set_attributes(
          {new attribute(strings[2890], new named_type(IFC4_types[708]), false),
           new attribute(strings[2937], new named_type(IFC4_types[708]), false),
           new attribute(strings[2938], new named_type(IFC4_types[509]), true),
           new attribute(strings[2939], new named_type(IFC4_types[886]), true),
           new attribute(strings[2940], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[840])
      ->set_attributes(
          {new attribute(strings[2941], new named_type(IFC4_types[1026]),
                         false),
           new attribute(strings[2942],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[928])),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[841])
      ->set_attributes(
          {new attribute(strings[2922], new named_type(IFC4_types[922]), false),
           new attribute(strings[2930], new named_type(IFC4_types[345]), false),
           new attribute(strings[2898], new named_type(IFC4_types[179]), true),
           new attribute(strings[2943], new named_type(IFC4_types[651]), false),
           new attribute(strings[2944], new named_type(IFC4_types[491]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[842])
      ->set_attributes(
          {new attribute(strings[2945], new named_type(IFC4_types[842]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[843])
      ->set_attributes(
          {new attribute(strings[2946], new named_type(IFC4_types[843]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[844])
      ->set_attributes(
          {new attribute(strings[2920], new named_type(IFC4_types[345]), false),
           new attribute(strings[2947], new named_type(IFC4_types[402]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[813])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[845])
      ->set_attributes({new attribute(strings[2948],
                                      new named_type(IFC4_types[638]), false)},
                       {false, false, false, false});
  ((entity *)IFC4_types[846])
      ->set_attributes(
          {new attribute(strings[2949], new named_type(IFC4_types[847]), false),
           new attribute(strings[2950], new named_type(IFC4_types[505]), true),
           new attribute(strings[2951], new named_type(IFC4_types[505]), true),
           new attribute(strings[2952],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[848])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[847])
      ->set_attributes(
          {new attribute(strings[2953], new named_type(IFC4_types[505]), true),
           new attribute(strings[2954], new named_type(IFC4_types[505]), true)},
          {false, false});
  ((entity *)IFC4_types[848])->set_attributes({}, {});
  ((entity *)IFC4_types[849])
      ->set_attributes(
          {new attribute(strings[2955], new named_type(IFC4_types[54]), false),
           new attribute(strings[2956], new named_type(IFC4_types[846]),
                         false)},
          {false, false});
  ((entity *)IFC4_types[850])
      ->set_attributes(
          {new attribute(strings[2368], new named_type(IFC4_types[476]), true),
           new attribute(strings[2334], new named_type(IFC4_types[1053]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[851])
      ->set_attributes(
          {new attribute(strings[2605],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[854])),
                         false),
           new attribute(strings[2363], new named_type(IFC4_types[38]), false)},
          {false, false, false, false});
  ((entity *)IFC4_types[852])
      ->set_attributes(
          {new attribute(strings[2896], new named_type(IFC4_types[185]), false),
           new attribute(strings[2605],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[854])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[853])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]),
                         true)},
          {false, false});
  ((entity *)IFC4_types[856])
      ->set_attributes(
          {new attribute(strings[2957], new named_type(IFC4_types[316]), true),
           new attribute(strings[2958], new named_type(IFC4_types[687]), true),
           new attribute(strings[2959], new named_type(IFC4_types[255]), true),
           new attribute(strings[2960], new named_type(IFC4_types[255]), true),
           new attribute(strings[2961], new named_type(IFC4_types[505]), true),
           new attribute(strings[2962], new named_type(IFC4_types[316]), true),
           new attribute(strings[2963], new named_type(IFC4_types[69]), true),
           new attribute(strings[2964], new named_type(IFC4_types[255]), true),
           new attribute(strings[2965], new named_type(IFC4_types[316]), true),
           new attribute(strings[2966], new named_type(IFC4_types[687]), true),
           new attribute(strings[2967], new named_type(IFC4_types[255]), true),
           new attribute(strings[2968], new named_type(IFC4_types[255]), true),
           new attribute(strings[2969], new named_type(IFC4_types[316]), true),
           new attribute(strings[2970], new named_type(IFC4_types[687]), true),
           new attribute(strings[2971], new named_type(IFC4_types[687]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[857])
      ->set_attributes(
          {new attribute(strings[2389], new named_type(IFC4_types[53]), false),
           new attribute(strings[2972], new named_type(IFC4_types[670]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[858])
      ->set_attributes({new attribute(strings[2607],
                                      new named_type(IFC4_types[715]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC4_types[859])
      ->set_attributes(
          {new attribute(strings[2781], new named_type(IFC4_types[685]), false),
           new attribute(strings[2973], new named_type(IFC4_types[685]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[860])
      ->set_attributes(
          {new attribute(strings[2781], new named_type(IFC4_types[685]), false),
           new attribute(strings[2457], new named_type(IFC4_types[685]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[862])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[864]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[863])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[864]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[865])
      ->set_attributes(
          {new attribute(strings[2974], new named_type(IFC4_types[458]), false),
           new attribute(strings[2975], new named_type(IFC4_types[636]), true),
           new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4_types[870])
      ->set_attributes({new attribute(strings[2976],
                                      new named_type(IFC4_types[685]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4_types[902])
      ->set_attributes(
          {new attribute(strings[2977], new named_type(IFC4_types[900]), true),
           new attribute(strings[2348], new named_type(IFC4_types[903]),
                         false)},
          {true, false, false, false});
  ((entity *)IFC4_types[871])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[873]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[872])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[873]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[874])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2978], new named_type(IFC4_types[253]), true),
           new attribute(strings[2979], new named_type(IFC4_types[505]), true)},
          {false, false, false});
  ((entity *)IFC4_types[875])->set_attributes({}, {false, false, false});
  ((entity *)IFC4_types[879])
      ->set_attributes(
          {new attribute(strings[2980], new named_type(IFC4_types[881]), false),
           new attribute(strings[2981], new named_type(IFC4_types[715]), false),
           new attribute(strings[2982], new named_type(IFC4_types[715]), true)},
          {false, false, false});
  ((entity *)IFC4_types[880])
      ->set_attributes(
          {new attribute(strings[2983], new named_type(IFC4_types[516]), false),
           new attribute(strings[2984], new named_type(IFC4_types[516]), false),
           new attribute(strings[2985], new named_type(IFC4_types[516]), true),
           new attribute(strings[2986], new named_type(IFC4_types[788]), false),
           new attribute(strings[2987], new named_type(IFC4_types[879]), false),
           new attribute(strings[2988],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[785])),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[877])
      ->set_attributes(
          {new attribute(strings[2989], new named_type(IFC4_types[165]), false),
           new attribute(strings[2990],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC4_types[715])),
                         false),
           new attribute(strings[2991],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC4_types[56])),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[883])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[885]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[884])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[885]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[887])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[889]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[888])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[889]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[890])
      ->set_attributes(
          {new attribute(strings[2992],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[891])),
                         false),
           new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2993], new named_type(IFC4_types[542]), false),
           new attribute(strings[2994], new named_type(IFC4_types[713]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[891])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[892])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[895])
      ->set_attributes(
          {new attribute(strings[2995],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[894])),
                         false)},
          {false});
  ((entity *)IFC4_types[896])->set_attributes({}, {false, false});
  ((entity *)IFC4_types[897])
      ->set_attributes(
          {new attribute(strings[2471], new named_type(IFC4_types[898]), true),
           new attribute(strings[2996], new named_type(IFC4_types[505]), true),
           new attribute(strings[2997], new named_type(IFC4_types[505]), true),
           new attribute(strings[2998], new named_type(IFC4_types[732]), true),
           new attribute(strings[2999], new named_type(IFC4_types[1110]), true),
           new attribute(strings[3000], new named_type(IFC4_types[1110]), true),
           new attribute(strings[2737], new named_type(IFC4_types[505]), true),
           new attribute(strings[3001], new named_type(IFC4_types[950]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4_types[901])
      ->set_attributes(
          {new attribute(strings[3002], new named_type(IFC4_types[169]), true),
           new attribute(strings[3003], new named_type(IFC4_types[169]), true),
           new attribute(strings[3004], new named_type(IFC4_types[516]), true),
           new attribute(strings[3005], new named_type(IFC4_types[505]), true),
           new attribute(strings[3006], new named_type(IFC4_types[688]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4_types[905])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[909]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[906])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[907])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[908])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[909]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[910])
      ->set_attributes(
          {new attribute(strings[3007], new named_type(IFC4_types[516]), true),
           new attribute(strings[3008], new named_type(IFC4_types[516]), true),
           new attribute(strings[3009], new named_type(IFC4_types[516]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[911])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[913]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[912])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[913]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[915])->set_attributes({}, {});
  ((entity *)IFC4_types[921])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[927]), true),
           new attribute(strings[3010], new named_type(IFC4_types[516]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[923])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[925]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[924])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[925]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[926])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[927]), false),
           new attribute(strings[2441], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[928])
      ->set_attributes(
          {new attribute(strings[2441], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[929])
      ->set_attributes(
          {new attribute(strings[2593], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[930])
      ->set_attributes(
          {new attribute(strings[3011], new named_type(IFC4_types[352]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[931])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[932])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[934]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[933])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[934]), false),
           new attribute(strings[2441], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[939])
      ->set_attributes({new attribute(strings[2457],
                                      new named_type(IFC4_types[685]), false)},
                       {false, false});
  ((entity *)IFC4_types[940])
      ->set_attributes({new attribute(strings[2457],
                                      new named_type(IFC4_types[685]), false)},
                       {false, false});
  ((entity *)IFC4_types[941])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[943]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[942])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[943]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[944])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[949]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[945])
      ->set_attributes(
          {new attribute(strings[3012], new named_type(IFC4_types[486]), true),
           new attribute(strings[3013], new named_type(IFC4_types[486]), true),
           new attribute(strings[3014], new named_type(IFC4_types[685]), true),
           new attribute(strings[3015], new named_type(IFC4_types[685]), true),
           new attribute(strings[2332], new named_type(IFC4_types[947]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4_types[946])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[947]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[948])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[949]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[951])
      ->set_attributes(
          {new attribute(strings[3016], new named_type(IFC4_types[69]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[952])
      ->set_attributes(
          {new attribute(strings[3017], new named_type(IFC4_types[966]), false),
           new attribute(strings[3018], new named_type(IFC4_types[459]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[954])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[30]), false),
           new attribute(strings[3019], new named_type(IFC4_types[56]), true),
           new attribute(strings[3020],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[969])),
                         true),
           new attribute(strings[3021],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[985])),
                         true),
           new attribute(strings[3022], new named_type(IFC4_types[618]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[955])
      ->set_attributes(
          {new attribute(strings[2911], new named_type(IFC4_types[74]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[956])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true)},
          {false});
  ((entity *)IFC4_types[957])
      ->set_attributes(
          {new attribute(strings[3023], new named_type(IFC4_types[720]), true),
           new attribute(strings[2332], new named_type(IFC4_types[958]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4_types[959])
      ->set_attributes(
          {new attribute(strings[2389], new named_type(IFC4_types[267]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[960])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[961]), false),
           new attribute(strings[2389], new named_type(IFC4_types[267]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[962])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[963])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[958]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[964])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[965])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false});
  ((entity *)IFC4_types[966])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true)},
          {false});
  ((entity *)IFC4_types[967])
      ->set_attributes(
          {new attribute(strings[3024],
                         new aggregation_type(aggregation_type::list_type, 3, 3,
                                              new named_type(IFC4_types[772])),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[968])
      ->set_attributes({new attribute(strings[2667],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4_types[971])),
                                      false),
                        new attribute(strings[3025],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new aggregation_type(
                                              aggregation_type::list_type, 1, 2,
                                              new named_type(IFC4_types[516]))),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4_types[969])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[540]), false),
           new attribute(strings[3026], new named_type(IFC4_types[5]), false),
           new attribute(strings[3027], new named_type(IFC4_types[4]), false),
           new attribute(strings[3028], new named_type(IFC4_types[772]), true),
           new attribute(strings[2339], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[970])
      ->set_attributes(
          {new attribute(strings[3029], new named_type(IFC4_types[535]), true),
           new attribute(strings[3030], new named_type(IFC4_types[535]), true),
           new attribute(strings[3031], new named_type(IFC4_types[535]), true),
           new attribute(strings[3032], new named_type(IFC4_types[536]), true),
           new attribute(strings[3033], new named_type(IFC4_types[536]), true),
           new attribute(strings[3034], new named_type(IFC4_types[536]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[971])->set_attributes({}, {false});
  ((entity *)IFC4_types[972])
      ->set_attributes(
          {new attribute(strings[3035], new named_type(IFC4_types[668]), true),
           new attribute(strings[3036], new named_type(IFC4_types[668]), true),
           new attribute(strings[3037], new named_type(IFC4_types[668]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[973])
      ->set_attributes(
          {new attribute(strings[3038], new named_type(IFC4_types[516]), true),
           new attribute(strings[3039], new named_type(IFC4_types[516]), true),
           new attribute(strings[3040], new named_type(IFC4_types[516]), true),
           new attribute(strings[3041], new named_type(IFC4_types[670]), true),
           new attribute(strings[3042], new named_type(IFC4_types[670]), true),
           new attribute(strings[3043], new named_type(IFC4_types[670]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[974])
      ->set_attributes(
          {new attribute(strings[3044], new named_type(IFC4_types[236]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[975])
      ->set_attributes(
          {new attribute(strings[3045], new named_type(IFC4_types[441]), true),
           new attribute(strings[3046], new named_type(IFC4_types[441]), true),
           new attribute(strings[3047], new named_type(IFC4_types[441]), true),
           new attribute(strings[3048], new named_type(IFC4_types[1088]), true),
           new attribute(strings[3049], new named_type(IFC4_types[1088]), true),
           new attribute(strings[3050], new named_type(IFC4_types[1088]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[976])
      ->set_attributes(
          {new attribute(strings[3051], new named_type(IFC4_types[1146]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[977])->set_attributes({}, {false});
  ((entity *)IFC4_types[978])
      ->set_attributes(
          {new attribute(strings[3052], new named_type(IFC4_types[1076]), true),
           new attribute(strings[3053], new named_type(IFC4_types[1076]), true),
           new attribute(strings[3054], new named_type(IFC4_types[1076]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4_types[979])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[980])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false});
  ((entity *)IFC4_types[981])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false});
  ((entity *)IFC4_types[982])
      ->set_attributes(
          {new attribute(strings[2914], new named_type(IFC4_types[56]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[983])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[984])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[985])
      ->set_attributes(
          {new attribute(strings[3055], new named_type(IFC4_types[31]), false),
           new attribute(strings[3056], new named_type(IFC4_types[969]), true),
           new attribute(strings[3057], new named_type(IFC4_types[69]), false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[986])
      ->set_attributes(
          {new attribute(strings[3023], new named_type(IFC4_types[720]), true),
           new attribute(strings[2332], new named_type(IFC4_types[987]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4_types[988])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[989])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[990]), false),
           new attribute(strings[2456], new named_type(IFC4_types[685]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[991])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[992])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[987]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[996])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[994])
      ->set_attributes(
          {new attribute(strings[3058], new named_type(IFC4_types[848]), true),
           new attribute(strings[2807],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[993])),
                         false),
           new attribute(strings[2348], new named_type(IFC4_types[505]), true)},
          {false, false, false});
  ((entity *)IFC4_types[995])->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[997])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[999]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[998])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[999]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4_types[1000])
      ->set_attributes({new attribute(strings[3059],
                                      new named_type(IFC4_types[318]), false)},
                       {false, false, false});
  ((entity *)IFC4_types[1001])->set_attributes({}, {});
  ((entity *)IFC4_types[1002])
      ->set_attributes(
          {new attribute(strings[3060], new named_type(IFC4_types[237]), false),
           new attribute(strings[3061],
                         new aggregation_type(aggregation_type::list_type, 1, 2,
                                              new named_type(IFC4_types[640])),
                         false),
           new attribute(strings[3062], new named_type(IFC4_types[696]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[1003])
      ->set_attributes(
          {new attribute(strings[2629], new named_type(IFC4_types[237]), false),
           new attribute(strings[2630], new named_type(IFC4_types[638]), true),
           new attribute(strings[2631], new named_type(IFC4_types[638]), true),
           new attribute(strings[3063], new named_type(IFC4_types[1001]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[1004])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1005]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1006])
      ->set_attributes(
          {new attribute(strings[2606], new named_type(IFC4_types[267]), false),
           new attribute(strings[2442], new named_type(IFC4_types[516]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[1007])
      ->set_attributes(
          {new attribute(strings[3064], new named_type(IFC4_types[53]), false)},
          {false, false, false});
  ((entity *)IFC4_types[1009])
      ->set_attributes(
          {new attribute(strings[3065],
                         new aggregation_type(aggregation_type::list_type, 2, 3,
                                              new named_type(IFC4_types[516])),
                         true),
           new attribute(strings[3066],
                         new aggregation_type(aggregation_type::list_type, 2, 3,
                                              new named_type(IFC4_types[516])),
                         true),
           new attribute(strings[3067], new named_type(IFC4_types[772]), true)},
          {false, false, false, false});
  ((entity *)IFC4_types[1011])
      ->set_attributes(
          {new attribute(strings[3068], new named_type(IFC4_types[1010]),
                         false),
           new attribute(strings[2807],
                         new aggregation_type(aggregation_type::set_type, 1, 5,
                                              new named_type(IFC4_types[1012])),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[1013])
      ->set_attributes(
          {new attribute(strings[3069], new named_type(IFC4_types[151]), false),
           new attribute(strings[3070], new named_type(IFC4_types[151]), false),
           new attribute(strings[3071], new named_type(IFC4_types[151]), false),
           new attribute(strings[3072], new named_type(IFC4_types[151]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4_types[1014])
      ->set_attributes(
          {new attribute(strings[3073], new named_type(IFC4_types[775]), true),
           new attribute(strings[3074], new named_type(IFC4_types[775]), true)},
          {false, false});
  ((entity *)IFC4_types[1015])
      ->set_attributes(
          {new attribute(strings[3075], new named_type(IFC4_types[150]), true),
           new attribute(strings[3071], new named_type(IFC4_types[150]), true),
           new attribute(strings[3069], new named_type(IFC4_types[150]), true),
           new attribute(strings[3076], new named_type(IFC4_types[150]), true),
           new attribute(strings[3077], new named_type(IFC4_types[150]), true),
           new attribute(strings[3078], new named_type(IFC4_types[937]), true),
           new attribute(strings[3079], new named_type(IFC4_types[783]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1016])
      ->set_attributes(
          {new attribute(strings[3080], new named_type(IFC4_types[151]), false),
           new attribute(strings[3081], new named_type(IFC4_types[611]), true)},
          {false, false});
  ((entity *)IFC4_types[1017])
      ->set_attributes({new attribute(strings[3082],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4_types[1018])),
                                      false)},
                       {false});
  ((entity *)IFC4_types[1018])
      ->set_attributes(
          {new attribute(strings[3083], new named_type(IFC4_types[69]), false),
           new attribute(strings[3084], new named_type(IFC4_types[69]), false),
           new attribute(strings[3085], new named_type(IFC4_types[476]), true),
           new attribute(strings[3086], new named_type(IFC4_types[124]), true),
           new attribute(strings[3087],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[476])),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[1019])
      ->set_attributes(
          {new attribute(strings[3088], new named_type(IFC4_types[715]), false),
           new attribute(strings[2479], new named_type(IFC4_types[56]), true)},
          {false, false});
  ((entity *)IFC4_types[1020])
      ->set_attributes(
          {new attribute(strings[2629], new named_type(IFC4_types[237]), false),
           new attribute(strings[2457], new named_type(IFC4_types[685]), false),
           new attribute(strings[3089], new named_type(IFC4_types[685]), true),
           new attribute(strings[2630], new named_type(IFC4_types[638]), true),
           new attribute(strings[2631], new named_type(IFC4_types[638]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[1021])
      ->set_attributes(
          {new attribute(strings[2651], new named_type(IFC4_types[685]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[1022])
      ->set_attributes(
          {new attribute(strings[3090], new named_type(IFC4_types[715]), false),
           new attribute(strings[2479], new named_type(IFC4_types[56]), true)},
          {false, false});
  ((entity *)IFC4_types[1023])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1025]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1024])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1025]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1026])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC4_types[1027])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1029]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1028])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1029]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1102])
      ->set_attributes(
          {new attribute(strings[2442], new named_type(IFC4_types[685]), false),
           new attribute(strings[3091], new named_type(IFC4_types[685]), false),
           new attribute(strings[2379], new named_type(IFC4_types[685]), false),
           new attribute(strings[2650], new named_type(IFC4_types[685]), false),
           new attribute(strings[2651], new named_type(IFC4_types[610]), true),
           new attribute(strings[2652], new named_type(IFC4_types[610]), true),
           new attribute(strings[3092], new named_type(IFC4_types[610]), true),
           new attribute(strings[3093], new named_type(IFC4_types[670]), true),
           new attribute(strings[2653], new named_type(IFC4_types[670]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4_types[1030])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[3094],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1032])),
                         true),
           new attribute(strings[3095],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1031])),
                         true)},
          {false, false, false});
  ((entity *)IFC4_types[1031])
      ->set_attributes(
          {new attribute(strings[2357], new named_type(IFC4_types[476]), true),
           new attribute(strings[2348], new named_type(IFC4_types[505]), true),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[2535], new named_type(IFC4_types[1110]), true),
           new attribute(strings[2745], new named_type(IFC4_types[782]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[1032])
      ->set_attributes(
          {new attribute(strings[3096],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1121])),
                         true),
           new attribute(strings[3097], new named_type(IFC4_types[69]), true)},
          {false, false});
  ((entity *)IFC4_types[1033])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1035]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1034])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1035]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1036])
      ->set_attributes(
          {new attribute(strings[2333], new named_type(IFC4_types[505]), true),
           new attribute(strings[3098], new named_type(IFC4_types[505]), true),
           new attribute(strings[3099], new named_type(IFC4_types[69]), false),
           new attribute(strings[2717], new named_type(IFC4_types[486]), true),
           new attribute(strings[3100], new named_type(IFC4_types[1038]), true),
           new attribute(strings[2332], new named_type(IFC4_types[1041]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4_types[1038])
      ->set_attributes(
          {new attribute(strings[2673], new named_type(IFC4_types[1037]), true),
           new attribute(strings[3101], new named_type(IFC4_types[316]), true),
           new attribute(strings[2959], new named_type(IFC4_types[255]), true),
           new attribute(strings[2960], new named_type(IFC4_types[255]), true),
           new attribute(strings[3102], new named_type(IFC4_types[255]), true),
           new attribute(strings[3103], new named_type(IFC4_types[255]), true),
           new attribute(strings[3104], new named_type(IFC4_types[255]), true),
           new attribute(strings[3105], new named_type(IFC4_types[255]), true),
           new attribute(strings[3106], new named_type(IFC4_types[316]), true),
           new attribute(strings[3107], new named_type(IFC4_types[316]), true),
           new attribute(strings[3108], new named_type(IFC4_types[69]), true),
           new attribute(strings[2964], new named_type(IFC4_types[255]), true),
           new attribute(strings[3109], new named_type(IFC4_types[316]), true),
           new attribute(strings[2967], new named_type(IFC4_types[255]), true),
           new attribute(strings[2968], new named_type(IFC4_types[255]), true),
           new attribute(strings[3110], new named_type(IFC4_types[316]), true),
           new attribute(strings[2971], new named_type(IFC4_types[687]), true)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4_types[1039])
      ->set_attributes({new attribute(strings[3111],
                                      new named_type(IFC4_types[780]), false)},
                       {false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1040])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1041]),
                         false),
           new attribute(strings[3098], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[1042])
      ->set_attributes(
          {new attribute(strings[3112],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[505])),
                         true),
           new attribute(strings[3113],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[505])),
                         true),
           new attribute(strings[3114], new named_type(IFC4_types[505]), true),
           new attribute(strings[3115],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[505])),
                         true),
           new attribute(strings[3116], new named_type(IFC4_types[1119]), true),
           new attribute(strings[3117],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1119])),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1045])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1050]), true),
           new attribute(strings[2740], new named_type(IFC4_types[685]), true),
           new attribute(strings[2870], new named_type(IFC4_types[45]), true),
           new attribute(strings[3118], new named_type(IFC4_types[441]), true),
           new attribute(strings[3119], new named_type(IFC4_types[704]), true),
           new attribute(strings[3120], new named_type(IFC4_types[611]), true),
           new attribute(strings[3121], new named_type(IFC4_types[685]), true),
           new attribute(strings[3122], new named_type(IFC4_types[685]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1046])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1048]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1047])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1048]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1049])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1050]),
                         false),
           new attribute(strings[2740], new named_type(IFC4_types[685]), true),
           new attribute(strings[2870], new named_type(IFC4_types[45]), true),
           new attribute(strings[3123], new named_type(IFC4_types[685]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4_types[1051])
      ->set_attributes({new attribute(strings[2447],
                                      new named_type(IFC4_types[122]), false)},
                       {false});
  ((entity *)IFC4_types[1052])->set_attributes({}, {});
  ((entity *)IFC4_types[1058])
      ->set_attributes(
          {new attribute(strings[3124], new named_type(IFC4_types[697]), false),
           new attribute(strings[2784], new named_type(IFC4_types[54]), false),
           new attribute(strings[3125], new named_type(IFC4_types[1060]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[1059])
      ->set_attributes(
          {new attribute(strings[3126], new named_type(IFC4_types[667]), false),
           new attribute(strings[3127], new named_type(IFC4_types[83]), false)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[1061])
      ->set_attributes(
          {new attribute(strings[3128], new named_type(IFC4_types[1063]), true),
           new attribute(strings[3129], new named_type(IFC4_types[1064]), true),
           new attribute(strings[3130], new named_type(IFC4_types[1057]),
                         false),
           new attribute(strings[2526], new named_type(IFC4_types[69]), true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[1062])
      ->set_attributes(
          {new attribute(strings[3131],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[1056])),
                         false),
           new attribute(strings[3132], new named_type(IFC4_types[435]), true),
           new attribute(strings[3133], new named_type(IFC4_types[436]), true),
           new attribute(strings[3134], new named_type(IFC4_types[437]), true),
           new attribute(strings[3135], new named_type(IFC4_types[904]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[1063])
      ->set_attributes(
          {new attribute(strings[3136], new named_type(IFC4_types[149]), false),
           new attribute(strings[3137], new named_type(IFC4_types[149]), true)},
          {false, false});
  ((entity *)IFC4_types[1064])
      ->set_attributes(
          {new attribute(strings[3138], new named_type(IFC4_types[904]), true),
           new attribute(strings[3139], new named_type(IFC4_types[1054]), true),
           new attribute(strings[3140], new named_type(IFC4_types[1055]), true),
           new attribute(strings[3141], new named_type(IFC4_types[904]), true),
           new attribute(strings[3142], new named_type(IFC4_types[904]), true),
           new attribute(strings[3143], new named_type(IFC4_types[1065]), true),
           new attribute(strings[3144], new named_type(IFC4_types[904]), true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1066])
      ->set_attributes({new attribute(strings[3145],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4_types[1018])),
                                      false)},
                       {false});
  ((entity *)IFC4_types[1067])
      ->set_attributes(
          {new attribute(strings[3085], new named_type(IFC4_types[505]), false),
           new attribute(strings[3087],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[775])),
                         true)},
          {false, false, false});
  ((entity *)IFC4_types[1068])
      ->set_attributes({new attribute(strings[3146],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC4_types[1069])),
                                      false),
                        new attribute(strings[2655],
                                      new named_type(IFC4_types[386]), false)},
                       {false, false, false});
  ((entity *)IFC4_types[1069])
      ->set_attributes(
          {new attribute(strings[2447],
                         new aggregation_type(aggregation_type::list_type, 2, 2,
                                              new named_type(IFC4_types[638])),
                         false)},
          {false});
  ((entity *)IFC4_types[1070])
      ->set_attributes({new attribute(strings[3147],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new aggregation_type(
                                              aggregation_type::list_type, 2, 2,
                                              new named_type(IFC4_types[638]))),
                                      false)},
                       {false});
  ((entity *)IFC4_types[1080])
      ->set_attributes({new attribute(strings[3148],
                                      new named_type(IFC4_types[1077]), false),
                        new attribute(strings[3149],
                                      new named_type(IFC4_types[1077]), false)},
                       {false, false});
  ((entity *)IFC4_types[1081])
      ->set_attributes(
          {new attribute(strings[2348], new named_type(IFC4_types[505]), false),
           new attribute(strings[2338], new named_type(IFC4_types[1053]), true),
           new attribute(strings[3148], new named_type(IFC4_types[255]), false),
           new attribute(strings[3149], new named_type(IFC4_types[255]), false),
           new attribute(strings[3150], new named_type(IFC4_types[1082]),
                         false),
           new attribute(strings[2978], new named_type(IFC4_types[253]), false),
           new attribute(strings[2979], new named_type(IFC4_types[505]), true),
           new attribute(strings[2535], new named_type(IFC4_types[1110]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1083])
      ->set_attributes({new attribute(strings[2669],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4_types[1121])),
                                      false)},
                       {false});
  ((entity *)IFC4_types[1085])->set_attributes({}, {});
  ((entity *)IFC4_types[1086])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4_types[1087])
      ->set_attributes(
          {new attribute(strings[3151], new named_type(IFC4_types[685]), false),
           new attribute(strings[3152], new named_type(IFC4_types[685]),
                         false)},
          {false, false, false});
  ((entity *)IFC4_types[1089])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1091]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1090])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1091]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1094])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1096]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1095])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1096]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1097])
      ->set_attributes(
          {new attribute(strings[3153], new named_type(IFC4_types[685]), false),
           new attribute(strings[3154], new named_type(IFC4_types[685]), false),
           new attribute(strings[2434], new named_type(IFC4_types[685]), false),
           new attribute(strings[3155], new named_type(IFC4_types[516]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1098])
      ->set_attributes(
          {new attribute(
               strings[3156],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4_types[638]))),
               true),
           new attribute(strings[2792], new named_type(IFC4_types[69]), true),
           new attribute(
               strings[2660],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4_types[684]))),
               false),
           new attribute(strings[2794],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[684])),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[1099])
      ->set_attributes(
          {new attribute(strings[2752], new named_type(IFC4_types[237]), false),
           new attribute(strings[3157],
                         new aggregation_type(aggregation_type::set_type, 1, 2,
                                              new named_type(IFC4_types[1101])),
                         false),
           new attribute(strings[3158],
                         new aggregation_type(aggregation_type::set_type, 1, 2,
                                              new named_type(IFC4_types[1101])),
                         false),
           new attribute(strings[3159], new named_type(IFC4_types[69]), false),
           new attribute(strings[3062], new named_type(IFC4_types[1100]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4_types[1103])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1105]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1104])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1105]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1106])
      ->set_attributes(
          {new attribute(strings[3160], new named_type(IFC4_types[476]), true),
           new attribute(strings[3161],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[736])),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[1107])
      ->set_attributes(
          {new attribute(strings[2368], new named_type(IFC4_types[476]), true),
           new attribute(strings[2334], new named_type(IFC4_types[1053]), true),
           new attribute(strings[3162], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1108])
      ->set_attributes(
          {new attribute(strings[3163],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4_types[849])),
                         true),
           new attribute(strings[2589], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1109])
      ->set_attributes(
          {new attribute(strings[2368], new named_type(IFC4_types[476]), true),
           new attribute(strings[2334], new named_type(IFC4_types[1053]), true),
           new attribute(strings[3164], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1120])
      ->set_attributes(
          {new attribute(strings[2442], new named_type(IFC4_types[685]), false),
           new attribute(strings[3091], new named_type(IFC4_types[685]), false),
           new attribute(strings[2379], new named_type(IFC4_types[685]), false),
           new attribute(strings[2650], new named_type(IFC4_types[685]), false),
           new attribute(strings[2651], new named_type(IFC4_types[610]), true),
           new attribute(strings[2670], new named_type(IFC4_types[610]), true),
           new attribute(strings[2653], new named_type(IFC4_types[670]), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4_types[1117])
      ->set_attributes(
          {new attribute(strings[3165],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[1110])),
                         false)},
          {false});
  ((entity *)IFC4_types[1111])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1113]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1112])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1113]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1114])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1116]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1115])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1116]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1122])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1124]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1123])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1124]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1126])
      ->set_attributes(
          {new attribute(strings[2611], new named_type(IFC4_types[267]), false),
           new attribute(strings[3166], new named_type(IFC4_types[516]),
                         false)},
          {false, false});
  ((entity *)IFC4_types[1128])->set_attributes({}, {});
  ((entity *)IFC4_types[1129])
      ->set_attributes({new attribute(strings[3167],
                                      new named_type(IFC4_types[1128]), false)},
                       {false});
  ((entity *)IFC4_types[1130])
      ->set_attributes({new attribute(strings[3168],
                                      new named_type(IFC4_types[675]), false)},
                       {false});
  ((entity *)IFC4_types[1131])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1133]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1132])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1133]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1134])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1135])
      ->set_attributes(
          {new attribute(strings[3169],
                         new aggregation_type(aggregation_type::list_type, 2, 2,
                                              new named_type(IFC4_types[461])),
                         false),
           new attribute(strings[3170],
                         new aggregation_type(aggregation_type::list_type, 2, 3,
                                              new named_type(IFC4_types[516])),
                         false)},
          {false, false});
  ((entity *)IFC4_types[1136])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1137]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1140])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1144]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1141])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1142])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1143])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1144]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1148])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1150]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1149])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1150]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4_types[1151])
      ->set_attributes(
          {new attribute(strings[2561], new named_type(IFC4_types[685]), true),
           new attribute(strings[2562], new named_type(IFC4_types[685]), true),
           new attribute(strings[2332], new named_type(IFC4_types[1161]), true),
           new attribute(strings[3171], new named_type(IFC4_types[1162]), true),
           new attribute(strings[3172], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4_types[1152])
      ->set_attributes(
          {new attribute(strings[2565], new named_type(IFC4_types[685]), true),
           new attribute(strings[2566], new named_type(IFC4_types[610]), true),
           new attribute(strings[2569], new named_type(IFC4_types[610]), true),
           new attribute(strings[3173], new named_type(IFC4_types[610]), true),
           new attribute(strings[3174], new named_type(IFC4_types[611]), true),
           new attribute(strings[3175], new named_type(IFC4_types[611]), true),
           new attribute(strings[3176], new named_type(IFC4_types[611]), true),
           new attribute(strings[3177], new named_type(IFC4_types[611]), true),
           new attribute(strings[2575], new named_type(IFC4_types[890]), true),
           new attribute(strings[2571], new named_type(IFC4_types[516]), true),
           new attribute(strings[2576], new named_type(IFC4_types[516]), true),
           new attribute(strings[2577], new named_type(IFC4_types[516]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4_types[1155])
      ->set_attributes(
          {new attribute(strings[2563], new named_type(IFC4_types[1153]),
                         false),
           new attribute(strings[2581], new named_type(IFC4_types[1154]),
                         false),
           new attribute(strings[2769], new named_type(IFC4_types[685]), true),
           new attribute(strings[2770], new named_type(IFC4_types[685]), true),
           new attribute(strings[2575], new named_type(IFC4_types[890]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1156])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false, false});
  ((entity *)IFC4_types[1157])
      ->set_attributes(
          {new attribute(strings[2582], new named_type(IFC4_types[1158]),
                         false),
           new attribute(strings[2563], new named_type(IFC4_types[1159]),
                         false),
           new attribute(strings[2583], new named_type(IFC4_types[69]), false),
           new attribute(strings[2584], new named_type(IFC4_types[69]), false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4_types[1160])
      ->set_attributes(
          {new attribute(strings[2332], new named_type(IFC4_types[1161]),
                         false),
           new attribute(strings[3171], new named_type(IFC4_types[1162]),
                         false),
           new attribute(strings[2583], new named_type(IFC4_types[69]), true),
           new attribute(strings[3172], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4_types[1163])
      ->set_attributes(
          {new attribute(strings[3178],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[1170])),
                         true),
           new attribute(strings[3179],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[1170])),
                         true),
           new attribute(strings[2332], new named_type(IFC4_types[1164]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1165])
      ->set_attributes(
          {new attribute(strings[2766], new named_type(IFC4_types[255]), false),
           new attribute(strings[3180],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4_types[647])),
                         true),
           new attribute(strings[2339], new named_type(IFC4_types[505]), true),
           new attribute(strings[3181], new named_type(IFC4_types[316]), true),
           new attribute(strings[3107], new named_type(IFC4_types[316]), true),
           new attribute(strings[3148], new named_type(IFC4_types[255]), false),
           new attribute(strings[3182], new named_type(IFC4_types[255]), true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4_types[1166])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1167]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false});
  ((entity *)IFC4_types[1168])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC4_types[1169]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false});
  ((entity *)IFC4_types[1170])
      ->set_attributes(
          {new attribute(strings[3183], new named_type(IFC4_types[780]), true),
           new attribute(strings[3184], new named_type(IFC4_types[254]), true),
           new attribute(strings[3185], new named_type(IFC4_types[254]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[1172])
      ->set_attributes(
          {new attribute(strings[2442], new named_type(IFC4_types[685]), false),
           new attribute(strings[3091], new named_type(IFC4_types[685]), false),
           new attribute(strings[2379], new named_type(IFC4_types[685]), false),
           new attribute(strings[2650], new named_type(IFC4_types[685]), false),
           new attribute(strings[2651], new named_type(IFC4_types[610]), true),
           new attribute(strings[2670], new named_type(IFC4_types[610]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4_types[1171])
      ->set_attributes(
          {new attribute(strings[2441], new named_type(IFC4_types[505]), true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4_types[6])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3186], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[799]),
          ((entity *)IFC4_types[799])->attributes()[0])});
  ((entity *)IFC4_types[7])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3187], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[380]),
          ((entity *)IFC4_types[380])->attributes()[1])});
  ((entity *)IFC4_types[12])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3188], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[647]),
                                 ((entity *)IFC4_types[647])->attributes()[7]),
           new inverse_attribute(
               strings[3189], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[629]),
               ((entity *)IFC4_types[629])->attributes()[4])});
  ((entity *)IFC4_types[33])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3190], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[823]),
          ((entity *)IFC4_types[823])->attributes()[0])});
  ((entity *)IFC4_types[36])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3187], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[380]),
          ((entity *)IFC4_types[380])->attributes()[1])});
  ((entity *)IFC4_types[38])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3191], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[380]),
                                 ((entity *)IFC4_types[380])->attributes()[1]),
           new inverse_attribute(strings[3192], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[807]),
                                 ((entity *)IFC4_types[807])->attributes()[0]),
           new inverse_attribute(strings[3193], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[851]),
                                 ((entity *)IFC4_types[851])->attributes()[1]),
           new inverse_attribute(strings[3194], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[39]),
                                 ((entity *)IFC4_types[39])->attributes()[1]),
           new inverse_attribute(strings[3195], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[39]),
                                 ((entity *)IFC4_types[39])->attributes()[0])});
  ((entity *)IFC4_types[141])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3196], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[808]),
                                 ((entity *)IFC4_types[808])->attributes()[0]),
           new inverse_attribute(
               strings[3197], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[142]),
               ((entity *)IFC4_types[142])->attributes()[0])});
  ((entity *)IFC4_types[142])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3198], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[808]),
                                 ((entity *)IFC4_types[808])->attributes()[0]),
           new inverse_attribute(
               strings[3197], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[142]),
               ((entity *)IFC4_types[142])->attributes()[0])});
  ((entity *)IFC4_types[167])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3199], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4_types[165]),
          ((entity *)IFC4_types[165])->attributes()[0])});
  ((entity *)IFC4_types[185])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3191], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[380]),
                                 ((entity *)IFC4_types[380])->attributes()[1]),
           new inverse_attribute(
               strings[3200], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[852]),
               ((entity *)IFC4_types[852])->attributes()[0])});
  ((entity *)IFC4_types[198])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3201], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[830]),
                                 ((entity *)IFC4_types[830])->attributes()[0]),
           new inverse_attribute(
               strings[3202], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[826]),
               ((entity *)IFC4_types[826])->attributes()[0])});
  ((entity *)IFC4_types[200])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3187], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[380]),
          ((entity *)IFC4_types[380])->attributes()[1])});
  ((entity *)IFC4_types[201])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3203], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[800]),
          ((entity *)IFC4_types[800])->attributes()[0])});
  ((entity *)IFC4_types[205])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3187], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[380]),
          ((entity *)IFC4_types[380])->attributes()[1])});
  ((entity *)IFC4_types[214])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3204], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[213]),
          ((entity *)IFC4_types[213])->attributes()[0])});
  ((entity *)IFC4_types[222])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3205], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[825]),
                                 ((entity *)IFC4_types[825])->attributes()[1]),
           new inverse_attribute(
               strings[3206], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4_types[824]),
               ((entity *)IFC4_types[824])->attributes()[1])});
  ((entity *)IFC4_types[276])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3207], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[834]),
          ((entity *)IFC4_types[834])->attributes()[0])});
  ((entity *)IFC4_types[278])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3208], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[818]),
          ((entity *)IFC4_types[818])->attributes()[1])});
  ((entity *)IFC4_types[280])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3209], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[834]),
          ((entity *)IFC4_types[834])->attributes()[1])});
  ((entity *)IFC4_types[287])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3210], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[810]),
                                 ((entity *)IFC4_types[810])->attributes()[0]),
           new inverse_attribute(strings[3211], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[289]),
                                 ((entity *)IFC4_types[289])->attributes()[1]),
           new inverse_attribute(strings[3212], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[288]),
                                 ((entity *)IFC4_types[288])->attributes()[1]),
           new inverse_attribute(
               strings[3213], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4_types[288]),
               ((entity *)IFC4_types[288])->attributes()[0])});
  ((entity *)IFC4_types[289])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3214], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[810]),
          ((entity *)IFC4_types[810])->attributes()[0])});
  ((entity *)IFC4_types[345])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3215], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[833]),
                                 ((entity *)IFC4_types[833])->attributes()[1]),
           new inverse_attribute(strings[3216], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[815]),
                                 ((entity *)IFC4_types[815])->attributes()[1]),
           new inverse_attribute(strings[3217], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[835]),
                                 ((entity *)IFC4_types[835])->attributes()[1]),
           new inverse_attribute(strings[3218], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[835]),
                                 ((entity *)IFC4_types[835])->attributes()[0]),
           new inverse_attribute(strings[3219], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[837]),
                                 ((entity *)IFC4_types[837])->attributes()[0]),
           new inverse_attribute(strings[3220], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[838]),
                                 ((entity *)IFC4_types[838])->attributes()[0]),
           new inverse_attribute(strings[3221], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[844]),
                                 ((entity *)IFC4_types[844])->attributes()[0]),
           new inverse_attribute(strings[3222], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[822]),
                                 ((entity *)IFC4_types[822])->attributes()[0]),
           new inverse_attribute(strings[3223], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[841]),
                                 ((entity *)IFC4_types[841])->attributes()[1]),
           new inverse_attribute(strings[3224], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[815]),
                                 ((entity *)IFC4_types[815])->attributes()[2]),
           new inverse_attribute(strings[3190], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[823]),
                                 ((entity *)IFC4_types[823])->attributes()[0]),
           new inverse_attribute(
               strings[3225], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[824]),
               ((entity *)IFC4_types[824])->attributes()[0])});
  ((entity *)IFC4_types[379])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3226], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[380]),
          ((entity *)IFC4_types[380])->attributes()[0])});
  ((entity *)IFC4_types[381])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3227], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[841]),
          ((entity *)IFC4_types[841])->attributes()[0])});
  ((entity *)IFC4_types[386])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3228], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[1068]),
          ((entity *)IFC4_types[1068])->attributes()[1])});
  ((entity *)IFC4_types[401])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3229], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4_types[837]),
          ((entity *)IFC4_types[837])->attributes()[1])});
  ((entity *)IFC4_types[402])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3230], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4_types[844]),
          ((entity *)IFC4_types[844])->attributes()[1])});
  ((entity *)IFC4_types[453])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3231], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[455]),
                                 ((entity *)IFC4_types[455])->attributes()[0]),
           new inverse_attribute(
               strings[3204], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4_types[213]),
               ((entity *)IFC4_types[213])->attributes()[0])});
  ((entity *)IFC4_types[460])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3190], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[823]),
          ((entity *)IFC4_types[823])->attributes()[0])});
  ((entity *)IFC4_types[461])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3232], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[460]),
                                 ((entity *)IFC4_types[460])->attributes()[2]),
           new inverse_attribute(strings[3233], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[460]),
                                 ((entity *)IFC4_types[460])->attributes()[1]),
           new inverse_attribute(strings[3234], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[460]),
                                 ((entity *)IFC4_types[460])->attributes()[0]),
           new inverse_attribute(
               strings[3235], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[1135]),
               ((entity *)IFC4_types[1135])->attributes()[0])});
  ((entity *)IFC4_types[465])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3236], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[801]),
          ((entity *)IFC4_types[801])->attributes()[0])});
  ((entity *)IFC4_types[481])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3237], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4_types[680]),
          ((entity *)IFC4_types[680])->attributes()[1])});
  ((entity *)IFC4_types[517])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3238], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[811]),
                                 ((entity *)IFC4_types[811])->attributes()[0]),
           new inverse_attribute(
               strings[3239], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[518]),
               ((entity *)IFC4_types[518])->attributes()[2])});
  ((entity *)IFC4_types[518])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3240], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[811]),
          ((entity *)IFC4_types[811])->attributes()[0])});
  ((entity *)IFC4_types[558])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3241], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[563]),
                                 ((entity *)IFC4_types[563])->attributes()[0]),
           new inverse_attribute(strings[3194], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[575]),
                                 ((entity *)IFC4_types[575])->attributes()[1]),
           new inverse_attribute(
               strings[3242], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4_types[575]),
               ((entity *)IFC4_types[575])->attributes()[0])});
  ((entity *)IFC4_types[560])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3243], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4_types[561]),
          ((entity *)IFC4_types[561])->attributes()[2])});
  ((entity *)IFC4_types[562])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3244], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[812]),
                                 ((entity *)IFC4_types[812])->attributes()[0]),
           new inverse_attribute(strings[3191], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[380]),
                                 ((entity *)IFC4_types[380])->attributes()[1]),
           new inverse_attribute(
               strings[2470], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[574]),
               ((entity *)IFC4_types[574])->attributes()[0])});
  ((entity *)IFC4_types[564])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3245], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4_types[565]),
          ((entity *)IFC4_types[565])->attributes()[0])});
  ((entity *)IFC4_types[569])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3246], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4_types[570]),
          ((entity *)IFC4_types[570])->attributes()[2])});
  ((entity *)IFC4_types[577])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3244], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4_types[812]),
          ((entity *)IFC4_types[812])->attributes()[0])});
  ((entity *)IFC4_types[614])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3247], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[829]),
                                 ((entity *)IFC4_types[829])->attributes()[0]),
           new inverse_attribute(strings[3202], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[829]),
                                 ((entity *)IFC4_types[829])->attributes()[1]),
           new inverse_attribute(strings[3248], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[832]),
                                 ((entity *)IFC4_types[832])->attributes()[0]),
           new inverse_attribute(
               strings[3201], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[830]),
               ((entity *)IFC4_types[830])->attributes()[0])});
  ((entity *)IFC4_types[615])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3249], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[798]),
                                 ((entity *)IFC4_types[798])->attributes()[0]),
           new inverse_attribute(strings[3250], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[836]),
                                 ((entity *)IFC4_types[836])->attributes()[1]),
           new inverse_attribute(strings[3251], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[836]),
                                 ((entity *)IFC4_types[836])->attributes()[0]),
           new inverse_attribute(strings[3252], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[826]),
                                 ((entity *)IFC4_types[826])->attributes()[1]),
           new inverse_attribute(strings[3253], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[797]),
                                 ((entity *)IFC4_types[797])->attributes()[0]),
           new inverse_attribute(strings[3254], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[797]),
                                 ((entity *)IFC4_types[797])->attributes()[1]),
           new inverse_attribute(
               strings[3255], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[806]),
               ((entity *)IFC4_types[806])->attributes()[0])});
  ((entity *)IFC4_types[618])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3256], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[710]),
                                 ((entity *)IFC4_types[710])->attributes()[0]),
           new inverse_attribute(
               strings[3257], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[541]),
               ((entity *)IFC4_types[541])->attributes()[0])});
  ((entity *)IFC4_types[625])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3258], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[833]),
          ((entity *)IFC4_types[833])->attributes()[0])});
  ((entity *)IFC4_types[629])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3259], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[630]),
                                 ((entity *)IFC4_types[630])->attributes()[1]),
           new inverse_attribute(strings[3195], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[630]),
                                 ((entity *)IFC4_types[630])->attributes()[0]),
           new inverse_attribute(
               strings[3260], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[648]),
               ((entity *)IFC4_types[648])->attributes()[1])});
  ((entity *)IFC4_types[647])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3261], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[648]),
          ((entity *)IFC4_types[648])->attributes()[0])});
  ((entity *)IFC4_types[652])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3191], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[380]),
                                 ((entity *)IFC4_types[380])->attributes()[1]),
           new inverse_attribute(
               strings[3262], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4_types[650]),
               ((entity *)IFC4_types[650])->attributes()[0])});
  ((entity *)IFC4_types[683])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3263], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[818]),
                                 ((entity *)IFC4_types[818])->attributes()[0]),
           new inverse_attribute(strings[3224], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[817]),
                                 ((entity *)IFC4_types[817])->attributes()[1]),
           new inverse_attribute(
               strings[3216], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4_types[817]),
               ((entity *)IFC4_types[817])->attributes()[0])});
  ((entity *)IFC4_types[708])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3264], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[839]),
                                 ((entity *)IFC4_types[839])->attributes()[0]),
           new inverse_attribute(strings[3265], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[839]),
                                 ((entity *)IFC4_types[839])->attributes()[1]),
           new inverse_attribute(
               strings[3266], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[803]),
               ((entity *)IFC4_types[803])->attributes()[0])});
  ((entity *)IFC4_types[710])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3267], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[804]),
          ((entity *)IFC4_types[804])->attributes()[0])});
  ((entity *)IFC4_types[711])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3268], inverse_attribute::set_type, 1,
                                 -1, ((entity *)IFC4_types[710]),
                                 ((entity *)IFC4_types[710])->attributes()[1]),
           new inverse_attribute(
               strings[3269], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[890]),
               ((entity *)IFC4_types[890])->attributes()[4])});
  ((entity *)IFC4_types[715])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3187], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[380]),
                                 ((entity *)IFC4_types[380])->attributes()[1]),
           new inverse_attribute(
               strings[2470], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[716]),
               ((entity *)IFC4_types[716])->attributes()[0])});
  ((entity *)IFC4_types[726])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3270], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[735]),
                                 ((entity *)IFC4_types[735])->attributes()[0]),
           new inverse_attribute(strings[3271], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[730]),
                                 ((entity *)IFC4_types[730])->attributes()[0]),
           new inverse_attribute(strings[3272], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[730]),
                                 ((entity *)IFC4_types[730])->attributes()[1]),
           new inverse_attribute(strings[3262], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[162]),
                                 ((entity *)IFC4_types[162])->attributes()[1]),
           new inverse_attribute(strings[3273], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[852]),
                                 ((entity *)IFC4_types[852])->attributes()[1]),
           new inverse_attribute(
               strings[3274], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[851]),
               ((entity *)IFC4_types[851])->attributes()[0])});
  ((entity *)IFC4_types[727])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3191], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[380]),
          ((entity *)IFC4_types[380])->attributes()[1])});
  ((entity *)IFC4_types[729])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3252], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[826]),
                                 ((entity *)IFC4_types[826])->attributes()[1]),
           new inverse_attribute(
               strings[3255], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[806]),
               ((entity *)IFC4_types[806])->attributes()[0])});
  ((entity *)IFC4_types[736])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3275], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[1106]),
                                 ((entity *)IFC4_types[1106])->attributes()[1]),
           new inverse_attribute(strings[3201], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[831]),
                                 ((entity *)IFC4_types[831])->attributes()[0]),
           new inverse_attribute(
               strings[3276], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[830]),
               ((entity *)IFC4_types[830])->attributes()[1])});
  ((entity *)IFC4_types[739])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3277], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[831]),
          ((entity *)IFC4_types[831])->attributes()[1])});
  ((entity *)IFC4_types[743])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3278], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[163]),
                                 ((entity *)IFC4_types[163])->attributes()[2]),
           new inverse_attribute(
               strings[3279], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[739]),
               ((entity *)IFC4_types[739])->attributes()[2])});
  ((entity *)IFC4_types[842])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2343], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[842]),
          ((entity *)IFC4_types[842])->attributes()[0])});
  ((entity *)IFC4_types[843])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3280], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[843]),
          ((entity *)IFC4_types[843])->attributes()[0])});
  ((entity *)IFC4_types[846])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3281], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[849]),
                                 ((entity *)IFC4_types[849])->attributes()[1]),
           new inverse_attribute(strings[3282], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[699]),
                                 ((entity *)IFC4_types[699])->attributes()[2]),
           new inverse_attribute(
               strings[3283], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[712]),
               ((entity *)IFC4_types[712])->attributes()[2])});
  ((entity *)IFC4_types[847])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3284], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[846]),
          ((entity *)IFC4_types[846])->attributes()[0])});
  ((entity *)IFC4_types[848])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3285], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[699]),
                                 ((entity *)IFC4_types[699])->attributes()[2]),
           new inverse_attribute(
               strings[3286], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4_types[994]),
               ((entity *)IFC4_types[994])->attributes()[0])});
  ((entity *)IFC4_types[849])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3269], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[890]),
                                 ((entity *)IFC4_types[890])->attributes()[4]),
           new inverse_attribute(
               strings[3287], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[553]),
               ((entity *)IFC4_types[553])->attributes()[0])});
  ((entity *)IFC4_types[850])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3288], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[805]),
          ((entity *)IFC4_types[805])->attributes()[0])});
  ((entity *)IFC4_types[891])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3289], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[890]),
          ((entity *)IFC4_types[890])->attributes()[0])});
  ((entity *)IFC4_types[921])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3225], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[825]),
                                 ((entity *)IFC4_types[825])->attributes()[0]),
           new inverse_attribute(
               strings[3227], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[841]),
               ((entity *)IFC4_types[841])->attributes()[0])});
  ((entity *)IFC4_types[928])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3290], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[823]),
                                 ((entity *)IFC4_types[823])->attributes()[1]),
           new inverse_attribute(strings[3291], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[840]),
                                 ((entity *)IFC4_types[840])->attributes()[1]),
           new inverse_attribute(
               strings[3292], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[838]),
               ((entity *)IFC4_types[838])->attributes()[1])});
  ((entity *)IFC4_types[952])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3293], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[819]),
          ((entity *)IFC4_types[819])->attributes()[1])});
  ((entity *)IFC4_types[955])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3294], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4_types[820]),
          ((entity *)IFC4_types[820])->attributes()[1])});
  ((entity *)IFC4_types[964])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3295], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[819]),
          ((entity *)IFC4_types[819])->attributes()[0])});
  ((entity *)IFC4_types[969])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3296], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[985]),
                                 ((entity *)IFC4_types[985])->attributes()[1]),
           new inverse_attribute(
               strings[3297], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[954]),
               ((entity *)IFC4_types[954])->attributes()[2])});
  ((entity *)IFC4_types[979])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3298], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[820]),
          ((entity *)IFC4_types[820])->attributes()[0])});
  ((entity *)IFC4_types[985])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3299], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[954]),
          ((entity *)IFC4_types[954])->attributes()[3])});
  ((entity *)IFC4_types[1018])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3300], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4_types[1066]),
                                 ((entity *)IFC4_types[1066])->attributes()[0]),
           new inverse_attribute(
               strings[3301], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[1017]),
               ((entity *)IFC4_types[1017])->attributes()[0])});
  ((entity *)IFC4_types[1026])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3302], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[840]),
          ((entity *)IFC4_types[840])->attributes()[0])});
  ((entity *)IFC4_types[1051])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[3303], inverse_attribute::set_type, 0,
                                 1, ((entity *)IFC4_types[479]),
                                 ((entity *)IFC4_types[479])->attributes()[0]),
           new inverse_attribute(
               strings[3304], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4_types[483]),
               ((entity *)IFC4_types[483])->attributes()[0])});
  ((entity *)IFC4_types[1081])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3187], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4_types[380]),
          ((entity *)IFC4_types[380])->attributes()[1])});
  ((entity *)IFC4_types[1106])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3305], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4_types[832]),
          ((entity *)IFC4_types[832])->attributes()[1])});
  ((entity *)IFC4_types[1107])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3266], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[803]),
          ((entity *)IFC4_types[803])->attributes()[0])});
  ((entity *)IFC4_types[1108])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3267], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[804]),
          ((entity *)IFC4_types[804])->attributes()[0])});
  ((entity *)IFC4_types[1109])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3288], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4_types[805]),
          ((entity *)IFC4_types[805])->attributes()[0])});
  ((entity *)IFC4_types[201])
      ->set_subtypes({((entity *)IFC4_types[2]), ((entity *)IFC4_types[216]),
                      ((entity *)IFC4_types[218]), ((entity *)IFC4_types[641]),
                      ((entity *)IFC4_types[645]), ((entity *)IFC4_types[724]),
                      ((entity *)IFC4_types[1163]),
                      ((entity *)IFC4_types[1165])});
  ((entity *)IFC4_types[614])
      ->set_subtypes({((entity *)IFC4_types[6]), ((entity *)IFC4_types[201]),
                      ((entity *)IFC4_types[465]), ((entity *)IFC4_types[708]),
                      ((entity *)IFC4_types[710]),
                      ((entity *)IFC4_types[850])});
  ((entity *)IFC4_types[276])
      ->set_subtypes({((entity *)IFC4_types[9]), ((entity *)IFC4_types[26]),
                      ((entity *)IFC4_types[202]), ((entity *)IFC4_types[419]),
                      ((entity *)IFC4_types[746]), ((entity *)IFC4_types[883]),
                      ((entity *)IFC4_types[1111])});
  ((entity *)IFC4_types[277])
      ->set_subtypes({((entity *)IFC4_types[10]), ((entity *)IFC4_types[27]),
                      ((entity *)IFC4_types[203]), ((entity *)IFC4_types[420]),
                      ((entity *)IFC4_types[747]), ((entity *)IFC4_types[884]),
                      ((entity *)IFC4_types[1112])});
  ((entity *)IFC4_types[551])
      ->set_subtypes({((entity *)IFC4_types[14]), ((entity *)IFC4_types[391])});
  ((entity *)IFC4_types[14])->set_subtypes({((entity *)IFC4_types[15])});
  ((entity *)IFC4_types[390])->set_subtypes({((entity *)IFC4_types[16])});
  ((entity *)IFC4_types[431])
      ->set_subtypes({((entity *)IFC4_types[17]), ((entity *)IFC4_types[50]),
                      ((entity *)IFC4_types[158]), ((entity *)IFC4_types[321]),
                      ((entity *)IFC4_types[410]), ((entity *)IFC4_types[510]),
                      ((entity *)IFC4_types[524]), ((entity *)IFC4_types[583]),
                      ((entity *)IFC4_types[633]), ((entity *)IFC4_types[871]),
                      ((entity *)IFC4_types[923]), ((entity *)IFC4_types[941]),
                      ((entity *)IFC4_types[1148])});
  ((entity *)IFC4_types[414])
      ->set_subtypes({((entity *)IFC4_types[18]), ((entity *)IFC4_types[250]),
                      ((entity *)IFC4_types[328]), ((entity *)IFC4_types[341]),
                      ((entity *)IFC4_types[422]), ((entity *)IFC4_types[745]),
                      ((entity *)IFC4_types[1023]),
                      ((entity *)IFC4_types[1122])});
  ((entity *)IFC4_types[415])
      ->set_subtypes({((entity *)IFC4_types[19]), ((entity *)IFC4_types[251]),
                      ((entity *)IFC4_types[329]), ((entity *)IFC4_types[342]),
                      ((entity *)IFC4_types[423]), ((entity *)IFC4_types[749]),
                      ((entity *)IFC4_types[1024]),
                      ((entity *)IFC4_types[1123])});
  ((entity *)IFC4_types[432])
      ->set_subtypes({((entity *)IFC4_types[21]), ((entity *)IFC4_types[51]),
                      ((entity *)IFC4_types[159]), ((entity *)IFC4_types[322]),
                      ((entity *)IFC4_types[411]), ((entity *)IFC4_types[511]),
                      ((entity *)IFC4_types[525]), ((entity *)IFC4_types[584]),
                      ((entity *)IFC4_types[634]), ((entity *)IFC4_types[872]),
                      ((entity *)IFC4_types[924]), ((entity *)IFC4_types[942]),
                      ((entity *)IFC4_types[1149])});
  ((entity *)IFC4_types[357])
      ->set_subtypes(
          {((entity *)IFC4_types[23]),   ((entity *)IFC4_types[66]),
           ((entity *)IFC4_types[103]),  ((entity *)IFC4_types[130]),
           ((entity *)IFC4_types[146]),  ((entity *)IFC4_types[173]),
           ((entity *)IFC4_types[207]),  ((entity *)IFC4_types[210]),
           ((entity *)IFC4_types[334]),  ((entity *)IFC4_types[337]),
           ((entity *)IFC4_types[360]),  ((entity *)IFC4_types[363]),
           ((entity *)IFC4_types[366]),  ((entity *)IFC4_types[468]),
           ((entity *)IFC4_types[473]),  ((entity *)IFC4_types[606]),
           ((entity *)IFC4_types[911]),  ((entity *)IFC4_types[1089]),
           ((entity *)IFC4_types[1103]), ((entity *)IFC4_types[1114])});
  ((entity *)IFC4_types[358])
      ->set_subtypes(
          {((entity *)IFC4_types[24]),   ((entity *)IFC4_types[67]),
           ((entity *)IFC4_types[104]),  ((entity *)IFC4_types[131]),
           ((entity *)IFC4_types[147]),  ((entity *)IFC4_types[174]),
           ((entity *)IFC4_types[208]),  ((entity *)IFC4_types[211]),
           ((entity *)IFC4_types[335]),  ((entity *)IFC4_types[338]),
           ((entity *)IFC4_types[361]),  ((entity *)IFC4_types[364]),
           ((entity *)IFC4_types[367]),  ((entity *)IFC4_types[469]),
           ((entity *)IFC4_types[474]),  ((entity *)IFC4_types[607]),
           ((entity *)IFC4_types[912]),  ((entity *)IFC4_types[1090]),
           ((entity *)IFC4_types[1104]), ((entity *)IFC4_types[1115])});
  ((entity *)IFC4_types[710])
      ->set_subtypes({((entity *)IFC4_types[33]), ((entity *)IFC4_types[345]),
                      ((entity *)IFC4_types[460]), ((entity *)IFC4_types[683]),
                      ((entity *)IFC4_types[751]), ((entity *)IFC4_types[928]),
                      ((entity *)IFC4_types[952]),
                      ((entity *)IFC4_types[964])});
  ((entity *)IFC4_types[454])
      ->set_subtypes(
          {((entity *)IFC4_types[34]),   ((entity *)IFC4_types[73]),
           ((entity *)IFC4_types[82]),   ((entity *)IFC4_types[120]),
           ((entity *)IFC4_types[123]),  ((entity *)IFC4_types[167]),
           ((entity *)IFC4_types[228]),  ((entity *)IFC4_types[237]),
           ((entity *)IFC4_types[267]),  ((entity *)IFC4_types[387]),
           ((entity *)IFC4_types[404]),  ((entity *)IFC4_types[405]),
           ((entity *)IFC4_types[456]),  ((entity *)IFC4_types[466]),
           ((entity *)IFC4_types[528]),  ((entity *)IFC4_types[665]),
           ((entity *)IFC4_types[667]),  ((entity *)IFC4_types[675]),
           ((entity *)IFC4_types[877]),  ((entity *)IFC4_types[895]),
           ((entity *)IFC4_types[915]),  ((entity *)IFC4_types[1001]),
           ((entity *)IFC4_types[1052]), ((entity *)IFC4_types[1058]),
           ((entity *)IFC4_types[1126])});
  ((entity *)IFC4_types[853])
      ->set_subtypes({((entity *)IFC4_types[39]), ((entity *)IFC4_types[232]),
                      ((entity *)IFC4_types[288]), ((entity *)IFC4_types[380]),
                      ((entity *)IFC4_types[575]), ((entity *)IFC4_types[630]),
                      ((entity *)IFC4_types[730]), ((entity *)IFC4_types[851]),
                      ((entity *)IFC4_types[852])});
  ((entity *)IFC4_types[715])
      ->set_subtypes({((entity *)IFC4_types[40]), ((entity *)IFC4_types[41]),
                      ((entity *)IFC4_types[168]), ((entity *)IFC4_types[260]),
                      ((entity *)IFC4_types[637])});
  ((entity *)IFC4_types[40])->set_subtypes({((entity *)IFC4_types[42])});
  ((entity *)IFC4_types[465])
      ->set_subtypes({((entity *)IFC4_types[48]), ((entity *)IFC4_types[493]),
                      ((entity *)IFC4_types[969]), ((entity *)IFC4_types[985]),
                      ((entity *)IFC4_types[1026])});
  ((entity *)IFC4_types[637])
      ->set_subtypes({((entity *)IFC4_types[49]), ((entity *)IFC4_types[231]),
                      ((entity *)IFC4_types[138]), ((entity *)IFC4_types[356]),
                      ((entity *)IFC4_types[498]), ((entity *)IFC4_types[545]),
                      ((entity *)IFC4_types[777]), ((entity *)IFC4_types[1102]),
                      ((entity *)IFC4_types[1097]),
                      ((entity *)IFC4_types[1120]),
                      ((entity *)IFC4_types[1172])});
  ((entity *)IFC4_types[665])
      ->set_subtypes({((entity *)IFC4_types[53]), ((entity *)IFC4_types[55]),
                      ((entity *)IFC4_types[56])});
  ((entity *)IFC4_types[80])
      ->set_subtypes({((entity *)IFC4_types[85]), ((entity *)IFC4_types[165]),
                      ((entity *)IFC4_types[480]), ((entity *)IFC4_types[681]),
                      ((entity *)IFC4_types[1099])});
  ((entity *)IFC4_types[85])->set_subtypes({((entity *)IFC4_types[87])});
  ((entity *)IFC4_types[81])
      ->set_subtypes({((entity *)IFC4_types[88]), ((entity *)IFC4_types[238]),
                      ((entity *)IFC4_types[239]),
                      ((entity *)IFC4_types[779])});
  ((entity *)IFC4_types[88])->set_subtypes({((entity *)IFC4_types[90])});
  ((entity *)IFC4_types[92])
      ->set_subtypes({((entity *)IFC4_types[57]),  ((entity *)IFC4_types[96]),
                      ((entity *)IFC4_types[133]), ((entity *)IFC4_types[154]),
                      ((entity *)IFC4_types[222]), ((entity *)IFC4_types[233]),
                      ((entity *)IFC4_types[292]), ((entity *)IFC4_types[438]),
                      ((entity *)IFC4_types[586]), ((entity *)IFC4_types[654]),
                      ((entity *)IFC4_types[671]), ((entity *)IFC4_types[763]),
                      ((entity *)IFC4_types[766]), ((entity *)IFC4_types[767]),
                      ((entity *)IFC4_types[862]), ((entity *)IFC4_types[887]),
                      ((entity *)IFC4_types[905]), ((entity *)IFC4_types[944]),
                      ((entity *)IFC4_types[945]), ((entity *)IFC4_types[1140]),
                      ((entity *)IFC4_types[1151])});
  ((entity *)IFC4_types[57])->set_subtypes({((entity *)IFC4_types[58])});
  ((entity *)IFC4_types[99])
      ->set_subtypes({((entity *)IFC4_types[59]),  ((entity *)IFC4_types[97]),
                      ((entity *)IFC4_types[134]), ((entity *)IFC4_types[156]),
                      ((entity *)IFC4_types[223]), ((entity *)IFC4_types[234]),
                      ((entity *)IFC4_types[301]), ((entity *)IFC4_types[439]),
                      ((entity *)IFC4_types[588]), ((entity *)IFC4_types[656]),
                      ((entity *)IFC4_types[673]), ((entity *)IFC4_types[764]),
                      ((entity *)IFC4_types[768]), ((entity *)IFC4_types[770]),
                      ((entity *)IFC4_types[863]), ((entity *)IFC4_types[888]),
                      ((entity *)IFC4_types[908]), ((entity *)IFC4_types[946]),
                      ((entity *)IFC4_types[948]), ((entity *)IFC4_types[1143]),
                      ((entity *)IFC4_types[1160])});
  ((entity *)IFC4_types[1018])
      ->set_subtypes({((entity *)IFC4_types[64]), ((entity *)IFC4_types[478]),
                      ((entity *)IFC4_types[664])});
  ((entity *)IFC4_types[228])
      ->set_subtypes({((entity *)IFC4_types[65]), ((entity *)IFC4_types[778]),
                      ((entity *)IFC4_types[859]), ((entity *)IFC4_types[860]),
                      ((entity *)IFC4_types[939])});
  ((entity *)IFC4_types[73])->set_subtypes({((entity *)IFC4_types[70])});
  ((entity *)IFC4_types[166])->set_subtypes({((entity *)IFC4_types[75])});
  ((entity *)IFC4_types[74])
      ->set_subtypes({((entity *)IFC4_types[76]), ((entity *)IFC4_types[77]),
                      ((entity *)IFC4_types[78])});
  ((entity *)IFC4_types[78])->set_subtypes({((entity *)IFC4_types[79])});
  ((entity *)IFC4_types[237])
      ->set_subtypes({((entity *)IFC4_types[80]), ((entity *)IFC4_types[176]),
                      ((entity *)IFC4_types[534]), ((entity *)IFC4_types[623]),
                      ((entity *)IFC4_types[624]), ((entity *)IFC4_types[640]),
                      ((entity *)IFC4_types[1002])});
  ((entity *)IFC4_types[1001])
      ->set_subtypes({((entity *)IFC4_types[81]), ((entity *)IFC4_types[346]),
                      ((entity *)IFC4_types[1022])});
  ((entity *)IFC4_types[466])
      ->set_subtypes({((entity *)IFC4_types[84]), ((entity *)IFC4_types[679])});
  ((entity *)IFC4_types[930])
      ->set_subtypes({((entity *)IFC4_types[91]), ((entity *)IFC4_types[100]),
                      ((entity *)IFC4_types[901]),
                      ((entity *)IFC4_types[921])});
  ((entity *)IFC4_types[345])
      ->set_subtypes({((entity *)IFC4_types[92]), ((entity *)IFC4_types[139]),
                      ((entity *)IFC4_types[278]), ((entity *)IFC4_types[347]),
                      ((entity *)IFC4_types[350]), ((entity *)IFC4_types[400]),
                      ((entity *)IFC4_types[443]), ((entity *)IFC4_types[448]),
                      ((entity *)IFC4_types[1094]),
                      ((entity *)IFC4_types[1134])});
  ((entity *)IFC4_types[350])
      ->set_subtypes({((entity *)IFC4_types[93]), ((entity *)IFC4_types[269]),
                      ((entity *)IFC4_types[397]), ((entity *)IFC4_types[580]),
                      ((entity *)IFC4_types[792]),
                      ((entity *)IFC4_types[1131])});
  ((entity *)IFC4_types[351])
      ->set_subtypes({((entity *)IFC4_types[94]), ((entity *)IFC4_types[270]),
                      ((entity *)IFC4_types[398]), ((entity *)IFC4_types[581]),
                      ((entity *)IFC4_types[793]),
                      ((entity *)IFC4_types[1132])});
  ((entity *)IFC4_types[354])
      ->set_subtypes({((entity *)IFC4_types[99]), ((entity *)IFC4_types[140]),
                      ((entity *)IFC4_types[279]), ((entity *)IFC4_types[348]),
                      ((entity *)IFC4_types[351]), ((entity *)IFC4_types[444]),
                      ((entity *)IFC4_types[449]),
                      ((entity *)IFC4_types[1095])});
  ((entity *)IFC4_types[1026])
      ->set_subtypes({((entity *)IFC4_types[101]), ((entity *)IFC4_types[284]),
                      ((entity *)IFC4_types[954]),
                      ((entity *)IFC4_types[1171])});
  ((entity *)IFC4_types[417])
      ->set_subtypes({((entity *)IFC4_types[106]), ((entity *)IFC4_types[112]),
                      ((entity *)IFC4_types[307]), ((entity *)IFC4_types[500]),
                      ((entity *)IFC4_types[658])});
  ((entity *)IFC4_types[418])
      ->set_subtypes({((entity *)IFC4_types[107]), ((entity *)IFC4_types[113]),
                      ((entity *)IFC4_types[308]), ((entity *)IFC4_types[501]),
                      ((entity *)IFC4_types[659])});
  ((entity *)IFC4_types[427])
      ->set_subtypes({((entity *)IFC4_types[109]), ((entity *)IFC4_types[115]),
                      ((entity *)IFC4_types[310]),
                      ((entity *)IFC4_types[661])});
  ((entity *)IFC4_types[428])
      ->set_subtypes({((entity *)IFC4_types[110]), ((entity *)IFC4_types[116]),
                      ((entity *)IFC4_types[311]),
                      ((entity *)IFC4_types[662])});
  ((entity *)IFC4_types[675])
      ->set_subtypes({((entity *)IFC4_types[119]), ((entity *)IFC4_types[676]),
                      ((entity *)IFC4_types[677])});
  ((entity *)IFC4_types[120])
      ->set_subtypes(
          {((entity *)IFC4_types[121]), ((entity *)IFC4_types[122])});
  ((entity *)IFC4_types[123])
      ->set_subtypes(
          {((entity *)IFC4_types[124]), ((entity *)IFC4_types[126])});
  ((entity *)IFC4_types[124])->set_subtypes({((entity *)IFC4_types[125])});
  ((entity *)IFC4_types[126])->set_subtypes({((entity *)IFC4_types[127])});
  ((entity *)IFC4_types[41])->set_subtypes({((entity *)IFC4_types[128])});
  ((entity *)IFC4_types[176])
      ->set_subtypes(
          {((entity *)IFC4_types[136]), ((entity *)IFC4_types[355])});
  ((entity *)IFC4_types[138])->set_subtypes({((entity *)IFC4_types[137])});
  ((entity *)IFC4_types[375])
      ->set_subtypes({((entity *)IFC4_types[141]), ((entity *)IFC4_types[287]),
                      ((entity *)IFC4_types[517])});
  ((entity *)IFC4_types[379])
      ->set_subtypes({((entity *)IFC4_types[142]), ((entity *)IFC4_types[289]),
                      ((entity *)IFC4_types[376]), ((entity *)IFC4_types[377]),
                      ((entity *)IFC4_types[378]),
                      ((entity *)IFC4_types[518])});
  ((entity *)IFC4_types[177])
      ->set_subtypes(
          {((entity *)IFC4_types[145]), ((entity *)IFC4_types[628])});
  ((entity *)IFC4_types[153])->set_subtypes({((entity *)IFC4_types[151])});
  ((entity *)IFC4_types[698])
      ->set_subtypes(
          {((entity *)IFC4_types[152]), ((entity *)IFC4_types[153]),
           ((entity *)IFC4_types[245]), ((entity *)IFC4_types[246]),
           ((entity *)IFC4_types[247]), ((entity *)IFC4_types[479]),
           ((entity *)IFC4_types[692]), ((entity *)IFC4_types[1013]),
           ((entity *)IFC4_types[1014]), ((entity *)IFC4_types[1016]),
           ((entity *)IFC4_types[1017]), ((entity *)IFC4_types[1018]),
           ((entity *)IFC4_types[1063]), ((entity *)IFC4_types[1064]),
           ((entity *)IFC4_types[1066]), ((entity *)IFC4_types[1069]),
           ((entity *)IFC4_types[1070])});
  ((entity *)IFC4_types[154])->set_subtypes({((entity *)IFC4_types[155])});
  ((entity *)IFC4_types[726])
      ->set_subtypes(
          {((entity *)IFC4_types[162]), ((entity *)IFC4_types[896])});
  ((entity *)IFC4_types[743])
      ->set_subtypes(
          {((entity *)IFC4_types[163]), ((entity *)IFC4_types[897])});
  ((entity *)IFC4_types[165])->set_subtypes({((entity *)IFC4_types[166])});
  ((entity *)IFC4_types[425])
      ->set_subtypes({((entity *)IFC4_types[170]), ((entity *)IFC4_types[394]),
                      ((entity *)IFC4_types[752])});
  ((entity *)IFC4_types[426])
      ->set_subtypes({((entity *)IFC4_types[171]), ((entity *)IFC4_types[395]),
                      ((entity *)IFC4_types[753])});
  ((entity *)IFC4_types[1085])
      ->set_subtypes({((entity *)IFC4_types[177]), ((entity *)IFC4_types[318]),
                      ((entity *)IFC4_types[386]), ((entity *)IFC4_types[388]),
                      ((entity *)IFC4_types[544]), ((entity *)IFC4_types[639]),
                      ((entity *)IFC4_types[1128])});
  ((entity *)IFC4_types[179])
      ->set_subtypes({((entity *)IFC4_types[178]), ((entity *)IFC4_types[181]),
                      ((entity *)IFC4_types[182]),
                      ((entity *)IFC4_types[184])});
  ((entity *)IFC4_types[181])->set_subtypes({((entity *)IFC4_types[180])});
  ((entity *)IFC4_types[196])
      ->set_subtypes({((entity *)IFC4_types[187]), ((entity *)IFC4_types[190]),
                      ((entity *)IFC4_types[193]), ((entity *)IFC4_types[225]),
                      ((entity *)IFC4_types[506]),
                      ((entity *)IFC4_types[997])});
  ((entity *)IFC4_types[197])
      ->set_subtypes({((entity *)IFC4_types[188]), ((entity *)IFC4_types[191]),
                      ((entity *)IFC4_types[194]), ((entity *)IFC4_types[226]),
                      ((entity *)IFC4_types[507]),
                      ((entity *)IFC4_types[998])});
  ((entity *)IFC4_types[850])->set_subtypes({((entity *)IFC4_types[196])});
  ((entity *)IFC4_types[1109])->set_subtypes({((entity *)IFC4_types[197])});
  ((entity *)IFC4_types[615])
      ->set_subtypes({((entity *)IFC4_types[198]), ((entity *)IFC4_types[614]),
                      ((entity *)IFC4_types[1106])});
  ((entity *)IFC4_types[609])
      ->set_subtypes({((entity *)IFC4_types[200]), ((entity *)IFC4_types[205]),
                      ((entity *)IFC4_types[902])});
  ((entity *)IFC4_types[205])->set_subtypes({((entity *)IFC4_types[206])});
  ((entity *)IFC4_types[36])->set_subtypes({((entity *)IFC4_types[220])});
  ((entity *)IFC4_types[915])
      ->set_subtypes({((entity *)IFC4_types[230]), ((entity *)IFC4_types[551]),
                      ((entity *)IFC4_types[1019]),
                      ((entity *)IFC4_types[1020])});
  ((entity *)IFC4_types[701])
      ->set_subtypes({((entity *)IFC4_types[244]), ((entity *)IFC4_types[403]),
                      ((entity *)IFC4_types[1011]),
                      ((entity *)IFC4_types[1061])});
  ((entity *)IFC4_types[346])
      ->set_subtypes({((entity *)IFC4_types[249]), ((entity *)IFC4_types[669]),
                      ((entity *)IFC4_types[940]),
                      ((entity *)IFC4_types[1087])});
  ((entity *)IFC4_types[280])
      ->set_subtypes({((entity *)IFC4_types[272]), ((entity *)IFC4_types[357]),
                      ((entity *)IFC4_types[414]), ((entity *)IFC4_types[417]),
                      ((entity *)IFC4_types[425]), ((entity *)IFC4_types[427]),
                      ((entity *)IFC4_types[429]), ((entity *)IFC4_types[431]),
                      ((entity *)IFC4_types[433])});
  ((entity *)IFC4_types[281])
      ->set_subtypes({((entity *)IFC4_types[273]), ((entity *)IFC4_types[358]),
                      ((entity *)IFC4_types[415]), ((entity *)IFC4_types[418]),
                      ((entity *)IFC4_types[426]), ((entity *)IFC4_types[428]),
                      ((entity *)IFC4_types[430]), ((entity *)IFC4_types[432]),
                      ((entity *)IFC4_types[434])});
  ((entity *)IFC4_types[284])->set_subtypes({((entity *)IFC4_types[275])});
  ((entity *)IFC4_types[278])
      ->set_subtypes(
          {((entity *)IFC4_types[276]), ((entity *)IFC4_types[280])});
  ((entity *)IFC4_types[279])
      ->set_subtypes(
          {((entity *)IFC4_types[277]), ((entity *)IFC4_types[281])});
  ((entity *)IFC4_types[683])->set_subtypes({((entity *)IFC4_types[282])});
  ((entity *)IFC4_types[694])
      ->set_subtypes({((entity *)IFC4_types[293]), ((entity *)IFC4_types[296]),
                      ((entity *)IFC4_types[644]), ((entity *)IFC4_types[786]),
                      ((entity *)IFC4_types[1152]),
                      ((entity *)IFC4_types[1155])});
  ((entity *)IFC4_types[292])->set_subtypes({((entity *)IFC4_types[297])});
  ((entity *)IFC4_types[1108])
      ->set_subtypes({((entity *)IFC4_types[298]), ((entity *)IFC4_types[354]),
                      ((entity *)IFC4_types[929]),
                      ((entity *)IFC4_types[1157])});
  ((entity *)IFC4_types[690])->set_subtypes({((entity *)IFC4_types[305])});
  ((entity *)IFC4_types[691])->set_subtypes({((entity *)IFC4_types[306])});
  ((entity *)IFC4_types[433])
      ->set_subtypes({((entity *)IFC4_types[313]), ((entity *)IFC4_types[407]),
                      ((entity *)IFC4_types[488])});
  ((entity *)IFC4_types[434])
      ->set_subtypes({((entity *)IFC4_types[314]), ((entity *)IFC4_types[408]),
                      ((entity *)IFC4_types[489])});
  ((entity *)IFC4_types[318])
      ->set_subtypes({((entity *)IFC4_types[319]), ((entity *)IFC4_types[631]),
                      ((entity *)IFC4_types[1000])});
  ((entity *)IFC4_types[544])
      ->set_subtypes({((entity *)IFC4_types[320]), ((entity *)IFC4_types[682]),
                      ((entity *)IFC4_types[1129])});
  ((entity *)IFC4_types[429])
      ->set_subtypes(
          {((entity *)IFC4_types[331]), ((entity *)IFC4_types[1033])});
  ((entity *)IFC4_types[430])
      ->set_subtypes(
          {((entity *)IFC4_types[332]), ((entity *)IFC4_types[1034])});
  ((entity *)IFC4_types[758])->set_subtypes({((entity *)IFC4_types[353])});
  ((entity *)IFC4_types[708])
      ->set_subtypes({((entity *)IFC4_types[369]), ((entity *)IFC4_types[705]),
                      ((entity *)IFC4_types[1036])});
  ((entity *)IFC4_types[874])
      ->set_subtypes({((entity *)IFC4_types[370]), ((entity *)IFC4_types[509]),
                      ((entity *)IFC4_types[856]), ((entity *)IFC4_types[1038]),
                      ((entity *)IFC4_types[1170])});
  ((entity *)IFC4_types[1107])
      ->set_subtypes({((entity *)IFC4_types[372]), ((entity *)IFC4_types[706]),
                      ((entity *)IFC4_types[1040])});
  ((entity *)IFC4_types[727])
      ->set_subtypes({((entity *)IFC4_types[374]), ((entity *)IFC4_types[693]),
                      ((entity *)IFC4_types[726]),
                      ((entity *)IFC4_types[732])});
  ((entity *)IFC4_types[383])->set_subtypes({((entity *)IFC4_types[381])});
  ((entity *)IFC4_types[928])
      ->set_subtypes({((entity *)IFC4_types[383]), ((entity *)IFC4_types[930]),
                      ((entity *)IFC4_types[932])});
  ((entity *)IFC4_types[1019])
      ->set_subtypes({((entity *)IFC4_types[384]), ((entity *)IFC4_types[413]),
                      ((entity *)IFC4_types[857]),
                      ((entity *)IFC4_types[1003])});
  ((entity *)IFC4_types[384])->set_subtypes({((entity *)IFC4_types[385])});
  ((entity *)IFC4_types[388])->set_subtypes({((entity *)IFC4_types[389])});
  ((entity *)IFC4_types[386])->set_subtypes({((entity *)IFC4_types[390])});
  ((entity *)IFC4_types[391])->set_subtypes({((entity *)IFC4_types[392])});
  ((entity *)IFC4_types[956])
      ->set_subtypes(
          {((entity *)IFC4_types[393]), ((entity *)IFC4_types[910])});
  ((entity *)IFC4_types[400])
      ->set_subtypes({((entity *)IFC4_types[401]), ((entity *)IFC4_types[402]),
                      ((entity *)IFC4_types[1004])});
  ((entity *)IFC4_types[443])
      ->set_subtypes(
          {((entity *)IFC4_types[445]), ((entity *)IFC4_types[1027])});
  ((entity *)IFC4_types[444])
      ->set_subtypes(
          {((entity *)IFC4_types[446]), ((entity *)IFC4_types[1028])});
  ((entity *)IFC4_types[456])->set_subtypes({((entity *)IFC4_types[451])});
  ((entity *)IFC4_types[847])->set_subtypes({((entity *)IFC4_types[453])});
  ((entity *)IFC4_types[848])
      ->set_subtypes({((entity *)IFC4_types[454]), ((entity *)IFC4_types[553]),
                      ((entity *)IFC4_types[994]),
                      ((entity *)IFC4_types[1085])});
  ((entity *)IFC4_types[453])->set_subtypes({((entity *)IFC4_types[455])});
  ((entity *)IFC4_types[618])
      ->set_subtypes(
          {((entity *)IFC4_types[462]), ((entity *)IFC4_types[541])});
  ((entity *)IFC4_types[1052])
      ->set_subtypes(
          {((entity *)IFC4_types[481]), ((entity *)IFC4_types[1051])});
  ((entity *)IFC4_types[481])->set_subtypes({((entity *)IFC4_types[482])});
  ((entity *)IFC4_types[1066])
      ->set_subtypes({((entity *)IFC4_types[483]), ((entity *)IFC4_types[1067]),
                      ((entity *)IFC4_types[1068])});
  ((entity *)IFC4_types[483])->set_subtypes({((entity *)IFC4_types[484])});
  ((entity *)IFC4_types[1002])
      ->set_subtypes(
          {((entity *)IFC4_types[492]), ((entity *)IFC4_types[875])});
  ((entity *)IFC4_types[1081])
      ->set_subtypes(
          {((entity *)IFC4_types[496]), ((entity *)IFC4_types[784])});
  ((entity *)IFC4_types[528])
      ->set_subtypes({((entity *)IFC4_types[529]), ((entity *)IFC4_types[530]),
                      ((entity *)IFC4_types[531]),
                      ((entity *)IFC4_types[532])});
  ((entity *)IFC4_types[532])->set_subtypes({((entity *)IFC4_types[533])});
  ((entity *)IFC4_types[213])->set_subtypes({((entity *)IFC4_types[552])});
  ((entity *)IFC4_types[562])
      ->set_subtypes({((entity *)IFC4_types[558]), ((entity *)IFC4_types[560]),
                      ((entity *)IFC4_types[561]), ((entity *)IFC4_types[564]),
                      ((entity *)IFC4_types[565]), ((entity *)IFC4_types[569]),
                      ((entity *)IFC4_types[570])});
  ((entity *)IFC4_types[712])
      ->set_subtypes(
          {((entity *)IFC4_types[563]), ((entity *)IFC4_types[711])});
  ((entity *)IFC4_types[577])
      ->set_subtypes(
          {((entity *)IFC4_types[566]), ((entity *)IFC4_types[571])});
  ((entity *)IFC4_types[564])->set_subtypes({((entity *)IFC4_types[567])});
  ((entity *)IFC4_types[571])->set_subtypes({((entity *)IFC4_types[572])});
  ((entity *)IFC4_types[569])->set_subtypes({((entity *)IFC4_types[573])});
  ((entity *)IFC4_types[374])
      ->set_subtypes(
          {((entity *)IFC4_types[574]), ((entity *)IFC4_types[716])});
  ((entity *)IFC4_types[586])->set_subtypes({((entity *)IFC4_types[587])});
  ((entity *)IFC4_types[185])
      ->set_subtypes(
          {((entity *)IFC4_types[590]), ((entity *)IFC4_types[616])});
  ((entity *)IFC4_types[260])->set_subtypes({((entity *)IFC4_types[592])});
  ((entity *)IFC4_types[865])
      ->set_subtypes({((entity *)IFC4_types[615]), ((entity *)IFC4_types[729]),
                      ((entity *)IFC4_types[813])});
  ((entity *)IFC4_types[6])->set_subtypes({((entity *)IFC4_types[621])});
  ((entity *)IFC4_types[402])
      ->set_subtypes(
          {((entity *)IFC4_types[625]), ((entity *)IFC4_types[1136])});
  ((entity *)IFC4_types[625])->set_subtypes({((entity *)IFC4_types[627])});
  ((entity *)IFC4_types[75])->set_subtypes({((entity *)IFC4_types[632])});
  ((entity *)IFC4_types[652])
      ->set_subtypes(
          {((entity *)IFC4_types[650]), ((entity *)IFC4_types[653])});
  ((entity *)IFC4_types[667])->set_subtypes({((entity *)IFC4_types[666])});
  ((entity *)IFC4_types[671])->set_subtypes({((entity *)IFC4_types[672])});
  ((entity *)IFC4_types[1051])
      ->set_subtypes(
          {((entity *)IFC4_types[680]), ((entity *)IFC4_types[1098])});
  ((entity *)IFC4_types[12])
      ->set_subtypes(
          {((entity *)IFC4_types[688]), ((entity *)IFC4_types[1042])});
  ((entity *)IFC4_types[692])
      ->set_subtypes({((entity *)IFC4_types[690]), ((entity *)IFC4_types[691]),
                      ((entity *)IFC4_types[695])});
  ((entity *)IFC4_types[736])
      ->set_subtypes({((entity *)IFC4_types[694]), ((entity *)IFC4_types[735]),
                      ((entity *)IFC4_types[758])});
  ((entity *)IFC4_types[699])->set_subtypes({((entity *)IFC4_types[700])});
  ((entity *)IFC4_types[198])
      ->set_subtypes(
          {((entity *)IFC4_types[718]), ((entity *)IFC4_types[723])});
  ((entity *)IFC4_types[214])->set_subtypes({((entity *)IFC4_types[719])});
  ((entity *)IFC4_types[401])->set_subtypes({((entity *)IFC4_types[721])});
  ((entity *)IFC4_types[896])
      ->set_subtypes({((entity *)IFC4_types[728]), ((entity *)IFC4_types[731]),
                      ((entity *)IFC4_types[733]), ((entity *)IFC4_types[734]),
                      ((entity *)IFC4_types[741]),
                      ((entity *)IFC4_types[742])});
  ((entity *)IFC4_types[729])
      ->set_subtypes(
          {((entity *)IFC4_types[736]), ((entity *)IFC4_types[744])});
  ((entity *)IFC4_types[744])
      ->set_subtypes(
          {((entity *)IFC4_types[739]), ((entity *)IFC4_types[743])});
  ((entity *)IFC4_types[653])
      ->set_subtypes({((entity *)IFC4_types[755]), ((entity *)IFC4_types[756]),
                      ((entity *)IFC4_types[757]), ((entity *)IFC4_types[759]),
                      ((entity *)IFC4_types[760]),
                      ((entity *)IFC4_types[761])});
  ((entity *)IFC4_types[87])->set_subtypes({((entity *)IFC4_types[773])});
  ((entity *)IFC4_types[90])->set_subtypes({((entity *)IFC4_types[774])});
  ((entity *)IFC4_types[777])
      ->set_subtypes(
          {((entity *)IFC4_types[776]), ((entity *)IFC4_types[870])});
  ((entity *)IFC4_types[693])
      ->set_subtypes({((entity *)IFC4_types[785]), ((entity *)IFC4_types[879]),
                      ((entity *)IFC4_types[880])});
  ((entity *)IFC4_types[792])
      ->set_subtypes({((entity *)IFC4_types[787]), ((entity *)IFC4_types[794]),
                      ((entity *)IFC4_types[1045]),
                      ((entity *)IFC4_types[1046])});
  ((entity *)IFC4_types[793])
      ->set_subtypes({((entity *)IFC4_types[790]), ((entity *)IFC4_types[795]),
                      ((entity *)IFC4_types[1047]),
                      ((entity *)IFC4_types[1049])});
  ((entity *)IFC4_types[827])
      ->set_subtypes({((entity *)IFC4_types[797]), ((entity *)IFC4_types[836]),
                      ((entity *)IFC4_types[837]),
                      ((entity *)IFC4_types[844])});
  ((entity *)IFC4_types[813])
      ->set_subtypes({((entity *)IFC4_types[798]), ((entity *)IFC4_types[806]),
                      ((entity *)IFC4_types[814]), ((entity *)IFC4_types[826]),
                      ((entity *)IFC4_types[827]),
                      ((entity *)IFC4_types[828])});
  ((entity *)IFC4_types[798])
      ->set_subtypes({((entity *)IFC4_types[799]), ((entity *)IFC4_types[800]),
                      ((entity *)IFC4_types[801]), ((entity *)IFC4_types[803]),
                      ((entity *)IFC4_types[804]),
                      ((entity *)IFC4_types[805])});
  ((entity *)IFC4_types[801])->set_subtypes({((entity *)IFC4_types[802])});
  ((entity *)IFC4_types[806])
      ->set_subtypes({((entity *)IFC4_types[807]), ((entity *)IFC4_types[808]),
                      ((entity *)IFC4_types[809]), ((entity *)IFC4_types[810]),
                      ((entity *)IFC4_types[811]),
                      ((entity *)IFC4_types[812])});
  ((entity *)IFC4_types[814])
      ->set_subtypes({((entity *)IFC4_types[815]), ((entity *)IFC4_types[818]),
                      ((entity *)IFC4_types[817]), ((entity *)IFC4_types[819]),
                      ((entity *)IFC4_types[820]), ((entity *)IFC4_types[823]),
                      ((entity *)IFC4_types[824]), ((entity *)IFC4_types[825]),
                      ((entity *)IFC4_types[833]), ((entity *)IFC4_types[834]),
                      ((entity *)IFC4_types[835]), ((entity *)IFC4_types[838]),
                      ((entity *)IFC4_types[839]), ((entity *)IFC4_types[840]),
                      ((entity *)IFC4_types[841])});
  ((entity *)IFC4_types[815])
      ->set_subtypes(
          {((entity *)IFC4_types[816]), ((entity *)IFC4_types[822])});
  ((entity *)IFC4_types[820])->set_subtypes({((entity *)IFC4_types[821])});
  ((entity *)IFC4_types[828])
      ->set_subtypes({((entity *)IFC4_types[829]), ((entity *)IFC4_types[830]),
                      ((entity *)IFC4_types[831]),
                      ((entity *)IFC4_types[832])});
  ((entity *)IFC4_types[841])->set_subtypes({((entity *)IFC4_types[842])});
  ((entity *)IFC4_types[842])->set_subtypes({((entity *)IFC4_types[843])});
  ((entity *)IFC4_types[167])->set_subtypes({((entity *)IFC4_types[845])});
  ((entity *)IFC4_types[857])->set_subtypes({((entity *)IFC4_types[858])});
  ((entity *)IFC4_types[846])
      ->set_subtypes(
          {((entity *)IFC4_types[891]), ((entity *)IFC4_types[996])});
  ((entity *)IFC4_types[891])
      ->set_subtypes(
          {((entity *)IFC4_types[892]), ((entity *)IFC4_types[1086])});
  ((entity *)IFC4_types[905])
      ->set_subtypes(
          {((entity *)IFC4_types[906]), ((entity *)IFC4_types[907])});
  ((entity *)IFC4_types[931])->set_subtypes({((entity *)IFC4_types[926])});
  ((entity *)IFC4_types[929])
      ->set_subtypes(
          {((entity *)IFC4_types[931]), ((entity *)IFC4_types[933])});
  ((entity *)IFC4_types[952])
      ->set_subtypes(
          {((entity *)IFC4_types[951]), ((entity *)IFC4_types[984])});
  ((entity *)IFC4_types[964])
      ->set_subtypes(
          {((entity *)IFC4_types[955]), ((entity *)IFC4_types[979])});
  ((entity *)IFC4_types[951])
      ->set_subtypes({((entity *)IFC4_types[957]), ((entity *)IFC4_types[981]),
                      ((entity *)IFC4_types[986])});
  ((entity *)IFC4_types[955])
      ->set_subtypes({((entity *)IFC4_types[959]), ((entity *)IFC4_types[982]),
                      ((entity *)IFC4_types[988])});
  ((entity *)IFC4_types[979])
      ->set_subtypes(
          {((entity *)IFC4_types[960]), ((entity *)IFC4_types[989])});
  ((entity *)IFC4_types[960])->set_subtypes({((entity *)IFC4_types[962])});
  ((entity *)IFC4_types[984])
      ->set_subtypes({((entity *)IFC4_types[963]), ((entity *)IFC4_types[983]),
                      ((entity *)IFC4_types[992])});
  ((entity *)IFC4_types[957])->set_subtypes({((entity *)IFC4_types[965])});
  ((entity *)IFC4_types[969])->set_subtypes({((entity *)IFC4_types[967])});
  ((entity *)IFC4_types[966])
      ->set_subtypes(
          {((entity *)IFC4_types[968]), ((entity *)IFC4_types[971])});
  ((entity *)IFC4_types[977])
      ->set_subtypes({((entity *)IFC4_types[970]), ((entity *)IFC4_types[972]),
                      ((entity *)IFC4_types[973]), ((entity *)IFC4_types[975]),
                      ((entity *)IFC4_types[978])});
  ((entity *)IFC4_types[973])->set_subtypes({((entity *)IFC4_types[974])});
  ((entity *)IFC4_types[975])->set_subtypes({((entity *)IFC4_types[976])});
  ((entity *)IFC4_types[971])
      ->set_subtypes(
          {((entity *)IFC4_types[977]), ((entity *)IFC4_types[1009])});
  ((entity *)IFC4_types[986])->set_subtypes({((entity *)IFC4_types[980])});
  ((entity *)IFC4_types[989])->set_subtypes({((entity *)IFC4_types[991])});
  ((entity *)IFC4_types[996])->set_subtypes({((entity *)IFC4_types[995])});
  ((entity *)IFC4_types[1022])
      ->set_subtypes(
          {((entity *)IFC4_types[1006]), ((entity *)IFC4_types[1007])});
  ((entity *)IFC4_types[1016])->set_subtypes({((entity *)IFC4_types[1015])});
  ((entity *)IFC4_types[1020])->set_subtypes({((entity *)IFC4_types[1021])});
  ((entity *)IFC4_types[1038])->set_subtypes({((entity *)IFC4_types[1039])});
  ((entity *)IFC4_types[1058])->set_subtypes({((entity *)IFC4_types[1059])});
  ((entity *)IFC4_types[695])->set_subtypes({((entity *)IFC4_types[1062])});
  ((entity *)IFC4_types[1106])
      ->set_subtypes({((entity *)IFC4_types[1107]),
                      ((entity *)IFC4_types[1108]),
                      ((entity *)IFC4_types[1109])});
  ((entity *)IFC4_types[1128])->set_subtypes({((entity *)IFC4_types[1130])});
  ((entity *)IFC4_types[1140])
      ->set_subtypes(
          {((entity *)IFC4_types[1141]), ((entity *)IFC4_types[1142])});
  ((entity *)IFC4_types[1151])->set_subtypes({((entity *)IFC4_types[1156])});
  ((entity *)IFC4_types[1165])
      ->set_subtypes(
          {((entity *)IFC4_types[1166]), ((entity *)IFC4_types[1168])});
  return new schema_definition(
      strings[3306],
      {IFC4_types[0],    IFC4_types[1],    IFC4_types[2],    IFC4_types[3],
       IFC4_types[4],    IFC4_types[5],    IFC4_types[6],    IFC4_types[7],
       IFC4_types[8],    IFC4_types[9],    IFC4_types[10],   IFC4_types[11],
       IFC4_types[12],   IFC4_types[13],   IFC4_types[14],   IFC4_types[15],
       IFC4_types[16],   IFC4_types[17],   IFC4_types[18],   IFC4_types[19],
       IFC4_types[20],   IFC4_types[21],   IFC4_types[22],   IFC4_types[23],
       IFC4_types[24],   IFC4_types[25],   IFC4_types[26],   IFC4_types[27],
       IFC4_types[28],   IFC4_types[29],   IFC4_types[30],   IFC4_types[31],
       IFC4_types[32],   IFC4_types[33],   IFC4_types[34],   IFC4_types[35],
       IFC4_types[36],   IFC4_types[37],   IFC4_types[38],   IFC4_types[39],
       IFC4_types[40],   IFC4_types[41],   IFC4_types[42],   IFC4_types[43],
       IFC4_types[44],   IFC4_types[45],   IFC4_types[46],   IFC4_types[47],
       IFC4_types[48],   IFC4_types[49],   IFC4_types[50],   IFC4_types[51],
       IFC4_types[52],   IFC4_types[53],   IFC4_types[54],   IFC4_types[55],
       IFC4_types[56],   IFC4_types[57],   IFC4_types[58],   IFC4_types[59],
       IFC4_types[60],   IFC4_types[61],   IFC4_types[62],   IFC4_types[63],
       IFC4_types[64],   IFC4_types[65],   IFC4_types[66],   IFC4_types[67],
       IFC4_types[68],   IFC4_types[69],   IFC4_types[70],   IFC4_types[71],
       IFC4_types[72],   IFC4_types[73],   IFC4_types[74],   IFC4_types[75],
       IFC4_types[76],   IFC4_types[77],   IFC4_types[78],   IFC4_types[79],
       IFC4_types[80],   IFC4_types[81],   IFC4_types[82],   IFC4_types[83],
       IFC4_types[84],   IFC4_types[85],   IFC4_types[86],   IFC4_types[87],
       IFC4_types[88],   IFC4_types[89],   IFC4_types[90],   IFC4_types[91],
       IFC4_types[92],   IFC4_types[93],   IFC4_types[94],   IFC4_types[95],
       IFC4_types[96],   IFC4_types[97],   IFC4_types[98],   IFC4_types[99],
       IFC4_types[100],  IFC4_types[101],  IFC4_types[102],  IFC4_types[103],
       IFC4_types[104],  IFC4_types[105],  IFC4_types[106],  IFC4_types[107],
       IFC4_types[108],  IFC4_types[109],  IFC4_types[110],  IFC4_types[111],
       IFC4_types[112],  IFC4_types[113],  IFC4_types[114],  IFC4_types[115],
       IFC4_types[116],  IFC4_types[117],  IFC4_types[118],  IFC4_types[119],
       IFC4_types[120],  IFC4_types[121],  IFC4_types[122],  IFC4_types[123],
       IFC4_types[124],  IFC4_types[125],  IFC4_types[126],  IFC4_types[127],
       IFC4_types[128],  IFC4_types[129],  IFC4_types[130],  IFC4_types[131],
       IFC4_types[132],  IFC4_types[133],  IFC4_types[134],  IFC4_types[135],
       IFC4_types[136],  IFC4_types[137],  IFC4_types[138],  IFC4_types[139],
       IFC4_types[140],  IFC4_types[141],  IFC4_types[142],  IFC4_types[143],
       IFC4_types[144],  IFC4_types[145],  IFC4_types[146],  IFC4_types[147],
       IFC4_types[148],  IFC4_types[149],  IFC4_types[150],  IFC4_types[151],
       IFC4_types[152],  IFC4_types[153],  IFC4_types[154],  IFC4_types[155],
       IFC4_types[156],  IFC4_types[157],  IFC4_types[158],  IFC4_types[159],
       IFC4_types[160],  IFC4_types[161],  IFC4_types[162],  IFC4_types[163],
       IFC4_types[164],  IFC4_types[165],  IFC4_types[166],  IFC4_types[167],
       IFC4_types[168],  IFC4_types[169],  IFC4_types[170],  IFC4_types[171],
       IFC4_types[172],  IFC4_types[173],  IFC4_types[174],  IFC4_types[175],
       IFC4_types[176],  IFC4_types[177],  IFC4_types[178],  IFC4_types[179],
       IFC4_types[180],  IFC4_types[181],  IFC4_types[182],  IFC4_types[183],
       IFC4_types[184],  IFC4_types[185],  IFC4_types[186],  IFC4_types[187],
       IFC4_types[188],  IFC4_types[189],  IFC4_types[190],  IFC4_types[191],
       IFC4_types[192],  IFC4_types[193],  IFC4_types[194],  IFC4_types[195],
       IFC4_types[196],  IFC4_types[197],  IFC4_types[198],  IFC4_types[199],
       IFC4_types[200],  IFC4_types[201],  IFC4_types[202],  IFC4_types[203],
       IFC4_types[204],  IFC4_types[205],  IFC4_types[206],  IFC4_types[207],
       IFC4_types[208],  IFC4_types[209],  IFC4_types[210],  IFC4_types[211],
       IFC4_types[212],  IFC4_types[213],  IFC4_types[214],  IFC4_types[215],
       IFC4_types[216],  IFC4_types[217],  IFC4_types[218],  IFC4_types[219],
       IFC4_types[220],  IFC4_types[221],  IFC4_types[222],  IFC4_types[223],
       IFC4_types[224],  IFC4_types[225],  IFC4_types[226],  IFC4_types[227],
       IFC4_types[228],  IFC4_types[229],  IFC4_types[230],  IFC4_types[231],
       IFC4_types[232],  IFC4_types[233],  IFC4_types[234],  IFC4_types[235],
       IFC4_types[236],  IFC4_types[237],  IFC4_types[238],  IFC4_types[239],
       IFC4_types[240],  IFC4_types[241],  IFC4_types[242],  IFC4_types[243],
       IFC4_types[244],  IFC4_types[245],  IFC4_types[246],  IFC4_types[247],
       IFC4_types[248],  IFC4_types[249],  IFC4_types[250],  IFC4_types[251],
       IFC4_types[252],  IFC4_types[253],  IFC4_types[254],  IFC4_types[255],
       IFC4_types[256],  IFC4_types[257],  IFC4_types[258],  IFC4_types[259],
       IFC4_types[260],  IFC4_types[261],  IFC4_types[262],  IFC4_types[263],
       IFC4_types[264],  IFC4_types[265],  IFC4_types[266],  IFC4_types[267],
       IFC4_types[268],  IFC4_types[269],  IFC4_types[270],  IFC4_types[271],
       IFC4_types[272],  IFC4_types[273],  IFC4_types[274],  IFC4_types[275],
       IFC4_types[276],  IFC4_types[277],  IFC4_types[278],  IFC4_types[279],
       IFC4_types[280],  IFC4_types[281],  IFC4_types[282],  IFC4_types[283],
       IFC4_types[284],  IFC4_types[285],  IFC4_types[286],  IFC4_types[287],
       IFC4_types[288],  IFC4_types[289],  IFC4_types[290],  IFC4_types[291],
       IFC4_types[292],  IFC4_types[293],  IFC4_types[294],  IFC4_types[295],
       IFC4_types[296],  IFC4_types[297],  IFC4_types[298],  IFC4_types[299],
       IFC4_types[300],  IFC4_types[301],  IFC4_types[302],  IFC4_types[303],
       IFC4_types[304],  IFC4_types[305],  IFC4_types[306],  IFC4_types[307],
       IFC4_types[308],  IFC4_types[309],  IFC4_types[310],  IFC4_types[311],
       IFC4_types[312],  IFC4_types[313],  IFC4_types[314],  IFC4_types[315],
       IFC4_types[316],  IFC4_types[317],  IFC4_types[318],  IFC4_types[319],
       IFC4_types[320],  IFC4_types[321],  IFC4_types[322],  IFC4_types[323],
       IFC4_types[324],  IFC4_types[325],  IFC4_types[326],  IFC4_types[327],
       IFC4_types[328],  IFC4_types[329],  IFC4_types[330],  IFC4_types[331],
       IFC4_types[332],  IFC4_types[333],  IFC4_types[334],  IFC4_types[335],
       IFC4_types[336],  IFC4_types[337],  IFC4_types[338],  IFC4_types[339],
       IFC4_types[340],  IFC4_types[341],  IFC4_types[342],  IFC4_types[343],
       IFC4_types[344],  IFC4_types[345],  IFC4_types[346],  IFC4_types[347],
       IFC4_types[348],  IFC4_types[349],  IFC4_types[350],  IFC4_types[351],
       IFC4_types[352],  IFC4_types[353],  IFC4_types[354],  IFC4_types[355],
       IFC4_types[356],  IFC4_types[357],  IFC4_types[358],  IFC4_types[359],
       IFC4_types[360],  IFC4_types[361],  IFC4_types[362],  IFC4_types[363],
       IFC4_types[364],  IFC4_types[365],  IFC4_types[366],  IFC4_types[367],
       IFC4_types[368],  IFC4_types[369],  IFC4_types[370],  IFC4_types[371],
       IFC4_types[372],  IFC4_types[373],  IFC4_types[374],  IFC4_types[375],
       IFC4_types[376],  IFC4_types[377],  IFC4_types[378],  IFC4_types[379],
       IFC4_types[380],  IFC4_types[381],  IFC4_types[382],  IFC4_types[383],
       IFC4_types[384],  IFC4_types[385],  IFC4_types[386],  IFC4_types[387],
       IFC4_types[388],  IFC4_types[389],  IFC4_types[390],  IFC4_types[391],
       IFC4_types[392],  IFC4_types[393],  IFC4_types[394],  IFC4_types[395],
       IFC4_types[396],  IFC4_types[397],  IFC4_types[398],  IFC4_types[399],
       IFC4_types[400],  IFC4_types[401],  IFC4_types[402],  IFC4_types[403],
       IFC4_types[404],  IFC4_types[405],  IFC4_types[406],  IFC4_types[407],
       IFC4_types[408],  IFC4_types[409],  IFC4_types[410],  IFC4_types[411],
       IFC4_types[412],  IFC4_types[413],  IFC4_types[414],  IFC4_types[415],
       IFC4_types[416],  IFC4_types[417],  IFC4_types[418],  IFC4_types[419],
       IFC4_types[420],  IFC4_types[421],  IFC4_types[422],  IFC4_types[423],
       IFC4_types[424],  IFC4_types[425],  IFC4_types[426],  IFC4_types[427],
       IFC4_types[428],  IFC4_types[429],  IFC4_types[430],  IFC4_types[431],
       IFC4_types[432],  IFC4_types[433],  IFC4_types[434],  IFC4_types[435],
       IFC4_types[436],  IFC4_types[437],  IFC4_types[438],  IFC4_types[439],
       IFC4_types[440],  IFC4_types[441],  IFC4_types[442],  IFC4_types[443],
       IFC4_types[444],  IFC4_types[445],  IFC4_types[446],  IFC4_types[447],
       IFC4_types[448],  IFC4_types[449],  IFC4_types[450],  IFC4_types[451],
       IFC4_types[452],  IFC4_types[453],  IFC4_types[454],  IFC4_types[455],
       IFC4_types[456],  IFC4_types[457],  IFC4_types[458],  IFC4_types[459],
       IFC4_types[460],  IFC4_types[461],  IFC4_types[462],  IFC4_types[463],
       IFC4_types[464],  IFC4_types[465],  IFC4_types[466],  IFC4_types[467],
       IFC4_types[468],  IFC4_types[469],  IFC4_types[470],  IFC4_types[471],
       IFC4_types[472],  IFC4_types[473],  IFC4_types[474],  IFC4_types[475],
       IFC4_types[476],  IFC4_types[477],  IFC4_types[478],  IFC4_types[479],
       IFC4_types[480],  IFC4_types[481],  IFC4_types[482],  IFC4_types[483],
       IFC4_types[484],  IFC4_types[485],  IFC4_types[486],  IFC4_types[487],
       IFC4_types[488],  IFC4_types[489],  IFC4_types[490],  IFC4_types[491],
       IFC4_types[492],  IFC4_types[493],  IFC4_types[494],  IFC4_types[495],
       IFC4_types[496],  IFC4_types[497],  IFC4_types[498],  IFC4_types[499],
       IFC4_types[500],  IFC4_types[501],  IFC4_types[502],  IFC4_types[503],
       IFC4_types[504],  IFC4_types[505],  IFC4_types[506],  IFC4_types[507],
       IFC4_types[508],  IFC4_types[509],  IFC4_types[510],  IFC4_types[511],
       IFC4_types[512],  IFC4_types[513],  IFC4_types[514],  IFC4_types[515],
       IFC4_types[516],  IFC4_types[517],  IFC4_types[518],  IFC4_types[519],
       IFC4_types[520],  IFC4_types[521],  IFC4_types[522],  IFC4_types[523],
       IFC4_types[524],  IFC4_types[525],  IFC4_types[526],  IFC4_types[527],
       IFC4_types[528],  IFC4_types[529],  IFC4_types[530],  IFC4_types[531],
       IFC4_types[532],  IFC4_types[533],  IFC4_types[534],  IFC4_types[535],
       IFC4_types[536],  IFC4_types[537],  IFC4_types[538],  IFC4_types[539],
       IFC4_types[540],  IFC4_types[541],  IFC4_types[542],  IFC4_types[543],
       IFC4_types[544],  IFC4_types[545],  IFC4_types[546],  IFC4_types[547],
       IFC4_types[548],  IFC4_types[549],  IFC4_types[550],  IFC4_types[551],
       IFC4_types[552],  IFC4_types[553],  IFC4_types[554],  IFC4_types[555],
       IFC4_types[556],  IFC4_types[557],  IFC4_types[558],  IFC4_types[559],
       IFC4_types[560],  IFC4_types[561],  IFC4_types[562],  IFC4_types[563],
       IFC4_types[564],  IFC4_types[565],  IFC4_types[566],  IFC4_types[567],
       IFC4_types[568],  IFC4_types[569],  IFC4_types[570],  IFC4_types[571],
       IFC4_types[572],  IFC4_types[573],  IFC4_types[574],  IFC4_types[575],
       IFC4_types[576],  IFC4_types[577],  IFC4_types[578],  IFC4_types[579],
       IFC4_types[580],  IFC4_types[581],  IFC4_types[582],  IFC4_types[583],
       IFC4_types[584],  IFC4_types[585],  IFC4_types[586],  IFC4_types[587],
       IFC4_types[588],  IFC4_types[589],  IFC4_types[590],  IFC4_types[591],
       IFC4_types[592],  IFC4_types[593],  IFC4_types[594],  IFC4_types[595],
       IFC4_types[596],  IFC4_types[597],  IFC4_types[598],  IFC4_types[599],
       IFC4_types[600],  IFC4_types[601],  IFC4_types[602],  IFC4_types[603],
       IFC4_types[604],  IFC4_types[605],  IFC4_types[606],  IFC4_types[607],
       IFC4_types[608],  IFC4_types[609],  IFC4_types[610],  IFC4_types[611],
       IFC4_types[612],  IFC4_types[613],  IFC4_types[614],  IFC4_types[615],
       IFC4_types[616],  IFC4_types[617],  IFC4_types[618],  IFC4_types[619],
       IFC4_types[620],  IFC4_types[621],  IFC4_types[622],  IFC4_types[623],
       IFC4_types[624],  IFC4_types[625],  IFC4_types[626],  IFC4_types[627],
       IFC4_types[628],  IFC4_types[629],  IFC4_types[630],  IFC4_types[631],
       IFC4_types[632],  IFC4_types[633],  IFC4_types[634],  IFC4_types[635],
       IFC4_types[636],  IFC4_types[637],  IFC4_types[638],  IFC4_types[639],
       IFC4_types[640],  IFC4_types[641],  IFC4_types[642],  IFC4_types[643],
       IFC4_types[644],  IFC4_types[645],  IFC4_types[646],  IFC4_types[647],
       IFC4_types[648],  IFC4_types[649],  IFC4_types[650],  IFC4_types[651],
       IFC4_types[652],  IFC4_types[653],  IFC4_types[654],  IFC4_types[655],
       IFC4_types[656],  IFC4_types[657],  IFC4_types[658],  IFC4_types[659],
       IFC4_types[660],  IFC4_types[661],  IFC4_types[662],  IFC4_types[663],
       IFC4_types[664],  IFC4_types[665],  IFC4_types[666],  IFC4_types[667],
       IFC4_types[668],  IFC4_types[669],  IFC4_types[670],  IFC4_types[671],
       IFC4_types[672],  IFC4_types[673],  IFC4_types[674],  IFC4_types[675],
       IFC4_types[676],  IFC4_types[677],  IFC4_types[678],  IFC4_types[679],
       IFC4_types[680],  IFC4_types[681],  IFC4_types[682],  IFC4_types[683],
       IFC4_types[684],  IFC4_types[685],  IFC4_types[686],  IFC4_types[687],
       IFC4_types[688],  IFC4_types[689],  IFC4_types[690],  IFC4_types[691],
       IFC4_types[692],  IFC4_types[693],  IFC4_types[694],  IFC4_types[695],
       IFC4_types[696],  IFC4_types[697],  IFC4_types[698],  IFC4_types[699],
       IFC4_types[700],  IFC4_types[701],  IFC4_types[702],  IFC4_types[703],
       IFC4_types[704],  IFC4_types[705],  IFC4_types[706],  IFC4_types[707],
       IFC4_types[708],  IFC4_types[709],  IFC4_types[710],  IFC4_types[711],
       IFC4_types[712],  IFC4_types[713],  IFC4_types[714],  IFC4_types[715],
       IFC4_types[716],  IFC4_types[717],  IFC4_types[718],  IFC4_types[719],
       IFC4_types[720],  IFC4_types[721],  IFC4_types[722],  IFC4_types[723],
       IFC4_types[724],  IFC4_types[725],  IFC4_types[726],  IFC4_types[727],
       IFC4_types[728],  IFC4_types[729],  IFC4_types[730],  IFC4_types[731],
       IFC4_types[732],  IFC4_types[733],  IFC4_types[734],  IFC4_types[735],
       IFC4_types[736],  IFC4_types[737],  IFC4_types[738],  IFC4_types[739],
       IFC4_types[740],  IFC4_types[741],  IFC4_types[742],  IFC4_types[743],
       IFC4_types[744],  IFC4_types[745],  IFC4_types[746],  IFC4_types[747],
       IFC4_types[748],  IFC4_types[749],  IFC4_types[750],  IFC4_types[751],
       IFC4_types[752],  IFC4_types[753],  IFC4_types[754],  IFC4_types[755],
       IFC4_types[756],  IFC4_types[757],  IFC4_types[758],  IFC4_types[759],
       IFC4_types[760],  IFC4_types[761],  IFC4_types[762],  IFC4_types[763],
       IFC4_types[764],  IFC4_types[765],  IFC4_types[766],  IFC4_types[767],
       IFC4_types[768],  IFC4_types[769],  IFC4_types[770],  IFC4_types[771],
       IFC4_types[772],  IFC4_types[773],  IFC4_types[774],  IFC4_types[775],
       IFC4_types[776],  IFC4_types[777],  IFC4_types[778],  IFC4_types[779],
       IFC4_types[780],  IFC4_types[781],  IFC4_types[782],  IFC4_types[783],
       IFC4_types[784],  IFC4_types[785],  IFC4_types[786],  IFC4_types[787],
       IFC4_types[788],  IFC4_types[789],  IFC4_types[790],  IFC4_types[791],
       IFC4_types[792],  IFC4_types[793],  IFC4_types[794],  IFC4_types[795],
       IFC4_types[796],  IFC4_types[797],  IFC4_types[798],  IFC4_types[799],
       IFC4_types[800],  IFC4_types[801],  IFC4_types[802],  IFC4_types[803],
       IFC4_types[804],  IFC4_types[805],  IFC4_types[806],  IFC4_types[807],
       IFC4_types[808],  IFC4_types[809],  IFC4_types[810],  IFC4_types[811],
       IFC4_types[812],  IFC4_types[813],  IFC4_types[814],  IFC4_types[815],
       IFC4_types[816],  IFC4_types[817],  IFC4_types[818],  IFC4_types[819],
       IFC4_types[820],  IFC4_types[821],  IFC4_types[822],  IFC4_types[823],
       IFC4_types[824],  IFC4_types[825],  IFC4_types[826],  IFC4_types[827],
       IFC4_types[828],  IFC4_types[829],  IFC4_types[830],  IFC4_types[831],
       IFC4_types[832],  IFC4_types[833],  IFC4_types[834],  IFC4_types[835],
       IFC4_types[836],  IFC4_types[837],  IFC4_types[838],  IFC4_types[839],
       IFC4_types[840],  IFC4_types[841],  IFC4_types[842],  IFC4_types[843],
       IFC4_types[844],  IFC4_types[845],  IFC4_types[846],  IFC4_types[847],
       IFC4_types[848],  IFC4_types[849],  IFC4_types[850],  IFC4_types[851],
       IFC4_types[852],  IFC4_types[853],  IFC4_types[854],  IFC4_types[855],
       IFC4_types[856],  IFC4_types[857],  IFC4_types[858],  IFC4_types[859],
       IFC4_types[860],  IFC4_types[861],  IFC4_types[862],  IFC4_types[863],
       IFC4_types[864],  IFC4_types[865],  IFC4_types[866],  IFC4_types[867],
       IFC4_types[868],  IFC4_types[869],  IFC4_types[870],  IFC4_types[871],
       IFC4_types[872],  IFC4_types[873],  IFC4_types[874],  IFC4_types[875],
       IFC4_types[876],  IFC4_types[877],  IFC4_types[878],  IFC4_types[879],
       IFC4_types[880],  IFC4_types[881],  IFC4_types[882],  IFC4_types[883],
       IFC4_types[884],  IFC4_types[885],  IFC4_types[886],  IFC4_types[887],
       IFC4_types[888],  IFC4_types[889],  IFC4_types[890],  IFC4_types[891],
       IFC4_types[892],  IFC4_types[893],  IFC4_types[894],  IFC4_types[895],
       IFC4_types[896],  IFC4_types[897],  IFC4_types[898],  IFC4_types[899],
       IFC4_types[900],  IFC4_types[901],  IFC4_types[902],  IFC4_types[903],
       IFC4_types[904],  IFC4_types[905],  IFC4_types[906],  IFC4_types[907],
       IFC4_types[908],  IFC4_types[909],  IFC4_types[910],  IFC4_types[911],
       IFC4_types[912],  IFC4_types[913],  IFC4_types[914],  IFC4_types[915],
       IFC4_types[916],  IFC4_types[917],  IFC4_types[918],  IFC4_types[919],
       IFC4_types[920],  IFC4_types[921],  IFC4_types[922],  IFC4_types[923],
       IFC4_types[924],  IFC4_types[925],  IFC4_types[926],  IFC4_types[927],
       IFC4_types[928],  IFC4_types[929],  IFC4_types[930],  IFC4_types[931],
       IFC4_types[932],  IFC4_types[933],  IFC4_types[934],  IFC4_types[935],
       IFC4_types[936],  IFC4_types[937],  IFC4_types[938],  IFC4_types[939],
       IFC4_types[940],  IFC4_types[941],  IFC4_types[942],  IFC4_types[943],
       IFC4_types[944],  IFC4_types[945],  IFC4_types[946],  IFC4_types[947],
       IFC4_types[948],  IFC4_types[949],  IFC4_types[950],  IFC4_types[951],
       IFC4_types[952],  IFC4_types[953],  IFC4_types[954],  IFC4_types[955],
       IFC4_types[956],  IFC4_types[957],  IFC4_types[958],  IFC4_types[959],
       IFC4_types[960],  IFC4_types[961],  IFC4_types[962],  IFC4_types[963],
       IFC4_types[964],  IFC4_types[965],  IFC4_types[966],  IFC4_types[967],
       IFC4_types[968],  IFC4_types[969],  IFC4_types[970],  IFC4_types[971],
       IFC4_types[972],  IFC4_types[973],  IFC4_types[974],  IFC4_types[975],
       IFC4_types[976],  IFC4_types[977],  IFC4_types[978],  IFC4_types[979],
       IFC4_types[980],  IFC4_types[981],  IFC4_types[982],  IFC4_types[983],
       IFC4_types[984],  IFC4_types[985],  IFC4_types[986],  IFC4_types[987],
       IFC4_types[988],  IFC4_types[989],  IFC4_types[990],  IFC4_types[991],
       IFC4_types[992],  IFC4_types[993],  IFC4_types[994],  IFC4_types[995],
       IFC4_types[996],  IFC4_types[997],  IFC4_types[998],  IFC4_types[999],
       IFC4_types[1000], IFC4_types[1001], IFC4_types[1002], IFC4_types[1003],
       IFC4_types[1004], IFC4_types[1005], IFC4_types[1006], IFC4_types[1007],
       IFC4_types[1008], IFC4_types[1009], IFC4_types[1010], IFC4_types[1011],
       IFC4_types[1012], IFC4_types[1013], IFC4_types[1014], IFC4_types[1015],
       IFC4_types[1016], IFC4_types[1017], IFC4_types[1018], IFC4_types[1019],
       IFC4_types[1020], IFC4_types[1021], IFC4_types[1022], IFC4_types[1023],
       IFC4_types[1024], IFC4_types[1025], IFC4_types[1026], IFC4_types[1027],
       IFC4_types[1028], IFC4_types[1029], IFC4_types[1030], IFC4_types[1031],
       IFC4_types[1032], IFC4_types[1033], IFC4_types[1034], IFC4_types[1035],
       IFC4_types[1036], IFC4_types[1037], IFC4_types[1038], IFC4_types[1039],
       IFC4_types[1040], IFC4_types[1041], IFC4_types[1042], IFC4_types[1043],
       IFC4_types[1044], IFC4_types[1045], IFC4_types[1046], IFC4_types[1047],
       IFC4_types[1048], IFC4_types[1049], IFC4_types[1050], IFC4_types[1051],
       IFC4_types[1052], IFC4_types[1053], IFC4_types[1054], IFC4_types[1055],
       IFC4_types[1056], IFC4_types[1057], IFC4_types[1058], IFC4_types[1059],
       IFC4_types[1060], IFC4_types[1061], IFC4_types[1062], IFC4_types[1063],
       IFC4_types[1064], IFC4_types[1065], IFC4_types[1066], IFC4_types[1067],
       IFC4_types[1068], IFC4_types[1069], IFC4_types[1070], IFC4_types[1071],
       IFC4_types[1072], IFC4_types[1073], IFC4_types[1074], IFC4_types[1075],
       IFC4_types[1076], IFC4_types[1077], IFC4_types[1078], IFC4_types[1079],
       IFC4_types[1080], IFC4_types[1081], IFC4_types[1082], IFC4_types[1083],
       IFC4_types[1084], IFC4_types[1085], IFC4_types[1086], IFC4_types[1087],
       IFC4_types[1088], IFC4_types[1089], IFC4_types[1090], IFC4_types[1091],
       IFC4_types[1092], IFC4_types[1093], IFC4_types[1094], IFC4_types[1095],
       IFC4_types[1096], IFC4_types[1097], IFC4_types[1098], IFC4_types[1099],
       IFC4_types[1100], IFC4_types[1101], IFC4_types[1102], IFC4_types[1103],
       IFC4_types[1104], IFC4_types[1105], IFC4_types[1106], IFC4_types[1107],
       IFC4_types[1108], IFC4_types[1109], IFC4_types[1110], IFC4_types[1111],
       IFC4_types[1112], IFC4_types[1113], IFC4_types[1114], IFC4_types[1115],
       IFC4_types[1116], IFC4_types[1117], IFC4_types[1118], IFC4_types[1119],
       IFC4_types[1120], IFC4_types[1121], IFC4_types[1122], IFC4_types[1123],
       IFC4_types[1124], IFC4_types[1125], IFC4_types[1126], IFC4_types[1127],
       IFC4_types[1128], IFC4_types[1129], IFC4_types[1130], IFC4_types[1131],
       IFC4_types[1132], IFC4_types[1133], IFC4_types[1134], IFC4_types[1135],
       IFC4_types[1136], IFC4_types[1137], IFC4_types[1138], IFC4_types[1139],
       IFC4_types[1140], IFC4_types[1141], IFC4_types[1142], IFC4_types[1143],
       IFC4_types[1144], IFC4_types[1145], IFC4_types[1146], IFC4_types[1147],
       IFC4_types[1148], IFC4_types[1149], IFC4_types[1150], IFC4_types[1151],
       IFC4_types[1152], IFC4_types[1153], IFC4_types[1154], IFC4_types[1155],
       IFC4_types[1156], IFC4_types[1157], IFC4_types[1158], IFC4_types[1159],
       IFC4_types[1160], IFC4_types[1161], IFC4_types[1162], IFC4_types[1163],
       IFC4_types[1164], IFC4_types[1165], IFC4_types[1166], IFC4_types[1167],
       IFC4_types[1168], IFC4_types[1169], IFC4_types[1170], IFC4_types[1171],
       IFC4_types[1172]},
      new IFC4_instance_factory());
}
static std::unique_ptr<schema_definition> schema;

void Ifc4::clear_schema() { schema.reset(); }

const schema_definition &Ifc4::get_schema() {
  if (!schema) {
    schema.reset(IFC4_populate_schema());
  }
  return *schema;
}
