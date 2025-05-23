#include <ifcparse/Ifc2x3.h>
#include <ifcparse/IfcSchema.h>
#include <string>

using namespace std::string_literals;
using namespace IfcParse;

declaration *IFC2X3_types[980] = {nullptr};

const std::string strings[] = {
    "IfcAbsorbedDoseMeasure"s,
    "IfcAccelerationMeasure"s,
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
    "USERDEFINED"s,
    "NOTDEFINED"s,
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
    "IfcAheadOrBehind"s,
    "AHEAD"s,
    "BEHIND"s,
    "IfcAirTerminalBoxTypeEnum"s,
    "CONSTANTFLOW"s,
    "VARIABLEFLOWPRESSUREDEPENDANT"s,
    "VARIABLEFLOWPRESSUREINDEPENDANT"s,
    "IfcAirTerminalTypeEnum"s,
    "GRILLE"s,
    "REGISTER"s,
    "DIFFUSER"s,
    "EYEBALL"s,
    "IRIS"s,
    "LINEARGRILLE"s,
    "LINEARDIFFUSER"s,
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
    "IfcAreaMeasure"s,
    "IfcArithmeticOperatorEnum"s,
    "ADD"s,
    "DIVIDE"s,
    "MULTIPLY"s,
    "SUBTRACT"s,
    "IfcAssemblyPlaceEnum"s,
    "FACTORY"s,
    "IfcBSplineCurveForm"s,
    "POLYLINE_FORM"s,
    "CIRCULAR_ARC"s,
    "ELLIPTIC_ARC"s,
    "PARABOLIC_ARC"s,
    "HYPERBOLIC_ARC"s,
    "UNSPECIFIED"s,
    "IfcBeamTypeEnum"s,
    "BEAM"s,
    "JOIST"s,
    "LINTEL"s,
    "T_BEAM"s,
    "IfcBenchmarkEnum"s,
    "GREATERTHAN"s,
    "GREATERTHANOREQUALTO"s,
    "LESSTHAN"s,
    "LESSTHANOREQUALTO"s,
    "EQUALTO"s,
    "NOTEQUALTO"s,
    "IfcBoilerTypeEnum"s,
    "WATER"s,
    "STEAM"s,
    "IfcBoolean"s,
    "IfcBooleanOperator"s,
    "UNION"s,
    "INTERSECTION"s,
    "DIFFERENCE"s,
    "IfcBuildingElementProxyTypeEnum"s,
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
    "IfcCableSegmentTypeEnum"s,
    "CABLESEGMENT"s,
    "CONDUCTORSEGMENT"s,
    "IfcChangeActionEnum"s,
    "NOCHANGE"s,
    "MODIFIED"s,
    "ADDED"s,
    "DELETED"s,
    "MODIFIEDADDED"s,
    "MODIFIEDDELETED"s,
    "IfcChillerTypeEnum"s,
    "AIRCOOLED"s,
    "WATERCOOLED"s,
    "HEATRECOVERY"s,
    "IfcCoilTypeEnum"s,
    "DXCOOLINGCOIL"s,
    "WATERCOOLINGCOIL"s,
    "STEAMHEATINGCOIL"s,
    "WATERHEATINGCOIL"s,
    "ELECTRICHEATINGCOIL"s,
    "GASHEATINGCOIL"s,
    "IfcColumnTypeEnum"s,
    "COLUMN"s,
    "IfcComplexNumber"s,
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
    "WATERCOOLEDSHELLTUBE"s,
    "WATERCOOLEDSHELLCOIL"s,
    "WATERCOOLEDTUBEINTUBE"s,
    "WATERCOOLEDBRAZEDPLATE"s,
    "EVAPORATIVECOOLED"s,
    "IfcConnectionTypeEnum"s,
    "ATPATH"s,
    "ATSTART"s,
    "ATEND"s,
    "IfcConstraintEnum"s,
    "HARD"s,
    "SOFT"s,
    "ADVISORY"s,
    "IfcContextDependentMeasure"s,
    "IfcControllerTypeEnum"s,
    "FLOATING"s,
    "PROPORTIONAL"s,
    "PROPORTIONALINTEGRAL"s,
    "PROPORTIONALINTEGRALDERIVATIVE"s,
    "TIMEDTWOPOSITION"s,
    "TWOPOSITION"s,
    "IfcCooledBeamTypeEnum"s,
    "ACTIVE"s,
    "PASSIVE"s,
    "IfcCoolingTowerTypeEnum"s,
    "NATURALDRAFT"s,
    "MECHANICALINDUCEDDRAFT"s,
    "MECHANICALFORCEDDRAFT"s,
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
    "INSULATION"s,
    "MEMBRANE"s,
    "SLEEVING"s,
    "WRAPPING"s,
    "IfcCurrencyEnum"s,
    "AED"s,
    "AES"s,
    "ATS"s,
    "AUD"s,
    "BBD"s,
    "BEG"s,
    "BGL"s,
    "BHD"s,
    "BMD"s,
    "BND"s,
    "BRL"s,
    "BSD"s,
    "BWP"s,
    "BZD"s,
    "CAD"s,
    "CBD"s,
    "CHF"s,
    "CLP"s,
    "CNY"s,
    "CYS"s,
    "CZK"s,
    "DDP"s,
    "DEM"s,
    "DKK"s,
    "EGL"s,
    "EST"s,
    "EUR"s,
    "FAK"s,
    "FIM"s,
    "FJD"s,
    "FKP"s,
    "FRF"s,
    "GBP"s,
    "GIP"s,
    "GMD"s,
    "GRX"s,
    "HKD"s,
    "HUF"s,
    "ICK"s,
    "IDR"s,
    "ILS"s,
    "INR"s,
    "IRP"s,
    "ITL"s,
    "JMD"s,
    "JOD"s,
    "JPY"s,
    "KES"s,
    "KRW"s,
    "KWD"s,
    "KYD"s,
    "LKR"s,
    "LUF"s,
    "MTL"s,
    "MUR"s,
    "MXN"s,
    "MYR"s,
    "NLG"s,
    "NZD"s,
    "OMR"s,
    "PGK"s,
    "PHP"s,
    "PKR"s,
    "PLN"s,
    "PTN"s,
    "QAR"s,
    "RUR"s,
    "SAR"s,
    "SCR"s,
    "SEK"s,
    "SGD"s,
    "SKP"s,
    "THB"s,
    "TRL"s,
    "TTD"s,
    "TWD"s,
    "USD"s,
    "VEB"s,
    "VND"s,
    "XEU"s,
    "ZAR"s,
    "ZWD"s,
    "NOK"s,
    "IfcCurtainWallTypeEnum"s,
    "IfcCurvatureMeasure"s,
    "IfcDamperTypeEnum"s,
    "CONTROLDAMPER"s,
    "FIREDAMPER"s,
    "SMOKEDAMPER"s,
    "FIRESMOKEDAMPER"s,
    "BACKDRAFTDAMPER"s,
    "RELIEFDAMPER"s,
    "BLASTDAMPER"s,
    "GRAVITYDAMPER"s,
    "GRAVITYRELIEFDAMPER"s,
    "BALANCINGDAMPER"s,
    "FUMEHOODEXHAUST"s,
    "IfcDataOriginEnum"s,
    "MEASURED"s,
    "PREDICTED"s,
    "SIMULATED"s,
    "IfcDayInMonthNumber"s,
    "IfcDaylightSavingHour"s,
    "IfcDerivedUnitEnum"s,
    "ANGULARVELOCITYUNIT"s,
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
    "SOUNDPOWERUNIT"s,
    "SOUNDPRESSUREUNIT"s,
    "TEMPERATUREGRADIENTUNIT"s,
    "THERMALEXPANSIONCOEFFICIENTUNIT"s,
    "WARPINGCONSTANTUNIT"s,
    "WARPINGMOMENTUNIT"s,
    "IfcDescriptiveMeasure"s,
    "IfcDimensionCount"s,
    "IfcDimensionExtentUsage"s,
    "ORIGIN"s,
    "TARGET"s,
    "IfcDirectionSenseEnum"s,
    "POSITIVE"s,
    "NEGATIVE"s,
    "IfcDistributionChamberElementTypeEnum"s,
    "FORMEDDUCT"s,
    "INSPECTIONCHAMBER"s,
    "INSPECTIONPIT"s,
    "MANHOLE"s,
    "METERCHAMBER"s,
    "SUMP"s,
    "TRENCH"s,
    "VALVECHAMBER"s,
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
    "IfcDoorPanelPositionEnum"s,
    "LEFT"s,
    "MIDDLE"s,
    "RIGHT"s,
    "IfcDoorStyleConstructionEnum"s,
    "ALUMINIUM"s,
    "HIGH_GRADE_STEEL"s,
    "STEEL"s,
    "WOOD"s,
    "ALUMINIUM_WOOD"s,
    "ALUMINIUM_PLASTIC"s,
    "PLASTIC"s,
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
    "IfcDoseEquivalentMeasure"s,
    "IfcDuctFittingTypeEnum"s,
    "CONNECTOR"s,
    "ENTRY"s,
    "EXIT"s,
    "JUNCTION"s,
    "OBSTRUCTION"s,
    "TRANSITION"s,
    "IfcDuctSegmentTypeEnum"s,
    "RIGIDSEGMENT"s,
    "FLEXIBLESEGMENT"s,
    "IfcDuctSilencerTypeEnum"s,
    "FLATOVAL"s,
    "RECTANGULAR"s,
    "ROUND"s,
    "IfcDynamicViscosityMeasure"s,
    "IfcElectricApplianceTypeEnum"s,
    "COMPUTER"s,
    "DIRECTWATERHEATER"s,
    "DISHWASHER"s,
    "ELECTRICCOOKER"s,
    "ELECTRICHEATER"s,
    "FACSIMILE"s,
    "FREESTANDINGFAN"s,
    "FREEZER"s,
    "FRIDGE_FREEZER"s,
    "HANDDRYER"s,
    "INDIRECTWATERHEATER"s,
    "MICROWAVE"s,
    "PHOTOCOPIER"s,
    "PRINTER"s,
    "REFRIGERATOR"s,
    "RADIANTHEATER"s,
    "SCANNER"s,
    "TELEPHONE"s,
    "TUMBLEDRYER"s,
    "TV"s,
    "VENDINGMACHINE"s,
    "WASHINGMACHINE"s,
    "WATERHEATER"s,
    "WATERCOOLER"s,
    "IfcElectricCapacitanceMeasure"s,
    "IfcElectricChargeMeasure"s,
    "IfcElectricConductanceMeasure"s,
    "IfcElectricCurrentEnum"s,
    "ALTERNATING"s,
    "DIRECT"s,
    "IfcElectricCurrentMeasure"s,
    "IfcElectricDistributionPointFunctionEnum"s,
    "ALARMPANEL"s,
    "CONSUMERUNIT"s,
    "CONTROLPANEL"s,
    "DISTRIBUTIONBOARD"s,
    "GASDETECTORPANEL"s,
    "INDICATORPANEL"s,
    "MIMICPANEL"s,
    "MOTORCONTROLCENTRE"s,
    "SWITCHBOARD"s,
    "IfcElectricFlowStorageDeviceTypeEnum"s,
    "BATTERY"s,
    "CAPACITORBANK"s,
    "HARMONICFILTER"s,
    "INDUCTORBANK"s,
    "UPS"s,
    "IfcElectricGeneratorTypeEnum"s,
    "IfcElectricHeaterTypeEnum"s,
    "ELECTRICPOINTHEATER"s,
    "ELECTRICCABLEHEATER"s,
    "ELECTRICMATHEATER"s,
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
    "COMPLEX"s,
    "ELEMENT"s,
    "PARTIAL"s,
    "IfcEnergyMeasure"s,
    "IfcEnergySequenceEnum"s,
    "PRIMARY"s,
    "SECONDARY"s,
    "TERTIARY"s,
    "AUXILIARY"s,
    "IfcEnvironmentalImpactCategoryEnum"s,
    "COMBINEDVALUE"s,
    "DISPOSAL"s,
    "EXTRACTION"s,
    "INSTALLATION"s,
    "MANUFACTURE"s,
    "TRANSPORTATION"s,
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
    "DIRECTEXPANSIONSHELLANDTUBE"s,
    "DIRECTEXPANSIONTUBEINTUBE"s,
    "DIRECTEXPANSIONBRAZEDPLATE"s,
    "FLOODEDSHELLANDTUBE"s,
    "SHELLANDCOIL"s,
    "IfcFanTypeEnum"s,
    "CENTRIFUGALFORWARDCURVED"s,
    "CENTRIFUGALRADIAL"s,
    "CENTRIFUGALBACKWARDINCLINEDCURVED"s,
    "CENTRIFUGALAIRFOIL"s,
    "TUBEAXIAL"s,
    "VANEAXIAL"s,
    "PROPELLORAXIAL"s,
    "IfcFilterTypeEnum"s,
    "AIRPARTICLEFILTER"s,
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
    "ELECTRICMETER"s,
    "ENERGYMETER"s,
    "FLOWMETER"s,
    "GASMETER"s,
    "OILMETER"s,
    "WATERMETER"s,
    "IfcFontStyle"s,
    "IfcFontVariant"s,
    "IfcFontWeight"s,
    "IfcFootingTypeEnum"s,
    "FOOTING_BEAM"s,
    "PAD_FOOTING"s,
    "PILE_CAP"s,
    "STRIP_FOOTING"s,
    "IfcForceMeasure"s,
    "IfcFrequencyMeasure"s,
    "IfcGasTerminalTypeEnum"s,
    "GASAPPLIANCE"s,
    "GASBOOSTER"s,
    "GASBURNER"s,
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
    "IfcHeatExchangerTypeEnum"s,
    "PLATE"s,
    "SHELLANDTUBE"s,
    "IfcHeatFluxDensityMeasure"s,
    "IfcHeatingValueMeasure"s,
    "IfcHourInDay"s,
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
    "IfcInternalOrExternalEnum"s,
    "INTERNAL"s,
    "EXTERNAL"s,
    "IfcInventoryTypeEnum"s,
    "ASSETINVENTORY"s,
    "SPACEINVENTORY"s,
    "FURNITUREINVENTORY"s,
    "IfcIonConcentrationMeasure"s,
    "IfcIsothermalMoistureCapacityMeasure"s,
    "IfcJunctionBoxTypeEnum"s,
    "IfcKinematicViscosityMeasure"s,
    "IfcLabel"s,
    "IfcLampTypeEnum"s,
    "COMPACTFLUORESCENT"s,
    "FLUORESCENT"s,
    "HIGHPRESSUREMERCURY"s,
    "HIGHPRESSURESODIUM"s,
    "METALHALIDE"s,
    "TUNGSTENFILAMENT"s,
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
    "IfcLinearForceMeasure"s,
    "IfcLinearMomentMeasure"s,
    "IfcLinearStiffnessMeasure"s,
    "IfcLinearVelocityMeasure"s,
    "IfcLoadGroupTypeEnum"s,
    "LOAD_GROUP"s,
    "LOAD_CASE"s,
    "LOAD_COMBINATION_GROUP"s,
    "LOAD_COMBINATION"s,
    "IfcLogical"s,
    "IfcLogicalOperatorEnum"s,
    "LOGICALAND"s,
    "LOGICALOR"s,
    "IfcLuminousFluxMeasure"s,
    "IfcLuminousIntensityDistributionMeasure"s,
    "IfcLuminousIntensityMeasure"s,
    "IfcMagneticFluxDensityMeasure"s,
    "IfcMagneticFluxMeasure"s,
    "IfcMassDensityMeasure"s,
    "IfcMassFlowRateMeasure"s,
    "IfcMassMeasure"s,
    "IfcMassPerLengthMeasure"s,
    "IfcMemberTypeEnum"s,
    "BRACE"s,
    "CHORD"s,
    "COLLAR"s,
    "MEMBER"s,
    "MULLION"s,
    "POST"s,
    "PURLIN"s,
    "RAFTER"s,
    "STRINGER"s,
    "STRUT"s,
    "STUD"s,
    "IfcMinuteInHour"s,
    "IfcModulusOfElasticityMeasure"s,
    "IfcModulusOfLinearSubgradeReactionMeasure"s,
    "IfcModulusOfRotationalSubgradeReactionMeasure"s,
    "IfcModulusOfSubgradeReactionMeasure"s,
    "IfcMoistureDiffusivityMeasure"s,
    "IfcMolecularWeightMeasure"s,
    "IfcMomentOfInertiaMeasure"s,
    "IfcMonetaryMeasure"s,
    "IfcMonthInYearNumber"s,
    "IfcMotorConnectionTypeEnum"s,
    "BELTDRIVE"s,
    "COUPLING"s,
    "DIRECTDRIVE"s,
    "IfcNullStyle"s,
    "NULL"s,
    "IfcNumericMeasure"s,
    "IfcObjectTypeEnum"s,
    "PRODUCT"s,
    "PROCESS"s,
    "CONTROL"s,
    "RESOURCE"s,
    "ACTOR"s,
    "GROUP"s,
    "PROJECT"s,
    "IfcObjectiveEnum"s,
    "CODECOMPLIANCE"s,
    "DESIGNINTENT"s,
    "HEALTHANDSAFETY"s,
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
    "IfcOutletTypeEnum"s,
    "AUDIOVISUALOUTLET"s,
    "COMMUNICATIONSOUTLET"s,
    "POWEROUTLET"s,
    "IfcPHMeasure"s,
    "IfcParameterValue"s,
    "IfcPermeableCoveringOperationEnum"s,
    "GRILL"s,
    "LOUVER"s,
    "SCREEN"s,
    "IfcPhysicalOrVirtualEnum"s,
    "PHYSICAL"s,
    "VIRTUAL"s,
    "IfcPileConstructionEnum"s,
    "CAST_IN_PLACE"s,
    "COMPOSITE"s,
    "PRECAST_CONCRETE"s,
    "PREFAB_STEEL"s,
    "IfcPileTypeEnum"s,
    "COHESION"s,
    "FRICTION"s,
    "SUPPORT"s,
    "IfcPipeFittingTypeEnum"s,
    "IfcPipeSegmentTypeEnum"s,
    "GUTTER"s,
    "SPOOL"s,
    "IfcPlanarForceMeasure"s,
    "IfcPlaneAngleMeasure"s,
    "IfcPlateTypeEnum"s,
    "CURTAIN_PANEL"s,
    "SHEET"s,
    "IfcPositiveLengthMeasure"s,
    "IfcPositivePlaneAngleMeasure"s,
    "IfcPowerMeasure"s,
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
    "IfcProjectOrderRecordTypeEnum"s,
    "CHANGE"s,
    "MAINTENANCE"s,
    "MOVE"s,
    "PURCHASE"s,
    "WORK"s,
    "IfcProjectOrderTypeEnum"s,
    "CHANGEORDER"s,
    "MAINTENANCEWORKORDER"s,
    "MOVEORDER"s,
    "PURCHASEORDER"s,
    "WORKORDER"s,
    "IfcProjectedOrTrueLengthEnum"s,
    "PROJECTED_LENGTH"s,
    "TRUE_LENGTH"s,
    "IfcPropertySourceEnum"s,
    "DESIGN"s,
    "DESIGNMAXIMUM"s,
    "DESIGNMINIMUM"s,
    "ASBUILT"s,
    "COMMISSIONING"s,
    "NOTKNOWN"s,
    "IfcProtectiveDeviceTypeEnum"s,
    "FUSEDISCONNECTOR"s,
    "CIRCUITBREAKER"s,
    "EARTHFAILUREDEVICE"s,
    "RESIDUALCURRENTCIRCUITBREAKER"s,
    "RESIDUALCURRENTSWITCH"s,
    "VARISTOR"s,
    "IfcPumpTypeEnum"s,
    "CIRCULATOR"s,
    "ENDSUCTION"s,
    "SPLITCASE"s,
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
    "IfcReflectanceMethodEnum"s,
    "BLINN"s,
    "FLAT"s,
    "GLASS"s,
    "MATT"s,
    "METAL"s,
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
    "IfcReinforcingBarSurfaceEnum"s,
    "PLAIN"s,
    "TEXTURED"s,
    "IfcResourceConsumptionEnum"s,
    "CONSUMED"s,
    "PARTIALLYCONSUMED"s,
    "NOTCONSUMED"s,
    "OCCUPIED"s,
    "PARTIALLYOCCUPIED"s,
    "NOTOCCUPIED"s,
    "IfcRibPlateDirectionEnum"s,
    "DIRECTION_X"s,
    "DIRECTION_Y"s,
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
    "COMISSIONINGENGINEER"s,
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
    "IfcSecondInMinute"s,
    "IfcSectionModulusMeasure"s,
    "IfcSectionTypeEnum"s,
    "UNIFORM"s,
    "TAPERED"s,
    "IfcSectionalAreaIntegralMeasure"s,
    "IfcSensorTypeEnum"s,
    "CO2SENSOR"s,
    "FIRESENSOR"s,
    "FLOWSENSOR"s,
    "GASSENSOR"s,
    "HEATSENSOR"s,
    "HUMIDITYSENSOR"s,
    "LIGHTSENSOR"s,
    "MOISTURESENSOR"s,
    "MOVEMENTSENSOR"s,
    "PRESSURESENSOR"s,
    "SMOKESENSOR"s,
    "SOUNDSENSOR"s,
    "TEMPERATURESENSOR"s,
    "IfcSequenceEnum"s,
    "START_START"s,
    "START_FINISH"s,
    "FINISH_START"s,
    "FINISH_FINISH"s,
    "IfcServiceLifeFactorTypeEnum"s,
    "A_QUALITYOFCOMPONENTS"s,
    "B_DESIGNLEVEL"s,
    "C_WORKEXECUTIONLEVEL"s,
    "D_INDOORENVIRONMENT"s,
    "E_OUTDOORENVIRONMENT"s,
    "F_INUSECONDITIONS"s,
    "G_MAINTENANCELEVEL"s,
    "IfcServiceLifeTypeEnum"s,
    "ACTUALSERVICELIFE"s,
    "EXPECTEDSERVICELIFE"s,
    "OPTIMISTICREFERENCESERVICELIFE"s,
    "PESSIMISTICREFERENCESERVICELIFE"s,
    "REFERENCESERVICELIFE"s,
    "IfcShearModulusMeasure"s,
    "IfcSlabTypeEnum"s,
    "FLOOR"s,
    "ROOF"s,
    "LANDING"s,
    "BASESLAB"s,
    "IfcSolidAngleMeasure"s,
    "IfcSoundPowerMeasure"s,
    "IfcSoundPressureMeasure"s,
    "IfcSoundScaleEnum"s,
    "DBA"s,
    "DBB"s,
    "DBC"s,
    "NC"s,
    "NR"s,
    "IfcSpaceHeaterTypeEnum"s,
    "SECTIONALRADIATOR"s,
    "PANELRADIATOR"s,
    "TUBULARRADIATOR"s,
    "CONVECTOR"s,
    "BASEBOARDHEATER"s,
    "FINNEDTUBEUNIT"s,
    "UNITHEATER"s,
    "IfcSpaceTypeEnum"s,
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
    "IfcStructuralCurveTypeEnum"s,
    "RIGID_JOINED_MEMBER"s,
    "PIN_JOINED_MEMBER"s,
    "CABLE"s,
    "TENSION_MEMBER"s,
    "COMPRESSION_MEMBER"s,
    "IfcStructuralSurfaceTypeEnum"s,
    "BENDING_ELEMENT"s,
    "MEMBRANE_ELEMENT"s,
    "SHELL"s,
    "IfcSurfaceSide"s,
    "BOTH"s,
    "IfcSurfaceTextureEnum"s,
    "BUMP"s,
    "OPACITY"s,
    "REFLECTION"s,
    "SELFILLUMINATION"s,
    "SHININESS"s,
    "SPECULAR"s,
    "TEXTURE"s,
    "TRANSPARENCYMAP"s,
    "IfcSwitchingDeviceTypeEnum"s,
    "CONTACTOR"s,
    "EMERGENCYSTOP"s,
    "STARTER"s,
    "SWITCHDISCONNECTOR"s,
    "TOGGLESWITCH"s,
    "IfcTankTypeEnum"s,
    "PREFORMED"s,
    "SECTIONAL"s,
    "EXPANSION"s,
    "PRESSUREVESSEL"s,
    "IfcTemperatureGradientMeasure"s,
    "IfcTendonTypeEnum"s,
    "STRAND"s,
    "WIRE"s,
    "BAR"s,
    "COATED"s,
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
    "IfcThermalLoadSourceEnum"s,
    "PEOPLE"s,
    "LIGHTING"s,
    "EQUIPMENT"s,
    "VENTILATIONINDOORAIR"s,
    "VENTILATIONOUTSIDEAIR"s,
    "RECIRCULATEDAIR"s,
    "EXHAUSTAIR"s,
    "AIREXCHANGERATE"s,
    "DRYBULBTEMPERATURE"s,
    "RELATIVEHUMIDITY"s,
    "INFILTRATION"s,
    "IfcThermalLoadTypeEnum"s,
    "SENSIBLE"s,
    "LATENT"s,
    "RADIANT"s,
    "IfcThermalResistanceMeasure"s,
    "IfcThermalTransmittanceMeasure"s,
    "IfcThermodynamicTemperatureMeasure"s,
    "IfcTimeMeasure"s,
    "IfcTimeSeriesDataTypeEnum"s,
    "CONTINUOUS"s,
    "DISCRETE"s,
    "DISCRETEBINARY"s,
    "PIECEWISEBINARY"s,
    "PIECEWISECONSTANT"s,
    "PIECEWISECONTINUOUS"s,
    "IfcTimeSeriesScheduleTypeEnum"s,
    "ANNUAL"s,
    "MONTHLY"s,
    "WEEKLY"s,
    "DAILY"s,
    "IfcTimeStamp"s,
    "IfcTorqueMeasure"s,
    "IfcTransformerTypeEnum"s,
    "FREQUENCY"s,
    "VOLTAGE"s,
    "IfcTransitionCode"s,
    "DISCONTINUOUS"s,
    "CONTSAMEGRADIENT"s,
    "CONTSAMEGRADIENTSAMECURVATURE"s,
    "IfcTransportElementTypeEnum"s,
    "ELEVATOR"s,
    "ESCALATOR"s,
    "MOVINGWALKWAY"s,
    "IfcTrimmingPreference"s,
    "CARTESIAN"s,
    "PARAMETER"s,
    "IfcTubeBundleTypeEnum"s,
    "FINNED"s,
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
    "IfcUnitaryEquipmentTypeEnum"s,
    "AIRHANDLER"s,
    "AIRCONDITIONINGUNIT"s,
    "SPLITSYSTEM"s,
    "ROOFTOPUNIT"s,
    "IfcValveTypeEnum"s,
    "AIRRELEASE"s,
    "ANTIVACUUM"s,
    "CHANGEOVER"s,
    "CHECK"s,
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
    "IfcVolumeMeasure"s,
    "IfcVolumetricFlowRateMeasure"s,
    "IfcWallTypeEnum"s,
    "STANDARD"s,
    "POLYGONAL"s,
    "ELEMENTEDWALL"s,
    "PLUMBINGWALL"s,
    "IfcWarpingConstantMeasure"s,
    "IfcWarpingMomentMeasure"s,
    "IfcWasteTerminalTypeEnum"s,
    "FLOORTRAP"s,
    "FLOORWASTE"s,
    "GULLYSUMP"s,
    "GULLYTRAP"s,
    "GREASEINTERCEPTOR"s,
    "OILINTERCEPTOR"s,
    "PETROLINTERCEPTOR"s,
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
    "IfcWorkControlTypeEnum"s,
    "ACTUAL"s,
    "BASELINE"s,
    "PLANNED"s,
    "IfcYearNumber"s,
    "IfcActorRole"s,
    "IfcAddress"s,
    "IfcApplication"s,
    "IfcAppliedValue"s,
    "IfcAppliedValueRelationship"s,
    "IfcApproval"s,
    "IfcApprovalActorRelationship"s,
    "IfcApprovalPropertyRelationship"s,
    "IfcApprovalRelationship"s,
    "IfcBoundaryCondition"s,
    "IfcBoundaryEdgeCondition"s,
    "IfcBoundaryFaceCondition"s,
    "IfcBoundaryNodeCondition"s,
    "IfcBoundaryNodeConditionWarping"s,
    "IfcCalendarDate"s,
    "IfcClassification"s,
    "IfcClassificationItem"s,
    "IfcClassificationItemRelationship"s,
    "IfcClassificationNotation"s,
    "IfcClassificationNotationFacet"s,
    "IfcColourSpecification"s,
    "IfcConnectionGeometry"s,
    "IfcConnectionPointGeometry"s,
    "IfcConnectionPortGeometry"s,
    "IfcConnectionSurfaceGeometry"s,
    "IfcConstraint"s,
    "IfcConstraintAggregationRelationship"s,
    "IfcConstraintClassificationRelationship"s,
    "IfcConstraintRelationship"s,
    "IfcCoordinatedUniversalTimeOffset"s,
    "IfcCostValue"s,
    "IfcCurrencyRelationship"s,
    "IfcCurveStyleFont"s,
    "IfcCurveStyleFontAndScaling"s,
    "IfcCurveStyleFontPattern"s,
    "IfcDateAndTime"s,
    "IfcDerivedUnit"s,
    "IfcDerivedUnitElement"s,
    "IfcDimensionalExponents"s,
    "IfcDocumentElectronicFormat"s,
    "IfcDocumentInformation"s,
    "IfcDocumentInformationRelationship"s,
    "IfcDraughtingCalloutRelationship"s,
    "IfcEnvironmentalImpactValue"s,
    "IfcExternalReference"s,
    "IfcExternallyDefinedHatchStyle"s,
    "IfcExternallyDefinedSurfaceStyle"s,
    "IfcExternallyDefinedSymbol"s,
    "IfcExternallyDefinedTextFont"s,
    "IfcGridAxis"s,
    "IfcIrregularTimeSeriesValue"s,
    "IfcLibraryInformation"s,
    "IfcLibraryReference"s,
    "IfcLightDistributionData"s,
    "IfcLightIntensityDistribution"s,
    "IfcLocalTime"s,
    "IfcMaterial"s,
    "IfcMaterialClassificationRelationship"s,
    "IfcMaterialLayer"s,
    "IfcMaterialLayerSet"s,
    "IfcMaterialLayerSetUsage"s,
    "IfcMaterialList"s,
    "IfcMaterialProperties"s,
    "IfcMeasureWithUnit"s,
    "IfcMechanicalMaterialProperties"s,
    "IfcMechanicalSteelMaterialProperties"s,
    "IfcMetric"s,
    "IfcMonetaryUnit"s,
    "IfcNamedUnit"s,
    "IfcObjectPlacement"s,
    "IfcObjective"s,
    "IfcOpticalMaterialProperties"s,
    "IfcOrganization"s,
    "IfcOrganizationRelationship"s,
    "IfcOwnerHistory"s,
    "IfcPerson"s,
    "IfcPersonAndOrganization"s,
    "IfcPhysicalQuantity"s,
    "IfcPhysicalSimpleQuantity"s,
    "IfcPostalAddress"s,
    "IfcPreDefinedItem"s,
    "IfcPreDefinedSymbol"s,
    "IfcPreDefinedTerminatorSymbol"s,
    "IfcPreDefinedTextFont"s,
    "IfcPresentationLayerAssignment"s,
    "IfcPresentationLayerWithStyle"s,
    "IfcPresentationStyle"s,
    "IfcPresentationStyleAssignment"s,
    "IfcProductRepresentation"s,
    "IfcProductsOfCombustionProperties"s,
    "IfcProfileDef"s,
    "IfcProfileProperties"s,
    "IfcProperty"s,
    "IfcPropertyConstraintRelationship"s,
    "IfcPropertyDependencyRelationship"s,
    "IfcPropertyEnumeration"s,
    "IfcQuantityArea"s,
    "IfcQuantityCount"s,
    "IfcQuantityLength"s,
    "IfcQuantityTime"s,
    "IfcQuantityVolume"s,
    "IfcQuantityWeight"s,
    "IfcReferencesValueDocument"s,
    "IfcReinforcementBarProperties"s,
    "IfcRelaxation"s,
    "IfcRepresentation"s,
    "IfcRepresentationContext"s,
    "IfcRepresentationItem"s,
    "IfcRepresentationMap"s,
    "IfcRibPlateProfileProperties"s,
    "IfcRoot"s,
    "IfcSIUnit"s,
    "IfcSectionProperties"s,
    "IfcSectionReinforcementProperties"s,
    "IfcShapeAspect"s,
    "IfcShapeModel"s,
    "IfcShapeRepresentation"s,
    "IfcSimpleProperty"s,
    "IfcStructuralConnectionCondition"s,
    "IfcStructuralLoad"s,
    "IfcStructuralLoadStatic"s,
    "IfcStructuralLoadTemperature"s,
    "IfcStyleModel"s,
    "IfcStyledItem"s,
    "IfcStyledRepresentation"s,
    "IfcSurfaceStyle"s,
    "IfcSurfaceStyleLighting"s,
    "IfcSurfaceStyleRefraction"s,
    "IfcSurfaceStyleShading"s,
    "IfcSurfaceStyleWithTextures"s,
    "IfcSurfaceTexture"s,
    "IfcSymbolStyle"s,
    "IfcTable"s,
    "IfcTableRow"s,
    "IfcTelecomAddress"s,
    "IfcTextStyle"s,
    "IfcTextStyleFontModel"s,
    "IfcTextStyleForDefinedFont"s,
    "IfcTextStyleTextModel"s,
    "IfcTextStyleWithBoxCharacteristics"s,
    "IfcTextureCoordinate"s,
    "IfcTextureCoordinateGenerator"s,
    "IfcTextureMap"s,
    "IfcTextureVertex"s,
    "IfcThermalMaterialProperties"s,
    "IfcTimeSeries"s,
    "IfcTimeSeriesReferenceRelationship"s,
    "IfcTimeSeriesValue"s,
    "IfcTopologicalRepresentationItem"s,
    "IfcTopologyRepresentation"s,
    "IfcUnitAssignment"s,
    "IfcVertex"s,
    "IfcVertexBasedTextureMap"s,
    "IfcVertexPoint"s,
    "IfcVirtualGridIntersection"s,
    "IfcWaterProperties"s,
    "IfcActorSelect"s,
    "IfcAppliedValueSelect"s,
    "IfcBoxAlignment"s,
    "IfcCharacterStyleSelect"s,
    "IfcConditionCriterionSelect"s,
    "IfcDateTimeSelect"s,
    "IfcDefinedSymbolSelect"s,
    "IfcDerivedMeasureValue"s,
    "IfcLayeredItem"s,
    "IfcLibrarySelect"s,
    "IfcLightDistributionDataSourceSelect"s,
    "IfcMaterialSelect"s,
    "IfcMetricValueSelect"s,
    "IfcNormalisedRatioMeasure"s,
    "IfcObjectReferenceSelect"s,
    "IfcPositiveRatioMeasure"s,
    "IfcSimpleValue"s,
    "IfcSizeSelect"s,
    "IfcSpecularHighlightSelect"s,
    "IfcSurfaceStyleElementSelect"s,
    "IfcTextFontSelect"s,
    "IfcTextStyleSelect"s,
    "IfcUnit"s,
    "IfcAnnotationOccurrence"s,
    "IfcAnnotationSurfaceOccurrence"s,
    "IfcAnnotationSymbolOccurrence"s,
    "IfcAnnotationTextOccurrence"s,
    "IfcArbitraryClosedProfileDef"s,
    "IfcArbitraryOpenProfileDef"s,
    "IfcArbitraryProfileDefWithVoids"s,
    "IfcBlobTexture"s,
    "IfcCenterLineProfileDef"s,
    "IfcClassificationReference"s,
    "IfcColourRgb"s,
    "IfcComplexProperty"s,
    "IfcCompositeProfileDef"s,
    "IfcConnectedFaceSet"s,
    "IfcConnectionCurveGeometry"s,
    "IfcConnectionPointEccentricity"s,
    "IfcContextDependentUnit"s,
    "IfcConversionBasedUnit"s,
    "IfcCurveStyle"s,
    "IfcDerivedProfileDef"s,
    "IfcDimensionCalloutRelationship"s,
    "IfcDimensionPair"s,
    "IfcDocumentReference"s,
    "IfcDraughtingPreDefinedTextFont"s,
    "IfcEdge"s,
    "IfcEdgeCurve"s,
    "IfcExtendedMaterialProperties"s,
    "IfcFace"s,
    "IfcFaceBound"s,
    "IfcFaceOuterBound"s,
    "IfcFaceSurface"s,
    "IfcFailureConnectionCondition"s,
    "IfcFillAreaStyle"s,
    "IfcFuelProperties"s,
    "IfcGeneralMaterialProperties"s,
    "IfcGeneralProfileProperties"s,
    "IfcGeometricRepresentationContext"s,
    "IfcGeometricRepresentationItem"s,
    "IfcGeometricRepresentationSubContext"s,
    "IfcGeometricSet"s,
    "IfcGridPlacement"s,
    "IfcHalfSpaceSolid"s,
    "IfcHygroscopicMaterialProperties"s,
    "IfcImageTexture"s,
    "IfcIrregularTimeSeries"s,
    "IfcLightSource"s,
    "IfcLightSourceAmbient"s,
    "IfcLightSourceDirectional"s,
    "IfcLightSourceGoniometric"s,
    "IfcLightSourcePositional"s,
    "IfcLightSourceSpot"s,
    "IfcLocalPlacement"s,
    "IfcLoop"s,
    "IfcMappedItem"s,
    "IfcMaterialDefinitionRepresentation"s,
    "IfcMechanicalConcreteMaterialProperties"s,
    "IfcObjectDefinition"s,
    "IfcOneDirectionRepeatFactor"s,
    "IfcOpenShell"s,
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
    "IfcPreDefinedColour"s,
    "IfcPreDefinedCurveFont"s,
    "IfcPreDefinedDimensionSymbol"s,
    "IfcPreDefinedPointMarkerSymbol"s,
    "IfcProductDefinitionShape"s,
    "IfcPropertyBoundedValue"s,
    "IfcPropertyDefinition"s,
    "IfcPropertyEnumeratedValue"s,
    "IfcPropertyListValue"s,
    "IfcPropertyReferenceValue"s,
    "IfcPropertySetDefinition"s,
    "IfcPropertySingleValue"s,
    "IfcPropertyTableValue"s,
    "IfcRectangleProfileDef"s,
    "IfcRegularTimeSeries"s,
    "IfcReinforcementDefinitionProperties"s,
    "IfcRelationship"s,
    "IfcRoundedRectangleProfileDef"s,
    "IfcSectionedSpine"s,
    "IfcServiceLifeFactor"s,
    "IfcShellBasedSurfaceModel"s,
    "IfcSlippageConnectionCondition"s,
    "IfcSolidModel"s,
    "IfcSoundProperties"s,
    "IfcSoundValue"s,
    "IfcSpaceThermalLoadProperties"s,
    "IfcStructuralLoadLinearForce"s,
    "IfcStructuralLoadPlanarForce"s,
    "IfcStructuralLoadSingleDisplacement"s,
    "IfcStructuralLoadSingleDisplacementDistortion"s,
    "IfcStructuralLoadSingleForce"s,
    "IfcStructuralLoadSingleForceWarping"s,
    "IfcStructuralProfileProperties"s,
    "IfcStructuralSteelProfileProperties"s,
    "IfcSubedge"s,
    "IfcSurface"s,
    "IfcSurfaceStyleRendering"s,
    "IfcSweptAreaSolid"s,
    "IfcSweptDiskSolid"s,
    "IfcSweptSurface"s,
    "IfcTShapeProfileDef"s,
    "IfcTerminatorSymbol"s,
    "IfcTextLiteral"s,
    "IfcTextLiteralWithExtent"s,
    "IfcTrapeziumProfileDef"s,
    "IfcTwoDirectionRepeatFactor"s,
    "IfcTypeObject"s,
    "IfcTypeProduct"s,
    "IfcUShapeProfileDef"s,
    "IfcVector"s,
    "IfcVertexLoop"s,
    "IfcWindowLiningProperties"s,
    "IfcWindowPanelProperties"s,
    "IfcWindowStyle"s,
    "IfcZShapeProfileDef"s,
    "IfcClassificationNotationSelect"s,
    "IfcColour"s,
    "IfcColourOrFactor"s,
    "IfcCurveStyleFontSelect"s,
    "IfcDocumentSelect"s,
    "IfcHatchLineDistanceSelect"s,
    "IfcMeasureValue"s,
    "IfcPointOrVertexPoint"s,
    "IfcPresentationStyleSelect"s,
    "IfcSymbolStyleSelect"s,
    "IfcValue"s,
    "IfcAnnotationCurveOccurrence"s,
    "IfcAnnotationFillArea"s,
    "IfcAnnotationFillAreaOccurrence"s,
    "IfcAnnotationSurface"s,
    "IfcAxis1Placement"s,
    "IfcAxis2Placement2D"s,
    "IfcAxis2Placement3D"s,
    "IfcBooleanResult"s,
    "IfcBoundedSurface"s,
    "IfcBoundingBox"s,
    "IfcBoxedHalfSpace"s,
    "IfcCShapeProfileDef"s,
    "IfcCartesianPoint"s,
    "IfcCartesianTransformationOperator"s,
    "IfcCartesianTransformationOperator2D"s,
    "IfcCartesianTransformationOperator2DnonUniform"s,
    "IfcCartesianTransformationOperator3D"s,
    "IfcCartesianTransformationOperator3DnonUniform"s,
    "IfcCircleProfileDef"s,
    "IfcClosedShell"s,
    "IfcCompositeCurveSegment"s,
    "IfcCraneRailAShapeProfileDef"s,
    "IfcCraneRailFShapeProfileDef"s,
    "IfcCsgPrimitive3D"s,
    "IfcCsgSolid"s,
    "IfcCurve"s,
    "IfcCurveBoundedPlane"s,
    "IfcDefinedSymbol"s,
    "IfcDimensionCurve"s,
    "IfcDimensionCurveTerminator"s,
    "IfcDirection"s,
    "IfcDoorLiningProperties"s,
    "IfcDoorPanelProperties"s,
    "IfcDoorStyle"s,
    "IfcDraughtingCallout"s,
    "IfcDraughtingPreDefinedColour"s,
    "IfcDraughtingPreDefinedCurveFont"s,
    "IfcEdgeLoop"s,
    "IfcElementQuantity"s,
    "IfcElementType"s,
    "IfcElementarySurface"s,
    "IfcEllipseProfileDef"s,
    "IfcEnergyProperties"s,
    "IfcExtrudedAreaSolid"s,
    "IfcFaceBasedSurfaceModel"s,
    "IfcFillAreaStyleHatching"s,
    "IfcFillAreaStyleTileSymbolWithStyle"s,
    "IfcFillAreaStyleTiles"s,
    "IfcFluidFlowProperties"s,
    "IfcFurnishingElementType"s,
    "IfcFurnitureType"s,
    "IfcGeometricCurveSet"s,
    "IfcIShapeProfileDef"s,
    "IfcLShapeProfileDef"s,
    "IfcLine"s,
    "IfcManifoldSolidBrep"s,
    "IfcObject"s,
    "IfcOffsetCurve2D"s,
    "IfcOffsetCurve3D"s,
    "IfcPermeableCoveringProperties"s,
    "IfcPlanarBox"s,
    "IfcPlane"s,
    "IfcProcess"s,
    "IfcProduct"s,
    "IfcProject"s,
    "IfcProjectionCurve"s,
    "IfcPropertySet"s,
    "IfcProxy"s,
    "IfcRectangleHollowProfileDef"s,
    "IfcRectangularPyramid"s,
    "IfcRectangularTrimmedSurface"s,
    "IfcRelAssigns"s,
    "IfcRelAssignsToActor"s,
    "IfcRelAssignsToControl"s,
    "IfcRelAssignsToGroup"s,
    "IfcRelAssignsToProcess"s,
    "IfcRelAssignsToProduct"s,
    "IfcRelAssignsToProjectOrder"s,
    "IfcRelAssignsToResource"s,
    "IfcRelAssociates"s,
    "IfcRelAssociatesAppliedValue"s,
    "IfcRelAssociatesApproval"s,
    "IfcRelAssociatesClassification"s,
    "IfcRelAssociatesConstraint"s,
    "IfcRelAssociatesDocument"s,
    "IfcRelAssociatesLibrary"s,
    "IfcRelAssociatesMaterial"s,
    "IfcRelAssociatesProfileProperties"s,
    "IfcRelConnects"s,
    "IfcRelConnectsElements"s,
    "IfcRelConnectsPathElements"s,
    "IfcRelConnectsPortToElement"s,
    "IfcRelConnectsPorts"s,
    "IfcRelConnectsStructuralActivity"s,
    "IfcRelConnectsStructuralElement"s,
    "IfcRelConnectsStructuralMember"s,
    "IfcRelConnectsWithEccentricity"s,
    "IfcRelConnectsWithRealizingElements"s,
    "IfcRelContainedInSpatialStructure"s,
    "IfcRelCoversBldgElements"s,
    "IfcRelCoversSpaces"s,
    "IfcRelDecomposes"s,
    "IfcRelDefines"s,
    "IfcRelDefinesByProperties"s,
    "IfcRelDefinesByType"s,
    "IfcRelFillsElement"s,
    "IfcRelFlowControlElements"s,
    "IfcRelInteractionRequirements"s,
    "IfcRelNests"s,
    "IfcRelOccupiesSpaces"s,
    "IfcRelOverridesProperties"s,
    "IfcRelProjectsElement"s,
    "IfcRelReferencedInSpatialStructure"s,
    "IfcRelSchedulesCostItems"s,
    "IfcRelSequence"s,
    "IfcRelServicesBuildings"s,
    "IfcRelSpaceBoundary"s,
    "IfcRelVoidsElement"s,
    "IfcResource"s,
    "IfcRevolvedAreaSolid"s,
    "IfcRightCircularCone"s,
    "IfcRightCircularCylinder"s,
    "IfcSpatialStructureElement"s,
    "IfcSpatialStructureElementType"s,
    "IfcSphere"s,
    "IfcStructuralActivity"s,
    "IfcStructuralItem"s,
    "IfcStructuralMember"s,
    "IfcStructuralReaction"s,
    "IfcStructuralSurfaceMember"s,
    "IfcStructuralSurfaceMemberVarying"s,
    "IfcStructuredDimensionCallout"s,
    "IfcSurfaceCurveSweptAreaSolid"s,
    "IfcSurfaceOfLinearExtrusion"s,
    "IfcSurfaceOfRevolution"s,
    "IfcSystemFurnitureElementType"s,
    "IfcTask"s,
    "IfcTransportElementType"s,
    "IfcAxis2Placement"s,
    "IfcBooleanOperand"s,
    "IfcCsgSelect"s,
    "IfcCurveFontOrScaledCurveFontSelect"s,
    "IfcDraughtingCalloutElement"s,
    "IfcFillAreaStyleTileShapeSelect"s,
    "IfcFillStyleSelect"s,
    "IfcGeometricSetSelect"s,
    "IfcOrientationSelect"s,
    "IfcShell"s,
    "IfcSurfaceOrFaceSurface"s,
    "IfcTrimmingSelect"s,
    "IfcVectorOrDirection"s,
    "IfcActor"s,
    "IfcAnnotation"s,
    "IfcAsymmetricIShapeProfileDef"s,
    "IfcBlock"s,
    "IfcBooleanClippingResult"s,
    "IfcBoundedCurve"s,
    "IfcBuilding"s,
    "IfcBuildingElementType"s,
    "IfcBuildingStorey"s,
    "IfcCircleHollowProfileDef"s,
    "IfcColumnType"s,
    "IfcCompositeCurve"s,
    "IfcConic"s,
    "IfcConstructionResource"s,
    "IfcControl"s,
    "IfcCostItem"s,
    "IfcCostSchedule"s,
    "IfcCoveringType"s,
    "IfcCrewResource"s,
    "IfcCurtainWallType"s,
    "IfcDimensionCurveDirectedCallout"s,
    "IfcDistributionElementType"s,
    "IfcDistributionFlowElementType"s,
    "IfcElectricalBaseProperties"s,
    "IfcElement"s,
    "IfcElementAssembly"s,
    "IfcElementComponent"s,
    "IfcElementComponentType"s,
    "IfcEllipse"s,
    "IfcEnergyConversionDeviceType"s,
    "IfcEquipmentElement"s,
    "IfcEquipmentStandard"s,
    "IfcEvaporativeCoolerType"s,
    "IfcEvaporatorType"s,
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
    "IfcFurnishingElement"s,
    "IfcFurnitureStandard"s,
    "IfcGasTerminalType"s,
    "IfcGrid"s,
    "IfcGroup"s,
    "IfcHeatExchangerType"s,
    "IfcHumidifierType"s,
    "IfcInventory"s,
    "IfcJunctionBoxType"s,
    "IfcLaborResource"s,
    "IfcLampType"s,
    "IfcLightFixtureType"s,
    "IfcLinearDimension"s,
    "IfcMechanicalFastener"s,
    "IfcMechanicalFastenerType"s,
    "IfcMemberType"s,
    "IfcMotorConnectionType"s,
    "IfcMove"s,
    "IfcOccupant"s,
    "IfcOpeningElement"s,
    "IfcOrderAction"s,
    "IfcOutletType"s,
    "IfcPerformanceHistory"s,
    "IfcPermit"s,
    "IfcPipeFittingType"s,
    "IfcPipeSegmentType"s,
    "IfcPlateType"s,
    "IfcPolyline"s,
    "IfcPort"s,
    "IfcProcedure"s,
    "IfcProjectOrder"s,
    "IfcProjectOrderRecord"s,
    "IfcProjectionElement"s,
    "IfcProtectiveDeviceType"s,
    "IfcPumpType"s,
    "IfcRadiusDimension"s,
    "IfcRailingType"s,
    "IfcRampFlightType"s,
    "IfcRelAggregates"s,
    "IfcRelAssignsTasks"s,
    "IfcSanitaryTerminalType"s,
    "IfcScheduleTimeControl"s,
    "IfcServiceLife"s,
    "IfcSite"s,
    "IfcSlabType"s,
    "IfcSpace"s,
    "IfcSpaceHeaterType"s,
    "IfcSpaceProgram"s,
    "IfcSpaceType"s,
    "IfcStackTerminalType"s,
    "IfcStairFlightType"s,
    "IfcStructuralAction"s,
    "IfcStructuralConnection"s,
    "IfcStructuralCurveConnection"s,
    "IfcStructuralCurveMember"s,
    "IfcStructuralCurveMemberVarying"s,
    "IfcStructuralLinearAction"s,
    "IfcStructuralLinearActionVarying"s,
    "IfcStructuralLoadGroup"s,
    "IfcStructuralPlanarAction"s,
    "IfcStructuralPlanarActionVarying"s,
    "IfcStructuralPointAction"s,
    "IfcStructuralPointConnection"s,
    "IfcStructuralPointReaction"s,
    "IfcStructuralResultGroup"s,
    "IfcStructuralSurfaceConnection"s,
    "IfcSubContractResource"s,
    "IfcSwitchingDeviceType"s,
    "IfcSystem"s,
    "IfcTankType"s,
    "IfcTimeSeriesSchedule"s,
    "IfcTransformerType"s,
    "IfcTransportElement"s,
    "IfcTrimmedCurve"s,
    "IfcTubeBundleType"s,
    "IfcUnitaryEquipmentType"s,
    "IfcValveType"s,
    "IfcVirtualElement"s,
    "IfcWallType"s,
    "IfcWasteTerminalType"s,
    "IfcWorkControl"s,
    "IfcWorkPlan"s,
    "IfcWorkSchedule"s,
    "IfcZone"s,
    "IfcCurveOrEdgeCurve"s,
    "IfcStructuralActivityAssignmentSelect"s,
    "Ifc2DCompositeCurve"s,
    "IfcActionRequest"s,
    "IfcAirTerminalBoxType"s,
    "IfcAirTerminalType"s,
    "IfcAirToAirHeatRecoveryType"s,
    "IfcAngularDimension"s,
    "IfcAsset"s,
    "IfcBSplineCurve"s,
    "IfcBeamType"s,
    "IfcBezierCurve"s,
    "IfcBoilerType"s,
    "IfcBuildingElement"s,
    "IfcBuildingElementComponent"s,
    "IfcBuildingElementPart"s,
    "IfcBuildingElementProxy"s,
    "IfcBuildingElementProxyType"s,
    "IfcCableCarrierFittingType"s,
    "IfcCableCarrierSegmentType"s,
    "IfcCableSegmentType"s,
    "IfcChillerType"s,
    "IfcCircle"s,
    "IfcCoilType"s,
    "IfcColumn"s,
    "IfcCompressorType"s,
    "IfcCondenserType"s,
    "IfcCondition"s,
    "IfcConditionCriterion"s,
    "IfcConstructionEquipmentResource"s,
    "IfcConstructionMaterialResource"s,
    "IfcConstructionProductResource"s,
    "IfcCooledBeamType"s,
    "IfcCoolingTowerType"s,
    "IfcCovering"s,
    "IfcCurtainWall"s,
    "IfcDamperType"s,
    "IfcDiameterDimension"s,
    "IfcDiscreteAccessory"s,
    "IfcDiscreteAccessoryType"s,
    "IfcDistributionChamberElementType"s,
    "IfcDistributionControlElementType"s,
    "IfcDistributionElement"s,
    "IfcDistributionFlowElement"s,
    "IfcDistributionPort"s,
    "IfcDoor"s,
    "IfcDuctFittingType"s,
    "IfcDuctSegmentType"s,
    "IfcDuctSilencerType"s,
    "IfcEdgeFeature"s,
    "IfcElectricApplianceType"s,
    "IfcElectricFlowStorageDeviceType"s,
    "IfcElectricGeneratorType"s,
    "IfcElectricHeaterType"s,
    "IfcElectricMotorType"s,
    "IfcElectricTimeControlType"s,
    "IfcElectricalCircuit"s,
    "IfcElectricalElement"s,
    "IfcEnergyConversionDevice"s,
    "IfcFanType"s,
    "IfcFilterType"s,
    "IfcFireSuppressionTerminalType"s,
    "IfcFlowController"s,
    "IfcFlowFitting"s,
    "IfcFlowInstrumentType"s,
    "IfcFlowMovingDevice"s,
    "IfcFlowSegment"s,
    "IfcFlowStorageDevice"s,
    "IfcFlowTerminal"s,
    "IfcFlowTreatmentDevice"s,
    "IfcFooting"s,
    "IfcMember"s,
    "IfcPile"s,
    "IfcPlate"s,
    "IfcRailing"s,
    "IfcRamp"s,
    "IfcRampFlight"s,
    "IfcRationalBezierCurve"s,
    "IfcReinforcingElement"s,
    "IfcReinforcingMesh"s,
    "IfcRoof"s,
    "IfcRoundedEdgeFeature"s,
    "IfcSensorType"s,
    "IfcSlab"s,
    "IfcStair"s,
    "IfcStairFlight"s,
    "IfcStructuralAnalysisModel"s,
    "IfcTendon"s,
    "IfcTendonAnchor"s,
    "IfcVibrationIsolatorType"s,
    "IfcWall"s,
    "IfcWallStandardCase"s,
    "IfcWindow"s,
    "IfcActuatorType"s,
    "IfcAlarmType"s,
    "IfcBeam"s,
    "IfcChamferEdgeFeature"s,
    "IfcControllerType"s,
    "IfcDistributionChamberElement"s,
    "IfcDistributionControlElement"s,
    "IfcElectricDistributionPoint"s,
    "IfcReinforcingBar"s,
    "RequestID"s,
    "TheActor"s,
    "Role"s,
    "UserDefinedRole"s,
    "Description"s,
    "PredefinedType"s,
    "Purpose"s,
    "UserDefinedPurpose"s,
    "OuterBoundary"s,
    "InnerBoundaries"s,
    "FillStyleTarget"s,
    "GlobalOrLocal"s,
    "Item"s,
    "TextureCoordinates"s,
    "ApplicationDeveloper"s,
    "Version"s,
    "ApplicationFullName"s,
    "ApplicationIdentifier"s,
    "Name"s,
    "AppliedValue"s,
    "UnitBasis"s,
    "ApplicableDate"s,
    "FixedUntilDate"s,
    "ComponentOfTotal"s,
    "Components"s,
    "ArithmeticOperator"s,
    "ApprovalDateTime"s,
    "ApprovalStatus"s,
    "ApprovalLevel"s,
    "ApprovalQualifier"s,
    "Identifier"s,
    "Actor"s,
    "Approval"s,
    "ApprovedProperties"s,
    "RelatedApproval"s,
    "RelatingApproval"s,
    "OuterCurve"s,
    "Curve"s,
    "InnerCurves"s,
    "AssetID"s,
    "OriginalValue"s,
    "CurrentValue"s,
    "TotalReplacementCost"s,
    "Owner"s,
    "User"s,
    "ResponsiblePerson"s,
    "IncorporationDate"s,
    "DepreciatedValue"s,
    "TopFlangeWidth"s,
    "TopFlangeThickness"s,
    "TopFlangeFilletRadius"s,
    "CentreOfGravityInY"s,
    "Axis"s,
    "RefDirection"s,
    "Degree"s,
    "ControlPointsList"s,
    "CurveForm"s,
    "ClosedCurve"s,
    "SelfIntersect"s,
    "RasterFormat"s,
    "RasterCode"s,
    "XLength"s,
    "YLength"s,
    "ZLength"s,
    "Operator"s,
    "FirstOperand"s,
    "SecondOperand"s,
    "LinearStiffnessByLengthX"s,
    "LinearStiffnessByLengthY"s,
    "LinearStiffnessByLengthZ"s,
    "RotationalStiffnessByLengthX"s,
    "RotationalStiffnessByLengthY"s,
    "RotationalStiffnessByLengthZ"s,
    "LinearStiffnessByAreaX"s,
    "LinearStiffnessByAreaY"s,
    "LinearStiffnessByAreaZ"s,
    "LinearStiffnessX"s,
    "LinearStiffnessY"s,
    "LinearStiffnessZ"s,
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
    "CompositionType"s,
    "Elevation"s,
    "Depth"s,
    "Width"s,
    "WallThickness"s,
    "Girth"s,
    "InternalFilletRadius"s,
    "CentreOfGravityInX"s,
    "DayComponent"s,
    "MonthComponent"s,
    "YearComponent"s,
    "Coordinates"s,
    "Axis1"s,
    "Axis2"s,
    "LocalOrigin"s,
    "Scale"s,
    "Scale2"s,
    "Axis3"s,
    "Scale3"s,
    "Thickness"s,
    "Height"s,
    "Radius"s,
    "Source"s,
    "Edition"s,
    "EditionDate"s,
    "Notation"s,
    "ItemOf"s,
    "Title"s,
    "RelatingItem"s,
    "RelatedItems"s,
    "NotationFacets"s,
    "NotationValue"s,
    "ReferencedSource"s,
    "Red"s,
    "Green"s,
    "Blue"s,
    "UsageName"s,
    "HasProperties"s,
    "Segments"s,
    "Transition"s,
    "SameSense"s,
    "ParentCurve"s,
    "Profiles"s,
    "Label"s,
    "Criterion"s,
    "CriterionDateTime"s,
    "Position"s,
    "CfsFaces"s,
    "CurveOnRelatingElement"s,
    "CurveOnRelatedElement"s,
    "EccentricityInX"s,
    "EccentricityInY"s,
    "EccentricityInZ"s,
    "PointOnRelatingElement"s,
    "PointOnRelatedElement"s,
    "LocationAtRelatingElement"s,
    "LocationAtRelatedElement"s,
    "ProfileOfPort"s,
    "SurfaceOnRelatingElement"s,
    "SurfaceOnRelatedElement"s,
    "ConstraintGrade"s,
    "ConstraintSource"s,
    "CreatingActor"s,
    "CreationTime"s,
    "UserDefinedGrade"s,
    "RelatingConstraint"s,
    "RelatedConstraints"s,
    "LogicalAggregator"s,
    "ClassifiedConstraint"s,
    "RelatedClassifications"s,
    "Suppliers"s,
    "UsageRatio"s,
    "ResourceIdentifier"s,
    "ResourceGroup"s,
    "ResourceConsumption"s,
    "BaseQuantity"s,
    "ConversionFactor"s,
    "HourOffset"s,
    "MinuteOffset"s,
    "Sense"s,
    "SubmittedBy"s,
    "PreparedBy"s,
    "SubmittedOn"s,
    "Status"s,
    "TargetUsers"s,
    "UpdateDate"s,
    "ID"s,
    "CostType"s,
    "Condition"s,
    "OverallHeight"s,
    "BaseWidth2"s,
    "HeadWidth"s,
    "HeadDepth2"s,
    "HeadDepth3"s,
    "WebThickness"s,
    "BaseWidth4"s,
    "BaseDepth1"s,
    "BaseDepth2"s,
    "BaseDepth3"s,
    "TreeRootExpression"s,
    "RelatingMonetaryUnit"s,
    "RelatedMonetaryUnit"s,
    "ExchangeRate"s,
    "RateDateTime"s,
    "RateSource"s,
    "BasisSurface"s,
    "CurveFont"s,
    "CurveWidth"s,
    "CurveColour"s,
    "PatternList"s,
    "CurveFontScaling"s,
    "VisibleSegmentLength"s,
    "InvisibleSegmentLength"s,
    "DateComponent"s,
    "TimeComponent"s,
    "Definition"s,
    "Target"s,
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
    "ControlElementId"s,
    "FlowDirection"s,
    "FileExtension"s,
    "MimeContentType"s,
    "MimeSubtype"s,
    "DocumentId"s,
    "DocumentReferences"s,
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
    "OverallWidth"s,
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
    "PanelDepth"s,
    "PanelOperation"s,
    "PanelWidth"s,
    "PanelPosition"s,
    "OperationType"s,
    "ConstructionType"s,
    "ParameterTakesPrecedence"s,
    "Sizeable"s,
    "Contents"s,
    "RelatingDraughtingCallout"s,
    "RelatedDraughtingCallout"s,
    "EdgeStart"s,
    "EdgeEnd"s,
    "EdgeGeometry"s,
    "FeatureLength"s,
    "EdgeList"s,
    "DistributionPointFunction"s,
    "UserDefinedFunction"s,
    "ElectricCurrentType"s,
    "InputVoltage"s,
    "InputFrequency"s,
    "FullLoadCurrent"s,
    "MinimumCircuitCurrent"s,
    "MaximumPowerInput"s,
    "RatedPowerInput"s,
    "InputPhase"s,
    "Tag"s,
    "AssemblyPlace"s,
    "MethodOfMeasurement"s,
    "Quantities"s,
    "ElementType"s,
    "SemiAxis1"s,
    "SemiAxis2"s,
    "EnergySequence"s,
    "UserDefinedEnergySequence"s,
    "ImpactType"s,
    "Category"s,
    "UserDefinedCategory"s,
    "ExtendedProperties"s,
    "Location"s,
    "ItemReference"s,
    "ExtrudedDirection"s,
    "Bounds"s,
    "FbsmFaces"s,
    "Bound"s,
    "Orientation"s,
    "FaceSurface"s,
    "Voids"s,
    "TensionFailureX"s,
    "TensionFailureY"s,
    "TensionFailureZ"s,
    "CompressionFailureX"s,
    "CompressionFailureY"s,
    "CompressionFailureZ"s,
    "FillStyles"s,
    "HatchLineAppearance"s,
    "StartOfNextHatchLine"s,
    "PointOfReferenceHatchLine"s,
    "PatternStart"s,
    "HatchLineAngle"s,
    "Symbol"s,
    "TilingPattern"s,
    "Tiles"s,
    "TilingScale"s,
    "PropertySource"s,
    "FlowConditionTimeSeries"s,
    "VelocityTimeSeries"s,
    "FlowrateTimeSeries"s,
    "Fluid"s,
    "PressureTimeSeries"s,
    "UserDefinedPropertySource"s,
    "TemperatureSingleValue"s,
    "WetBulbTemperatureSingleValue"s,
    "WetBulbTemperatureTimeSeries"s,
    "TemperatureTimeSeries"s,
    "FlowrateSingleValue"s,
    "FlowConditionSingleValue"s,
    "VelocitySingleValue"s,
    "PressureSingleValue"s,
    "CombustionTemperature"s,
    "CarbonContent"s,
    "LowerHeatingValue"s,
    "HigherHeatingValue"s,
    "MolecularWeight"s,
    "Porosity"s,
    "MassDensity"s,
    "PhysicalWeight"s,
    "Perimeter"s,
    "MinimumPlateThickness"s,
    "MaximumPlateThickness"s,
    "CrossSectionArea"s,
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
    "UpperVaporResistanceFactor"s,
    "LowerVaporResistanceFactor"s,
    "IsothermalMoistureCapacity"s,
    "VaporPermeability"s,
    "MoistureDiffusivity"s,
    "OverallDepth"s,
    "FlangeThickness"s,
    "FilletRadius"s,
    "UrlReference"s,
    "InventoryType"s,
    "Jurisdiction"s,
    "ResponsiblePersons"s,
    "LastUpdateDate"s,
    "Values"s,
    "TimeStamp"s,
    "ListValues"s,
    "EdgeRadius"s,
    "LegSlope"s,
    "SkillSet"s,
    "Publisher"s,
    "VersionDate"s,
    "LibraryReference"s,
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
    "HourComponent"s,
    "MinuteComponent"s,
    "SecondComponent"s,
    "Zone"s,
    "DaylightSavingOffset"s,
    "Outer"s,
    "MappingSource"s,
    "MappingTarget"s,
    "MaterialClassifications"s,
    "ClassifiedMaterial"s,
    "RepresentedMaterial"s,
    "Material"s,
    "LayerThickness"s,
    "IsVentilated"s,
    "MaterialLayers"s,
    "LayerSetName"s,
    "ForLayerSet"s,
    "LayerSetDirection"s,
    "DirectionSense"s,
    "OffsetFromReferenceLine"s,
    "Materials"s,
    "ValueComponent"s,
    "UnitComponent"s,
    "CompressiveStrength"s,
    "MaxAggregateSize"s,
    "AdmixturesDescription"s,
    "Workability"s,
    "ProtectivePoreRatio"s,
    "WaterImpermeability"s,
    "NominalDiameter"s,
    "NominalLength"s,
    "DynamicViscosity"s,
    "YoungModulus"s,
    "ShearModulus"s,
    "PoissonRatio"s,
    "ThermalExpansionCoefficient"s,
    "YieldStress"s,
    "UltimateStress"s,
    "UltimateStrain"s,
    "HardeningModule"s,
    "ProportionalStress"s,
    "PlasticStrain"s,
    "Relaxations"s,
    "Benchmark"s,
    "ValueSource"s,
    "DataValue"s,
    "Currency"s,
    "MoveFrom"s,
    "MoveTo"s,
    "PunchList"s,
    "Dimensions"s,
    "ObjectType"s,
    "BenchmarkValues"s,
    "ResultValues"s,
    "ObjectiveQualifier"s,
    "UserDefinedQualifier"s,
    "BasisCurve"s,
    "Distance"s,
    "RepeatFactor"s,
    "VisibleTransmittance"s,
    "SolarTransmittance"s,
    "ThermalIrTransmittance"s,
    "ThermalIrEmissivityBack"s,
    "ThermalIrEmissivityFront"s,
    "VisibleReflectanceBack"s,
    "VisibleReflectanceFront"s,
    "SolarReflectanceFront"s,
    "SolarReflectanceBack"s,
    "ActionID"s,
    "Id"s,
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
    "LifeCyclePhase"s,
    "FrameDepth"s,
    "FrameThickness"s,
    "PermitID"s,
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
    "Usage"s,
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
    "Points"s,
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
    "ProcedureID"s,
    "ProcedureType"s,
    "UserDefinedProcedureType"s,
    "ObjectPlacement"s,
    "Representation"s,
    "Representations"s,
    "SpecificHeatCapacity"s,
    "N20Content"s,
    "COContent"s,
    "CO2Content"s,
    "ProfileType"s,
    "ProfileName"s,
    "ProfileDefinition"s,
    "LongName"s,
    "Phase"s,
    "RepresentationContexts"s,
    "UnitsInContext"s,
    "Records"s,
    "UpperBoundValue"s,
    "LowerBoundValue"s,
    "RelatedProperties"s,
    "DependingProperty"s,
    "DependantProperty"s,
    "Expression"s,
    "EnumerationValues"s,
    "EnumerationReference"s,
    "PropertyReference"s,
    "NominalValue"s,
    "DefiningValues"s,
    "DefinedValues"s,
    "DefiningUnit"s,
    "DefinedUnit"s,
    "ProxyType"s,
    "AreaValue"s,
    "CountValue"s,
    "LengthValue"s,
    "TimeValue"s,
    "VolumeValue"s,
    "WeightValue"s,
    "ShapeType"s,
    "WeightsData"s,
    "InnerFilletRadius"s,
    "OuterFilletRadius"s,
    "U1"s,
    "V1"s,
    "U2"s,
    "V2"s,
    "Usense"s,
    "Vsense"s,
    "ReferencedDocument"s,
    "ReferencingValues"s,
    "TimeStep"s,
    "TotalCrossSectionArea"s,
    "SteelGrade"s,
    "BarSurface"s,
    "EffectiveDepth"s,
    "NominalBarDiameter"s,
    "BarCount"s,
    "DefinitionType"s,
    "ReinforcementSectionDefinitions"s,
    "BarLength"s,
    "BarRole"s,
    "MeshLength"s,
    "MeshWidth"s,
    "LongitudinalBarNominalDiameter"s,
    "TransverseBarNominalDiameter"s,
    "LongitudinalBarCrossSectionArea"s,
    "TransverseBarCrossSectionArea"s,
    "LongitudinalBarSpacing"s,
    "TransverseBarSpacing"s,
    "RelatedObjects"s,
    "RelatedObjectsType"s,
    "TimeForTask"s,
    "RelatingActor"s,
    "ActingRole"s,
    "RelatingControl"s,
    "RelatingGroup"s,
    "RelatingProcess"s,
    "QuantityInProcess"s,
    "RelatingProduct"s,
    "RelatingResource"s,
    "RelatingAppliedValue"s,
    "RelatingClassification"s,
    "Intent"s,
    "RelatingLibrary"s,
    "RelatingMaterial"s,
    "RelatingProfileProperties"s,
    "ProfileSectionLocation"s,
    "ProfileOrientation"s,
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
    "RelatedStructuralMember"s,
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
    "RelatedSpace"s,
    "RelatingObject"s,
    "RelatingPropertyDefinition"s,
    "RelatingType"s,
    "RelatingOpeningElement"s,
    "RelatedBuildingElement"s,
    "RelatedControlElements"s,
    "RelatingFlowElement"s,
    "DailyInteraction"s,
    "ImportanceRating"s,
    "LocationOfInteraction"s,
    "RelatedSpaceProgram"s,
    "RelatingSpaceProgram"s,
    "OverridingProperties"s,
    "RelatedFeatureElement"s,
    "RelatedProcess"s,
    "TimeLag"s,
    "SequenceType"s,
    "RelatingSystem"s,
    "RelatedBuildings"s,
    "RelatingSpace"s,
    "PhysicalOrVirtualBoundary"s,
    "InternalOrExternalBoundary"s,
    "RelatedOpeningElement"s,
    "RelaxationValue"s,
    "InitialStress"s,
    "ContextOfItems"s,
    "RepresentationIdentifier"s,
    "RepresentationType"s,
    "Items"s,
    "ContextIdentifier"s,
    "ContextType"s,
    "MappingOrigin"s,
    "MappedRepresentation"s,
    "Angle"s,
    "RibHeight"s,
    "RibWidth"s,
    "RibSpacing"s,
    "Direction"s,
    "BottomRadius"s,
    "GlobalId"s,
    "OwnerHistory"s,
    "RoundingRadius"s,
    "Prefix"s,
    "ActualStart"s,
    "EarlyStart"s,
    "LateStart"s,
    "ScheduleStart"s,
    "ActualFinish"s,
    "EarlyFinish"s,
    "LateFinish"s,
    "ScheduleFinish"s,
    "ScheduleDuration"s,
    "ActualDuration"s,
    "RemainingTime"s,
    "FreeFloat"s,
    "TotalFloat"s,
    "IsCritical"s,
    "StatusTime"s,
    "StartFloat"s,
    "FinishFloat"s,
    "Completion"s,
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
    "ServiceLifeType"s,
    "ServiceLifeDuration"s,
    "UpperValue"s,
    "MostUsedValue"s,
    "LowerValue"s,
    "ShapeRepresentations"s,
    "ProductDefinitional"s,
    "PartOfProductDefinitionShape"s,
    "SbsmBoundary"s,
    "RefLatitude"s,
    "RefLongitude"s,
    "RefElevation"s,
    "LandTitleNumber"s,
    "SiteAddress"s,
    "SlippageX"s,
    "SlippageY"s,
    "SlippageZ"s,
    "IsAttenuating"s,
    "SoundScale"s,
    "SoundValues"s,
    "SoundLevelTimeSeries"s,
    "Frequency"s,
    "SoundLevelSingleValue"s,
    "InteriorOrExteriorSpace"s,
    "ElevationWithFlooring"s,
    "SpaceProgramIdentifier"s,
    "MaxRequiredArea"s,
    "MinRequiredArea"s,
    "RequestedLocation"s,
    "StandardRequiredArea"s,
    "ApplicableValueRatio"s,
    "ThermalLoadSource"s,
    "SourceDescription"s,
    "MaximumValue"s,
    "MinimumValue"s,
    "ThermalLoadTimeSeriesValues"s,
    "UserDefinedThermalLoadSource"s,
    "ThermalLoadType"s,
    "NumberOfRiser"s,
    "NumberOfTreads"s,
    "RiserHeight"s,
    "TreadLength"s,
    "DestabilizingLoad"s,
    "CausedBy"s,
    "AppliedLoad"s,
    "OrientationOf2DPlane"s,
    "LoadedBy"s,
    "HasResults"s,
    "ProjectedOrTrue"s,
    "VaryingAppliedLoadLocation"s,
    "SubsequentAppliedLoads"s,
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
    "DeltaT_Constant"s,
    "DeltaT_Y"s,
    "DeltaT_Z"s,
    "TorsionalConstantX"s,
    "MomentOfInertiaYZ"s,
    "MomentOfInertiaY"s,
    "MomentOfInertiaZ"s,
    "WarpingConstant"s,
    "ShearCentreZ"s,
    "ShearCentreY"s,
    "ShearDeformationAreaZ"s,
    "ShearDeformationAreaY"s,
    "MaximumSectionModulusY"s,
    "MinimumSectionModulusY"s,
    "MaximumSectionModulusZ"s,
    "MinimumSectionModulusZ"s,
    "TorsionalSectionModulus"s,
    "TheoryType"s,
    "ResultForLoadGroup"s,
    "IsLinear"s,
    "ShearAreaZ"s,
    "ShearAreaY"s,
    "PlasticShapeFactorY"s,
    "PlasticShapeFactorZ"s,
    "SubsequentThickness"s,
    "VaryingThicknessLocation"s,
    "SubContractor"s,
    "JobDescription"s,
    "ParentEdge"s,
    "Directrix"s,
    "StartParam"s,
    "EndParam"s,
    "ReferenceSurface"s,
    "AxisPosition"s,
    "Side"s,
    "DiffuseTransmissionColour"s,
    "DiffuseReflectionColour"s,
    "TransmissionColour"s,
    "ReflectanceColour"s,
    "RefractionIndex"s,
    "DispersionFactor"s,
    "Transparency"s,
    "DiffuseColour"s,
    "ReflectionColour"s,
    "SpecularColour"s,
    "SpecularHighlight"s,
    "ReflectanceMethod"s,
    "SurfaceColour"s,
    "Textures"s,
    "RepeatS"s,
    "RepeatT"s,
    "TextureType"s,
    "TextureTransform"s,
    "SweptArea"s,
    "InnerRadius"s,
    "SweptCurve"s,
    "StyleOfSymbol"s,
    "FlangeWidth"s,
    "FlangeEdgeRadius"s,
    "WebEdgeRadius"s,
    "WebSlope"s,
    "FlangeSlope"s,
    "Rows"s,
    "RowCells"s,
    "IsHeading"s,
    "TaskId"s,
    "WorkMethod"s,
    "IsMilestone"s,
    "Priority"s,
    "TelephoneNumbers"s,
    "FacsimileNumbers"s,
    "PagerNumber"s,
    "ElectronicMailAddresses"s,
    "WWWHomePageURL"s,
    "TensionForce"s,
    "PreStress"s,
    "FrictionCoefficient"s,
    "AnchorageSlip"s,
    "MinCurvatureRadius"s,
    "AnnotatedCurve"s,
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
    "BoxHeight"s,
    "BoxWidth"s,
    "BoxSlantAngle"s,
    "BoxRotateAngle"s,
    "CharacterSpacing"s,
    "Mode"s,
    "Parameter"s,
    "TextureMaps"s,
    "BoilingPoint"s,
    "FreezingPoint"s,
    "ThermalConductivity"s,
    "StartTime"s,
    "EndTime"s,
    "TimeSeriesDataType"s,
    "DataOrigin"s,
    "UserDefinedDataOrigin"s,
    "ReferencedTimeSeries"s,
    "TimeSeriesReferences"s,
    "ApplicableDates"s,
    "TimeSeriesScheduleType"s,
    "TimeSeries"s,
    "CapacityByWeight"s,
    "CapacityByNumber"s,
    "BottomXDim"s,
    "TopXDim"s,
    "TopXOffset"s,
    "Trim1"s,
    "Trim2"s,
    "SenseAgreement"s,
    "MasterRepresentation"s,
    "SecondRepeatFactor"s,
    "ApplicableOccurrence"s,
    "HasPropertySets"s,
    "RepresentationMaps"s,
    "Units"s,
    "Magnitude"s,
    "TextureVertices"s,
    "TexturePoints"s,
    "LoopVertex"s,
    "VertexGeometry"s,
    "IntersectingAxes"s,
    "OffsetDistances"s,
    "IsPotable"s,
    "Hardness"s,
    "AlkalinityConcentration"s,
    "AcidityConcentration"s,
    "ImpuritiesContent"s,
    "PHLevel"s,
    "DissolvedSolidsContent"s,
    "MullionThickness"s,
    "FirstTransomOffset"s,
    "SecondTransomOffset"s,
    "FirstMullionOffset"s,
    "SecondMullionOffset"s,
    "Creators"s,
    "Duration"s,
    "FinishTime"s,
    "WorkControlType"s,
    "UserDefinedControlType"s,
    "IsActingUpon"s,
    "OfPerson"s,
    "OfOrganization"s,
    "ContainedInStructure"s,
    "ValuesReferenced"s,
    "ValueOfComponents"s,
    "IsComponentIn"s,
    "Actors"s,
    "IsRelatedWith"s,
    "Relates"s,
    "Contains"s,
    "IsClassifiedItemIn"s,
    "IsClassifyingItemIn"s,
    "UsingCurves"s,
    "ClassifiedAs"s,
    "RelatesConstraints"s,
    "PropertiesForConstraint"s,
    "Aggregates"s,
    "IsAggregatedIn"s,
    "Controls"s,
    "CoversSpaces"s,
    "Covers"s,
    "AnnotatedBySymbols"s,
    "AssignedToFlowElement"s,
    "HasControlElements"s,
    "IsPointedTo"s,
    "IsPointer"s,
    "ReferenceToDocument"s,
    "IsRelatedFromCallout"s,
    "IsRelatedToCallout"s,
    "HasStructuralMember"s,
    "FillsVoids"s,
    "ConnectedTo"s,
    "HasCoverings"s,
    "HasProjections"s,
    "ReferencedInStructures"s,
    "HasPorts"s,
    "HasOpenings"s,
    "IsConnectionRealization"s,
    "ProvidesBoundaries"s,
    "ConnectedFrom"s,
    "ProjectsElements"s,
    "VoidsElements"s,
    "HasSubContexts"s,
    "PartOfW"s,
    "PartOfV"s,
    "PartOfU"s,
    "HasIntersections"s,
    "IsGroupedBy"s,
    "ReferenceIntoLibrary"s,
    "HasRepresentation"s,
    "ToMaterialLayerSet"s,
    "IsDefinedBy"s,
    "HasAssignments"s,
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
    "OperatesOn"s,
    "IsSuccessorFrom"s,
    "IsPredecessorTo"s,
    "ReferencedBy"s,
    "ShapeOfProduct"s,
    "HasShapeAspects"s,
    "PropertyForDependance"s,
    "PropertyDependsOn"s,
    "PropertyDefinitionOf"s,
    "DefinesType"s,
    "RepresentationMap"s,
    "LayerAssignments"s,
    "OfProductRepresentation"s,
    "RepresentationsInContext"s,
    "StyledByItem"s,
    "MapUsage"s,
    "ResourceOf"s,
    "ScheduleTimeControlAssigned"s,
    "OfShapeAspect"s,
    "BoundedBy"s,
    "HasInteractionReqsFrom"s,
    "HasInteractionReqsTo"s,
    "ReferencesElements"s,
    "ServicedBySystems"s,
    "ContainsElements"s,
    "AssignedToStructuralItem"s,
    "ConnectsStructuralMembers"s,
    "AssignedStructuralActivity"s,
    "SourceOfResultGroup"s,
    "LoadGroupFor"s,
    "ReferencesElement"s,
    "ConnectedBy"s,
    "Causes"s,
    "ResultGroupFor"s,
    "ServicesBuildings"s,
    "OfTable"s,
    "AnnotatedSurface"s,
    "DocumentedBy"s,
    "ObjectTypeOf"s,
    "IFC2X3"s};

class IFC2X3_instance_factory : public IfcParse::instance_factory {
  virtual IfcUtil::IfcBaseClass *
  operator()(const IfcParse::declaration *decl,
             IfcEntityInstanceData &&data) const {
    switch (decl->index_in_schema()) {
    case 0:
      return new ::Ifc2x3::Ifc2DCompositeCurve(std::move(data));
    case 1:
      return new ::Ifc2x3::IfcAbsorbedDoseMeasure(std::move(data));
    case 2:
      return new ::Ifc2x3::IfcAccelerationMeasure(std::move(data));
    case 3:
      return new ::Ifc2x3::IfcActionRequest(std::move(data));
    case 4:
      return new ::Ifc2x3::IfcActionSourceTypeEnum(std::move(data));
    case 5:
      return new ::Ifc2x3::IfcActionTypeEnum(std::move(data));
    case 6:
      return new ::Ifc2x3::IfcActor(std::move(data));
    case 7:
      return new ::Ifc2x3::IfcActorRole(std::move(data));
    case 9:
      return new ::Ifc2x3::IfcActuatorType(std::move(data));
    case 10:
      return new ::Ifc2x3::IfcActuatorTypeEnum(std::move(data));
    case 11:
      return new ::Ifc2x3::IfcAddress(std::move(data));
    case 12:
      return new ::Ifc2x3::IfcAddressTypeEnum(std::move(data));
    case 13:
      return new ::Ifc2x3::IfcAheadOrBehind(std::move(data));
    case 14:
      return new ::Ifc2x3::IfcAirTerminalBoxType(std::move(data));
    case 15:
      return new ::Ifc2x3::IfcAirTerminalBoxTypeEnum(std::move(data));
    case 16:
      return new ::Ifc2x3::IfcAirTerminalType(std::move(data));
    case 17:
      return new ::Ifc2x3::IfcAirTerminalTypeEnum(std::move(data));
    case 18:
      return new ::Ifc2x3::IfcAirToAirHeatRecoveryType(std::move(data));
    case 19:
      return new ::Ifc2x3::IfcAirToAirHeatRecoveryTypeEnum(std::move(data));
    case 20:
      return new ::Ifc2x3::IfcAlarmType(std::move(data));
    case 21:
      return new ::Ifc2x3::IfcAlarmTypeEnum(std::move(data));
    case 22:
      return new ::Ifc2x3::IfcAmountOfSubstanceMeasure(std::move(data));
    case 23:
      return new ::Ifc2x3::IfcAnalysisModelTypeEnum(std::move(data));
    case 24:
      return new ::Ifc2x3::IfcAnalysisTheoryTypeEnum(std::move(data));
    case 25:
      return new ::Ifc2x3::IfcAngularDimension(std::move(data));
    case 26:
      return new ::Ifc2x3::IfcAngularVelocityMeasure(std::move(data));
    case 27:
      return new ::Ifc2x3::IfcAnnotation(std::move(data));
    case 28:
      return new ::Ifc2x3::IfcAnnotationCurveOccurrence(std::move(data));
    case 29:
      return new ::Ifc2x3::IfcAnnotationFillArea(std::move(data));
    case 30:
      return new ::Ifc2x3::IfcAnnotationFillAreaOccurrence(std::move(data));
    case 31:
      return new ::Ifc2x3::IfcAnnotationOccurrence(std::move(data));
    case 32:
      return new ::Ifc2x3::IfcAnnotationSurface(std::move(data));
    case 33:
      return new ::Ifc2x3::IfcAnnotationSurfaceOccurrence(std::move(data));
    case 34:
      return new ::Ifc2x3::IfcAnnotationSymbolOccurrence(std::move(data));
    case 35:
      return new ::Ifc2x3::IfcAnnotationTextOccurrence(std::move(data));
    case 36:
      return new ::Ifc2x3::IfcApplication(std::move(data));
    case 37:
      return new ::Ifc2x3::IfcAppliedValue(std::move(data));
    case 38:
      return new ::Ifc2x3::IfcAppliedValueRelationship(std::move(data));
    case 40:
      return new ::Ifc2x3::IfcApproval(std::move(data));
    case 41:
      return new ::Ifc2x3::IfcApprovalActorRelationship(std::move(data));
    case 42:
      return new ::Ifc2x3::IfcApprovalPropertyRelationship(std::move(data));
    case 43:
      return new ::Ifc2x3::IfcApprovalRelationship(std::move(data));
    case 44:
      return new ::Ifc2x3::IfcArbitraryClosedProfileDef(std::move(data));
    case 45:
      return new ::Ifc2x3::IfcArbitraryOpenProfileDef(std::move(data));
    case 46:
      return new ::Ifc2x3::IfcArbitraryProfileDefWithVoids(std::move(data));
    case 47:
      return new ::Ifc2x3::IfcAreaMeasure(std::move(data));
    case 48:
      return new ::Ifc2x3::IfcArithmeticOperatorEnum(std::move(data));
    case 49:
      return new ::Ifc2x3::IfcAssemblyPlaceEnum(std::move(data));
    case 50:
      return new ::Ifc2x3::IfcAsset(std::move(data));
    case 51:
      return new ::Ifc2x3::IfcAsymmetricIShapeProfileDef(std::move(data));
    case 52:
      return new ::Ifc2x3::IfcAxis1Placement(std::move(data));
    case 54:
      return new ::Ifc2x3::IfcAxis2Placement2D(std::move(data));
    case 55:
      return new ::Ifc2x3::IfcAxis2Placement3D(std::move(data));
    case 56:
      return new ::Ifc2x3::IfcBeam(std::move(data));
    case 57:
      return new ::Ifc2x3::IfcBeamType(std::move(data));
    case 58:
      return new ::Ifc2x3::IfcBeamTypeEnum(std::move(data));
    case 59:
      return new ::Ifc2x3::IfcBenchmarkEnum(std::move(data));
    case 60:
      return new ::Ifc2x3::IfcBezierCurve(std::move(data));
    case 61:
      return new ::Ifc2x3::IfcBlobTexture(std::move(data));
    case 62:
      return new ::Ifc2x3::IfcBlock(std::move(data));
    case 63:
      return new ::Ifc2x3::IfcBoilerType(std::move(data));
    case 64:
      return new ::Ifc2x3::IfcBoilerTypeEnum(std::move(data));
    case 65:
      return new ::Ifc2x3::IfcBoolean(std::move(data));
    case 66:
      return new ::Ifc2x3::IfcBooleanClippingResult(std::move(data));
    case 68:
      return new ::Ifc2x3::IfcBooleanOperator(std::move(data));
    case 69:
      return new ::Ifc2x3::IfcBooleanResult(std::move(data));
    case 70:
      return new ::Ifc2x3::IfcBoundaryCondition(std::move(data));
    case 71:
      return new ::Ifc2x3::IfcBoundaryEdgeCondition(std::move(data));
    case 72:
      return new ::Ifc2x3::IfcBoundaryFaceCondition(std::move(data));
    case 73:
      return new ::Ifc2x3::IfcBoundaryNodeCondition(std::move(data));
    case 74:
      return new ::Ifc2x3::IfcBoundaryNodeConditionWarping(std::move(data));
    case 75:
      return new ::Ifc2x3::IfcBoundedCurve(std::move(data));
    case 76:
      return new ::Ifc2x3::IfcBoundedSurface(std::move(data));
    case 77:
      return new ::Ifc2x3::IfcBoundingBox(std::move(data));
    case 78:
      return new ::Ifc2x3::IfcBoxAlignment(std::move(data));
    case 79:
      return new ::Ifc2x3::IfcBoxedHalfSpace(std::move(data));
    case 80:
      return new ::Ifc2x3::IfcBSplineCurve(std::move(data));
    case 81:
      return new ::Ifc2x3::IfcBSplineCurveForm(std::move(data));
    case 82:
      return new ::Ifc2x3::IfcBuilding(std::move(data));
    case 83:
      return new ::Ifc2x3::IfcBuildingElement(std::move(data));
    case 84:
      return new ::Ifc2x3::IfcBuildingElementComponent(std::move(data));
    case 85:
      return new ::Ifc2x3::IfcBuildingElementPart(std::move(data));
    case 86:
      return new ::Ifc2x3::IfcBuildingElementProxy(std::move(data));
    case 87:
      return new ::Ifc2x3::IfcBuildingElementProxyType(std::move(data));
    case 88:
      return new ::Ifc2x3::IfcBuildingElementProxyTypeEnum(std::move(data));
    case 89:
      return new ::Ifc2x3::IfcBuildingElementType(std::move(data));
    case 90:
      return new ::Ifc2x3::IfcBuildingStorey(std::move(data));
    case 91:
      return new ::Ifc2x3::IfcCableCarrierFittingType(std::move(data));
    case 92:
      return new ::Ifc2x3::IfcCableCarrierFittingTypeEnum(std::move(data));
    case 93:
      return new ::Ifc2x3::IfcCableCarrierSegmentType(std::move(data));
    case 94:
      return new ::Ifc2x3::IfcCableCarrierSegmentTypeEnum(std::move(data));
    case 95:
      return new ::Ifc2x3::IfcCableSegmentType(std::move(data));
    case 96:
      return new ::Ifc2x3::IfcCableSegmentTypeEnum(std::move(data));
    case 97:
      return new ::Ifc2x3::IfcCalendarDate(std::move(data));
    case 98:
      return new ::Ifc2x3::IfcCartesianPoint(std::move(data));
    case 99:
      return new ::Ifc2x3::IfcCartesianTransformationOperator(std::move(data));
    case 100:
      return new ::Ifc2x3::IfcCartesianTransformationOperator2D(
          std::move(data));
    case 101:
      return new ::Ifc2x3::IfcCartesianTransformationOperator2DnonUniform(
          std::move(data));
    case 102:
      return new ::Ifc2x3::IfcCartesianTransformationOperator3D(
          std::move(data));
    case 103:
      return new ::Ifc2x3::IfcCartesianTransformationOperator3DnonUniform(
          std::move(data));
    case 104:
      return new ::Ifc2x3::IfcCenterLineProfileDef(std::move(data));
    case 105:
      return new ::Ifc2x3::IfcChamferEdgeFeature(std::move(data));
    case 106:
      return new ::Ifc2x3::IfcChangeActionEnum(std::move(data));
    case 108:
      return new ::Ifc2x3::IfcChillerType(std::move(data));
    case 109:
      return new ::Ifc2x3::IfcChillerTypeEnum(std::move(data));
    case 110:
      return new ::Ifc2x3::IfcCircle(std::move(data));
    case 111:
      return new ::Ifc2x3::IfcCircleHollowProfileDef(std::move(data));
    case 112:
      return new ::Ifc2x3::IfcCircleProfileDef(std::move(data));
    case 113:
      return new ::Ifc2x3::IfcClassification(std::move(data));
    case 114:
      return new ::Ifc2x3::IfcClassificationItem(std::move(data));
    case 115:
      return new ::Ifc2x3::IfcClassificationItemRelationship(std::move(data));
    case 116:
      return new ::Ifc2x3::IfcClassificationNotation(std::move(data));
    case 117:
      return new ::Ifc2x3::IfcClassificationNotationFacet(std::move(data));
    case 119:
      return new ::Ifc2x3::IfcClassificationReference(std::move(data));
    case 120:
      return new ::Ifc2x3::IfcClosedShell(std::move(data));
    case 121:
      return new ::Ifc2x3::IfcCoilType(std::move(data));
    case 122:
      return new ::Ifc2x3::IfcCoilTypeEnum(std::move(data));
    case 125:
      return new ::Ifc2x3::IfcColourRgb(std::move(data));
    case 126:
      return new ::Ifc2x3::IfcColourSpecification(std::move(data));
    case 127:
      return new ::Ifc2x3::IfcColumn(std::move(data));
    case 128:
      return new ::Ifc2x3::IfcColumnType(std::move(data));
    case 129:
      return new ::Ifc2x3::IfcColumnTypeEnum(std::move(data));
    case 130:
      return new ::Ifc2x3::IfcComplexNumber(std::move(data));
    case 131:
      return new ::Ifc2x3::IfcComplexProperty(std::move(data));
    case 132:
      return new ::Ifc2x3::IfcCompositeCurve(std::move(data));
    case 133:
      return new ::Ifc2x3::IfcCompositeCurveSegment(std::move(data));
    case 134:
      return new ::Ifc2x3::IfcCompositeProfileDef(std::move(data));
    case 135:
      return new ::Ifc2x3::IfcCompoundPlaneAngleMeasure(std::move(data));
    case 136:
      return new ::Ifc2x3::IfcCompressorType(std::move(data));
    case 137:
      return new ::Ifc2x3::IfcCompressorTypeEnum(std::move(data));
    case 138:
      return new ::Ifc2x3::IfcCondenserType(std::move(data));
    case 139:
      return new ::Ifc2x3::IfcCondenserTypeEnum(std::move(data));
    case 140:
      return new ::Ifc2x3::IfcCondition(std::move(data));
    case 141:
      return new ::Ifc2x3::IfcConditionCriterion(std::move(data));
    case 143:
      return new ::Ifc2x3::IfcConic(std::move(data));
    case 144:
      return new ::Ifc2x3::IfcConnectedFaceSet(std::move(data));
    case 145:
      return new ::Ifc2x3::IfcConnectionCurveGeometry(std::move(data));
    case 146:
      return new ::Ifc2x3::IfcConnectionGeometry(std::move(data));
    case 147:
      return new ::Ifc2x3::IfcConnectionPointEccentricity(std::move(data));
    case 148:
      return new ::Ifc2x3::IfcConnectionPointGeometry(std::move(data));
    case 149:
      return new ::Ifc2x3::IfcConnectionPortGeometry(std::move(data));
    case 150:
      return new ::Ifc2x3::IfcConnectionSurfaceGeometry(std::move(data));
    case 151:
      return new ::Ifc2x3::IfcConnectionTypeEnum(std::move(data));
    case 152:
      return new ::Ifc2x3::IfcConstraint(std::move(data));
    case 153:
      return new ::Ifc2x3::IfcConstraintAggregationRelationship(
          std::move(data));
    case 154:
      return new ::Ifc2x3::IfcConstraintClassificationRelationship(
          std::move(data));
    case 155:
      return new ::Ifc2x3::IfcConstraintEnum(std::move(data));
    case 156:
      return new ::Ifc2x3::IfcConstraintRelationship(std::move(data));
    case 157:
      return new ::Ifc2x3::IfcConstructionEquipmentResource(std::move(data));
    case 158:
      return new ::Ifc2x3::IfcConstructionMaterialResource(std::move(data));
    case 159:
      return new ::Ifc2x3::IfcConstructionProductResource(std::move(data));
    case 160:
      return new ::Ifc2x3::IfcConstructionResource(std::move(data));
    case 161:
      return new ::Ifc2x3::IfcContextDependentMeasure(std::move(data));
    case 162:
      return new ::Ifc2x3::IfcContextDependentUnit(std::move(data));
    case 163:
      return new ::Ifc2x3::IfcControl(std::move(data));
    case 164:
      return new ::Ifc2x3::IfcControllerType(std::move(data));
    case 165:
      return new ::Ifc2x3::IfcControllerTypeEnum(std::move(data));
    case 166:
      return new ::Ifc2x3::IfcConversionBasedUnit(std::move(data));
    case 167:
      return new ::Ifc2x3::IfcCooledBeamType(std::move(data));
    case 168:
      return new ::Ifc2x3::IfcCooledBeamTypeEnum(std::move(data));
    case 169:
      return new ::Ifc2x3::IfcCoolingTowerType(std::move(data));
    case 170:
      return new ::Ifc2x3::IfcCoolingTowerTypeEnum(std::move(data));
    case 171:
      return new ::Ifc2x3::IfcCoordinatedUniversalTimeOffset(std::move(data));
    case 172:
      return new ::Ifc2x3::IfcCostItem(std::move(data));
    case 173:
      return new ::Ifc2x3::IfcCostSchedule(std::move(data));
    case 174:
      return new ::Ifc2x3::IfcCostScheduleTypeEnum(std::move(data));
    case 175:
      return new ::Ifc2x3::IfcCostValue(std::move(data));
    case 176:
      return new ::Ifc2x3::IfcCountMeasure(std::move(data));
    case 177:
      return new ::Ifc2x3::IfcCovering(std::move(data));
    case 178:
      return new ::Ifc2x3::IfcCoveringType(std::move(data));
    case 179:
      return new ::Ifc2x3::IfcCoveringTypeEnum(std::move(data));
    case 180:
      return new ::Ifc2x3::IfcCraneRailAShapeProfileDef(std::move(data));
    case 181:
      return new ::Ifc2x3::IfcCraneRailFShapeProfileDef(std::move(data));
    case 182:
      return new ::Ifc2x3::IfcCrewResource(std::move(data));
    case 183:
      return new ::Ifc2x3::IfcCsgPrimitive3D(std::move(data));
    case 185:
      return new ::Ifc2x3::IfcCsgSolid(std::move(data));
    case 186:
      return new ::Ifc2x3::IfcCShapeProfileDef(std::move(data));
    case 187:
      return new ::Ifc2x3::IfcCurrencyEnum(std::move(data));
    case 188:
      return new ::Ifc2x3::IfcCurrencyRelationship(std::move(data));
    case 189:
      return new ::Ifc2x3::IfcCurtainWall(std::move(data));
    case 190:
      return new ::Ifc2x3::IfcCurtainWallType(std::move(data));
    case 191:
      return new ::Ifc2x3::IfcCurtainWallTypeEnum(std::move(data));
    case 192:
      return new ::Ifc2x3::IfcCurvatureMeasure(std::move(data));
    case 193:
      return new ::Ifc2x3::IfcCurve(std::move(data));
    case 194:
      return new ::Ifc2x3::IfcCurveBoundedPlane(std::move(data));
    case 197:
      return new ::Ifc2x3::IfcCurveStyle(std::move(data));
    case 198:
      return new ::Ifc2x3::IfcCurveStyleFont(std::move(data));
    case 199:
      return new ::Ifc2x3::IfcCurveStyleFontAndScaling(std::move(data));
    case 200:
      return new ::Ifc2x3::IfcCurveStyleFontPattern(std::move(data));
    case 202:
      return new ::Ifc2x3::IfcDamperType(std::move(data));
    case 203:
      return new ::Ifc2x3::IfcDamperTypeEnum(std::move(data));
    case 204:
      return new ::Ifc2x3::IfcDataOriginEnum(std::move(data));
    case 205:
      return new ::Ifc2x3::IfcDateAndTime(std::move(data));
    case 207:
      return new ::Ifc2x3::IfcDayInMonthNumber(std::move(data));
    case 208:
      return new ::Ifc2x3::IfcDaylightSavingHour(std::move(data));
    case 209:
      return new ::Ifc2x3::IfcDefinedSymbol(std::move(data));
    case 212:
      return new ::Ifc2x3::IfcDerivedProfileDef(std::move(data));
    case 213:
      return new ::Ifc2x3::IfcDerivedUnit(std::move(data));
    case 214:
      return new ::Ifc2x3::IfcDerivedUnitElement(std::move(data));
    case 215:
      return new ::Ifc2x3::IfcDerivedUnitEnum(std::move(data));
    case 216:
      return new ::Ifc2x3::IfcDescriptiveMeasure(std::move(data));
    case 217:
      return new ::Ifc2x3::IfcDiameterDimension(std::move(data));
    case 218:
      return new ::Ifc2x3::IfcDimensionalExponents(std::move(data));
    case 219:
      return new ::Ifc2x3::IfcDimensionCalloutRelationship(std::move(data));
    case 220:
      return new ::Ifc2x3::IfcDimensionCount(std::move(data));
    case 221:
      return new ::Ifc2x3::IfcDimensionCurve(std::move(data));
    case 222:
      return new ::Ifc2x3::IfcDimensionCurveDirectedCallout(std::move(data));
    case 223:
      return new ::Ifc2x3::IfcDimensionCurveTerminator(std::move(data));
    case 224:
      return new ::Ifc2x3::IfcDimensionExtentUsage(std::move(data));
    case 225:
      return new ::Ifc2x3::IfcDimensionPair(std::move(data));
    case 226:
      return new ::Ifc2x3::IfcDirection(std::move(data));
    case 227:
      return new ::Ifc2x3::IfcDirectionSenseEnum(std::move(data));
    case 228:
      return new ::Ifc2x3::IfcDiscreteAccessory(std::move(data));
    case 229:
      return new ::Ifc2x3::IfcDiscreteAccessoryType(std::move(data));
    case 230:
      return new ::Ifc2x3::IfcDistributionChamberElement(std::move(data));
    case 231:
      return new ::Ifc2x3::IfcDistributionChamberElementType(std::move(data));
    case 232:
      return new ::Ifc2x3::IfcDistributionChamberElementTypeEnum(
          std::move(data));
    case 233:
      return new ::Ifc2x3::IfcDistributionControlElement(std::move(data));
    case 234:
      return new ::Ifc2x3::IfcDistributionControlElementType(std::move(data));
    case 235:
      return new ::Ifc2x3::IfcDistributionElement(std::move(data));
    case 236:
      return new ::Ifc2x3::IfcDistributionElementType(std::move(data));
    case 237:
      return new ::Ifc2x3::IfcDistributionFlowElement(std::move(data));
    case 238:
      return new ::Ifc2x3::IfcDistributionFlowElementType(std::move(data));
    case 239:
      return new ::Ifc2x3::IfcDistributionPort(std::move(data));
    case 240:
      return new ::Ifc2x3::IfcDocumentConfidentialityEnum(std::move(data));
    case 241:
      return new ::Ifc2x3::IfcDocumentElectronicFormat(std::move(data));
    case 242:
      return new ::Ifc2x3::IfcDocumentInformation(std::move(data));
    case 243:
      return new ::Ifc2x3::IfcDocumentInformationRelationship(std::move(data));
    case 244:
      return new ::Ifc2x3::IfcDocumentReference(std::move(data));
    case 246:
      return new ::Ifc2x3::IfcDocumentStatusEnum(std::move(data));
    case 247:
      return new ::Ifc2x3::IfcDoor(std::move(data));
    case 248:
      return new ::Ifc2x3::IfcDoorLiningProperties(std::move(data));
    case 249:
      return new ::Ifc2x3::IfcDoorPanelOperationEnum(std::move(data));
    case 250:
      return new ::Ifc2x3::IfcDoorPanelPositionEnum(std::move(data));
    case 251:
      return new ::Ifc2x3::IfcDoorPanelProperties(std::move(data));
    case 252:
      return new ::Ifc2x3::IfcDoorStyle(std::move(data));
    case 253:
      return new ::Ifc2x3::IfcDoorStyleConstructionEnum(std::move(data));
    case 254:
      return new ::Ifc2x3::IfcDoorStyleOperationEnum(std::move(data));
    case 255:
      return new ::Ifc2x3::IfcDoseEquivalentMeasure(std::move(data));
    case 256:
      return new ::Ifc2x3::IfcDraughtingCallout(std::move(data));
    case 258:
      return new ::Ifc2x3::IfcDraughtingCalloutRelationship(std::move(data));
    case 259:
      return new ::Ifc2x3::IfcDraughtingPreDefinedColour(std::move(data));
    case 260:
      return new ::Ifc2x3::IfcDraughtingPreDefinedCurveFont(std::move(data));
    case 261:
      return new ::Ifc2x3::IfcDraughtingPreDefinedTextFont(std::move(data));
    case 262:
      return new ::Ifc2x3::IfcDuctFittingType(std::move(data));
    case 263:
      return new ::Ifc2x3::IfcDuctFittingTypeEnum(std::move(data));
    case 264:
      return new ::Ifc2x3::IfcDuctSegmentType(std::move(data));
    case 265:
      return new ::Ifc2x3::IfcDuctSegmentTypeEnum(std::move(data));
    case 266:
      return new ::Ifc2x3::IfcDuctSilencerType(std::move(data));
    case 267:
      return new ::Ifc2x3::IfcDuctSilencerTypeEnum(std::move(data));
    case 268:
      return new ::Ifc2x3::IfcDynamicViscosityMeasure(std::move(data));
    case 269:
      return new ::Ifc2x3::IfcEdge(std::move(data));
    case 270:
      return new ::Ifc2x3::IfcEdgeCurve(std::move(data));
    case 271:
      return new ::Ifc2x3::IfcEdgeFeature(std::move(data));
    case 272:
      return new ::Ifc2x3::IfcEdgeLoop(std::move(data));
    case 273:
      return new ::Ifc2x3::IfcElectricalBaseProperties(std::move(data));
    case 274:
      return new ::Ifc2x3::IfcElectricalCircuit(std::move(data));
    case 275:
      return new ::Ifc2x3::IfcElectricalElement(std::move(data));
    case 276:
      return new ::Ifc2x3::IfcElectricApplianceType(std::move(data));
    case 277:
      return new ::Ifc2x3::IfcElectricApplianceTypeEnum(std::move(data));
    case 278:
      return new ::Ifc2x3::IfcElectricCapacitanceMeasure(std::move(data));
    case 279:
      return new ::Ifc2x3::IfcElectricChargeMeasure(std::move(data));
    case 280:
      return new ::Ifc2x3::IfcElectricConductanceMeasure(std::move(data));
    case 281:
      return new ::Ifc2x3::IfcElectricCurrentEnum(std::move(data));
    case 282:
      return new ::Ifc2x3::IfcElectricCurrentMeasure(std::move(data));
    case 283:
      return new ::Ifc2x3::IfcElectricDistributionPoint(std::move(data));
    case 284:
      return new ::Ifc2x3::IfcElectricDistributionPointFunctionEnum(
          std::move(data));
    case 285:
      return new ::Ifc2x3::IfcElectricFlowStorageDeviceType(std::move(data));
    case 286:
      return new ::Ifc2x3::IfcElectricFlowStorageDeviceTypeEnum(
          std::move(data));
    case 287:
      return new ::Ifc2x3::IfcElectricGeneratorType(std::move(data));
    case 288:
      return new ::Ifc2x3::IfcElectricGeneratorTypeEnum(std::move(data));
    case 289:
      return new ::Ifc2x3::IfcElectricHeaterType(std::move(data));
    case 290:
      return new ::Ifc2x3::IfcElectricHeaterTypeEnum(std::move(data));
    case 291:
      return new ::Ifc2x3::IfcElectricMotorType(std::move(data));
    case 292:
      return new ::Ifc2x3::IfcElectricMotorTypeEnum(std::move(data));
    case 293:
      return new ::Ifc2x3::IfcElectricResistanceMeasure(std::move(data));
    case 294:
      return new ::Ifc2x3::IfcElectricTimeControlType(std::move(data));
    case 295:
      return new ::Ifc2x3::IfcElectricTimeControlTypeEnum(std::move(data));
    case 296:
      return new ::Ifc2x3::IfcElectricVoltageMeasure(std::move(data));
    case 297:
      return new ::Ifc2x3::IfcElement(std::move(data));
    case 298:
      return new ::Ifc2x3::IfcElementarySurface(std::move(data));
    case 299:
      return new ::Ifc2x3::IfcElementAssembly(std::move(data));
    case 300:
      return new ::Ifc2x3::IfcElementAssemblyTypeEnum(std::move(data));
    case 301:
      return new ::Ifc2x3::IfcElementComponent(std::move(data));
    case 302:
      return new ::Ifc2x3::IfcElementComponentType(std::move(data));
    case 303:
      return new ::Ifc2x3::IfcElementCompositionEnum(std::move(data));
    case 304:
      return new ::Ifc2x3::IfcElementQuantity(std::move(data));
    case 305:
      return new ::Ifc2x3::IfcElementType(std::move(data));
    case 306:
      return new ::Ifc2x3::IfcEllipse(std::move(data));
    case 307:
      return new ::Ifc2x3::IfcEllipseProfileDef(std::move(data));
    case 308:
      return new ::Ifc2x3::IfcEnergyConversionDevice(std::move(data));
    case 309:
      return new ::Ifc2x3::IfcEnergyConversionDeviceType(std::move(data));
    case 310:
      return new ::Ifc2x3::IfcEnergyMeasure(std::move(data));
    case 311:
      return new ::Ifc2x3::IfcEnergyProperties(std::move(data));
    case 312:
      return new ::Ifc2x3::IfcEnergySequenceEnum(std::move(data));
    case 313:
      return new ::Ifc2x3::IfcEnvironmentalImpactCategoryEnum(std::move(data));
    case 314:
      return new ::Ifc2x3::IfcEnvironmentalImpactValue(std::move(data));
    case 315:
      return new ::Ifc2x3::IfcEquipmentElement(std::move(data));
    case 316:
      return new ::Ifc2x3::IfcEquipmentStandard(std::move(data));
    case 317:
      return new ::Ifc2x3::IfcEvaporativeCoolerType(std::move(data));
    case 318:
      return new ::Ifc2x3::IfcEvaporativeCoolerTypeEnum(std::move(data));
    case 319:
      return new ::Ifc2x3::IfcEvaporatorType(std::move(data));
    case 320:
      return new ::Ifc2x3::IfcEvaporatorTypeEnum(std::move(data));
    case 321:
      return new ::Ifc2x3::IfcExtendedMaterialProperties(std::move(data));
    case 322:
      return new ::Ifc2x3::IfcExternallyDefinedHatchStyle(std::move(data));
    case 323:
      return new ::Ifc2x3::IfcExternallyDefinedSurfaceStyle(std::move(data));
    case 324:
      return new ::Ifc2x3::IfcExternallyDefinedSymbol(std::move(data));
    case 325:
      return new ::Ifc2x3::IfcExternallyDefinedTextFont(std::move(data));
    case 326:
      return new ::Ifc2x3::IfcExternalReference(std::move(data));
    case 327:
      return new ::Ifc2x3::IfcExtrudedAreaSolid(std::move(data));
    case 328:
      return new ::Ifc2x3::IfcFace(std::move(data));
    case 329:
      return new ::Ifc2x3::IfcFaceBasedSurfaceModel(std::move(data));
    case 330:
      return new ::Ifc2x3::IfcFaceBound(std::move(data));
    case 331:
      return new ::Ifc2x3::IfcFaceOuterBound(std::move(data));
    case 332:
      return new ::Ifc2x3::IfcFaceSurface(std::move(data));
    case 333:
      return new ::Ifc2x3::IfcFacetedBrep(std::move(data));
    case 334:
      return new ::Ifc2x3::IfcFacetedBrepWithVoids(std::move(data));
    case 335:
      return new ::Ifc2x3::IfcFailureConnectionCondition(std::move(data));
    case 336:
      return new ::Ifc2x3::IfcFanType(std::move(data));
    case 337:
      return new ::Ifc2x3::IfcFanTypeEnum(std::move(data));
    case 338:
      return new ::Ifc2x3::IfcFastener(std::move(data));
    case 339:
      return new ::Ifc2x3::IfcFastenerType(std::move(data));
    case 340:
      return new ::Ifc2x3::IfcFeatureElement(std::move(data));
    case 341:
      return new ::Ifc2x3::IfcFeatureElementAddition(std::move(data));
    case 342:
      return new ::Ifc2x3::IfcFeatureElementSubtraction(std::move(data));
    case 343:
      return new ::Ifc2x3::IfcFillAreaStyle(std::move(data));
    case 344:
      return new ::Ifc2x3::IfcFillAreaStyleHatching(std::move(data));
    case 345:
      return new ::Ifc2x3::IfcFillAreaStyleTiles(std::move(data));
    case 347:
      return new ::Ifc2x3::IfcFillAreaStyleTileSymbolWithStyle(std::move(data));
    case 349:
      return new ::Ifc2x3::IfcFilterType(std::move(data));
    case 350:
      return new ::Ifc2x3::IfcFilterTypeEnum(std::move(data));
    case 351:
      return new ::Ifc2x3::IfcFireSuppressionTerminalType(std::move(data));
    case 352:
      return new ::Ifc2x3::IfcFireSuppressionTerminalTypeEnum(std::move(data));
    case 353:
      return new ::Ifc2x3::IfcFlowController(std::move(data));
    case 354:
      return new ::Ifc2x3::IfcFlowControllerType(std::move(data));
    case 355:
      return new ::Ifc2x3::IfcFlowDirectionEnum(std::move(data));
    case 356:
      return new ::Ifc2x3::IfcFlowFitting(std::move(data));
    case 357:
      return new ::Ifc2x3::IfcFlowFittingType(std::move(data));
    case 358:
      return new ::Ifc2x3::IfcFlowInstrumentType(std::move(data));
    case 359:
      return new ::Ifc2x3::IfcFlowInstrumentTypeEnum(std::move(data));
    case 360:
      return new ::Ifc2x3::IfcFlowMeterType(std::move(data));
    case 361:
      return new ::Ifc2x3::IfcFlowMeterTypeEnum(std::move(data));
    case 362:
      return new ::Ifc2x3::IfcFlowMovingDevice(std::move(data));
    case 363:
      return new ::Ifc2x3::IfcFlowMovingDeviceType(std::move(data));
    case 364:
      return new ::Ifc2x3::IfcFlowSegment(std::move(data));
    case 365:
      return new ::Ifc2x3::IfcFlowSegmentType(std::move(data));
    case 366:
      return new ::Ifc2x3::IfcFlowStorageDevice(std::move(data));
    case 367:
      return new ::Ifc2x3::IfcFlowStorageDeviceType(std::move(data));
    case 368:
      return new ::Ifc2x3::IfcFlowTerminal(std::move(data));
    case 369:
      return new ::Ifc2x3::IfcFlowTerminalType(std::move(data));
    case 370:
      return new ::Ifc2x3::IfcFlowTreatmentDevice(std::move(data));
    case 371:
      return new ::Ifc2x3::IfcFlowTreatmentDeviceType(std::move(data));
    case 372:
      return new ::Ifc2x3::IfcFluidFlowProperties(std::move(data));
    case 373:
      return new ::Ifc2x3::IfcFontStyle(std::move(data));
    case 374:
      return new ::Ifc2x3::IfcFontVariant(std::move(data));
    case 375:
      return new ::Ifc2x3::IfcFontWeight(std::move(data));
    case 376:
      return new ::Ifc2x3::IfcFooting(std::move(data));
    case 377:
      return new ::Ifc2x3::IfcFootingTypeEnum(std::move(data));
    case 378:
      return new ::Ifc2x3::IfcForceMeasure(std::move(data));
    case 379:
      return new ::Ifc2x3::IfcFrequencyMeasure(std::move(data));
    case 380:
      return new ::Ifc2x3::IfcFuelProperties(std::move(data));
    case 381:
      return new ::Ifc2x3::IfcFurnishingElement(std::move(data));
    case 382:
      return new ::Ifc2x3::IfcFurnishingElementType(std::move(data));
    case 383:
      return new ::Ifc2x3::IfcFurnitureStandard(std::move(data));
    case 384:
      return new ::Ifc2x3::IfcFurnitureType(std::move(data));
    case 385:
      return new ::Ifc2x3::IfcGasTerminalType(std::move(data));
    case 386:
      return new ::Ifc2x3::IfcGasTerminalTypeEnum(std::move(data));
    case 387:
      return new ::Ifc2x3::IfcGeneralMaterialProperties(std::move(data));
    case 388:
      return new ::Ifc2x3::IfcGeneralProfileProperties(std::move(data));
    case 389:
      return new ::Ifc2x3::IfcGeometricCurveSet(std::move(data));
    case 390:
      return new ::Ifc2x3::IfcGeometricProjectionEnum(std::move(data));
    case 391:
      return new ::Ifc2x3::IfcGeometricRepresentationContext(std::move(data));
    case 392:
      return new ::Ifc2x3::IfcGeometricRepresentationItem(std::move(data));
    case 393:
      return new ::Ifc2x3::IfcGeometricRepresentationSubContext(
          std::move(data));
    case 394:
      return new ::Ifc2x3::IfcGeometricSet(std::move(data));
    case 396:
      return new ::Ifc2x3::IfcGloballyUniqueId(std::move(data));
    case 397:
      return new ::Ifc2x3::IfcGlobalOrLocalEnum(std::move(data));
    case 398:
      return new ::Ifc2x3::IfcGrid(std::move(data));
    case 399:
      return new ::Ifc2x3::IfcGridAxis(std::move(data));
    case 400:
      return new ::Ifc2x3::IfcGridPlacement(std::move(data));
    case 401:
      return new ::Ifc2x3::IfcGroup(std::move(data));
    case 402:
      return new ::Ifc2x3::IfcHalfSpaceSolid(std::move(data));
    case 404:
      return new ::Ifc2x3::IfcHeatExchangerType(std::move(data));
    case 405:
      return new ::Ifc2x3::IfcHeatExchangerTypeEnum(std::move(data));
    case 406:
      return new ::Ifc2x3::IfcHeatFluxDensityMeasure(std::move(data));
    case 407:
      return new ::Ifc2x3::IfcHeatingValueMeasure(std::move(data));
    case 408:
      return new ::Ifc2x3::IfcHourInDay(std::move(data));
    case 409:
      return new ::Ifc2x3::IfcHumidifierType(std::move(data));
    case 410:
      return new ::Ifc2x3::IfcHumidifierTypeEnum(std::move(data));
    case 411:
      return new ::Ifc2x3::IfcHygroscopicMaterialProperties(std::move(data));
    case 412:
      return new ::Ifc2x3::IfcIdentifier(std::move(data));
    case 413:
      return new ::Ifc2x3::IfcIlluminanceMeasure(std::move(data));
    case 414:
      return new ::Ifc2x3::IfcImageTexture(std::move(data));
    case 415:
      return new ::Ifc2x3::IfcInductanceMeasure(std::move(data));
    case 416:
      return new ::Ifc2x3::IfcInteger(std::move(data));
    case 417:
      return new ::Ifc2x3::IfcIntegerCountRateMeasure(std::move(data));
    case 418:
      return new ::Ifc2x3::IfcInternalOrExternalEnum(std::move(data));
    case 419:
      return new ::Ifc2x3::IfcInventory(std::move(data));
    case 420:
      return new ::Ifc2x3::IfcInventoryTypeEnum(std::move(data));
    case 421:
      return new ::Ifc2x3::IfcIonConcentrationMeasure(std::move(data));
    case 422:
      return new ::Ifc2x3::IfcIrregularTimeSeries(std::move(data));
    case 423:
      return new ::Ifc2x3::IfcIrregularTimeSeriesValue(std::move(data));
    case 424:
      return new ::Ifc2x3::IfcIShapeProfileDef(std::move(data));
    case 425:
      return new ::Ifc2x3::IfcIsothermalMoistureCapacityMeasure(
          std::move(data));
    case 426:
      return new ::Ifc2x3::IfcJunctionBoxType(std::move(data));
    case 427:
      return new ::Ifc2x3::IfcJunctionBoxTypeEnum(std::move(data));
    case 428:
      return new ::Ifc2x3::IfcKinematicViscosityMeasure(std::move(data));
    case 429:
      return new ::Ifc2x3::IfcLabel(std::move(data));
    case 430:
      return new ::Ifc2x3::IfcLaborResource(std::move(data));
    case 431:
      return new ::Ifc2x3::IfcLampType(std::move(data));
    case 432:
      return new ::Ifc2x3::IfcLampTypeEnum(std::move(data));
    case 434:
      return new ::Ifc2x3::IfcLayerSetDirectionEnum(std::move(data));
    case 435:
      return new ::Ifc2x3::IfcLengthMeasure(std::move(data));
    case 436:
      return new ::Ifc2x3::IfcLibraryInformation(std::move(data));
    case 437:
      return new ::Ifc2x3::IfcLibraryReference(std::move(data));
    case 439:
      return new ::Ifc2x3::IfcLightDistributionCurveEnum(std::move(data));
    case 440:
      return new ::Ifc2x3::IfcLightDistributionData(std::move(data));
    case 442:
      return new ::Ifc2x3::IfcLightEmissionSourceEnum(std::move(data));
    case 443:
      return new ::Ifc2x3::IfcLightFixtureType(std::move(data));
    case 444:
      return new ::Ifc2x3::IfcLightFixtureTypeEnum(std::move(data));
    case 445:
      return new ::Ifc2x3::IfcLightIntensityDistribution(std::move(data));
    case 446:
      return new ::Ifc2x3::IfcLightSource(std::move(data));
    case 447:
      return new ::Ifc2x3::IfcLightSourceAmbient(std::move(data));
    case 448:
      return new ::Ifc2x3::IfcLightSourceDirectional(std::move(data));
    case 449:
      return new ::Ifc2x3::IfcLightSourceGoniometric(std::move(data));
    case 450:
      return new ::Ifc2x3::IfcLightSourcePositional(std::move(data));
    case 451:
      return new ::Ifc2x3::IfcLightSourceSpot(std::move(data));
    case 452:
      return new ::Ifc2x3::IfcLine(std::move(data));
    case 453:
      return new ::Ifc2x3::IfcLinearDimension(std::move(data));
    case 454:
      return new ::Ifc2x3::IfcLinearForceMeasure(std::move(data));
    case 455:
      return new ::Ifc2x3::IfcLinearMomentMeasure(std::move(data));
    case 456:
      return new ::Ifc2x3::IfcLinearStiffnessMeasure(std::move(data));
    case 457:
      return new ::Ifc2x3::IfcLinearVelocityMeasure(std::move(data));
    case 458:
      return new ::Ifc2x3::IfcLoadGroupTypeEnum(std::move(data));
    case 459:
      return new ::Ifc2x3::IfcLocalPlacement(std::move(data));
    case 460:
      return new ::Ifc2x3::IfcLocalTime(std::move(data));
    case 461:
      return new ::Ifc2x3::IfcLogical(std::move(data));
    case 462:
      return new ::Ifc2x3::IfcLogicalOperatorEnum(std::move(data));
    case 463:
      return new ::Ifc2x3::IfcLoop(std::move(data));
    case 464:
      return new ::Ifc2x3::IfcLShapeProfileDef(std::move(data));
    case 465:
      return new ::Ifc2x3::IfcLuminousFluxMeasure(std::move(data));
    case 466:
      return new ::Ifc2x3::IfcLuminousIntensityDistributionMeasure(
          std::move(data));
    case 467:
      return new ::Ifc2x3::IfcLuminousIntensityMeasure(std::move(data));
    case 468:
      return new ::Ifc2x3::IfcMagneticFluxDensityMeasure(std::move(data));
    case 469:
      return new ::Ifc2x3::IfcMagneticFluxMeasure(std::move(data));
    case 470:
      return new ::Ifc2x3::IfcManifoldSolidBrep(std::move(data));
    case 471:
      return new ::Ifc2x3::IfcMappedItem(std::move(data));
    case 472:
      return new ::Ifc2x3::IfcMassDensityMeasure(std::move(data));
    case 473:
      return new ::Ifc2x3::IfcMassFlowRateMeasure(std::move(data));
    case 474:
      return new ::Ifc2x3::IfcMassMeasure(std::move(data));
    case 475:
      return new ::Ifc2x3::IfcMassPerLengthMeasure(std::move(data));
    case 476:
      return new ::Ifc2x3::IfcMaterial(std::move(data));
    case 477:
      return new ::Ifc2x3::IfcMaterialClassificationRelationship(
          std::move(data));
    case 478:
      return new ::Ifc2x3::IfcMaterialDefinitionRepresentation(std::move(data));
    case 479:
      return new ::Ifc2x3::IfcMaterialLayer(std::move(data));
    case 480:
      return new ::Ifc2x3::IfcMaterialLayerSet(std::move(data));
    case 481:
      return new ::Ifc2x3::IfcMaterialLayerSetUsage(std::move(data));
    case 482:
      return new ::Ifc2x3::IfcMaterialList(std::move(data));
    case 483:
      return new ::Ifc2x3::IfcMaterialProperties(std::move(data));
    case 486:
      return new ::Ifc2x3::IfcMeasureWithUnit(std::move(data));
    case 487:
      return new ::Ifc2x3::IfcMechanicalConcreteMaterialProperties(
          std::move(data));
    case 488:
      return new ::Ifc2x3::IfcMechanicalFastener(std::move(data));
    case 489:
      return new ::Ifc2x3::IfcMechanicalFastenerType(std::move(data));
    case 490:
      return new ::Ifc2x3::IfcMechanicalMaterialProperties(std::move(data));
    case 491:
      return new ::Ifc2x3::IfcMechanicalSteelMaterialProperties(
          std::move(data));
    case 492:
      return new ::Ifc2x3::IfcMember(std::move(data));
    case 493:
      return new ::Ifc2x3::IfcMemberType(std::move(data));
    case 494:
      return new ::Ifc2x3::IfcMemberTypeEnum(std::move(data));
    case 495:
      return new ::Ifc2x3::IfcMetric(std::move(data));
    case 497:
      return new ::Ifc2x3::IfcMinuteInHour(std::move(data));
    case 498:
      return new ::Ifc2x3::IfcModulusOfElasticityMeasure(std::move(data));
    case 499:
      return new ::Ifc2x3::IfcModulusOfLinearSubgradeReactionMeasure(
          std::move(data));
    case 500:
      return new ::Ifc2x3::IfcModulusOfRotationalSubgradeReactionMeasure(
          std::move(data));
    case 501:
      return new ::Ifc2x3::IfcModulusOfSubgradeReactionMeasure(std::move(data));
    case 502:
      return new ::Ifc2x3::IfcMoistureDiffusivityMeasure(std::move(data));
    case 503:
      return new ::Ifc2x3::IfcMolecularWeightMeasure(std::move(data));
    case 504:
      return new ::Ifc2x3::IfcMomentOfInertiaMeasure(std::move(data));
    case 505:
      return new ::Ifc2x3::IfcMonetaryMeasure(std::move(data));
    case 506:
      return new ::Ifc2x3::IfcMonetaryUnit(std::move(data));
    case 507:
      return new ::Ifc2x3::IfcMonthInYearNumber(std::move(data));
    case 508:
      return new ::Ifc2x3::IfcMotorConnectionType(std::move(data));
    case 509:
      return new ::Ifc2x3::IfcMotorConnectionTypeEnum(std::move(data));
    case 510:
      return new ::Ifc2x3::IfcMove(std::move(data));
    case 511:
      return new ::Ifc2x3::IfcNamedUnit(std::move(data));
    case 512:
      return new ::Ifc2x3::IfcNormalisedRatioMeasure(std::move(data));
    case 513:
      return new ::Ifc2x3::IfcNullStyle(std::move(data));
    case 514:
      return new ::Ifc2x3::IfcNumericMeasure(std::move(data));
    case 515:
      return new ::Ifc2x3::IfcObject(std::move(data));
    case 516:
      return new ::Ifc2x3::IfcObjectDefinition(std::move(data));
    case 517:
      return new ::Ifc2x3::IfcObjective(std::move(data));
    case 518:
      return new ::Ifc2x3::IfcObjectiveEnum(std::move(data));
    case 519:
      return new ::Ifc2x3::IfcObjectPlacement(std::move(data));
    case 521:
      return new ::Ifc2x3::IfcObjectTypeEnum(std::move(data));
    case 522:
      return new ::Ifc2x3::IfcOccupant(std::move(data));
    case 523:
      return new ::Ifc2x3::IfcOccupantTypeEnum(std::move(data));
    case 524:
      return new ::Ifc2x3::IfcOffsetCurve2D(std::move(data));
    case 525:
      return new ::Ifc2x3::IfcOffsetCurve3D(std::move(data));
    case 526:
      return new ::Ifc2x3::IfcOneDirectionRepeatFactor(std::move(data));
    case 527:
      return new ::Ifc2x3::IfcOpeningElement(std::move(data));
    case 528:
      return new ::Ifc2x3::IfcOpenShell(std::move(data));
    case 529:
      return new ::Ifc2x3::IfcOpticalMaterialProperties(std::move(data));
    case 530:
      return new ::Ifc2x3::IfcOrderAction(std::move(data));
    case 531:
      return new ::Ifc2x3::IfcOrganization(std::move(data));
    case 532:
      return new ::Ifc2x3::IfcOrganizationRelationship(std::move(data));
    case 534:
      return new ::Ifc2x3::IfcOrientedEdge(std::move(data));
    case 535:
      return new ::Ifc2x3::IfcOutletType(std::move(data));
    case 536:
      return new ::Ifc2x3::IfcOutletTypeEnum(std::move(data));
    case 537:
      return new ::Ifc2x3::IfcOwnerHistory(std::move(data));
    case 538:
      return new ::Ifc2x3::IfcParameterizedProfileDef(std::move(data));
    case 539:
      return new ::Ifc2x3::IfcParameterValue(std::move(data));
    case 540:
      return new ::Ifc2x3::IfcPath(std::move(data));
    case 541:
      return new ::Ifc2x3::IfcPerformanceHistory(std::move(data));
    case 542:
      return new ::Ifc2x3::IfcPermeableCoveringOperationEnum(std::move(data));
    case 543:
      return new ::Ifc2x3::IfcPermeableCoveringProperties(std::move(data));
    case 544:
      return new ::Ifc2x3::IfcPermit(std::move(data));
    case 545:
      return new ::Ifc2x3::IfcPerson(std::move(data));
    case 546:
      return new ::Ifc2x3::IfcPersonAndOrganization(std::move(data));
    case 547:
      return new ::Ifc2x3::IfcPHMeasure(std::move(data));
    case 548:
      return new ::Ifc2x3::IfcPhysicalComplexQuantity(std::move(data));
    case 549:
      return new ::Ifc2x3::IfcPhysicalOrVirtualEnum(std::move(data));
    case 550:
      return new ::Ifc2x3::IfcPhysicalQuantity(std::move(data));
    case 551:
      return new ::Ifc2x3::IfcPhysicalSimpleQuantity(std::move(data));
    case 552:
      return new ::Ifc2x3::IfcPile(std::move(data));
    case 553:
      return new ::Ifc2x3::IfcPileConstructionEnum(std::move(data));
    case 554:
      return new ::Ifc2x3::IfcPileTypeEnum(std::move(data));
    case 555:
      return new ::Ifc2x3::IfcPipeFittingType(std::move(data));
    case 556:
      return new ::Ifc2x3::IfcPipeFittingTypeEnum(std::move(data));
    case 557:
      return new ::Ifc2x3::IfcPipeSegmentType(std::move(data));
    case 558:
      return new ::Ifc2x3::IfcPipeSegmentTypeEnum(std::move(data));
    case 559:
      return new ::Ifc2x3::IfcPixelTexture(std::move(data));
    case 560:
      return new ::Ifc2x3::IfcPlacement(std::move(data));
    case 561:
      return new ::Ifc2x3::IfcPlanarBox(std::move(data));
    case 562:
      return new ::Ifc2x3::IfcPlanarExtent(std::move(data));
    case 563:
      return new ::Ifc2x3::IfcPlanarForceMeasure(std::move(data));
    case 564:
      return new ::Ifc2x3::IfcPlane(std::move(data));
    case 565:
      return new ::Ifc2x3::IfcPlaneAngleMeasure(std::move(data));
    case 566:
      return new ::Ifc2x3::IfcPlate(std::move(data));
    case 567:
      return new ::Ifc2x3::IfcPlateType(std::move(data));
    case 568:
      return new ::Ifc2x3::IfcPlateTypeEnum(std::move(data));
    case 569:
      return new ::Ifc2x3::IfcPoint(std::move(data));
    case 570:
      return new ::Ifc2x3::IfcPointOnCurve(std::move(data));
    case 571:
      return new ::Ifc2x3::IfcPointOnSurface(std::move(data));
    case 573:
      return new ::Ifc2x3::IfcPolygonalBoundedHalfSpace(std::move(data));
    case 574:
      return new ::Ifc2x3::IfcPolyline(std::move(data));
    case 575:
      return new ::Ifc2x3::IfcPolyLoop(std::move(data));
    case 576:
      return new ::Ifc2x3::IfcPort(std::move(data));
    case 577:
      return new ::Ifc2x3::IfcPositiveLengthMeasure(std::move(data));
    case 578:
      return new ::Ifc2x3::IfcPositivePlaneAngleMeasure(std::move(data));
    case 579:
      return new ::Ifc2x3::IfcPositiveRatioMeasure(std::move(data));
    case 580:
      return new ::Ifc2x3::IfcPostalAddress(std::move(data));
    case 581:
      return new ::Ifc2x3::IfcPowerMeasure(std::move(data));
    case 582:
      return new ::Ifc2x3::IfcPreDefinedColour(std::move(data));
    case 583:
      return new ::Ifc2x3::IfcPreDefinedCurveFont(std::move(data));
    case 584:
      return new ::Ifc2x3::IfcPreDefinedDimensionSymbol(std::move(data));
    case 585:
      return new ::Ifc2x3::IfcPreDefinedItem(std::move(data));
    case 586:
      return new ::Ifc2x3::IfcPreDefinedPointMarkerSymbol(std::move(data));
    case 587:
      return new ::Ifc2x3::IfcPreDefinedSymbol(std::move(data));
    case 588:
      return new ::Ifc2x3::IfcPreDefinedTerminatorSymbol(std::move(data));
    case 589:
      return new ::Ifc2x3::IfcPreDefinedTextFont(std::move(data));
    case 590:
      return new ::Ifc2x3::IfcPresentableText(std::move(data));
    case 591:
      return new ::Ifc2x3::IfcPresentationLayerAssignment(std::move(data));
    case 592:
      return new ::Ifc2x3::IfcPresentationLayerWithStyle(std::move(data));
    case 593:
      return new ::Ifc2x3::IfcPresentationStyle(std::move(data));
    case 594:
      return new ::Ifc2x3::IfcPresentationStyleAssignment(std::move(data));
    case 596:
      return new ::Ifc2x3::IfcPressureMeasure(std::move(data));
    case 597:
      return new ::Ifc2x3::IfcProcedure(std::move(data));
    case 598:
      return new ::Ifc2x3::IfcProcedureTypeEnum(std::move(data));
    case 599:
      return new ::Ifc2x3::IfcProcess(std::move(data));
    case 600:
      return new ::Ifc2x3::IfcProduct(std::move(data));
    case 601:
      return new ::Ifc2x3::IfcProductDefinitionShape(std::move(data));
    case 602:
      return new ::Ifc2x3::IfcProductRepresentation(std::move(data));
    case 603:
      return new ::Ifc2x3::IfcProductsOfCombustionProperties(std::move(data));
    case 604:
      return new ::Ifc2x3::IfcProfileDef(std::move(data));
    case 605:
      return new ::Ifc2x3::IfcProfileProperties(std::move(data));
    case 606:
      return new ::Ifc2x3::IfcProfileTypeEnum(std::move(data));
    case 607:
      return new ::Ifc2x3::IfcProject(std::move(data));
    case 608:
      return new ::Ifc2x3::IfcProjectedOrTrueLengthEnum(std::move(data));
    case 609:
      return new ::Ifc2x3::IfcProjectionCurve(std::move(data));
    case 610:
      return new ::Ifc2x3::IfcProjectionElement(std::move(data));
    case 611:
      return new ::Ifc2x3::IfcProjectOrder(std::move(data));
    case 612:
      return new ::Ifc2x3::IfcProjectOrderRecord(std::move(data));
    case 613:
      return new ::Ifc2x3::IfcProjectOrderRecordTypeEnum(std::move(data));
    case 614:
      return new ::Ifc2x3::IfcProjectOrderTypeEnum(std::move(data));
    case 615:
      return new ::Ifc2x3::IfcProperty(std::move(data));
    case 616:
      return new ::Ifc2x3::IfcPropertyBoundedValue(std::move(data));
    case 617:
      return new ::Ifc2x3::IfcPropertyConstraintRelationship(std::move(data));
    case 618:
      return new ::Ifc2x3::IfcPropertyDefinition(std::move(data));
    case 619:
      return new ::Ifc2x3::IfcPropertyDependencyRelationship(std::move(data));
    case 620:
      return new ::Ifc2x3::IfcPropertyEnumeratedValue(std::move(data));
    case 621:
      return new ::Ifc2x3::IfcPropertyEnumeration(std::move(data));
    case 622:
      return new ::Ifc2x3::IfcPropertyListValue(std::move(data));
    case 623:
      return new ::Ifc2x3::IfcPropertyReferenceValue(std::move(data));
    case 624:
      return new ::Ifc2x3::IfcPropertySet(std::move(data));
    case 625:
      return new ::Ifc2x3::IfcPropertySetDefinition(std::move(data));
    case 626:
      return new ::Ifc2x3::IfcPropertySingleValue(std::move(data));
    case 627:
      return new ::Ifc2x3::IfcPropertySourceEnum(std::move(data));
    case 628:
      return new ::Ifc2x3::IfcPropertyTableValue(std::move(data));
    case 629:
      return new ::Ifc2x3::IfcProtectiveDeviceType(std::move(data));
    case 630:
      return new ::Ifc2x3::IfcProtectiveDeviceTypeEnum(std::move(data));
    case 631:
      return new ::Ifc2x3::IfcProxy(std::move(data));
    case 632:
      return new ::Ifc2x3::IfcPumpType(std::move(data));
    case 633:
      return new ::Ifc2x3::IfcPumpTypeEnum(std::move(data));
    case 634:
      return new ::Ifc2x3::IfcQuantityArea(std::move(data));
    case 635:
      return new ::Ifc2x3::IfcQuantityCount(std::move(data));
    case 636:
      return new ::Ifc2x3::IfcQuantityLength(std::move(data));
    case 637:
      return new ::Ifc2x3::IfcQuantityTime(std::move(data));
    case 638:
      return new ::Ifc2x3::IfcQuantityVolume(std::move(data));
    case 639:
      return new ::Ifc2x3::IfcQuantityWeight(std::move(data));
    case 640:
      return new ::Ifc2x3::IfcRadioActivityMeasure(std::move(data));
    case 641:
      return new ::Ifc2x3::IfcRadiusDimension(std::move(data));
    case 642:
      return new ::Ifc2x3::IfcRailing(std::move(data));
    case 643:
      return new ::Ifc2x3::IfcRailingType(std::move(data));
    case 644:
      return new ::Ifc2x3::IfcRailingTypeEnum(std::move(data));
    case 645:
      return new ::Ifc2x3::IfcRamp(std::move(data));
    case 646:
      return new ::Ifc2x3::IfcRampFlight(std::move(data));
    case 647:
      return new ::Ifc2x3::IfcRampFlightType(std::move(data));
    case 648:
      return new ::Ifc2x3::IfcRampFlightTypeEnum(std::move(data));
    case 649:
      return new ::Ifc2x3::IfcRampTypeEnum(std::move(data));
    case 650:
      return new ::Ifc2x3::IfcRatioMeasure(std::move(data));
    case 651:
      return new ::Ifc2x3::IfcRationalBezierCurve(std::move(data));
    case 652:
      return new ::Ifc2x3::IfcReal(std::move(data));
    case 653:
      return new ::Ifc2x3::IfcRectangleHollowProfileDef(std::move(data));
    case 654:
      return new ::Ifc2x3::IfcRectangleProfileDef(std::move(data));
    case 655:
      return new ::Ifc2x3::IfcRectangularPyramid(std::move(data));
    case 656:
      return new ::Ifc2x3::IfcRectangularTrimmedSurface(std::move(data));
    case 657:
      return new ::Ifc2x3::IfcReferencesValueDocument(std::move(data));
    case 658:
      return new ::Ifc2x3::IfcReflectanceMethodEnum(std::move(data));
    case 659:
      return new ::Ifc2x3::IfcRegularTimeSeries(std::move(data));
    case 660:
      return new ::Ifc2x3::IfcReinforcementBarProperties(std::move(data));
    case 661:
      return new ::Ifc2x3::IfcReinforcementDefinitionProperties(
          std::move(data));
    case 662:
      return new ::Ifc2x3::IfcReinforcingBar(std::move(data));
    case 663:
      return new ::Ifc2x3::IfcReinforcingBarRoleEnum(std::move(data));
    case 664:
      return new ::Ifc2x3::IfcReinforcingBarSurfaceEnum(std::move(data));
    case 665:
      return new ::Ifc2x3::IfcReinforcingElement(std::move(data));
    case 666:
      return new ::Ifc2x3::IfcReinforcingMesh(std::move(data));
    case 667:
      return new ::Ifc2x3::IfcRelAggregates(std::move(data));
    case 668:
      return new ::Ifc2x3::IfcRelAssigns(std::move(data));
    case 669:
      return new ::Ifc2x3::IfcRelAssignsTasks(std::move(data));
    case 670:
      return new ::Ifc2x3::IfcRelAssignsToActor(std::move(data));
    case 671:
      return new ::Ifc2x3::IfcRelAssignsToControl(std::move(data));
    case 672:
      return new ::Ifc2x3::IfcRelAssignsToGroup(std::move(data));
    case 673:
      return new ::Ifc2x3::IfcRelAssignsToProcess(std::move(data));
    case 674:
      return new ::Ifc2x3::IfcRelAssignsToProduct(std::move(data));
    case 675:
      return new ::Ifc2x3::IfcRelAssignsToProjectOrder(std::move(data));
    case 676:
      return new ::Ifc2x3::IfcRelAssignsToResource(std::move(data));
    case 677:
      return new ::Ifc2x3::IfcRelAssociates(std::move(data));
    case 678:
      return new ::Ifc2x3::IfcRelAssociatesAppliedValue(std::move(data));
    case 679:
      return new ::Ifc2x3::IfcRelAssociatesApproval(std::move(data));
    case 680:
      return new ::Ifc2x3::IfcRelAssociatesClassification(std::move(data));
    case 681:
      return new ::Ifc2x3::IfcRelAssociatesConstraint(std::move(data));
    case 682:
      return new ::Ifc2x3::IfcRelAssociatesDocument(std::move(data));
    case 683:
      return new ::Ifc2x3::IfcRelAssociatesLibrary(std::move(data));
    case 684:
      return new ::Ifc2x3::IfcRelAssociatesMaterial(std::move(data));
    case 685:
      return new ::Ifc2x3::IfcRelAssociatesProfileProperties(std::move(data));
    case 686:
      return new ::Ifc2x3::IfcRelationship(std::move(data));
    case 687:
      return new ::Ifc2x3::IfcRelaxation(std::move(data));
    case 688:
      return new ::Ifc2x3::IfcRelConnects(std::move(data));
    case 689:
      return new ::Ifc2x3::IfcRelConnectsElements(std::move(data));
    case 690:
      return new ::Ifc2x3::IfcRelConnectsPathElements(std::move(data));
    case 691:
      return new ::Ifc2x3::IfcRelConnectsPorts(std::move(data));
    case 692:
      return new ::Ifc2x3::IfcRelConnectsPortToElement(std::move(data));
    case 693:
      return new ::Ifc2x3::IfcRelConnectsStructuralActivity(std::move(data));
    case 694:
      return new ::Ifc2x3::IfcRelConnectsStructuralElement(std::move(data));
    case 695:
      return new ::Ifc2x3::IfcRelConnectsStructuralMember(std::move(data));
    case 696:
      return new ::Ifc2x3::IfcRelConnectsWithEccentricity(std::move(data));
    case 697:
      return new ::Ifc2x3::IfcRelConnectsWithRealizingElements(std::move(data));
    case 698:
      return new ::Ifc2x3::IfcRelContainedInSpatialStructure(std::move(data));
    case 699:
      return new ::Ifc2x3::IfcRelCoversBldgElements(std::move(data));
    case 700:
      return new ::Ifc2x3::IfcRelCoversSpaces(std::move(data));
    case 701:
      return new ::Ifc2x3::IfcRelDecomposes(std::move(data));
    case 702:
      return new ::Ifc2x3::IfcRelDefines(std::move(data));
    case 703:
      return new ::Ifc2x3::IfcRelDefinesByProperties(std::move(data));
    case 704:
      return new ::Ifc2x3::IfcRelDefinesByType(std::move(data));
    case 705:
      return new ::Ifc2x3::IfcRelFillsElement(std::move(data));
    case 706:
      return new ::Ifc2x3::IfcRelFlowControlElements(std::move(data));
    case 707:
      return new ::Ifc2x3::IfcRelInteractionRequirements(std::move(data));
    case 708:
      return new ::Ifc2x3::IfcRelNests(std::move(data));
    case 709:
      return new ::Ifc2x3::IfcRelOccupiesSpaces(std::move(data));
    case 710:
      return new ::Ifc2x3::IfcRelOverridesProperties(std::move(data));
    case 711:
      return new ::Ifc2x3::IfcRelProjectsElement(std::move(data));
    case 712:
      return new ::Ifc2x3::IfcRelReferencedInSpatialStructure(std::move(data));
    case 713:
      return new ::Ifc2x3::IfcRelSchedulesCostItems(std::move(data));
    case 714:
      return new ::Ifc2x3::IfcRelSequence(std::move(data));
    case 715:
      return new ::Ifc2x3::IfcRelServicesBuildings(std::move(data));
    case 716:
      return new ::Ifc2x3::IfcRelSpaceBoundary(std::move(data));
    case 717:
      return new ::Ifc2x3::IfcRelVoidsElement(std::move(data));
    case 718:
      return new ::Ifc2x3::IfcRepresentation(std::move(data));
    case 719:
      return new ::Ifc2x3::IfcRepresentationContext(std::move(data));
    case 720:
      return new ::Ifc2x3::IfcRepresentationItem(std::move(data));
    case 721:
      return new ::Ifc2x3::IfcRepresentationMap(std::move(data));
    case 722:
      return new ::Ifc2x3::IfcResource(std::move(data));
    case 723:
      return new ::Ifc2x3::IfcResourceConsumptionEnum(std::move(data));
    case 724:
      return new ::Ifc2x3::IfcRevolvedAreaSolid(std::move(data));
    case 725:
      return new ::Ifc2x3::IfcRibPlateDirectionEnum(std::move(data));
    case 726:
      return new ::Ifc2x3::IfcRibPlateProfileProperties(std::move(data));
    case 727:
      return new ::Ifc2x3::IfcRightCircularCone(std::move(data));
    case 728:
      return new ::Ifc2x3::IfcRightCircularCylinder(std::move(data));
    case 729:
      return new ::Ifc2x3::IfcRoleEnum(std::move(data));
    case 730:
      return new ::Ifc2x3::IfcRoof(std::move(data));
    case 731:
      return new ::Ifc2x3::IfcRoofTypeEnum(std::move(data));
    case 732:
      return new ::Ifc2x3::IfcRoot(std::move(data));
    case 733:
      return new ::Ifc2x3::IfcRotationalFrequencyMeasure(std::move(data));
    case 734:
      return new ::Ifc2x3::IfcRotationalMassMeasure(std::move(data));
    case 735:
      return new ::Ifc2x3::IfcRotationalStiffnessMeasure(std::move(data));
    case 736:
      return new ::Ifc2x3::IfcRoundedEdgeFeature(std::move(data));
    case 737:
      return new ::Ifc2x3::IfcRoundedRectangleProfileDef(std::move(data));
    case 738:
      return new ::Ifc2x3::IfcSanitaryTerminalType(std::move(data));
    case 739:
      return new ::Ifc2x3::IfcSanitaryTerminalTypeEnum(std::move(data));
    case 740:
      return new ::Ifc2x3::IfcScheduleTimeControl(std::move(data));
    case 741:
      return new ::Ifc2x3::IfcSecondInMinute(std::move(data));
    case 742:
      return new ::Ifc2x3::IfcSectionalAreaIntegralMeasure(std::move(data));
    case 743:
      return new ::Ifc2x3::IfcSectionedSpine(std::move(data));
    case 744:
      return new ::Ifc2x3::IfcSectionModulusMeasure(std::move(data));
    case 745:
      return new ::Ifc2x3::IfcSectionProperties(std::move(data));
    case 746:
      return new ::Ifc2x3::IfcSectionReinforcementProperties(std::move(data));
    case 747:
      return new ::Ifc2x3::IfcSectionTypeEnum(std::move(data));
    case 748:
      return new ::Ifc2x3::IfcSensorType(std::move(data));
    case 749:
      return new ::Ifc2x3::IfcSensorTypeEnum(std::move(data));
    case 750:
      return new ::Ifc2x3::IfcSequenceEnum(std::move(data));
    case 751:
      return new ::Ifc2x3::IfcServiceLife(std::move(data));
    case 752:
      return new ::Ifc2x3::IfcServiceLifeFactor(std::move(data));
    case 753:
      return new ::Ifc2x3::IfcServiceLifeFactorTypeEnum(std::move(data));
    case 754:
      return new ::Ifc2x3::IfcServiceLifeTypeEnum(std::move(data));
    case 755:
      return new ::Ifc2x3::IfcShapeAspect(std::move(data));
    case 756:
      return new ::Ifc2x3::IfcShapeModel(std::move(data));
    case 757:
      return new ::Ifc2x3::IfcShapeRepresentation(std::move(data));
    case 758:
      return new ::Ifc2x3::IfcShearModulusMeasure(std::move(data));
    case 760:
      return new ::Ifc2x3::IfcShellBasedSurfaceModel(std::move(data));
    case 761:
      return new ::Ifc2x3::IfcSimpleProperty(std::move(data));
    case 763:
      return new ::Ifc2x3::IfcSIPrefix(std::move(data));
    case 764:
      return new ::Ifc2x3::IfcSite(std::move(data));
    case 765:
      return new ::Ifc2x3::IfcSIUnit(std::move(data));
    case 766:
      return new ::Ifc2x3::IfcSIUnitName(std::move(data));
    case 768:
      return new ::Ifc2x3::IfcSlab(std::move(data));
    case 769:
      return new ::Ifc2x3::IfcSlabType(std::move(data));
    case 770:
      return new ::Ifc2x3::IfcSlabTypeEnum(std::move(data));
    case 771:
      return new ::Ifc2x3::IfcSlippageConnectionCondition(std::move(data));
    case 772:
      return new ::Ifc2x3::IfcSolidAngleMeasure(std::move(data));
    case 773:
      return new ::Ifc2x3::IfcSolidModel(std::move(data));
    case 774:
      return new ::Ifc2x3::IfcSoundPowerMeasure(std::move(data));
    case 775:
      return new ::Ifc2x3::IfcSoundPressureMeasure(std::move(data));
    case 776:
      return new ::Ifc2x3::IfcSoundProperties(std::move(data));
    case 777:
      return new ::Ifc2x3::IfcSoundScaleEnum(std::move(data));
    case 778:
      return new ::Ifc2x3::IfcSoundValue(std::move(data));
    case 779:
      return new ::Ifc2x3::IfcSpace(std::move(data));
    case 780:
      return new ::Ifc2x3::IfcSpaceHeaterType(std::move(data));
    case 781:
      return new ::Ifc2x3::IfcSpaceHeaterTypeEnum(std::move(data));
    case 782:
      return new ::Ifc2x3::IfcSpaceProgram(std::move(data));
    case 783:
      return new ::Ifc2x3::IfcSpaceThermalLoadProperties(std::move(data));
    case 784:
      return new ::Ifc2x3::IfcSpaceType(std::move(data));
    case 785:
      return new ::Ifc2x3::IfcSpaceTypeEnum(std::move(data));
    case 786:
      return new ::Ifc2x3::IfcSpatialStructureElement(std::move(data));
    case 787:
      return new ::Ifc2x3::IfcSpatialStructureElementType(std::move(data));
    case 788:
      return new ::Ifc2x3::IfcSpecificHeatCapacityMeasure(std::move(data));
    case 789:
      return new ::Ifc2x3::IfcSpecularExponent(std::move(data));
    case 791:
      return new ::Ifc2x3::IfcSpecularRoughness(std::move(data));
    case 792:
      return new ::Ifc2x3::IfcSphere(std::move(data));
    case 793:
      return new ::Ifc2x3::IfcStackTerminalType(std::move(data));
    case 794:
      return new ::Ifc2x3::IfcStackTerminalTypeEnum(std::move(data));
    case 795:
      return new ::Ifc2x3::IfcStair(std::move(data));
    case 796:
      return new ::Ifc2x3::IfcStairFlight(std::move(data));
    case 797:
      return new ::Ifc2x3::IfcStairFlightType(std::move(data));
    case 798:
      return new ::Ifc2x3::IfcStairFlightTypeEnum(std::move(data));
    case 799:
      return new ::Ifc2x3::IfcStairTypeEnum(std::move(data));
    case 800:
      return new ::Ifc2x3::IfcStateEnum(std::move(data));
    case 801:
      return new ::Ifc2x3::IfcStructuralAction(std::move(data));
    case 802:
      return new ::Ifc2x3::IfcStructuralActivity(std::move(data));
    case 804:
      return new ::Ifc2x3::IfcStructuralAnalysisModel(std::move(data));
    case 805:
      return new ::Ifc2x3::IfcStructuralConnection(std::move(data));
    case 806:
      return new ::Ifc2x3::IfcStructuralConnectionCondition(std::move(data));
    case 807:
      return new ::Ifc2x3::IfcStructuralCurveConnection(std::move(data));
    case 808:
      return new ::Ifc2x3::IfcStructuralCurveMember(std::move(data));
    case 809:
      return new ::Ifc2x3::IfcStructuralCurveMemberVarying(std::move(data));
    case 810:
      return new ::Ifc2x3::IfcStructuralCurveTypeEnum(std::move(data));
    case 811:
      return new ::Ifc2x3::IfcStructuralItem(std::move(data));
    case 812:
      return new ::Ifc2x3::IfcStructuralLinearAction(std::move(data));
    case 813:
      return new ::Ifc2x3::IfcStructuralLinearActionVarying(std::move(data));
    case 814:
      return new ::Ifc2x3::IfcStructuralLoad(std::move(data));
    case 815:
      return new ::Ifc2x3::IfcStructuralLoadGroup(std::move(data));
    case 816:
      return new ::Ifc2x3::IfcStructuralLoadLinearForce(std::move(data));
    case 817:
      return new ::Ifc2x3::IfcStructuralLoadPlanarForce(std::move(data));
    case 818:
      return new ::Ifc2x3::IfcStructuralLoadSingleDisplacement(std::move(data));
    case 819:
      return new ::Ifc2x3::IfcStructuralLoadSingleDisplacementDistortion(
          std::move(data));
    case 820:
      return new ::Ifc2x3::IfcStructuralLoadSingleForce(std::move(data));
    case 821:
      return new ::Ifc2x3::IfcStructuralLoadSingleForceWarping(std::move(data));
    case 822:
      return new ::Ifc2x3::IfcStructuralLoadStatic(std::move(data));
    case 823:
      return new ::Ifc2x3::IfcStructuralLoadTemperature(std::move(data));
    case 824:
      return new ::Ifc2x3::IfcStructuralMember(std::move(data));
    case 825:
      return new ::Ifc2x3::IfcStructuralPlanarAction(std::move(data));
    case 826:
      return new ::Ifc2x3::IfcStructuralPlanarActionVarying(std::move(data));
    case 827:
      return new ::Ifc2x3::IfcStructuralPointAction(std::move(data));
    case 828:
      return new ::Ifc2x3::IfcStructuralPointConnection(std::move(data));
    case 829:
      return new ::Ifc2x3::IfcStructuralPointReaction(std::move(data));
    case 830:
      return new ::Ifc2x3::IfcStructuralProfileProperties(std::move(data));
    case 831:
      return new ::Ifc2x3::IfcStructuralReaction(std::move(data));
    case 832:
      return new ::Ifc2x3::IfcStructuralResultGroup(std::move(data));
    case 833:
      return new ::Ifc2x3::IfcStructuralSteelProfileProperties(std::move(data));
    case 834:
      return new ::Ifc2x3::IfcStructuralSurfaceConnection(std::move(data));
    case 835:
      return new ::Ifc2x3::IfcStructuralSurfaceMember(std::move(data));
    case 836:
      return new ::Ifc2x3::IfcStructuralSurfaceMemberVarying(std::move(data));
    case 837:
      return new ::Ifc2x3::IfcStructuralSurfaceTypeEnum(std::move(data));
    case 838:
      return new ::Ifc2x3::IfcStructuredDimensionCallout(std::move(data));
    case 839:
      return new ::Ifc2x3::IfcStyledItem(std::move(data));
    case 840:
      return new ::Ifc2x3::IfcStyledRepresentation(std::move(data));
    case 841:
      return new ::Ifc2x3::IfcStyleModel(std::move(data));
    case 842:
      return new ::Ifc2x3::IfcSubContractResource(std::move(data));
    case 843:
      return new ::Ifc2x3::IfcSubedge(std::move(data));
    case 844:
      return new ::Ifc2x3::IfcSurface(std::move(data));
    case 845:
      return new ::Ifc2x3::IfcSurfaceCurveSweptAreaSolid(std::move(data));
    case 846:
      return new ::Ifc2x3::IfcSurfaceOfLinearExtrusion(std::move(data));
    case 847:
      return new ::Ifc2x3::IfcSurfaceOfRevolution(std::move(data));
    case 849:
      return new ::Ifc2x3::IfcSurfaceSide(std::move(data));
    case 850:
      return new ::Ifc2x3::IfcSurfaceStyle(std::move(data));
    case 852:
      return new ::Ifc2x3::IfcSurfaceStyleLighting(std::move(data));
    case 853:
      return new ::Ifc2x3::IfcSurfaceStyleRefraction(std::move(data));
    case 854:
      return new ::Ifc2x3::IfcSurfaceStyleRendering(std::move(data));
    case 855:
      return new ::Ifc2x3::IfcSurfaceStyleShading(std::move(data));
    case 856:
      return new ::Ifc2x3::IfcSurfaceStyleWithTextures(std::move(data));
    case 857:
      return new ::Ifc2x3::IfcSurfaceTexture(std::move(data));
    case 858:
      return new ::Ifc2x3::IfcSurfaceTextureEnum(std::move(data));
    case 859:
      return new ::Ifc2x3::IfcSweptAreaSolid(std::move(data));
    case 860:
      return new ::Ifc2x3::IfcSweptDiskSolid(std::move(data));
    case 861:
      return new ::Ifc2x3::IfcSweptSurface(std::move(data));
    case 862:
      return new ::Ifc2x3::IfcSwitchingDeviceType(std::move(data));
    case 863:
      return new ::Ifc2x3::IfcSwitchingDeviceTypeEnum(std::move(data));
    case 864:
      return new ::Ifc2x3::IfcSymbolStyle(std::move(data));
    case 866:
      return new ::Ifc2x3::IfcSystem(std::move(data));
    case 867:
      return new ::Ifc2x3::IfcSystemFurnitureElementType(std::move(data));
    case 868:
      return new ::Ifc2x3::IfcTable(std::move(data));
    case 869:
      return new ::Ifc2x3::IfcTableRow(std::move(data));
    case 870:
      return new ::Ifc2x3::IfcTankType(std::move(data));
    case 871:
      return new ::Ifc2x3::IfcTankTypeEnum(std::move(data));
    case 872:
      return new ::Ifc2x3::IfcTask(std::move(data));
    case 873:
      return new ::Ifc2x3::IfcTelecomAddress(std::move(data));
    case 874:
      return new ::Ifc2x3::IfcTemperatureGradientMeasure(std::move(data));
    case 875:
      return new ::Ifc2x3::IfcTendon(std::move(data));
    case 876:
      return new ::Ifc2x3::IfcTendonAnchor(std::move(data));
    case 877:
      return new ::Ifc2x3::IfcTendonTypeEnum(std::move(data));
    case 878:
      return new ::Ifc2x3::IfcTerminatorSymbol(std::move(data));
    case 879:
      return new ::Ifc2x3::IfcText(std::move(data));
    case 880:
      return new ::Ifc2x3::IfcTextAlignment(std::move(data));
    case 881:
      return new ::Ifc2x3::IfcTextDecoration(std::move(data));
    case 882:
      return new ::Ifc2x3::IfcTextFontName(std::move(data));
    case 884:
      return new ::Ifc2x3::IfcTextLiteral(std::move(data));
    case 885:
      return new ::Ifc2x3::IfcTextLiteralWithExtent(std::move(data));
    case 886:
      return new ::Ifc2x3::IfcTextPath(std::move(data));
    case 887:
      return new ::Ifc2x3::IfcTextStyle(std::move(data));
    case 888:
      return new ::Ifc2x3::IfcTextStyleFontModel(std::move(data));
    case 889:
      return new ::Ifc2x3::IfcTextStyleForDefinedFont(std::move(data));
    case 891:
      return new ::Ifc2x3::IfcTextStyleTextModel(std::move(data));
    case 892:
      return new ::Ifc2x3::IfcTextStyleWithBoxCharacteristics(std::move(data));
    case 893:
      return new ::Ifc2x3::IfcTextTransformation(std::move(data));
    case 894:
      return new ::Ifc2x3::IfcTextureCoordinate(std::move(data));
    case 895:
      return new ::Ifc2x3::IfcTextureCoordinateGenerator(std::move(data));
    case 896:
      return new ::Ifc2x3::IfcTextureMap(std::move(data));
    case 897:
      return new ::Ifc2x3::IfcTextureVertex(std::move(data));
    case 898:
      return new ::Ifc2x3::IfcThermalAdmittanceMeasure(std::move(data));
    case 899:
      return new ::Ifc2x3::IfcThermalConductivityMeasure(std::move(data));
    case 900:
      return new ::Ifc2x3::IfcThermalExpansionCoefficientMeasure(
          std::move(data));
    case 901:
      return new ::Ifc2x3::IfcThermalLoadSourceEnum(std::move(data));
    case 902:
      return new ::Ifc2x3::IfcThermalLoadTypeEnum(std::move(data));
    case 903:
      return new ::Ifc2x3::IfcThermalMaterialProperties(std::move(data));
    case 904:
      return new ::Ifc2x3::IfcThermalResistanceMeasure(std::move(data));
    case 905:
      return new ::Ifc2x3::IfcThermalTransmittanceMeasure(std::move(data));
    case 906:
      return new ::Ifc2x3::IfcThermodynamicTemperatureMeasure(std::move(data));
    case 907:
      return new ::Ifc2x3::IfcTimeMeasure(std::move(data));
    case 908:
      return new ::Ifc2x3::IfcTimeSeries(std::move(data));
    case 909:
      return new ::Ifc2x3::IfcTimeSeriesDataTypeEnum(std::move(data));
    case 910:
      return new ::Ifc2x3::IfcTimeSeriesReferenceRelationship(std::move(data));
    case 911:
      return new ::Ifc2x3::IfcTimeSeriesSchedule(std::move(data));
    case 912:
      return new ::Ifc2x3::IfcTimeSeriesScheduleTypeEnum(std::move(data));
    case 913:
      return new ::Ifc2x3::IfcTimeSeriesValue(std::move(data));
    case 914:
      return new ::Ifc2x3::IfcTimeStamp(std::move(data));
    case 915:
      return new ::Ifc2x3::IfcTopologicalRepresentationItem(std::move(data));
    case 916:
      return new ::Ifc2x3::IfcTopologyRepresentation(std::move(data));
    case 917:
      return new ::Ifc2x3::IfcTorqueMeasure(std::move(data));
    case 918:
      return new ::Ifc2x3::IfcTransformerType(std::move(data));
    case 919:
      return new ::Ifc2x3::IfcTransformerTypeEnum(std::move(data));
    case 920:
      return new ::Ifc2x3::IfcTransitionCode(std::move(data));
    case 921:
      return new ::Ifc2x3::IfcTransportElement(std::move(data));
    case 922:
      return new ::Ifc2x3::IfcTransportElementType(std::move(data));
    case 923:
      return new ::Ifc2x3::IfcTransportElementTypeEnum(std::move(data));
    case 924:
      return new ::Ifc2x3::IfcTrapeziumProfileDef(std::move(data));
    case 925:
      return new ::Ifc2x3::IfcTrimmedCurve(std::move(data));
    case 926:
      return new ::Ifc2x3::IfcTrimmingPreference(std::move(data));
    case 928:
      return new ::Ifc2x3::IfcTShapeProfileDef(std::move(data));
    case 929:
      return new ::Ifc2x3::IfcTubeBundleType(std::move(data));
    case 930:
      return new ::Ifc2x3::IfcTubeBundleTypeEnum(std::move(data));
    case 931:
      return new ::Ifc2x3::IfcTwoDirectionRepeatFactor(std::move(data));
    case 932:
      return new ::Ifc2x3::IfcTypeObject(std::move(data));
    case 933:
      return new ::Ifc2x3::IfcTypeProduct(std::move(data));
    case 935:
      return new ::Ifc2x3::IfcUnitaryEquipmentType(std::move(data));
    case 936:
      return new ::Ifc2x3::IfcUnitaryEquipmentTypeEnum(std::move(data));
    case 937:
      return new ::Ifc2x3::IfcUnitAssignment(std::move(data));
    case 938:
      return new ::Ifc2x3::IfcUnitEnum(std::move(data));
    case 939:
      return new ::Ifc2x3::IfcUShapeProfileDef(std::move(data));
    case 941:
      return new ::Ifc2x3::IfcValveType(std::move(data));
    case 942:
      return new ::Ifc2x3::IfcValveTypeEnum(std::move(data));
    case 943:
      return new ::Ifc2x3::IfcVaporPermeabilityMeasure(std::move(data));
    case 944:
      return new ::Ifc2x3::IfcVector(std::move(data));
    case 946:
      return new ::Ifc2x3::IfcVertex(std::move(data));
    case 947:
      return new ::Ifc2x3::IfcVertexBasedTextureMap(std::move(data));
    case 948:
      return new ::Ifc2x3::IfcVertexLoop(std::move(data));
    case 949:
      return new ::Ifc2x3::IfcVertexPoint(std::move(data));
    case 950:
      return new ::Ifc2x3::IfcVibrationIsolatorType(std::move(data));
    case 951:
      return new ::Ifc2x3::IfcVibrationIsolatorTypeEnum(std::move(data));
    case 952:
      return new ::Ifc2x3::IfcVirtualElement(std::move(data));
    case 953:
      return new ::Ifc2x3::IfcVirtualGridIntersection(std::move(data));
    case 954:
      return new ::Ifc2x3::IfcVolumeMeasure(std::move(data));
    case 955:
      return new ::Ifc2x3::IfcVolumetricFlowRateMeasure(std::move(data));
    case 956:
      return new ::Ifc2x3::IfcWall(std::move(data));
    case 957:
      return new ::Ifc2x3::IfcWallStandardCase(std::move(data));
    case 958:
      return new ::Ifc2x3::IfcWallType(std::move(data));
    case 959:
      return new ::Ifc2x3::IfcWallTypeEnum(std::move(data));
    case 960:
      return new ::Ifc2x3::IfcWarpingConstantMeasure(std::move(data));
    case 961:
      return new ::Ifc2x3::IfcWarpingMomentMeasure(std::move(data));
    case 962:
      return new ::Ifc2x3::IfcWasteTerminalType(std::move(data));
    case 963:
      return new ::Ifc2x3::IfcWasteTerminalTypeEnum(std::move(data));
    case 964:
      return new ::Ifc2x3::IfcWaterProperties(std::move(data));
    case 965:
      return new ::Ifc2x3::IfcWindow(std::move(data));
    case 966:
      return new ::Ifc2x3::IfcWindowLiningProperties(std::move(data));
    case 967:
      return new ::Ifc2x3::IfcWindowPanelOperationEnum(std::move(data));
    case 968:
      return new ::Ifc2x3::IfcWindowPanelPositionEnum(std::move(data));
    case 969:
      return new ::Ifc2x3::IfcWindowPanelProperties(std::move(data));
    case 970:
      return new ::Ifc2x3::IfcWindowStyle(std::move(data));
    case 971:
      return new ::Ifc2x3::IfcWindowStyleConstructionEnum(std::move(data));
    case 972:
      return new ::Ifc2x3::IfcWindowStyleOperationEnum(std::move(data));
    case 973:
      return new ::Ifc2x3::IfcWorkControl(std::move(data));
    case 974:
      return new ::Ifc2x3::IfcWorkControlTypeEnum(std::move(data));
    case 975:
      return new ::Ifc2x3::IfcWorkPlan(std::move(data));
    case 976:
      return new ::Ifc2x3::IfcWorkSchedule(std::move(data));
    case 977:
      return new ::Ifc2x3::IfcYearNumber(std::move(data));
    case 978:
      return new ::Ifc2x3::IfcZone(std::move(data));
    case 979:
      return new ::Ifc2x3::IfcZShapeProfileDef(std::move(data));
    default:
      throw IfcParse::IfcException(decl->name() + " cannot be instantiated");
    }
  }
};

IfcParse::schema_definition *IFC2X3_populate_schema() {
  IFC2X3_types[1] = new type_declaration(
      strings[0], 1, new simple_type(simple_type::real_type));
  IFC2X3_types[2] = new type_declaration(
      strings[1], 2, new simple_type(simple_type::real_type));
  IFC2X3_types[4] = new enumeration_type(
      strings[2], 4,
      {strings[3],  strings[4],  strings[5],  strings[6],  strings[7],
       strings[8],  strings[9],  strings[10], strings[11], strings[12],
       strings[13], strings[14], strings[15], strings[16], strings[17],
       strings[18], strings[19], strings[20], strings[21], strings[22],
       strings[23], strings[24], strings[25], strings[26], strings[27],
       strings[28], strings[29]});
  IFC2X3_types[5] = new enumeration_type(
      strings[30], 5,
      {strings[31], strings[32], strings[33], strings[28], strings[29]});
  IFC2X3_types[10] =
      new enumeration_type(strings[34], 10,
                           {strings[35], strings[36], strings[37], strings[38],
                            strings[39], strings[28], strings[29]});
  IFC2X3_types[12] = new enumeration_type(
      strings[40], 12,
      {strings[41], strings[42], strings[43], strings[44], strings[28]});
  IFC2X3_types[13] =
      new enumeration_type(strings[45], 13, {strings[46], strings[47]});
  IFC2X3_types[15] = new enumeration_type(
      strings[48], 15,
      {strings[49], strings[50], strings[51], strings[28], strings[29]});
  IFC2X3_types[17] = new enumeration_type(
      strings[52], 17,
      {strings[53], strings[54], strings[55], strings[56], strings[57],
       strings[58], strings[59], strings[28], strings[29]});
  IFC2X3_types[19] =
      new enumeration_type(strings[60], 19,
                           {strings[61], strings[62], strings[63], strings[64],
                            strings[65], strings[66], strings[67], strings[68],
                            strings[69], strings[28], strings[29]});
  IFC2X3_types[21] = new enumeration_type(
      strings[70], 21,
      {strings[71], strings[72], strings[73], strings[74], strings[75],
       strings[76], strings[28], strings[29]});
  IFC2X3_types[22] = new type_declaration(
      strings[77], 22, new simple_type(simple_type::real_type));
  IFC2X3_types[23] = new enumeration_type(
      strings[78], 23,
      {strings[79], strings[80], strings[81], strings[28], strings[29]});
  IFC2X3_types[24] =
      new enumeration_type(strings[82], 24,
                           {strings[83], strings[84], strings[85], strings[86],
                            strings[28], strings[29]});
  IFC2X3_types[26] = new type_declaration(
      strings[87], 26, new simple_type(simple_type::real_type));
  IFC2X3_types[47] = new type_declaration(
      strings[88], 47, new simple_type(simple_type::real_type));
  IFC2X3_types[48] = new enumeration_type(
      strings[89], 48, {strings[90], strings[91], strings[92], strings[93]});
  IFC2X3_types[49] = new enumeration_type(
      strings[94], 49, {strings[42], strings[95], strings[29]});
  IFC2X3_types[81] =
      new enumeration_type(strings[96], 81,
                           {strings[97], strings[98], strings[99], strings[100],
                            strings[101], strings[102]});
  IFC2X3_types[58] =
      new enumeration_type(strings[103], 58,
                           {strings[104], strings[105], strings[106],
                            strings[107], strings[28], strings[29]});
  IFC2X3_types[59] =
      new enumeration_type(strings[108], 59,
                           {strings[109], strings[110], strings[111],
                            strings[112], strings[113], strings[114]});
  IFC2X3_types[64] = new enumeration_type(
      strings[115], 64, {strings[116], strings[117], strings[28], strings[29]});
  IFC2X3_types[65] = new type_declaration(
      strings[118], 65, new simple_type(simple_type::boolean_type));
  IFC2X3_types[68] = new enumeration_type(
      strings[119], 68, {strings[120], strings[121], strings[122]});
  IFC2X3_types[88] =
      new enumeration_type(strings[123], 88, {strings[28], strings[29]});
  IFC2X3_types[92] =
      new enumeration_type(strings[124], 92,
                           {strings[125], strings[126], strings[127],
                            strings[128], strings[28], strings[29]});
  IFC2X3_types[94] =
      new enumeration_type(strings[129], 94,
                           {strings[130], strings[131], strings[132],
                            strings[133], strings[28], strings[29]});
  IFC2X3_types[96] = new enumeration_type(
      strings[134], 96, {strings[135], strings[136], strings[28], strings[29]});
  IFC2X3_types[106] =
      new enumeration_type(strings[137], 106,
                           {strings[138], strings[139], strings[140],
                            strings[141], strings[142], strings[143]});
  IFC2X3_types[109] = new enumeration_type(
      strings[144], 109,
      {strings[145], strings[146], strings[147], strings[28], strings[29]});
  IFC2X3_types[122] = new enumeration_type(
      strings[148], 122,
      {strings[149], strings[150], strings[151], strings[152], strings[153],
       strings[154], strings[28], strings[29]});
  IFC2X3_types[129] = new enumeration_type(
      strings[155], 129, {strings[156], strings[28], strings[29]});
  IFC2X3_types[130] = new type_declaration(
      strings[157], 130,
      new aggregation_type(aggregation_type::array_type, 1, 2,
                           new simple_type(simple_type::real_type)));
  IFC2X3_types[135] = new type_declaration(
      strings[158], 135,
      new aggregation_type(aggregation_type::list_type, 3, 4,
                           new simple_type(simple_type::integer_type)));
  IFC2X3_types[137] = new enumeration_type(
      strings[159], 137,
      {strings[160], strings[161], strings[162], strings[163], strings[164],
       strings[165], strings[166], strings[167], strings[168], strings[169],
       strings[170], strings[171], strings[172], strings[173], strings[174],
       strings[28], strings[29]});
  IFC2X3_types[139] = new enumeration_type(
      strings[175], 139,
      {strings[176], strings[177], strings[178], strings[179], strings[145],
       strings[180], strings[28], strings[29]});
  IFC2X3_types[151] = new enumeration_type(
      strings[181], 151,
      {strings[182], strings[183], strings[184], strings[29]});
  IFC2X3_types[155] = new enumeration_type(
      strings[185], 155,
      {strings[186], strings[187], strings[188], strings[28], strings[29]});
  IFC2X3_types[161] = new type_declaration(
      strings[189], 161, new simple_type(simple_type::real_type));
  IFC2X3_types[165] = new enumeration_type(
      strings[190], 165,
      {strings[191], strings[192], strings[193], strings[194], strings[195],
       strings[196], strings[28], strings[29]});
  IFC2X3_types[168] = new enumeration_type(
      strings[197], 168,
      {strings[198], strings[199], strings[28], strings[29]});
  IFC2X3_types[170] = new enumeration_type(
      strings[200], 170,
      {strings[201], strings[202], strings[203], strings[28], strings[29]});
  IFC2X3_types[174] = new enumeration_type(
      strings[204], 174,
      {strings[205], strings[206], strings[207], strings[208], strings[209],
       strings[210], strings[211], strings[28], strings[29]});
  IFC2X3_types[176] = new type_declaration(
      strings[212], 176, new simple_type(simple_type::number_type));
  IFC2X3_types[179] = new enumeration_type(
      strings[213], 179,
      {strings[214], strings[215], strings[216], strings[217], strings[218],
       strings[219], strings[220], strings[221], strings[28], strings[29]});
  IFC2X3_types[187] = new enumeration_type(
      strings[222], 187,
      {strings[223], strings[224], strings[225], strings[226], strings[227],
       strings[228], strings[229], strings[230], strings[231], strings[232],
       strings[233], strings[234], strings[235], strings[236], strings[237],
       strings[238], strings[239], strings[240], strings[241], strings[242],
       strings[243], strings[244], strings[245], strings[246], strings[247],
       strings[248], strings[249], strings[250], strings[251], strings[252],
       strings[253], strings[254], strings[255], strings[256], strings[257],
       strings[258], strings[259], strings[260], strings[261], strings[262],
       strings[263], strings[264], strings[265], strings[266], strings[267],
       strings[268], strings[269], strings[270], strings[271], strings[272],
       strings[273], strings[274], strings[275], strings[276], strings[277],
       strings[278], strings[279], strings[280], strings[281], strings[282],
       strings[283], strings[284], strings[285], strings[286], strings[287],
       strings[288], strings[289], strings[290], strings[291], strings[292],
       strings[293], strings[294], strings[295], strings[296], strings[297],
       strings[298], strings[299], strings[300], strings[301], strings[302],
       strings[303], strings[304], strings[305]});
  IFC2X3_types[191] =
      new enumeration_type(strings[306], 191, {strings[28], strings[29]});
  IFC2X3_types[192] = new type_declaration(
      strings[307], 192, new simple_type(simple_type::real_type));
  IFC2X3_types[203] = new enumeration_type(
      strings[308], 203,
      {strings[309], strings[310], strings[311], strings[312], strings[313],
       strings[314], strings[315], strings[316], strings[317], strings[318],
       strings[319], strings[28], strings[29]});
  IFC2X3_types[204] = new enumeration_type(
      strings[320], 204,
      {strings[321], strings[322], strings[323], strings[28], strings[29]});
  IFC2X3_types[207] = new type_declaration(
      strings[324], 207, new simple_type(simple_type::integer_type));
  IFC2X3_types[208] = new type_declaration(
      strings[325], 208, new simple_type(simple_type::integer_type));
  IFC2X3_types[215] = new enumeration_type(
      strings[326], 215,
      {strings[327], strings[328], strings[329], strings[330], strings[331],
       strings[332], strings[333], strings[334], strings[335], strings[336],
       strings[337], strings[338], strings[339], strings[340], strings[341],
       strings[342], strings[343], strings[344], strings[345], strings[346],
       strings[347], strings[348], strings[349], strings[350], strings[351],
       strings[352], strings[353], strings[354], strings[355], strings[356],
       strings[357], strings[358], strings[359], strings[360], strings[361],
       strings[362], strings[363], strings[364], strings[365], strings[366],
       strings[367], strings[368], strings[369], strings[370], strings[371],
       strings[372], strings[373], strings[374], strings[28]});
  IFC2X3_types[216] = new type_declaration(
      strings[375], 216, new simple_type(simple_type::string_type));
  IFC2X3_types[220] = new type_declaration(
      strings[376], 220, new simple_type(simple_type::integer_type));
  IFC2X3_types[224] =
      new enumeration_type(strings[377], 224, {strings[378], strings[379]});
  IFC2X3_types[227] =
      new enumeration_type(strings[380], 227, {strings[381], strings[382]});
  IFC2X3_types[232] = new enumeration_type(
      strings[383], 232,
      {strings[384], strings[385], strings[386], strings[387], strings[388],
       strings[389], strings[390], strings[391], strings[28], strings[29]});
  IFC2X3_types[240] =
      new enumeration_type(strings[392], 240,
                           {strings[393], strings[394], strings[395],
                            strings[396], strings[28], strings[29]});
  IFC2X3_types[246] = new enumeration_type(
      strings[397], 246,
      {strings[398], strings[399], strings[400], strings[401], strings[29]});
  IFC2X3_types[249] = new enumeration_type(
      strings[402], 249,
      {strings[403], strings[404], strings[405], strings[406], strings[407],
       strings[408], strings[28], strings[29]});
  IFC2X3_types[250] = new enumeration_type(
      strings[409], 250,
      {strings[410], strings[411], strings[412], strings[29]});
  IFC2X3_types[253] = new enumeration_type(
      strings[413], 253,
      {strings[414], strings[415], strings[416], strings[417], strings[418],
       strings[419], strings[420], strings[28], strings[29]});
  IFC2X3_types[254] = new enumeration_type(
      strings[421], 254,
      {strings[422], strings[423], strings[424], strings[425], strings[426],
       strings[427], strings[428], strings[429], strings[430], strings[431],
       strings[432], strings[433], strings[434], strings[435], strings[407],
       strings[408], strings[28], strings[29]});
  IFC2X3_types[255] = new type_declaration(
      strings[436], 255, new simple_type(simple_type::real_type));
  IFC2X3_types[263] = new enumeration_type(
      strings[437], 263,
      {strings[125], strings[438], strings[439], strings[440], strings[441],
       strings[442], strings[443], strings[28], strings[29]});
  IFC2X3_types[265] = new enumeration_type(
      strings[444], 265,
      {strings[445], strings[446], strings[28], strings[29]});
  IFC2X3_types[267] = new enumeration_type(
      strings[447], 267,
      {strings[448], strings[449], strings[450], strings[28], strings[29]});
  IFC2X3_types[268] = new type_declaration(
      strings[451], 268, new simple_type(simple_type::real_type));
  IFC2X3_types[277] = new enumeration_type(
      strings[452], 277,
      {strings[453], strings[454], strings[455], strings[456], strings[457],
       strings[458], strings[459], strings[460], strings[461], strings[462],
       strings[463], strings[464], strings[465], strings[466], strings[467],
       strings[468], strings[469], strings[470], strings[471], strings[472],
       strings[473], strings[474], strings[475], strings[476], strings[28],
       strings[29]});
  IFC2X3_types[278] = new type_declaration(
      strings[477], 278, new simple_type(simple_type::real_type));
  IFC2X3_types[279] = new type_declaration(
      strings[478], 279, new simple_type(simple_type::real_type));
  IFC2X3_types[280] = new type_declaration(
      strings[479], 280, new simple_type(simple_type::real_type));
  IFC2X3_types[281] = new enumeration_type(
      strings[480], 281, {strings[481], strings[482], strings[29]});
  IFC2X3_types[282] = new type_declaration(
      strings[483], 282, new simple_type(simple_type::real_type));
  IFC2X3_types[284] = new enumeration_type(
      strings[484], 284,
      {strings[485], strings[486], strings[487], strings[488], strings[489],
       strings[490], strings[491], strings[492], strings[493], strings[28],
       strings[29]});
  IFC2X3_types[286] = new enumeration_type(
      strings[494], 286,
      {strings[495], strings[496], strings[497], strings[498], strings[499],
       strings[28], strings[29]});
  IFC2X3_types[288] =
      new enumeration_type(strings[500], 288, {strings[28], strings[29]});
  IFC2X3_types[290] = new enumeration_type(
      strings[501], 290,
      {strings[502], strings[503], strings[504], strings[28], strings[29]});
  IFC2X3_types[292] = new enumeration_type(
      strings[505], 292,
      {strings[506], strings[507], strings[508], strings[509], strings[510],
       strings[28], strings[29]});
  IFC2X3_types[293] = new type_declaration(
      strings[511], 293, new simple_type(simple_type::real_type));
  IFC2X3_types[295] = new enumeration_type(
      strings[512], 295,
      {strings[513], strings[514], strings[515], strings[28], strings[29]});
  IFC2X3_types[296] = new type_declaration(
      strings[516], 296, new simple_type(simple_type::real_type));
  IFC2X3_types[300] = new enumeration_type(
      strings[517], 300,
      {strings[518], strings[519], strings[520], strings[521], strings[522],
       strings[523], strings[524], strings[525], strings[526], strings[28],
       strings[29]});
  IFC2X3_types[303] = new enumeration_type(
      strings[527], 303, {strings[528], strings[529], strings[530]});
  IFC2X3_types[310] = new type_declaration(
      strings[531], 310, new simple_type(simple_type::real_type));
  IFC2X3_types[312] =
      new enumeration_type(strings[532], 312,
                           {strings[533], strings[534], strings[535],
                            strings[536], strings[28], strings[29]});
  IFC2X3_types[313] = new enumeration_type(
      strings[537], 313,
      {strings[538], strings[539], strings[540], strings[541], strings[542],
       strings[543], strings[28], strings[29]});
  IFC2X3_types[318] = new enumeration_type(
      strings[544], 318,
      {strings[545], strings[546], strings[547], strings[548], strings[549],
       strings[550], strings[551], strings[552], strings[553], strings[28],
       strings[29]});
  IFC2X3_types[320] = new enumeration_type(
      strings[554], 320,
      {strings[555], strings[556], strings[557], strings[558], strings[559],
       strings[28], strings[29]});
  IFC2X3_types[337] = new enumeration_type(
      strings[560], 337,
      {strings[561], strings[562], strings[563], strings[564], strings[565],
       strings[566], strings[567], strings[28], strings[29]});
  IFC2X3_types[350] = new enumeration_type(
      strings[568], 350,
      {strings[569], strings[570], strings[571], strings[572], strings[573],
       strings[28], strings[29]});
  IFC2X3_types[352] = new enumeration_type(
      strings[574], 352,
      {strings[575], strings[576], strings[577], strings[578], strings[579],
       strings[28], strings[29]});
  IFC2X3_types[355] = new enumeration_type(
      strings[580], 355,
      {strings[581], strings[582], strings[583], strings[29]});
  IFC2X3_types[359] = new enumeration_type(
      strings[584], 359,
      {strings[585], strings[586], strings[587], strings[588], strings[589],
       strings[590], strings[591], strings[592], strings[28], strings[29]});
  IFC2X3_types[361] = new enumeration_type(
      strings[593], 361,
      {strings[594], strings[595], strings[596], strings[597], strings[598],
       strings[599], strings[28], strings[29]});
  IFC2X3_types[373] = new type_declaration(
      strings[600], 373, new simple_type(simple_type::string_type));
  IFC2X3_types[374] = new type_declaration(
      strings[601], 374, new simple_type(simple_type::string_type));
  IFC2X3_types[375] = new type_declaration(
      strings[602], 375, new simple_type(simple_type::string_type));
  IFC2X3_types[377] =
      new enumeration_type(strings[603], 377,
                           {strings[604], strings[605], strings[606],
                            strings[607], strings[28], strings[29]});
  IFC2X3_types[378] = new type_declaration(
      strings[608], 378, new simple_type(simple_type::real_type));
  IFC2X3_types[379] = new type_declaration(
      strings[609], 379, new simple_type(simple_type::real_type));
  IFC2X3_types[386] = new enumeration_type(
      strings[610], 386,
      {strings[611], strings[612], strings[613], strings[28], strings[29]});
  IFC2X3_types[390] = new enumeration_type(
      strings[614], 390,
      {strings[615], strings[616], strings[617], strings[618], strings[619],
       strings[620], strings[621], strings[28], strings[29]});
  IFC2X3_types[397] =
      new enumeration_type(strings[622], 397, {strings[623], strings[624]});
  IFC2X3_types[396] = new type_declaration(
      strings[625], 396, new simple_type(simple_type::string_type));
  IFC2X3_types[405] = new enumeration_type(
      strings[626], 405,
      {strings[627], strings[628], strings[28], strings[29]});
  IFC2X3_types[406] = new type_declaration(
      strings[629], 406, new simple_type(simple_type::real_type));
  IFC2X3_types[407] = new type_declaration(
      strings[630], 407, new simple_type(simple_type::real_type));
  IFC2X3_types[408] = new type_declaration(
      strings[631], 408, new simple_type(simple_type::integer_type));
  IFC2X3_types[410] = new enumeration_type(
      strings[632], 410,
      {strings[633], strings[634], strings[635], strings[636], strings[637],
       strings[638], strings[639], strings[640], strings[641], strings[642],
       strings[643], strings[644], strings[645], strings[28], strings[29]});
  IFC2X3_types[412] = new type_declaration(
      strings[646], 412, new simple_type(simple_type::string_type));
  IFC2X3_types[413] = new type_declaration(
      strings[647], 413, new simple_type(simple_type::real_type));
  IFC2X3_types[415] = new type_declaration(
      strings[648], 415, new simple_type(simple_type::real_type));
  IFC2X3_types[416] = new type_declaration(
      strings[649], 416, new simple_type(simple_type::integer_type));
  IFC2X3_types[417] = new type_declaration(
      strings[650], 417, new simple_type(simple_type::integer_type));
  IFC2X3_types[418] = new enumeration_type(
      strings[651], 418, {strings[652], strings[653], strings[29]});
  IFC2X3_types[420] = new enumeration_type(
      strings[654], 420,
      {strings[655], strings[656], strings[657], strings[28], strings[29]});
  IFC2X3_types[421] = new type_declaration(
      strings[658], 421, new simple_type(simple_type::real_type));
  IFC2X3_types[425] = new type_declaration(
      strings[659], 425, new simple_type(simple_type::real_type));
  IFC2X3_types[427] =
      new enumeration_type(strings[660], 427, {strings[28], strings[29]});
  IFC2X3_types[428] = new type_declaration(
      strings[661], 428, new simple_type(simple_type::real_type));
  IFC2X3_types[429] = new type_declaration(
      strings[662], 429, new simple_type(simple_type::string_type));
  IFC2X3_types[432] = new enumeration_type(
      strings[663], 432,
      {strings[664], strings[665], strings[666], strings[667], strings[668],
       strings[669], strings[28], strings[29]});
  IFC2X3_types[434] = new enumeration_type(
      strings[670], 434, {strings[671], strings[672], strings[673]});
  IFC2X3_types[435] = new type_declaration(
      strings[674], 435, new simple_type(simple_type::real_type));
  IFC2X3_types[439] = new enumeration_type(
      strings[675], 439,
      {strings[676], strings[677], strings[678], strings[29]});
  IFC2X3_types[442] = new enumeration_type(
      strings[679], 442,
      {strings[664], strings[665], strings[666], strings[667], strings[680],
       strings[681], strings[682], strings[683], strings[668], strings[669],
       strings[29]});
  IFC2X3_types[444] = new enumeration_type(
      strings[684], 444,
      {strings[685], strings[686], strings[28], strings[29]});
  IFC2X3_types[454] = new type_declaration(
      strings[687], 454, new simple_type(simple_type::real_type));
  IFC2X3_types[455] = new type_declaration(
      strings[688], 455, new simple_type(simple_type::real_type));
  IFC2X3_types[456] = new type_declaration(
      strings[689], 456, new simple_type(simple_type::real_type));
  IFC2X3_types[457] = new type_declaration(
      strings[690], 457, new simple_type(simple_type::real_type));
  IFC2X3_types[458] =
      new enumeration_type(strings[691], 458,
                           {strings[692], strings[693], strings[694],
                            strings[695], strings[28], strings[29]});
  IFC2X3_types[461] = new type_declaration(
      strings[696], 461, new simple_type(simple_type::logical_type));
  IFC2X3_types[462] =
      new enumeration_type(strings[697], 462, {strings[698], strings[699]});
  IFC2X3_types[465] = new type_declaration(
      strings[700], 465, new simple_type(simple_type::real_type));
  IFC2X3_types[466] = new type_declaration(
      strings[701], 466, new simple_type(simple_type::real_type));
  IFC2X3_types[467] = new type_declaration(
      strings[702], 467, new simple_type(simple_type::real_type));
  IFC2X3_types[468] = new type_declaration(
      strings[703], 468, new simple_type(simple_type::real_type));
  IFC2X3_types[469] = new type_declaration(
      strings[704], 469, new simple_type(simple_type::real_type));
  IFC2X3_types[472] = new type_declaration(
      strings[705], 472, new simple_type(simple_type::real_type));
  IFC2X3_types[473] = new type_declaration(
      strings[706], 473, new simple_type(simple_type::real_type));
  IFC2X3_types[474] = new type_declaration(
      strings[707], 474, new simple_type(simple_type::real_type));
  IFC2X3_types[475] = new type_declaration(
      strings[708], 475, new simple_type(simple_type::real_type));
  IFC2X3_types[494] = new enumeration_type(
      strings[709], 494,
      {strings[710], strings[711], strings[712], strings[713], strings[714],
       strings[627], strings[715], strings[716], strings[717], strings[718],
       strings[719], strings[720], strings[28], strings[29]});
  IFC2X3_types[497] = new type_declaration(
      strings[721], 497, new simple_type(simple_type::integer_type));
  IFC2X3_types[498] = new type_declaration(
      strings[722], 498, new simple_type(simple_type::real_type));
  IFC2X3_types[499] = new type_declaration(
      strings[723], 499, new simple_type(simple_type::real_type));
  IFC2X3_types[500] = new type_declaration(
      strings[724], 500, new simple_type(simple_type::real_type));
  IFC2X3_types[501] = new type_declaration(
      strings[725], 501, new simple_type(simple_type::real_type));
  IFC2X3_types[502] = new type_declaration(
      strings[726], 502, new simple_type(simple_type::real_type));
  IFC2X3_types[503] = new type_declaration(
      strings[727], 503, new simple_type(simple_type::real_type));
  IFC2X3_types[504] = new type_declaration(
      strings[728], 504, new simple_type(simple_type::real_type));
  IFC2X3_types[505] = new type_declaration(
      strings[729], 505, new simple_type(simple_type::real_type));
  IFC2X3_types[507] = new type_declaration(
      strings[730], 507, new simple_type(simple_type::integer_type));
  IFC2X3_types[509] = new enumeration_type(
      strings[731], 509,
      {strings[732], strings[733], strings[734], strings[28], strings[29]});
  IFC2X3_types[513] = new enumeration_type(strings[735], 513, {strings[736]});
  IFC2X3_types[514] = new type_declaration(
      strings[737], 514, new simple_type(simple_type::number_type));
  IFC2X3_types[521] = new enumeration_type(
      strings[738], 521,
      {strings[739], strings[740], strings[741], strings[742], strings[743],
       strings[744], strings[745], strings[29]});
  IFC2X3_types[518] = new enumeration_type(
      strings[746], 518,
      {strings[747], strings[748], strings[749], strings[750], strings[751],
       strings[752], strings[28], strings[29]});
  IFC2X3_types[523] = new enumeration_type(
      strings[753], 523,
      {strings[754], strings[755], strings[756], strings[757], strings[758],
       strings[759], strings[760], strings[28], strings[29]});
  IFC2X3_types[536] = new enumeration_type(
      strings[761], 536,
      {strings[762], strings[763], strings[764], strings[28], strings[29]});
  IFC2X3_types[547] = new type_declaration(
      strings[765], 547, new simple_type(simple_type::real_type));
  IFC2X3_types[539] = new type_declaration(
      strings[766], 539, new simple_type(simple_type::real_type));
  IFC2X3_types[542] = new enumeration_type(
      strings[767], 542,
      {strings[768], strings[769], strings[770], strings[28], strings[29]});
  IFC2X3_types[549] = new enumeration_type(
      strings[771], 549, {strings[772], strings[773], strings[29]});
  IFC2X3_types[553] =
      new enumeration_type(strings[774], 553,
                           {strings[775], strings[776], strings[777],
                            strings[778], strings[28], strings[29]});
  IFC2X3_types[554] = new enumeration_type(
      strings[779], 554,
      {strings[780], strings[781], strings[782], strings[28], strings[29]});
  IFC2X3_types[556] = new enumeration_type(
      strings[783], 556,
      {strings[125], strings[438], strings[439], strings[440], strings[441],
       strings[442], strings[443], strings[28], strings[29]});
  IFC2X3_types[558] =
      new enumeration_type(strings[784], 558,
                           {strings[446], strings[445], strings[785],
                            strings[786], strings[28], strings[29]});
  IFC2X3_types[563] = new type_declaration(
      strings[787], 563, new simple_type(simple_type::real_type));
  IFC2X3_types[565] = new type_declaration(
      strings[788], 565, new simple_type(simple_type::real_type));
  IFC2X3_types[568] = new enumeration_type(
      strings[789], 568,
      {strings[790], strings[791], strings[28], strings[29]});
  IFC2X3_types[577] = new type_declaration(strings[792], 577,
                                           new named_type(IFC2X3_types[435]));
  IFC2X3_types[578] = new type_declaration(strings[793], 578,
                                           new named_type(IFC2X3_types[565]));
  IFC2X3_types[581] = new type_declaration(
      strings[794], 581, new simple_type(simple_type::real_type));
  IFC2X3_types[590] = new type_declaration(
      strings[795], 590, new simple_type(simple_type::string_type));
  IFC2X3_types[596] = new type_declaration(
      strings[796], 596, new simple_type(simple_type::real_type));
  IFC2X3_types[598] = new enumeration_type(
      strings[797], 598,
      {strings[798], strings[799], strings[800], strings[801], strings[802],
       strings[803], strings[804], strings[28], strings[29]});
  IFC2X3_types[606] =
      new enumeration_type(strings[805], 606, {strings[806], strings[807]});
  IFC2X3_types[613] = new enumeration_type(
      strings[808], 613,
      {strings[809], strings[810], strings[811], strings[812], strings[813],
       strings[28], strings[29]});
  IFC2X3_types[614] = new enumeration_type(
      strings[814], 614,
      {strings[815], strings[816], strings[817], strings[818], strings[819],
       strings[28], strings[29]});
  IFC2X3_types[608] =
      new enumeration_type(strings[820], 608, {strings[821], strings[822]});
  IFC2X3_types[627] = new enumeration_type(
      strings[823], 627,
      {strings[824], strings[825], strings[826], strings[323], strings[827],
       strings[828], strings[321], strings[28], strings[829]});
  IFC2X3_types[630] = new enumeration_type(
      strings[830], 630,
      {strings[831], strings[832], strings[833], strings[834], strings[835],
       strings[836], strings[28], strings[29]});
  IFC2X3_types[633] = new enumeration_type(
      strings[837], 633,
      {strings[838], strings[839], strings[840], strings[841], strings[842],
       strings[28], strings[29]});
  IFC2X3_types[640] = new type_declaration(
      strings[843], 640, new simple_type(simple_type::real_type));
  IFC2X3_types[644] = new enumeration_type(
      strings[844], 644,
      {strings[845], strings[846], strings[847], strings[28], strings[29]});
  IFC2X3_types[648] = new enumeration_type(
      strings[848], 648,
      {strings[849], strings[850], strings[28], strings[29]});
  IFC2X3_types[649] = new enumeration_type(
      strings[851], 649,
      {strings[852], strings[853], strings[854], strings[855], strings[856],
       strings[857], strings[28], strings[29]});
  IFC2X3_types[650] = new type_declaration(
      strings[858], 650, new simple_type(simple_type::real_type));
  IFC2X3_types[652] = new type_declaration(
      strings[859], 652, new simple_type(simple_type::real_type));
  IFC2X3_types[658] = new enumeration_type(
      strings[860], 658,
      {strings[861], strings[862], strings[863], strings[864], strings[865],
       strings[866], strings[867], strings[420], strings[868], strings[29]});
  IFC2X3_types[663] = new enumeration_type(
      strings[869], 663,
      {strings[870], strings[871], strings[872], strings[720], strings[873],
       strings[874], strings[875], strings[28], strings[29]});
  IFC2X3_types[664] =
      new enumeration_type(strings[876], 664, {strings[877], strings[878]});
  IFC2X3_types[723] = new enumeration_type(
      strings[879], 723,
      {strings[880], strings[881], strings[882], strings[883], strings[884],
       strings[885], strings[28], strings[29]});
  IFC2X3_types[725] =
      new enumeration_type(strings[886], 725, {strings[887], strings[888]});
  IFC2X3_types[729] = new enumeration_type(
      strings[889], 729,
      {strings[890], strings[891], strings[892], strings[893], strings[894],
       strings[895], strings[896], strings[897], strings[898], strings[899],
       strings[900], strings[901], strings[902], strings[903], strings[904],
       strings[905], strings[906], strings[759], strings[907], strings[908],
       strings[909], strings[910], strings[28]});
  IFC2X3_types[731] = new enumeration_type(
      strings[911], 731,
      {strings[912], strings[913], strings[914], strings[915], strings[916],
       strings[917], strings[918], strings[919], strings[920], strings[921],
       strings[922], strings[923], strings[924], strings[29]});
  IFC2X3_types[733] = new type_declaration(
      strings[925], 733, new simple_type(simple_type::real_type));
  IFC2X3_types[734] = new type_declaration(
      strings[926], 734, new simple_type(simple_type::real_type));
  IFC2X3_types[735] = new type_declaration(
      strings[927], 735, new simple_type(simple_type::real_type));
  IFC2X3_types[763] = new enumeration_type(
      strings[928], 763,
      {strings[929], strings[930], strings[931], strings[932], strings[933],
       strings[934], strings[935], strings[936], strings[937], strings[938],
       strings[939], strings[940], strings[941], strings[942], strings[943],
       strings[944]});
  IFC2X3_types[766] = new enumeration_type(
      strings[945], 766,
      {strings[946], strings[947], strings[948], strings[949], strings[950],
       strings[951], strings[952], strings[953], strings[954], strings[955],
       strings[956], strings[957], strings[958], strings[959], strings[960],
       strings[961], strings[962], strings[963], strings[964], strings[965],
       strings[966], strings[967], strings[968], strings[969], strings[970],
       strings[971], strings[972], strings[973], strings[974], strings[975]});
  IFC2X3_types[739] = new enumeration_type(
      strings[976], 739,
      {strings[977], strings[978], strings[979], strings[980], strings[582],
       strings[981], strings[982], strings[983], strings[984], strings[985],
       strings[28], strings[29]});
  IFC2X3_types[741] = new type_declaration(
      strings[986], 741, new simple_type(simple_type::real_type));
  IFC2X3_types[744] = new type_declaration(
      strings[987], 744, new simple_type(simple_type::real_type));
  IFC2X3_types[747] =
      new enumeration_type(strings[988], 747, {strings[989], strings[990]});
  IFC2X3_types[742] = new type_declaration(
      strings[991], 742, new simple_type(simple_type::real_type));
  IFC2X3_types[749] = new enumeration_type(
      strings[992], 749,
      {strings[993], strings[994], strings[995], strings[996], strings[997],
       strings[998], strings[999], strings[1000], strings[1001], strings[1002],
       strings[1003], strings[1004], strings[1005], strings[28], strings[29]});
  IFC2X3_types[750] =
      new enumeration_type(strings[1006], 750,
                           {strings[1007], strings[1008], strings[1009],
                            strings[1010], strings[29]});
  IFC2X3_types[753] = new enumeration_type(
      strings[1011], 753,
      {strings[1012], strings[1013], strings[1014], strings[1015],
       strings[1016], strings[1017], strings[1018], strings[28], strings[29]});
  IFC2X3_types[754] =
      new enumeration_type(strings[1019], 754,
                           {strings[1020], strings[1021], strings[1022],
                            strings[1023], strings[1024]});
  IFC2X3_types[758] = new type_declaration(
      strings[1025], 758, new simple_type(simple_type::real_type));
  IFC2X3_types[770] =
      new enumeration_type(strings[1026], 770,
                           {strings[1027], strings[1028], strings[1029],
                            strings[1030], strings[28], strings[29]});
  IFC2X3_types[772] = new type_declaration(
      strings[1031], 772, new simple_type(simple_type::real_type));
  IFC2X3_types[774] = new type_declaration(
      strings[1032], 774, new simple_type(simple_type::real_type));
  IFC2X3_types[775] = new type_declaration(
      strings[1033], 775, new simple_type(simple_type::real_type));
  IFC2X3_types[777] = new enumeration_type(
      strings[1034], 777,
      {strings[1035], strings[1036], strings[1037], strings[1038],
       strings[1039], strings[28], strings[29]});
  IFC2X3_types[781] = new enumeration_type(
      strings[1040], 781,
      {strings[1041], strings[1042], strings[1043], strings[1044],
       strings[1045], strings[1046], strings[1047], strings[28], strings[29]});
  IFC2X3_types[785] =
      new enumeration_type(strings[1048], 785, {strings[28], strings[29]});
  IFC2X3_types[788] = new type_declaration(
      strings[1049], 788, new simple_type(simple_type::real_type));
  IFC2X3_types[789] = new type_declaration(
      strings[1050], 789, new simple_type(simple_type::real_type));
  IFC2X3_types[791] = new type_declaration(
      strings[1051], 791, new simple_type(simple_type::real_type));
  IFC2X3_types[794] = new enumeration_type(
      strings[1052], 794,
      {strings[1053], strings[1054], strings[1055], strings[28], strings[29]});
  IFC2X3_types[798] = new enumeration_type(
      strings[1056], 798,
      {strings[849], strings[1057], strings[850], strings[1058], strings[924],
       strings[28], strings[29]});
  IFC2X3_types[799] = new enumeration_type(
      strings[1059], 799,
      {strings[1060], strings[1061], strings[1062], strings[1063],
       strings[1064], strings[1065], strings[1066], strings[1067],
       strings[1068], strings[1069], strings[1070], strings[1071],
       strings[1072], strings[1073], strings[28], strings[29]});
  IFC2X3_types[800] =
      new enumeration_type(strings[1074], 800,
                           {strings[1075], strings[1076], strings[1077],
                            strings[1078], strings[1079]});
  IFC2X3_types[810] = new enumeration_type(
      strings[1080], 810,
      {strings[1081], strings[1082], strings[1083], strings[1084],
       strings[1085], strings[28], strings[29]});
  IFC2X3_types[837] = new enumeration_type(
      strings[1086], 837,
      {strings[1087], strings[1088], strings[1089], strings[28], strings[29]});
  IFC2X3_types[849] = new enumeration_type(
      strings[1090], 849, {strings[381], strings[382], strings[1091]});
  IFC2X3_types[858] =
      new enumeration_type(strings[1092], 858,
                           {strings[1093], strings[1094], strings[1095],
                            strings[1096], strings[1097], strings[1098],
                            strings[1099], strings[1100], strings[29]});
  IFC2X3_types[863] = new enumeration_type(
      strings[1101], 863,
      {strings[1102], strings[1103], strings[1104], strings[1105],
       strings[1106], strings[28], strings[29]});
  IFC2X3_types[871] =
      new enumeration_type(strings[1107], 871,
                           {strings[1108], strings[1109], strings[1110],
                            strings[1111], strings[28], strings[29]});
  IFC2X3_types[874] = new type_declaration(
      strings[1112], 874, new simple_type(simple_type::real_type));
  IFC2X3_types[877] =
      new enumeration_type(strings[1113], 877,
                           {strings[1114], strings[1115], strings[1116],
                            strings[1117], strings[28], strings[29]});
  IFC2X3_types[879] = new type_declaration(
      strings[1118], 879, new simple_type(simple_type::string_type));
  IFC2X3_types[880] = new type_declaration(
      strings[1119], 880, new simple_type(simple_type::string_type));
  IFC2X3_types[881] = new type_declaration(
      strings[1120], 881, new simple_type(simple_type::string_type));
  IFC2X3_types[882] = new type_declaration(
      strings[1121], 882, new simple_type(simple_type::string_type));
  IFC2X3_types[886] = new enumeration_type(
      strings[1122], 886,
      {strings[410], strings[412], strings[1123], strings[1124]});
  IFC2X3_types[893] = new type_declaration(
      strings[1125], 893, new simple_type(simple_type::string_type));
  IFC2X3_types[898] = new type_declaration(
      strings[1126], 898, new simple_type(simple_type::real_type));
  IFC2X3_types[899] = new type_declaration(
      strings[1127], 899, new simple_type(simple_type::real_type));
  IFC2X3_types[900] = new type_declaration(
      strings[1128], 900, new simple_type(simple_type::real_type));
  IFC2X3_types[901] = new enumeration_type(
      strings[1129], 901,
      {strings[1130], strings[1131], strings[1132], strings[1133],
       strings[1134], strings[1135], strings[1136], strings[1137],
       strings[1138], strings[1139], strings[1140], strings[28], strings[29]});
  IFC2X3_types[902] = new enumeration_type(
      strings[1141], 902,
      {strings[1142], strings[1143], strings[1144], strings[29]});
  IFC2X3_types[904] = new type_declaration(
      strings[1145], 904, new simple_type(simple_type::real_type));
  IFC2X3_types[905] = new type_declaration(
      strings[1146], 905, new simple_type(simple_type::real_type));
  IFC2X3_types[906] = new type_declaration(
      strings[1147], 906, new simple_type(simple_type::real_type));
  IFC2X3_types[907] = new type_declaration(
      strings[1148], 907, new simple_type(simple_type::real_type));
  IFC2X3_types[909] = new enumeration_type(
      strings[1149], 909,
      {strings[1150], strings[1151], strings[1152], strings[1153],
       strings[1154], strings[1155], strings[29]});
  IFC2X3_types[912] =
      new enumeration_type(strings[1156], 912,
                           {strings[1157], strings[1158], strings[1159],
                            strings[1160], strings[28], strings[29]});
  IFC2X3_types[914] = new type_declaration(
      strings[1161], 914, new simple_type(simple_type::integer_type));
  IFC2X3_types[917] = new type_declaration(
      strings[1162], 917, new simple_type(simple_type::real_type));
  IFC2X3_types[919] = new enumeration_type(
      strings[1163], 919,
      {strings[24], strings[1164], strings[1165], strings[28], strings[29]});
  IFC2X3_types[920] = new enumeration_type(
      strings[1166], 920,
      {strings[1167], strings[1150], strings[1168], strings[1169]});
  IFC2X3_types[923] = new enumeration_type(
      strings[1170], 923,
      {strings[1171], strings[1172], strings[1173], strings[28], strings[29]});
  IFC2X3_types[926] = new enumeration_type(
      strings[1174], 926, {strings[1175], strings[1176], strings[102]});
  IFC2X3_types[930] = new enumeration_type(
      strings[1177], 930, {strings[1178], strings[28], strings[29]});
  IFC2X3_types[938] = new enumeration_type(
      strings[1179], 938,
      {strings[1180], strings[1181], strings[1182], strings[1183],
       strings[1184], strings[1185], strings[1186], strings[1187],
       strings[1188], strings[1189], strings[1190], strings[1191],
       strings[1192], strings[1193], strings[1194], strings[1195],
       strings[1196], strings[1197], strings[1198], strings[1199],
       strings[1200], strings[1201], strings[1202], strings[1203],
       strings[1204], strings[1205], strings[1206], strings[1207],
       strings[1208], strings[28]});
  IFC2X3_types[936] =
      new enumeration_type(strings[1209], 936,
                           {strings[1210], strings[1211], strings[1212],
                            strings[1213], strings[28], strings[29]});
  IFC2X3_types[942] = new enumeration_type(
      strings[1214], 942,
      {strings[1215], strings[1216], strings[1217], strings[1218],
       strings[828],  strings[1219], strings[1220], strings[1221],
       strings[1222], strings[1223], strings[1224], strings[1225],
       strings[1226], strings[1227], strings[1228], strings[1229],
       strings[1230], strings[1231], strings[1232], strings[1233],
       strings[1234], strings[28],   strings[29]});
  IFC2X3_types[943] = new type_declaration(
      strings[1235], 943, new simple_type(simple_type::real_type));
  IFC2X3_types[951] = new enumeration_type(
      strings[1236], 951,
      {strings[1237], strings[1238], strings[28], strings[29]});
  IFC2X3_types[954] = new type_declaration(
      strings[1239], 954, new simple_type(simple_type::real_type));
  IFC2X3_types[955] = new type_declaration(
      strings[1240], 955, new simple_type(simple_type::real_type));
  IFC2X3_types[959] = new enumeration_type(
      strings[1241], 959,
      {strings[1242], strings[1243], strings[871], strings[1244], strings[1245],
       strings[28], strings[29]});
  IFC2X3_types[960] = new type_declaration(
      strings[1246], 960, new simple_type(simple_type::real_type));
  IFC2X3_types[961] = new type_declaration(
      strings[1247], 961, new simple_type(simple_type::real_type));
  IFC2X3_types[963] = new enumeration_type(
      strings[1248], 963,
      {strings[1249], strings[1250], strings[1251], strings[1252],
       strings[1253], strings[1254], strings[1255], strings[1256],
       strings[1257], strings[1258], strings[28], strings[29]});
  IFC2X3_types[967] = new enumeration_type(
      strings[1259], 967,
      {strings[1260], strings[1261], strings[1262], strings[1263],
       strings[1264], strings[1265], strings[1266], strings[1267],
       strings[1268], strings[1269], strings[1270], strings[1271],
       strings[1272], strings[29]});
  IFC2X3_types[968] =
      new enumeration_type(strings[1273], 968,
                           {strings[410], strings[411], strings[412],
                            strings[1274], strings[1275], strings[29]});
  IFC2X3_types[971] = new enumeration_type(
      strings[1276], 971,
      {strings[414], strings[415], strings[416], strings[417], strings[418],
       strings[420], strings[1277], strings[29]});
  IFC2X3_types[972] = new enumeration_type(
      strings[1278], 972,
      {strings[1279], strings[1280], strings[1281], strings[1282],
       strings[1283], strings[1284], strings[1285], strings[1286],
       strings[1287], strings[28], strings[29]});
  IFC2X3_types[974] = new enumeration_type(
      strings[1288], 974,
      {strings[1289], strings[1290], strings[1291], strings[28], strings[29]});
  IFC2X3_types[977] = new type_declaration(
      strings[1292], 977, new simple_type(simple_type::integer_type));
  IFC2X3_types[7] = new entity(strings[1293], false, 7, (entity *)0);
  IFC2X3_types[11] = new entity(strings[1294], true, 11, (entity *)0);
  IFC2X3_types[36] = new entity(strings[1295], false, 36, (entity *)0);
  IFC2X3_types[37] = new entity(strings[1296], true, 37, (entity *)0);
  IFC2X3_types[38] = new entity(strings[1297], false, 38, (entity *)0);
  IFC2X3_types[40] = new entity(strings[1298], false, 40, (entity *)0);
  IFC2X3_types[41] = new entity(strings[1299], false, 41, (entity *)0);
  IFC2X3_types[42] = new entity(strings[1300], false, 42, (entity *)0);
  IFC2X3_types[43] = new entity(strings[1301], false, 43, (entity *)0);
  IFC2X3_types[70] = new entity(strings[1302], true, 70, (entity *)0);
  IFC2X3_types[71] =
      new entity(strings[1303], false, 71, (entity *)IFC2X3_types[70]);
  IFC2X3_types[72] =
      new entity(strings[1304], false, 72, (entity *)IFC2X3_types[70]);
  IFC2X3_types[73] =
      new entity(strings[1305], false, 73, (entity *)IFC2X3_types[70]);
  IFC2X3_types[74] =
      new entity(strings[1306], false, 74, (entity *)IFC2X3_types[73]);
  IFC2X3_types[97] = new entity(strings[1307], false, 97, (entity *)0);
  IFC2X3_types[113] = new entity(strings[1308], false, 113, (entity *)0);
  IFC2X3_types[114] = new entity(strings[1309], false, 114, (entity *)0);
  IFC2X3_types[115] = new entity(strings[1310], false, 115, (entity *)0);
  IFC2X3_types[116] = new entity(strings[1311], false, 116, (entity *)0);
  IFC2X3_types[117] = new entity(strings[1312], false, 117, (entity *)0);
  IFC2X3_types[126] = new entity(strings[1313], true, 126, (entity *)0);
  IFC2X3_types[146] = new entity(strings[1314], true, 146, (entity *)0);
  IFC2X3_types[148] =
      new entity(strings[1315], false, 148, (entity *)IFC2X3_types[146]);
  IFC2X3_types[149] =
      new entity(strings[1316], false, 149, (entity *)IFC2X3_types[146]);
  IFC2X3_types[150] =
      new entity(strings[1317], false, 150, (entity *)IFC2X3_types[146]);
  IFC2X3_types[152] = new entity(strings[1318], true, 152, (entity *)0);
  IFC2X3_types[153] = new entity(strings[1319], false, 153, (entity *)0);
  IFC2X3_types[154] = new entity(strings[1320], false, 154, (entity *)0);
  IFC2X3_types[156] = new entity(strings[1321], false, 156, (entity *)0);
  IFC2X3_types[171] = new entity(strings[1322], false, 171, (entity *)0);
  IFC2X3_types[175] =
      new entity(strings[1323], false, 175, (entity *)IFC2X3_types[37]);
  IFC2X3_types[188] = new entity(strings[1324], false, 188, (entity *)0);
  IFC2X3_types[198] = new entity(strings[1325], false, 198, (entity *)0);
  IFC2X3_types[199] = new entity(strings[1326], false, 199, (entity *)0);
  IFC2X3_types[200] = new entity(strings[1327], false, 200, (entity *)0);
  IFC2X3_types[205] = new entity(strings[1328], false, 205, (entity *)0);
  IFC2X3_types[213] = new entity(strings[1329], false, 213, (entity *)0);
  IFC2X3_types[214] = new entity(strings[1330], false, 214, (entity *)0);
  IFC2X3_types[218] = new entity(strings[1331], false, 218, (entity *)0);
  IFC2X3_types[241] = new entity(strings[1332], false, 241, (entity *)0);
  IFC2X3_types[242] = new entity(strings[1333], false, 242, (entity *)0);
  IFC2X3_types[243] = new entity(strings[1334], false, 243, (entity *)0);
  IFC2X3_types[258] = new entity(strings[1335], false, 258, (entity *)0);
  IFC2X3_types[314] =
      new entity(strings[1336], false, 314, (entity *)IFC2X3_types[37]);
  IFC2X3_types[326] = new entity(strings[1337], true, 326, (entity *)0);
  IFC2X3_types[322] =
      new entity(strings[1338], false, 322, (entity *)IFC2X3_types[326]);
  IFC2X3_types[323] =
      new entity(strings[1339], false, 323, (entity *)IFC2X3_types[326]);
  IFC2X3_types[324] =
      new entity(strings[1340], false, 324, (entity *)IFC2X3_types[326]);
  IFC2X3_types[325] =
      new entity(strings[1341], false, 325, (entity *)IFC2X3_types[326]);
  IFC2X3_types[399] = new entity(strings[1342], false, 399, (entity *)0);
  IFC2X3_types[423] = new entity(strings[1343], false, 423, (entity *)0);
  IFC2X3_types[436] = new entity(strings[1344], false, 436, (entity *)0);
  IFC2X3_types[437] =
      new entity(strings[1345], false, 437, (entity *)IFC2X3_types[326]);
  IFC2X3_types[440] = new entity(strings[1346], false, 440, (entity *)0);
  IFC2X3_types[445] = new entity(strings[1347], false, 445, (entity *)0);
  IFC2X3_types[460] = new entity(strings[1348], false, 460, (entity *)0);
  IFC2X3_types[476] = new entity(strings[1349], false, 476, (entity *)0);
  IFC2X3_types[477] = new entity(strings[1350], false, 477, (entity *)0);
  IFC2X3_types[479] = new entity(strings[1351], false, 479, (entity *)0);
  IFC2X3_types[480] = new entity(strings[1352], false, 480, (entity *)0);
  IFC2X3_types[481] = new entity(strings[1353], false, 481, (entity *)0);
  IFC2X3_types[482] = new entity(strings[1354], false, 482, (entity *)0);
  IFC2X3_types[483] = new entity(strings[1355], true, 483, (entity *)0);
  IFC2X3_types[486] = new entity(strings[1356], false, 486, (entity *)0);
  IFC2X3_types[490] =
      new entity(strings[1357], false, 490, (entity *)IFC2X3_types[483]);
  IFC2X3_types[491] =
      new entity(strings[1358], false, 491, (entity *)IFC2X3_types[490]);
  IFC2X3_types[495] =
      new entity(strings[1359], false, 495, (entity *)IFC2X3_types[152]);
  IFC2X3_types[506] = new entity(strings[1360], false, 506, (entity *)0);
  IFC2X3_types[511] = new entity(strings[1361], true, 511, (entity *)0);
  IFC2X3_types[519] = new entity(strings[1362], true, 519, (entity *)0);
  IFC2X3_types[517] =
      new entity(strings[1363], false, 517, (entity *)IFC2X3_types[152]);
  IFC2X3_types[529] =
      new entity(strings[1364], false, 529, (entity *)IFC2X3_types[483]);
  IFC2X3_types[531] = new entity(strings[1365], false, 531, (entity *)0);
  IFC2X3_types[532] = new entity(strings[1366], false, 532, (entity *)0);
  IFC2X3_types[537] = new entity(strings[1367], false, 537, (entity *)0);
  IFC2X3_types[545] = new entity(strings[1368], false, 545, (entity *)0);
  IFC2X3_types[546] = new entity(strings[1369], false, 546, (entity *)0);
  IFC2X3_types[550] = new entity(strings[1370], true, 550, (entity *)0);
  IFC2X3_types[551] =
      new entity(strings[1371], true, 551, (entity *)IFC2X3_types[550]);
  IFC2X3_types[580] =
      new entity(strings[1372], false, 580, (entity *)IFC2X3_types[11]);
  IFC2X3_types[585] = new entity(strings[1373], true, 585, (entity *)0);
  IFC2X3_types[587] =
      new entity(strings[1374], true, 587, (entity *)IFC2X3_types[585]);
  IFC2X3_types[588] =
      new entity(strings[1375], false, 588, (entity *)IFC2X3_types[587]);
  IFC2X3_types[589] =
      new entity(strings[1376], true, 589, (entity *)IFC2X3_types[585]);
  IFC2X3_types[591] = new entity(strings[1377], false, 591, (entity *)0);
  IFC2X3_types[592] =
      new entity(strings[1378], false, 592, (entity *)IFC2X3_types[591]);
  IFC2X3_types[593] = new entity(strings[1379], true, 593, (entity *)0);
  IFC2X3_types[594] = new entity(strings[1380], false, 594, (entity *)0);
  IFC2X3_types[602] = new entity(strings[1381], false, 602, (entity *)0);
  IFC2X3_types[603] =
      new entity(strings[1382], false, 603, (entity *)IFC2X3_types[483]);
  IFC2X3_types[604] = new entity(strings[1383], true, 604, (entity *)0);
  IFC2X3_types[605] = new entity(strings[1384], true, 605, (entity *)0);
  IFC2X3_types[615] = new entity(strings[1385], true, 615, (entity *)0);
  IFC2X3_types[617] = new entity(strings[1386], false, 617, (entity *)0);
  IFC2X3_types[619] = new entity(strings[1387], false, 619, (entity *)0);
  IFC2X3_types[621] = new entity(strings[1388], false, 621, (entity *)0);
  IFC2X3_types[634] =
      new entity(strings[1389], false, 634, (entity *)IFC2X3_types[551]);
  IFC2X3_types[635] =
      new entity(strings[1390], false, 635, (entity *)IFC2X3_types[551]);
  IFC2X3_types[636] =
      new entity(strings[1391], false, 636, (entity *)IFC2X3_types[551]);
  IFC2X3_types[637] =
      new entity(strings[1392], false, 637, (entity *)IFC2X3_types[551]);
  IFC2X3_types[638] =
      new entity(strings[1393], false, 638, (entity *)IFC2X3_types[551]);
  IFC2X3_types[639] =
      new entity(strings[1394], false, 639, (entity *)IFC2X3_types[551]);
  IFC2X3_types[657] = new entity(strings[1395], false, 657, (entity *)0);
  IFC2X3_types[660] = new entity(strings[1396], false, 660, (entity *)0);
  IFC2X3_types[687] = new entity(strings[1397], false, 687, (entity *)0);
  IFC2X3_types[718] = new entity(strings[1398], false, 718, (entity *)0);
  IFC2X3_types[719] = new entity(strings[1399], false, 719, (entity *)0);
  IFC2X3_types[720] = new entity(strings[1400], true, 720, (entity *)0);
  IFC2X3_types[721] = new entity(strings[1401], false, 721, (entity *)0);
  IFC2X3_types[726] =
      new entity(strings[1402], false, 726, (entity *)IFC2X3_types[605]);
  IFC2X3_types[732] = new entity(strings[1403], true, 732, (entity *)0);
  IFC2X3_types[765] =
      new entity(strings[1404], false, 765, (entity *)IFC2X3_types[511]);
  IFC2X3_types[745] = new entity(strings[1405], false, 745, (entity *)0);
  IFC2X3_types[746] = new entity(strings[1406], false, 746, (entity *)0);
  IFC2X3_types[755] = new entity(strings[1407], false, 755, (entity *)0);
  IFC2X3_types[756] =
      new entity(strings[1408], true, 756, (entity *)IFC2X3_types[718]);
  IFC2X3_types[757] =
      new entity(strings[1409], false, 757, (entity *)IFC2X3_types[756]);
  IFC2X3_types[761] =
      new entity(strings[1410], true, 761, (entity *)IFC2X3_types[615]);
  IFC2X3_types[806] = new entity(strings[1411], true, 806, (entity *)0);
  IFC2X3_types[814] = new entity(strings[1412], true, 814, (entity *)0);
  IFC2X3_types[822] =
      new entity(strings[1413], true, 822, (entity *)IFC2X3_types[814]);
  IFC2X3_types[823] =
      new entity(strings[1414], false, 823, (entity *)IFC2X3_types[822]);
  IFC2X3_types[841] =
      new entity(strings[1415], true, 841, (entity *)IFC2X3_types[718]);
  IFC2X3_types[839] =
      new entity(strings[1416], false, 839, (entity *)IFC2X3_types[720]);
  IFC2X3_types[840] =
      new entity(strings[1417], false, 840, (entity *)IFC2X3_types[841]);
  IFC2X3_types[850] =
      new entity(strings[1418], false, 850, (entity *)IFC2X3_types[593]);
  IFC2X3_types[852] = new entity(strings[1419], false, 852, (entity *)0);
  IFC2X3_types[853] = new entity(strings[1420], false, 853, (entity *)0);
  IFC2X3_types[855] = new entity(strings[1421], false, 855, (entity *)0);
  IFC2X3_types[856] = new entity(strings[1422], false, 856, (entity *)0);
  IFC2X3_types[857] = new entity(strings[1423], true, 857, (entity *)0);
  IFC2X3_types[864] =
      new entity(strings[1424], false, 864, (entity *)IFC2X3_types[593]);
  IFC2X3_types[868] = new entity(strings[1425], false, 868, (entity *)0);
  IFC2X3_types[869] = new entity(strings[1426], false, 869, (entity *)0);
  IFC2X3_types[873] =
      new entity(strings[1427], false, 873, (entity *)IFC2X3_types[11]);
  IFC2X3_types[887] =
      new entity(strings[1428], false, 887, (entity *)IFC2X3_types[593]);
  IFC2X3_types[888] =
      new entity(strings[1429], false, 888, (entity *)IFC2X3_types[589]);
  IFC2X3_types[889] = new entity(strings[1430], false, 889, (entity *)0);
  IFC2X3_types[891] = new entity(strings[1431], false, 891, (entity *)0);
  IFC2X3_types[892] = new entity(strings[1432], false, 892, (entity *)0);
  IFC2X3_types[894] = new entity(strings[1433], true, 894, (entity *)0);
  IFC2X3_types[895] =
      new entity(strings[1434], false, 895, (entity *)IFC2X3_types[894]);
  IFC2X3_types[896] =
      new entity(strings[1435], false, 896, (entity *)IFC2X3_types[894]);
  IFC2X3_types[897] = new entity(strings[1436], false, 897, (entity *)0);
  IFC2X3_types[903] =
      new entity(strings[1437], false, 903, (entity *)IFC2X3_types[483]);
  IFC2X3_types[908] = new entity(strings[1438], true, 908, (entity *)0);
  IFC2X3_types[910] = new entity(strings[1439], false, 910, (entity *)0);
  IFC2X3_types[913] = new entity(strings[1440], false, 913, (entity *)0);
  IFC2X3_types[915] =
      new entity(strings[1441], true, 915, (entity *)IFC2X3_types[720]);
  IFC2X3_types[916] =
      new entity(strings[1442], false, 916, (entity *)IFC2X3_types[756]);
  IFC2X3_types[937] = new entity(strings[1443], false, 937, (entity *)0);
  IFC2X3_types[946] =
      new entity(strings[1444], false, 946, (entity *)IFC2X3_types[915]);
  IFC2X3_types[947] = new entity(strings[1445], false, 947, (entity *)0);
  IFC2X3_types[949] =
      new entity(strings[1446], false, 949, (entity *)IFC2X3_types[946]);
  IFC2X3_types[953] = new entity(strings[1447], false, 953, (entity *)0);
  IFC2X3_types[964] =
      new entity(strings[1448], false, 964, (entity *)IFC2X3_types[483]);
  IFC2X3_types[8] = new select_type(
      strings[1449], 8,
      {IFC2X3_types[531], IFC2X3_types[545], IFC2X3_types[546]});
  IFC2X3_types[39] = new select_type(
      strings[1450], 39,
      {IFC2X3_types[486], IFC2X3_types[505], IFC2X3_types[650]});
  IFC2X3_types[78] = new type_declaration(strings[1451], 78,
                                          new named_type(IFC2X3_types[429]));
  IFC2X3_types[107] = new select_type(strings[1452], 107, {IFC2X3_types[889]});
  IFC2X3_types[142] = new select_type(strings[1453], 142,
                                      {IFC2X3_types[429], IFC2X3_types[486]});
  IFC2X3_types[206] =
      new select_type(strings[1454], 206,
                      {IFC2X3_types[97], IFC2X3_types[205], IFC2X3_types[460]});
  IFC2X3_types[210] = new select_type(strings[1455], 210,
                                      {IFC2X3_types[324], IFC2X3_types[587]});
  IFC2X3_types[211] =
      new select_type(strings[1456], 211,
                      {IFC2X3_types[1],   IFC2X3_types[2],   IFC2X3_types[26],
                       IFC2X3_types[135], IFC2X3_types[192], IFC2X3_types[255],
                       IFC2X3_types[268], IFC2X3_types[278], IFC2X3_types[279],
                       IFC2X3_types[280], IFC2X3_types[293], IFC2X3_types[296],
                       IFC2X3_types[310], IFC2X3_types[378], IFC2X3_types[379],
                       IFC2X3_types[406], IFC2X3_types[407], IFC2X3_types[413],
                       IFC2X3_types[415], IFC2X3_types[417], IFC2X3_types[421],
                       IFC2X3_types[425], IFC2X3_types[428], IFC2X3_types[454],
                       IFC2X3_types[455], IFC2X3_types[456], IFC2X3_types[457],
                       IFC2X3_types[465], IFC2X3_types[466], IFC2X3_types[468],
                       IFC2X3_types[469], IFC2X3_types[472], IFC2X3_types[473],
                       IFC2X3_types[475], IFC2X3_types[498], IFC2X3_types[499],
                       IFC2X3_types[500], IFC2X3_types[501], IFC2X3_types[502],
                       IFC2X3_types[503], IFC2X3_types[504], IFC2X3_types[505],
                       IFC2X3_types[547], IFC2X3_types[563], IFC2X3_types[581],
                       IFC2X3_types[596], IFC2X3_types[640], IFC2X3_types[733],
                       IFC2X3_types[734], IFC2X3_types[735], IFC2X3_types[744],
                       IFC2X3_types[742], IFC2X3_types[758], IFC2X3_types[774],
                       IFC2X3_types[775], IFC2X3_types[788], IFC2X3_types[874],
                       IFC2X3_types[898], IFC2X3_types[899], IFC2X3_types[900],
                       IFC2X3_types[904], IFC2X3_types[905], IFC2X3_types[914],
                       IFC2X3_types[917], IFC2X3_types[943], IFC2X3_types[955],
                       IFC2X3_types[960], IFC2X3_types[961]});
  IFC2X3_types[433] = new select_type(strings[1457], 433,
                                      {IFC2X3_types[718], IFC2X3_types[720]});
  IFC2X3_types[438] = new select_type(strings[1458], 438,
                                      {IFC2X3_types[436], IFC2X3_types[437]});
  IFC2X3_types[441] = new select_type(strings[1459], 441,
                                      {IFC2X3_types[326], IFC2X3_types[445]});
  IFC2X3_types[484] =
      new select_type(strings[1460], 484,
                      {IFC2X3_types[476], IFC2X3_types[479], IFC2X3_types[480],
                       IFC2X3_types[481], IFC2X3_types[482]});
  IFC2X3_types[496] = new select_type(strings[1461], 496,
                                      {IFC2X3_types[175], IFC2X3_types[206],
                                       IFC2X3_types[486], IFC2X3_types[868],
                                       IFC2X3_types[879], IFC2X3_types[908]});
  IFC2X3_types[512] = new type_declaration(strings[1462], 512,
                                           new named_type(IFC2X3_types[650]));
  IFC2X3_types[520] = new select_type(
      strings[1463], 520,
      {IFC2X3_types[11], IFC2X3_types[37], IFC2X3_types[97], IFC2X3_types[205],
       IFC2X3_types[326], IFC2X3_types[460], IFC2X3_types[476],
       IFC2X3_types[479], IFC2X3_types[482], IFC2X3_types[531],
       IFC2X3_types[545], IFC2X3_types[546], IFC2X3_types[908]});
  IFC2X3_types[579] = new type_declaration(strings[1464], 579,
                                           new named_type(IFC2X3_types[650]));
  IFC2X3_types[762] =
      new select_type(strings[1465], 762,
                      {IFC2X3_types[65], IFC2X3_types[412], IFC2X3_types[416],
                       IFC2X3_types[429], IFC2X3_types[461], IFC2X3_types[652],
                       IFC2X3_types[879]});
  IFC2X3_types[767] = new select_type(strings[1466], 767,
                                      {IFC2X3_types[216], IFC2X3_types[435],
                                       IFC2X3_types[512], IFC2X3_types[577],
                                       IFC2X3_types[579], IFC2X3_types[650]});
  IFC2X3_types[790] = new select_type(strings[1467], 790,
                                      {IFC2X3_types[789], IFC2X3_types[791]});
  IFC2X3_types[851] =
      new select_type(strings[1468], 851,
                      {IFC2X3_types[323], IFC2X3_types[852], IFC2X3_types[853],
                       IFC2X3_types[855], IFC2X3_types[856]});
  IFC2X3_types[883] = new select_type(strings[1469], 883,
                                      {IFC2X3_types[325], IFC2X3_types[589]});
  IFC2X3_types[890] = new select_type(strings[1470], 890,
                                      {IFC2X3_types[891], IFC2X3_types[892]});
  IFC2X3_types[934] = new select_type(
      strings[1471], 934,
      {IFC2X3_types[213], IFC2X3_types[506], IFC2X3_types[511]});
  IFC2X3_types[31] =
      new entity(strings[1472], true, 31, (entity *)IFC2X3_types[839]);
  IFC2X3_types[33] =
      new entity(strings[1473], false, 33, (entity *)IFC2X3_types[31]);
  IFC2X3_types[34] =
      new entity(strings[1474], false, 34, (entity *)IFC2X3_types[31]);
  IFC2X3_types[35] =
      new entity(strings[1475], false, 35, (entity *)IFC2X3_types[31]);
  IFC2X3_types[44] =
      new entity(strings[1476], false, 44, (entity *)IFC2X3_types[604]);
  IFC2X3_types[45] =
      new entity(strings[1477], false, 45, (entity *)IFC2X3_types[604]);
  IFC2X3_types[46] =
      new entity(strings[1478], false, 46, (entity *)IFC2X3_types[44]);
  IFC2X3_types[61] =
      new entity(strings[1479], false, 61, (entity *)IFC2X3_types[857]);
  IFC2X3_types[104] =
      new entity(strings[1480], false, 104, (entity *)IFC2X3_types[45]);
  IFC2X3_types[119] =
      new entity(strings[1481], false, 119, (entity *)IFC2X3_types[326]);
  IFC2X3_types[125] =
      new entity(strings[1482], false, 125, (entity *)IFC2X3_types[126]);
  IFC2X3_types[131] =
      new entity(strings[1483], false, 131, (entity *)IFC2X3_types[615]);
  IFC2X3_types[134] =
      new entity(strings[1484], false, 134, (entity *)IFC2X3_types[604]);
  IFC2X3_types[144] =
      new entity(strings[1485], false, 144, (entity *)IFC2X3_types[915]);
  IFC2X3_types[145] =
      new entity(strings[1486], false, 145, (entity *)IFC2X3_types[146]);
  IFC2X3_types[147] =
      new entity(strings[1487], false, 147, (entity *)IFC2X3_types[148]);
  IFC2X3_types[162] =
      new entity(strings[1488], false, 162, (entity *)IFC2X3_types[511]);
  IFC2X3_types[166] =
      new entity(strings[1489], false, 166, (entity *)IFC2X3_types[511]);
  IFC2X3_types[197] =
      new entity(strings[1490], false, 197, (entity *)IFC2X3_types[593]);
  IFC2X3_types[212] =
      new entity(strings[1491], false, 212, (entity *)IFC2X3_types[604]);
  IFC2X3_types[219] =
      new entity(strings[1492], false, 219, (entity *)IFC2X3_types[258]);
  IFC2X3_types[225] =
      new entity(strings[1493], false, 225, (entity *)IFC2X3_types[258]);
  IFC2X3_types[244] =
      new entity(strings[1494], false, 244, (entity *)IFC2X3_types[326]);
  IFC2X3_types[261] =
      new entity(strings[1495], false, 261, (entity *)IFC2X3_types[589]);
  IFC2X3_types[269] =
      new entity(strings[1496], false, 269, (entity *)IFC2X3_types[915]);
  IFC2X3_types[270] =
      new entity(strings[1497], false, 270, (entity *)IFC2X3_types[269]);
  IFC2X3_types[321] =
      new entity(strings[1498], false, 321, (entity *)IFC2X3_types[483]);
  IFC2X3_types[328] =
      new entity(strings[1499], false, 328, (entity *)IFC2X3_types[915]);
  IFC2X3_types[330] =
      new entity(strings[1500], false, 330, (entity *)IFC2X3_types[915]);
  IFC2X3_types[331] =
      new entity(strings[1501], false, 331, (entity *)IFC2X3_types[330]);
  IFC2X3_types[332] =
      new entity(strings[1502], false, 332, (entity *)IFC2X3_types[328]);
  IFC2X3_types[335] =
      new entity(strings[1503], false, 335, (entity *)IFC2X3_types[806]);
  IFC2X3_types[343] =
      new entity(strings[1504], false, 343, (entity *)IFC2X3_types[593]);
  IFC2X3_types[380] =
      new entity(strings[1505], false, 380, (entity *)IFC2X3_types[483]);
  IFC2X3_types[387] =
      new entity(strings[1506], false, 387, (entity *)IFC2X3_types[483]);
  IFC2X3_types[388] =
      new entity(strings[1507], false, 388, (entity *)IFC2X3_types[605]);
  IFC2X3_types[391] =
      new entity(strings[1508], false, 391, (entity *)IFC2X3_types[719]);
  IFC2X3_types[392] =
      new entity(strings[1509], true, 392, (entity *)IFC2X3_types[720]);
  IFC2X3_types[393] =
      new entity(strings[1510], false, 393, (entity *)IFC2X3_types[391]);
  IFC2X3_types[394] =
      new entity(strings[1511], false, 394, (entity *)IFC2X3_types[392]);
  IFC2X3_types[400] =
      new entity(strings[1512], false, 400, (entity *)IFC2X3_types[519]);
  IFC2X3_types[402] =
      new entity(strings[1513], false, 402, (entity *)IFC2X3_types[392]);
  IFC2X3_types[411] =
      new entity(strings[1514], false, 411, (entity *)IFC2X3_types[483]);
  IFC2X3_types[414] =
      new entity(strings[1515], false, 414, (entity *)IFC2X3_types[857]);
  IFC2X3_types[422] =
      new entity(strings[1516], false, 422, (entity *)IFC2X3_types[908]);
  IFC2X3_types[446] =
      new entity(strings[1517], true, 446, (entity *)IFC2X3_types[392]);
  IFC2X3_types[447] =
      new entity(strings[1518], false, 447, (entity *)IFC2X3_types[446]);
  IFC2X3_types[448] =
      new entity(strings[1519], false, 448, (entity *)IFC2X3_types[446]);
  IFC2X3_types[449] =
      new entity(strings[1520], false, 449, (entity *)IFC2X3_types[446]);
  IFC2X3_types[450] =
      new entity(strings[1521], false, 450, (entity *)IFC2X3_types[446]);
  IFC2X3_types[451] =
      new entity(strings[1522], false, 451, (entity *)IFC2X3_types[450]);
  IFC2X3_types[459] =
      new entity(strings[1523], false, 459, (entity *)IFC2X3_types[519]);
  IFC2X3_types[463] =
      new entity(strings[1524], false, 463, (entity *)IFC2X3_types[915]);
  IFC2X3_types[471] =
      new entity(strings[1525], false, 471, (entity *)IFC2X3_types[720]);
  IFC2X3_types[478] =
      new entity(strings[1526], false, 478, (entity *)IFC2X3_types[602]);
  IFC2X3_types[487] =
      new entity(strings[1527], false, 487, (entity *)IFC2X3_types[490]);
  IFC2X3_types[516] =
      new entity(strings[1528], true, 516, (entity *)IFC2X3_types[732]);
  IFC2X3_types[526] =
      new entity(strings[1529], false, 526, (entity *)IFC2X3_types[392]);
  IFC2X3_types[528] =
      new entity(strings[1530], false, 528, (entity *)IFC2X3_types[144]);
  IFC2X3_types[534] =
      new entity(strings[1531], false, 534, (entity *)IFC2X3_types[269]);
  IFC2X3_types[538] =
      new entity(strings[1532], true, 538, (entity *)IFC2X3_types[604]);
  IFC2X3_types[540] =
      new entity(strings[1533], false, 540, (entity *)IFC2X3_types[915]);
  IFC2X3_types[548] =
      new entity(strings[1534], false, 548, (entity *)IFC2X3_types[550]);
  IFC2X3_types[559] =
      new entity(strings[1535], false, 559, (entity *)IFC2X3_types[857]);
  IFC2X3_types[560] =
      new entity(strings[1536], true, 560, (entity *)IFC2X3_types[392]);
  IFC2X3_types[562] =
      new entity(strings[1537], false, 562, (entity *)IFC2X3_types[392]);
  IFC2X3_types[569] =
      new entity(strings[1538], true, 569, (entity *)IFC2X3_types[392]);
  IFC2X3_types[570] =
      new entity(strings[1539], false, 570, (entity *)IFC2X3_types[569]);
  IFC2X3_types[571] =
      new entity(strings[1540], false, 571, (entity *)IFC2X3_types[569]);
  IFC2X3_types[575] =
      new entity(strings[1541], false, 575, (entity *)IFC2X3_types[463]);
  IFC2X3_types[573] =
      new entity(strings[1542], false, 573, (entity *)IFC2X3_types[402]);
  IFC2X3_types[582] =
      new entity(strings[1543], true, 582, (entity *)IFC2X3_types[585]);
  IFC2X3_types[583] =
      new entity(strings[1544], true, 583, (entity *)IFC2X3_types[585]);
  IFC2X3_types[584] =
      new entity(strings[1545], false, 584, (entity *)IFC2X3_types[587]);
  IFC2X3_types[586] =
      new entity(strings[1546], false, 586, (entity *)IFC2X3_types[587]);
  IFC2X3_types[601] =
      new entity(strings[1547], false, 601, (entity *)IFC2X3_types[602]);
  IFC2X3_types[616] =
      new entity(strings[1548], false, 616, (entity *)IFC2X3_types[761]);
  IFC2X3_types[618] =
      new entity(strings[1549], true, 618, (entity *)IFC2X3_types[732]);
  IFC2X3_types[620] =
      new entity(strings[1550], false, 620, (entity *)IFC2X3_types[761]);
  IFC2X3_types[622] =
      new entity(strings[1551], false, 622, (entity *)IFC2X3_types[761]);
  IFC2X3_types[623] =
      new entity(strings[1552], false, 623, (entity *)IFC2X3_types[761]);
  IFC2X3_types[625] =
      new entity(strings[1553], true, 625, (entity *)IFC2X3_types[618]);
  IFC2X3_types[626] =
      new entity(strings[1554], false, 626, (entity *)IFC2X3_types[761]);
  IFC2X3_types[628] =
      new entity(strings[1555], false, 628, (entity *)IFC2X3_types[761]);
  IFC2X3_types[654] =
      new entity(strings[1556], false, 654, (entity *)IFC2X3_types[538]);
  IFC2X3_types[659] =
      new entity(strings[1557], false, 659, (entity *)IFC2X3_types[908]);
  IFC2X3_types[661] =
      new entity(strings[1558], false, 661, (entity *)IFC2X3_types[625]);
  IFC2X3_types[686] =
      new entity(strings[1559], true, 686, (entity *)IFC2X3_types[732]);
  IFC2X3_types[737] =
      new entity(strings[1560], false, 737, (entity *)IFC2X3_types[654]);
  IFC2X3_types[743] =
      new entity(strings[1561], false, 743, (entity *)IFC2X3_types[392]);
  IFC2X3_types[752] =
      new entity(strings[1562], false, 752, (entity *)IFC2X3_types[625]);
  IFC2X3_types[760] =
      new entity(strings[1563], false, 760, (entity *)IFC2X3_types[392]);
  IFC2X3_types[771] =
      new entity(strings[1564], false, 771, (entity *)IFC2X3_types[806]);
  IFC2X3_types[773] =
      new entity(strings[1565], true, 773, (entity *)IFC2X3_types[392]);
  IFC2X3_types[776] =
      new entity(strings[1566], false, 776, (entity *)IFC2X3_types[625]);
  IFC2X3_types[778] =
      new entity(strings[1567], false, 778, (entity *)IFC2X3_types[625]);
  IFC2X3_types[783] =
      new entity(strings[1568], false, 783, (entity *)IFC2X3_types[625]);
  IFC2X3_types[816] =
      new entity(strings[1569], false, 816, (entity *)IFC2X3_types[822]);
  IFC2X3_types[817] =
      new entity(strings[1570], false, 817, (entity *)IFC2X3_types[822]);
  IFC2X3_types[818] =
      new entity(strings[1571], false, 818, (entity *)IFC2X3_types[822]);
  IFC2X3_types[819] =
      new entity(strings[1572], false, 819, (entity *)IFC2X3_types[818]);
  IFC2X3_types[820] =
      new entity(strings[1573], false, 820, (entity *)IFC2X3_types[822]);
  IFC2X3_types[821] =
      new entity(strings[1574], false, 821, (entity *)IFC2X3_types[820]);
  IFC2X3_types[830] =
      new entity(strings[1575], false, 830, (entity *)IFC2X3_types[388]);
  IFC2X3_types[833] =
      new entity(strings[1576], false, 833, (entity *)IFC2X3_types[830]);
  IFC2X3_types[843] =
      new entity(strings[1577], false, 843, (entity *)IFC2X3_types[269]);
  IFC2X3_types[844] =
      new entity(strings[1578], true, 844, (entity *)IFC2X3_types[392]);
  IFC2X3_types[854] =
      new entity(strings[1579], false, 854, (entity *)IFC2X3_types[855]);
  IFC2X3_types[859] =
      new entity(strings[1580], true, 859, (entity *)IFC2X3_types[773]);
  IFC2X3_types[860] =
      new entity(strings[1581], false, 860, (entity *)IFC2X3_types[773]);
  IFC2X3_types[861] =
      new entity(strings[1582], true, 861, (entity *)IFC2X3_types[844]);
  IFC2X3_types[928] =
      new entity(strings[1583], false, 928, (entity *)IFC2X3_types[538]);
  IFC2X3_types[878] =
      new entity(strings[1584], false, 878, (entity *)IFC2X3_types[34]);
  IFC2X3_types[884] =
      new entity(strings[1585], false, 884, (entity *)IFC2X3_types[392]);
  IFC2X3_types[885] =
      new entity(strings[1586], false, 885, (entity *)IFC2X3_types[884]);
  IFC2X3_types[924] =
      new entity(strings[1587], false, 924, (entity *)IFC2X3_types[538]);
  IFC2X3_types[931] =
      new entity(strings[1588], false, 931, (entity *)IFC2X3_types[526]);
  IFC2X3_types[932] =
      new entity(strings[1589], false, 932, (entity *)IFC2X3_types[516]);
  IFC2X3_types[933] =
      new entity(strings[1590], false, 933, (entity *)IFC2X3_types[932]);
  IFC2X3_types[939] =
      new entity(strings[1591], false, 939, (entity *)IFC2X3_types[538]);
  IFC2X3_types[944] =
      new entity(strings[1592], false, 944, (entity *)IFC2X3_types[392]);
  IFC2X3_types[948] =
      new entity(strings[1593], false, 948, (entity *)IFC2X3_types[463]);
  IFC2X3_types[966] =
      new entity(strings[1594], false, 966, (entity *)IFC2X3_types[625]);
  IFC2X3_types[969] =
      new entity(strings[1595], false, 969, (entity *)IFC2X3_types[625]);
  IFC2X3_types[970] =
      new entity(strings[1596], false, 970, (entity *)IFC2X3_types[933]);
  IFC2X3_types[979] =
      new entity(strings[1597], false, 979, (entity *)IFC2X3_types[538]);
  IFC2X3_types[118] = new select_type(strings[1598], 118,
                                      {IFC2X3_types[116], IFC2X3_types[119]});
  IFC2X3_types[123] = new select_type(strings[1599], 123,
                                      {IFC2X3_types[126], IFC2X3_types[582]});
  IFC2X3_types[124] = new select_type(strings[1600], 124,
                                      {IFC2X3_types[125], IFC2X3_types[512]});
  IFC2X3_types[201] = new select_type(strings[1601], 201,
                                      {IFC2X3_types[198], IFC2X3_types[583]});
  IFC2X3_types[245] = new select_type(strings[1602], 245,
                                      {IFC2X3_types[242], IFC2X3_types[244]});
  IFC2X3_types[403] = new select_type(strings[1603], 403,
                                      {IFC2X3_types[526], IFC2X3_types[577]});
  IFC2X3_types[485] =
      new select_type(strings[1604], 485,
                      {IFC2X3_types[22],  IFC2X3_types[47],  IFC2X3_types[130],
                       IFC2X3_types[161], IFC2X3_types[176], IFC2X3_types[216],
                       IFC2X3_types[282], IFC2X3_types[435], IFC2X3_types[467],
                       IFC2X3_types[474], IFC2X3_types[512], IFC2X3_types[514],
                       IFC2X3_types[539], IFC2X3_types[565], IFC2X3_types[577],
                       IFC2X3_types[578], IFC2X3_types[579], IFC2X3_types[650],
                       IFC2X3_types[772], IFC2X3_types[906], IFC2X3_types[907],
                       IFC2X3_types[954]});
  IFC2X3_types[572] = new select_type(strings[1605], 572,
                                      {IFC2X3_types[569], IFC2X3_types[949]});
  IFC2X3_types[595] = new select_type(strings[1606], 595,
                                      {IFC2X3_types[197], IFC2X3_types[343],
                                       IFC2X3_types[513], IFC2X3_types[850],
                                       IFC2X3_types[864], IFC2X3_types[887]});
  IFC2X3_types[865] = new select_type(strings[1607], 865, {IFC2X3_types[123]});
  IFC2X3_types[940] = new select_type(
      strings[1608], 940,
      {IFC2X3_types[211], IFC2X3_types[485], IFC2X3_types[762]});
  IFC2X3_types[28] =
      new entity(strings[1609], false, 28, (entity *)IFC2X3_types[31]);
  IFC2X3_types[29] =
      new entity(strings[1610], false, 29, (entity *)IFC2X3_types[392]);
  IFC2X3_types[30] =
      new entity(strings[1611], false, 30, (entity *)IFC2X3_types[31]);
  IFC2X3_types[32] =
      new entity(strings[1612], false, 32, (entity *)IFC2X3_types[392]);
  IFC2X3_types[52] =
      new entity(strings[1613], false, 52, (entity *)IFC2X3_types[560]);
  IFC2X3_types[54] =
      new entity(strings[1614], false, 54, (entity *)IFC2X3_types[560]);
  IFC2X3_types[55] =
      new entity(strings[1615], false, 55, (entity *)IFC2X3_types[560]);
  IFC2X3_types[69] =
      new entity(strings[1616], false, 69, (entity *)IFC2X3_types[392]);
  IFC2X3_types[76] =
      new entity(strings[1617], false, 76, (entity *)IFC2X3_types[844]);
  IFC2X3_types[77] =
      new entity(strings[1618], false, 77, (entity *)IFC2X3_types[392]);
  IFC2X3_types[79] =
      new entity(strings[1619], false, 79, (entity *)IFC2X3_types[402]);
  IFC2X3_types[186] =
      new entity(strings[1620], false, 186, (entity *)IFC2X3_types[538]);
  IFC2X3_types[98] =
      new entity(strings[1621], false, 98, (entity *)IFC2X3_types[569]);
  IFC2X3_types[99] =
      new entity(strings[1622], true, 99, (entity *)IFC2X3_types[392]);
  IFC2X3_types[100] =
      new entity(strings[1623], false, 100, (entity *)IFC2X3_types[99]);
  IFC2X3_types[101] =
      new entity(strings[1624], false, 101, (entity *)IFC2X3_types[100]);
  IFC2X3_types[102] =
      new entity(strings[1625], false, 102, (entity *)IFC2X3_types[99]);
  IFC2X3_types[103] =
      new entity(strings[1626], false, 103, (entity *)IFC2X3_types[102]);
  IFC2X3_types[112] =
      new entity(strings[1627], false, 112, (entity *)IFC2X3_types[538]);
  IFC2X3_types[120] =
      new entity(strings[1628], false, 120, (entity *)IFC2X3_types[144]);
  IFC2X3_types[133] =
      new entity(strings[1629], false, 133, (entity *)IFC2X3_types[392]);
  IFC2X3_types[180] =
      new entity(strings[1630], false, 180, (entity *)IFC2X3_types[538]);
  IFC2X3_types[181] =
      new entity(strings[1631], false, 181, (entity *)IFC2X3_types[538]);
  IFC2X3_types[183] =
      new entity(strings[1632], true, 183, (entity *)IFC2X3_types[392]);
  IFC2X3_types[185] =
      new entity(strings[1633], false, 185, (entity *)IFC2X3_types[773]);
  IFC2X3_types[193] =
      new entity(strings[1634], true, 193, (entity *)IFC2X3_types[392]);
  IFC2X3_types[194] =
      new entity(strings[1635], false, 194, (entity *)IFC2X3_types[76]);
  IFC2X3_types[209] =
      new entity(strings[1636], false, 209, (entity *)IFC2X3_types[392]);
  IFC2X3_types[221] =
      new entity(strings[1637], false, 221, (entity *)IFC2X3_types[28]);
  IFC2X3_types[223] =
      new entity(strings[1638], false, 223, (entity *)IFC2X3_types[878]);
  IFC2X3_types[226] =
      new entity(strings[1639], false, 226, (entity *)IFC2X3_types[392]);
  IFC2X3_types[248] =
      new entity(strings[1640], false, 248, (entity *)IFC2X3_types[625]);
  IFC2X3_types[251] =
      new entity(strings[1641], false, 251, (entity *)IFC2X3_types[625]);
  IFC2X3_types[252] =
      new entity(strings[1642], false, 252, (entity *)IFC2X3_types[933]);
  IFC2X3_types[256] =
      new entity(strings[1643], false, 256, (entity *)IFC2X3_types[392]);
  IFC2X3_types[259] =
      new entity(strings[1644], false, 259, (entity *)IFC2X3_types[582]);
  IFC2X3_types[260] =
      new entity(strings[1645], false, 260, (entity *)IFC2X3_types[583]);
  IFC2X3_types[272] =
      new entity(strings[1646], false, 272, (entity *)IFC2X3_types[463]);
  IFC2X3_types[304] =
      new entity(strings[1647], false, 304, (entity *)IFC2X3_types[625]);
  IFC2X3_types[305] =
      new entity(strings[1648], true, 305, (entity *)IFC2X3_types[933]);
  IFC2X3_types[298] =
      new entity(strings[1649], true, 298, (entity *)IFC2X3_types[844]);
  IFC2X3_types[307] =
      new entity(strings[1650], false, 307, (entity *)IFC2X3_types[538]);
  IFC2X3_types[311] =
      new entity(strings[1651], false, 311, (entity *)IFC2X3_types[625]);
  IFC2X3_types[327] =
      new entity(strings[1652], false, 327, (entity *)IFC2X3_types[859]);
  IFC2X3_types[329] =
      new entity(strings[1653], false, 329, (entity *)IFC2X3_types[392]);
  IFC2X3_types[344] =
      new entity(strings[1654], false, 344, (entity *)IFC2X3_types[392]);
  IFC2X3_types[347] =
      new entity(strings[1655], false, 347, (entity *)IFC2X3_types[392]);
  IFC2X3_types[345] =
      new entity(strings[1656], false, 345, (entity *)IFC2X3_types[392]);
  IFC2X3_types[372] =
      new entity(strings[1657], false, 372, (entity *)IFC2X3_types[625]);
  IFC2X3_types[382] =
      new entity(strings[1658], false, 382, (entity *)IFC2X3_types[305]);
  IFC2X3_types[384] =
      new entity(strings[1659], false, 384, (entity *)IFC2X3_types[382]);
  IFC2X3_types[389] =
      new entity(strings[1660], false, 389, (entity *)IFC2X3_types[394]);
  IFC2X3_types[424] =
      new entity(strings[1661], false, 424, (entity *)IFC2X3_types[538]);
  IFC2X3_types[464] =
      new entity(strings[1662], false, 464, (entity *)IFC2X3_types[538]);
  IFC2X3_types[452] =
      new entity(strings[1663], false, 452, (entity *)IFC2X3_types[193]);
  IFC2X3_types[470] =
      new entity(strings[1664], true, 470, (entity *)IFC2X3_types[773]);
  IFC2X3_types[515] =
      new entity(strings[1665], true, 515, (entity *)IFC2X3_types[516]);
  IFC2X3_types[524] =
      new entity(strings[1666], false, 524, (entity *)IFC2X3_types[193]);
  IFC2X3_types[525] =
      new entity(strings[1667], false, 525, (entity *)IFC2X3_types[193]);
  IFC2X3_types[543] =
      new entity(strings[1668], false, 543, (entity *)IFC2X3_types[625]);
  IFC2X3_types[561] =
      new entity(strings[1669], false, 561, (entity *)IFC2X3_types[562]);
  IFC2X3_types[564] =
      new entity(strings[1670], false, 564, (entity *)IFC2X3_types[298]);
  IFC2X3_types[599] =
      new entity(strings[1671], true, 599, (entity *)IFC2X3_types[515]);
  IFC2X3_types[600] =
      new entity(strings[1672], true, 600, (entity *)IFC2X3_types[515]);
  IFC2X3_types[607] =
      new entity(strings[1673], false, 607, (entity *)IFC2X3_types[515]);
  IFC2X3_types[609] =
      new entity(strings[1674], false, 609, (entity *)IFC2X3_types[28]);
  IFC2X3_types[624] =
      new entity(strings[1675], false, 624, (entity *)IFC2X3_types[625]);
  IFC2X3_types[631] =
      new entity(strings[1676], false, 631, (entity *)IFC2X3_types[600]);
  IFC2X3_types[653] =
      new entity(strings[1677], false, 653, (entity *)IFC2X3_types[654]);
  IFC2X3_types[655] =
      new entity(strings[1678], false, 655, (entity *)IFC2X3_types[183]);
  IFC2X3_types[656] =
      new entity(strings[1679], false, 656, (entity *)IFC2X3_types[76]);
  IFC2X3_types[668] =
      new entity(strings[1680], true, 668, (entity *)IFC2X3_types[686]);
  IFC2X3_types[670] =
      new entity(strings[1681], false, 670, (entity *)IFC2X3_types[668]);
  IFC2X3_types[671] =
      new entity(strings[1682], false, 671, (entity *)IFC2X3_types[668]);
  IFC2X3_types[672] =
      new entity(strings[1683], false, 672, (entity *)IFC2X3_types[668]);
  IFC2X3_types[673] =
      new entity(strings[1684], false, 673, (entity *)IFC2X3_types[668]);
  IFC2X3_types[674] =
      new entity(strings[1685], false, 674, (entity *)IFC2X3_types[668]);
  IFC2X3_types[675] =
      new entity(strings[1686], false, 675, (entity *)IFC2X3_types[671]);
  IFC2X3_types[676] =
      new entity(strings[1687], false, 676, (entity *)IFC2X3_types[668]);
  IFC2X3_types[677] =
      new entity(strings[1688], false, 677, (entity *)IFC2X3_types[686]);
  IFC2X3_types[678] =
      new entity(strings[1689], false, 678, (entity *)IFC2X3_types[677]);
  IFC2X3_types[679] =
      new entity(strings[1690], false, 679, (entity *)IFC2X3_types[677]);
  IFC2X3_types[680] =
      new entity(strings[1691], false, 680, (entity *)IFC2X3_types[677]);
  IFC2X3_types[681] =
      new entity(strings[1692], false, 681, (entity *)IFC2X3_types[677]);
  IFC2X3_types[682] =
      new entity(strings[1693], false, 682, (entity *)IFC2X3_types[677]);
  IFC2X3_types[683] =
      new entity(strings[1694], false, 683, (entity *)IFC2X3_types[677]);
  IFC2X3_types[684] =
      new entity(strings[1695], false, 684, (entity *)IFC2X3_types[677]);
  IFC2X3_types[685] =
      new entity(strings[1696], false, 685, (entity *)IFC2X3_types[677]);
  IFC2X3_types[688] =
      new entity(strings[1697], true, 688, (entity *)IFC2X3_types[686]);
  IFC2X3_types[689] =
      new entity(strings[1698], false, 689, (entity *)IFC2X3_types[688]);
  IFC2X3_types[690] =
      new entity(strings[1699], false, 690, (entity *)IFC2X3_types[689]);
  IFC2X3_types[692] =
      new entity(strings[1700], false, 692, (entity *)IFC2X3_types[688]);
  IFC2X3_types[691] =
      new entity(strings[1701], false, 691, (entity *)IFC2X3_types[688]);
  IFC2X3_types[693] =
      new entity(strings[1702], false, 693, (entity *)IFC2X3_types[688]);
  IFC2X3_types[694] =
      new entity(strings[1703], false, 694, (entity *)IFC2X3_types[688]);
  IFC2X3_types[695] =
      new entity(strings[1704], false, 695, (entity *)IFC2X3_types[688]);
  IFC2X3_types[696] =
      new entity(strings[1705], false, 696, (entity *)IFC2X3_types[695]);
  IFC2X3_types[697] =
      new entity(strings[1706], false, 697, (entity *)IFC2X3_types[689]);
  IFC2X3_types[698] =
      new entity(strings[1707], false, 698, (entity *)IFC2X3_types[688]);
  IFC2X3_types[699] =
      new entity(strings[1708], false, 699, (entity *)IFC2X3_types[688]);
  IFC2X3_types[700] =
      new entity(strings[1709], false, 700, (entity *)IFC2X3_types[688]);
  IFC2X3_types[701] =
      new entity(strings[1710], true, 701, (entity *)IFC2X3_types[686]);
  IFC2X3_types[702] =
      new entity(strings[1711], true, 702, (entity *)IFC2X3_types[686]);
  IFC2X3_types[703] =
      new entity(strings[1712], false, 703, (entity *)IFC2X3_types[702]);
  IFC2X3_types[704] =
      new entity(strings[1713], false, 704, (entity *)IFC2X3_types[702]);
  IFC2X3_types[705] =
      new entity(strings[1714], false, 705, (entity *)IFC2X3_types[688]);
  IFC2X3_types[706] =
      new entity(strings[1715], false, 706, (entity *)IFC2X3_types[688]);
  IFC2X3_types[707] =
      new entity(strings[1716], false, 707, (entity *)IFC2X3_types[688]);
  IFC2X3_types[708] =
      new entity(strings[1717], false, 708, (entity *)IFC2X3_types[701]);
  IFC2X3_types[709] =
      new entity(strings[1718], false, 709, (entity *)IFC2X3_types[670]);
  IFC2X3_types[710] =
      new entity(strings[1719], false, 710, (entity *)IFC2X3_types[703]);
  IFC2X3_types[711] =
      new entity(strings[1720], false, 711, (entity *)IFC2X3_types[688]);
  IFC2X3_types[712] =
      new entity(strings[1721], false, 712, (entity *)IFC2X3_types[688]);
  IFC2X3_types[713] =
      new entity(strings[1722], false, 713, (entity *)IFC2X3_types[671]);
  IFC2X3_types[714] =
      new entity(strings[1723], false, 714, (entity *)IFC2X3_types[688]);
  IFC2X3_types[715] =
      new entity(strings[1724], false, 715, (entity *)IFC2X3_types[688]);
  IFC2X3_types[716] =
      new entity(strings[1725], false, 716, (entity *)IFC2X3_types[688]);
  IFC2X3_types[717] =
      new entity(strings[1726], false, 717, (entity *)IFC2X3_types[688]);
  IFC2X3_types[722] =
      new entity(strings[1727], true, 722, (entity *)IFC2X3_types[515]);
  IFC2X3_types[724] =
      new entity(strings[1728], false, 724, (entity *)IFC2X3_types[859]);
  IFC2X3_types[727] =
      new entity(strings[1729], false, 727, (entity *)IFC2X3_types[183]);
  IFC2X3_types[728] =
      new entity(strings[1730], false, 728, (entity *)IFC2X3_types[183]);
  IFC2X3_types[786] =
      new entity(strings[1731], true, 786, (entity *)IFC2X3_types[600]);
  IFC2X3_types[787] =
      new entity(strings[1732], true, 787, (entity *)IFC2X3_types[305]);
  IFC2X3_types[792] =
      new entity(strings[1733], false, 792, (entity *)IFC2X3_types[183]);
  IFC2X3_types[802] =
      new entity(strings[1734], true, 802, (entity *)IFC2X3_types[600]);
  IFC2X3_types[811] =
      new entity(strings[1735], true, 811, (entity *)IFC2X3_types[600]);
  IFC2X3_types[824] =
      new entity(strings[1736], true, 824, (entity *)IFC2X3_types[811]);
  IFC2X3_types[831] =
      new entity(strings[1737], true, 831, (entity *)IFC2X3_types[802]);
  IFC2X3_types[835] =
      new entity(strings[1738], false, 835, (entity *)IFC2X3_types[824]);
  IFC2X3_types[836] =
      new entity(strings[1739], false, 836, (entity *)IFC2X3_types[835]);
  IFC2X3_types[838] =
      new entity(strings[1740], false, 838, (entity *)IFC2X3_types[256]);
  IFC2X3_types[845] =
      new entity(strings[1741], false, 845, (entity *)IFC2X3_types[859]);
  IFC2X3_types[846] =
      new entity(strings[1742], false, 846, (entity *)IFC2X3_types[861]);
  IFC2X3_types[847] =
      new entity(strings[1743], false, 847, (entity *)IFC2X3_types[861]);
  IFC2X3_types[867] =
      new entity(strings[1744], false, 867, (entity *)IFC2X3_types[382]);
  IFC2X3_types[872] =
      new entity(strings[1745], false, 872, (entity *)IFC2X3_types[599]);
  IFC2X3_types[922] =
      new entity(strings[1746], false, 922, (entity *)IFC2X3_types[305]);
  IFC2X3_types[53] =
      new select_type(strings[1747], 53, {IFC2X3_types[54], IFC2X3_types[55]});
  IFC2X3_types[67] = new select_type(strings[1748], 67,
                                     {IFC2X3_types[69], IFC2X3_types[183],
                                      IFC2X3_types[402], IFC2X3_types[773]});
  IFC2X3_types[184] = new select_type(strings[1749], 184,
                                      {IFC2X3_types[69], IFC2X3_types[183]});
  IFC2X3_types[195] = new select_type(strings[1750], 195,
                                      {IFC2X3_types[199], IFC2X3_types[201]});
  IFC2X3_types[257] =
      new select_type(strings[1751], 257,
                      {IFC2X3_types[28], IFC2X3_types[34], IFC2X3_types[35]});
  IFC2X3_types[346] = new select_type(strings[1752], 346, {IFC2X3_types[347]});
  IFC2X3_types[348] = new select_type(strings[1753], 348,
                                      {IFC2X3_types[123], IFC2X3_types[322],
                                       IFC2X3_types[344], IFC2X3_types[345]});
  IFC2X3_types[395] = new select_type(
      strings[1754], 395,
      {IFC2X3_types[193], IFC2X3_types[569], IFC2X3_types[844]});
  IFC2X3_types[533] = new select_type(strings[1755], 533,
                                      {IFC2X3_types[226], IFC2X3_types[565]});
  IFC2X3_types[759] = new select_type(strings[1756], 759,
                                      {IFC2X3_types[120], IFC2X3_types[528]});
  IFC2X3_types[848] = new select_type(
      strings[1757], 848,
      {IFC2X3_types[329], IFC2X3_types[332], IFC2X3_types[844]});
  IFC2X3_types[927] = new select_type(strings[1758], 927,
                                      {IFC2X3_types[98], IFC2X3_types[539]});
  IFC2X3_types[945] = new select_type(strings[1759], 945,
                                      {IFC2X3_types[226], IFC2X3_types[944]});
  IFC2X3_types[6] =
      new entity(strings[1760], false, 6, (entity *)IFC2X3_types[515]);
  IFC2X3_types[27] =
      new entity(strings[1761], false, 27, (entity *)IFC2X3_types[600]);
  IFC2X3_types[51] =
      new entity(strings[1762], false, 51, (entity *)IFC2X3_types[424]);
  IFC2X3_types[62] =
      new entity(strings[1763], false, 62, (entity *)IFC2X3_types[183]);
  IFC2X3_types[66] =
      new entity(strings[1764], false, 66, (entity *)IFC2X3_types[69]);
  IFC2X3_types[75] =
      new entity(strings[1765], true, 75, (entity *)IFC2X3_types[193]);
  IFC2X3_types[82] =
      new entity(strings[1766], false, 82, (entity *)IFC2X3_types[786]);
  IFC2X3_types[89] =
      new entity(strings[1767], true, 89, (entity *)IFC2X3_types[305]);
  IFC2X3_types[90] =
      new entity(strings[1768], false, 90, (entity *)IFC2X3_types[786]);
  IFC2X3_types[111] =
      new entity(strings[1769], false, 111, (entity *)IFC2X3_types[112]);
  IFC2X3_types[128] =
      new entity(strings[1770], false, 128, (entity *)IFC2X3_types[89]);
  IFC2X3_types[132] =
      new entity(strings[1771], false, 132, (entity *)IFC2X3_types[75]);
  IFC2X3_types[143] =
      new entity(strings[1772], true, 143, (entity *)IFC2X3_types[193]);
  IFC2X3_types[160] =
      new entity(strings[1773], true, 160, (entity *)IFC2X3_types[722]);
  IFC2X3_types[163] =
      new entity(strings[1774], true, 163, (entity *)IFC2X3_types[515]);
  IFC2X3_types[172] =
      new entity(strings[1775], false, 172, (entity *)IFC2X3_types[163]);
  IFC2X3_types[173] =
      new entity(strings[1776], false, 173, (entity *)IFC2X3_types[163]);
  IFC2X3_types[178] =
      new entity(strings[1777], false, 178, (entity *)IFC2X3_types[89]);
  IFC2X3_types[182] =
      new entity(strings[1778], false, 182, (entity *)IFC2X3_types[160]);
  IFC2X3_types[190] =
      new entity(strings[1779], false, 190, (entity *)IFC2X3_types[89]);
  IFC2X3_types[222] =
      new entity(strings[1780], false, 222, (entity *)IFC2X3_types[256]);
  IFC2X3_types[236] =
      new entity(strings[1781], false, 236, (entity *)IFC2X3_types[305]);
  IFC2X3_types[238] =
      new entity(strings[1782], true, 238, (entity *)IFC2X3_types[236]);
  IFC2X3_types[273] =
      new entity(strings[1783], false, 273, (entity *)IFC2X3_types[311]);
  IFC2X3_types[297] =
      new entity(strings[1784], true, 297, (entity *)IFC2X3_types[600]);
  IFC2X3_types[299] =
      new entity(strings[1785], false, 299, (entity *)IFC2X3_types[297]);
  IFC2X3_types[301] =
      new entity(strings[1786], true, 301, (entity *)IFC2X3_types[297]);
  IFC2X3_types[302] =
      new entity(strings[1787], true, 302, (entity *)IFC2X3_types[305]);
  IFC2X3_types[306] =
      new entity(strings[1788], false, 306, (entity *)IFC2X3_types[143]);
  IFC2X3_types[309] =
      new entity(strings[1789], true, 309, (entity *)IFC2X3_types[238]);
  IFC2X3_types[315] =
      new entity(strings[1790], false, 315, (entity *)IFC2X3_types[297]);
  IFC2X3_types[316] =
      new entity(strings[1791], false, 316, (entity *)IFC2X3_types[163]);
  IFC2X3_types[317] =
      new entity(strings[1792], false, 317, (entity *)IFC2X3_types[309]);
  IFC2X3_types[319] =
      new entity(strings[1793], false, 319, (entity *)IFC2X3_types[309]);
  IFC2X3_types[333] =
      new entity(strings[1794], false, 333, (entity *)IFC2X3_types[470]);
  IFC2X3_types[334] =
      new entity(strings[1795], false, 334, (entity *)IFC2X3_types[470]);
  IFC2X3_types[338] =
      new entity(strings[1796], false, 338, (entity *)IFC2X3_types[301]);
  IFC2X3_types[339] =
      new entity(strings[1797], false, 339, (entity *)IFC2X3_types[302]);
  IFC2X3_types[340] =
      new entity(strings[1798], true, 340, (entity *)IFC2X3_types[297]);
  IFC2X3_types[341] =
      new entity(strings[1799], true, 341, (entity *)IFC2X3_types[340]);
  IFC2X3_types[342] =
      new entity(strings[1800], true, 342, (entity *)IFC2X3_types[340]);
  IFC2X3_types[354] =
      new entity(strings[1801], true, 354, (entity *)IFC2X3_types[238]);
  IFC2X3_types[357] =
      new entity(strings[1802], true, 357, (entity *)IFC2X3_types[238]);
  IFC2X3_types[360] =
      new entity(strings[1803], false, 360, (entity *)IFC2X3_types[354]);
  IFC2X3_types[363] =
      new entity(strings[1804], true, 363, (entity *)IFC2X3_types[238]);
  IFC2X3_types[365] =
      new entity(strings[1805], true, 365, (entity *)IFC2X3_types[238]);
  IFC2X3_types[367] =
      new entity(strings[1806], true, 367, (entity *)IFC2X3_types[238]);
  IFC2X3_types[369] =
      new entity(strings[1807], true, 369, (entity *)IFC2X3_types[238]);
  IFC2X3_types[371] =
      new entity(strings[1808], true, 371, (entity *)IFC2X3_types[238]);
  IFC2X3_types[381] =
      new entity(strings[1809], false, 381, (entity *)IFC2X3_types[297]);
  IFC2X3_types[383] =
      new entity(strings[1810], false, 383, (entity *)IFC2X3_types[163]);
  IFC2X3_types[385] =
      new entity(strings[1811], false, 385, (entity *)IFC2X3_types[369]);
  IFC2X3_types[398] =
      new entity(strings[1812], false, 398, (entity *)IFC2X3_types[600]);
  IFC2X3_types[401] =
      new entity(strings[1813], false, 401, (entity *)IFC2X3_types[515]);
  IFC2X3_types[404] =
      new entity(strings[1814], false, 404, (entity *)IFC2X3_types[309]);
  IFC2X3_types[409] =
      new entity(strings[1815], false, 409, (entity *)IFC2X3_types[309]);
  IFC2X3_types[419] =
      new entity(strings[1816], false, 419, (entity *)IFC2X3_types[401]);
  IFC2X3_types[426] =
      new entity(strings[1817], false, 426, (entity *)IFC2X3_types[357]);
  IFC2X3_types[430] =
      new entity(strings[1818], false, 430, (entity *)IFC2X3_types[160]);
  IFC2X3_types[431] =
      new entity(strings[1819], false, 431, (entity *)IFC2X3_types[369]);
  IFC2X3_types[443] =
      new entity(strings[1820], false, 443, (entity *)IFC2X3_types[369]);
  IFC2X3_types[453] =
      new entity(strings[1821], false, 453, (entity *)IFC2X3_types[222]);
  IFC2X3_types[488] =
      new entity(strings[1822], false, 488, (entity *)IFC2X3_types[338]);
  IFC2X3_types[489] =
      new entity(strings[1823], false, 489, (entity *)IFC2X3_types[339]);
  IFC2X3_types[493] =
      new entity(strings[1824], false, 493, (entity *)IFC2X3_types[89]);
  IFC2X3_types[508] =
      new entity(strings[1825], false, 508, (entity *)IFC2X3_types[309]);
  IFC2X3_types[510] =
      new entity(strings[1826], false, 510, (entity *)IFC2X3_types[872]);
  IFC2X3_types[522] =
      new entity(strings[1827], false, 522, (entity *)IFC2X3_types[6]);
  IFC2X3_types[527] =
      new entity(strings[1828], false, 527, (entity *)IFC2X3_types[342]);
  IFC2X3_types[530] =
      new entity(strings[1829], false, 530, (entity *)IFC2X3_types[872]);
  IFC2X3_types[535] =
      new entity(strings[1830], false, 535, (entity *)IFC2X3_types[369]);
  IFC2X3_types[541] =
      new entity(strings[1831], false, 541, (entity *)IFC2X3_types[163]);
  IFC2X3_types[544] =
      new entity(strings[1832], false, 544, (entity *)IFC2X3_types[163]);
  IFC2X3_types[555] =
      new entity(strings[1833], false, 555, (entity *)IFC2X3_types[357]);
  IFC2X3_types[557] =
      new entity(strings[1834], false, 557, (entity *)IFC2X3_types[365]);
  IFC2X3_types[567] =
      new entity(strings[1835], false, 567, (entity *)IFC2X3_types[89]);
  IFC2X3_types[574] =
      new entity(strings[1836], false, 574, (entity *)IFC2X3_types[75]);
  IFC2X3_types[576] =
      new entity(strings[1837], true, 576, (entity *)IFC2X3_types[600]);
  IFC2X3_types[597] =
      new entity(strings[1838], false, 597, (entity *)IFC2X3_types[599]);
  IFC2X3_types[611] =
      new entity(strings[1839], false, 611, (entity *)IFC2X3_types[163]);
  IFC2X3_types[612] =
      new entity(strings[1840], false, 612, (entity *)IFC2X3_types[163]);
  IFC2X3_types[610] =
      new entity(strings[1841], false, 610, (entity *)IFC2X3_types[341]);
  IFC2X3_types[629] =
      new entity(strings[1842], false, 629, (entity *)IFC2X3_types[354]);
  IFC2X3_types[632] =
      new entity(strings[1843], false, 632, (entity *)IFC2X3_types[363]);
  IFC2X3_types[641] =
      new entity(strings[1844], false, 641, (entity *)IFC2X3_types[222]);
  IFC2X3_types[643] =
      new entity(strings[1845], false, 643, (entity *)IFC2X3_types[89]);
  IFC2X3_types[647] =
      new entity(strings[1846], false, 647, (entity *)IFC2X3_types[89]);
  IFC2X3_types[667] =
      new entity(strings[1847], false, 667, (entity *)IFC2X3_types[701]);
  IFC2X3_types[669] =
      new entity(strings[1848], false, 669, (entity *)IFC2X3_types[671]);
  IFC2X3_types[738] =
      new entity(strings[1849], false, 738, (entity *)IFC2X3_types[369]);
  IFC2X3_types[740] =
      new entity(strings[1850], false, 740, (entity *)IFC2X3_types[163]);
  IFC2X3_types[751] =
      new entity(strings[1851], false, 751, (entity *)IFC2X3_types[163]);
  IFC2X3_types[764] =
      new entity(strings[1852], false, 764, (entity *)IFC2X3_types[786]);
  IFC2X3_types[769] =
      new entity(strings[1853], false, 769, (entity *)IFC2X3_types[89]);
  IFC2X3_types[779] =
      new entity(strings[1854], false, 779, (entity *)IFC2X3_types[786]);
  IFC2X3_types[780] =
      new entity(strings[1855], false, 780, (entity *)IFC2X3_types[309]);
  IFC2X3_types[782] =
      new entity(strings[1856], false, 782, (entity *)IFC2X3_types[163]);
  IFC2X3_types[784] =
      new entity(strings[1857], false, 784, (entity *)IFC2X3_types[787]);
  IFC2X3_types[793] =
      new entity(strings[1858], false, 793, (entity *)IFC2X3_types[369]);
  IFC2X3_types[797] =
      new entity(strings[1859], false, 797, (entity *)IFC2X3_types[89]);
  IFC2X3_types[801] =
      new entity(strings[1860], true, 801, (entity *)IFC2X3_types[802]);
  IFC2X3_types[805] =
      new entity(strings[1861], true, 805, (entity *)IFC2X3_types[811]);
  IFC2X3_types[807] =
      new entity(strings[1862], false, 807, (entity *)IFC2X3_types[805]);
  IFC2X3_types[808] =
      new entity(strings[1863], false, 808, (entity *)IFC2X3_types[824]);
  IFC2X3_types[809] =
      new entity(strings[1864], false, 809, (entity *)IFC2X3_types[808]);
  IFC2X3_types[812] =
      new entity(strings[1865], false, 812, (entity *)IFC2X3_types[801]);
  IFC2X3_types[813] =
      new entity(strings[1866], false, 813, (entity *)IFC2X3_types[812]);
  IFC2X3_types[815] =
      new entity(strings[1867], false, 815, (entity *)IFC2X3_types[401]);
  IFC2X3_types[825] =
      new entity(strings[1868], false, 825, (entity *)IFC2X3_types[801]);
  IFC2X3_types[826] =
      new entity(strings[1869], false, 826, (entity *)IFC2X3_types[825]);
  IFC2X3_types[827] =
      new entity(strings[1870], false, 827, (entity *)IFC2X3_types[801]);
  IFC2X3_types[828] =
      new entity(strings[1871], false, 828, (entity *)IFC2X3_types[805]);
  IFC2X3_types[829] =
      new entity(strings[1872], false, 829, (entity *)IFC2X3_types[831]);
  IFC2X3_types[832] =
      new entity(strings[1873], false, 832, (entity *)IFC2X3_types[401]);
  IFC2X3_types[834] =
      new entity(strings[1874], false, 834, (entity *)IFC2X3_types[805]);
  IFC2X3_types[842] =
      new entity(strings[1875], false, 842, (entity *)IFC2X3_types[160]);
  IFC2X3_types[862] =
      new entity(strings[1876], false, 862, (entity *)IFC2X3_types[354]);
  IFC2X3_types[866] =
      new entity(strings[1877], false, 866, (entity *)IFC2X3_types[401]);
  IFC2X3_types[870] =
      new entity(strings[1878], false, 870, (entity *)IFC2X3_types[367]);
  IFC2X3_types[911] =
      new entity(strings[1879], false, 911, (entity *)IFC2X3_types[163]);
  IFC2X3_types[918] =
      new entity(strings[1880], false, 918, (entity *)IFC2X3_types[309]);
  IFC2X3_types[921] =
      new entity(strings[1881], false, 921, (entity *)IFC2X3_types[297]);
  IFC2X3_types[925] =
      new entity(strings[1882], false, 925, (entity *)IFC2X3_types[75]);
  IFC2X3_types[929] =
      new entity(strings[1883], false, 929, (entity *)IFC2X3_types[309]);
  IFC2X3_types[935] =
      new entity(strings[1884], false, 935, (entity *)IFC2X3_types[309]);
  IFC2X3_types[941] =
      new entity(strings[1885], false, 941, (entity *)IFC2X3_types[354]);
  IFC2X3_types[952] =
      new entity(strings[1886], false, 952, (entity *)IFC2X3_types[297]);
  IFC2X3_types[958] =
      new entity(strings[1887], false, 958, (entity *)IFC2X3_types[89]);
  IFC2X3_types[962] =
      new entity(strings[1888], false, 962, (entity *)IFC2X3_types[369]);
  IFC2X3_types[973] =
      new entity(strings[1889], true, 973, (entity *)IFC2X3_types[163]);
  IFC2X3_types[975] =
      new entity(strings[1890], false, 975, (entity *)IFC2X3_types[973]);
  IFC2X3_types[976] =
      new entity(strings[1891], false, 976, (entity *)IFC2X3_types[973]);
  IFC2X3_types[978] =
      new entity(strings[1892], false, 978, (entity *)IFC2X3_types[401]);
  IFC2X3_types[196] = new select_type(strings[1893], 196,
                                      {IFC2X3_types[75], IFC2X3_types[270]});
  IFC2X3_types[803] = new select_type(strings[1894], 803,
                                      {IFC2X3_types[297], IFC2X3_types[811]});
  IFC2X3_types[0] =
      new entity(strings[1895], false, 0, (entity *)IFC2X3_types[132]);
  IFC2X3_types[3] =
      new entity(strings[1896], false, 3, (entity *)IFC2X3_types[163]);
  IFC2X3_types[14] =
      new entity(strings[1897], false, 14, (entity *)IFC2X3_types[354]);
  IFC2X3_types[16] =
      new entity(strings[1898], false, 16, (entity *)IFC2X3_types[369]);
  IFC2X3_types[18] =
      new entity(strings[1899], false, 18, (entity *)IFC2X3_types[309]);
  IFC2X3_types[25] =
      new entity(strings[1900], false, 25, (entity *)IFC2X3_types[222]);
  IFC2X3_types[50] =
      new entity(strings[1901], false, 50, (entity *)IFC2X3_types[401]);
  IFC2X3_types[80] =
      new entity(strings[1902], true, 80, (entity *)IFC2X3_types[75]);
  IFC2X3_types[57] =
      new entity(strings[1903], false, 57, (entity *)IFC2X3_types[89]);
  IFC2X3_types[60] =
      new entity(strings[1904], false, 60, (entity *)IFC2X3_types[80]);
  IFC2X3_types[63] =
      new entity(strings[1905], false, 63, (entity *)IFC2X3_types[309]);
  IFC2X3_types[83] =
      new entity(strings[1906], true, 83, (entity *)IFC2X3_types[297]);
  IFC2X3_types[84] =
      new entity(strings[1907], true, 84, (entity *)IFC2X3_types[83]);
  IFC2X3_types[85] =
      new entity(strings[1908], false, 85, (entity *)IFC2X3_types[84]);
  IFC2X3_types[86] =
      new entity(strings[1909], false, 86, (entity *)IFC2X3_types[83]);
  IFC2X3_types[87] =
      new entity(strings[1910], false, 87, (entity *)IFC2X3_types[89]);
  IFC2X3_types[91] =
      new entity(strings[1911], false, 91, (entity *)IFC2X3_types[357]);
  IFC2X3_types[93] =
      new entity(strings[1912], false, 93, (entity *)IFC2X3_types[365]);
  IFC2X3_types[95] =
      new entity(strings[1913], false, 95, (entity *)IFC2X3_types[365]);
  IFC2X3_types[108] =
      new entity(strings[1914], false, 108, (entity *)IFC2X3_types[309]);
  IFC2X3_types[110] =
      new entity(strings[1915], false, 110, (entity *)IFC2X3_types[143]);
  IFC2X3_types[121] =
      new entity(strings[1916], false, 121, (entity *)IFC2X3_types[309]);
  IFC2X3_types[127] =
      new entity(strings[1917], false, 127, (entity *)IFC2X3_types[83]);
  IFC2X3_types[136] =
      new entity(strings[1918], false, 136, (entity *)IFC2X3_types[363]);
  IFC2X3_types[138] =
      new entity(strings[1919], false, 138, (entity *)IFC2X3_types[309]);
  IFC2X3_types[140] =
      new entity(strings[1920], false, 140, (entity *)IFC2X3_types[401]);
  IFC2X3_types[141] =
      new entity(strings[1921], false, 141, (entity *)IFC2X3_types[163]);
  IFC2X3_types[157] =
      new entity(strings[1922], false, 157, (entity *)IFC2X3_types[160]);
  IFC2X3_types[158] =
      new entity(strings[1923], false, 158, (entity *)IFC2X3_types[160]);
  IFC2X3_types[159] =
      new entity(strings[1924], false, 159, (entity *)IFC2X3_types[160]);
  IFC2X3_types[167] =
      new entity(strings[1925], false, 167, (entity *)IFC2X3_types[309]);
  IFC2X3_types[169] =
      new entity(strings[1926], false, 169, (entity *)IFC2X3_types[309]);
  IFC2X3_types[177] =
      new entity(strings[1927], false, 177, (entity *)IFC2X3_types[83]);
  IFC2X3_types[189] =
      new entity(strings[1928], false, 189, (entity *)IFC2X3_types[83]);
  IFC2X3_types[202] =
      new entity(strings[1929], false, 202, (entity *)IFC2X3_types[354]);
  IFC2X3_types[217] =
      new entity(strings[1930], false, 217, (entity *)IFC2X3_types[222]);
  IFC2X3_types[228] =
      new entity(strings[1931], false, 228, (entity *)IFC2X3_types[301]);
  IFC2X3_types[229] =
      new entity(strings[1932], false, 229, (entity *)IFC2X3_types[302]);
  IFC2X3_types[231] =
      new entity(strings[1933], false, 231, (entity *)IFC2X3_types[238]);
  IFC2X3_types[234] =
      new entity(strings[1934], true, 234, (entity *)IFC2X3_types[236]);
  IFC2X3_types[235] =
      new entity(strings[1935], false, 235, (entity *)IFC2X3_types[297]);
  IFC2X3_types[237] =
      new entity(strings[1936], false, 237, (entity *)IFC2X3_types[235]);
  IFC2X3_types[239] =
      new entity(strings[1937], false, 239, (entity *)IFC2X3_types[576]);
  IFC2X3_types[247] =
      new entity(strings[1938], false, 247, (entity *)IFC2X3_types[83]);
  IFC2X3_types[262] =
      new entity(strings[1939], false, 262, (entity *)IFC2X3_types[357]);
  IFC2X3_types[264] =
      new entity(strings[1940], false, 264, (entity *)IFC2X3_types[365]);
  IFC2X3_types[266] =
      new entity(strings[1941], false, 266, (entity *)IFC2X3_types[371]);
  IFC2X3_types[271] =
      new entity(strings[1942], true, 271, (entity *)IFC2X3_types[342]);
  IFC2X3_types[276] =
      new entity(strings[1943], false, 276, (entity *)IFC2X3_types[369]);
  IFC2X3_types[285] =
      new entity(strings[1944], false, 285, (entity *)IFC2X3_types[367]);
  IFC2X3_types[287] =
      new entity(strings[1945], false, 287, (entity *)IFC2X3_types[309]);
  IFC2X3_types[289] =
      new entity(strings[1946], false, 289, (entity *)IFC2X3_types[369]);
  IFC2X3_types[291] =
      new entity(strings[1947], false, 291, (entity *)IFC2X3_types[309]);
  IFC2X3_types[294] =
      new entity(strings[1948], false, 294, (entity *)IFC2X3_types[354]);
  IFC2X3_types[274] =
      new entity(strings[1949], false, 274, (entity *)IFC2X3_types[866]);
  IFC2X3_types[275] =
      new entity(strings[1950], false, 275, (entity *)IFC2X3_types[297]);
  IFC2X3_types[308] =
      new entity(strings[1951], false, 308, (entity *)IFC2X3_types[237]);
  IFC2X3_types[336] =
      new entity(strings[1952], false, 336, (entity *)IFC2X3_types[363]);
  IFC2X3_types[349] =
      new entity(strings[1953], false, 349, (entity *)IFC2X3_types[371]);
  IFC2X3_types[351] =
      new entity(strings[1954], false, 351, (entity *)IFC2X3_types[369]);
  IFC2X3_types[353] =
      new entity(strings[1955], false, 353, (entity *)IFC2X3_types[237]);
  IFC2X3_types[356] =
      new entity(strings[1956], false, 356, (entity *)IFC2X3_types[237]);
  IFC2X3_types[358] =
      new entity(strings[1957], false, 358, (entity *)IFC2X3_types[234]);
  IFC2X3_types[362] =
      new entity(strings[1958], false, 362, (entity *)IFC2X3_types[237]);
  IFC2X3_types[364] =
      new entity(strings[1959], false, 364, (entity *)IFC2X3_types[237]);
  IFC2X3_types[366] =
      new entity(strings[1960], false, 366, (entity *)IFC2X3_types[237]);
  IFC2X3_types[368] =
      new entity(strings[1961], false, 368, (entity *)IFC2X3_types[237]);
  IFC2X3_types[370] =
      new entity(strings[1962], false, 370, (entity *)IFC2X3_types[237]);
  IFC2X3_types[376] =
      new entity(strings[1963], false, 376, (entity *)IFC2X3_types[83]);
  IFC2X3_types[492] =
      new entity(strings[1964], false, 492, (entity *)IFC2X3_types[83]);
  IFC2X3_types[552] =
      new entity(strings[1965], false, 552, (entity *)IFC2X3_types[83]);
  IFC2X3_types[566] =
      new entity(strings[1966], false, 566, (entity *)IFC2X3_types[83]);
  IFC2X3_types[642] =
      new entity(strings[1967], false, 642, (entity *)IFC2X3_types[83]);
  IFC2X3_types[645] =
      new entity(strings[1968], false, 645, (entity *)IFC2X3_types[83]);
  IFC2X3_types[646] =
      new entity(strings[1969], false, 646, (entity *)IFC2X3_types[83]);
  IFC2X3_types[651] =
      new entity(strings[1970], false, 651, (entity *)IFC2X3_types[60]);
  IFC2X3_types[665] =
      new entity(strings[1971], true, 665, (entity *)IFC2X3_types[84]);
  IFC2X3_types[666] =
      new entity(strings[1972], false, 666, (entity *)IFC2X3_types[665]);
  IFC2X3_types[730] =
      new entity(strings[1973], false, 730, (entity *)IFC2X3_types[83]);
  IFC2X3_types[736] =
      new entity(strings[1974], false, 736, (entity *)IFC2X3_types[271]);
  IFC2X3_types[748] =
      new entity(strings[1975], false, 748, (entity *)IFC2X3_types[234]);
  IFC2X3_types[768] =
      new entity(strings[1976], false, 768, (entity *)IFC2X3_types[83]);
  IFC2X3_types[795] =
      new entity(strings[1977], false, 795, (entity *)IFC2X3_types[83]);
  IFC2X3_types[796] =
      new entity(strings[1978], false, 796, (entity *)IFC2X3_types[83]);
  IFC2X3_types[804] =
      new entity(strings[1979], false, 804, (entity *)IFC2X3_types[866]);
  IFC2X3_types[875] =
      new entity(strings[1980], false, 875, (entity *)IFC2X3_types[665]);
  IFC2X3_types[876] =
      new entity(strings[1981], false, 876, (entity *)IFC2X3_types[665]);
  IFC2X3_types[950] =
      new entity(strings[1982], false, 950, (entity *)IFC2X3_types[229]);
  IFC2X3_types[956] =
      new entity(strings[1983], false, 956, (entity *)IFC2X3_types[83]);
  IFC2X3_types[957] =
      new entity(strings[1984], false, 957, (entity *)IFC2X3_types[956]);
  IFC2X3_types[965] =
      new entity(strings[1985], false, 965, (entity *)IFC2X3_types[83]);
  IFC2X3_types[9] =
      new entity(strings[1986], false, 9, (entity *)IFC2X3_types[234]);
  IFC2X3_types[20] =
      new entity(strings[1987], false, 20, (entity *)IFC2X3_types[234]);
  IFC2X3_types[56] =
      new entity(strings[1988], false, 56, (entity *)IFC2X3_types[83]);
  IFC2X3_types[105] =
      new entity(strings[1989], false, 105, (entity *)IFC2X3_types[271]);
  IFC2X3_types[164] =
      new entity(strings[1990], false, 164, (entity *)IFC2X3_types[234]);
  IFC2X3_types[230] =
      new entity(strings[1991], false, 230, (entity *)IFC2X3_types[237]);
  IFC2X3_types[233] =
      new entity(strings[1992], false, 233, (entity *)IFC2X3_types[235]);
  IFC2X3_types[283] =
      new entity(strings[1993], false, 283, (entity *)IFC2X3_types[353]);
  IFC2X3_types[662] =
      new entity(strings[1994], false, 662, (entity *)IFC2X3_types[665]);
  ((entity *)IFC2X3_types[0])->set_attributes({}, {false, false});
  ((entity *)IFC2X3_types[3])
      ->set_attributes(
          {new attribute(strings[1995], new named_type(IFC2X3_types[412]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[6])
      ->set_attributes({new attribute(strings[1996],
                                      new named_type(IFC2X3_types[8]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[7])
      ->set_attributes({new attribute(strings[1997],
                                      new named_type(IFC2X3_types[729]), false),
                        new attribute(strings[1998],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[9])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[10]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[11])
      ->set_attributes(
          {new attribute(strings[2001], new named_type(IFC2X3_types[12]), true),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2002], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false});
  ((entity *)IFC2X3_types[14])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[15]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[16])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[17]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[18])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[19]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[20])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[21]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[25])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[27])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[28])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[29])
      ->set_attributes({new attribute(strings[2003],
                                      new named_type(IFC2X3_types[193]), false),
                        new attribute(strings[2004],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[193])),
                                      true)},
                       {false, false});
  ((entity *)IFC2X3_types[30])
      ->set_attributes({new attribute(strings[2005],
                                      new named_type(IFC2X3_types[569]), true),
                        new attribute(strings[2006],
                                      new named_type(IFC2X3_types[397]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[31])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[32])
      ->set_attributes({new attribute(strings[2007],
                                      new named_type(IFC2X3_types[392]), false),
                        new attribute(strings[2008],
                                      new named_type(IFC2X3_types[894]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[33])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[34])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[35])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[36])
      ->set_attributes(
          {new attribute(strings[2009], new named_type(IFC2X3_types[531]),
                         false),
           new attribute(strings[2010], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[2011], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[2012], new named_type(IFC2X3_types[412]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[37])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2014], new named_type(IFC2X3_types[39]), true),
           new attribute(strings[2015], new named_type(IFC2X3_types[486]),
                         true),
           new attribute(strings[2016], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2017], new named_type(IFC2X3_types[206]),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[38])
      ->set_attributes(
          {new attribute(strings[2018], new named_type(IFC2X3_types[37]),
                         false),
           new attribute(strings[2019],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC2X3_types[37])),
                         false),
           new attribute(strings[2020], new named_type(IFC2X3_types[48]),
                         false),
           new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[40])
      ->set_attributes(
          {new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2021], new named_type(IFC2X3_types[206]),
                         false),
           new attribute(strings[2022], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2023], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2024], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[2025], new named_type(IFC2X3_types[412]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[41])
      ->set_attributes(
          {new attribute(strings[2026], new named_type(IFC2X3_types[8]), false),
           new attribute(strings[2027], new named_type(IFC2X3_types[40]),
                         false),
           new attribute(strings[1997], new named_type(IFC2X3_types[7]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[42])
      ->set_attributes({new attribute(strings[2028],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[615])),
                                      false),
                        new attribute(strings[2027],
                                      new named_type(IFC2X3_types[40]), false)},
                       {false, false});
  ((entity *)IFC2X3_types[43])
      ->set_attributes(
          {new attribute(strings[2029], new named_type(IFC2X3_types[40]),
                         false),
           new attribute(strings[2030], new named_type(IFC2X3_types[40]),
                         false),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[44])
      ->set_attributes(
          {new attribute(strings[2031], new named_type(IFC2X3_types[193]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[45])
      ->set_attributes({new attribute(strings[2032],
                                      new named_type(IFC2X3_types[75]), false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[46])
      ->set_attributes({new attribute(strings[2033],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[193])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[50])
      ->set_attributes(
          {new attribute(strings[2034], new named_type(IFC2X3_types[412]),
                         false),
           new attribute(strings[2035], new named_type(IFC2X3_types[175]),
                         false),
           new attribute(strings[2036], new named_type(IFC2X3_types[175]),
                         false),
           new attribute(strings[2037], new named_type(IFC2X3_types[175]),
                         false),
           new attribute(strings[2038], new named_type(IFC2X3_types[8]), false),
           new attribute(strings[2039], new named_type(IFC2X3_types[8]), false),
           new attribute(strings[2040], new named_type(IFC2X3_types[545]),
                         false),
           new attribute(strings[2041], new named_type(IFC2X3_types[97]),
                         false),
           new attribute(strings[2042], new named_type(IFC2X3_types[175]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC2X3_types[51])
      ->set_attributes({new attribute(strings[2043],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2044],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2045],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2046],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC2X3_types[52])
      ->set_attributes({new attribute(strings[2047],
                                      new named_type(IFC2X3_types[226]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[54])
      ->set_attributes({new attribute(strings[2048],
                                      new named_type(IFC2X3_types[226]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[55])
      ->set_attributes({new attribute(strings[2047],
                                      new named_type(IFC2X3_types[226]), true),
                        new attribute(strings[2048],
                                      new named_type(IFC2X3_types[226]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[80])
      ->set_attributes(
          {new attribute(strings[2049],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2050],
                         new aggregation_type(aggregation_type::list_type, 2,
                                              -1,
                                              new named_type(IFC2X3_types[98])),
                         false),
           new attribute(strings[2051], new named_type(IFC2X3_types[81]),
                         false),
           new attribute(strings[2052],
                         new simple_type(simple_type::logical_type), false),
           new attribute(strings[2053],
                         new simple_type(simple_type::logical_type), false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[56])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[57])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[58]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[60])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[61])
      ->set_attributes(
          {new attribute(strings[2054], new named_type(IFC2X3_types[412]),
                         false),
           new attribute(strings[2055],
                         new simple_type(simple_type::boolean_type), false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[62])
      ->set_attributes(
          {new attribute(strings[2056], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2057], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2058], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[63])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[64]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[66])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[69])
      ->set_attributes({new attribute(strings[2059],
                                      new named_type(IFC2X3_types[68]), false),
                        new attribute(strings[2060],
                                      new named_type(IFC2X3_types[67]), false),
                        new attribute(strings[2061],
                                      new named_type(IFC2X3_types[67]), false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[70])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false});
  ((entity *)IFC2X3_types[71])
      ->set_attributes({new attribute(strings[2062],
                                      new named_type(IFC2X3_types[499]), true),
                        new attribute(strings[2063],
                                      new named_type(IFC2X3_types[499]), true),
                        new attribute(strings[2064],
                                      new named_type(IFC2X3_types[499]), true),
                        new attribute(strings[2065],
                                      new named_type(IFC2X3_types[500]), true),
                        new attribute(strings[2066],
                                      new named_type(IFC2X3_types[500]), true),
                        new attribute(strings[2067],
                                      new named_type(IFC2X3_types[500]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[72])
      ->set_attributes({new attribute(strings[2068],
                                      new named_type(IFC2X3_types[501]), true),
                        new attribute(strings[2069],
                                      new named_type(IFC2X3_types[501]), true),
                        new attribute(strings[2070],
                                      new named_type(IFC2X3_types[501]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[73])
      ->set_attributes({new attribute(strings[2071],
                                      new named_type(IFC2X3_types[456]), true),
                        new attribute(strings[2072],
                                      new named_type(IFC2X3_types[456]), true),
                        new attribute(strings[2073],
                                      new named_type(IFC2X3_types[456]), true),
                        new attribute(strings[2074],
                                      new named_type(IFC2X3_types[735]), true),
                        new attribute(strings[2075],
                                      new named_type(IFC2X3_types[735]), true),
                        new attribute(strings[2076],
                                      new named_type(IFC2X3_types[735]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[74])
      ->set_attributes(
          {new attribute(strings[2077], new named_type(IFC2X3_types[961]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[75])->set_attributes({}, {});
  ((entity *)IFC2X3_types[76])->set_attributes({}, {});
  ((entity *)IFC2X3_types[77])
      ->set_attributes(
          {new attribute(strings[2078], new named_type(IFC2X3_types[98]),
                         false),
           new attribute(strings[2079], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2080], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2081], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[79])
      ->set_attributes({new attribute(strings[2082],
                                      new named_type(IFC2X3_types[77]), false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[82])
      ->set_attributes({new attribute(strings[2083],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2084],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2085],
                                      new named_type(IFC2X3_types[580]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC2X3_types[83])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[84])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[85])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[86])
      ->set_attributes(
          {new attribute(strings[2086], new named_type(IFC2X3_types[303]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[87])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[88]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[89])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[90])
      ->set_attributes({new attribute(strings[2087],
                                      new named_type(IFC2X3_types[435]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[186])
      ->set_attributes(
          {new attribute(strings[2088], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2089], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2090], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2091], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2092], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2093], new named_type(IFC2X3_types[577]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[91])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[92]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[93])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[94]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[95])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[96]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[97])
      ->set_attributes(
          {new attribute(strings[2094], new named_type(IFC2X3_types[207]),
                         false),
           new attribute(strings[2095], new named_type(IFC2X3_types[507]),
                         false),
           new attribute(strings[2096], new named_type(IFC2X3_types[977]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[98])
      ->set_attributes({new attribute(strings[2097],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, 3,
                                          new named_type(IFC2X3_types[435])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[99])
      ->set_attributes(
          {new attribute(strings[2098], new named_type(IFC2X3_types[226]),
                         true),
           new attribute(strings[2099], new named_type(IFC2X3_types[226]),
                         true),
           new attribute(strings[2100], new named_type(IFC2X3_types[98]),
                         false),
           new attribute(strings[2101], new simple_type(simple_type::real_type),
                         true)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[100])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[101])
      ->set_attributes(
          {new attribute(strings[2102], new simple_type(simple_type::real_type),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[102])
      ->set_attributes({new attribute(strings[2103],
                                      new named_type(IFC2X3_types[226]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[103])
      ->set_attributes(
          {new attribute(strings[2102], new simple_type(simple_type::real_type),
                         true),
           new attribute(strings[2104], new simple_type(simple_type::real_type),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[104])
      ->set_attributes(
          {new attribute(strings[2105], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[105])
      ->set_attributes({new attribute(strings[2089],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2106],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC2X3_types[108])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[109]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[110])
      ->set_attributes(
          {new attribute(strings[2107], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[111])
      ->set_attributes(
          {new attribute(strings[2090], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[112])
      ->set_attributes(
          {new attribute(strings[2107], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[113])
      ->set_attributes(
          {new attribute(strings[2108], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[2109], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[2110], new named_type(IFC2X3_types[97]), true),
           new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[114])
      ->set_attributes(
          {new attribute(strings[2111], new named_type(IFC2X3_types[117]),
                         false),
           new attribute(strings[2112], new named_type(IFC2X3_types[113]),
                         true),
           new attribute(strings[2113], new named_type(IFC2X3_types[429]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[115])
      ->set_attributes({new attribute(strings[2114],
                                      new named_type(IFC2X3_types[114]), false),
                        new attribute(strings[2115],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[114])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[116])
      ->set_attributes({new attribute(strings[2116],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[117])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[117])
      ->set_attributes(
          {new attribute(strings[2117], new named_type(IFC2X3_types[429]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[119])
      ->set_attributes({new attribute(strings[2118],
                                      new named_type(IFC2X3_types[113]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[120])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[121])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[122]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[125])
      ->set_attributes(
          {new attribute(strings[2119], new named_type(IFC2X3_types[512]),
                         false),
           new attribute(strings[2120], new named_type(IFC2X3_types[512]),
                         false),
           new attribute(strings[2121], new named_type(IFC2X3_types[512]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[126])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false});
  ((entity *)IFC2X3_types[127])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[128])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[129]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[131])
      ->set_attributes({new attribute(strings[2122],
                                      new named_type(IFC2X3_types[412]), false),
                        new attribute(strings[2123],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[615])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[132])
      ->set_attributes(
          {new attribute(
               strings[2124],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[133])),
               false),
           new attribute(strings[2053],
                         new simple_type(simple_type::logical_type), false)},
          {false, false});
  ((entity *)IFC2X3_types[133])
      ->set_attributes(
          {new attribute(strings[2125], new named_type(IFC2X3_types[920]),
                         false),
           new attribute(strings[2126],
                         new simple_type(simple_type::boolean_type), false),
           new attribute(strings[2127], new named_type(IFC2X3_types[193]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[134])
      ->set_attributes({new attribute(strings[2128],
                                      new aggregation_type(
                                          aggregation_type::set_type, 2, -1,
                                          new named_type(IFC2X3_types[604])),
                                      false),
                        new attribute(strings[2129],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[136])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[137]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[138])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[139]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[140])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[141])
      ->set_attributes(
          {new attribute(strings[2130], new named_type(IFC2X3_types[142]),
                         false),
           new attribute(strings[2131], new named_type(IFC2X3_types[206]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[143])
      ->set_attributes({new attribute(strings[2132],
                                      new named_type(IFC2X3_types[53]), false)},
                       {false});
  ((entity *)IFC2X3_types[144])
      ->set_attributes({new attribute(strings[2133],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[328])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[145])
      ->set_attributes({new attribute(strings[2134],
                                      new named_type(IFC2X3_types[196]), false),
                        new attribute(strings[2135],
                                      new named_type(IFC2X3_types[196]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[146])->set_attributes({}, {});
  ((entity *)IFC2X3_types[147])
      ->set_attributes({new attribute(strings[2136],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2137],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2138],
                                      new named_type(IFC2X3_types[435]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[148])
      ->set_attributes({new attribute(strings[2139],
                                      new named_type(IFC2X3_types[572]), false),
                        new attribute(strings[2140],
                                      new named_type(IFC2X3_types[572]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[149])
      ->set_attributes(
          {new attribute(strings[2141], new named_type(IFC2X3_types[53]),
                         false),
           new attribute(strings[2142], new named_type(IFC2X3_types[53]), true),
           new attribute(strings[2143], new named_type(IFC2X3_types[604]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[150])
      ->set_attributes({new attribute(strings[2144],
                                      new named_type(IFC2X3_types[848]), false),
                        new attribute(strings[2145],
                                      new named_type(IFC2X3_types[848]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[152])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2146], new named_type(IFC2X3_types[155]),
                         false),
           new attribute(strings[2147], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2148], new named_type(IFC2X3_types[8]), true),
           new attribute(strings[2149], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2150], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[153])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2151], new named_type(IFC2X3_types[152]),
                         false),
           new attribute(
               strings[2152],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[152])),
               false),
           new attribute(strings[2153], new named_type(IFC2X3_types[462]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[154])
      ->set_attributes({new attribute(strings[2154],
                                      new named_type(IFC2X3_types[152]), false),
                        new attribute(strings[2155],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[118])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[156])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true),
                        new attribute(strings[2151],
                                      new named_type(IFC2X3_types[152]), false),
                        new attribute(strings[2152],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[152])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[157])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[158])
      ->set_attributes(
          {new attribute(strings[2156],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC2X3_types[8])),
                         true),
           new attribute(strings[2157], new named_type(IFC2X3_types[650]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[159])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[160])
      ->set_attributes(
          {new attribute(strings[2158], new named_type(IFC2X3_types[412]),
                         true),
           new attribute(strings[2159], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2160], new named_type(IFC2X3_types[723]),
                         true),
           new attribute(strings[2161], new named_type(IFC2X3_types[486]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[162])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[163])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[164])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[165]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[166])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[2162], new named_type(IFC2X3_types[486]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[167])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[168]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[169])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[170]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[171])
      ->set_attributes({new attribute(strings[2163],
                                      new named_type(IFC2X3_types[408]), false),
                        new attribute(strings[2164],
                                      new named_type(IFC2X3_types[497]), true),
                        new attribute(strings[2165],
                                      new named_type(IFC2X3_types[13]), false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[172])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[173])
      ->set_attributes(
          {new attribute(strings[2166], new named_type(IFC2X3_types[8]), true),
           new attribute(strings[2167], new named_type(IFC2X3_types[8]), true),
           new attribute(strings[2168], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2169], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2170],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC2X3_types[8])),
                         true),
           new attribute(strings[2171], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2172], new named_type(IFC2X3_types[412]),
                         false),
           new attribute(strings[2000], new named_type(IFC2X3_types[174]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC2X3_types[175])
      ->set_attributes(
          {new attribute(strings[2173], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[2174], new named_type(IFC2X3_types[879]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[177])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[179]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[178])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[179]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[180])
      ->set_attributes({new attribute(strings[2175],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2176],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2107],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2177],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2178],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2179],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2180],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2181],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2182],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2183],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2184],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2046],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[181])
      ->set_attributes({new attribute(strings[2175],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2177],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2107],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2178],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2179],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2180],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2182],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2183],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2046],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC2X3_types[182])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[183])
      ->set_attributes({new attribute(strings[2132],
                                      new named_type(IFC2X3_types[55]), false)},
                       {false});
  ((entity *)IFC2X3_types[185])
      ->set_attributes(
          {new attribute(strings[2185], new named_type(IFC2X3_types[184]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[188])
      ->set_attributes({new attribute(strings[2186],
                                      new named_type(IFC2X3_types[506]), false),
                        new attribute(strings[2187],
                                      new named_type(IFC2X3_types[506]), false),
                        new attribute(strings[2188],
                                      new named_type(IFC2X3_types[579]), false),
                        new attribute(strings[2189],
                                      new named_type(IFC2X3_types[205]), false),
                        new attribute(strings[2190],
                                      new named_type(IFC2X3_types[436]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[189])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[190])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[191]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[193])->set_attributes({}, {});
  ((entity *)IFC2X3_types[194])
      ->set_attributes({new attribute(strings[2191],
                                      new named_type(IFC2X3_types[564]), false),
                        new attribute(strings[2003],
                                      new named_type(IFC2X3_types[193]), false),
                        new attribute(strings[2004],
                                      new aggregation_type(
                                          aggregation_type::set_type, 0, -1,
                                          new named_type(IFC2X3_types[193])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[197])
      ->set_attributes({new attribute(strings[2192],
                                      new named_type(IFC2X3_types[195]), true),
                        new attribute(strings[2193],
                                      new named_type(IFC2X3_types[767]), true),
                        new attribute(strings[2194],
                                      new named_type(IFC2X3_types[123]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[198])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2195],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[200])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[199])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2192], new named_type(IFC2X3_types[201]),
                         false),
           new attribute(strings[2196], new named_type(IFC2X3_types[579]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[200])
      ->set_attributes(
          {new attribute(strings[2197], new named_type(IFC2X3_types[435]),
                         false),
           new attribute(strings[2198], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[202])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[203]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[205])
      ->set_attributes(
          {new attribute(strings[2199], new named_type(IFC2X3_types[97]),
                         false),
           new attribute(strings[2200], new named_type(IFC2X3_types[460]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[209])
      ->set_attributes(
          {new attribute(strings[2201], new named_type(IFC2X3_types[210]),
                         false),
           new attribute(strings[2202], new named_type(IFC2X3_types[100]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[212])
      ->set_attributes({new attribute(strings[2203],
                                      new named_type(IFC2X3_types[604]), false),
                        new attribute(strings[2059],
                                      new named_type(IFC2X3_types[100]), false),
                        new attribute(strings[2129],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[213])
      ->set_attributes({new attribute(strings[2204],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[214])),
                                      false),
                        new attribute(strings[2205],
                                      new named_type(IFC2X3_types[215]), false),
                        new attribute(strings[2206],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[214])
      ->set_attributes(
          {new attribute(strings[2207], new named_type(IFC2X3_types[511]),
                         false),
           new attribute(strings[2208],
                         new simple_type(simple_type::integer_type), false)},
          {false, false});
  ((entity *)IFC2X3_types[217])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[219])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[221])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[222])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[223])
      ->set_attributes(
          {new attribute(strings[1997], new named_type(IFC2X3_types[224]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[225])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[218])
      ->set_attributes(
          {new attribute(strings[2209],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2210],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2211],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2212],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2213],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2214],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2215],
                         new simple_type(simple_type::integer_type), false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[226])
      ->set_attributes(
          {new attribute(
              strings[2216],
              new aggregation_type(aggregation_type::list_type, 2, 3,
                                   new simple_type(simple_type::real_type)),
              false)},
          {false});
  ((entity *)IFC2X3_types[228])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[229])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[230])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[231])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[232]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[233])
      ->set_attributes(
          {new attribute(strings[2217], new named_type(IFC2X3_types[412]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[234])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[235])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[236])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[237])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[238])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[239])
      ->set_attributes(
          {new attribute(strings[2218], new named_type(IFC2X3_types[355]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[241])
      ->set_attributes({new attribute(strings[2219],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2220],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2221],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[242])
      ->set_attributes(
          {new attribute(strings[2222], new named_type(IFC2X3_types[412]),
                         false),
           new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(
               strings[2223],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[244])),
               true),
           new attribute(strings[2001], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2224], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2225], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2226], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2227], new named_type(IFC2X3_types[8]), true),
           new attribute(strings[2228],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC2X3_types[8])),
                         true),
           new attribute(strings[2149], new named_type(IFC2X3_types[205]),
                         true),
           new attribute(strings[2229], new named_type(IFC2X3_types[205]),
                         true),
           new attribute(strings[2230], new named_type(IFC2X3_types[241]),
                         true),
           new attribute(strings[2231], new named_type(IFC2X3_types[97]), true),
           new attribute(strings[2232], new named_type(IFC2X3_types[97]), true),
           new attribute(strings[2233], new named_type(IFC2X3_types[240]),
                         true),
           new attribute(strings[2169], new named_type(IFC2X3_types[246]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[243])
      ->set_attributes({new attribute(strings[2234],
                                      new named_type(IFC2X3_types[242]), false),
                        new attribute(strings[2235],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[242])),
                                      false),
                        new attribute(strings[2236],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[244])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[247])
      ->set_attributes({new attribute(strings[2175],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2237],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[248])
      ->set_attributes({new attribute(strings[2238],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2239],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2240],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2241],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2242],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2243],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2244],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2245],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2246],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2247],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2248],
                                      new named_type(IFC2X3_types[755]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[251])
      ->set_attributes(
          {new attribute(strings[2249], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2250], new named_type(IFC2X3_types[249]),
                         false),
           new attribute(strings[2251], new named_type(IFC2X3_types[512]),
                         true),
           new attribute(strings[2252], new named_type(IFC2X3_types[250]),
                         false),
           new attribute(strings[2248], new named_type(IFC2X3_types[755]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[252])
      ->set_attributes(
          {new attribute(strings[2253], new named_type(IFC2X3_types[254]),
                         false),
           new attribute(strings[2254], new named_type(IFC2X3_types[253]),
                         false),
           new attribute(strings[2255],
                         new simple_type(simple_type::boolean_type), false),
           new attribute(strings[2256],
                         new simple_type(simple_type::boolean_type), false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC2X3_types[256])
      ->set_attributes({new attribute(strings[2257],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[257])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[258])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2258], new named_type(IFC2X3_types[256]),
                         false),
           new attribute(strings[2259], new named_type(IFC2X3_types[256]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[259])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[260])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[261])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[262])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[263]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[264])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[265]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[266])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[267]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[269])
      ->set_attributes(
          {new attribute(strings[2260], new named_type(IFC2X3_types[946]),
                         false),
           new attribute(strings[2261], new named_type(IFC2X3_types[946]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[270])
      ->set_attributes(
          {new attribute(strings[2262], new named_type(IFC2X3_types[193]),
                         false),
           new attribute(strings[2126],
                         new simple_type(simple_type::boolean_type), false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[271])
      ->set_attributes(
          {new attribute(strings[2263], new named_type(IFC2X3_types[577]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[272])
      ->set_attributes({new attribute(strings[2264],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[534])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[276])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[277]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[283])
      ->set_attributes({new attribute(strings[2265],
                                      new named_type(IFC2X3_types[284]), false),
                        new attribute(strings[2266],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[285])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[286]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[287])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[288]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[289])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[290]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[291])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[292]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[294])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[295]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[273])
      ->set_attributes(
          {new attribute(strings[2267], new named_type(IFC2X3_types[281]),
                         true),
           new attribute(strings[2268], new named_type(IFC2X3_types[296]),
                         false),
           new attribute(strings[2269], new named_type(IFC2X3_types[379]),
                         false),
           new attribute(strings[2270], new named_type(IFC2X3_types[282]),
                         true),
           new attribute(strings[2271], new named_type(IFC2X3_types[282]),
                         true),
           new attribute(strings[2272], new named_type(IFC2X3_types[581]),
                         true),
           new attribute(strings[2273], new named_type(IFC2X3_types[581]),
                         true),
           new attribute(strings[2274],
                         new simple_type(simple_type::integer_type), false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC2X3_types[274])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[275])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[297])
      ->set_attributes(
          {new attribute(strings[2275], new named_type(IFC2X3_types[412]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[299])
      ->set_attributes(
          {new attribute(strings[2276], new named_type(IFC2X3_types[49]), true),
           new attribute(strings[2000], new named_type(IFC2X3_types[300]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[301])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[302])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[304])
      ->set_attributes({new attribute(strings[2277],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2278],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[550])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[305])
      ->set_attributes(
          {new attribute(strings[2279], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[298])
      ->set_attributes({new attribute(strings[2132],
                                      new named_type(IFC2X3_types[55]), false)},
                       {false});
  ((entity *)IFC2X3_types[306])
      ->set_attributes(
          {new attribute(strings[2280], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2281], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[307])
      ->set_attributes(
          {new attribute(strings[2280], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2281], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[308])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[309])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[311])
      ->set_attributes({new attribute(strings[2282],
                                      new named_type(IFC2X3_types[312]), true),
                        new attribute(strings[2283],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[314])
      ->set_attributes(
          {new attribute(strings[2284], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[2285], new named_type(IFC2X3_types[313]),
                         false),
           new attribute(strings[2286], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[315])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[316])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[317])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[318]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[319])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[320]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[321])
      ->set_attributes(
          {new attribute(
               strings[2287],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[615])),
               false),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[326])
      ->set_attributes({new attribute(strings[2288],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2289],
                                      new named_type(IFC2X3_types[412]), true),
                        new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[322])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[323])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[324])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[325])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[327])
      ->set_attributes(
          {new attribute(strings[2290], new named_type(IFC2X3_types[226]),
                         false),
           new attribute(strings[2088], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[328])
      ->set_attributes({new attribute(strings[2291],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[330])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[329])
      ->set_attributes({new attribute(strings[2292],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[144])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[330])
      ->set_attributes(
          {new attribute(strings[2293], new named_type(IFC2X3_types[463]),
                         false),
           new attribute(strings[2294],
                         new simple_type(simple_type::boolean_type), false)},
          {false, false});
  ((entity *)IFC2X3_types[331])->set_attributes({}, {false, false});
  ((entity *)IFC2X3_types[332])
      ->set_attributes(
          {new attribute(strings[2295], new named_type(IFC2X3_types[844]),
                         false),
           new attribute(strings[2126],
                         new simple_type(simple_type::boolean_type), false)},
          {false, false, false});
  ((entity *)IFC2X3_types[333])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[334])
      ->set_attributes({new attribute(strings[2296],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[120])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[335])
      ->set_attributes({new attribute(strings[2297],
                                      new named_type(IFC2X3_types[378]), true),
                        new attribute(strings[2298],
                                      new named_type(IFC2X3_types[378]), true),
                        new attribute(strings[2299],
                                      new named_type(IFC2X3_types[378]), true),
                        new attribute(strings[2300],
                                      new named_type(IFC2X3_types[378]), true),
                        new attribute(strings[2301],
                                      new named_type(IFC2X3_types[378]), true),
                        new attribute(strings[2302],
                                      new named_type(IFC2X3_types[378]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[336])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[337]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[338])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[339])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[340])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[341])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[342])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[343])
      ->set_attributes({new attribute(strings[2303],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[348])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[344])
      ->set_attributes(
          {new attribute(strings[2304], new named_type(IFC2X3_types[197]),
                         false),
           new attribute(strings[2305], new named_type(IFC2X3_types[403]),
                         false),
           new attribute(strings[2306], new named_type(IFC2X3_types[98]), true),
           new attribute(strings[2307], new named_type(IFC2X3_types[98]), true),
           new attribute(strings[2308], new named_type(IFC2X3_types[565]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[347])
      ->set_attributes({new attribute(strings[2309],
                                      new named_type(IFC2X3_types[34]), false)},
                       {false});
  ((entity *)IFC2X3_types[345])
      ->set_attributes(
          {new attribute(strings[2310], new named_type(IFC2X3_types[526]),
                         false),
           new attribute(
               strings[2311],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[346])),
               false),
           new attribute(strings[2312], new named_type(IFC2X3_types[579]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[349])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[350]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[351])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[352]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[353])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[354])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[356])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[357])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[358])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[359]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[360])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[361]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[362])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[363])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[364])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[365])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[366])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[367])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[368])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[369])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[370])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[371])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[372])
      ->set_attributes({new attribute(strings[2313],
                                      new named_type(IFC2X3_types[627]), false),
                        new attribute(strings[2314],
                                      new named_type(IFC2X3_types[908]), true),
                        new attribute(strings[2315],
                                      new named_type(IFC2X3_types[908]), true),
                        new attribute(strings[2316],
                                      new named_type(IFC2X3_types[908]), true),
                        new attribute(strings[2317],
                                      new named_type(IFC2X3_types[476]), false),
                        new attribute(strings[2318],
                                      new named_type(IFC2X3_types[908]), true),
                        new attribute(strings[2319],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2320],
                                      new named_type(IFC2X3_types[906]), true),
                        new attribute(strings[2321],
                                      new named_type(IFC2X3_types[906]), true),
                        new attribute(strings[2322],
                                      new named_type(IFC2X3_types[908]), true),
                        new attribute(strings[2323],
                                      new named_type(IFC2X3_types[908]), true),
                        new attribute(strings[2324],
                                      new named_type(IFC2X3_types[211]), true),
                        new attribute(strings[2325],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2326],
                                      new named_type(IFC2X3_types[457]), true),
                        new attribute(strings[2327],
                                      new named_type(IFC2X3_types[596]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC2X3_types[376])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[377]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[380])
      ->set_attributes({new attribute(strings[2328],
                                      new named_type(IFC2X3_types[906]), true),
                        new attribute(strings[2329],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2330],
                                      new named_type(IFC2X3_types[407]), true),
                        new attribute(strings[2331],
                                      new named_type(IFC2X3_types[407]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[381])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[382])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[383])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[384])
      ->set_attributes({new attribute(strings[2276],
                                      new named_type(IFC2X3_types[49]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[385])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[386]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[387])
      ->set_attributes({new attribute(strings[2332],
                                      new named_type(IFC2X3_types[503]), true),
                        new attribute(strings[2333],
                                      new named_type(IFC2X3_types[512]), true),
                        new attribute(strings[2334],
                                      new named_type(IFC2X3_types[472]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[388])
      ->set_attributes({new attribute(strings[2335],
                                      new named_type(IFC2X3_types[475]), true),
                        new attribute(strings[2336],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2337],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2338],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2339],
                                      new named_type(IFC2X3_types[47]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[389])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[391])
      ->set_attributes(
          {new attribute(strings[2340], new named_type(IFC2X3_types[220]),
                         false),
           new attribute(strings[2341], new simple_type(simple_type::real_type),
                         true),
           new attribute(strings[2342], new named_type(IFC2X3_types[53]),
                         false),
           new attribute(strings[2343], new named_type(IFC2X3_types[226]),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[392])->set_attributes({}, {});
  ((entity *)IFC2X3_types[393])
      ->set_attributes(
          {new attribute(strings[2344], new named_type(IFC2X3_types[391]),
                         false),
           new attribute(strings[2345], new named_type(IFC2X3_types[579]),
                         true),
           new attribute(strings[2346], new named_type(IFC2X3_types[390]),
                         false),
           new attribute(strings[2347], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, true, true, true, true, false, false, false, false});
  ((entity *)IFC2X3_types[394])
      ->set_attributes({new attribute(strings[2204],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[395])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[398])
      ->set_attributes({new attribute(strings[2348],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[399])),
                                      false),
                        new attribute(strings[2349],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[399])),
                                      false),
                        new attribute(strings[2350],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[399])),
                                      true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[399])
      ->set_attributes({new attribute(strings[2351],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2352],
                                      new named_type(IFC2X3_types[193]), false),
                        new attribute(strings[2126],
                                      new named_type(IFC2X3_types[65]), false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[400])
      ->set_attributes({new attribute(strings[2353],
                                      new named_type(IFC2X3_types[953]), false),
                        new attribute(strings[2354],
                                      new named_type(IFC2X3_types[953]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[401])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[402])
      ->set_attributes(
          {new attribute(strings[2355], new named_type(IFC2X3_types[844]),
                         false),
           new attribute(strings[2356],
                         new simple_type(simple_type::boolean_type), false)},
          {false, false});
  ((entity *)IFC2X3_types[404])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[405]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[409])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[410]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[411])
      ->set_attributes({new attribute(strings[2357],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2358],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2359],
                                      new named_type(IFC2X3_types[425]), true),
                        new attribute(strings[2360],
                                      new named_type(IFC2X3_types[943]), true),
                        new attribute(strings[2361],
                                      new named_type(IFC2X3_types[502]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[424])
      ->set_attributes(
          {new attribute(strings[2237], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2362], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2180], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2363], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2364], new named_type(IFC2X3_types[577]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[414])
      ->set_attributes(
          {new attribute(strings[2365], new named_type(IFC2X3_types[412]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[419])
      ->set_attributes(
          {new attribute(strings[2366], new named_type(IFC2X3_types[420]),
                         false),
           new attribute(strings[2367], new named_type(IFC2X3_types[8]), false),
           new attribute(
               strings[2368],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[545])),
               false),
           new attribute(strings[2369], new named_type(IFC2X3_types[97]),
                         false),
           new attribute(strings[2036], new named_type(IFC2X3_types[175]),
                         true),
           new attribute(strings[2035], new named_type(IFC2X3_types[175]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[422])
      ->set_attributes(
          {new attribute(
              strings[2370],
              new aggregation_type(aggregation_type::list_type, 1, -1,
                                   new named_type(IFC2X3_types[423])),
              false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[423])
      ->set_attributes({new attribute(strings[2371],
                                      new named_type(IFC2X3_types[206]), false),
                        new attribute(strings[2372],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[940])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[426])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[427]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[464])
      ->set_attributes({new attribute(strings[2088],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2089],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2105],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2364],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2373],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2374],
                                      new named_type(IFC2X3_types[565]), true),
                        new attribute(strings[2093],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2046],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC2X3_types[430])
      ->set_attributes({new attribute(strings[2375],
                                      new named_type(IFC2X3_types[879]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[431])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[432]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[436])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[2010], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2376], new named_type(IFC2X3_types[531]),
                         true),
           new attribute(strings[2377], new named_type(IFC2X3_types[97]), true),
           new attribute(
               strings[2378],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[437])),
               true)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[437])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[440])
      ->set_attributes({new attribute(strings[2379],
                                      new named_type(IFC2X3_types[565]), false),
                        new attribute(strings[2380],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[565])),
                                      false),
                        new attribute(strings[2381],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[466])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[443])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[444]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[445])
      ->set_attributes({new attribute(strings[2382],
                                      new named_type(IFC2X3_types[439]), false),
                        new attribute(strings[2383],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[440])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[446])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2384],
                                      new named_type(IFC2X3_types[125]), false),
                        new attribute(strings[2385],
                                      new named_type(IFC2X3_types[512]), true),
                        new attribute(strings[2386],
                                      new named_type(IFC2X3_types[512]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[447])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[448])
      ->set_attributes(
          {new attribute(strings[2294], new named_type(IFC2X3_types[226]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[449])
      ->set_attributes(
          {new attribute(strings[2132], new named_type(IFC2X3_types[55]),
                         false),
           new attribute(strings[2387], new named_type(IFC2X3_types[125]),
                         true),
           new attribute(strings[2388], new named_type(IFC2X3_types[906]),
                         false),
           new attribute(strings[2389], new named_type(IFC2X3_types[465]),
                         false),
           new attribute(strings[2390], new named_type(IFC2X3_types[442]),
                         false),
           new attribute(strings[2391], new named_type(IFC2X3_types[441]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[450])
      ->set_attributes(
          {new attribute(strings[2132], new named_type(IFC2X3_types[98]),
                         false),
           new attribute(strings[2107], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2392], new named_type(IFC2X3_types[652]),
                         false),
           new attribute(strings[2393], new named_type(IFC2X3_types[652]),
                         false),
           new attribute(strings[2394], new named_type(IFC2X3_types[652]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[451])
      ->set_attributes(
          {new attribute(strings[2294], new named_type(IFC2X3_types[226]),
                         false),
           new attribute(strings[2395], new named_type(IFC2X3_types[652]),
                         true),
           new attribute(strings[2396], new named_type(IFC2X3_types[578]),
                         false),
           new attribute(strings[2397], new named_type(IFC2X3_types[578]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC2X3_types[452])
      ->set_attributes(
          {new attribute(strings[2398], new named_type(IFC2X3_types[98]),
                         false),
           new attribute(strings[2399], new named_type(IFC2X3_types[944]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[453])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[459])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC2X3_types[519]), true),
                        new attribute(strings[2401],
                                      new named_type(IFC2X3_types[53]), false)},
                       {false, false});
  ((entity *)IFC2X3_types[460])
      ->set_attributes({new attribute(strings[2402],
                                      new named_type(IFC2X3_types[408]), false),
                        new attribute(strings[2403],
                                      new named_type(IFC2X3_types[497]), true),
                        new attribute(strings[2404],
                                      new named_type(IFC2X3_types[741]), true),
                        new attribute(strings[2405],
                                      new named_type(IFC2X3_types[171]), true),
                        new attribute(strings[2406],
                                      new named_type(IFC2X3_types[208]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[463])->set_attributes({}, {});
  ((entity *)IFC2X3_types[470])
      ->set_attributes(
          {new attribute(strings[2407], new named_type(IFC2X3_types[120]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[471])
      ->set_attributes({new attribute(strings[2408],
                                      new named_type(IFC2X3_types[721]), false),
                        new attribute(strings[2409],
                                      new named_type(IFC2X3_types[99]), false)},
                       {false, false});
  ((entity *)IFC2X3_types[476])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[477])
      ->set_attributes(
          {new attribute(
               strings[2410],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[118])),
               false),
           new attribute(strings[2411], new named_type(IFC2X3_types[476]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[478])
      ->set_attributes(
          {new attribute(strings[2412], new named_type(IFC2X3_types[476]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[479])
      ->set_attributes({new attribute(strings[2413],
                                      new named_type(IFC2X3_types[476]), true),
                        new attribute(strings[2414],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2415],
                                      new named_type(IFC2X3_types[461]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[480])
      ->set_attributes({new attribute(strings[2416],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[479])),
                                      false),
                        new attribute(strings[2417],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[481])
      ->set_attributes(
          {new attribute(strings[2418], new named_type(IFC2X3_types[480]),
                         false),
           new attribute(strings[2419], new named_type(IFC2X3_types[434]),
                         false),
           new attribute(strings[2420], new named_type(IFC2X3_types[227]),
                         false),
           new attribute(strings[2421], new named_type(IFC2X3_types[435]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[482])
      ->set_attributes({new attribute(strings[2422],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[476])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[483])
      ->set_attributes(
          {new attribute(strings[2413], new named_type(IFC2X3_types[476]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[486])
      ->set_attributes(
          {new attribute(strings[2423], new named_type(IFC2X3_types[940]),
                         false),
           new attribute(strings[2424], new named_type(IFC2X3_types[934]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[487])
      ->set_attributes({new attribute(strings[2425],
                                      new named_type(IFC2X3_types[596]), true),
                        new attribute(strings[2426],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2427],
                                      new named_type(IFC2X3_types[879]), true),
                        new attribute(strings[2428],
                                      new named_type(IFC2X3_types[879]), true),
                        new attribute(strings[2429],
                                      new named_type(IFC2X3_types[512]), true),
                        new attribute(strings[2430],
                                      new named_type(IFC2X3_types[879]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC2X3_types[488])
      ->set_attributes({new attribute(strings[2431],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2432],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[489])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[490])
      ->set_attributes({new attribute(strings[2433],
                                      new named_type(IFC2X3_types[268]), true),
                        new attribute(strings[2434],
                                      new named_type(IFC2X3_types[498]), true),
                        new attribute(strings[2435],
                                      new named_type(IFC2X3_types[498]), true),
                        new attribute(strings[2436],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2437],
                                      new named_type(IFC2X3_types[900]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[491])
      ->set_attributes({new attribute(strings[2438],
                                      new named_type(IFC2X3_types[596]), true),
                        new attribute(strings[2439],
                                      new named_type(IFC2X3_types[596]), true),
                        new attribute(strings[2440],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2441],
                                      new named_type(IFC2X3_types[498]), true),
                        new attribute(strings[2442],
                                      new named_type(IFC2X3_types[596]), true),
                        new attribute(strings[2443],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2444],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[687])),
                                      true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC2X3_types[492])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[493])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[494]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[495])
      ->set_attributes(
          {new attribute(strings[2445], new named_type(IFC2X3_types[59]),
                         false),
           new attribute(strings[2446], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2447], new named_type(IFC2X3_types[496]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[506])
      ->set_attributes(
          {new attribute(strings[2448], new named_type(IFC2X3_types[187]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[508])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[509]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[510])
      ->set_attributes({new attribute(strings[2449],
                                      new named_type(IFC2X3_types[786]), false),
                        new attribute(strings[2450],
                                      new named_type(IFC2X3_types[786]), false),
                        new attribute(strings[2451],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[879])),
                                      true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC2X3_types[511])
      ->set_attributes(
          {new attribute(strings[2452], new named_type(IFC2X3_types[218]),
                         false),
           new attribute(strings[2205], new named_type(IFC2X3_types[938]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[515])
      ->set_attributes({new attribute(strings[2453],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[516])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[519])->set_attributes({}, {});
  ((entity *)IFC2X3_types[517])
      ->set_attributes({new attribute(strings[2454],
                                      new named_type(IFC2X3_types[495]), true),
                        new attribute(strings[2455],
                                      new named_type(IFC2X3_types[495]), true),
                        new attribute(strings[2456],
                                      new named_type(IFC2X3_types[518]), false),
                        new attribute(strings[2457],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC2X3_types[522])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[523]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[524])
      ->set_attributes(
          {new attribute(strings[2458], new named_type(IFC2X3_types[193]),
                         false),
           new attribute(strings[2459], new named_type(IFC2X3_types[435]),
                         false),
           new attribute(strings[2053],
                         new simple_type(simple_type::logical_type), false)},
          {false, false, false});
  ((entity *)IFC2X3_types[525])
      ->set_attributes(
          {new attribute(strings[2458], new named_type(IFC2X3_types[193]),
                         false),
           new attribute(strings[2459], new named_type(IFC2X3_types[435]),
                         false),
           new attribute(strings[2053],
                         new simple_type(simple_type::logical_type), false),
           new attribute(strings[2048], new named_type(IFC2X3_types[226]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[526])
      ->set_attributes(
          {new attribute(strings[2460], new named_type(IFC2X3_types[944]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[528])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[527])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[529])
      ->set_attributes({new attribute(strings[2461],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2462],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2463],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2464],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2465],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2466],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2467],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2468],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2469],
                                      new named_type(IFC2X3_types[579]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[530])
      ->set_attributes(
          {new attribute(strings[2470], new named_type(IFC2X3_types[412]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[531])
      ->set_attributes({new attribute(strings[2471],
                                      new named_type(IFC2X3_types[412]), true),
                        new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), false),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true),
                        new attribute(strings[2472],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[7])),
                                      true),
                        new attribute(strings[2473],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[11])),
                                      true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[532])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), false),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true),
                        new attribute(strings[2474],
                                      new named_type(IFC2X3_types[531]), false),
                        new attribute(strings[2475],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[531])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[534])
      ->set_attributes(
          {new attribute(strings[2476], new named_type(IFC2X3_types[269]),
                         false),
           new attribute(strings[2294],
                         new simple_type(simple_type::boolean_type), false)},
          {true, true, false, false});
  ((entity *)IFC2X3_types[535])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[536]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[537])
      ->set_attributes(
          {new attribute(strings[2477], new named_type(IFC2X3_types[546]),
                         false),
           new attribute(strings[2478], new named_type(IFC2X3_types[36]),
                         false),
           new attribute(strings[2479], new named_type(IFC2X3_types[800]),
                         true),
           new attribute(strings[2480], new named_type(IFC2X3_types[106]),
                         false),
           new attribute(strings[2481], new named_type(IFC2X3_types[914]),
                         true),
           new attribute(strings[2482], new named_type(IFC2X3_types[546]),
                         true),
           new attribute(strings[2483], new named_type(IFC2X3_types[36]), true),
           new attribute(strings[2484], new named_type(IFC2X3_types[914]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[538])
      ->set_attributes({new attribute(strings[2132],
                                      new named_type(IFC2X3_types[54]), false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[540])
      ->set_attributes({new attribute(strings[2264],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[534])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[541])
      ->set_attributes(
          {new attribute(strings[2485], new named_type(IFC2X3_types[429]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[543])
      ->set_attributes(
          {new attribute(strings[2253], new named_type(IFC2X3_types[542]),
                         false),
           new attribute(strings[2252], new named_type(IFC2X3_types[968]),
                         false),
           new attribute(strings[2486], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2487], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2248], new named_type(IFC2X3_types[755]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[544])
      ->set_attributes(
          {new attribute(strings[2488], new named_type(IFC2X3_types[412]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[545])
      ->set_attributes(
          {new attribute(strings[2471], new named_type(IFC2X3_types[412]),
                         true),
           new attribute(strings[2489], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2490], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(
               strings[2491],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[429])),
               true),
           new attribute(
               strings[2492],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[429])),
               true),
           new attribute(
               strings[2493],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[429])),
               true),
           new attribute(strings[2472],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC2X3_types[7])),
                         true),
           new attribute(strings[2473],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC2X3_types[11])),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[546])
      ->set_attributes({new attribute(strings[2494],
                                      new named_type(IFC2X3_types[545]), false),
                        new attribute(strings[2495],
                                      new named_type(IFC2X3_types[531]), false),
                        new attribute(strings[2472],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[7])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[548])
      ->set_attributes({new attribute(strings[2496],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[550])),
                                      false),
                        new attribute(strings[2497],
                                      new named_type(IFC2X3_types[429]), false),
                        new attribute(strings[2498],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2499],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[550])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), false),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[551])
      ->set_attributes({new attribute(strings[2207],
                                      new named_type(IFC2X3_types[511]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[552])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[554]), false),
                        new attribute(strings[2254],
                                      new named_type(IFC2X3_types[553]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[555])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[556]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[557])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[558]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[559])
      ->set_attributes(
          {new attribute(strings[2089], new named_type(IFC2X3_types[416]),
                         false),
           new attribute(strings[2106], new named_type(IFC2X3_types[416]),
                         false),
           new attribute(strings[2500], new named_type(IFC2X3_types[416]),
                         false),
           new attribute(
               strings[2501],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new simple_type(simple_type::binary_type)),
               false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[560])
      ->set_attributes({new attribute(strings[2288],
                                      new named_type(IFC2X3_types[98]), false)},
                       {false});
  ((entity *)IFC2X3_types[561])
      ->set_attributes({new attribute(strings[2502],
                                      new named_type(IFC2X3_types[53]), false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[562])
      ->set_attributes(
          {new attribute(strings[2503], new named_type(IFC2X3_types[435]),
                         false),
           new attribute(strings[2504], new named_type(IFC2X3_types[435]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[564])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[566])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[567])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[568]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[569])->set_attributes({}, {});
  ((entity *)IFC2X3_types[570])
      ->set_attributes(
          {new attribute(strings[2458], new named_type(IFC2X3_types[193]),
                         false),
           new attribute(strings[2505], new named_type(IFC2X3_types[539]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[571])
      ->set_attributes(
          {new attribute(strings[2191], new named_type(IFC2X3_types[844]),
                         false),
           new attribute(strings[2506], new named_type(IFC2X3_types[539]),
                         false),
           new attribute(strings[2507], new named_type(IFC2X3_types[539]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[575])
      ->set_attributes({new attribute(strings[2508],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC2X3_types[98])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[573])
      ->set_attributes({new attribute(strings[2132],
                                      new named_type(IFC2X3_types[55]), false),
                        new attribute(strings[2509],
                                      new named_type(IFC2X3_types[75]), false)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[574])
      ->set_attributes({new attribute(strings[2510],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC2X3_types[98])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[576])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[580])
      ->set_attributes({new attribute(strings[2511],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2512],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[429])),
                                      true),
                        new attribute(strings[2513],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2514],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2515],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2516],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2517],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[582])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[583])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[584])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[585])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[586])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[587])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[588])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[589])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[591])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), false),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true),
                        new attribute(strings[2518],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[433])),
                                      false),
                        new attribute(strings[2025],
                                      new named_type(IFC2X3_types[412]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[592])
      ->set_attributes(
          {new attribute(strings[2519],
                         new simple_type(simple_type::logical_type), false),
           new attribute(strings[2520],
                         new simple_type(simple_type::logical_type), false),
           new attribute(strings[2521],
                         new simple_type(simple_type::logical_type), false),
           new attribute(
               strings[2522],
               new aggregation_type(aggregation_type::set_type, 0, -1,
                                    new named_type(IFC2X3_types[595])),
               false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[593])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false});
  ((entity *)IFC2X3_types[594])
      ->set_attributes({new attribute(strings[2523],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[595])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[597])
      ->set_attributes(
          {new attribute(strings[2524], new named_type(IFC2X3_types[412]),
                         false),
           new attribute(strings[2525], new named_type(IFC2X3_types[598]),
                         false),
           new attribute(strings[2526], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[599])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[600])
      ->set_attributes({new attribute(strings[2527],
                                      new named_type(IFC2X3_types[519]), true),
                        new attribute(strings[2528],
                                      new named_type(IFC2X3_types[602]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[601])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[602])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true),
                        new attribute(strings[2529],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[718])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[603])
      ->set_attributes({new attribute(strings[2530],
                                      new named_type(IFC2X3_types[788]), true),
                        new attribute(strings[2531],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2532],
                                      new named_type(IFC2X3_types[579]), true),
                        new attribute(strings[2533],
                                      new named_type(IFC2X3_types[579]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[604])
      ->set_attributes({new attribute(strings[2534],
                                      new named_type(IFC2X3_types[606]), false),
                        new attribute(strings[2535],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[605])
      ->set_attributes({new attribute(strings[2535],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2536],
                                      new named_type(IFC2X3_types[604]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[607])
      ->set_attributes(
          {new attribute(strings[2537], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2538], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(
               strings[2539],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[719])),
               false),
           new attribute(strings[2540], new named_type(IFC2X3_types[937]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[611])
      ->set_attributes(
          {new attribute(strings[2172], new named_type(IFC2X3_types[412]),
                         false),
           new attribute(strings[2000], new named_type(IFC2X3_types[614]),
                         false),
           new attribute(strings[2169], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[612])
      ->set_attributes(
          {new attribute(
               strings[2541],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[675])),
               false),
           new attribute(strings[2000], new named_type(IFC2X3_types[613]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[609])->set_attributes({}, {false, false, false});
  ((entity *)IFC2X3_types[610])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[615])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[412]), false),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[616])
      ->set_attributes({new attribute(strings[2542],
                                      new named_type(IFC2X3_types[940]), true),
                        new attribute(strings[2543],
                                      new named_type(IFC2X3_types[940]), true),
                        new attribute(strings[2207],
                                      new named_type(IFC2X3_types[934]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[617])
      ->set_attributes({new attribute(strings[2151],
                                      new named_type(IFC2X3_types[152]), false),
                        new attribute(strings[2544],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[615])),
                                      false),
                        new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[618])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[619])
      ->set_attributes({new attribute(strings[2545],
                                      new named_type(IFC2X3_types[615]), false),
                        new attribute(strings[2546],
                                      new named_type(IFC2X3_types[615]), false),
                        new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true),
                        new attribute(strings[2547],
                                      new named_type(IFC2X3_types[879]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[620])
      ->set_attributes({new attribute(strings[2548],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[940])),
                                      false),
                        new attribute(strings[2549],
                                      new named_type(IFC2X3_types[621]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[621])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), false),
                        new attribute(strings[2548],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[940])),
                                      false),
                        new attribute(strings[2207],
                                      new named_type(IFC2X3_types[934]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[622])
      ->set_attributes({new attribute(strings[2372],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[940])),
                                      false),
                        new attribute(strings[2207],
                                      new named_type(IFC2X3_types[934]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[623])
      ->set_attributes(
          {new attribute(strings[2122], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2550], new named_type(IFC2X3_types[520]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[624])
      ->set_attributes({new attribute(strings[2123],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[615])),
                                      false)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[625])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[626])
      ->set_attributes({new attribute(strings[2551],
                                      new named_type(IFC2X3_types[940]), true),
                        new attribute(strings[2207],
                                      new named_type(IFC2X3_types[934]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[628])
      ->set_attributes({new attribute(strings[2552],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[940])),
                                      false),
                        new attribute(strings[2553],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[940])),
                                      false),
                        new attribute(strings[2547],
                                      new named_type(IFC2X3_types[879]), true),
                        new attribute(strings[2554],
                                      new named_type(IFC2X3_types[934]), true),
                        new attribute(strings[2555],
                                      new named_type(IFC2X3_types[934]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[629])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[630]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[631])
      ->set_attributes(
          {new attribute(strings[2556], new named_type(IFC2X3_types[521]),
                         false),
           new attribute(strings[2275], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[632])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[633]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[634])
      ->set_attributes({new attribute(strings[2557],
                                      new named_type(IFC2X3_types[47]), false)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[635])
      ->set_attributes(
          {new attribute(strings[2558], new named_type(IFC2X3_types[176]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[636])
      ->set_attributes(
          {new attribute(strings[2559], new named_type(IFC2X3_types[435]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[637])
      ->set_attributes(
          {new attribute(strings[2560], new named_type(IFC2X3_types[907]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[638])
      ->set_attributes(
          {new attribute(strings[2561], new named_type(IFC2X3_types[954]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[639])
      ->set_attributes(
          {new attribute(strings[2562], new named_type(IFC2X3_types[474]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[641])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[642])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[644]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[643])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[644]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[645])
      ->set_attributes(
          {new attribute(strings[2563], new named_type(IFC2X3_types[649]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[646])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[647])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[648]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[651])
      ->set_attributes(
          {new attribute(
              strings[2564],
              new aggregation_type(aggregation_type::list_type, 2, -1,
                                   new simple_type(simple_type::real_type)),
              false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[653])
      ->set_attributes(
          {new attribute(strings[2090], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2565], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2566], new named_type(IFC2X3_types[577]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[654])
      ->set_attributes(
          {new attribute(strings[2079], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2080], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[655])
      ->set_attributes(
          {new attribute(strings[2056], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2057], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2106], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[656])
      ->set_attributes(
          {new attribute(strings[2191], new named_type(IFC2X3_types[844]),
                         false),
           new attribute(strings[2567], new named_type(IFC2X3_types[539]),
                         false),
           new attribute(strings[2568], new named_type(IFC2X3_types[539]),
                         false),
           new attribute(strings[2569], new named_type(IFC2X3_types[539]),
                         false),
           new attribute(strings[2570], new named_type(IFC2X3_types[539]),
                         false),
           new attribute(strings[2571],
                         new simple_type(simple_type::boolean_type), false),
           new attribute(strings[2572],
                         new simple_type(simple_type::boolean_type), false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[657])
      ->set_attributes(
          {new attribute(strings[2573], new named_type(IFC2X3_types[245]),
                         false),
           new attribute(strings[2574],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC2X3_types[37])),
                         false),
           new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[659])
      ->set_attributes({new attribute(strings[2575],
                                      new named_type(IFC2X3_types[907]), false),
                        new attribute(strings[2370],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[913])),
                                      false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[660])
      ->set_attributes({new attribute(strings[2576],
                                      new named_type(IFC2X3_types[47]), false),
                        new attribute(strings[2577],
                                      new named_type(IFC2X3_types[429]), false),
                        new attribute(strings[2578],
                                      new named_type(IFC2X3_types[664]), true),
                        new attribute(strings[2579],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2580],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2581],
                                      new named_type(IFC2X3_types[176]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[661])
      ->set_attributes({new attribute(strings[2582],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2583],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[746])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[662])
      ->set_attributes({new attribute(strings[2431],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2339],
                                      new named_type(IFC2X3_types[47]), false),
                        new attribute(strings[2584],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2585],
                                      new named_type(IFC2X3_types[663]), false),
                        new attribute(strings[2578],
                                      new named_type(IFC2X3_types[664]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false});
  ((entity *)IFC2X3_types[665])
      ->set_attributes(
          {new attribute(strings[2577], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[666])
      ->set_attributes(
          {new attribute(strings[2586], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2587], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2588], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2589], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2590], new named_type(IFC2X3_types[47]),
                         false),
           new attribute(strings[2591], new named_type(IFC2X3_types[47]),
                         false),
           new attribute(strings[2592], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2593], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[667])
      ->set_attributes({}, {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[668])
      ->set_attributes({new attribute(strings[2594],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[516])),
                                      false),
                        new attribute(strings[2595],
                                      new named_type(IFC2X3_types[521]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[669])
      ->set_attributes(
          {new attribute(strings[2596], new named_type(IFC2X3_types[740]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[670])
      ->set_attributes(
          {new attribute(strings[2597], new named_type(IFC2X3_types[6]), false),
           new attribute(strings[2598], new named_type(IFC2X3_types[7]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[671])
      ->set_attributes(
          {new attribute(strings[2599], new named_type(IFC2X3_types[163]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[672])
      ->set_attributes(
          {new attribute(strings[2600], new named_type(IFC2X3_types[401]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[673])
      ->set_attributes(
          {new attribute(strings[2601], new named_type(IFC2X3_types[599]),
                         false),
           new attribute(strings[2602], new named_type(IFC2X3_types[486]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[674])
      ->set_attributes(
          {new attribute(strings[2603], new named_type(IFC2X3_types[600]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[675])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[676])
      ->set_attributes(
          {new attribute(strings[2604], new named_type(IFC2X3_types[722]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[677])
      ->set_attributes({new attribute(strings[2594],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[732])),
                                      false)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[678])
      ->set_attributes({new attribute(strings[2605],
                                      new named_type(IFC2X3_types[37]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[679])
      ->set_attributes({new attribute(strings[2030],
                                      new named_type(IFC2X3_types[40]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[680])
      ->set_attributes(
          {new attribute(strings[2606], new named_type(IFC2X3_types[118]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[681])
      ->set_attributes(
          {new attribute(strings[2607], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[2151], new named_type(IFC2X3_types[152]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[682])
      ->set_attributes(
          {new attribute(strings[2234], new named_type(IFC2X3_types[245]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[683])
      ->set_attributes(
          {new attribute(strings[2608], new named_type(IFC2X3_types[438]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[684])
      ->set_attributes(
          {new attribute(strings[2609], new named_type(IFC2X3_types[484]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[685])
      ->set_attributes(
          {new attribute(strings[2610], new named_type(IFC2X3_types[605]),
                         false),
           new attribute(strings[2611], new named_type(IFC2X3_types[755]),
                         true),
           new attribute(strings[2612], new named_type(IFC2X3_types[533]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[688])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[689])
      ->set_attributes(
          {new attribute(strings[2613], new named_type(IFC2X3_types[146]),
                         true),
           new attribute(strings[2614], new named_type(IFC2X3_types[297]),
                         false),
           new attribute(strings[2615], new named_type(IFC2X3_types[297]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[690])
      ->set_attributes(
          {new attribute(
               strings[2616],
               new aggregation_type(aggregation_type::list_type, 0, -1,
                                    new simple_type(simple_type::integer_type)),
               false),
           new attribute(
               strings[2617],
               new aggregation_type(aggregation_type::list_type, 0, -1,
                                    new simple_type(simple_type::integer_type)),
               false),
           new attribute(strings[2618], new named_type(IFC2X3_types[151]),
                         false),
           new attribute(strings[2619], new named_type(IFC2X3_types[151]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[692])
      ->set_attributes(
          {new attribute(strings[2620], new named_type(IFC2X3_types[576]),
                         false),
           new attribute(strings[2615], new named_type(IFC2X3_types[297]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[691])
      ->set_attributes({new attribute(strings[2620],
                                      new named_type(IFC2X3_types[576]), false),
                        new attribute(strings[2621],
                                      new named_type(IFC2X3_types[576]), false),
                        new attribute(strings[2622],
                                      new named_type(IFC2X3_types[297]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[693])
      ->set_attributes(
          {new attribute(strings[2614], new named_type(IFC2X3_types[803]),
                         false),
           new attribute(strings[2623], new named_type(IFC2X3_types[802]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[694])
      ->set_attributes(
          {new attribute(strings[2614], new named_type(IFC2X3_types[297]),
                         false),
           new attribute(strings[2624], new named_type(IFC2X3_types[824]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[695])
      ->set_attributes(
          {new attribute(strings[2625], new named_type(IFC2X3_types[824]),
                         false),
           new attribute(strings[2626], new named_type(IFC2X3_types[805]),
                         false),
           new attribute(strings[2627], new named_type(IFC2X3_types[70]), true),
           new attribute(strings[2628], new named_type(IFC2X3_types[806]),
                         true),
           new attribute(strings[2629], new named_type(IFC2X3_types[435]),
                         true),
           new attribute(strings[2630], new named_type(IFC2X3_types[55]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[696])
      ->set_attributes(
          {new attribute(strings[2631], new named_type(IFC2X3_types[146]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[697])
      ->set_attributes(
          {new attribute(
               strings[2632],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[297])),
               false),
           new attribute(strings[2633], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[698])
      ->set_attributes(
          {new attribute(
               strings[2634],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[600])),
               false),
           new attribute(strings[2635], new named_type(IFC2X3_types[786]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[699])
      ->set_attributes({new attribute(strings[2636],
                                      new named_type(IFC2X3_types[297]), false),
                        new attribute(strings[2637],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[177])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[700])
      ->set_attributes({new attribute(strings[2638],
                                      new named_type(IFC2X3_types[779]), false),
                        new attribute(strings[2637],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[177])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[701])
      ->set_attributes({new attribute(strings[2639],
                                      new named_type(IFC2X3_types[516]), false),
                        new attribute(strings[2594],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[516])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[702])
      ->set_attributes({new attribute(strings[2594],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[515])),
                                      false)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[703])
      ->set_attributes(
          {new attribute(strings[2640], new named_type(IFC2X3_types[625]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[704])
      ->set_attributes(
          {new attribute(strings[2641], new named_type(IFC2X3_types[932]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[705])
      ->set_attributes(
          {new attribute(strings[2642], new named_type(IFC2X3_types[527]),
                         false),
           new attribute(strings[2643], new named_type(IFC2X3_types[297]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[706])
      ->set_attributes(
          {new attribute(
               strings[2644],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[233])),
               false),
           new attribute(strings[2645], new named_type(IFC2X3_types[237]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[707])
      ->set_attributes(
          {new attribute(strings[2646], new named_type(IFC2X3_types[176]),
                         true),
           new attribute(strings[2647], new named_type(IFC2X3_types[512]),
                         true),
           new attribute(strings[2648], new named_type(IFC2X3_types[786]),
                         true),
           new attribute(strings[2649], new named_type(IFC2X3_types[782]),
                         false),
           new attribute(strings[2650], new named_type(IFC2X3_types[782]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[708])
      ->set_attributes({}, {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[709])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[710])
      ->set_attributes({new attribute(strings[2651],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[615])),
                                      false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[711])
      ->set_attributes(
          {new attribute(strings[2614], new named_type(IFC2X3_types[297]),
                         false),
           new attribute(strings[2652], new named_type(IFC2X3_types[341]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[712])
      ->set_attributes(
          {new attribute(
               strings[2634],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[600])),
               false),
           new attribute(strings[2635], new named_type(IFC2X3_types[786]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[713])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[714])
      ->set_attributes(
          {new attribute(strings[2601], new named_type(IFC2X3_types[599]),
                         false),
           new attribute(strings[2653], new named_type(IFC2X3_types[599]),
                         false),
           new attribute(strings[2654], new named_type(IFC2X3_types[907]),
                         false),
           new attribute(strings[2655], new named_type(IFC2X3_types[750]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[715])
      ->set_attributes({new attribute(strings[2656],
                                      new named_type(IFC2X3_types[866]), false),
                        new attribute(strings[2657],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[786])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[716])
      ->set_attributes(
          {new attribute(strings[2658], new named_type(IFC2X3_types[779]),
                         false),
           new attribute(strings[2643], new named_type(IFC2X3_types[297]),
                         true),
           new attribute(strings[2613], new named_type(IFC2X3_types[146]),
                         true),
           new attribute(strings[2659], new named_type(IFC2X3_types[549]),
                         false),
           new attribute(strings[2660], new named_type(IFC2X3_types[418]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[717])
      ->set_attributes(
          {new attribute(strings[2636], new named_type(IFC2X3_types[297]),
                         false),
           new attribute(strings[2661], new named_type(IFC2X3_types[342]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[686])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[687])
      ->set_attributes(
          {new attribute(strings[2662], new named_type(IFC2X3_types[512]),
                         false),
           new attribute(strings[2663], new named_type(IFC2X3_types[512]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[718])
      ->set_attributes({new attribute(strings[2664],
                                      new named_type(IFC2X3_types[719]), false),
                        new attribute(strings[2665],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2666],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2667],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[720])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[719])
      ->set_attributes({new attribute(strings[2668],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2669],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[720])->set_attributes({}, {});
  ((entity *)IFC2X3_types[721])
      ->set_attributes(
          {new attribute(strings[2670], new named_type(IFC2X3_types[53]),
                         false),
           new attribute(strings[2671], new named_type(IFC2X3_types[718]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[722])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[724])
      ->set_attributes(
          {new attribute(strings[2047], new named_type(IFC2X3_types[52]),
                         false),
           new attribute(strings[2672], new named_type(IFC2X3_types[565]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[726])
      ->set_attributes(
          {new attribute(strings[2105], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2673], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2674], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2675], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2676], new named_type(IFC2X3_types[725]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[727])
      ->set_attributes(
          {new attribute(strings[2106], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2677], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[728])
      ->set_attributes(
          {new attribute(strings[2106], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2107], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[730])
      ->set_attributes(
          {new attribute(strings[2563], new named_type(IFC2X3_types[731]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[732])
      ->set_attributes({new attribute(strings[2678],
                                      new named_type(IFC2X3_types[396]), false),
                        new attribute(strings[2679],
                                      new named_type(IFC2X3_types[537]), false),
                        new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[1999],
                                      new named_type(IFC2X3_types[879]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[736])
      ->set_attributes({new attribute(strings[2107],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[737])
      ->set_attributes(
          {new attribute(strings[2680], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[765])
      ->set_attributes(
          {new attribute(strings[2681], new named_type(IFC2X3_types[763]),
                         true),
           new attribute(strings[2013], new named_type(IFC2X3_types[766]),
                         false)},
          {true, false, false, false});
  ((entity *)IFC2X3_types[738])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[739]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[740])
      ->set_attributes(
          {new attribute(strings[2682], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2683], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2684], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2685], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2686], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2687], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2688], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2689], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2690], new named_type(IFC2X3_types[907]),
                         true),
           new attribute(strings[2691], new named_type(IFC2X3_types[907]),
                         true),
           new attribute(strings[2692], new named_type(IFC2X3_types[907]),
                         true),
           new attribute(strings[2693], new named_type(IFC2X3_types[907]),
                         true),
           new attribute(strings[2694], new named_type(IFC2X3_types[907]),
                         true),
           new attribute(strings[2695],
                         new simple_type(simple_type::boolean_type), true),
           new attribute(strings[2696], new named_type(IFC2X3_types[206]),
                         true),
           new attribute(strings[2697], new named_type(IFC2X3_types[907]),
                         true),
           new attribute(strings[2698], new named_type(IFC2X3_types[907]),
                         true),
           new attribute(strings[2699], new named_type(IFC2X3_types[579]),
                         true)},
          {false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[745])
      ->set_attributes({new attribute(strings[2700],
                                      new named_type(IFC2X3_types[747]), false),
                        new attribute(strings[2701],
                                      new named_type(IFC2X3_types[604]), false),
                        new attribute(strings[2702],
                                      new named_type(IFC2X3_types[604]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[746])
      ->set_attributes({new attribute(strings[2703],
                                      new named_type(IFC2X3_types[435]), false),
                        new attribute(strings[2704],
                                      new named_type(IFC2X3_types[435]), false),
                        new attribute(strings[2705],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2706],
                                      new named_type(IFC2X3_types[663]), false),
                        new attribute(strings[2707],
                                      new named_type(IFC2X3_types[745]), false),
                        new attribute(strings[2708],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[660])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[743])
      ->set_attributes({new attribute(strings[2709],
                                      new named_type(IFC2X3_types[132]), false),
                        new attribute(strings[2710],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC2X3_types[604])),
                                      false),
                        new attribute(strings[2711],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC2X3_types[55])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[748])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[749]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[751])
      ->set_attributes(
          {new attribute(strings[2712], new named_type(IFC2X3_types[754]),
                         false),
           new attribute(strings[2713], new named_type(IFC2X3_types[907]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[752])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[753]),
                         false),
           new attribute(strings[2714], new named_type(IFC2X3_types[485]),
                         true),
           new attribute(strings[2715], new named_type(IFC2X3_types[485]),
                         false),
           new attribute(strings[2716], new named_type(IFC2X3_types[485]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[755])
      ->set_attributes(
          {new attribute(
               strings[2717],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[756])),
               false),
           new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2718],
                         new simple_type(simple_type::logical_type), false),
           new attribute(strings[2719], new named_type(IFC2X3_types[601]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[756])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[757])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[760])
      ->set_attributes({new attribute(strings[2720],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[759])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[761])->set_attributes({}, {false, false});
  ((entity *)IFC2X3_types[764])
      ->set_attributes({new attribute(strings[2721],
                                      new named_type(IFC2X3_types[135]), true),
                        new attribute(strings[2722],
                                      new named_type(IFC2X3_types[135]), true),
                        new attribute(strings[2723],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2724],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2725],
                                      new named_type(IFC2X3_types[580]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false});
  ((entity *)IFC2X3_types[768])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[770]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[769])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[770]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[771])
      ->set_attributes({new attribute(strings[2726],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2727],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2728],
                                      new named_type(IFC2X3_types[435]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[773])->set_attributes({}, {});
  ((entity *)IFC2X3_types[776])
      ->set_attributes({new attribute(strings[2729],
                                      new named_type(IFC2X3_types[65]), false),
                        new attribute(strings[2730],
                                      new named_type(IFC2X3_types[777]), true),
                        new attribute(strings[2731],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, 8,
                                          new named_type(IFC2X3_types[778])),
                                      false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[778])
      ->set_attributes({new attribute(strings[2732],
                                      new named_type(IFC2X3_types[908]), true),
                        new attribute(strings[2733],
                                      new named_type(IFC2X3_types[379]), false),
                        new attribute(strings[2734],
                                      new named_type(IFC2X3_types[211]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[779])
      ->set_attributes({new attribute(strings[2735],
                                      new named_type(IFC2X3_types[418]), false),
                        new attribute(strings[2736],
                                      new named_type(IFC2X3_types[435]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC2X3_types[780])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[781]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[782])
      ->set_attributes(
          {new attribute(strings[2737], new named_type(IFC2X3_types[412]),
                         false),
           new attribute(strings[2738], new named_type(IFC2X3_types[47]), true),
           new attribute(strings[2739], new named_type(IFC2X3_types[47]), true),
           new attribute(strings[2740], new named_type(IFC2X3_types[786]),
                         true),
           new attribute(strings[2741], new named_type(IFC2X3_types[47]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[783])
      ->set_attributes(
          {new attribute(strings[2742], new named_type(IFC2X3_types[579]),
                         true),
           new attribute(strings[2743], new named_type(IFC2X3_types[901]),
                         false),
           new attribute(strings[2313], new named_type(IFC2X3_types[627]),
                         false),
           new attribute(strings[2744], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2745], new named_type(IFC2X3_types[581]),
                         false),
           new attribute(strings[2746], new named_type(IFC2X3_types[581]),
                         true),
           new attribute(strings[2747], new named_type(IFC2X3_types[908]),
                         true),
           new attribute(strings[2748], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2319], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2749], new named_type(IFC2X3_types[902]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC2X3_types[784])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[785]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[786])
      ->set_attributes(
          {new attribute(strings[2537], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2086], new named_type(IFC2X3_types[303]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[787])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[792])
      ->set_attributes(
          {new attribute(strings[2107], new named_type(IFC2X3_types[577]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[793])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[794]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[795])
      ->set_attributes(
          {new attribute(strings[2563], new named_type(IFC2X3_types[799]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[796])
      ->set_attributes(
          {new attribute(strings[2750],
                         new simple_type(simple_type::integer_type), true),
           new attribute(strings[2751],
                         new simple_type(simple_type::integer_type), true),
           new attribute(strings[2752], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2753], new named_type(IFC2X3_types[577]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC2X3_types[797])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[798]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[801])
      ->set_attributes(
          {new attribute(strings[2754],
                         new simple_type(simple_type::boolean_type), false),
           new attribute(strings[2755], new named_type(IFC2X3_types[831]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[802])
      ->set_attributes(
          {new attribute(strings[2756], new named_type(IFC2X3_types[814]),
                         false),
           new attribute(strings[2006], new named_type(IFC2X3_types[397]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[804])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[23]),
                         false),
           new attribute(strings[2757], new named_type(IFC2X3_types[55]), true),
           new attribute(
               strings[2758],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[815])),
               true),
           new attribute(
               strings[2759],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC2X3_types[832])),
               true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[805])
      ->set_attributes(
          {new attribute(strings[2627], new named_type(IFC2X3_types[70]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[806])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false});
  ((entity *)IFC2X3_types[807])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[808])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[810]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[809])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[811])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[812])
      ->set_attributes(
          {new attribute(strings[2760], new named_type(IFC2X3_types[608]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC2X3_types[813])
      ->set_attributes({new attribute(strings[2761],
                                      new named_type(IFC2X3_types[755]), false),
                        new attribute(strings[2762],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[814])),
                                      false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false});
  ((entity *)IFC2X3_types[814])
      ->set_attributes({new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false});
  ((entity *)IFC2X3_types[815])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[458]),
                         false),
           new attribute(strings[2763], new named_type(IFC2X3_types[5]), false),
           new attribute(strings[2764], new named_type(IFC2X3_types[4]), false),
           new attribute(strings[2765], new named_type(IFC2X3_types[650]),
                         true),
           new attribute(strings[2001], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[816])
      ->set_attributes({new attribute(strings[2766],
                                      new named_type(IFC2X3_types[454]), true),
                        new attribute(strings[2767],
                                      new named_type(IFC2X3_types[454]), true),
                        new attribute(strings[2768],
                                      new named_type(IFC2X3_types[454]), true),
                        new attribute(strings[2769],
                                      new named_type(IFC2X3_types[455]), true),
                        new attribute(strings[2770],
                                      new named_type(IFC2X3_types[455]), true),
                        new attribute(strings[2771],
                                      new named_type(IFC2X3_types[455]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[817])
      ->set_attributes({new attribute(strings[2772],
                                      new named_type(IFC2X3_types[563]), true),
                        new attribute(strings[2773],
                                      new named_type(IFC2X3_types[563]), true),
                        new attribute(strings[2774],
                                      new named_type(IFC2X3_types[563]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[818])
      ->set_attributes({new attribute(strings[2775],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2776],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2777],
                                      new named_type(IFC2X3_types[435]), true),
                        new attribute(strings[2778],
                                      new named_type(IFC2X3_types[565]), true),
                        new attribute(strings[2779],
                                      new named_type(IFC2X3_types[565]), true),
                        new attribute(strings[2780],
                                      new named_type(IFC2X3_types[565]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[819])
      ->set_attributes(
          {new attribute(strings[2781], new named_type(IFC2X3_types[192]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[820])
      ->set_attributes({new attribute(strings[2782],
                                      new named_type(IFC2X3_types[378]), true),
                        new attribute(strings[2783],
                                      new named_type(IFC2X3_types[378]), true),
                        new attribute(strings[2784],
                                      new named_type(IFC2X3_types[378]), true),
                        new attribute(strings[2785],
                                      new named_type(IFC2X3_types[917]), true),
                        new attribute(strings[2786],
                                      new named_type(IFC2X3_types[917]), true),
                        new attribute(strings[2787],
                                      new named_type(IFC2X3_types[917]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[821])
      ->set_attributes(
          {new attribute(strings[2788], new named_type(IFC2X3_types[961]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[822])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[823])
      ->set_attributes({new attribute(strings[2789],
                                      new named_type(IFC2X3_types[906]), true),
                        new attribute(strings[2790],
                                      new named_type(IFC2X3_types[906]), true),
                        new attribute(strings[2791],
                                      new named_type(IFC2X3_types[906]), true)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[824])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[825])
      ->set_attributes(
          {new attribute(strings[2760], new named_type(IFC2X3_types[608]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC2X3_types[826])
      ->set_attributes({new attribute(strings[2761],
                                      new named_type(IFC2X3_types[755]), false),
                        new attribute(strings[2762],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC2X3_types[814])),
                                      false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false});
  ((entity *)IFC2X3_types[827])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false});
  ((entity *)IFC2X3_types[828])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[829])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[830])
      ->set_attributes(
          {new attribute(strings[2792], new named_type(IFC2X3_types[504]),
                         true),
           new attribute(strings[2793], new named_type(IFC2X3_types[504]),
                         true),
           new attribute(strings[2794], new named_type(IFC2X3_types[504]),
                         true),
           new attribute(strings[2795], new named_type(IFC2X3_types[504]),
                         true),
           new attribute(strings[2796], new named_type(IFC2X3_types[960]),
                         true),
           new attribute(strings[2797], new named_type(IFC2X3_types[435]),
                         true),
           new attribute(strings[2798], new named_type(IFC2X3_types[435]),
                         true),
           new attribute(strings[2799], new named_type(IFC2X3_types[47]), true),
           new attribute(strings[2800], new named_type(IFC2X3_types[47]), true),
           new attribute(strings[2801], new named_type(IFC2X3_types[744]),
                         true),
           new attribute(strings[2802], new named_type(IFC2X3_types[744]),
                         true),
           new attribute(strings[2803], new named_type(IFC2X3_types[744]),
                         true),
           new attribute(strings[2804], new named_type(IFC2X3_types[744]),
                         true),
           new attribute(strings[2805], new named_type(IFC2X3_types[744]),
                         true),
           new attribute(strings[2093], new named_type(IFC2X3_types[435]),
                         true),
           new attribute(strings[2046], new named_type(IFC2X3_types[435]),
                         true)},
          {false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[831])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[832])
      ->set_attributes(
          {new attribute(strings[2806], new named_type(IFC2X3_types[24]),
                         false),
           new attribute(strings[2807], new named_type(IFC2X3_types[815]),
                         true),
           new attribute(strings[2808],
                         new simple_type(simple_type::boolean_type), false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[833])
      ->set_attributes(
          {new attribute(strings[2809], new named_type(IFC2X3_types[47]), true),
           new attribute(strings[2810], new named_type(IFC2X3_types[47]), true),
           new attribute(strings[2811], new named_type(IFC2X3_types[579]),
                         true),
           new attribute(strings[2812], new named_type(IFC2X3_types[579]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[834])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[835])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[837]),
                         false),
           new attribute(strings[2105], new named_type(IFC2X3_types[577]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[836])
      ->set_attributes(
          {new attribute(
               strings[2813],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC2X3_types[577])),
               false),
           new attribute(strings[2814], new named_type(IFC2X3_types[755]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[838])->set_attributes({}, {false});
  ((entity *)IFC2X3_types[841])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[839])
      ->set_attributes({new attribute(strings[2007],
                                      new named_type(IFC2X3_types[720]), true),
                        new attribute(strings[2523],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[594])),
                                      false),
                        new attribute(strings[2013],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false});
  ((entity *)IFC2X3_types[840])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[842])
      ->set_attributes(
          {new attribute(strings[2815], new named_type(IFC2X3_types[8]), true),
           new attribute(strings[2816], new named_type(IFC2X3_types[879]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[843])
      ->set_attributes(
          {new attribute(strings[2817], new named_type(IFC2X3_types[269]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[844])->set_attributes({}, {});
  ((entity *)IFC2X3_types[845])
      ->set_attributes(
          {new attribute(strings[2818], new named_type(IFC2X3_types[193]),
                         false),
           new attribute(strings[2819], new named_type(IFC2X3_types[539]),
                         false),
           new attribute(strings[2820], new named_type(IFC2X3_types[539]),
                         false),
           new attribute(strings[2821], new named_type(IFC2X3_types[844]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[846])
      ->set_attributes(
          {new attribute(strings[2290], new named_type(IFC2X3_types[226]),
                         false),
           new attribute(strings[2088], new named_type(IFC2X3_types[435]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[847])
      ->set_attributes({new attribute(strings[2822],
                                      new named_type(IFC2X3_types[52]), false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[850])
      ->set_attributes({new attribute(strings[2823],
                                      new named_type(IFC2X3_types[849]), false),
                        new attribute(strings[2523],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, 5,
                                          new named_type(IFC2X3_types[851])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC2X3_types[852])
      ->set_attributes(
          {new attribute(strings[2824], new named_type(IFC2X3_types[125]),
                         false),
           new attribute(strings[2825], new named_type(IFC2X3_types[125]),
                         false),
           new attribute(strings[2826], new named_type(IFC2X3_types[125]),
                         false),
           new attribute(strings[2827], new named_type(IFC2X3_types[125]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[853])
      ->set_attributes({new attribute(strings[2828],
                                      new named_type(IFC2X3_types[652]), true),
                        new attribute(strings[2829],
                                      new named_type(IFC2X3_types[652]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[854])
      ->set_attributes(
          {new attribute(strings[2830], new named_type(IFC2X3_types[512]),
                         true),
           new attribute(strings[2831], new named_type(IFC2X3_types[124]),
                         true),
           new attribute(strings[2826], new named_type(IFC2X3_types[124]),
                         true),
           new attribute(strings[2824], new named_type(IFC2X3_types[124]),
                         true),
           new attribute(strings[2832], new named_type(IFC2X3_types[124]),
                         true),
           new attribute(strings[2833], new named_type(IFC2X3_types[124]),
                         true),
           new attribute(strings[2834], new named_type(IFC2X3_types[790]),
                         true),
           new attribute(strings[2835], new named_type(IFC2X3_types[658]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[855])
      ->set_attributes(
          {new attribute(strings[2836], new named_type(IFC2X3_types[125]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[856])
      ->set_attributes({new attribute(strings[2837],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[857])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[857])
      ->set_attributes(
          {new attribute(strings[2838],
                         new simple_type(simple_type::boolean_type), false),
           new attribute(strings[2839],
                         new simple_type(simple_type::boolean_type), false),
           new attribute(strings[2840], new named_type(IFC2X3_types[858]),
                         false),
           new attribute(strings[2841], new named_type(IFC2X3_types[100]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[859])
      ->set_attributes({new attribute(strings[2842],
                                      new named_type(IFC2X3_types[604]), false),
                        new attribute(strings[2132],
                                      new named_type(IFC2X3_types[55]), false)},
                       {false, false});
  ((entity *)IFC2X3_types[860])
      ->set_attributes(
          {new attribute(strings[2818], new named_type(IFC2X3_types[193]),
                         false),
           new attribute(strings[2107], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2843], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2819], new named_type(IFC2X3_types[539]),
                         false),
           new attribute(strings[2820], new named_type(IFC2X3_types[539]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[861])
      ->set_attributes({new attribute(strings[2844],
                                      new named_type(IFC2X3_types[604]), false),
                        new attribute(strings[2132],
                                      new named_type(IFC2X3_types[55]), false)},
                       {false, false});
  ((entity *)IFC2X3_types[862])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[863]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[864])
      ->set_attributes(
          {new attribute(strings[2845], new named_type(IFC2X3_types[865]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[866])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[867])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[928])
      ->set_attributes({new attribute(strings[2088],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2846],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2180],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2363],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2364],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2847],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2848],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2849],
                                      new named_type(IFC2X3_types[565]), true),
                        new attribute(strings[2850],
                                      new named_type(IFC2X3_types[565]), true),
                        new attribute(strings[2046],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC2X3_types[868])
      ->set_attributes(
          {new attribute(strings[2013],
                         new simple_type(simple_type::string_type), false),
           new attribute(
               strings[2851],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[869])),
               false)},
          {false, false});
  ((entity *)IFC2X3_types[869])
      ->set_attributes(
          {new attribute(
               strings[2852],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[940])),
               false),
           new attribute(strings[2853],
                         new simple_type(simple_type::boolean_type), false)},
          {false, false});
  ((entity *)IFC2X3_types[870])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[871]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[872])
      ->set_attributes(
          {new attribute(strings[2854], new named_type(IFC2X3_types[412]),
                         false),
           new attribute(strings[2169], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2855], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2856],
                         new simple_type(simple_type::boolean_type), false),
           new attribute(strings[2857],
                         new simple_type(simple_type::integer_type), true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[873])
      ->set_attributes(
          {new attribute(
               strings[2858],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[429])),
               true),
           new attribute(
               strings[2859],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[429])),
               true),
           new attribute(strings[2860], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(
               strings[2861],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[429])),
               true),
           new attribute(strings[2862], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[875])
      ->set_attributes({new attribute(strings[2000],
                                      new named_type(IFC2X3_types[877]), false),
                        new attribute(strings[2431],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2339],
                                      new named_type(IFC2X3_types[47]), false),
                        new attribute(strings[2863],
                                      new named_type(IFC2X3_types[378]), true),
                        new attribute(strings[2864],
                                      new named_type(IFC2X3_types[596]), true),
                        new attribute(strings[2865],
                                      new named_type(IFC2X3_types[512]), true),
                        new attribute(strings[2866],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2867],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false, false,
                        false});
  ((entity *)IFC2X3_types[876])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[878])
      ->set_attributes({new attribute(strings[2868],
                                      new named_type(IFC2X3_types[28]), false)},
                       {false, false, false, false});
  ((entity *)IFC2X3_types[884])
      ->set_attributes(
          {new attribute(strings[2869], new named_type(IFC2X3_types[590]),
                         false),
           new attribute(strings[2502], new named_type(IFC2X3_types[53]),
                         false),
           new attribute(strings[2870], new named_type(IFC2X3_types[886]),
                         false)},
          {false, false, false});
  ((entity *)IFC2X3_types[885])
      ->set_attributes({new attribute(strings[2871],
                                      new named_type(IFC2X3_types[562]), false),
                        new attribute(strings[2872],
                                      new named_type(IFC2X3_types[78]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[887])
      ->set_attributes(
          {new attribute(strings[2873], new named_type(IFC2X3_types[107]),
                         true),
           new attribute(strings[2874], new named_type(IFC2X3_types[890]),
                         true),
           new attribute(strings[2875], new named_type(IFC2X3_types[883]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC2X3_types[888])
      ->set_attributes(
          {new attribute(
               strings[2876],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[882])),
               true),
           new attribute(strings[2877], new named_type(IFC2X3_types[373]),
                         true),
           new attribute(strings[2878], new named_type(IFC2X3_types[374]),
                         true),
           new attribute(strings[2879], new named_type(IFC2X3_types[375]),
                         true),
           new attribute(strings[2880], new named_type(IFC2X3_types[767]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[889])
      ->set_attributes({new attribute(strings[2881],
                                      new named_type(IFC2X3_types[123]), false),
                        new attribute(strings[2882],
                                      new named_type(IFC2X3_types[123]), true)},
                       {false, false});
  ((entity *)IFC2X3_types[891])
      ->set_attributes({new attribute(strings[2883],
                                      new named_type(IFC2X3_types[767]), true),
                        new attribute(strings[2884],
                                      new named_type(IFC2X3_types[880]), true),
                        new attribute(strings[2885],
                                      new named_type(IFC2X3_types[881]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC2X3_types[767]), true),
                        new attribute(strings[2887],
                                      new named_type(IFC2X3_types[767]), true),
                        new attribute(strings[2888],
                                      new named_type(IFC2X3_types[893]), true),
                        new attribute(strings[2889],
                                      new named_type(IFC2X3_types[767]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[892])
      ->set_attributes({new attribute(strings[2890],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2891],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2892],
                                      new named_type(IFC2X3_types[565]), true),
                        new attribute(strings[2893],
                                      new named_type(IFC2X3_types[565]), true),
                        new attribute(strings[2894],
                                      new named_type(IFC2X3_types[767]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[894])->set_attributes({}, {});
  ((entity *)IFC2X3_types[895])
      ->set_attributes({new attribute(strings[2895],
                                      new named_type(IFC2X3_types[429]), false),
                        new attribute(strings[2896],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[762])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[896])
      ->set_attributes({new attribute(strings[2897],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[947])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[897])
      ->set_attributes({new attribute(strings[2097],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 2,
                                          new named_type(IFC2X3_types[539])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[903])
      ->set_attributes({new attribute(strings[2530],
                                      new named_type(IFC2X3_types[788]), true),
                        new attribute(strings[2898],
                                      new named_type(IFC2X3_types[906]), true),
                        new attribute(strings[2899],
                                      new named_type(IFC2X3_types[906]), true),
                        new attribute(strings[2900],
                                      new named_type(IFC2X3_types[899]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC2X3_types[908])
      ->set_attributes(
          {new attribute(strings[2013], new named_type(IFC2X3_types[429]),
                         false),
           new attribute(strings[1999], new named_type(IFC2X3_types[879]),
                         true),
           new attribute(strings[2901], new named_type(IFC2X3_types[206]),
                         false),
           new attribute(strings[2902], new named_type(IFC2X3_types[206]),
                         false),
           new attribute(strings[2903], new named_type(IFC2X3_types[909]),
                         false),
           new attribute(strings[2904], new named_type(IFC2X3_types[204]),
                         false),
           new attribute(strings[2905], new named_type(IFC2X3_types[429]),
                         true),
           new attribute(strings[2207], new named_type(IFC2X3_types[934]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[910])
      ->set_attributes({new attribute(strings[2906],
                                      new named_type(IFC2X3_types[908]), false),
                        new attribute(strings[2907],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[245])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[911])
      ->set_attributes(
          {new attribute(
               strings[2908],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[206])),
               true),
           new attribute(strings[2909], new named_type(IFC2X3_types[912]),
                         false),
           new attribute(strings[2910], new named_type(IFC2X3_types[908]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[913])
      ->set_attributes({new attribute(strings[2372],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC2X3_types[940])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[915])->set_attributes({}, {});
  ((entity *)IFC2X3_types[916])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC2X3_types[918])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[919]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[921])
      ->set_attributes({new attribute(strings[2253],
                                      new named_type(IFC2X3_types[923]), true),
                        new attribute(strings[2911],
                                      new named_type(IFC2X3_types[474]), true),
                        new attribute(strings[2912],
                                      new named_type(IFC2X3_types[176]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC2X3_types[922])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[923]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[924])
      ->set_attributes(
          {new attribute(strings[2913], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2914], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2080], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2915], new named_type(IFC2X3_types[435]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[925])
      ->set_attributes(
          {new attribute(strings[2458], new named_type(IFC2X3_types[193]),
                         false),
           new attribute(
               strings[2916],
               new aggregation_type(aggregation_type::set_type, 1, 2,
                                    new named_type(IFC2X3_types[927])),
               false),
           new attribute(
               strings[2917],
               new aggregation_type(aggregation_type::set_type, 1, 2,
                                    new named_type(IFC2X3_types[927])),
               false),
           new attribute(strings[2918],
                         new simple_type(simple_type::boolean_type), false),
           new attribute(strings[2919], new named_type(IFC2X3_types[926]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC2X3_types[929])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[930]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[931])
      ->set_attributes(
          {new attribute(strings[2920], new named_type(IFC2X3_types[944]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[932])
      ->set_attributes({new attribute(strings[2921],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2922],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[625])),
                                      true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC2X3_types[933])
      ->set_attributes(
          {new attribute(
               strings[2923],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC2X3_types[721])),
               true),
           new attribute(strings[2275], new named_type(IFC2X3_types[429]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[939])
      ->set_attributes({new attribute(strings[2088],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2846],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2180],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2363],
                                      new named_type(IFC2X3_types[577]), false),
                        new attribute(strings[2364],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2373],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2850],
                                      new named_type(IFC2X3_types[565]), true),
                        new attribute(strings[2093],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC2X3_types[937])
      ->set_attributes({new attribute(strings[2924],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[934])),
                                      false)},
                       {false});
  ((entity *)IFC2X3_types[935])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[936]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[941])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[942]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[944])
      ->set_attributes(
          {new attribute(strings[2294], new named_type(IFC2X3_types[226]),
                         false),
           new attribute(strings[2925], new named_type(IFC2X3_types[435]),
                         false)},
          {false, false});
  ((entity *)IFC2X3_types[946])->set_attributes({}, {});
  ((entity *)IFC2X3_types[947])
      ->set_attributes({new attribute(strings[2926],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC2X3_types[897])),
                                      false),
                        new attribute(strings[2927],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC2X3_types[98])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[948])
      ->set_attributes(
          {new attribute(strings[2928], new named_type(IFC2X3_types[946]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[949])
      ->set_attributes(
          {new attribute(strings[2929], new named_type(IFC2X3_types[569]),
                         false)},
          {false});
  ((entity *)IFC2X3_types[950])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[951]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[952])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[953])
      ->set_attributes({new attribute(strings[2930],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 2,
                                          new named_type(IFC2X3_types[399])),
                                      false),
                        new attribute(strings[2931],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC2X3_types[435])),
                                      false)},
                       {false, false});
  ((entity *)IFC2X3_types[956])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[957])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[958])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[959]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[962])
      ->set_attributes(
          {new attribute(strings[2000], new named_type(IFC2X3_types[963]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC2X3_types[964])
      ->set_attributes(
          {new attribute(strings[2932],
                         new simple_type(simple_type::boolean_type), true),
           new attribute(strings[2933], new named_type(IFC2X3_types[421]),
                         true),
           new attribute(strings[2934], new named_type(IFC2X3_types[421]),
                         true),
           new attribute(strings[2935], new named_type(IFC2X3_types[421]),
                         true),
           new attribute(strings[2936], new named_type(IFC2X3_types[512]),
                         true),
           new attribute(strings[2937], new named_type(IFC2X3_types[547]),
                         true),
           new attribute(strings[2938], new named_type(IFC2X3_types[512]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[965])
      ->set_attributes({new attribute(strings[2175],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2237],
                                      new named_type(IFC2X3_types[577]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC2X3_types[966])
      ->set_attributes({new attribute(strings[2238],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2239],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2242],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2939],
                                      new named_type(IFC2X3_types[577]), true),
                        new attribute(strings[2940],
                                      new named_type(IFC2X3_types[512]), true),
                        new attribute(strings[2941],
                                      new named_type(IFC2X3_types[512]), true),
                        new attribute(strings[2942],
                                      new named_type(IFC2X3_types[512]), true),
                        new attribute(strings[2943],
                                      new named_type(IFC2X3_types[512]), true),
                        new attribute(strings[2248],
                                      new named_type(IFC2X3_types[755]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC2X3_types[969])
      ->set_attributes(
          {new attribute(strings[2253], new named_type(IFC2X3_types[967]),
                         false),
           new attribute(strings[2252], new named_type(IFC2X3_types[968]),
                         false),
           new attribute(strings[2486], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2487], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2248], new named_type(IFC2X3_types[755]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[970])
      ->set_attributes(
          {new attribute(strings[2254], new named_type(IFC2X3_types[971]),
                         false),
           new attribute(strings[2253], new named_type(IFC2X3_types[972]),
                         false),
           new attribute(strings[2255],
                         new simple_type(simple_type::boolean_type), false),
           new attribute(strings[2256],
                         new simple_type(simple_type::boolean_type), false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC2X3_types[973])
      ->set_attributes({new attribute(strings[2025],
                                      new named_type(IFC2X3_types[412]), false),
                        new attribute(strings[2484],
                                      new named_type(IFC2X3_types[206]), false),
                        new attribute(strings[2944],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC2X3_types[545])),
                                      true),
                        new attribute(strings[2001],
                                      new named_type(IFC2X3_types[429]), true),
                        new attribute(strings[2945],
                                      new named_type(IFC2X3_types[907]), true),
                        new attribute(strings[2694],
                                      new named_type(IFC2X3_types[907]), true),
                        new attribute(strings[2901],
                                      new named_type(IFC2X3_types[206]), false),
                        new attribute(strings[2946],
                                      new named_type(IFC2X3_types[206]), true),
                        new attribute(strings[2947],
                                      new named_type(IFC2X3_types[974]), true),
                        new attribute(strings[2948],
                                      new named_type(IFC2X3_types[429]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[975])
      ->set_attributes({},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[976])
      ->set_attributes({},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[979])
      ->set_attributes(
          {new attribute(strings[2088], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2846], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2180], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2363], new named_type(IFC2X3_types[577]),
                         false),
           new attribute(strings[2364], new named_type(IFC2X3_types[577]),
                         true),
           new attribute(strings[2373], new named_type(IFC2X3_types[577]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC2X3_types[978])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC2X3_types[6])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2949], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[670]),
          ((entity *)IFC2X3_types[670])->attributes()[0])});
  ((entity *)IFC2X3_types[11])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2950], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[545]),
               ((entity *)IFC2X3_types[545])->attributes()[7]),
           new inverse_attribute(
               strings[2951], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[531]),
               ((entity *)IFC2X3_types[531])->attributes()[4])});
  ((entity *)IFC2X3_types[27])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2952], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[698]),
          ((entity *)IFC2X3_types[698])->attributes()[0])});
  ((entity *)IFC2X3_types[37])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2953], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[657]),
               ((entity *)IFC2X3_types[657])->attributes()[1]),
           new inverse_attribute(strings[2954], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC2X3_types[38]),
                                 ((entity *)IFC2X3_types[38])->attributes()[0]),
           new inverse_attribute(
               strings[2955], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[38]),
               ((entity *)IFC2X3_types[38])->attributes()[1])});
  ((entity *)IFC2X3_types[40])
      ->set_inverse_attributes(
          {new inverse_attribute(strings[2956], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC2X3_types[41]),
                                 ((entity *)IFC2X3_types[41])->attributes()[1]),
           new inverse_attribute(strings[2957], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC2X3_types[43]),
                                 ((entity *)IFC2X3_types[43])->attributes()[0]),
           new inverse_attribute(
               strings[2958], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[43]),
               ((entity *)IFC2X3_types[43])->attributes()[1])});
  ((entity *)IFC2X3_types[113])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2959], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[114]),
          ((entity *)IFC2X3_types[114])->attributes()[1])});
  ((entity *)IFC2X3_types[114])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2960], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[115]),
               ((entity *)IFC2X3_types[115])->attributes()[1]),
           new inverse_attribute(
               strings[2961], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[115]),
               ((entity *)IFC2X3_types[115])->attributes()[0])});
  ((entity *)IFC2X3_types[133])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2962], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC2X3_types[132]),
          ((entity *)IFC2X3_types[132])->attributes()[0])});
  ((entity *)IFC2X3_types[152])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2963], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[154]),
               ((entity *)IFC2X3_types[154])->attributes()[0]),
           new inverse_attribute(
               strings[2964], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[156]),
               ((entity *)IFC2X3_types[156])->attributes()[2]),
           new inverse_attribute(
               strings[2957], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[156]),
               ((entity *)IFC2X3_types[156])->attributes()[3]),
           new inverse_attribute(
               strings[2965], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[617]),
               ((entity *)IFC2X3_types[617])->attributes()[0]),
           new inverse_attribute(
               strings[2966], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[153]),
               ((entity *)IFC2X3_types[153])->attributes()[2]),
           new inverse_attribute(
               strings[2967], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[153]),
               ((entity *)IFC2X3_types[153])->attributes()[3])});
  ((entity *)IFC2X3_types[163])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2968], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[671]),
          ((entity *)IFC2X3_types[671])->attributes()[0])});
  ((entity *)IFC2X3_types[177])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2969], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[700]),
               ((entity *)IFC2X3_types[700])->attributes()[1]),
           new inverse_attribute(
               strings[2970], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[699]),
               ((entity *)IFC2X3_types[699])->attributes()[1])});
  ((entity *)IFC2X3_types[221])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2971], inverse_attribute::set_type, 0, 2,
          ((entity *)IFC2X3_types[878]),
          ((entity *)IFC2X3_types[878])->attributes()[0])});
  ((entity *)IFC2X3_types[233])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2972], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[706]),
          ((entity *)IFC2X3_types[706])->attributes()[0])});
  ((entity *)IFC2X3_types[237])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2973], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[706]),
          ((entity *)IFC2X3_types[706])->attributes()[1])});
  ((entity *)IFC2X3_types[242])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2974], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[243]),
               ((entity *)IFC2X3_types[243])->attributes()[1]),
           new inverse_attribute(
               strings[2975], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[243]),
               ((entity *)IFC2X3_types[243])->attributes()[0])});
  ((entity *)IFC2X3_types[244])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2976], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[242]),
          ((entity *)IFC2X3_types[242])->attributes()[3])});
  ((entity *)IFC2X3_types[256])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2977], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[258]),
               ((entity *)IFC2X3_types[258])->attributes()[3]),
           new inverse_attribute(
               strings[2978], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[258]),
               ((entity *)IFC2X3_types[258])->attributes()[2])});
  ((entity *)IFC2X3_types[297])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2979], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[694]),
               ((entity *)IFC2X3_types[694])->attributes()[0]),
           new inverse_attribute(
               strings[2980], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[705]),
               ((entity *)IFC2X3_types[705])->attributes()[1]),
           new inverse_attribute(
               strings[2981], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[689]),
               ((entity *)IFC2X3_types[689])->attributes()[1]),
           new inverse_attribute(
               strings[2982], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[699]),
               ((entity *)IFC2X3_types[699])->attributes()[0]),
           new inverse_attribute(
               strings[2983], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[711]),
               ((entity *)IFC2X3_types[711])->attributes()[0]),
           new inverse_attribute(
               strings[2984], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[712]),
               ((entity *)IFC2X3_types[712])->attributes()[0]),
           new inverse_attribute(
               strings[2985], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[692]),
               ((entity *)IFC2X3_types[692])->attributes()[1]),
           new inverse_attribute(
               strings[2986], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[717]),
               ((entity *)IFC2X3_types[717])->attributes()[0]),
           new inverse_attribute(
               strings[2987], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[697]),
               ((entity *)IFC2X3_types[697])->attributes()[0]),
           new inverse_attribute(
               strings[2988], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[716]),
               ((entity *)IFC2X3_types[716])->attributes()[1]),
           new inverse_attribute(
               strings[2989], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[689]),
               ((entity *)IFC2X3_types[689])->attributes()[2]),
           new inverse_attribute(
               strings[2952], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[698]),
               ((entity *)IFC2X3_types[698])->attributes()[0])});
  ((entity *)IFC2X3_types[341])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2990], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC2X3_types[711]),
          ((entity *)IFC2X3_types[711])->attributes()[1])});
  ((entity *)IFC2X3_types[342])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2991], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC2X3_types[717]),
          ((entity *)IFC2X3_types[717])->attributes()[1])});
  ((entity *)IFC2X3_types[391])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2992], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[393]),
          ((entity *)IFC2X3_types[393])->attributes()[0])});
  ((entity *)IFC2X3_types[398])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2952], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[698]),
          ((entity *)IFC2X3_types[698])->attributes()[0])});
  ((entity *)IFC2X3_types[399])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2993], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[398]),
               ((entity *)IFC2X3_types[398])->attributes()[2]),
           new inverse_attribute(
               strings[2994], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[398]),
               ((entity *)IFC2X3_types[398])->attributes()[1]),
           new inverse_attribute(
               strings[2995], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[398]),
               ((entity *)IFC2X3_types[398])->attributes()[0]),
           new inverse_attribute(
               strings[2996], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[953]),
               ((entity *)IFC2X3_types[953])->attributes()[0])});
  ((entity *)IFC2X3_types[401])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2997], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC2X3_types[672]),
          ((entity *)IFC2X3_types[672])->attributes()[0])});
  ((entity *)IFC2X3_types[437])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2998], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[436]),
          ((entity *)IFC2X3_types[436])->attributes()[4])});
  ((entity *)IFC2X3_types[476])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2999], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[478]),
               ((entity *)IFC2X3_types[478])->attributes()[0]),
           new inverse_attribute(
               strings[2963], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[477]),
               ((entity *)IFC2X3_types[477])->attributes()[1])});
  ((entity *)IFC2X3_types[479])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3000], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC2X3_types[480]),
          ((entity *)IFC2X3_types[480])->attributes()[0])});
  ((entity *)IFC2X3_types[515])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3001], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[702]),
          ((entity *)IFC2X3_types[702])->attributes()[0])});
  ((entity *)IFC2X3_types[516])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3002], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[668]),
               ((entity *)IFC2X3_types[668])->attributes()[0]),
           new inverse_attribute(
               strings[3003], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[701]),
               ((entity *)IFC2X3_types[701])->attributes()[0]),
           new inverse_attribute(
               strings[3004], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[701]),
               ((entity *)IFC2X3_types[701])->attributes()[1]),
           new inverse_attribute(
               strings[3005], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[677]),
               ((entity *)IFC2X3_types[677])->attributes()[0])});
  ((entity *)IFC2X3_types[519])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3006], inverse_attribute::set_type, 1, 1,
               ((entity *)IFC2X3_types[600]),
               ((entity *)IFC2X3_types[600])->attributes()[0]),
           new inverse_attribute(
               strings[3007], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[459]),
               ((entity *)IFC2X3_types[459])->attributes()[0])});
  ((entity *)IFC2X3_types[527])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3008], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[705]),
          ((entity *)IFC2X3_types[705])->attributes()[0])});
  ((entity *)IFC2X3_types[531])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3009], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[532]),
               ((entity *)IFC2X3_types[532])->attributes()[3]),
           new inverse_attribute(
               strings[2958], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[532]),
               ((entity *)IFC2X3_types[532])->attributes()[2]),
           new inverse_attribute(
               strings[3010], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[546]),
               ((entity *)IFC2X3_types[546])->attributes()[1])});
  ((entity *)IFC2X3_types[545])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3011], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[546]),
          ((entity *)IFC2X3_types[546])->attributes()[0])});
  ((entity *)IFC2X3_types[550])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3012], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[548]),
          ((entity *)IFC2X3_types[548])->attributes()[0])});
  ((entity *)IFC2X3_types[576])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3013], inverse_attribute::unspecified_type, -1, -1,
               ((entity *)IFC2X3_types[692]),
               ((entity *)IFC2X3_types[692])->attributes()[0]),
           new inverse_attribute(
               strings[2989], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[691]),
               ((entity *)IFC2X3_types[691])->attributes()[1]),
           new inverse_attribute(
               strings[2981], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[691]),
               ((entity *)IFC2X3_types[691])->attributes()[0])});
  ((entity *)IFC2X3_types[599])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3014], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[673]),
               ((entity *)IFC2X3_types[673])->attributes()[0]),
           new inverse_attribute(
               strings[3015], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[714]),
               ((entity *)IFC2X3_types[714])->attributes()[1]),
           new inverse_attribute(
               strings[3016], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[714]),
               ((entity *)IFC2X3_types[714])->attributes()[0])});
  ((entity *)IFC2X3_types[600])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3017], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[674]),
          ((entity *)IFC2X3_types[674])->attributes()[0])});
  ((entity *)IFC2X3_types[601])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3018], inverse_attribute::set_type, 1, 1,
               ((entity *)IFC2X3_types[600]),
               ((entity *)IFC2X3_types[600])->attributes()[1]),
           new inverse_attribute(
               strings[3019], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[755]),
               ((entity *)IFC2X3_types[755])->attributes()[4])});
  ((entity *)IFC2X3_types[615])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3020], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[619]),
               ((entity *)IFC2X3_types[619])->attributes()[0]),
           new inverse_attribute(
               strings[3021], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[619]),
               ((entity *)IFC2X3_types[619])->attributes()[1]),
           new inverse_attribute(
               strings[3012], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[131]),
               ((entity *)IFC2X3_types[131])->attributes()[1])});
  ((entity *)IFC2X3_types[618])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3005], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[677]),
          ((entity *)IFC2X3_types[677])->attributes()[0])});
  ((entity *)IFC2X3_types[625])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3022], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[703]),
               ((entity *)IFC2X3_types[703])->attributes()[0]),
           new inverse_attribute(
               strings[3023], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[932]),
               ((entity *)IFC2X3_types[932])->attributes()[1])});
  ((entity *)IFC2X3_types[718])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3024], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[721]),
               ((entity *)IFC2X3_types[721])->attributes()[1]),
           new inverse_attribute(
               strings[3025], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[591]),
               ((entity *)IFC2X3_types[591])->attributes()[2]),
           new inverse_attribute(
               strings[3026], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[602]),
               ((entity *)IFC2X3_types[602])->attributes()[2])});
  ((entity *)IFC2X3_types[719])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3027], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[718]),
          ((entity *)IFC2X3_types[718])->attributes()[0])});
  ((entity *)IFC2X3_types[720])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3025], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[591]),
               ((entity *)IFC2X3_types[591])->attributes()[2]),
           new inverse_attribute(
               strings[3028], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[839]),
               ((entity *)IFC2X3_types[839])->attributes()[0])});
  ((entity *)IFC2X3_types[721])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3029], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[471]),
          ((entity *)IFC2X3_types[471])->attributes()[0])});
  ((entity *)IFC2X3_types[722])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3030], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[676]),
          ((entity *)IFC2X3_types[676])->attributes()[0])});
  ((entity *)IFC2X3_types[740])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3031], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC2X3_types[669]),
          ((entity *)IFC2X3_types[669])->attributes()[0])});
  ((entity *)IFC2X3_types[756])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3032], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[755]),
          ((entity *)IFC2X3_types[755])->attributes()[0])});
  ((entity *)IFC2X3_types[779])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[2982], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[700]),
               ((entity *)IFC2X3_types[700])->attributes()[0]),
           new inverse_attribute(
               strings[3033], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[716]),
               ((entity *)IFC2X3_types[716])->attributes()[0])});
  ((entity *)IFC2X3_types[782])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3034], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[707]),
               ((entity *)IFC2X3_types[707])->attributes()[3]),
           new inverse_attribute(
               strings[3035], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[707]),
               ((entity *)IFC2X3_types[707])->attributes()[4])});
  ((entity *)IFC2X3_types[786])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3036], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[712]),
               ((entity *)IFC2X3_types[712])->attributes()[1]),
           new inverse_attribute(
               strings[3037], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[715]),
               ((entity *)IFC2X3_types[715])->attributes()[1]),
           new inverse_attribute(
               strings[3038], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[698]),
               ((entity *)IFC2X3_types[698])->attributes()[1])});
  ((entity *)IFC2X3_types[802])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3039], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC2X3_types[693]),
          ((entity *)IFC2X3_types[693])->attributes()[1])});
  ((entity *)IFC2X3_types[805])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3040], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC2X3_types[695]),
          ((entity *)IFC2X3_types[695])->attributes()[1])});
  ((entity *)IFC2X3_types[811])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3041], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[693]),
          ((entity *)IFC2X3_types[693])->attributes()[0])});
  ((entity *)IFC2X3_types[815])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3042], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC2X3_types[832]),
               ((entity *)IFC2X3_types[832])->attributes()[1]),
           new inverse_attribute(
               strings[3043], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[804]),
               ((entity *)IFC2X3_types[804])->attributes()[2])});
  ((entity *)IFC2X3_types[824])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3044], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[694]),
               ((entity *)IFC2X3_types[694])->attributes()[1]),
           new inverse_attribute(
               strings[3045], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC2X3_types[695]),
               ((entity *)IFC2X3_types[695])->attributes()[0])});
  ((entity *)IFC2X3_types[831])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3046], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC2X3_types[801]),
          ((entity *)IFC2X3_types[801])->attributes()[1])});
  ((entity *)IFC2X3_types[832])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3047], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[804]),
          ((entity *)IFC2X3_types[804])->attributes()[3])});
  ((entity *)IFC2X3_types[866])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3048], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[715]),
          ((entity *)IFC2X3_types[715])->attributes()[0])});
  ((entity *)IFC2X3_types[869])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3049], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC2X3_types[868]),
          ((entity *)IFC2X3_types[868])->attributes()[1])});
  ((entity *)IFC2X3_types[894])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3050], inverse_attribute::set_type, 1, 1,
          ((entity *)IFC2X3_types[32]),
          ((entity *)IFC2X3_types[32])->attributes()[1])});
  ((entity *)IFC2X3_types[908])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3051], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[910]),
          ((entity *)IFC2X3_types[910])->attributes()[0])});
  ((entity *)IFC2X3_types[932])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3052], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC2X3_types[704]),
          ((entity *)IFC2X3_types[704])->attributes()[0])});
  ((entity *)IFC2X3_types[132])->set_subtypes({((entity *)IFC2X3_types[0])});
  ((entity *)IFC2X3_types[163])
      ->set_subtypes(
          {((entity *)IFC2X3_types[3]), ((entity *)IFC2X3_types[141]),
           ((entity *)IFC2X3_types[172]), ((entity *)IFC2X3_types[173]),
           ((entity *)IFC2X3_types[316]), ((entity *)IFC2X3_types[383]),
           ((entity *)IFC2X3_types[541]), ((entity *)IFC2X3_types[544]),
           ((entity *)IFC2X3_types[611]), ((entity *)IFC2X3_types[612]),
           ((entity *)IFC2X3_types[740]), ((entity *)IFC2X3_types[751]),
           ((entity *)IFC2X3_types[782]), ((entity *)IFC2X3_types[911]),
           ((entity *)IFC2X3_types[973])});
  ((entity *)IFC2X3_types[515])
      ->set_subtypes(
          {((entity *)IFC2X3_types[6]), ((entity *)IFC2X3_types[163]),
           ((entity *)IFC2X3_types[401]), ((entity *)IFC2X3_types[599]),
           ((entity *)IFC2X3_types[600]), ((entity *)IFC2X3_types[607]),
           ((entity *)IFC2X3_types[722])});
  ((entity *)IFC2X3_types[234])
      ->set_subtypes({((entity *)IFC2X3_types[9]), ((entity *)IFC2X3_types[20]),
                      ((entity *)IFC2X3_types[164]),
                      ((entity *)IFC2X3_types[358]),
                      ((entity *)IFC2X3_types[748])});
  ((entity *)IFC2X3_types[354])
      ->set_subtypes(
          {((entity *)IFC2X3_types[14]), ((entity *)IFC2X3_types[202]),
           ((entity *)IFC2X3_types[294]), ((entity *)IFC2X3_types[360]),
           ((entity *)IFC2X3_types[629]), ((entity *)IFC2X3_types[862]),
           ((entity *)IFC2X3_types[941])});
  ((entity *)IFC2X3_types[369])
      ->set_subtypes(
          {((entity *)IFC2X3_types[16]), ((entity *)IFC2X3_types[276]),
           ((entity *)IFC2X3_types[289]), ((entity *)IFC2X3_types[351]),
           ((entity *)IFC2X3_types[385]), ((entity *)IFC2X3_types[431]),
           ((entity *)IFC2X3_types[443]), ((entity *)IFC2X3_types[535]),
           ((entity *)IFC2X3_types[738]), ((entity *)IFC2X3_types[793]),
           ((entity *)IFC2X3_types[962])});
  ((entity *)IFC2X3_types[309])
      ->set_subtypes(
          {((entity *)IFC2X3_types[18]), ((entity *)IFC2X3_types[63]),
           ((entity *)IFC2X3_types[108]), ((entity *)IFC2X3_types[121]),
           ((entity *)IFC2X3_types[138]), ((entity *)IFC2X3_types[167]),
           ((entity *)IFC2X3_types[169]), ((entity *)IFC2X3_types[287]),
           ((entity *)IFC2X3_types[291]), ((entity *)IFC2X3_types[317]),
           ((entity *)IFC2X3_types[319]), ((entity *)IFC2X3_types[404]),
           ((entity *)IFC2X3_types[409]), ((entity *)IFC2X3_types[508]),
           ((entity *)IFC2X3_types[780]), ((entity *)IFC2X3_types[918]),
           ((entity *)IFC2X3_types[929]), ((entity *)IFC2X3_types[935])});
  ((entity *)IFC2X3_types[222])
      ->set_subtypes(
          {((entity *)IFC2X3_types[25]), ((entity *)IFC2X3_types[217]),
           ((entity *)IFC2X3_types[453]), ((entity *)IFC2X3_types[641])});
  ((entity *)IFC2X3_types[600])
      ->set_subtypes(
          {((entity *)IFC2X3_types[27]), ((entity *)IFC2X3_types[297]),
           ((entity *)IFC2X3_types[398]), ((entity *)IFC2X3_types[576]),
           ((entity *)IFC2X3_types[631]), ((entity *)IFC2X3_types[786]),
           ((entity *)IFC2X3_types[802]), ((entity *)IFC2X3_types[811])});
  ((entity *)IFC2X3_types[31])
      ->set_subtypes(
          {((entity *)IFC2X3_types[28]), ((entity *)IFC2X3_types[30]),
           ((entity *)IFC2X3_types[33]), ((entity *)IFC2X3_types[34]),
           ((entity *)IFC2X3_types[35])});
  ((entity *)IFC2X3_types[392])
      ->set_subtypes(
          {((entity *)IFC2X3_types[29]),  ((entity *)IFC2X3_types[32]),
           ((entity *)IFC2X3_types[69]),  ((entity *)IFC2X3_types[77]),
           ((entity *)IFC2X3_types[99]),  ((entity *)IFC2X3_types[133]),
           ((entity *)IFC2X3_types[183]), ((entity *)IFC2X3_types[193]),
           ((entity *)IFC2X3_types[209]), ((entity *)IFC2X3_types[226]),
           ((entity *)IFC2X3_types[256]), ((entity *)IFC2X3_types[329]),
           ((entity *)IFC2X3_types[344]), ((entity *)IFC2X3_types[347]),
           ((entity *)IFC2X3_types[345]), ((entity *)IFC2X3_types[394]),
           ((entity *)IFC2X3_types[402]), ((entity *)IFC2X3_types[446]),
           ((entity *)IFC2X3_types[526]), ((entity *)IFC2X3_types[560]),
           ((entity *)IFC2X3_types[562]), ((entity *)IFC2X3_types[569]),
           ((entity *)IFC2X3_types[743]), ((entity *)IFC2X3_types[760]),
           ((entity *)IFC2X3_types[773]), ((entity *)IFC2X3_types[844]),
           ((entity *)IFC2X3_types[884]), ((entity *)IFC2X3_types[944])});
  ((entity *)IFC2X3_types[839])->set_subtypes({((entity *)IFC2X3_types[31])});
  ((entity *)IFC2X3_types[604])
      ->set_subtypes(
          {((entity *)IFC2X3_types[44]), ((entity *)IFC2X3_types[45]),
           ((entity *)IFC2X3_types[134]), ((entity *)IFC2X3_types[212]),
           ((entity *)IFC2X3_types[538])});
  ((entity *)IFC2X3_types[44])->set_subtypes({((entity *)IFC2X3_types[46])});
  ((entity *)IFC2X3_types[401])
      ->set_subtypes(
          {((entity *)IFC2X3_types[50]), ((entity *)IFC2X3_types[140]),
           ((entity *)IFC2X3_types[419]), ((entity *)IFC2X3_types[815]),
           ((entity *)IFC2X3_types[832]), ((entity *)IFC2X3_types[866]),
           ((entity *)IFC2X3_types[978])});
  ((entity *)IFC2X3_types[424])->set_subtypes({((entity *)IFC2X3_types[51])});
  ((entity *)IFC2X3_types[560])
      ->set_subtypes({((entity *)IFC2X3_types[52]),
                      ((entity *)IFC2X3_types[54]),
                      ((entity *)IFC2X3_types[55])});
  ((entity *)IFC2X3_types[75])
      ->set_subtypes(
          {((entity *)IFC2X3_types[80]), ((entity *)IFC2X3_types[132]),
           ((entity *)IFC2X3_types[574]), ((entity *)IFC2X3_types[925])});
  ((entity *)IFC2X3_types[83])
      ->set_subtypes(
          {((entity *)IFC2X3_types[56]),  ((entity *)IFC2X3_types[84]),
           ((entity *)IFC2X3_types[86]),  ((entity *)IFC2X3_types[127]),
           ((entity *)IFC2X3_types[177]), ((entity *)IFC2X3_types[189]),
           ((entity *)IFC2X3_types[247]), ((entity *)IFC2X3_types[376]),
           ((entity *)IFC2X3_types[492]), ((entity *)IFC2X3_types[552]),
           ((entity *)IFC2X3_types[566]), ((entity *)IFC2X3_types[642]),
           ((entity *)IFC2X3_types[645]), ((entity *)IFC2X3_types[646]),
           ((entity *)IFC2X3_types[730]), ((entity *)IFC2X3_types[768]),
           ((entity *)IFC2X3_types[795]), ((entity *)IFC2X3_types[796]),
           ((entity *)IFC2X3_types[956]), ((entity *)IFC2X3_types[965])});
  ((entity *)IFC2X3_types[89])
      ->set_subtypes(
          {((entity *)IFC2X3_types[57]), ((entity *)IFC2X3_types[87]),
           ((entity *)IFC2X3_types[128]), ((entity *)IFC2X3_types[178]),
           ((entity *)IFC2X3_types[190]), ((entity *)IFC2X3_types[493]),
           ((entity *)IFC2X3_types[567]), ((entity *)IFC2X3_types[643]),
           ((entity *)IFC2X3_types[647]), ((entity *)IFC2X3_types[769]),
           ((entity *)IFC2X3_types[797]), ((entity *)IFC2X3_types[958])});
  ((entity *)IFC2X3_types[80])->set_subtypes({((entity *)IFC2X3_types[60])});
  ((entity *)IFC2X3_types[857])
      ->set_subtypes({((entity *)IFC2X3_types[61]),
                      ((entity *)IFC2X3_types[414]),
                      ((entity *)IFC2X3_types[559])});
  ((entity *)IFC2X3_types[183])
      ->set_subtypes(
          {((entity *)IFC2X3_types[62]), ((entity *)IFC2X3_types[655]),
           ((entity *)IFC2X3_types[727]), ((entity *)IFC2X3_types[728]),
           ((entity *)IFC2X3_types[792])});
  ((entity *)IFC2X3_types[69])->set_subtypes({((entity *)IFC2X3_types[66])});
  ((entity *)IFC2X3_types[70])
      ->set_subtypes({((entity *)IFC2X3_types[71]),
                      ((entity *)IFC2X3_types[72]),
                      ((entity *)IFC2X3_types[73])});
  ((entity *)IFC2X3_types[73])->set_subtypes({((entity *)IFC2X3_types[74])});
  ((entity *)IFC2X3_types[193])
      ->set_subtypes(
          {((entity *)IFC2X3_types[75]), ((entity *)IFC2X3_types[143]),
           ((entity *)IFC2X3_types[452]), ((entity *)IFC2X3_types[524]),
           ((entity *)IFC2X3_types[525])});
  ((entity *)IFC2X3_types[844])
      ->set_subtypes({((entity *)IFC2X3_types[76]),
                      ((entity *)IFC2X3_types[298]),
                      ((entity *)IFC2X3_types[861])});
  ((entity *)IFC2X3_types[402])
      ->set_subtypes(
          {((entity *)IFC2X3_types[79]), ((entity *)IFC2X3_types[573])});
  ((entity *)IFC2X3_types[786])
      ->set_subtypes(
          {((entity *)IFC2X3_types[82]), ((entity *)IFC2X3_types[90]),
           ((entity *)IFC2X3_types[764]), ((entity *)IFC2X3_types[779])});
  ((entity *)IFC2X3_types[297])
      ->set_subtypes(
          {((entity *)IFC2X3_types[83]), ((entity *)IFC2X3_types[235]),
           ((entity *)IFC2X3_types[275]), ((entity *)IFC2X3_types[299]),
           ((entity *)IFC2X3_types[301]), ((entity *)IFC2X3_types[315]),
           ((entity *)IFC2X3_types[340]), ((entity *)IFC2X3_types[381]),
           ((entity *)IFC2X3_types[921]), ((entity *)IFC2X3_types[952])});
  ((entity *)IFC2X3_types[84])
      ->set_subtypes(
          {((entity *)IFC2X3_types[85]), ((entity *)IFC2X3_types[665])});
  ((entity *)IFC2X3_types[305])
      ->set_subtypes(
          {((entity *)IFC2X3_types[89]), ((entity *)IFC2X3_types[236]),
           ((entity *)IFC2X3_types[302]), ((entity *)IFC2X3_types[382]),
           ((entity *)IFC2X3_types[787]), ((entity *)IFC2X3_types[922])});
  ((entity *)IFC2X3_types[538])
      ->set_subtypes(
          {((entity *)IFC2X3_types[186]), ((entity *)IFC2X3_types[112]),
           ((entity *)IFC2X3_types[180]), ((entity *)IFC2X3_types[181]),
           ((entity *)IFC2X3_types[307]), ((entity *)IFC2X3_types[424]),
           ((entity *)IFC2X3_types[464]), ((entity *)IFC2X3_types[654]),
           ((entity *)IFC2X3_types[928]), ((entity *)IFC2X3_types[924]),
           ((entity *)IFC2X3_types[939]), ((entity *)IFC2X3_types[979])});
  ((entity *)IFC2X3_types[357])
      ->set_subtypes(
          {((entity *)IFC2X3_types[91]), ((entity *)IFC2X3_types[262]),
           ((entity *)IFC2X3_types[426]), ((entity *)IFC2X3_types[555])});
  ((entity *)IFC2X3_types[365])
      ->set_subtypes(
          {((entity *)IFC2X3_types[93]), ((entity *)IFC2X3_types[95]),
           ((entity *)IFC2X3_types[264]), ((entity *)IFC2X3_types[557])});
  ((entity *)IFC2X3_types[569])
      ->set_subtypes({((entity *)IFC2X3_types[98]),
                      ((entity *)IFC2X3_types[570]),
                      ((entity *)IFC2X3_types[571])});
  ((entity *)IFC2X3_types[99])
      ->set_subtypes(
          {((entity *)IFC2X3_types[100]), ((entity *)IFC2X3_types[102])});
  ((entity *)IFC2X3_types[100])->set_subtypes({((entity *)IFC2X3_types[101])});
  ((entity *)IFC2X3_types[102])->set_subtypes({((entity *)IFC2X3_types[103])});
  ((entity *)IFC2X3_types[45])->set_subtypes({((entity *)IFC2X3_types[104])});
  ((entity *)IFC2X3_types[271])
      ->set_subtypes(
          {((entity *)IFC2X3_types[105]), ((entity *)IFC2X3_types[736])});
  ((entity *)IFC2X3_types[143])
      ->set_subtypes(
          {((entity *)IFC2X3_types[110]), ((entity *)IFC2X3_types[306])});
  ((entity *)IFC2X3_types[112])->set_subtypes({((entity *)IFC2X3_types[111])});
  ((entity *)IFC2X3_types[326])
      ->set_subtypes(
          {((entity *)IFC2X3_types[119]), ((entity *)IFC2X3_types[244]),
           ((entity *)IFC2X3_types[322]), ((entity *)IFC2X3_types[323]),
           ((entity *)IFC2X3_types[324]), ((entity *)IFC2X3_types[325]),
           ((entity *)IFC2X3_types[437])});
  ((entity *)IFC2X3_types[144])
      ->set_subtypes(
          {((entity *)IFC2X3_types[120]), ((entity *)IFC2X3_types[528])});
  ((entity *)IFC2X3_types[126])->set_subtypes({((entity *)IFC2X3_types[125])});
  ((entity *)IFC2X3_types[615])
      ->set_subtypes(
          {((entity *)IFC2X3_types[131]), ((entity *)IFC2X3_types[761])});
  ((entity *)IFC2X3_types[363])
      ->set_subtypes({((entity *)IFC2X3_types[136]),
                      ((entity *)IFC2X3_types[336]),
                      ((entity *)IFC2X3_types[632])});
  ((entity *)IFC2X3_types[915])
      ->set_subtypes(
          {((entity *)IFC2X3_types[144]), ((entity *)IFC2X3_types[269]),
           ((entity *)IFC2X3_types[328]), ((entity *)IFC2X3_types[330]),
           ((entity *)IFC2X3_types[463]), ((entity *)IFC2X3_types[540]),
           ((entity *)IFC2X3_types[946])});
  ((entity *)IFC2X3_types[146])
      ->set_subtypes(
          {((entity *)IFC2X3_types[145]), ((entity *)IFC2X3_types[148]),
           ((entity *)IFC2X3_types[149]), ((entity *)IFC2X3_types[150])});
  ((entity *)IFC2X3_types[148])->set_subtypes({((entity *)IFC2X3_types[147])});
  ((entity *)IFC2X3_types[160])
      ->set_subtypes(
          {((entity *)IFC2X3_types[157]), ((entity *)IFC2X3_types[158]),
           ((entity *)IFC2X3_types[159]), ((entity *)IFC2X3_types[182]),
           ((entity *)IFC2X3_types[430]), ((entity *)IFC2X3_types[842])});
  ((entity *)IFC2X3_types[722])->set_subtypes({((entity *)IFC2X3_types[160])});
  ((entity *)IFC2X3_types[511])
      ->set_subtypes({((entity *)IFC2X3_types[162]),
                      ((entity *)IFC2X3_types[166]),
                      ((entity *)IFC2X3_types[765])});
  ((entity *)IFC2X3_types[37])
      ->set_subtypes(
          {((entity *)IFC2X3_types[175]), ((entity *)IFC2X3_types[314])});
  ((entity *)IFC2X3_types[773])
      ->set_subtypes(
          {((entity *)IFC2X3_types[185]), ((entity *)IFC2X3_types[470]),
           ((entity *)IFC2X3_types[859]), ((entity *)IFC2X3_types[860])});
  ((entity *)IFC2X3_types[76])
      ->set_subtypes(
          {((entity *)IFC2X3_types[194]), ((entity *)IFC2X3_types[656])});
  ((entity *)IFC2X3_types[593])
      ->set_subtypes(
          {((entity *)IFC2X3_types[197]), ((entity *)IFC2X3_types[343]),
           ((entity *)IFC2X3_types[850]), ((entity *)IFC2X3_types[864]),
           ((entity *)IFC2X3_types[887])});
  ((entity *)IFC2X3_types[258])
      ->set_subtypes(
          {((entity *)IFC2X3_types[219]), ((entity *)IFC2X3_types[225])});
  ((entity *)IFC2X3_types[28])
      ->set_subtypes(
          {((entity *)IFC2X3_types[221]), ((entity *)IFC2X3_types[609])});
  ((entity *)IFC2X3_types[256])
      ->set_subtypes(
          {((entity *)IFC2X3_types[222]), ((entity *)IFC2X3_types[838])});
  ((entity *)IFC2X3_types[878])->set_subtypes({((entity *)IFC2X3_types[223])});
  ((entity *)IFC2X3_types[301])
      ->set_subtypes(
          {((entity *)IFC2X3_types[228]), ((entity *)IFC2X3_types[338])});
  ((entity *)IFC2X3_types[302])
      ->set_subtypes(
          {((entity *)IFC2X3_types[229]), ((entity *)IFC2X3_types[339])});
  ((entity *)IFC2X3_types[237])
      ->set_subtypes(
          {((entity *)IFC2X3_types[230]), ((entity *)IFC2X3_types[308]),
           ((entity *)IFC2X3_types[353]), ((entity *)IFC2X3_types[356]),
           ((entity *)IFC2X3_types[362]), ((entity *)IFC2X3_types[364]),
           ((entity *)IFC2X3_types[366]), ((entity *)IFC2X3_types[368]),
           ((entity *)IFC2X3_types[370])});
  ((entity *)IFC2X3_types[238])
      ->set_subtypes(
          {((entity *)IFC2X3_types[231]), ((entity *)IFC2X3_types[309]),
           ((entity *)IFC2X3_types[354]), ((entity *)IFC2X3_types[357]),
           ((entity *)IFC2X3_types[363]), ((entity *)IFC2X3_types[365]),
           ((entity *)IFC2X3_types[367]), ((entity *)IFC2X3_types[369]),
           ((entity *)IFC2X3_types[371])});
  ((entity *)IFC2X3_types[235])
      ->set_subtypes(
          {((entity *)IFC2X3_types[233]), ((entity *)IFC2X3_types[237])});
  ((entity *)IFC2X3_types[236])
      ->set_subtypes(
          {((entity *)IFC2X3_types[234]), ((entity *)IFC2X3_types[238])});
  ((entity *)IFC2X3_types[576])->set_subtypes({((entity *)IFC2X3_types[239])});
  ((entity *)IFC2X3_types[625])
      ->set_subtypes(
          {((entity *)IFC2X3_types[248]), ((entity *)IFC2X3_types[251]),
           ((entity *)IFC2X3_types[304]), ((entity *)IFC2X3_types[311]),
           ((entity *)IFC2X3_types[372]), ((entity *)IFC2X3_types[543]),
           ((entity *)IFC2X3_types[624]), ((entity *)IFC2X3_types[661]),
           ((entity *)IFC2X3_types[752]), ((entity *)IFC2X3_types[776]),
           ((entity *)IFC2X3_types[778]), ((entity *)IFC2X3_types[783]),
           ((entity *)IFC2X3_types[966]), ((entity *)IFC2X3_types[969])});
  ((entity *)IFC2X3_types[933])
      ->set_subtypes({((entity *)IFC2X3_types[252]),
                      ((entity *)IFC2X3_types[305]),
                      ((entity *)IFC2X3_types[970])});
  ((entity *)IFC2X3_types[582])->set_subtypes({((entity *)IFC2X3_types[259])});
  ((entity *)IFC2X3_types[583])->set_subtypes({((entity *)IFC2X3_types[260])});
  ((entity *)IFC2X3_types[589])
      ->set_subtypes(
          {((entity *)IFC2X3_types[261]), ((entity *)IFC2X3_types[888])});
  ((entity *)IFC2X3_types[371])
      ->set_subtypes(
          {((entity *)IFC2X3_types[266]), ((entity *)IFC2X3_types[349])});
  ((entity *)IFC2X3_types[269])
      ->set_subtypes({((entity *)IFC2X3_types[270]),
                      ((entity *)IFC2X3_types[534]),
                      ((entity *)IFC2X3_types[843])});
  ((entity *)IFC2X3_types[342])
      ->set_subtypes(
          {((entity *)IFC2X3_types[271]), ((entity *)IFC2X3_types[527])});
  ((entity *)IFC2X3_types[463])
      ->set_subtypes({((entity *)IFC2X3_types[272]),
                      ((entity *)IFC2X3_types[575]),
                      ((entity *)IFC2X3_types[948])});
  ((entity *)IFC2X3_types[353])->set_subtypes({((entity *)IFC2X3_types[283])});
  ((entity *)IFC2X3_types[367])
      ->set_subtypes(
          {((entity *)IFC2X3_types[285]), ((entity *)IFC2X3_types[870])});
  ((entity *)IFC2X3_types[311])->set_subtypes({((entity *)IFC2X3_types[273])});
  ((entity *)IFC2X3_types[866])
      ->set_subtypes(
          {((entity *)IFC2X3_types[274]), ((entity *)IFC2X3_types[804])});
  ((entity *)IFC2X3_types[483])
      ->set_subtypes(
          {((entity *)IFC2X3_types[321]), ((entity *)IFC2X3_types[380]),
           ((entity *)IFC2X3_types[387]), ((entity *)IFC2X3_types[411]),
           ((entity *)IFC2X3_types[490]), ((entity *)IFC2X3_types[529]),
           ((entity *)IFC2X3_types[603]), ((entity *)IFC2X3_types[903]),
           ((entity *)IFC2X3_types[964])});
  ((entity *)IFC2X3_types[859])
      ->set_subtypes({((entity *)IFC2X3_types[327]),
                      ((entity *)IFC2X3_types[724]),
                      ((entity *)IFC2X3_types[845])});
  ((entity *)IFC2X3_types[330])->set_subtypes({((entity *)IFC2X3_types[331])});
  ((entity *)IFC2X3_types[328])->set_subtypes({((entity *)IFC2X3_types[332])});
  ((entity *)IFC2X3_types[470])
      ->set_subtypes(
          {((entity *)IFC2X3_types[333]), ((entity *)IFC2X3_types[334])});
  ((entity *)IFC2X3_types[806])
      ->set_subtypes(
          {((entity *)IFC2X3_types[335]), ((entity *)IFC2X3_types[771])});
  ((entity *)IFC2X3_types[340])
      ->set_subtypes(
          {((entity *)IFC2X3_types[341]), ((entity *)IFC2X3_types[342])});
  ((entity *)IFC2X3_types[382])
      ->set_subtypes(
          {((entity *)IFC2X3_types[384]), ((entity *)IFC2X3_types[867])});
  ((entity *)IFC2X3_types[605])
      ->set_subtypes(
          {((entity *)IFC2X3_types[388]), ((entity *)IFC2X3_types[726])});
  ((entity *)IFC2X3_types[394])->set_subtypes({((entity *)IFC2X3_types[389])});
  ((entity *)IFC2X3_types[719])->set_subtypes({((entity *)IFC2X3_types[391])});
  ((entity *)IFC2X3_types[720])
      ->set_subtypes(
          {((entity *)IFC2X3_types[392]), ((entity *)IFC2X3_types[471]),
           ((entity *)IFC2X3_types[839]), ((entity *)IFC2X3_types[915])});
  ((entity *)IFC2X3_types[391])->set_subtypes({((entity *)IFC2X3_types[393])});
  ((entity *)IFC2X3_types[519])
      ->set_subtypes(
          {((entity *)IFC2X3_types[400]), ((entity *)IFC2X3_types[459])});
  ((entity *)IFC2X3_types[908])
      ->set_subtypes(
          {((entity *)IFC2X3_types[422]), ((entity *)IFC2X3_types[659])});
  ((entity *)IFC2X3_types[446])
      ->set_subtypes(
          {((entity *)IFC2X3_types[447]), ((entity *)IFC2X3_types[448]),
           ((entity *)IFC2X3_types[449]), ((entity *)IFC2X3_types[450])});
  ((entity *)IFC2X3_types[450])->set_subtypes({((entity *)IFC2X3_types[451])});
  ((entity *)IFC2X3_types[602])
      ->set_subtypes(
          {((entity *)IFC2X3_types[478]), ((entity *)IFC2X3_types[601])});
  ((entity *)IFC2X3_types[490])
      ->set_subtypes(
          {((entity *)IFC2X3_types[487]), ((entity *)IFC2X3_types[491])});
  ((entity *)IFC2X3_types[338])->set_subtypes({((entity *)IFC2X3_types[488])});
  ((entity *)IFC2X3_types[339])->set_subtypes({((entity *)IFC2X3_types[489])});
  ((entity *)IFC2X3_types[152])
      ->set_subtypes(
          {((entity *)IFC2X3_types[495]), ((entity *)IFC2X3_types[517])});
  ((entity *)IFC2X3_types[872])
      ->set_subtypes(
          {((entity *)IFC2X3_types[510]), ((entity *)IFC2X3_types[530])});
  ((entity *)IFC2X3_types[516])
      ->set_subtypes(
          {((entity *)IFC2X3_types[515]), ((entity *)IFC2X3_types[932])});
  ((entity *)IFC2X3_types[732])
      ->set_subtypes({((entity *)IFC2X3_types[516]),
                      ((entity *)IFC2X3_types[618]),
                      ((entity *)IFC2X3_types[686])});
  ((entity *)IFC2X3_types[6])->set_subtypes({((entity *)IFC2X3_types[522])});
  ((entity *)IFC2X3_types[550])
      ->set_subtypes(
          {((entity *)IFC2X3_types[548]), ((entity *)IFC2X3_types[551])});
  ((entity *)IFC2X3_types[562])->set_subtypes({((entity *)IFC2X3_types[561])});
  ((entity *)IFC2X3_types[298])->set_subtypes({((entity *)IFC2X3_types[564])});
  ((entity *)IFC2X3_types[11])
      ->set_subtypes(
          {((entity *)IFC2X3_types[580]), ((entity *)IFC2X3_types[873])});
  ((entity *)IFC2X3_types[585])
      ->set_subtypes(
          {((entity *)IFC2X3_types[582]), ((entity *)IFC2X3_types[583]),
           ((entity *)IFC2X3_types[587]), ((entity *)IFC2X3_types[589])});
  ((entity *)IFC2X3_types[587])
      ->set_subtypes({((entity *)IFC2X3_types[584]),
                      ((entity *)IFC2X3_types[586]),
                      ((entity *)IFC2X3_types[588])});
  ((entity *)IFC2X3_types[591])->set_subtypes({((entity *)IFC2X3_types[592])});
  ((entity *)IFC2X3_types[599])
      ->set_subtypes(
          {((entity *)IFC2X3_types[597]), ((entity *)IFC2X3_types[872])});
  ((entity *)IFC2X3_types[341])->set_subtypes({((entity *)IFC2X3_types[610])});
  ((entity *)IFC2X3_types[761])
      ->set_subtypes(
          {((entity *)IFC2X3_types[616]), ((entity *)IFC2X3_types[620]),
           ((entity *)IFC2X3_types[622]), ((entity *)IFC2X3_types[623]),
           ((entity *)IFC2X3_types[626]), ((entity *)IFC2X3_types[628])});
  ((entity *)IFC2X3_types[618])->set_subtypes({((entity *)IFC2X3_types[625])});
  ((entity *)IFC2X3_types[551])
      ->set_subtypes(
          {((entity *)IFC2X3_types[634]), ((entity *)IFC2X3_types[635]),
           ((entity *)IFC2X3_types[636]), ((entity *)IFC2X3_types[637]),
           ((entity *)IFC2X3_types[638]), ((entity *)IFC2X3_types[639])});
  ((entity *)IFC2X3_types[60])->set_subtypes({((entity *)IFC2X3_types[651])});
  ((entity *)IFC2X3_types[654])
      ->set_subtypes(
          {((entity *)IFC2X3_types[653]), ((entity *)IFC2X3_types[737])});
  ((entity *)IFC2X3_types[665])
      ->set_subtypes(
          {((entity *)IFC2X3_types[662]), ((entity *)IFC2X3_types[666]),
           ((entity *)IFC2X3_types[875]), ((entity *)IFC2X3_types[876])});
  ((entity *)IFC2X3_types[701])
      ->set_subtypes(
          {((entity *)IFC2X3_types[667]), ((entity *)IFC2X3_types[708])});
  ((entity *)IFC2X3_types[686])
      ->set_subtypes(
          {((entity *)IFC2X3_types[668]), ((entity *)IFC2X3_types[677]),
           ((entity *)IFC2X3_types[688]), ((entity *)IFC2X3_types[701]),
           ((entity *)IFC2X3_types[702])});
  ((entity *)IFC2X3_types[671])
      ->set_subtypes({((entity *)IFC2X3_types[669]),
                      ((entity *)IFC2X3_types[675]),
                      ((entity *)IFC2X3_types[713])});
  ((entity *)IFC2X3_types[668])
      ->set_subtypes(
          {((entity *)IFC2X3_types[670]), ((entity *)IFC2X3_types[671]),
           ((entity *)IFC2X3_types[672]), ((entity *)IFC2X3_types[673]),
           ((entity *)IFC2X3_types[674]), ((entity *)IFC2X3_types[676])});
  ((entity *)IFC2X3_types[677])
      ->set_subtypes(
          {((entity *)IFC2X3_types[678]), ((entity *)IFC2X3_types[679]),
           ((entity *)IFC2X3_types[680]), ((entity *)IFC2X3_types[681]),
           ((entity *)IFC2X3_types[682]), ((entity *)IFC2X3_types[683]),
           ((entity *)IFC2X3_types[684]), ((entity *)IFC2X3_types[685])});
  ((entity *)IFC2X3_types[688])
      ->set_subtypes(
          {((entity *)IFC2X3_types[689]), ((entity *)IFC2X3_types[692]),
           ((entity *)IFC2X3_types[691]), ((entity *)IFC2X3_types[693]),
           ((entity *)IFC2X3_types[694]), ((entity *)IFC2X3_types[695]),
           ((entity *)IFC2X3_types[698]), ((entity *)IFC2X3_types[699]),
           ((entity *)IFC2X3_types[700]), ((entity *)IFC2X3_types[705]),
           ((entity *)IFC2X3_types[706]), ((entity *)IFC2X3_types[707]),
           ((entity *)IFC2X3_types[711]), ((entity *)IFC2X3_types[712]),
           ((entity *)IFC2X3_types[714]), ((entity *)IFC2X3_types[715]),
           ((entity *)IFC2X3_types[716]), ((entity *)IFC2X3_types[717])});
  ((entity *)IFC2X3_types[689])
      ->set_subtypes(
          {((entity *)IFC2X3_types[690]), ((entity *)IFC2X3_types[697])});
  ((entity *)IFC2X3_types[695])->set_subtypes({((entity *)IFC2X3_types[696])});
  ((entity *)IFC2X3_types[702])
      ->set_subtypes(
          {((entity *)IFC2X3_types[703]), ((entity *)IFC2X3_types[704])});
  ((entity *)IFC2X3_types[670])->set_subtypes({((entity *)IFC2X3_types[709])});
  ((entity *)IFC2X3_types[703])->set_subtypes({((entity *)IFC2X3_types[710])});
  ((entity *)IFC2X3_types[718])
      ->set_subtypes(
          {((entity *)IFC2X3_types[756]), ((entity *)IFC2X3_types[841])});
  ((entity *)IFC2X3_types[756])
      ->set_subtypes(
          {((entity *)IFC2X3_types[757]), ((entity *)IFC2X3_types[916])});
  ((entity *)IFC2X3_types[787])->set_subtypes({((entity *)IFC2X3_types[784])});
  ((entity *)IFC2X3_types[802])
      ->set_subtypes(
          {((entity *)IFC2X3_types[801]), ((entity *)IFC2X3_types[831])});
  ((entity *)IFC2X3_types[811])
      ->set_subtypes(
          {((entity *)IFC2X3_types[805]), ((entity *)IFC2X3_types[824])});
  ((entity *)IFC2X3_types[805])
      ->set_subtypes({((entity *)IFC2X3_types[807]),
                      ((entity *)IFC2X3_types[828]),
                      ((entity *)IFC2X3_types[834])});
  ((entity *)IFC2X3_types[824])
      ->set_subtypes(
          {((entity *)IFC2X3_types[808]), ((entity *)IFC2X3_types[835])});
  ((entity *)IFC2X3_types[808])->set_subtypes({((entity *)IFC2X3_types[809])});
  ((entity *)IFC2X3_types[801])
      ->set_subtypes({((entity *)IFC2X3_types[812]),
                      ((entity *)IFC2X3_types[825]),
                      ((entity *)IFC2X3_types[827])});
  ((entity *)IFC2X3_types[812])->set_subtypes({((entity *)IFC2X3_types[813])});
  ((entity *)IFC2X3_types[822])
      ->set_subtypes(
          {((entity *)IFC2X3_types[816]), ((entity *)IFC2X3_types[817]),
           ((entity *)IFC2X3_types[818]), ((entity *)IFC2X3_types[820]),
           ((entity *)IFC2X3_types[823])});
  ((entity *)IFC2X3_types[818])->set_subtypes({((entity *)IFC2X3_types[819])});
  ((entity *)IFC2X3_types[820])->set_subtypes({((entity *)IFC2X3_types[821])});
  ((entity *)IFC2X3_types[814])->set_subtypes({((entity *)IFC2X3_types[822])});
  ((entity *)IFC2X3_types[825])->set_subtypes({((entity *)IFC2X3_types[826])});
  ((entity *)IFC2X3_types[831])->set_subtypes({((entity *)IFC2X3_types[829])});
  ((entity *)IFC2X3_types[388])->set_subtypes({((entity *)IFC2X3_types[830])});
  ((entity *)IFC2X3_types[830])->set_subtypes({((entity *)IFC2X3_types[833])});
  ((entity *)IFC2X3_types[835])->set_subtypes({((entity *)IFC2X3_types[836])});
  ((entity *)IFC2X3_types[841])->set_subtypes({((entity *)IFC2X3_types[840])});
  ((entity *)IFC2X3_types[861])
      ->set_subtypes(
          {((entity *)IFC2X3_types[846]), ((entity *)IFC2X3_types[847])});
  ((entity *)IFC2X3_types[855])->set_subtypes({((entity *)IFC2X3_types[854])});
  ((entity *)IFC2X3_types[34])->set_subtypes({((entity *)IFC2X3_types[878])});
  ((entity *)IFC2X3_types[884])->set_subtypes({((entity *)IFC2X3_types[885])});
  ((entity *)IFC2X3_types[894])
      ->set_subtypes(
          {((entity *)IFC2X3_types[895]), ((entity *)IFC2X3_types[896])});
  ((entity *)IFC2X3_types[526])->set_subtypes({((entity *)IFC2X3_types[931])});
  ((entity *)IFC2X3_types[932])->set_subtypes({((entity *)IFC2X3_types[933])});
  ((entity *)IFC2X3_types[946])->set_subtypes({((entity *)IFC2X3_types[949])});
  ((entity *)IFC2X3_types[229])->set_subtypes({((entity *)IFC2X3_types[950])});
  ((entity *)IFC2X3_types[956])->set_subtypes({((entity *)IFC2X3_types[957])});
  ((entity *)IFC2X3_types[973])
      ->set_subtypes(
          {((entity *)IFC2X3_types[975]), ((entity *)IFC2X3_types[976])});
  return new schema_definition(
      strings[3053], {IFC2X3_types[0],   IFC2X3_types[1],   IFC2X3_types[2],
                      IFC2X3_types[3],   IFC2X3_types[4],   IFC2X3_types[5],
                      IFC2X3_types[6],   IFC2X3_types[7],   IFC2X3_types[8],
                      IFC2X3_types[9],   IFC2X3_types[10],  IFC2X3_types[11],
                      IFC2X3_types[12],  IFC2X3_types[13],  IFC2X3_types[14],
                      IFC2X3_types[15],  IFC2X3_types[16],  IFC2X3_types[17],
                      IFC2X3_types[18],  IFC2X3_types[19],  IFC2X3_types[20],
                      IFC2X3_types[21],  IFC2X3_types[22],  IFC2X3_types[23],
                      IFC2X3_types[24],  IFC2X3_types[25],  IFC2X3_types[26],
                      IFC2X3_types[27],  IFC2X3_types[28],  IFC2X3_types[29],
                      IFC2X3_types[30],  IFC2X3_types[31],  IFC2X3_types[32],
                      IFC2X3_types[33],  IFC2X3_types[34],  IFC2X3_types[35],
                      IFC2X3_types[36],  IFC2X3_types[37],  IFC2X3_types[38],
                      IFC2X3_types[39],  IFC2X3_types[40],  IFC2X3_types[41],
                      IFC2X3_types[42],  IFC2X3_types[43],  IFC2X3_types[44],
                      IFC2X3_types[45],  IFC2X3_types[46],  IFC2X3_types[47],
                      IFC2X3_types[48],  IFC2X3_types[49],  IFC2X3_types[50],
                      IFC2X3_types[51],  IFC2X3_types[52],  IFC2X3_types[53],
                      IFC2X3_types[54],  IFC2X3_types[55],  IFC2X3_types[56],
                      IFC2X3_types[57],  IFC2X3_types[58],  IFC2X3_types[59],
                      IFC2X3_types[60],  IFC2X3_types[61],  IFC2X3_types[62],
                      IFC2X3_types[63],  IFC2X3_types[64],  IFC2X3_types[65],
                      IFC2X3_types[66],  IFC2X3_types[67],  IFC2X3_types[68],
                      IFC2X3_types[69],  IFC2X3_types[70],  IFC2X3_types[71],
                      IFC2X3_types[72],  IFC2X3_types[73],  IFC2X3_types[74],
                      IFC2X3_types[75],  IFC2X3_types[76],  IFC2X3_types[77],
                      IFC2X3_types[78],  IFC2X3_types[79],  IFC2X3_types[80],
                      IFC2X3_types[81],  IFC2X3_types[82],  IFC2X3_types[83],
                      IFC2X3_types[84],  IFC2X3_types[85],  IFC2X3_types[86],
                      IFC2X3_types[87],  IFC2X3_types[88],  IFC2X3_types[89],
                      IFC2X3_types[90],  IFC2X3_types[91],  IFC2X3_types[92],
                      IFC2X3_types[93],  IFC2X3_types[94],  IFC2X3_types[95],
                      IFC2X3_types[96],  IFC2X3_types[97],  IFC2X3_types[98],
                      IFC2X3_types[99],  IFC2X3_types[100], IFC2X3_types[101],
                      IFC2X3_types[102], IFC2X3_types[103], IFC2X3_types[104],
                      IFC2X3_types[105], IFC2X3_types[106], IFC2X3_types[107],
                      IFC2X3_types[108], IFC2X3_types[109], IFC2X3_types[110],
                      IFC2X3_types[111], IFC2X3_types[112], IFC2X3_types[113],
                      IFC2X3_types[114], IFC2X3_types[115], IFC2X3_types[116],
                      IFC2X3_types[117], IFC2X3_types[118], IFC2X3_types[119],
                      IFC2X3_types[120], IFC2X3_types[121], IFC2X3_types[122],
                      IFC2X3_types[123], IFC2X3_types[124], IFC2X3_types[125],
                      IFC2X3_types[126], IFC2X3_types[127], IFC2X3_types[128],
                      IFC2X3_types[129], IFC2X3_types[130], IFC2X3_types[131],
                      IFC2X3_types[132], IFC2X3_types[133], IFC2X3_types[134],
                      IFC2X3_types[135], IFC2X3_types[136], IFC2X3_types[137],
                      IFC2X3_types[138], IFC2X3_types[139], IFC2X3_types[140],
                      IFC2X3_types[141], IFC2X3_types[142], IFC2X3_types[143],
                      IFC2X3_types[144], IFC2X3_types[145], IFC2X3_types[146],
                      IFC2X3_types[147], IFC2X3_types[148], IFC2X3_types[149],
                      IFC2X3_types[150], IFC2X3_types[151], IFC2X3_types[152],
                      IFC2X3_types[153], IFC2X3_types[154], IFC2X3_types[155],
                      IFC2X3_types[156], IFC2X3_types[157], IFC2X3_types[158],
                      IFC2X3_types[159], IFC2X3_types[160], IFC2X3_types[161],
                      IFC2X3_types[162], IFC2X3_types[163], IFC2X3_types[164],
                      IFC2X3_types[165], IFC2X3_types[166], IFC2X3_types[167],
                      IFC2X3_types[168], IFC2X3_types[169], IFC2X3_types[170],
                      IFC2X3_types[171], IFC2X3_types[172], IFC2X3_types[173],
                      IFC2X3_types[174], IFC2X3_types[175], IFC2X3_types[176],
                      IFC2X3_types[177], IFC2X3_types[178], IFC2X3_types[179],
                      IFC2X3_types[180], IFC2X3_types[181], IFC2X3_types[182],
                      IFC2X3_types[183], IFC2X3_types[184], IFC2X3_types[185],
                      IFC2X3_types[186], IFC2X3_types[187], IFC2X3_types[188],
                      IFC2X3_types[189], IFC2X3_types[190], IFC2X3_types[191],
                      IFC2X3_types[192], IFC2X3_types[193], IFC2X3_types[194],
                      IFC2X3_types[195], IFC2X3_types[196], IFC2X3_types[197],
                      IFC2X3_types[198], IFC2X3_types[199], IFC2X3_types[200],
                      IFC2X3_types[201], IFC2X3_types[202], IFC2X3_types[203],
                      IFC2X3_types[204], IFC2X3_types[205], IFC2X3_types[206],
                      IFC2X3_types[207], IFC2X3_types[208], IFC2X3_types[209],
                      IFC2X3_types[210], IFC2X3_types[211], IFC2X3_types[212],
                      IFC2X3_types[213], IFC2X3_types[214], IFC2X3_types[215],
                      IFC2X3_types[216], IFC2X3_types[217], IFC2X3_types[218],
                      IFC2X3_types[219], IFC2X3_types[220], IFC2X3_types[221],
                      IFC2X3_types[222], IFC2X3_types[223], IFC2X3_types[224],
                      IFC2X3_types[225], IFC2X3_types[226], IFC2X3_types[227],
                      IFC2X3_types[228], IFC2X3_types[229], IFC2X3_types[230],
                      IFC2X3_types[231], IFC2X3_types[232], IFC2X3_types[233],
                      IFC2X3_types[234], IFC2X3_types[235], IFC2X3_types[236],
                      IFC2X3_types[237], IFC2X3_types[238], IFC2X3_types[239],
                      IFC2X3_types[240], IFC2X3_types[241], IFC2X3_types[242],
                      IFC2X3_types[243], IFC2X3_types[244], IFC2X3_types[245],
                      IFC2X3_types[246], IFC2X3_types[247], IFC2X3_types[248],
                      IFC2X3_types[249], IFC2X3_types[250], IFC2X3_types[251],
                      IFC2X3_types[252], IFC2X3_types[253], IFC2X3_types[254],
                      IFC2X3_types[255], IFC2X3_types[256], IFC2X3_types[257],
                      IFC2X3_types[258], IFC2X3_types[259], IFC2X3_types[260],
                      IFC2X3_types[261], IFC2X3_types[262], IFC2X3_types[263],
                      IFC2X3_types[264], IFC2X3_types[265], IFC2X3_types[266],
                      IFC2X3_types[267], IFC2X3_types[268], IFC2X3_types[269],
                      IFC2X3_types[270], IFC2X3_types[271], IFC2X3_types[272],
                      IFC2X3_types[273], IFC2X3_types[274], IFC2X3_types[275],
                      IFC2X3_types[276], IFC2X3_types[277], IFC2X3_types[278],
                      IFC2X3_types[279], IFC2X3_types[280], IFC2X3_types[281],
                      IFC2X3_types[282], IFC2X3_types[283], IFC2X3_types[284],
                      IFC2X3_types[285], IFC2X3_types[286], IFC2X3_types[287],
                      IFC2X3_types[288], IFC2X3_types[289], IFC2X3_types[290],
                      IFC2X3_types[291], IFC2X3_types[292], IFC2X3_types[293],
                      IFC2X3_types[294], IFC2X3_types[295], IFC2X3_types[296],
                      IFC2X3_types[297], IFC2X3_types[298], IFC2X3_types[299],
                      IFC2X3_types[300], IFC2X3_types[301], IFC2X3_types[302],
                      IFC2X3_types[303], IFC2X3_types[304], IFC2X3_types[305],
                      IFC2X3_types[306], IFC2X3_types[307], IFC2X3_types[308],
                      IFC2X3_types[309], IFC2X3_types[310], IFC2X3_types[311],
                      IFC2X3_types[312], IFC2X3_types[313], IFC2X3_types[314],
                      IFC2X3_types[315], IFC2X3_types[316], IFC2X3_types[317],
                      IFC2X3_types[318], IFC2X3_types[319], IFC2X3_types[320],
                      IFC2X3_types[321], IFC2X3_types[322], IFC2X3_types[323],
                      IFC2X3_types[324], IFC2X3_types[325], IFC2X3_types[326],
                      IFC2X3_types[327], IFC2X3_types[328], IFC2X3_types[329],
                      IFC2X3_types[330], IFC2X3_types[331], IFC2X3_types[332],
                      IFC2X3_types[333], IFC2X3_types[334], IFC2X3_types[335],
                      IFC2X3_types[336], IFC2X3_types[337], IFC2X3_types[338],
                      IFC2X3_types[339], IFC2X3_types[340], IFC2X3_types[341],
                      IFC2X3_types[342], IFC2X3_types[343], IFC2X3_types[344],
                      IFC2X3_types[345], IFC2X3_types[346], IFC2X3_types[347],
                      IFC2X3_types[348], IFC2X3_types[349], IFC2X3_types[350],
                      IFC2X3_types[351], IFC2X3_types[352], IFC2X3_types[353],
                      IFC2X3_types[354], IFC2X3_types[355], IFC2X3_types[356],
                      IFC2X3_types[357], IFC2X3_types[358], IFC2X3_types[359],
                      IFC2X3_types[360], IFC2X3_types[361], IFC2X3_types[362],
                      IFC2X3_types[363], IFC2X3_types[364], IFC2X3_types[365],
                      IFC2X3_types[366], IFC2X3_types[367], IFC2X3_types[368],
                      IFC2X3_types[369], IFC2X3_types[370], IFC2X3_types[371],
                      IFC2X3_types[372], IFC2X3_types[373], IFC2X3_types[374],
                      IFC2X3_types[375], IFC2X3_types[376], IFC2X3_types[377],
                      IFC2X3_types[378], IFC2X3_types[379], IFC2X3_types[380],
                      IFC2X3_types[381], IFC2X3_types[382], IFC2X3_types[383],
                      IFC2X3_types[384], IFC2X3_types[385], IFC2X3_types[386],
                      IFC2X3_types[387], IFC2X3_types[388], IFC2X3_types[389],
                      IFC2X3_types[390], IFC2X3_types[391], IFC2X3_types[392],
                      IFC2X3_types[393], IFC2X3_types[394], IFC2X3_types[395],
                      IFC2X3_types[396], IFC2X3_types[397], IFC2X3_types[398],
                      IFC2X3_types[399], IFC2X3_types[400], IFC2X3_types[401],
                      IFC2X3_types[402], IFC2X3_types[403], IFC2X3_types[404],
                      IFC2X3_types[405], IFC2X3_types[406], IFC2X3_types[407],
                      IFC2X3_types[408], IFC2X3_types[409], IFC2X3_types[410],
                      IFC2X3_types[411], IFC2X3_types[412], IFC2X3_types[413],
                      IFC2X3_types[414], IFC2X3_types[415], IFC2X3_types[416],
                      IFC2X3_types[417], IFC2X3_types[418], IFC2X3_types[419],
                      IFC2X3_types[420], IFC2X3_types[421], IFC2X3_types[422],
                      IFC2X3_types[423], IFC2X3_types[424], IFC2X3_types[425],
                      IFC2X3_types[426], IFC2X3_types[427], IFC2X3_types[428],
                      IFC2X3_types[429], IFC2X3_types[430], IFC2X3_types[431],
                      IFC2X3_types[432], IFC2X3_types[433], IFC2X3_types[434],
                      IFC2X3_types[435], IFC2X3_types[436], IFC2X3_types[437],
                      IFC2X3_types[438], IFC2X3_types[439], IFC2X3_types[440],
                      IFC2X3_types[441], IFC2X3_types[442], IFC2X3_types[443],
                      IFC2X3_types[444], IFC2X3_types[445], IFC2X3_types[446],
                      IFC2X3_types[447], IFC2X3_types[448], IFC2X3_types[449],
                      IFC2X3_types[450], IFC2X3_types[451], IFC2X3_types[452],
                      IFC2X3_types[453], IFC2X3_types[454], IFC2X3_types[455],
                      IFC2X3_types[456], IFC2X3_types[457], IFC2X3_types[458],
                      IFC2X3_types[459], IFC2X3_types[460], IFC2X3_types[461],
                      IFC2X3_types[462], IFC2X3_types[463], IFC2X3_types[464],
                      IFC2X3_types[465], IFC2X3_types[466], IFC2X3_types[467],
                      IFC2X3_types[468], IFC2X3_types[469], IFC2X3_types[470],
                      IFC2X3_types[471], IFC2X3_types[472], IFC2X3_types[473],
                      IFC2X3_types[474], IFC2X3_types[475], IFC2X3_types[476],
                      IFC2X3_types[477], IFC2X3_types[478], IFC2X3_types[479],
                      IFC2X3_types[480], IFC2X3_types[481], IFC2X3_types[482],
                      IFC2X3_types[483], IFC2X3_types[484], IFC2X3_types[485],
                      IFC2X3_types[486], IFC2X3_types[487], IFC2X3_types[488],
                      IFC2X3_types[489], IFC2X3_types[490], IFC2X3_types[491],
                      IFC2X3_types[492], IFC2X3_types[493], IFC2X3_types[494],
                      IFC2X3_types[495], IFC2X3_types[496], IFC2X3_types[497],
                      IFC2X3_types[498], IFC2X3_types[499], IFC2X3_types[500],
                      IFC2X3_types[501], IFC2X3_types[502], IFC2X3_types[503],
                      IFC2X3_types[504], IFC2X3_types[505], IFC2X3_types[506],
                      IFC2X3_types[507], IFC2X3_types[508], IFC2X3_types[509],
                      IFC2X3_types[510], IFC2X3_types[511], IFC2X3_types[512],
                      IFC2X3_types[513], IFC2X3_types[514], IFC2X3_types[515],
                      IFC2X3_types[516], IFC2X3_types[517], IFC2X3_types[518],
                      IFC2X3_types[519], IFC2X3_types[520], IFC2X3_types[521],
                      IFC2X3_types[522], IFC2X3_types[523], IFC2X3_types[524],
                      IFC2X3_types[525], IFC2X3_types[526], IFC2X3_types[527],
                      IFC2X3_types[528], IFC2X3_types[529], IFC2X3_types[530],
                      IFC2X3_types[531], IFC2X3_types[532], IFC2X3_types[533],
                      IFC2X3_types[534], IFC2X3_types[535], IFC2X3_types[536],
                      IFC2X3_types[537], IFC2X3_types[538], IFC2X3_types[539],
                      IFC2X3_types[540], IFC2X3_types[541], IFC2X3_types[542],
                      IFC2X3_types[543], IFC2X3_types[544], IFC2X3_types[545],
                      IFC2X3_types[546], IFC2X3_types[547], IFC2X3_types[548],
                      IFC2X3_types[549], IFC2X3_types[550], IFC2X3_types[551],
                      IFC2X3_types[552], IFC2X3_types[553], IFC2X3_types[554],
                      IFC2X3_types[555], IFC2X3_types[556], IFC2X3_types[557],
                      IFC2X3_types[558], IFC2X3_types[559], IFC2X3_types[560],
                      IFC2X3_types[561], IFC2X3_types[562], IFC2X3_types[563],
                      IFC2X3_types[564], IFC2X3_types[565], IFC2X3_types[566],
                      IFC2X3_types[567], IFC2X3_types[568], IFC2X3_types[569],
                      IFC2X3_types[570], IFC2X3_types[571], IFC2X3_types[572],
                      IFC2X3_types[573], IFC2X3_types[574], IFC2X3_types[575],
                      IFC2X3_types[576], IFC2X3_types[577], IFC2X3_types[578],
                      IFC2X3_types[579], IFC2X3_types[580], IFC2X3_types[581],
                      IFC2X3_types[582], IFC2X3_types[583], IFC2X3_types[584],
                      IFC2X3_types[585], IFC2X3_types[586], IFC2X3_types[587],
                      IFC2X3_types[588], IFC2X3_types[589], IFC2X3_types[590],
                      IFC2X3_types[591], IFC2X3_types[592], IFC2X3_types[593],
                      IFC2X3_types[594], IFC2X3_types[595], IFC2X3_types[596],
                      IFC2X3_types[597], IFC2X3_types[598], IFC2X3_types[599],
                      IFC2X3_types[600], IFC2X3_types[601], IFC2X3_types[602],
                      IFC2X3_types[603], IFC2X3_types[604], IFC2X3_types[605],
                      IFC2X3_types[606], IFC2X3_types[607], IFC2X3_types[608],
                      IFC2X3_types[609], IFC2X3_types[610], IFC2X3_types[611],
                      IFC2X3_types[612], IFC2X3_types[613], IFC2X3_types[614],
                      IFC2X3_types[615], IFC2X3_types[616], IFC2X3_types[617],
                      IFC2X3_types[618], IFC2X3_types[619], IFC2X3_types[620],
                      IFC2X3_types[621], IFC2X3_types[622], IFC2X3_types[623],
                      IFC2X3_types[624], IFC2X3_types[625], IFC2X3_types[626],
                      IFC2X3_types[627], IFC2X3_types[628], IFC2X3_types[629],
                      IFC2X3_types[630], IFC2X3_types[631], IFC2X3_types[632],
                      IFC2X3_types[633], IFC2X3_types[634], IFC2X3_types[635],
                      IFC2X3_types[636], IFC2X3_types[637], IFC2X3_types[638],
                      IFC2X3_types[639], IFC2X3_types[640], IFC2X3_types[641],
                      IFC2X3_types[642], IFC2X3_types[643], IFC2X3_types[644],
                      IFC2X3_types[645], IFC2X3_types[646], IFC2X3_types[647],
                      IFC2X3_types[648], IFC2X3_types[649], IFC2X3_types[650],
                      IFC2X3_types[651], IFC2X3_types[652], IFC2X3_types[653],
                      IFC2X3_types[654], IFC2X3_types[655], IFC2X3_types[656],
                      IFC2X3_types[657], IFC2X3_types[658], IFC2X3_types[659],
                      IFC2X3_types[660], IFC2X3_types[661], IFC2X3_types[662],
                      IFC2X3_types[663], IFC2X3_types[664], IFC2X3_types[665],
                      IFC2X3_types[666], IFC2X3_types[667], IFC2X3_types[668],
                      IFC2X3_types[669], IFC2X3_types[670], IFC2X3_types[671],
                      IFC2X3_types[672], IFC2X3_types[673], IFC2X3_types[674],
                      IFC2X3_types[675], IFC2X3_types[676], IFC2X3_types[677],
                      IFC2X3_types[678], IFC2X3_types[679], IFC2X3_types[680],
                      IFC2X3_types[681], IFC2X3_types[682], IFC2X3_types[683],
                      IFC2X3_types[684], IFC2X3_types[685], IFC2X3_types[686],
                      IFC2X3_types[687], IFC2X3_types[688], IFC2X3_types[689],
                      IFC2X3_types[690], IFC2X3_types[691], IFC2X3_types[692],
                      IFC2X3_types[693], IFC2X3_types[694], IFC2X3_types[695],
                      IFC2X3_types[696], IFC2X3_types[697], IFC2X3_types[698],
                      IFC2X3_types[699], IFC2X3_types[700], IFC2X3_types[701],
                      IFC2X3_types[702], IFC2X3_types[703], IFC2X3_types[704],
                      IFC2X3_types[705], IFC2X3_types[706], IFC2X3_types[707],
                      IFC2X3_types[708], IFC2X3_types[709], IFC2X3_types[710],
                      IFC2X3_types[711], IFC2X3_types[712], IFC2X3_types[713],
                      IFC2X3_types[714], IFC2X3_types[715], IFC2X3_types[716],
                      IFC2X3_types[717], IFC2X3_types[718], IFC2X3_types[719],
                      IFC2X3_types[720], IFC2X3_types[721], IFC2X3_types[722],
                      IFC2X3_types[723], IFC2X3_types[724], IFC2X3_types[725],
                      IFC2X3_types[726], IFC2X3_types[727], IFC2X3_types[728],
                      IFC2X3_types[729], IFC2X3_types[730], IFC2X3_types[731],
                      IFC2X3_types[732], IFC2X3_types[733], IFC2X3_types[734],
                      IFC2X3_types[735], IFC2X3_types[736], IFC2X3_types[737],
                      IFC2X3_types[738], IFC2X3_types[739], IFC2X3_types[740],
                      IFC2X3_types[741], IFC2X3_types[742], IFC2X3_types[743],
                      IFC2X3_types[744], IFC2X3_types[745], IFC2X3_types[746],
                      IFC2X3_types[747], IFC2X3_types[748], IFC2X3_types[749],
                      IFC2X3_types[750], IFC2X3_types[751], IFC2X3_types[752],
                      IFC2X3_types[753], IFC2X3_types[754], IFC2X3_types[755],
                      IFC2X3_types[756], IFC2X3_types[757], IFC2X3_types[758],
                      IFC2X3_types[759], IFC2X3_types[760], IFC2X3_types[761],
                      IFC2X3_types[762], IFC2X3_types[763], IFC2X3_types[764],
                      IFC2X3_types[765], IFC2X3_types[766], IFC2X3_types[767],
                      IFC2X3_types[768], IFC2X3_types[769], IFC2X3_types[770],
                      IFC2X3_types[771], IFC2X3_types[772], IFC2X3_types[773],
                      IFC2X3_types[774], IFC2X3_types[775], IFC2X3_types[776],
                      IFC2X3_types[777], IFC2X3_types[778], IFC2X3_types[779],
                      IFC2X3_types[780], IFC2X3_types[781], IFC2X3_types[782],
                      IFC2X3_types[783], IFC2X3_types[784], IFC2X3_types[785],
                      IFC2X3_types[786], IFC2X3_types[787], IFC2X3_types[788],
                      IFC2X3_types[789], IFC2X3_types[790], IFC2X3_types[791],
                      IFC2X3_types[792], IFC2X3_types[793], IFC2X3_types[794],
                      IFC2X3_types[795], IFC2X3_types[796], IFC2X3_types[797],
                      IFC2X3_types[798], IFC2X3_types[799], IFC2X3_types[800],
                      IFC2X3_types[801], IFC2X3_types[802], IFC2X3_types[803],
                      IFC2X3_types[804], IFC2X3_types[805], IFC2X3_types[806],
                      IFC2X3_types[807], IFC2X3_types[808], IFC2X3_types[809],
                      IFC2X3_types[810], IFC2X3_types[811], IFC2X3_types[812],
                      IFC2X3_types[813], IFC2X3_types[814], IFC2X3_types[815],
                      IFC2X3_types[816], IFC2X3_types[817], IFC2X3_types[818],
                      IFC2X3_types[819], IFC2X3_types[820], IFC2X3_types[821],
                      IFC2X3_types[822], IFC2X3_types[823], IFC2X3_types[824],
                      IFC2X3_types[825], IFC2X3_types[826], IFC2X3_types[827],
                      IFC2X3_types[828], IFC2X3_types[829], IFC2X3_types[830],
                      IFC2X3_types[831], IFC2X3_types[832], IFC2X3_types[833],
                      IFC2X3_types[834], IFC2X3_types[835], IFC2X3_types[836],
                      IFC2X3_types[837], IFC2X3_types[838], IFC2X3_types[839],
                      IFC2X3_types[840], IFC2X3_types[841], IFC2X3_types[842],
                      IFC2X3_types[843], IFC2X3_types[844], IFC2X3_types[845],
                      IFC2X3_types[846], IFC2X3_types[847], IFC2X3_types[848],
                      IFC2X3_types[849], IFC2X3_types[850], IFC2X3_types[851],
                      IFC2X3_types[852], IFC2X3_types[853], IFC2X3_types[854],
                      IFC2X3_types[855], IFC2X3_types[856], IFC2X3_types[857],
                      IFC2X3_types[858], IFC2X3_types[859], IFC2X3_types[860],
                      IFC2X3_types[861], IFC2X3_types[862], IFC2X3_types[863],
                      IFC2X3_types[864], IFC2X3_types[865], IFC2X3_types[866],
                      IFC2X3_types[867], IFC2X3_types[868], IFC2X3_types[869],
                      IFC2X3_types[870], IFC2X3_types[871], IFC2X3_types[872],
                      IFC2X3_types[873], IFC2X3_types[874], IFC2X3_types[875],
                      IFC2X3_types[876], IFC2X3_types[877], IFC2X3_types[878],
                      IFC2X3_types[879], IFC2X3_types[880], IFC2X3_types[881],
                      IFC2X3_types[882], IFC2X3_types[883], IFC2X3_types[884],
                      IFC2X3_types[885], IFC2X3_types[886], IFC2X3_types[887],
                      IFC2X3_types[888], IFC2X3_types[889], IFC2X3_types[890],
                      IFC2X3_types[891], IFC2X3_types[892], IFC2X3_types[893],
                      IFC2X3_types[894], IFC2X3_types[895], IFC2X3_types[896],
                      IFC2X3_types[897], IFC2X3_types[898], IFC2X3_types[899],
                      IFC2X3_types[900], IFC2X3_types[901], IFC2X3_types[902],
                      IFC2X3_types[903], IFC2X3_types[904], IFC2X3_types[905],
                      IFC2X3_types[906], IFC2X3_types[907], IFC2X3_types[908],
                      IFC2X3_types[909], IFC2X3_types[910], IFC2X3_types[911],
                      IFC2X3_types[912], IFC2X3_types[913], IFC2X3_types[914],
                      IFC2X3_types[915], IFC2X3_types[916], IFC2X3_types[917],
                      IFC2X3_types[918], IFC2X3_types[919], IFC2X3_types[920],
                      IFC2X3_types[921], IFC2X3_types[922], IFC2X3_types[923],
                      IFC2X3_types[924], IFC2X3_types[925], IFC2X3_types[926],
                      IFC2X3_types[927], IFC2X3_types[928], IFC2X3_types[929],
                      IFC2X3_types[930], IFC2X3_types[931], IFC2X3_types[932],
                      IFC2X3_types[933], IFC2X3_types[934], IFC2X3_types[935],
                      IFC2X3_types[936], IFC2X3_types[937], IFC2X3_types[938],
                      IFC2X3_types[939], IFC2X3_types[940], IFC2X3_types[941],
                      IFC2X3_types[942], IFC2X3_types[943], IFC2X3_types[944],
                      IFC2X3_types[945], IFC2X3_types[946], IFC2X3_types[947],
                      IFC2X3_types[948], IFC2X3_types[949], IFC2X3_types[950],
                      IFC2X3_types[951], IFC2X3_types[952], IFC2X3_types[953],
                      IFC2X3_types[954], IFC2X3_types[955], IFC2X3_types[956],
                      IFC2X3_types[957], IFC2X3_types[958], IFC2X3_types[959],
                      IFC2X3_types[960], IFC2X3_types[961], IFC2X3_types[962],
                      IFC2X3_types[963], IFC2X3_types[964], IFC2X3_types[965],
                      IFC2X3_types[966], IFC2X3_types[967], IFC2X3_types[968],
                      IFC2X3_types[969], IFC2X3_types[970], IFC2X3_types[971],
                      IFC2X3_types[972], IFC2X3_types[973], IFC2X3_types[974],
                      IFC2X3_types[975], IFC2X3_types[976], IFC2X3_types[977],
                      IFC2X3_types[978], IFC2X3_types[979]},
      new IFC2X3_instance_factory());
}
static std::unique_ptr<schema_definition> schema;

void Ifc2x3::clear_schema() { schema.reset(); }

const schema_definition &Ifc2x3::get_schema() {
  if (!schema) {
    schema.reset(IFC2X3_populate_schema());
  }
  return *schema;
}
