#include <ifcparse/Ifc4x1.h>
#include <ifcparse/IfcSchema.h>
#include <string>

using namespace std::string_literals;
using namespace IfcParse;

declaration *IFC4X1_types[1201] = {nullptr};

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
    "IfcAlignmentTypeEnum"s,
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
    "IfcReferentTypeEnum"s,
    "KILOPOINT"s,
    "MILEPOINT"s,
    "STATION"s,
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
    "IfcTransitionCurveType"s,
    "BIQUADRATICPARABOLA"s,
    "BLOSSCURVE"s,
    "CLOTHOIDCURVE"s,
    "COSINECURVE"s,
    "CUBICPARABOLA"s,
    "SINECURVE"s,
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
    "IfcLinearPlacement"s,
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
    "IfcOrientationExpression"s,
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
    "IfcAlignment2DHorizontal"s,
    "IfcAlignment2DSegment"s,
    "IfcAlignment2DVertical"s,
    "IfcAlignment2DVerticalSegment"s,
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
    "IfcDistanceExpression"s,
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
    "IfcOffsetCurve"s,
    "IfcOffsetCurve2D"s,
    "IfcOffsetCurve3D"s,
    "IfcOffsetCurveByDistances"s,
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
    "IfcSectionedSolid"s,
    "IfcSectionedSolidHorizontal"s,
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
    "IfcTriangulatedIrregularNetwork"s,
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
    "IfcAlignment2DHorizontalSegment"s,
    "IfcAlignment2DVerSegCircularArc"s,
    "IfcAlignment2DVerSegLine"s,
    "IfcAlignment2DVerSegParabolicArc"s,
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
    "IfcCurveSegment2D"s,
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
    "IfcLineSegment2D"s,
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
    "IfcPositioningElement"s,
    "IfcProcedure"s,
    "IfcProjectOrder"s,
    "IfcProjectionElement"s,
    "IfcProtectiveDeviceType"s,
    "IfcPumpType"s,
    "IfcRailingType"s,
    "IfcRampFlightType"s,
    "IfcRampType"s,
    "IfcRationalBSplineSurfaceWithKnots"s,
    "IfcReferent"s,
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
    "IfcTransitionCurveSegment2D"s,
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
    "IfcAlignmentCurve"s,
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
    "IfcCircularArcSegment2D"s,
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
    "IfcGrid"s,
    "IfcHeatExchanger"s,
    "IfcHumidifier"s,
    "IfcInterceptor"s,
    "IfcJunctionBox"s,
    "IfcLamp"s,
    "IfcLightFixture"s,
    "IfcLinearPositioningElement"s,
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
    "IfcAlignment"s,
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
    "StartDistAlong"s,
    "Segments"s,
    "CurveGeometry"s,
    "TangentialContinuity"s,
    "StartTag"s,
    "EndTag"s,
    "Radius"s,
    "IsConvex"s,
    "ParabolaConstant"s,
    "HorizontalLength"s,
    "StartHeight"s,
    "StartGradient"s,
    "Horizontal"s,
    "Vertical"s,
    "Tag"s,
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
    "TagList"s,
    "Axis1"s,
    "Axis2"s,
    "LocalOrigin"s,
    "Scale"s,
    "Scale2"s,
    "Axis3"s,
    "Scale3"s,
    "Thickness"s,
    "IsCCW"s,
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
    "StartPoint"s,
    "StartDirection"s,
    "SegmentLength"s,
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
    "DistanceAlong"s,
    "OffsetLateral"s,
    "OffsetVertical"s,
    "OffsetLongitudinal"s,
    "AlongHorizontal"s,
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
    "Distance"s,
    "CartesianPosition"s,
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
    "Roles"s,
    "Addresses"s,
    "RelatingOrganization"s,
    "RelatedOrganizations"s,
    "LateralAxisDirection"s,
    "VerticalAxisDirection"s,
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
    "RestartDistance"s,
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
    "CrossSections"s,
    "CrossSectionPositions"s,
    "FixedAxisVertical"s,
    "SpineCurve"s,
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
    "StartRadius"s,
    "EndRadius"s,
    "IsStartRadiusCCW"s,
    "IsEndRadiusCCW"s,
    "TransitionCurveType"s,
    "BottomXDim"s,
    "TopXDim"s,
    "TopXOffset"s,
    "Normals"s,
    "Flags"s,
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
    "ToAlignmentCurve"s,
    "ToHorizontal"s,
    "ToVertical"s,
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
    "IFC4X1"s};

class IFC4X1_instance_factory : public IfcParse::instance_factory {
  virtual IfcUtil::IfcBaseClass *
  operator()(const IfcParse::declaration *decl,
             IfcEntityInstanceData &&data) const {
    switch (decl->index_in_schema()) {
    case 0:
      return new ::Ifc4x1::IfcAbsorbedDoseMeasure(std::move(data));
    case 1:
      return new ::Ifc4x1::IfcAccelerationMeasure(std::move(data));
    case 2:
      return new ::Ifc4x1::IfcActionRequest(std::move(data));
    case 3:
      return new ::Ifc4x1::IfcActionRequestTypeEnum(std::move(data));
    case 4:
      return new ::Ifc4x1::IfcActionSourceTypeEnum(std::move(data));
    case 5:
      return new ::Ifc4x1::IfcActionTypeEnum(std::move(data));
    case 6:
      return new ::Ifc4x1::IfcActor(std::move(data));
    case 7:
      return new ::Ifc4x1::IfcActorRole(std::move(data));
    case 9:
      return new ::Ifc4x1::IfcActuator(std::move(data));
    case 10:
      return new ::Ifc4x1::IfcActuatorType(std::move(data));
    case 11:
      return new ::Ifc4x1::IfcActuatorTypeEnum(std::move(data));
    case 12:
      return new ::Ifc4x1::IfcAddress(std::move(data));
    case 13:
      return new ::Ifc4x1::IfcAddressTypeEnum(std::move(data));
    case 14:
      return new ::Ifc4x1::IfcAdvancedBrep(std::move(data));
    case 15:
      return new ::Ifc4x1::IfcAdvancedBrepWithVoids(std::move(data));
    case 16:
      return new ::Ifc4x1::IfcAdvancedFace(std::move(data));
    case 17:
      return new ::Ifc4x1::IfcAirTerminal(std::move(data));
    case 18:
      return new ::Ifc4x1::IfcAirTerminalBox(std::move(data));
    case 19:
      return new ::Ifc4x1::IfcAirTerminalBoxType(std::move(data));
    case 20:
      return new ::Ifc4x1::IfcAirTerminalBoxTypeEnum(std::move(data));
    case 21:
      return new ::Ifc4x1::IfcAirTerminalType(std::move(data));
    case 22:
      return new ::Ifc4x1::IfcAirTerminalTypeEnum(std::move(data));
    case 23:
      return new ::Ifc4x1::IfcAirToAirHeatRecovery(std::move(data));
    case 24:
      return new ::Ifc4x1::IfcAirToAirHeatRecoveryType(std::move(data));
    case 25:
      return new ::Ifc4x1::IfcAirToAirHeatRecoveryTypeEnum(std::move(data));
    case 26:
      return new ::Ifc4x1::IfcAlarm(std::move(data));
    case 27:
      return new ::Ifc4x1::IfcAlarmType(std::move(data));
    case 28:
      return new ::Ifc4x1::IfcAlarmTypeEnum(std::move(data));
    case 29:
      return new ::Ifc4x1::IfcAlignment(std::move(data));
    case 30:
      return new ::Ifc4x1::IfcAlignment2DHorizontal(std::move(data));
    case 31:
      return new ::Ifc4x1::IfcAlignment2DHorizontalSegment(std::move(data));
    case 32:
      return new ::Ifc4x1::IfcAlignment2DSegment(std::move(data));
    case 33:
      return new ::Ifc4x1::IfcAlignment2DVerSegCircularArc(std::move(data));
    case 34:
      return new ::Ifc4x1::IfcAlignment2DVerSegLine(std::move(data));
    case 35:
      return new ::Ifc4x1::IfcAlignment2DVerSegParabolicArc(std::move(data));
    case 36:
      return new ::Ifc4x1::IfcAlignment2DVertical(std::move(data));
    case 37:
      return new ::Ifc4x1::IfcAlignment2DVerticalSegment(std::move(data));
    case 38:
      return new ::Ifc4x1::IfcAlignmentCurve(std::move(data));
    case 39:
      return new ::Ifc4x1::IfcAlignmentTypeEnum(std::move(data));
    case 40:
      return new ::Ifc4x1::IfcAmountOfSubstanceMeasure(std::move(data));
    case 41:
      return new ::Ifc4x1::IfcAnalysisModelTypeEnum(std::move(data));
    case 42:
      return new ::Ifc4x1::IfcAnalysisTheoryTypeEnum(std::move(data));
    case 43:
      return new ::Ifc4x1::IfcAngularVelocityMeasure(std::move(data));
    case 44:
      return new ::Ifc4x1::IfcAnnotation(std::move(data));
    case 45:
      return new ::Ifc4x1::IfcAnnotationFillArea(std::move(data));
    case 46:
      return new ::Ifc4x1::IfcApplication(std::move(data));
    case 47:
      return new ::Ifc4x1::IfcAppliedValue(std::move(data));
    case 49:
      return new ::Ifc4x1::IfcApproval(std::move(data));
    case 50:
      return new ::Ifc4x1::IfcApprovalRelationship(std::move(data));
    case 51:
      return new ::Ifc4x1::IfcArbitraryClosedProfileDef(std::move(data));
    case 52:
      return new ::Ifc4x1::IfcArbitraryOpenProfileDef(std::move(data));
    case 53:
      return new ::Ifc4x1::IfcArbitraryProfileDefWithVoids(std::move(data));
    case 54:
      return new ::Ifc4x1::IfcArcIndex(std::move(data));
    case 55:
      return new ::Ifc4x1::IfcAreaDensityMeasure(std::move(data));
    case 56:
      return new ::Ifc4x1::IfcAreaMeasure(std::move(data));
    case 57:
      return new ::Ifc4x1::IfcArithmeticOperatorEnum(std::move(data));
    case 58:
      return new ::Ifc4x1::IfcAssemblyPlaceEnum(std::move(data));
    case 59:
      return new ::Ifc4x1::IfcAsset(std::move(data));
    case 60:
      return new ::Ifc4x1::IfcAsymmetricIShapeProfileDef(std::move(data));
    case 61:
      return new ::Ifc4x1::IfcAudioVisualAppliance(std::move(data));
    case 62:
      return new ::Ifc4x1::IfcAudioVisualApplianceType(std::move(data));
    case 63:
      return new ::Ifc4x1::IfcAudioVisualApplianceTypeEnum(std::move(data));
    case 64:
      return new ::Ifc4x1::IfcAxis1Placement(std::move(data));
    case 66:
      return new ::Ifc4x1::IfcAxis2Placement2D(std::move(data));
    case 67:
      return new ::Ifc4x1::IfcAxis2Placement3D(std::move(data));
    case 68:
      return new ::Ifc4x1::IfcBeam(std::move(data));
    case 69:
      return new ::Ifc4x1::IfcBeamStandardCase(std::move(data));
    case 70:
      return new ::Ifc4x1::IfcBeamType(std::move(data));
    case 71:
      return new ::Ifc4x1::IfcBeamTypeEnum(std::move(data));
    case 72:
      return new ::Ifc4x1::IfcBenchmarkEnum(std::move(data));
    case 74:
      return new ::Ifc4x1::IfcBinary(std::move(data));
    case 75:
      return new ::Ifc4x1::IfcBlobTexture(std::move(data));
    case 76:
      return new ::Ifc4x1::IfcBlock(std::move(data));
    case 77:
      return new ::Ifc4x1::IfcBoiler(std::move(data));
    case 78:
      return new ::Ifc4x1::IfcBoilerType(std::move(data));
    case 79:
      return new ::Ifc4x1::IfcBoilerTypeEnum(std::move(data));
    case 80:
      return new ::Ifc4x1::IfcBoolean(std::move(data));
    case 81:
      return new ::Ifc4x1::IfcBooleanClippingResult(std::move(data));
    case 83:
      return new ::Ifc4x1::IfcBooleanOperator(std::move(data));
    case 84:
      return new ::Ifc4x1::IfcBooleanResult(std::move(data));
    case 85:
      return new ::Ifc4x1::IfcBoundaryCondition(std::move(data));
    case 86:
      return new ::Ifc4x1::IfcBoundaryCurve(std::move(data));
    case 87:
      return new ::Ifc4x1::IfcBoundaryEdgeCondition(std::move(data));
    case 88:
      return new ::Ifc4x1::IfcBoundaryFaceCondition(std::move(data));
    case 89:
      return new ::Ifc4x1::IfcBoundaryNodeCondition(std::move(data));
    case 90:
      return new ::Ifc4x1::IfcBoundaryNodeConditionWarping(std::move(data));
    case 91:
      return new ::Ifc4x1::IfcBoundedCurve(std::move(data));
    case 92:
      return new ::Ifc4x1::IfcBoundedSurface(std::move(data));
    case 93:
      return new ::Ifc4x1::IfcBoundingBox(std::move(data));
    case 94:
      return new ::Ifc4x1::IfcBoxAlignment(std::move(data));
    case 95:
      return new ::Ifc4x1::IfcBoxedHalfSpace(std::move(data));
    case 96:
      return new ::Ifc4x1::IfcBSplineCurve(std::move(data));
    case 97:
      return new ::Ifc4x1::IfcBSplineCurveForm(std::move(data));
    case 98:
      return new ::Ifc4x1::IfcBSplineCurveWithKnots(std::move(data));
    case 99:
      return new ::Ifc4x1::IfcBSplineSurface(std::move(data));
    case 100:
      return new ::Ifc4x1::IfcBSplineSurfaceForm(std::move(data));
    case 101:
      return new ::Ifc4x1::IfcBSplineSurfaceWithKnots(std::move(data));
    case 102:
      return new ::Ifc4x1::IfcBuilding(std::move(data));
    case 103:
      return new ::Ifc4x1::IfcBuildingElement(std::move(data));
    case 104:
      return new ::Ifc4x1::IfcBuildingElementPart(std::move(data));
    case 105:
      return new ::Ifc4x1::IfcBuildingElementPartType(std::move(data));
    case 106:
      return new ::Ifc4x1::IfcBuildingElementPartTypeEnum(std::move(data));
    case 107:
      return new ::Ifc4x1::IfcBuildingElementProxy(std::move(data));
    case 108:
      return new ::Ifc4x1::IfcBuildingElementProxyType(std::move(data));
    case 109:
      return new ::Ifc4x1::IfcBuildingElementProxyTypeEnum(std::move(data));
    case 110:
      return new ::Ifc4x1::IfcBuildingElementType(std::move(data));
    case 111:
      return new ::Ifc4x1::IfcBuildingStorey(std::move(data));
    case 112:
      return new ::Ifc4x1::IfcBuildingSystem(std::move(data));
    case 113:
      return new ::Ifc4x1::IfcBuildingSystemTypeEnum(std::move(data));
    case 114:
      return new ::Ifc4x1::IfcBurner(std::move(data));
    case 115:
      return new ::Ifc4x1::IfcBurnerType(std::move(data));
    case 116:
      return new ::Ifc4x1::IfcBurnerTypeEnum(std::move(data));
    case 117:
      return new ::Ifc4x1::IfcCableCarrierFitting(std::move(data));
    case 118:
      return new ::Ifc4x1::IfcCableCarrierFittingType(std::move(data));
    case 119:
      return new ::Ifc4x1::IfcCableCarrierFittingTypeEnum(std::move(data));
    case 120:
      return new ::Ifc4x1::IfcCableCarrierSegment(std::move(data));
    case 121:
      return new ::Ifc4x1::IfcCableCarrierSegmentType(std::move(data));
    case 122:
      return new ::Ifc4x1::IfcCableCarrierSegmentTypeEnum(std::move(data));
    case 123:
      return new ::Ifc4x1::IfcCableFitting(std::move(data));
    case 124:
      return new ::Ifc4x1::IfcCableFittingType(std::move(data));
    case 125:
      return new ::Ifc4x1::IfcCableFittingTypeEnum(std::move(data));
    case 126:
      return new ::Ifc4x1::IfcCableSegment(std::move(data));
    case 127:
      return new ::Ifc4x1::IfcCableSegmentType(std::move(data));
    case 128:
      return new ::Ifc4x1::IfcCableSegmentTypeEnum(std::move(data));
    case 129:
      return new ::Ifc4x1::IfcCardinalPointReference(std::move(data));
    case 130:
      return new ::Ifc4x1::IfcCartesianPoint(std::move(data));
    case 131:
      return new ::Ifc4x1::IfcCartesianPointList(std::move(data));
    case 132:
      return new ::Ifc4x1::IfcCartesianPointList2D(std::move(data));
    case 133:
      return new ::Ifc4x1::IfcCartesianPointList3D(std::move(data));
    case 134:
      return new ::Ifc4x1::IfcCartesianTransformationOperator(std::move(data));
    case 135:
      return new ::Ifc4x1::IfcCartesianTransformationOperator2D(
          std::move(data));
    case 136:
      return new ::Ifc4x1::IfcCartesianTransformationOperator2DnonUniform(
          std::move(data));
    case 137:
      return new ::Ifc4x1::IfcCartesianTransformationOperator3D(
          std::move(data));
    case 138:
      return new ::Ifc4x1::IfcCartesianTransformationOperator3DnonUniform(
          std::move(data));
    case 139:
      return new ::Ifc4x1::IfcCenterLineProfileDef(std::move(data));
    case 140:
      return new ::Ifc4x1::IfcChangeActionEnum(std::move(data));
    case 141:
      return new ::Ifc4x1::IfcChiller(std::move(data));
    case 142:
      return new ::Ifc4x1::IfcChillerType(std::move(data));
    case 143:
      return new ::Ifc4x1::IfcChillerTypeEnum(std::move(data));
    case 144:
      return new ::Ifc4x1::IfcChimney(std::move(data));
    case 145:
      return new ::Ifc4x1::IfcChimneyType(std::move(data));
    case 146:
      return new ::Ifc4x1::IfcChimneyTypeEnum(std::move(data));
    case 147:
      return new ::Ifc4x1::IfcCircle(std::move(data));
    case 148:
      return new ::Ifc4x1::IfcCircleHollowProfileDef(std::move(data));
    case 149:
      return new ::Ifc4x1::IfcCircleProfileDef(std::move(data));
    case 150:
      return new ::Ifc4x1::IfcCircularArcSegment2D(std::move(data));
    case 151:
      return new ::Ifc4x1::IfcCivilElement(std::move(data));
    case 152:
      return new ::Ifc4x1::IfcCivilElementType(std::move(data));
    case 153:
      return new ::Ifc4x1::IfcClassification(std::move(data));
    case 154:
      return new ::Ifc4x1::IfcClassificationReference(std::move(data));
    case 157:
      return new ::Ifc4x1::IfcClosedShell(std::move(data));
    case 158:
      return new ::Ifc4x1::IfcCoil(std::move(data));
    case 159:
      return new ::Ifc4x1::IfcCoilType(std::move(data));
    case 160:
      return new ::Ifc4x1::IfcCoilTypeEnum(std::move(data));
    case 163:
      return new ::Ifc4x1::IfcColourRgb(std::move(data));
    case 164:
      return new ::Ifc4x1::IfcColourRgbList(std::move(data));
    case 165:
      return new ::Ifc4x1::IfcColourSpecification(std::move(data));
    case 166:
      return new ::Ifc4x1::IfcColumn(std::move(data));
    case 167:
      return new ::Ifc4x1::IfcColumnStandardCase(std::move(data));
    case 168:
      return new ::Ifc4x1::IfcColumnType(std::move(data));
    case 169:
      return new ::Ifc4x1::IfcColumnTypeEnum(std::move(data));
    case 170:
      return new ::Ifc4x1::IfcCommunicationsAppliance(std::move(data));
    case 171:
      return new ::Ifc4x1::IfcCommunicationsApplianceType(std::move(data));
    case 172:
      return new ::Ifc4x1::IfcCommunicationsApplianceTypeEnum(std::move(data));
    case 173:
      return new ::Ifc4x1::IfcComplexNumber(std::move(data));
    case 174:
      return new ::Ifc4x1::IfcComplexProperty(std::move(data));
    case 175:
      return new ::Ifc4x1::IfcComplexPropertyTemplate(std::move(data));
    case 176:
      return new ::Ifc4x1::IfcComplexPropertyTemplateTypeEnum(std::move(data));
    case 177:
      return new ::Ifc4x1::IfcCompositeCurve(std::move(data));
    case 178:
      return new ::Ifc4x1::IfcCompositeCurveOnSurface(std::move(data));
    case 179:
      return new ::Ifc4x1::IfcCompositeCurveSegment(std::move(data));
    case 180:
      return new ::Ifc4x1::IfcCompositeProfileDef(std::move(data));
    case 181:
      return new ::Ifc4x1::IfcCompoundPlaneAngleMeasure(std::move(data));
    case 182:
      return new ::Ifc4x1::IfcCompressor(std::move(data));
    case 183:
      return new ::Ifc4x1::IfcCompressorType(std::move(data));
    case 184:
      return new ::Ifc4x1::IfcCompressorTypeEnum(std::move(data));
    case 185:
      return new ::Ifc4x1::IfcCondenser(std::move(data));
    case 186:
      return new ::Ifc4x1::IfcCondenserType(std::move(data));
    case 187:
      return new ::Ifc4x1::IfcCondenserTypeEnum(std::move(data));
    case 188:
      return new ::Ifc4x1::IfcConic(std::move(data));
    case 189:
      return new ::Ifc4x1::IfcConnectedFaceSet(std::move(data));
    case 190:
      return new ::Ifc4x1::IfcConnectionCurveGeometry(std::move(data));
    case 191:
      return new ::Ifc4x1::IfcConnectionGeometry(std::move(data));
    case 192:
      return new ::Ifc4x1::IfcConnectionPointEccentricity(std::move(data));
    case 193:
      return new ::Ifc4x1::IfcConnectionPointGeometry(std::move(data));
    case 194:
      return new ::Ifc4x1::IfcConnectionSurfaceGeometry(std::move(data));
    case 195:
      return new ::Ifc4x1::IfcConnectionTypeEnum(std::move(data));
    case 196:
      return new ::Ifc4x1::IfcConnectionVolumeGeometry(std::move(data));
    case 197:
      return new ::Ifc4x1::IfcConstraint(std::move(data));
    case 198:
      return new ::Ifc4x1::IfcConstraintEnum(std::move(data));
    case 199:
      return new ::Ifc4x1::IfcConstructionEquipmentResource(std::move(data));
    case 200:
      return new ::Ifc4x1::IfcConstructionEquipmentResourceType(
          std::move(data));
    case 201:
      return new ::Ifc4x1::IfcConstructionEquipmentResourceTypeEnum(
          std::move(data));
    case 202:
      return new ::Ifc4x1::IfcConstructionMaterialResource(std::move(data));
    case 203:
      return new ::Ifc4x1::IfcConstructionMaterialResourceType(std::move(data));
    case 204:
      return new ::Ifc4x1::IfcConstructionMaterialResourceTypeEnum(
          std::move(data));
    case 205:
      return new ::Ifc4x1::IfcConstructionProductResource(std::move(data));
    case 206:
      return new ::Ifc4x1::IfcConstructionProductResourceType(std::move(data));
    case 207:
      return new ::Ifc4x1::IfcConstructionProductResourceTypeEnum(
          std::move(data));
    case 208:
      return new ::Ifc4x1::IfcConstructionResource(std::move(data));
    case 209:
      return new ::Ifc4x1::IfcConstructionResourceType(std::move(data));
    case 210:
      return new ::Ifc4x1::IfcContext(std::move(data));
    case 211:
      return new ::Ifc4x1::IfcContextDependentMeasure(std::move(data));
    case 212:
      return new ::Ifc4x1::IfcContextDependentUnit(std::move(data));
    case 213:
      return new ::Ifc4x1::IfcControl(std::move(data));
    case 214:
      return new ::Ifc4x1::IfcController(std::move(data));
    case 215:
      return new ::Ifc4x1::IfcControllerType(std::move(data));
    case 216:
      return new ::Ifc4x1::IfcControllerTypeEnum(std::move(data));
    case 217:
      return new ::Ifc4x1::IfcConversionBasedUnit(std::move(data));
    case 218:
      return new ::Ifc4x1::IfcConversionBasedUnitWithOffset(std::move(data));
    case 219:
      return new ::Ifc4x1::IfcCooledBeam(std::move(data));
    case 220:
      return new ::Ifc4x1::IfcCooledBeamType(std::move(data));
    case 221:
      return new ::Ifc4x1::IfcCooledBeamTypeEnum(std::move(data));
    case 222:
      return new ::Ifc4x1::IfcCoolingTower(std::move(data));
    case 223:
      return new ::Ifc4x1::IfcCoolingTowerType(std::move(data));
    case 224:
      return new ::Ifc4x1::IfcCoolingTowerTypeEnum(std::move(data));
    case 225:
      return new ::Ifc4x1::IfcCoordinateOperation(std::move(data));
    case 226:
      return new ::Ifc4x1::IfcCoordinateReferenceSystem(std::move(data));
    case 228:
      return new ::Ifc4x1::IfcCostItem(std::move(data));
    case 229:
      return new ::Ifc4x1::IfcCostItemTypeEnum(std::move(data));
    case 230:
      return new ::Ifc4x1::IfcCostSchedule(std::move(data));
    case 231:
      return new ::Ifc4x1::IfcCostScheduleTypeEnum(std::move(data));
    case 232:
      return new ::Ifc4x1::IfcCostValue(std::move(data));
    case 233:
      return new ::Ifc4x1::IfcCountMeasure(std::move(data));
    case 234:
      return new ::Ifc4x1::IfcCovering(std::move(data));
    case 235:
      return new ::Ifc4x1::IfcCoveringType(std::move(data));
    case 236:
      return new ::Ifc4x1::IfcCoveringTypeEnum(std::move(data));
    case 237:
      return new ::Ifc4x1::IfcCrewResource(std::move(data));
    case 238:
      return new ::Ifc4x1::IfcCrewResourceType(std::move(data));
    case 239:
      return new ::Ifc4x1::IfcCrewResourceTypeEnum(std::move(data));
    case 240:
      return new ::Ifc4x1::IfcCsgPrimitive3D(std::move(data));
    case 242:
      return new ::Ifc4x1::IfcCsgSolid(std::move(data));
    case 243:
      return new ::Ifc4x1::IfcCShapeProfileDef(std::move(data));
    case 244:
      return new ::Ifc4x1::IfcCurrencyRelationship(std::move(data));
    case 245:
      return new ::Ifc4x1::IfcCurtainWall(std::move(data));
    case 246:
      return new ::Ifc4x1::IfcCurtainWallType(std::move(data));
    case 247:
      return new ::Ifc4x1::IfcCurtainWallTypeEnum(std::move(data));
    case 248:
      return new ::Ifc4x1::IfcCurvatureMeasure(std::move(data));
    case 249:
      return new ::Ifc4x1::IfcCurve(std::move(data));
    case 250:
      return new ::Ifc4x1::IfcCurveBoundedPlane(std::move(data));
    case 251:
      return new ::Ifc4x1::IfcCurveBoundedSurface(std::move(data));
    case 253:
      return new ::Ifc4x1::IfcCurveInterpolationEnum(std::move(data));
    case 256:
      return new ::Ifc4x1::IfcCurveSegment2D(std::move(data));
    case 257:
      return new ::Ifc4x1::IfcCurveStyle(std::move(data));
    case 258:
      return new ::Ifc4x1::IfcCurveStyleFont(std::move(data));
    case 259:
      return new ::Ifc4x1::IfcCurveStyleFontAndScaling(std::move(data));
    case 260:
      return new ::Ifc4x1::IfcCurveStyleFontPattern(std::move(data));
    case 262:
      return new ::Ifc4x1::IfcCylindricalSurface(std::move(data));
    case 263:
      return new ::Ifc4x1::IfcDamper(std::move(data));
    case 264:
      return new ::Ifc4x1::IfcDamperType(std::move(data));
    case 265:
      return new ::Ifc4x1::IfcDamperTypeEnum(std::move(data));
    case 266:
      return new ::Ifc4x1::IfcDataOriginEnum(std::move(data));
    case 267:
      return new ::Ifc4x1::IfcDate(std::move(data));
    case 268:
      return new ::Ifc4x1::IfcDateTime(std::move(data));
    case 269:
      return new ::Ifc4x1::IfcDayInMonthNumber(std::move(data));
    case 270:
      return new ::Ifc4x1::IfcDayInWeekNumber(std::move(data));
    case 273:
      return new ::Ifc4x1::IfcDerivedProfileDef(std::move(data));
    case 274:
      return new ::Ifc4x1::IfcDerivedUnit(std::move(data));
    case 275:
      return new ::Ifc4x1::IfcDerivedUnitElement(std::move(data));
    case 276:
      return new ::Ifc4x1::IfcDerivedUnitEnum(std::move(data));
    case 277:
      return new ::Ifc4x1::IfcDescriptiveMeasure(std::move(data));
    case 278:
      return new ::Ifc4x1::IfcDimensionalExponents(std::move(data));
    case 279:
      return new ::Ifc4x1::IfcDimensionCount(std::move(data));
    case 280:
      return new ::Ifc4x1::IfcDirection(std::move(data));
    case 281:
      return new ::Ifc4x1::IfcDirectionSenseEnum(std::move(data));
    case 282:
      return new ::Ifc4x1::IfcDiscreteAccessory(std::move(data));
    case 283:
      return new ::Ifc4x1::IfcDiscreteAccessoryType(std::move(data));
    case 284:
      return new ::Ifc4x1::IfcDiscreteAccessoryTypeEnum(std::move(data));
    case 285:
      return new ::Ifc4x1::IfcDistanceExpression(std::move(data));
    case 286:
      return new ::Ifc4x1::IfcDistributionChamberElement(std::move(data));
    case 287:
      return new ::Ifc4x1::IfcDistributionChamberElementType(std::move(data));
    case 288:
      return new ::Ifc4x1::IfcDistributionChamberElementTypeEnum(
          std::move(data));
    case 289:
      return new ::Ifc4x1::IfcDistributionCircuit(std::move(data));
    case 290:
      return new ::Ifc4x1::IfcDistributionControlElement(std::move(data));
    case 291:
      return new ::Ifc4x1::IfcDistributionControlElementType(std::move(data));
    case 292:
      return new ::Ifc4x1::IfcDistributionElement(std::move(data));
    case 293:
      return new ::Ifc4x1::IfcDistributionElementType(std::move(data));
    case 294:
      return new ::Ifc4x1::IfcDistributionFlowElement(std::move(data));
    case 295:
      return new ::Ifc4x1::IfcDistributionFlowElementType(std::move(data));
    case 296:
      return new ::Ifc4x1::IfcDistributionPort(std::move(data));
    case 297:
      return new ::Ifc4x1::IfcDistributionPortTypeEnum(std::move(data));
    case 298:
      return new ::Ifc4x1::IfcDistributionSystem(std::move(data));
    case 299:
      return new ::Ifc4x1::IfcDistributionSystemEnum(std::move(data));
    case 300:
      return new ::Ifc4x1::IfcDocumentConfidentialityEnum(std::move(data));
    case 301:
      return new ::Ifc4x1::IfcDocumentInformation(std::move(data));
    case 302:
      return new ::Ifc4x1::IfcDocumentInformationRelationship(std::move(data));
    case 303:
      return new ::Ifc4x1::IfcDocumentReference(std::move(data));
    case 305:
      return new ::Ifc4x1::IfcDocumentStatusEnum(std::move(data));
    case 306:
      return new ::Ifc4x1::IfcDoor(std::move(data));
    case 307:
      return new ::Ifc4x1::IfcDoorLiningProperties(std::move(data));
    case 308:
      return new ::Ifc4x1::IfcDoorPanelOperationEnum(std::move(data));
    case 309:
      return new ::Ifc4x1::IfcDoorPanelPositionEnum(std::move(data));
    case 310:
      return new ::Ifc4x1::IfcDoorPanelProperties(std::move(data));
    case 311:
      return new ::Ifc4x1::IfcDoorStandardCase(std::move(data));
    case 312:
      return new ::Ifc4x1::IfcDoorStyle(std::move(data));
    case 313:
      return new ::Ifc4x1::IfcDoorStyleConstructionEnum(std::move(data));
    case 314:
      return new ::Ifc4x1::IfcDoorStyleOperationEnum(std::move(data));
    case 315:
      return new ::Ifc4x1::IfcDoorType(std::move(data));
    case 316:
      return new ::Ifc4x1::IfcDoorTypeEnum(std::move(data));
    case 317:
      return new ::Ifc4x1::IfcDoorTypeOperationEnum(std::move(data));
    case 318:
      return new ::Ifc4x1::IfcDoseEquivalentMeasure(std::move(data));
    case 319:
      return new ::Ifc4x1::IfcDraughtingPreDefinedColour(std::move(data));
    case 320:
      return new ::Ifc4x1::IfcDraughtingPreDefinedCurveFont(std::move(data));
    case 321:
      return new ::Ifc4x1::IfcDuctFitting(std::move(data));
    case 322:
      return new ::Ifc4x1::IfcDuctFittingType(std::move(data));
    case 323:
      return new ::Ifc4x1::IfcDuctFittingTypeEnum(std::move(data));
    case 324:
      return new ::Ifc4x1::IfcDuctSegment(std::move(data));
    case 325:
      return new ::Ifc4x1::IfcDuctSegmentType(std::move(data));
    case 326:
      return new ::Ifc4x1::IfcDuctSegmentTypeEnum(std::move(data));
    case 327:
      return new ::Ifc4x1::IfcDuctSilencer(std::move(data));
    case 328:
      return new ::Ifc4x1::IfcDuctSilencerType(std::move(data));
    case 329:
      return new ::Ifc4x1::IfcDuctSilencerTypeEnum(std::move(data));
    case 330:
      return new ::Ifc4x1::IfcDuration(std::move(data));
    case 331:
      return new ::Ifc4x1::IfcDynamicViscosityMeasure(std::move(data));
    case 332:
      return new ::Ifc4x1::IfcEdge(std::move(data));
    case 333:
      return new ::Ifc4x1::IfcEdgeCurve(std::move(data));
    case 334:
      return new ::Ifc4x1::IfcEdgeLoop(std::move(data));
    case 335:
      return new ::Ifc4x1::IfcElectricAppliance(std::move(data));
    case 336:
      return new ::Ifc4x1::IfcElectricApplianceType(std::move(data));
    case 337:
      return new ::Ifc4x1::IfcElectricApplianceTypeEnum(std::move(data));
    case 338:
      return new ::Ifc4x1::IfcElectricCapacitanceMeasure(std::move(data));
    case 339:
      return new ::Ifc4x1::IfcElectricChargeMeasure(std::move(data));
    case 340:
      return new ::Ifc4x1::IfcElectricConductanceMeasure(std::move(data));
    case 341:
      return new ::Ifc4x1::IfcElectricCurrentMeasure(std::move(data));
    case 342:
      return new ::Ifc4x1::IfcElectricDistributionBoard(std::move(data));
    case 343:
      return new ::Ifc4x1::IfcElectricDistributionBoardType(std::move(data));
    case 344:
      return new ::Ifc4x1::IfcElectricDistributionBoardTypeEnum(
          std::move(data));
    case 345:
      return new ::Ifc4x1::IfcElectricFlowStorageDevice(std::move(data));
    case 346:
      return new ::Ifc4x1::IfcElectricFlowStorageDeviceType(std::move(data));
    case 347:
      return new ::Ifc4x1::IfcElectricFlowStorageDeviceTypeEnum(
          std::move(data));
    case 348:
      return new ::Ifc4x1::IfcElectricGenerator(std::move(data));
    case 349:
      return new ::Ifc4x1::IfcElectricGeneratorType(std::move(data));
    case 350:
      return new ::Ifc4x1::IfcElectricGeneratorTypeEnum(std::move(data));
    case 351:
      return new ::Ifc4x1::IfcElectricMotor(std::move(data));
    case 352:
      return new ::Ifc4x1::IfcElectricMotorType(std::move(data));
    case 353:
      return new ::Ifc4x1::IfcElectricMotorTypeEnum(std::move(data));
    case 354:
      return new ::Ifc4x1::IfcElectricResistanceMeasure(std::move(data));
    case 355:
      return new ::Ifc4x1::IfcElectricTimeControl(std::move(data));
    case 356:
      return new ::Ifc4x1::IfcElectricTimeControlType(std::move(data));
    case 357:
      return new ::Ifc4x1::IfcElectricTimeControlTypeEnum(std::move(data));
    case 358:
      return new ::Ifc4x1::IfcElectricVoltageMeasure(std::move(data));
    case 359:
      return new ::Ifc4x1::IfcElement(std::move(data));
    case 360:
      return new ::Ifc4x1::IfcElementarySurface(std::move(data));
    case 361:
      return new ::Ifc4x1::IfcElementAssembly(std::move(data));
    case 362:
      return new ::Ifc4x1::IfcElementAssemblyType(std::move(data));
    case 363:
      return new ::Ifc4x1::IfcElementAssemblyTypeEnum(std::move(data));
    case 364:
      return new ::Ifc4x1::IfcElementComponent(std::move(data));
    case 365:
      return new ::Ifc4x1::IfcElementComponentType(std::move(data));
    case 366:
      return new ::Ifc4x1::IfcElementCompositionEnum(std::move(data));
    case 367:
      return new ::Ifc4x1::IfcElementQuantity(std::move(data));
    case 368:
      return new ::Ifc4x1::IfcElementType(std::move(data));
    case 369:
      return new ::Ifc4x1::IfcEllipse(std::move(data));
    case 370:
      return new ::Ifc4x1::IfcEllipseProfileDef(std::move(data));
    case 371:
      return new ::Ifc4x1::IfcEnergyConversionDevice(std::move(data));
    case 372:
      return new ::Ifc4x1::IfcEnergyConversionDeviceType(std::move(data));
    case 373:
      return new ::Ifc4x1::IfcEnergyMeasure(std::move(data));
    case 374:
      return new ::Ifc4x1::IfcEngine(std::move(data));
    case 375:
      return new ::Ifc4x1::IfcEngineType(std::move(data));
    case 376:
      return new ::Ifc4x1::IfcEngineTypeEnum(std::move(data));
    case 377:
      return new ::Ifc4x1::IfcEvaporativeCooler(std::move(data));
    case 378:
      return new ::Ifc4x1::IfcEvaporativeCoolerType(std::move(data));
    case 379:
      return new ::Ifc4x1::IfcEvaporativeCoolerTypeEnum(std::move(data));
    case 380:
      return new ::Ifc4x1::IfcEvaporator(std::move(data));
    case 381:
      return new ::Ifc4x1::IfcEvaporatorType(std::move(data));
    case 382:
      return new ::Ifc4x1::IfcEvaporatorTypeEnum(std::move(data));
    case 383:
      return new ::Ifc4x1::IfcEvent(std::move(data));
    case 384:
      return new ::Ifc4x1::IfcEventTime(std::move(data));
    case 385:
      return new ::Ifc4x1::IfcEventTriggerTypeEnum(std::move(data));
    case 386:
      return new ::Ifc4x1::IfcEventType(std::move(data));
    case 387:
      return new ::Ifc4x1::IfcEventTypeEnum(std::move(data));
    case 388:
      return new ::Ifc4x1::IfcExtendedProperties(std::move(data));
    case 389:
      return new ::Ifc4x1::IfcExternalInformation(std::move(data));
    case 390:
      return new ::Ifc4x1::IfcExternallyDefinedHatchStyle(std::move(data));
    case 391:
      return new ::Ifc4x1::IfcExternallyDefinedSurfaceStyle(std::move(data));
    case 392:
      return new ::Ifc4x1::IfcExternallyDefinedTextFont(std::move(data));
    case 393:
      return new ::Ifc4x1::IfcExternalReference(std::move(data));
    case 394:
      return new ::Ifc4x1::IfcExternalReferenceRelationship(std::move(data));
    case 395:
      return new ::Ifc4x1::IfcExternalSpatialElement(std::move(data));
    case 396:
      return new ::Ifc4x1::IfcExternalSpatialElementTypeEnum(std::move(data));
    case 397:
      return new ::Ifc4x1::IfcExternalSpatialStructureElement(std::move(data));
    case 398:
      return new ::Ifc4x1::IfcExtrudedAreaSolid(std::move(data));
    case 399:
      return new ::Ifc4x1::IfcExtrudedAreaSolidTapered(std::move(data));
    case 400:
      return new ::Ifc4x1::IfcFace(std::move(data));
    case 401:
      return new ::Ifc4x1::IfcFaceBasedSurfaceModel(std::move(data));
    case 402:
      return new ::Ifc4x1::IfcFaceBound(std::move(data));
    case 403:
      return new ::Ifc4x1::IfcFaceOuterBound(std::move(data));
    case 404:
      return new ::Ifc4x1::IfcFaceSurface(std::move(data));
    case 405:
      return new ::Ifc4x1::IfcFacetedBrep(std::move(data));
    case 406:
      return new ::Ifc4x1::IfcFacetedBrepWithVoids(std::move(data));
    case 407:
      return new ::Ifc4x1::IfcFailureConnectionCondition(std::move(data));
    case 408:
      return new ::Ifc4x1::IfcFan(std::move(data));
    case 409:
      return new ::Ifc4x1::IfcFanType(std::move(data));
    case 410:
      return new ::Ifc4x1::IfcFanTypeEnum(std::move(data));
    case 411:
      return new ::Ifc4x1::IfcFastener(std::move(data));
    case 412:
      return new ::Ifc4x1::IfcFastenerType(std::move(data));
    case 413:
      return new ::Ifc4x1::IfcFastenerTypeEnum(std::move(data));
    case 414:
      return new ::Ifc4x1::IfcFeatureElement(std::move(data));
    case 415:
      return new ::Ifc4x1::IfcFeatureElementAddition(std::move(data));
    case 416:
      return new ::Ifc4x1::IfcFeatureElementSubtraction(std::move(data));
    case 417:
      return new ::Ifc4x1::IfcFillAreaStyle(std::move(data));
    case 418:
      return new ::Ifc4x1::IfcFillAreaStyleHatching(std::move(data));
    case 419:
      return new ::Ifc4x1::IfcFillAreaStyleTiles(std::move(data));
    case 421:
      return new ::Ifc4x1::IfcFilter(std::move(data));
    case 422:
      return new ::Ifc4x1::IfcFilterType(std::move(data));
    case 423:
      return new ::Ifc4x1::IfcFilterTypeEnum(std::move(data));
    case 424:
      return new ::Ifc4x1::IfcFireSuppressionTerminal(std::move(data));
    case 425:
      return new ::Ifc4x1::IfcFireSuppressionTerminalType(std::move(data));
    case 426:
      return new ::Ifc4x1::IfcFireSuppressionTerminalTypeEnum(std::move(data));
    case 427:
      return new ::Ifc4x1::IfcFixedReferenceSweptAreaSolid(std::move(data));
    case 428:
      return new ::Ifc4x1::IfcFlowController(std::move(data));
    case 429:
      return new ::Ifc4x1::IfcFlowControllerType(std::move(data));
    case 430:
      return new ::Ifc4x1::IfcFlowDirectionEnum(std::move(data));
    case 431:
      return new ::Ifc4x1::IfcFlowFitting(std::move(data));
    case 432:
      return new ::Ifc4x1::IfcFlowFittingType(std::move(data));
    case 433:
      return new ::Ifc4x1::IfcFlowInstrument(std::move(data));
    case 434:
      return new ::Ifc4x1::IfcFlowInstrumentType(std::move(data));
    case 435:
      return new ::Ifc4x1::IfcFlowInstrumentTypeEnum(std::move(data));
    case 436:
      return new ::Ifc4x1::IfcFlowMeter(std::move(data));
    case 437:
      return new ::Ifc4x1::IfcFlowMeterType(std::move(data));
    case 438:
      return new ::Ifc4x1::IfcFlowMeterTypeEnum(std::move(data));
    case 439:
      return new ::Ifc4x1::IfcFlowMovingDevice(std::move(data));
    case 440:
      return new ::Ifc4x1::IfcFlowMovingDeviceType(std::move(data));
    case 441:
      return new ::Ifc4x1::IfcFlowSegment(std::move(data));
    case 442:
      return new ::Ifc4x1::IfcFlowSegmentType(std::move(data));
    case 443:
      return new ::Ifc4x1::IfcFlowStorageDevice(std::move(data));
    case 444:
      return new ::Ifc4x1::IfcFlowStorageDeviceType(std::move(data));
    case 445:
      return new ::Ifc4x1::IfcFlowTerminal(std::move(data));
    case 446:
      return new ::Ifc4x1::IfcFlowTerminalType(std::move(data));
    case 447:
      return new ::Ifc4x1::IfcFlowTreatmentDevice(std::move(data));
    case 448:
      return new ::Ifc4x1::IfcFlowTreatmentDeviceType(std::move(data));
    case 449:
      return new ::Ifc4x1::IfcFontStyle(std::move(data));
    case 450:
      return new ::Ifc4x1::IfcFontVariant(std::move(data));
    case 451:
      return new ::Ifc4x1::IfcFontWeight(std::move(data));
    case 452:
      return new ::Ifc4x1::IfcFooting(std::move(data));
    case 453:
      return new ::Ifc4x1::IfcFootingType(std::move(data));
    case 454:
      return new ::Ifc4x1::IfcFootingTypeEnum(std::move(data));
    case 455:
      return new ::Ifc4x1::IfcForceMeasure(std::move(data));
    case 456:
      return new ::Ifc4x1::IfcFrequencyMeasure(std::move(data));
    case 457:
      return new ::Ifc4x1::IfcFurnishingElement(std::move(data));
    case 458:
      return new ::Ifc4x1::IfcFurnishingElementType(std::move(data));
    case 459:
      return new ::Ifc4x1::IfcFurniture(std::move(data));
    case 460:
      return new ::Ifc4x1::IfcFurnitureType(std::move(data));
    case 461:
      return new ::Ifc4x1::IfcFurnitureTypeEnum(std::move(data));
    case 462:
      return new ::Ifc4x1::IfcGeographicElement(std::move(data));
    case 463:
      return new ::Ifc4x1::IfcGeographicElementType(std::move(data));
    case 464:
      return new ::Ifc4x1::IfcGeographicElementTypeEnum(std::move(data));
    case 465:
      return new ::Ifc4x1::IfcGeometricCurveSet(std::move(data));
    case 466:
      return new ::Ifc4x1::IfcGeometricProjectionEnum(std::move(data));
    case 467:
      return new ::Ifc4x1::IfcGeometricRepresentationContext(std::move(data));
    case 468:
      return new ::Ifc4x1::IfcGeometricRepresentationItem(std::move(data));
    case 469:
      return new ::Ifc4x1::IfcGeometricRepresentationSubContext(
          std::move(data));
    case 470:
      return new ::Ifc4x1::IfcGeometricSet(std::move(data));
    case 472:
      return new ::Ifc4x1::IfcGloballyUniqueId(std::move(data));
    case 473:
      return new ::Ifc4x1::IfcGlobalOrLocalEnum(std::move(data));
    case 474:
      return new ::Ifc4x1::IfcGrid(std::move(data));
    case 475:
      return new ::Ifc4x1::IfcGridAxis(std::move(data));
    case 476:
      return new ::Ifc4x1::IfcGridPlacement(std::move(data));
    case 478:
      return new ::Ifc4x1::IfcGridTypeEnum(std::move(data));
    case 479:
      return new ::Ifc4x1::IfcGroup(std::move(data));
    case 480:
      return new ::Ifc4x1::IfcHalfSpaceSolid(std::move(data));
    case 482:
      return new ::Ifc4x1::IfcHeatExchanger(std::move(data));
    case 483:
      return new ::Ifc4x1::IfcHeatExchangerType(std::move(data));
    case 484:
      return new ::Ifc4x1::IfcHeatExchangerTypeEnum(std::move(data));
    case 485:
      return new ::Ifc4x1::IfcHeatFluxDensityMeasure(std::move(data));
    case 486:
      return new ::Ifc4x1::IfcHeatingValueMeasure(std::move(data));
    case 487:
      return new ::Ifc4x1::IfcHumidifier(std::move(data));
    case 488:
      return new ::Ifc4x1::IfcHumidifierType(std::move(data));
    case 489:
      return new ::Ifc4x1::IfcHumidifierTypeEnum(std::move(data));
    case 490:
      return new ::Ifc4x1::IfcIdentifier(std::move(data));
    case 491:
      return new ::Ifc4x1::IfcIlluminanceMeasure(std::move(data));
    case 492:
      return new ::Ifc4x1::IfcImageTexture(std::move(data));
    case 493:
      return new ::Ifc4x1::IfcIndexedColourMap(std::move(data));
    case 494:
      return new ::Ifc4x1::IfcIndexedPolyCurve(std::move(data));
    case 495:
      return new ::Ifc4x1::IfcIndexedPolygonalFace(std::move(data));
    case 496:
      return new ::Ifc4x1::IfcIndexedPolygonalFaceWithVoids(std::move(data));
    case 497:
      return new ::Ifc4x1::IfcIndexedTextureMap(std::move(data));
    case 498:
      return new ::Ifc4x1::IfcIndexedTriangleTextureMap(std::move(data));
    case 499:
      return new ::Ifc4x1::IfcInductanceMeasure(std::move(data));
    case 500:
      return new ::Ifc4x1::IfcInteger(std::move(data));
    case 501:
      return new ::Ifc4x1::IfcIntegerCountRateMeasure(std::move(data));
    case 502:
      return new ::Ifc4x1::IfcInterceptor(std::move(data));
    case 503:
      return new ::Ifc4x1::IfcInterceptorType(std::move(data));
    case 504:
      return new ::Ifc4x1::IfcInterceptorTypeEnum(std::move(data));
    case 505:
      return new ::Ifc4x1::IfcInternalOrExternalEnum(std::move(data));
    case 506:
      return new ::Ifc4x1::IfcIntersectionCurve(std::move(data));
    case 507:
      return new ::Ifc4x1::IfcInventory(std::move(data));
    case 508:
      return new ::Ifc4x1::IfcInventoryTypeEnum(std::move(data));
    case 509:
      return new ::Ifc4x1::IfcIonConcentrationMeasure(std::move(data));
    case 510:
      return new ::Ifc4x1::IfcIrregularTimeSeries(std::move(data));
    case 511:
      return new ::Ifc4x1::IfcIrregularTimeSeriesValue(std::move(data));
    case 512:
      return new ::Ifc4x1::IfcIShapeProfileDef(std::move(data));
    case 513:
      return new ::Ifc4x1::IfcIsothermalMoistureCapacityMeasure(
          std::move(data));
    case 514:
      return new ::Ifc4x1::IfcJunctionBox(std::move(data));
    case 515:
      return new ::Ifc4x1::IfcJunctionBoxType(std::move(data));
    case 516:
      return new ::Ifc4x1::IfcJunctionBoxTypeEnum(std::move(data));
    case 517:
      return new ::Ifc4x1::IfcKinematicViscosityMeasure(std::move(data));
    case 518:
      return new ::Ifc4x1::IfcKnotType(std::move(data));
    case 519:
      return new ::Ifc4x1::IfcLabel(std::move(data));
    case 520:
      return new ::Ifc4x1::IfcLaborResource(std::move(data));
    case 521:
      return new ::Ifc4x1::IfcLaborResourceType(std::move(data));
    case 522:
      return new ::Ifc4x1::IfcLaborResourceTypeEnum(std::move(data));
    case 523:
      return new ::Ifc4x1::IfcLagTime(std::move(data));
    case 524:
      return new ::Ifc4x1::IfcLamp(std::move(data));
    case 525:
      return new ::Ifc4x1::IfcLampType(std::move(data));
    case 526:
      return new ::Ifc4x1::IfcLampTypeEnum(std::move(data));
    case 527:
      return new ::Ifc4x1::IfcLanguageId(std::move(data));
    case 529:
      return new ::Ifc4x1::IfcLayerSetDirectionEnum(std::move(data));
    case 530:
      return new ::Ifc4x1::IfcLengthMeasure(std::move(data));
    case 531:
      return new ::Ifc4x1::IfcLibraryInformation(std::move(data));
    case 532:
      return new ::Ifc4x1::IfcLibraryReference(std::move(data));
    case 534:
      return new ::Ifc4x1::IfcLightDistributionCurveEnum(std::move(data));
    case 535:
      return new ::Ifc4x1::IfcLightDistributionData(std::move(data));
    case 537:
      return new ::Ifc4x1::IfcLightEmissionSourceEnum(std::move(data));
    case 538:
      return new ::Ifc4x1::IfcLightFixture(std::move(data));
    case 539:
      return new ::Ifc4x1::IfcLightFixtureType(std::move(data));
    case 540:
      return new ::Ifc4x1::IfcLightFixtureTypeEnum(std::move(data));
    case 541:
      return new ::Ifc4x1::IfcLightIntensityDistribution(std::move(data));
    case 542:
      return new ::Ifc4x1::IfcLightSource(std::move(data));
    case 543:
      return new ::Ifc4x1::IfcLightSourceAmbient(std::move(data));
    case 544:
      return new ::Ifc4x1::IfcLightSourceDirectional(std::move(data));
    case 545:
      return new ::Ifc4x1::IfcLightSourceGoniometric(std::move(data));
    case 546:
      return new ::Ifc4x1::IfcLightSourcePositional(std::move(data));
    case 547:
      return new ::Ifc4x1::IfcLightSourceSpot(std::move(data));
    case 548:
      return new ::Ifc4x1::IfcLine(std::move(data));
    case 549:
      return new ::Ifc4x1::IfcLinearForceMeasure(std::move(data));
    case 550:
      return new ::Ifc4x1::IfcLinearMomentMeasure(std::move(data));
    case 551:
      return new ::Ifc4x1::IfcLinearPlacement(std::move(data));
    case 552:
      return new ::Ifc4x1::IfcLinearPositioningElement(std::move(data));
    case 553:
      return new ::Ifc4x1::IfcLinearStiffnessMeasure(std::move(data));
    case 554:
      return new ::Ifc4x1::IfcLinearVelocityMeasure(std::move(data));
    case 555:
      return new ::Ifc4x1::IfcLineIndex(std::move(data));
    case 556:
      return new ::Ifc4x1::IfcLineSegment2D(std::move(data));
    case 557:
      return new ::Ifc4x1::IfcLoadGroupTypeEnum(std::move(data));
    case 558:
      return new ::Ifc4x1::IfcLocalPlacement(std::move(data));
    case 559:
      return new ::Ifc4x1::IfcLogical(std::move(data));
    case 560:
      return new ::Ifc4x1::IfcLogicalOperatorEnum(std::move(data));
    case 561:
      return new ::Ifc4x1::IfcLoop(std::move(data));
    case 562:
      return new ::Ifc4x1::IfcLShapeProfileDef(std::move(data));
    case 563:
      return new ::Ifc4x1::IfcLuminousFluxMeasure(std::move(data));
    case 564:
      return new ::Ifc4x1::IfcLuminousIntensityDistributionMeasure(
          std::move(data));
    case 565:
      return new ::Ifc4x1::IfcLuminousIntensityMeasure(std::move(data));
    case 566:
      return new ::Ifc4x1::IfcMagneticFluxDensityMeasure(std::move(data));
    case 567:
      return new ::Ifc4x1::IfcMagneticFluxMeasure(std::move(data));
    case 568:
      return new ::Ifc4x1::IfcManifoldSolidBrep(std::move(data));
    case 569:
      return new ::Ifc4x1::IfcMapConversion(std::move(data));
    case 570:
      return new ::Ifc4x1::IfcMappedItem(std::move(data));
    case 571:
      return new ::Ifc4x1::IfcMassDensityMeasure(std::move(data));
    case 572:
      return new ::Ifc4x1::IfcMassFlowRateMeasure(std::move(data));
    case 573:
      return new ::Ifc4x1::IfcMassMeasure(std::move(data));
    case 574:
      return new ::Ifc4x1::IfcMassPerLengthMeasure(std::move(data));
    case 575:
      return new ::Ifc4x1::IfcMaterial(std::move(data));
    case 576:
      return new ::Ifc4x1::IfcMaterialClassificationRelationship(
          std::move(data));
    case 577:
      return new ::Ifc4x1::IfcMaterialConstituent(std::move(data));
    case 578:
      return new ::Ifc4x1::IfcMaterialConstituentSet(std::move(data));
    case 579:
      return new ::Ifc4x1::IfcMaterialDefinition(std::move(data));
    case 580:
      return new ::Ifc4x1::IfcMaterialDefinitionRepresentation(std::move(data));
    case 581:
      return new ::Ifc4x1::IfcMaterialLayer(std::move(data));
    case 582:
      return new ::Ifc4x1::IfcMaterialLayerSet(std::move(data));
    case 583:
      return new ::Ifc4x1::IfcMaterialLayerSetUsage(std::move(data));
    case 584:
      return new ::Ifc4x1::IfcMaterialLayerWithOffsets(std::move(data));
    case 585:
      return new ::Ifc4x1::IfcMaterialList(std::move(data));
    case 586:
      return new ::Ifc4x1::IfcMaterialProfile(std::move(data));
    case 587:
      return new ::Ifc4x1::IfcMaterialProfileSet(std::move(data));
    case 588:
      return new ::Ifc4x1::IfcMaterialProfileSetUsage(std::move(data));
    case 589:
      return new ::Ifc4x1::IfcMaterialProfileSetUsageTapering(std::move(data));
    case 590:
      return new ::Ifc4x1::IfcMaterialProfileWithOffsets(std::move(data));
    case 591:
      return new ::Ifc4x1::IfcMaterialProperties(std::move(data));
    case 592:
      return new ::Ifc4x1::IfcMaterialRelationship(std::move(data));
    case 594:
      return new ::Ifc4x1::IfcMaterialUsageDefinition(std::move(data));
    case 596:
      return new ::Ifc4x1::IfcMeasureWithUnit(std::move(data));
    case 597:
      return new ::Ifc4x1::IfcMechanicalFastener(std::move(data));
    case 598:
      return new ::Ifc4x1::IfcMechanicalFastenerType(std::move(data));
    case 599:
      return new ::Ifc4x1::IfcMechanicalFastenerTypeEnum(std::move(data));
    case 600:
      return new ::Ifc4x1::IfcMedicalDevice(std::move(data));
    case 601:
      return new ::Ifc4x1::IfcMedicalDeviceType(std::move(data));
    case 602:
      return new ::Ifc4x1::IfcMedicalDeviceTypeEnum(std::move(data));
    case 603:
      return new ::Ifc4x1::IfcMember(std::move(data));
    case 604:
      return new ::Ifc4x1::IfcMemberStandardCase(std::move(data));
    case 605:
      return new ::Ifc4x1::IfcMemberType(std::move(data));
    case 606:
      return new ::Ifc4x1::IfcMemberTypeEnum(std::move(data));
    case 607:
      return new ::Ifc4x1::IfcMetric(std::move(data));
    case 609:
      return new ::Ifc4x1::IfcMirroredProfileDef(std::move(data));
    case 610:
      return new ::Ifc4x1::IfcModulusOfElasticityMeasure(std::move(data));
    case 611:
      return new ::Ifc4x1::IfcModulusOfLinearSubgradeReactionMeasure(
          std::move(data));
    case 612:
      return new ::Ifc4x1::IfcModulusOfRotationalSubgradeReactionMeasure(
          std::move(data));
    case 614:
      return new ::Ifc4x1::IfcModulusOfSubgradeReactionMeasure(std::move(data));
    case 617:
      return new ::Ifc4x1::IfcMoistureDiffusivityMeasure(std::move(data));
    case 618:
      return new ::Ifc4x1::IfcMolecularWeightMeasure(std::move(data));
    case 619:
      return new ::Ifc4x1::IfcMomentOfInertiaMeasure(std::move(data));
    case 620:
      return new ::Ifc4x1::IfcMonetaryMeasure(std::move(data));
    case 621:
      return new ::Ifc4x1::IfcMonetaryUnit(std::move(data));
    case 622:
      return new ::Ifc4x1::IfcMonthInYearNumber(std::move(data));
    case 623:
      return new ::Ifc4x1::IfcMotorConnection(std::move(data));
    case 624:
      return new ::Ifc4x1::IfcMotorConnectionType(std::move(data));
    case 625:
      return new ::Ifc4x1::IfcMotorConnectionTypeEnum(std::move(data));
    case 626:
      return new ::Ifc4x1::IfcNamedUnit(std::move(data));
    case 627:
      return new ::Ifc4x1::IfcNonNegativeLengthMeasure(std::move(data));
    case 628:
      return new ::Ifc4x1::IfcNormalisedRatioMeasure(std::move(data));
    case 629:
      return new ::Ifc4x1::IfcNullStyle(std::move(data));
    case 630:
      return new ::Ifc4x1::IfcNumericMeasure(std::move(data));
    case 631:
      return new ::Ifc4x1::IfcObject(std::move(data));
    case 632:
      return new ::Ifc4x1::IfcObjectDefinition(std::move(data));
    case 633:
      return new ::Ifc4x1::IfcObjective(std::move(data));
    case 634:
      return new ::Ifc4x1::IfcObjectiveEnum(std::move(data));
    case 635:
      return new ::Ifc4x1::IfcObjectPlacement(std::move(data));
    case 637:
      return new ::Ifc4x1::IfcObjectTypeEnum(std::move(data));
    case 638:
      return new ::Ifc4x1::IfcOccupant(std::move(data));
    case 639:
      return new ::Ifc4x1::IfcOccupantTypeEnum(std::move(data));
    case 640:
      return new ::Ifc4x1::IfcOffsetCurve(std::move(data));
    case 641:
      return new ::Ifc4x1::IfcOffsetCurve2D(std::move(data));
    case 642:
      return new ::Ifc4x1::IfcOffsetCurve3D(std::move(data));
    case 643:
      return new ::Ifc4x1::IfcOffsetCurveByDistances(std::move(data));
    case 644:
      return new ::Ifc4x1::IfcOpeningElement(std::move(data));
    case 645:
      return new ::Ifc4x1::IfcOpeningElementTypeEnum(std::move(data));
    case 646:
      return new ::Ifc4x1::IfcOpeningStandardCase(std::move(data));
    case 647:
      return new ::Ifc4x1::IfcOpenShell(std::move(data));
    case 648:
      return new ::Ifc4x1::IfcOrganization(std::move(data));
    case 649:
      return new ::Ifc4x1::IfcOrganizationRelationship(std::move(data));
    case 650:
      return new ::Ifc4x1::IfcOrientationExpression(std::move(data));
    case 651:
      return new ::Ifc4x1::IfcOrientedEdge(std::move(data));
    case 652:
      return new ::Ifc4x1::IfcOuterBoundaryCurve(std::move(data));
    case 653:
      return new ::Ifc4x1::IfcOutlet(std::move(data));
    case 654:
      return new ::Ifc4x1::IfcOutletType(std::move(data));
    case 655:
      return new ::Ifc4x1::IfcOutletTypeEnum(std::move(data));
    case 656:
      return new ::Ifc4x1::IfcOwnerHistory(std::move(data));
    case 657:
      return new ::Ifc4x1::IfcParameterizedProfileDef(std::move(data));
    case 658:
      return new ::Ifc4x1::IfcParameterValue(std::move(data));
    case 659:
      return new ::Ifc4x1::IfcPath(std::move(data));
    case 660:
      return new ::Ifc4x1::IfcPcurve(std::move(data));
    case 661:
      return new ::Ifc4x1::IfcPerformanceHistory(std::move(data));
    case 662:
      return new ::Ifc4x1::IfcPerformanceHistoryTypeEnum(std::move(data));
    case 663:
      return new ::Ifc4x1::IfcPermeableCoveringOperationEnum(std::move(data));
    case 664:
      return new ::Ifc4x1::IfcPermeableCoveringProperties(std::move(data));
    case 665:
      return new ::Ifc4x1::IfcPermit(std::move(data));
    case 666:
      return new ::Ifc4x1::IfcPermitTypeEnum(std::move(data));
    case 667:
      return new ::Ifc4x1::IfcPerson(std::move(data));
    case 668:
      return new ::Ifc4x1::IfcPersonAndOrganization(std::move(data));
    case 669:
      return new ::Ifc4x1::IfcPHMeasure(std::move(data));
    case 670:
      return new ::Ifc4x1::IfcPhysicalComplexQuantity(std::move(data));
    case 671:
      return new ::Ifc4x1::IfcPhysicalOrVirtualEnum(std::move(data));
    case 672:
      return new ::Ifc4x1::IfcPhysicalQuantity(std::move(data));
    case 673:
      return new ::Ifc4x1::IfcPhysicalSimpleQuantity(std::move(data));
    case 674:
      return new ::Ifc4x1::IfcPile(std::move(data));
    case 675:
      return new ::Ifc4x1::IfcPileConstructionEnum(std::move(data));
    case 676:
      return new ::Ifc4x1::IfcPileType(std::move(data));
    case 677:
      return new ::Ifc4x1::IfcPileTypeEnum(std::move(data));
    case 678:
      return new ::Ifc4x1::IfcPipeFitting(std::move(data));
    case 679:
      return new ::Ifc4x1::IfcPipeFittingType(std::move(data));
    case 680:
      return new ::Ifc4x1::IfcPipeFittingTypeEnum(std::move(data));
    case 681:
      return new ::Ifc4x1::IfcPipeSegment(std::move(data));
    case 682:
      return new ::Ifc4x1::IfcPipeSegmentType(std::move(data));
    case 683:
      return new ::Ifc4x1::IfcPipeSegmentTypeEnum(std::move(data));
    case 684:
      return new ::Ifc4x1::IfcPixelTexture(std::move(data));
    case 685:
      return new ::Ifc4x1::IfcPlacement(std::move(data));
    case 686:
      return new ::Ifc4x1::IfcPlanarBox(std::move(data));
    case 687:
      return new ::Ifc4x1::IfcPlanarExtent(std::move(data));
    case 688:
      return new ::Ifc4x1::IfcPlanarForceMeasure(std::move(data));
    case 689:
      return new ::Ifc4x1::IfcPlane(std::move(data));
    case 690:
      return new ::Ifc4x1::IfcPlaneAngleMeasure(std::move(data));
    case 691:
      return new ::Ifc4x1::IfcPlate(std::move(data));
    case 692:
      return new ::Ifc4x1::IfcPlateStandardCase(std::move(data));
    case 693:
      return new ::Ifc4x1::IfcPlateType(std::move(data));
    case 694:
      return new ::Ifc4x1::IfcPlateTypeEnum(std::move(data));
    case 695:
      return new ::Ifc4x1::IfcPoint(std::move(data));
    case 696:
      return new ::Ifc4x1::IfcPointOnCurve(std::move(data));
    case 697:
      return new ::Ifc4x1::IfcPointOnSurface(std::move(data));
    case 699:
      return new ::Ifc4x1::IfcPolygonalBoundedHalfSpace(std::move(data));
    case 700:
      return new ::Ifc4x1::IfcPolygonalFaceSet(std::move(data));
    case 701:
      return new ::Ifc4x1::IfcPolyline(std::move(data));
    case 702:
      return new ::Ifc4x1::IfcPolyLoop(std::move(data));
    case 703:
      return new ::Ifc4x1::IfcPort(std::move(data));
    case 704:
      return new ::Ifc4x1::IfcPositioningElement(std::move(data));
    case 705:
      return new ::Ifc4x1::IfcPositiveInteger(std::move(data));
    case 706:
      return new ::Ifc4x1::IfcPositiveLengthMeasure(std::move(data));
    case 707:
      return new ::Ifc4x1::IfcPositivePlaneAngleMeasure(std::move(data));
    case 708:
      return new ::Ifc4x1::IfcPositiveRatioMeasure(std::move(data));
    case 709:
      return new ::Ifc4x1::IfcPostalAddress(std::move(data));
    case 710:
      return new ::Ifc4x1::IfcPowerMeasure(std::move(data));
    case 711:
      return new ::Ifc4x1::IfcPreDefinedColour(std::move(data));
    case 712:
      return new ::Ifc4x1::IfcPreDefinedCurveFont(std::move(data));
    case 713:
      return new ::Ifc4x1::IfcPreDefinedItem(std::move(data));
    case 714:
      return new ::Ifc4x1::IfcPreDefinedProperties(std::move(data));
    case 715:
      return new ::Ifc4x1::IfcPreDefinedPropertySet(std::move(data));
    case 716:
      return new ::Ifc4x1::IfcPreDefinedTextFont(std::move(data));
    case 717:
      return new ::Ifc4x1::IfcPreferredSurfaceCurveRepresentation(
          std::move(data));
    case 718:
      return new ::Ifc4x1::IfcPresentableText(std::move(data));
    case 719:
      return new ::Ifc4x1::IfcPresentationItem(std::move(data));
    case 720:
      return new ::Ifc4x1::IfcPresentationLayerAssignment(std::move(data));
    case 721:
      return new ::Ifc4x1::IfcPresentationLayerWithStyle(std::move(data));
    case 722:
      return new ::Ifc4x1::IfcPresentationStyle(std::move(data));
    case 723:
      return new ::Ifc4x1::IfcPresentationStyleAssignment(std::move(data));
    case 725:
      return new ::Ifc4x1::IfcPressureMeasure(std::move(data));
    case 726:
      return new ::Ifc4x1::IfcProcedure(std::move(data));
    case 727:
      return new ::Ifc4x1::IfcProcedureType(std::move(data));
    case 728:
      return new ::Ifc4x1::IfcProcedureTypeEnum(std::move(data));
    case 729:
      return new ::Ifc4x1::IfcProcess(std::move(data));
    case 731:
      return new ::Ifc4x1::IfcProduct(std::move(data));
    case 732:
      return new ::Ifc4x1::IfcProductDefinitionShape(std::move(data));
    case 733:
      return new ::Ifc4x1::IfcProductRepresentation(std::move(data));
    case 736:
      return new ::Ifc4x1::IfcProfileDef(std::move(data));
    case 737:
      return new ::Ifc4x1::IfcProfileProperties(std::move(data));
    case 738:
      return new ::Ifc4x1::IfcProfileTypeEnum(std::move(data));
    case 739:
      return new ::Ifc4x1::IfcProject(std::move(data));
    case 740:
      return new ::Ifc4x1::IfcProjectedCRS(std::move(data));
    case 741:
      return new ::Ifc4x1::IfcProjectedOrTrueLengthEnum(std::move(data));
    case 742:
      return new ::Ifc4x1::IfcProjectionElement(std::move(data));
    case 743:
      return new ::Ifc4x1::IfcProjectionElementTypeEnum(std::move(data));
    case 744:
      return new ::Ifc4x1::IfcProjectLibrary(std::move(data));
    case 745:
      return new ::Ifc4x1::IfcProjectOrder(std::move(data));
    case 746:
      return new ::Ifc4x1::IfcProjectOrderTypeEnum(std::move(data));
    case 747:
      return new ::Ifc4x1::IfcProperty(std::move(data));
    case 748:
      return new ::Ifc4x1::IfcPropertyAbstraction(std::move(data));
    case 749:
      return new ::Ifc4x1::IfcPropertyBoundedValue(std::move(data));
    case 750:
      return new ::Ifc4x1::IfcPropertyDefinition(std::move(data));
    case 751:
      return new ::Ifc4x1::IfcPropertyDependencyRelationship(std::move(data));
    case 752:
      return new ::Ifc4x1::IfcPropertyEnumeratedValue(std::move(data));
    case 753:
      return new ::Ifc4x1::IfcPropertyEnumeration(std::move(data));
    case 754:
      return new ::Ifc4x1::IfcPropertyListValue(std::move(data));
    case 755:
      return new ::Ifc4x1::IfcPropertyReferenceValue(std::move(data));
    case 756:
      return new ::Ifc4x1::IfcPropertySet(std::move(data));
    case 757:
      return new ::Ifc4x1::IfcPropertySetDefinition(std::move(data));
    case 759:
      return new ::Ifc4x1::IfcPropertySetDefinitionSet(std::move(data));
    case 760:
      return new ::Ifc4x1::IfcPropertySetTemplate(std::move(data));
    case 761:
      return new ::Ifc4x1::IfcPropertySetTemplateTypeEnum(std::move(data));
    case 762:
      return new ::Ifc4x1::IfcPropertySingleValue(std::move(data));
    case 763:
      return new ::Ifc4x1::IfcPropertyTableValue(std::move(data));
    case 764:
      return new ::Ifc4x1::IfcPropertyTemplate(std::move(data));
    case 765:
      return new ::Ifc4x1::IfcPropertyTemplateDefinition(std::move(data));
    case 766:
      return new ::Ifc4x1::IfcProtectiveDevice(std::move(data));
    case 767:
      return new ::Ifc4x1::IfcProtectiveDeviceTrippingUnit(std::move(data));
    case 768:
      return new ::Ifc4x1::IfcProtectiveDeviceTrippingUnitType(std::move(data));
    case 769:
      return new ::Ifc4x1::IfcProtectiveDeviceTrippingUnitTypeEnum(
          std::move(data));
    case 770:
      return new ::Ifc4x1::IfcProtectiveDeviceType(std::move(data));
    case 771:
      return new ::Ifc4x1::IfcProtectiveDeviceTypeEnum(std::move(data));
    case 772:
      return new ::Ifc4x1::IfcProxy(std::move(data));
    case 773:
      return new ::Ifc4x1::IfcPump(std::move(data));
    case 774:
      return new ::Ifc4x1::IfcPumpType(std::move(data));
    case 775:
      return new ::Ifc4x1::IfcPumpTypeEnum(std::move(data));
    case 776:
      return new ::Ifc4x1::IfcQuantityArea(std::move(data));
    case 777:
      return new ::Ifc4x1::IfcQuantityCount(std::move(data));
    case 778:
      return new ::Ifc4x1::IfcQuantityLength(std::move(data));
    case 779:
      return new ::Ifc4x1::IfcQuantitySet(std::move(data));
    case 780:
      return new ::Ifc4x1::IfcQuantityTime(std::move(data));
    case 781:
      return new ::Ifc4x1::IfcQuantityVolume(std::move(data));
    case 782:
      return new ::Ifc4x1::IfcQuantityWeight(std::move(data));
    case 783:
      return new ::Ifc4x1::IfcRadioActivityMeasure(std::move(data));
    case 784:
      return new ::Ifc4x1::IfcRailing(std::move(data));
    case 785:
      return new ::Ifc4x1::IfcRailingType(std::move(data));
    case 786:
      return new ::Ifc4x1::IfcRailingTypeEnum(std::move(data));
    case 787:
      return new ::Ifc4x1::IfcRamp(std::move(data));
    case 788:
      return new ::Ifc4x1::IfcRampFlight(std::move(data));
    case 789:
      return new ::Ifc4x1::IfcRampFlightType(std::move(data));
    case 790:
      return new ::Ifc4x1::IfcRampFlightTypeEnum(std::move(data));
    case 791:
      return new ::Ifc4x1::IfcRampType(std::move(data));
    case 792:
      return new ::Ifc4x1::IfcRampTypeEnum(std::move(data));
    case 793:
      return new ::Ifc4x1::IfcRatioMeasure(std::move(data));
    case 794:
      return new ::Ifc4x1::IfcRationalBSplineCurveWithKnots(std::move(data));
    case 795:
      return new ::Ifc4x1::IfcRationalBSplineSurfaceWithKnots(std::move(data));
    case 796:
      return new ::Ifc4x1::IfcReal(std::move(data));
    case 797:
      return new ::Ifc4x1::IfcRectangleHollowProfileDef(std::move(data));
    case 798:
      return new ::Ifc4x1::IfcRectangleProfileDef(std::move(data));
    case 799:
      return new ::Ifc4x1::IfcRectangularPyramid(std::move(data));
    case 800:
      return new ::Ifc4x1::IfcRectangularTrimmedSurface(std::move(data));
    case 801:
      return new ::Ifc4x1::IfcRecurrencePattern(std::move(data));
    case 802:
      return new ::Ifc4x1::IfcRecurrenceTypeEnum(std::move(data));
    case 803:
      return new ::Ifc4x1::IfcReference(std::move(data));
    case 804:
      return new ::Ifc4x1::IfcReferent(std::move(data));
    case 805:
      return new ::Ifc4x1::IfcReferentTypeEnum(std::move(data));
    case 806:
      return new ::Ifc4x1::IfcReflectanceMethodEnum(std::move(data));
    case 807:
      return new ::Ifc4x1::IfcRegularTimeSeries(std::move(data));
    case 808:
      return new ::Ifc4x1::IfcReinforcementBarProperties(std::move(data));
    case 809:
      return new ::Ifc4x1::IfcReinforcementDefinitionProperties(
          std::move(data));
    case 810:
      return new ::Ifc4x1::IfcReinforcingBar(std::move(data));
    case 811:
      return new ::Ifc4x1::IfcReinforcingBarRoleEnum(std::move(data));
    case 812:
      return new ::Ifc4x1::IfcReinforcingBarSurfaceEnum(std::move(data));
    case 813:
      return new ::Ifc4x1::IfcReinforcingBarType(std::move(data));
    case 814:
      return new ::Ifc4x1::IfcReinforcingBarTypeEnum(std::move(data));
    case 815:
      return new ::Ifc4x1::IfcReinforcingElement(std::move(data));
    case 816:
      return new ::Ifc4x1::IfcReinforcingElementType(std::move(data));
    case 817:
      return new ::Ifc4x1::IfcReinforcingMesh(std::move(data));
    case 818:
      return new ::Ifc4x1::IfcReinforcingMeshType(std::move(data));
    case 819:
      return new ::Ifc4x1::IfcReinforcingMeshTypeEnum(std::move(data));
    case 820:
      return new ::Ifc4x1::IfcRelAggregates(std::move(data));
    case 821:
      return new ::Ifc4x1::IfcRelAssigns(std::move(data));
    case 822:
      return new ::Ifc4x1::IfcRelAssignsToActor(std::move(data));
    case 823:
      return new ::Ifc4x1::IfcRelAssignsToControl(std::move(data));
    case 824:
      return new ::Ifc4x1::IfcRelAssignsToGroup(std::move(data));
    case 825:
      return new ::Ifc4x1::IfcRelAssignsToGroupByFactor(std::move(data));
    case 826:
      return new ::Ifc4x1::IfcRelAssignsToProcess(std::move(data));
    case 827:
      return new ::Ifc4x1::IfcRelAssignsToProduct(std::move(data));
    case 828:
      return new ::Ifc4x1::IfcRelAssignsToResource(std::move(data));
    case 829:
      return new ::Ifc4x1::IfcRelAssociates(std::move(data));
    case 830:
      return new ::Ifc4x1::IfcRelAssociatesApproval(std::move(data));
    case 831:
      return new ::Ifc4x1::IfcRelAssociatesClassification(std::move(data));
    case 832:
      return new ::Ifc4x1::IfcRelAssociatesConstraint(std::move(data));
    case 833:
      return new ::Ifc4x1::IfcRelAssociatesDocument(std::move(data));
    case 834:
      return new ::Ifc4x1::IfcRelAssociatesLibrary(std::move(data));
    case 835:
      return new ::Ifc4x1::IfcRelAssociatesMaterial(std::move(data));
    case 836:
      return new ::Ifc4x1::IfcRelationship(std::move(data));
    case 837:
      return new ::Ifc4x1::IfcRelConnects(std::move(data));
    case 838:
      return new ::Ifc4x1::IfcRelConnectsElements(std::move(data));
    case 839:
      return new ::Ifc4x1::IfcRelConnectsPathElements(std::move(data));
    case 840:
      return new ::Ifc4x1::IfcRelConnectsPorts(std::move(data));
    case 841:
      return new ::Ifc4x1::IfcRelConnectsPortToElement(std::move(data));
    case 842:
      return new ::Ifc4x1::IfcRelConnectsStructuralActivity(std::move(data));
    case 843:
      return new ::Ifc4x1::IfcRelConnectsStructuralMember(std::move(data));
    case 844:
      return new ::Ifc4x1::IfcRelConnectsWithEccentricity(std::move(data));
    case 845:
      return new ::Ifc4x1::IfcRelConnectsWithRealizingElements(std::move(data));
    case 846:
      return new ::Ifc4x1::IfcRelContainedInSpatialStructure(std::move(data));
    case 847:
      return new ::Ifc4x1::IfcRelCoversBldgElements(std::move(data));
    case 848:
      return new ::Ifc4x1::IfcRelCoversSpaces(std::move(data));
    case 849:
      return new ::Ifc4x1::IfcRelDeclares(std::move(data));
    case 850:
      return new ::Ifc4x1::IfcRelDecomposes(std::move(data));
    case 851:
      return new ::Ifc4x1::IfcRelDefines(std::move(data));
    case 852:
      return new ::Ifc4x1::IfcRelDefinesByObject(std::move(data));
    case 853:
      return new ::Ifc4x1::IfcRelDefinesByProperties(std::move(data));
    case 854:
      return new ::Ifc4x1::IfcRelDefinesByTemplate(std::move(data));
    case 855:
      return new ::Ifc4x1::IfcRelDefinesByType(std::move(data));
    case 856:
      return new ::Ifc4x1::IfcRelFillsElement(std::move(data));
    case 857:
      return new ::Ifc4x1::IfcRelFlowControlElements(std::move(data));
    case 858:
      return new ::Ifc4x1::IfcRelInterferesElements(std::move(data));
    case 859:
      return new ::Ifc4x1::IfcRelNests(std::move(data));
    case 860:
      return new ::Ifc4x1::IfcRelProjectsElement(std::move(data));
    case 861:
      return new ::Ifc4x1::IfcRelReferencedInSpatialStructure(std::move(data));
    case 862:
      return new ::Ifc4x1::IfcRelSequence(std::move(data));
    case 863:
      return new ::Ifc4x1::IfcRelServicesBuildings(std::move(data));
    case 864:
      return new ::Ifc4x1::IfcRelSpaceBoundary(std::move(data));
    case 865:
      return new ::Ifc4x1::IfcRelSpaceBoundary1stLevel(std::move(data));
    case 866:
      return new ::Ifc4x1::IfcRelSpaceBoundary2ndLevel(std::move(data));
    case 867:
      return new ::Ifc4x1::IfcRelVoidsElement(std::move(data));
    case 868:
      return new ::Ifc4x1::IfcReparametrisedCompositeCurveSegment(
          std::move(data));
    case 869:
      return new ::Ifc4x1::IfcRepresentation(std::move(data));
    case 870:
      return new ::Ifc4x1::IfcRepresentationContext(std::move(data));
    case 871:
      return new ::Ifc4x1::IfcRepresentationItem(std::move(data));
    case 872:
      return new ::Ifc4x1::IfcRepresentationMap(std::move(data));
    case 873:
      return new ::Ifc4x1::IfcResource(std::move(data));
    case 874:
      return new ::Ifc4x1::IfcResourceApprovalRelationship(std::move(data));
    case 875:
      return new ::Ifc4x1::IfcResourceConstraintRelationship(std::move(data));
    case 876:
      return new ::Ifc4x1::IfcResourceLevelRelationship(std::move(data));
    case 879:
      return new ::Ifc4x1::IfcResourceTime(std::move(data));
    case 880:
      return new ::Ifc4x1::IfcRevolvedAreaSolid(std::move(data));
    case 881:
      return new ::Ifc4x1::IfcRevolvedAreaSolidTapered(std::move(data));
    case 882:
      return new ::Ifc4x1::IfcRightCircularCone(std::move(data));
    case 883:
      return new ::Ifc4x1::IfcRightCircularCylinder(std::move(data));
    case 884:
      return new ::Ifc4x1::IfcRoleEnum(std::move(data));
    case 885:
      return new ::Ifc4x1::IfcRoof(std::move(data));
    case 886:
      return new ::Ifc4x1::IfcRoofType(std::move(data));
    case 887:
      return new ::Ifc4x1::IfcRoofTypeEnum(std::move(data));
    case 888:
      return new ::Ifc4x1::IfcRoot(std::move(data));
    case 889:
      return new ::Ifc4x1::IfcRotationalFrequencyMeasure(std::move(data));
    case 890:
      return new ::Ifc4x1::IfcRotationalMassMeasure(std::move(data));
    case 891:
      return new ::Ifc4x1::IfcRotationalStiffnessMeasure(std::move(data));
    case 893:
      return new ::Ifc4x1::IfcRoundedRectangleProfileDef(std::move(data));
    case 894:
      return new ::Ifc4x1::IfcSanitaryTerminal(std::move(data));
    case 895:
      return new ::Ifc4x1::IfcSanitaryTerminalType(std::move(data));
    case 896:
      return new ::Ifc4x1::IfcSanitaryTerminalTypeEnum(std::move(data));
    case 897:
      return new ::Ifc4x1::IfcSchedulingTime(std::move(data));
    case 898:
      return new ::Ifc4x1::IfcSeamCurve(std::move(data));
    case 899:
      return new ::Ifc4x1::IfcSectionalAreaIntegralMeasure(std::move(data));
    case 900:
      return new ::Ifc4x1::IfcSectionedSolid(std::move(data));
    case 901:
      return new ::Ifc4x1::IfcSectionedSolidHorizontal(std::move(data));
    case 902:
      return new ::Ifc4x1::IfcSectionedSpine(std::move(data));
    case 903:
      return new ::Ifc4x1::IfcSectionModulusMeasure(std::move(data));
    case 904:
      return new ::Ifc4x1::IfcSectionProperties(std::move(data));
    case 905:
      return new ::Ifc4x1::IfcSectionReinforcementProperties(std::move(data));
    case 906:
      return new ::Ifc4x1::IfcSectionTypeEnum(std::move(data));
    case 908:
      return new ::Ifc4x1::IfcSensor(std::move(data));
    case 909:
      return new ::Ifc4x1::IfcSensorType(std::move(data));
    case 910:
      return new ::Ifc4x1::IfcSensorTypeEnum(std::move(data));
    case 911:
      return new ::Ifc4x1::IfcSequenceEnum(std::move(data));
    case 912:
      return new ::Ifc4x1::IfcShadingDevice(std::move(data));
    case 913:
      return new ::Ifc4x1::IfcShadingDeviceType(std::move(data));
    case 914:
      return new ::Ifc4x1::IfcShadingDeviceTypeEnum(std::move(data));
    case 915:
      return new ::Ifc4x1::IfcShapeAspect(std::move(data));
    case 916:
      return new ::Ifc4x1::IfcShapeModel(std::move(data));
    case 917:
      return new ::Ifc4x1::IfcShapeRepresentation(std::move(data));
    case 918:
      return new ::Ifc4x1::IfcShearModulusMeasure(std::move(data));
    case 920:
      return new ::Ifc4x1::IfcShellBasedSurfaceModel(std::move(data));
    case 921:
      return new ::Ifc4x1::IfcSimpleProperty(std::move(data));
    case 922:
      return new ::Ifc4x1::IfcSimplePropertyTemplate(std::move(data));
    case 923:
      return new ::Ifc4x1::IfcSimplePropertyTemplateTypeEnum(std::move(data));
    case 925:
      return new ::Ifc4x1::IfcSIPrefix(std::move(data));
    case 926:
      return new ::Ifc4x1::IfcSite(std::move(data));
    case 927:
      return new ::Ifc4x1::IfcSIUnit(std::move(data));
    case 928:
      return new ::Ifc4x1::IfcSIUnitName(std::move(data));
    case 930:
      return new ::Ifc4x1::IfcSlab(std::move(data));
    case 931:
      return new ::Ifc4x1::IfcSlabElementedCase(std::move(data));
    case 932:
      return new ::Ifc4x1::IfcSlabStandardCase(std::move(data));
    case 933:
      return new ::Ifc4x1::IfcSlabType(std::move(data));
    case 934:
      return new ::Ifc4x1::IfcSlabTypeEnum(std::move(data));
    case 935:
      return new ::Ifc4x1::IfcSlippageConnectionCondition(std::move(data));
    case 936:
      return new ::Ifc4x1::IfcSolarDevice(std::move(data));
    case 937:
      return new ::Ifc4x1::IfcSolarDeviceType(std::move(data));
    case 938:
      return new ::Ifc4x1::IfcSolarDeviceTypeEnum(std::move(data));
    case 939:
      return new ::Ifc4x1::IfcSolidAngleMeasure(std::move(data));
    case 940:
      return new ::Ifc4x1::IfcSolidModel(std::move(data));
    case 942:
      return new ::Ifc4x1::IfcSoundPowerLevelMeasure(std::move(data));
    case 943:
      return new ::Ifc4x1::IfcSoundPowerMeasure(std::move(data));
    case 944:
      return new ::Ifc4x1::IfcSoundPressureLevelMeasure(std::move(data));
    case 945:
      return new ::Ifc4x1::IfcSoundPressureMeasure(std::move(data));
    case 946:
      return new ::Ifc4x1::IfcSpace(std::move(data));
    case 948:
      return new ::Ifc4x1::IfcSpaceHeater(std::move(data));
    case 949:
      return new ::Ifc4x1::IfcSpaceHeaterType(std::move(data));
    case 950:
      return new ::Ifc4x1::IfcSpaceHeaterTypeEnum(std::move(data));
    case 951:
      return new ::Ifc4x1::IfcSpaceType(std::move(data));
    case 952:
      return new ::Ifc4x1::IfcSpaceTypeEnum(std::move(data));
    case 953:
      return new ::Ifc4x1::IfcSpatialElement(std::move(data));
    case 954:
      return new ::Ifc4x1::IfcSpatialElementType(std::move(data));
    case 955:
      return new ::Ifc4x1::IfcSpatialStructureElement(std::move(data));
    case 956:
      return new ::Ifc4x1::IfcSpatialStructureElementType(std::move(data));
    case 957:
      return new ::Ifc4x1::IfcSpatialZone(std::move(data));
    case 958:
      return new ::Ifc4x1::IfcSpatialZoneType(std::move(data));
    case 959:
      return new ::Ifc4x1::IfcSpatialZoneTypeEnum(std::move(data));
    case 960:
      return new ::Ifc4x1::IfcSpecificHeatCapacityMeasure(std::move(data));
    case 961:
      return new ::Ifc4x1::IfcSpecularExponent(std::move(data));
    case 963:
      return new ::Ifc4x1::IfcSpecularRoughness(std::move(data));
    case 964:
      return new ::Ifc4x1::IfcSphere(std::move(data));
    case 965:
      return new ::Ifc4x1::IfcSphericalSurface(std::move(data));
    case 966:
      return new ::Ifc4x1::IfcStackTerminal(std::move(data));
    case 967:
      return new ::Ifc4x1::IfcStackTerminalType(std::move(data));
    case 968:
      return new ::Ifc4x1::IfcStackTerminalTypeEnum(std::move(data));
    case 969:
      return new ::Ifc4x1::IfcStair(std::move(data));
    case 970:
      return new ::Ifc4x1::IfcStairFlight(std::move(data));
    case 971:
      return new ::Ifc4x1::IfcStairFlightType(std::move(data));
    case 972:
      return new ::Ifc4x1::IfcStairFlightTypeEnum(std::move(data));
    case 973:
      return new ::Ifc4x1::IfcStairType(std::move(data));
    case 974:
      return new ::Ifc4x1::IfcStairTypeEnum(std::move(data));
    case 975:
      return new ::Ifc4x1::IfcStateEnum(std::move(data));
    case 976:
      return new ::Ifc4x1::IfcStructuralAction(std::move(data));
    case 977:
      return new ::Ifc4x1::IfcStructuralActivity(std::move(data));
    case 979:
      return new ::Ifc4x1::IfcStructuralAnalysisModel(std::move(data));
    case 980:
      return new ::Ifc4x1::IfcStructuralConnection(std::move(data));
    case 981:
      return new ::Ifc4x1::IfcStructuralConnectionCondition(std::move(data));
    case 982:
      return new ::Ifc4x1::IfcStructuralCurveAction(std::move(data));
    case 983:
      return new ::Ifc4x1::IfcStructuralCurveActivityTypeEnum(std::move(data));
    case 984:
      return new ::Ifc4x1::IfcStructuralCurveConnection(std::move(data));
    case 985:
      return new ::Ifc4x1::IfcStructuralCurveMember(std::move(data));
    case 986:
      return new ::Ifc4x1::IfcStructuralCurveMemberTypeEnum(std::move(data));
    case 987:
      return new ::Ifc4x1::IfcStructuralCurveMemberVarying(std::move(data));
    case 988:
      return new ::Ifc4x1::IfcStructuralCurveReaction(std::move(data));
    case 989:
      return new ::Ifc4x1::IfcStructuralItem(std::move(data));
    case 990:
      return new ::Ifc4x1::IfcStructuralLinearAction(std::move(data));
    case 991:
      return new ::Ifc4x1::IfcStructuralLoad(std::move(data));
    case 992:
      return new ::Ifc4x1::IfcStructuralLoadCase(std::move(data));
    case 993:
      return new ::Ifc4x1::IfcStructuralLoadConfiguration(std::move(data));
    case 994:
      return new ::Ifc4x1::IfcStructuralLoadGroup(std::move(data));
    case 995:
      return new ::Ifc4x1::IfcStructuralLoadLinearForce(std::move(data));
    case 996:
      return new ::Ifc4x1::IfcStructuralLoadOrResult(std::move(data));
    case 997:
      return new ::Ifc4x1::IfcStructuralLoadPlanarForce(std::move(data));
    case 998:
      return new ::Ifc4x1::IfcStructuralLoadSingleDisplacement(std::move(data));
    case 999:
      return new ::Ifc4x1::IfcStructuralLoadSingleDisplacementDistortion(
          std::move(data));
    case 1000:
      return new ::Ifc4x1::IfcStructuralLoadSingleForce(std::move(data));
    case 1001:
      return new ::Ifc4x1::IfcStructuralLoadSingleForceWarping(std::move(data));
    case 1002:
      return new ::Ifc4x1::IfcStructuralLoadStatic(std::move(data));
    case 1003:
      return new ::Ifc4x1::IfcStructuralLoadTemperature(std::move(data));
    case 1004:
      return new ::Ifc4x1::IfcStructuralMember(std::move(data));
    case 1005:
      return new ::Ifc4x1::IfcStructuralPlanarAction(std::move(data));
    case 1006:
      return new ::Ifc4x1::IfcStructuralPointAction(std::move(data));
    case 1007:
      return new ::Ifc4x1::IfcStructuralPointConnection(std::move(data));
    case 1008:
      return new ::Ifc4x1::IfcStructuralPointReaction(std::move(data));
    case 1009:
      return new ::Ifc4x1::IfcStructuralReaction(std::move(data));
    case 1010:
      return new ::Ifc4x1::IfcStructuralResultGroup(std::move(data));
    case 1011:
      return new ::Ifc4x1::IfcStructuralSurfaceAction(std::move(data));
    case 1012:
      return new ::Ifc4x1::IfcStructuralSurfaceActivityTypeEnum(
          std::move(data));
    case 1013:
      return new ::Ifc4x1::IfcStructuralSurfaceConnection(std::move(data));
    case 1014:
      return new ::Ifc4x1::IfcStructuralSurfaceMember(std::move(data));
    case 1015:
      return new ::Ifc4x1::IfcStructuralSurfaceMemberTypeEnum(std::move(data));
    case 1016:
      return new ::Ifc4x1::IfcStructuralSurfaceMemberVarying(std::move(data));
    case 1017:
      return new ::Ifc4x1::IfcStructuralSurfaceReaction(std::move(data));
    case 1019:
      return new ::Ifc4x1::IfcStyledItem(std::move(data));
    case 1020:
      return new ::Ifc4x1::IfcStyledRepresentation(std::move(data));
    case 1021:
      return new ::Ifc4x1::IfcStyleModel(std::move(data));
    case 1022:
      return new ::Ifc4x1::IfcSubContractResource(std::move(data));
    case 1023:
      return new ::Ifc4x1::IfcSubContractResourceType(std::move(data));
    case 1024:
      return new ::Ifc4x1::IfcSubContractResourceTypeEnum(std::move(data));
    case 1025:
      return new ::Ifc4x1::IfcSubedge(std::move(data));
    case 1026:
      return new ::Ifc4x1::IfcSurface(std::move(data));
    case 1027:
      return new ::Ifc4x1::IfcSurfaceCurve(std::move(data));
    case 1028:
      return new ::Ifc4x1::IfcSurfaceCurveSweptAreaSolid(std::move(data));
    case 1029:
      return new ::Ifc4x1::IfcSurfaceFeature(std::move(data));
    case 1030:
      return new ::Ifc4x1::IfcSurfaceFeatureTypeEnum(std::move(data));
    case 1031:
      return new ::Ifc4x1::IfcSurfaceOfLinearExtrusion(std::move(data));
    case 1032:
      return new ::Ifc4x1::IfcSurfaceOfRevolution(std::move(data));
    case 1034:
      return new ::Ifc4x1::IfcSurfaceReinforcementArea(std::move(data));
    case 1035:
      return new ::Ifc4x1::IfcSurfaceSide(std::move(data));
    case 1036:
      return new ::Ifc4x1::IfcSurfaceStyle(std::move(data));
    case 1038:
      return new ::Ifc4x1::IfcSurfaceStyleLighting(std::move(data));
    case 1039:
      return new ::Ifc4x1::IfcSurfaceStyleRefraction(std::move(data));
    case 1040:
      return new ::Ifc4x1::IfcSurfaceStyleRendering(std::move(data));
    case 1041:
      return new ::Ifc4x1::IfcSurfaceStyleShading(std::move(data));
    case 1042:
      return new ::Ifc4x1::IfcSurfaceStyleWithTextures(std::move(data));
    case 1043:
      return new ::Ifc4x1::IfcSurfaceTexture(std::move(data));
    case 1044:
      return new ::Ifc4x1::IfcSweptAreaSolid(std::move(data));
    case 1045:
      return new ::Ifc4x1::IfcSweptDiskSolid(std::move(data));
    case 1046:
      return new ::Ifc4x1::IfcSweptDiskSolidPolygonal(std::move(data));
    case 1047:
      return new ::Ifc4x1::IfcSweptSurface(std::move(data));
    case 1048:
      return new ::Ifc4x1::IfcSwitchingDevice(std::move(data));
    case 1049:
      return new ::Ifc4x1::IfcSwitchingDeviceType(std::move(data));
    case 1050:
      return new ::Ifc4x1::IfcSwitchingDeviceTypeEnum(std::move(data));
    case 1051:
      return new ::Ifc4x1::IfcSystem(std::move(data));
    case 1052:
      return new ::Ifc4x1::IfcSystemFurnitureElement(std::move(data));
    case 1053:
      return new ::Ifc4x1::IfcSystemFurnitureElementType(std::move(data));
    case 1054:
      return new ::Ifc4x1::IfcSystemFurnitureElementTypeEnum(std::move(data));
    case 1055:
      return new ::Ifc4x1::IfcTable(std::move(data));
    case 1056:
      return new ::Ifc4x1::IfcTableColumn(std::move(data));
    case 1057:
      return new ::Ifc4x1::IfcTableRow(std::move(data));
    case 1058:
      return new ::Ifc4x1::IfcTank(std::move(data));
    case 1059:
      return new ::Ifc4x1::IfcTankType(std::move(data));
    case 1060:
      return new ::Ifc4x1::IfcTankTypeEnum(std::move(data));
    case 1061:
      return new ::Ifc4x1::IfcTask(std::move(data));
    case 1062:
      return new ::Ifc4x1::IfcTaskDurationEnum(std::move(data));
    case 1063:
      return new ::Ifc4x1::IfcTaskTime(std::move(data));
    case 1064:
      return new ::Ifc4x1::IfcTaskTimeRecurring(std::move(data));
    case 1065:
      return new ::Ifc4x1::IfcTaskType(std::move(data));
    case 1066:
      return new ::Ifc4x1::IfcTaskTypeEnum(std::move(data));
    case 1067:
      return new ::Ifc4x1::IfcTelecomAddress(std::move(data));
    case 1068:
      return new ::Ifc4x1::IfcTemperatureGradientMeasure(std::move(data));
    case 1069:
      return new ::Ifc4x1::IfcTemperatureRateOfChangeMeasure(std::move(data));
    case 1070:
      return new ::Ifc4x1::IfcTendon(std::move(data));
    case 1071:
      return new ::Ifc4x1::IfcTendonAnchor(std::move(data));
    case 1072:
      return new ::Ifc4x1::IfcTendonAnchorType(std::move(data));
    case 1073:
      return new ::Ifc4x1::IfcTendonAnchorTypeEnum(std::move(data));
    case 1074:
      return new ::Ifc4x1::IfcTendonType(std::move(data));
    case 1075:
      return new ::Ifc4x1::IfcTendonTypeEnum(std::move(data));
    case 1076:
      return new ::Ifc4x1::IfcTessellatedFaceSet(std::move(data));
    case 1077:
      return new ::Ifc4x1::IfcTessellatedItem(std::move(data));
    case 1078:
      return new ::Ifc4x1::IfcText(std::move(data));
    case 1079:
      return new ::Ifc4x1::IfcTextAlignment(std::move(data));
    case 1080:
      return new ::Ifc4x1::IfcTextDecoration(std::move(data));
    case 1081:
      return new ::Ifc4x1::IfcTextFontName(std::move(data));
    case 1083:
      return new ::Ifc4x1::IfcTextLiteral(std::move(data));
    case 1084:
      return new ::Ifc4x1::IfcTextLiteralWithExtent(std::move(data));
    case 1085:
      return new ::Ifc4x1::IfcTextPath(std::move(data));
    case 1086:
      return new ::Ifc4x1::IfcTextStyle(std::move(data));
    case 1087:
      return new ::Ifc4x1::IfcTextStyleFontModel(std::move(data));
    case 1088:
      return new ::Ifc4x1::IfcTextStyleForDefinedFont(std::move(data));
    case 1089:
      return new ::Ifc4x1::IfcTextStyleTextModel(std::move(data));
    case 1090:
      return new ::Ifc4x1::IfcTextTransformation(std::move(data));
    case 1091:
      return new ::Ifc4x1::IfcTextureCoordinate(std::move(data));
    case 1092:
      return new ::Ifc4x1::IfcTextureCoordinateGenerator(std::move(data));
    case 1093:
      return new ::Ifc4x1::IfcTextureMap(std::move(data));
    case 1094:
      return new ::Ifc4x1::IfcTextureVertex(std::move(data));
    case 1095:
      return new ::Ifc4x1::IfcTextureVertexList(std::move(data));
    case 1096:
      return new ::Ifc4x1::IfcThermalAdmittanceMeasure(std::move(data));
    case 1097:
      return new ::Ifc4x1::IfcThermalConductivityMeasure(std::move(data));
    case 1098:
      return new ::Ifc4x1::IfcThermalExpansionCoefficientMeasure(
          std::move(data));
    case 1099:
      return new ::Ifc4x1::IfcThermalResistanceMeasure(std::move(data));
    case 1100:
      return new ::Ifc4x1::IfcThermalTransmittanceMeasure(std::move(data));
    case 1101:
      return new ::Ifc4x1::IfcThermodynamicTemperatureMeasure(std::move(data));
    case 1102:
      return new ::Ifc4x1::IfcTime(std::move(data));
    case 1103:
      return new ::Ifc4x1::IfcTimeMeasure(std::move(data));
    case 1105:
      return new ::Ifc4x1::IfcTimePeriod(std::move(data));
    case 1106:
      return new ::Ifc4x1::IfcTimeSeries(std::move(data));
    case 1107:
      return new ::Ifc4x1::IfcTimeSeriesDataTypeEnum(std::move(data));
    case 1108:
      return new ::Ifc4x1::IfcTimeSeriesValue(std::move(data));
    case 1109:
      return new ::Ifc4x1::IfcTimeStamp(std::move(data));
    case 1110:
      return new ::Ifc4x1::IfcTopologicalRepresentationItem(std::move(data));
    case 1111:
      return new ::Ifc4x1::IfcTopologyRepresentation(std::move(data));
    case 1112:
      return new ::Ifc4x1::IfcToroidalSurface(std::move(data));
    case 1113:
      return new ::Ifc4x1::IfcTorqueMeasure(std::move(data));
    case 1114:
      return new ::Ifc4x1::IfcTransformer(std::move(data));
    case 1115:
      return new ::Ifc4x1::IfcTransformerType(std::move(data));
    case 1116:
      return new ::Ifc4x1::IfcTransformerTypeEnum(std::move(data));
    case 1117:
      return new ::Ifc4x1::IfcTransitionCode(std::move(data));
    case 1118:
      return new ::Ifc4x1::IfcTransitionCurveSegment2D(std::move(data));
    case 1119:
      return new ::Ifc4x1::IfcTransitionCurveType(std::move(data));
    case 1121:
      return new ::Ifc4x1::IfcTransportElement(std::move(data));
    case 1122:
      return new ::Ifc4x1::IfcTransportElementType(std::move(data));
    case 1123:
      return new ::Ifc4x1::IfcTransportElementTypeEnum(std::move(data));
    case 1124:
      return new ::Ifc4x1::IfcTrapeziumProfileDef(std::move(data));
    case 1125:
      return new ::Ifc4x1::IfcTriangulatedFaceSet(std::move(data));
    case 1126:
      return new ::Ifc4x1::IfcTriangulatedIrregularNetwork(std::move(data));
    case 1127:
      return new ::Ifc4x1::IfcTrimmedCurve(std::move(data));
    case 1128:
      return new ::Ifc4x1::IfcTrimmingPreference(std::move(data));
    case 1130:
      return new ::Ifc4x1::IfcTShapeProfileDef(std::move(data));
    case 1131:
      return new ::Ifc4x1::IfcTubeBundle(std::move(data));
    case 1132:
      return new ::Ifc4x1::IfcTubeBundleType(std::move(data));
    case 1133:
      return new ::Ifc4x1::IfcTubeBundleTypeEnum(std::move(data));
    case 1134:
      return new ::Ifc4x1::IfcTypeObject(std::move(data));
    case 1135:
      return new ::Ifc4x1::IfcTypeProcess(std::move(data));
    case 1136:
      return new ::Ifc4x1::IfcTypeProduct(std::move(data));
    case 1137:
      return new ::Ifc4x1::IfcTypeResource(std::move(data));
    case 1139:
      return new ::Ifc4x1::IfcUnitaryControlElement(std::move(data));
    case 1140:
      return new ::Ifc4x1::IfcUnitaryControlElementType(std::move(data));
    case 1141:
      return new ::Ifc4x1::IfcUnitaryControlElementTypeEnum(std::move(data));
    case 1142:
      return new ::Ifc4x1::IfcUnitaryEquipment(std::move(data));
    case 1143:
      return new ::Ifc4x1::IfcUnitaryEquipmentType(std::move(data));
    case 1144:
      return new ::Ifc4x1::IfcUnitaryEquipmentTypeEnum(std::move(data));
    case 1145:
      return new ::Ifc4x1::IfcUnitAssignment(std::move(data));
    case 1146:
      return new ::Ifc4x1::IfcUnitEnum(std::move(data));
    case 1147:
      return new ::Ifc4x1::IfcURIReference(std::move(data));
    case 1148:
      return new ::Ifc4x1::IfcUShapeProfileDef(std::move(data));
    case 1150:
      return new ::Ifc4x1::IfcValve(std::move(data));
    case 1151:
      return new ::Ifc4x1::IfcValveType(std::move(data));
    case 1152:
      return new ::Ifc4x1::IfcValveTypeEnum(std::move(data));
    case 1153:
      return new ::Ifc4x1::IfcVaporPermeabilityMeasure(std::move(data));
    case 1154:
      return new ::Ifc4x1::IfcVector(std::move(data));
    case 1156:
      return new ::Ifc4x1::IfcVertex(std::move(data));
    case 1157:
      return new ::Ifc4x1::IfcVertexLoop(std::move(data));
    case 1158:
      return new ::Ifc4x1::IfcVertexPoint(std::move(data));
    case 1159:
      return new ::Ifc4x1::IfcVibrationIsolator(std::move(data));
    case 1160:
      return new ::Ifc4x1::IfcVibrationIsolatorType(std::move(data));
    case 1161:
      return new ::Ifc4x1::IfcVibrationIsolatorTypeEnum(std::move(data));
    case 1162:
      return new ::Ifc4x1::IfcVirtualElement(std::move(data));
    case 1163:
      return new ::Ifc4x1::IfcVirtualGridIntersection(std::move(data));
    case 1164:
      return new ::Ifc4x1::IfcVoidingFeature(std::move(data));
    case 1165:
      return new ::Ifc4x1::IfcVoidingFeatureTypeEnum(std::move(data));
    case 1166:
      return new ::Ifc4x1::IfcVolumeMeasure(std::move(data));
    case 1167:
      return new ::Ifc4x1::IfcVolumetricFlowRateMeasure(std::move(data));
    case 1168:
      return new ::Ifc4x1::IfcWall(std::move(data));
    case 1169:
      return new ::Ifc4x1::IfcWallElementedCase(std::move(data));
    case 1170:
      return new ::Ifc4x1::IfcWallStandardCase(std::move(data));
    case 1171:
      return new ::Ifc4x1::IfcWallType(std::move(data));
    case 1172:
      return new ::Ifc4x1::IfcWallTypeEnum(std::move(data));
    case 1173:
      return new ::Ifc4x1::IfcWarpingConstantMeasure(std::move(data));
    case 1174:
      return new ::Ifc4x1::IfcWarpingMomentMeasure(std::move(data));
    case 1176:
      return new ::Ifc4x1::IfcWasteTerminal(std::move(data));
    case 1177:
      return new ::Ifc4x1::IfcWasteTerminalType(std::move(data));
    case 1178:
      return new ::Ifc4x1::IfcWasteTerminalTypeEnum(std::move(data));
    case 1179:
      return new ::Ifc4x1::IfcWindow(std::move(data));
    case 1180:
      return new ::Ifc4x1::IfcWindowLiningProperties(std::move(data));
    case 1181:
      return new ::Ifc4x1::IfcWindowPanelOperationEnum(std::move(data));
    case 1182:
      return new ::Ifc4x1::IfcWindowPanelPositionEnum(std::move(data));
    case 1183:
      return new ::Ifc4x1::IfcWindowPanelProperties(std::move(data));
    case 1184:
      return new ::Ifc4x1::IfcWindowStandardCase(std::move(data));
    case 1185:
      return new ::Ifc4x1::IfcWindowStyle(std::move(data));
    case 1186:
      return new ::Ifc4x1::IfcWindowStyleConstructionEnum(std::move(data));
    case 1187:
      return new ::Ifc4x1::IfcWindowStyleOperationEnum(std::move(data));
    case 1188:
      return new ::Ifc4x1::IfcWindowType(std::move(data));
    case 1189:
      return new ::Ifc4x1::IfcWindowTypeEnum(std::move(data));
    case 1190:
      return new ::Ifc4x1::IfcWindowTypePartitioningEnum(std::move(data));
    case 1191:
      return new ::Ifc4x1::IfcWorkCalendar(std::move(data));
    case 1192:
      return new ::Ifc4x1::IfcWorkCalendarTypeEnum(std::move(data));
    case 1193:
      return new ::Ifc4x1::IfcWorkControl(std::move(data));
    case 1194:
      return new ::Ifc4x1::IfcWorkPlan(std::move(data));
    case 1195:
      return new ::Ifc4x1::IfcWorkPlanTypeEnum(std::move(data));
    case 1196:
      return new ::Ifc4x1::IfcWorkSchedule(std::move(data));
    case 1197:
      return new ::Ifc4x1::IfcWorkScheduleTypeEnum(std::move(data));
    case 1198:
      return new ::Ifc4x1::IfcWorkTime(std::move(data));
    case 1199:
      return new ::Ifc4x1::IfcZone(std::move(data));
    case 1200:
      return new ::Ifc4x1::IfcZShapeProfileDef(std::move(data));
    default:
      throw IfcParse::IfcException(decl->name() + " cannot be instantiated");
    }
  }
};

IfcParse::schema_definition *IFC4X1_populate_schema() {
  IFC4X1_types[0] = new type_declaration(
      strings[0], 0, new simple_type(simple_type::real_type));
  IFC4X1_types[1] = new type_declaration(
      strings[1], 1, new simple_type(simple_type::real_type));
  IFC4X1_types[3] =
      new enumeration_type(strings[2], 3,
                           {strings[3], strings[4], strings[5], strings[6],
                            strings[7], strings[8], strings[9]});
  IFC4X1_types[4] = new enumeration_type(
      strings[10], 4,
      {strings[11], strings[12], strings[13], strings[14], strings[15],
       strings[16], strings[17], strings[18], strings[19], strings[20],
       strings[21], strings[22], strings[23], strings[24], strings[25],
       strings[26], strings[27], strings[28], strings[29], strings[30],
       strings[31], strings[32], strings[33], strings[34], strings[35],
       strings[8],  strings[9]});
  IFC4X1_types[5] = new enumeration_type(
      strings[36], 5,
      {strings[37], strings[38], strings[39], strings[8], strings[9]});
  IFC4X1_types[11] =
      new enumeration_type(strings[40], 11,
                           {strings[41], strings[42], strings[43], strings[44],
                            strings[45], strings[8], strings[9]});
  IFC4X1_types[13] = new enumeration_type(
      strings[46], 13,
      {strings[47], strings[48], strings[49], strings[50], strings[8]});
  IFC4X1_types[20] = new enumeration_type(
      strings[51], 20,
      {strings[52], strings[53], strings[54], strings[8], strings[9]});
  IFC4X1_types[22] =
      new enumeration_type(strings[55], 22,
                           {strings[56], strings[57], strings[58], strings[59],
                            strings[8], strings[9]});
  IFC4X1_types[25] =
      new enumeration_type(strings[60], 25,
                           {strings[61], strings[62], strings[63], strings[64],
                            strings[65], strings[66], strings[67], strings[68],
                            strings[69], strings[8], strings[9]});
  IFC4X1_types[28] =
      new enumeration_type(strings[70], 28,
                           {strings[71], strings[72], strings[73], strings[74],
                            strings[75], strings[76], strings[8], strings[9]});
  IFC4X1_types[39] =
      new enumeration_type(strings[77], 39, {strings[8], strings[9]});
  IFC4X1_types[40] = new type_declaration(
      strings[78], 40, new simple_type(simple_type::real_type));
  IFC4X1_types[41] = new enumeration_type(
      strings[79], 41,
      {strings[80], strings[81], strings[82], strings[8], strings[9]});
  IFC4X1_types[42] =
      new enumeration_type(strings[83], 42,
                           {strings[84], strings[85], strings[86], strings[87],
                            strings[8], strings[9]});
  IFC4X1_types[43] = new type_declaration(
      strings[88], 43, new simple_type(simple_type::real_type));
  IFC4X1_types[55] = new type_declaration(
      strings[89], 55, new simple_type(simple_type::real_type));
  IFC4X1_types[56] = new type_declaration(
      strings[90], 56, new simple_type(simple_type::real_type));
  IFC4X1_types[57] = new enumeration_type(
      strings[91], 57, {strings[92], strings[93], strings[94], strings[95]});
  IFC4X1_types[58] = new enumeration_type(
      strings[96], 58, {strings[48], strings[97], strings[9]});
  IFC4X1_types[63] = new enumeration_type(
      strings[98], 63,
      {strings[99], strings[100], strings[101], strings[102], strings[103],
       strings[104], strings[105], strings[106], strings[107], strings[108],
       strings[109], strings[8], strings[9]});
  IFC4X1_types[97] =
      new enumeration_type(strings[110], 97,
                           {strings[111], strings[112], strings[113],
                            strings[114], strings[115], strings[116]});
  IFC4X1_types[100] = new enumeration_type(
      strings[117], 100,
      {strings[118], strings[119], strings[120], strings[121], strings[122],
       strings[123], strings[124], strings[125], strings[126], strings[127],
       strings[116]});
  IFC4X1_types[71] = new enumeration_type(
      strings[128], 71,
      {strings[129], strings[130], strings[131], strings[132], strings[133],
       strings[134], strings[8], strings[9]});
  IFC4X1_types[72] = new enumeration_type(
      strings[135], 72,
      {strings[136], strings[137], strings[138], strings[139], strings[140],
       strings[141], strings[142], strings[143], strings[144], strings[145]});
  IFC4X1_types[74] = new type_declaration(
      strings[146], 74, new simple_type(simple_type::binary_type));
  IFC4X1_types[79] = new enumeration_type(
      strings[147], 79, {strings[148], strings[149], strings[8], strings[9]});
  IFC4X1_types[80] = new type_declaration(
      strings[150], 80, new simple_type(simple_type::boolean_type));
  IFC4X1_types[83] = new enumeration_type(
      strings[151], 83, {strings[152], strings[153], strings[154]});
  IFC4X1_types[106] = new enumeration_type(
      strings[155], 106, {strings[156], strings[157], strings[8], strings[9]});
  IFC4X1_types[109] = new enumeration_type(
      strings[158], 109,
      {strings[159], strings[160], strings[161], strings[162], strings[163],
       strings[8], strings[9]});
  IFC4X1_types[113] = new enumeration_type(
      strings[164], 113,
      {strings[165], strings[166], strings[167], strings[168], strings[169],
       strings[23], strings[8], strings[9]});
  IFC4X1_types[116] =
      new enumeration_type(strings[170], 116, {strings[8], strings[9]});
  IFC4X1_types[119] =
      new enumeration_type(strings[171], 119,
                           {strings[172], strings[173], strings[174],
                            strings[175], strings[8], strings[9]});
  IFC4X1_types[122] =
      new enumeration_type(strings[176], 122,
                           {strings[177], strings[178], strings[179],
                            strings[180], strings[8], strings[9]});
  IFC4X1_types[125] = new enumeration_type(
      strings[181], 125,
      {strings[182], strings[183], strings[184], strings[185], strings[186],
       strings[8], strings[9]});
  IFC4X1_types[128] =
      new enumeration_type(strings[187], 128,
                           {strings[188], strings[189], strings[190],
                            strings[191], strings[8], strings[9]});
  IFC4X1_types[129] = new type_declaration(
      strings[192], 129, new simple_type(simple_type::integer_type));
  IFC4X1_types[140] = new enumeration_type(
      strings[193], 140,
      {strings[194], strings[195], strings[196], strings[197], strings[9]});
  IFC4X1_types[143] = new enumeration_type(
      strings[198], 143,
      {strings[199], strings[200], strings[201], strings[8], strings[9]});
  IFC4X1_types[146] =
      new enumeration_type(strings[202], 146, {strings[8], strings[9]});
  IFC4X1_types[160] = new enumeration_type(
      strings[203], 160,
      {strings[204], strings[205], strings[206], strings[207], strings[208],
       strings[209], strings[210], strings[8], strings[9]});
  IFC4X1_types[169] = new enumeration_type(
      strings[211], 169, {strings[212], strings[213], strings[8], strings[9]});
  IFC4X1_types[172] = new enumeration_type(
      strings[214], 172,
      {strings[215], strings[216], strings[4], strings[217], strings[218],
       strings[219], strings[220], strings[221], strings[222], strings[223],
       strings[224], strings[225], strings[8], strings[9]});
  IFC4X1_types[173] = new type_declaration(
      strings[226], 173,
      new aggregation_type(aggregation_type::array_type, 1, 2,
                           new simple_type(simple_type::real_type)));
  IFC4X1_types[176] =
      new enumeration_type(strings[227], 176, {strings[228], strings[229]});
  IFC4X1_types[181] = new type_declaration(
      strings[230], 181,
      new aggregation_type(aggregation_type::list_type, 3, 4,
                           new simple_type(simple_type::integer_type)));
  IFC4X1_types[184] = new enumeration_type(
      strings[231], 184,
      {strings[232], strings[233], strings[234], strings[235], strings[236],
       strings[237], strings[238], strings[239], strings[240], strings[241],
       strings[242], strings[243], strings[244], strings[245], strings[246],
       strings[8], strings[9]});
  IFC4X1_types[187] = new enumeration_type(
      strings[247], 187,
      {strings[199], strings[248], strings[200], strings[249], strings[250],
       strings[251], strings[252], strings[8], strings[9]});
  IFC4X1_types[195] = new enumeration_type(
      strings[253], 195,
      {strings[254], strings[255], strings[256], strings[9]});
  IFC4X1_types[198] = new enumeration_type(
      strings[257], 198,
      {strings[258], strings[259], strings[260], strings[8], strings[9]});
  IFC4X1_types[201] = new enumeration_type(
      strings[261], 201,
      {strings[262], strings[263], strings[264], strings[265], strings[266],
       strings[267], strings[268], strings[269], strings[8], strings[9]});
  IFC4X1_types[204] = new enumeration_type(
      strings[270], 204,
      {strings[271], strings[272], strings[273], strings[274], strings[275],
       strings[276], strings[277], strings[278], strings[279], strings[9],
       strings[8]});
  IFC4X1_types[207] = new enumeration_type(
      strings[280], 207, {strings[281], strings[282], strings[8], strings[9]});
  IFC4X1_types[211] = new type_declaration(
      strings[283], 211, new simple_type(simple_type::real_type));
  IFC4X1_types[216] = new enumeration_type(
      strings[284], 216,
      {strings[285], strings[286], strings[287], strings[288], strings[289],
       strings[8], strings[9]});
  IFC4X1_types[221] = new enumeration_type(
      strings[290], 221, {strings[291], strings[292], strings[8], strings[9]});
  IFC4X1_types[224] = new enumeration_type(
      strings[293], 224,
      {strings[294], strings[295], strings[296], strings[8], strings[9]});
  IFC4X1_types[229] =
      new enumeration_type(strings[297], 229, {strings[8], strings[9]});
  IFC4X1_types[231] = new enumeration_type(
      strings[298], 231,
      {strings[299], strings[300], strings[301], strings[302], strings[303],
       strings[304], strings[305], strings[8], strings[9]});
  IFC4X1_types[233] = new type_declaration(
      strings[306], 233, new simple_type(simple_type::number_type));
  IFC4X1_types[236] = new enumeration_type(
      strings[307], 236,
      {strings[308], strings[309], strings[310], strings[311], strings[312],
       strings[313], strings[156], strings[314], strings[315], strings[316],
       strings[8], strings[9]});
  IFC4X1_types[239] = new enumeration_type(
      strings[317], 239, {strings[47], strings[48], strings[8], strings[9]});
  IFC4X1_types[247] =
      new enumeration_type(strings[318], 247, {strings[8], strings[9]});
  IFC4X1_types[248] = new type_declaration(
      strings[319], 248, new simple_type(simple_type::real_type));
  IFC4X1_types[253] = new enumeration_type(
      strings[320], 253,
      {strings[321], strings[322], strings[323], strings[9]});
  IFC4X1_types[265] = new enumeration_type(
      strings[324], 265,
      {strings[325], strings[326], strings[327], strings[328], strings[329],
       strings[330], strings[331], strings[332], strings[333], strings[334],
       strings[335], strings[8], strings[9]});
  IFC4X1_types[266] = new enumeration_type(
      strings[336], 266,
      {strings[337], strings[338], strings[339], strings[8], strings[9]});
  IFC4X1_types[267] = new type_declaration(
      strings[340], 267, new simple_type(simple_type::string_type));
  IFC4X1_types[268] = new type_declaration(
      strings[341], 268, new simple_type(simple_type::string_type));
  IFC4X1_types[269] = new type_declaration(
      strings[342], 269, new simple_type(simple_type::integer_type));
  IFC4X1_types[270] = new type_declaration(
      strings[343], 270, new simple_type(simple_type::integer_type));
  IFC4X1_types[276] = new enumeration_type(
      strings[344], 276,
      {strings[345], strings[346], strings[347], strings[348], strings[349],
       strings[350], strings[351], strings[352], strings[353], strings[354],
       strings[355], strings[356], strings[357], strings[358], strings[359],
       strings[360], strings[361], strings[362], strings[363], strings[364],
       strings[365], strings[366], strings[367], strings[368], strings[369],
       strings[370], strings[371], strings[372], strings[373], strings[374],
       strings[375], strings[376], strings[377], strings[378], strings[379],
       strings[380], strings[381], strings[382], strings[383], strings[384],
       strings[385], strings[386], strings[387], strings[388], strings[389],
       strings[390], strings[391], strings[392], strings[393], strings[394],
       strings[395], strings[396], strings[8]});
  IFC4X1_types[277] = new type_declaration(
      strings[397], 277, new simple_type(simple_type::string_type));
  IFC4X1_types[279] = new type_declaration(
      strings[398], 279, new simple_type(simple_type::integer_type));
  IFC4X1_types[281] =
      new enumeration_type(strings[399], 281, {strings[400], strings[401]});
  IFC4X1_types[284] = new enumeration_type(
      strings[402], 284,
      {strings[403], strings[404], strings[405], strings[8], strings[9]});
  IFC4X1_types[288] = new enumeration_type(
      strings[406], 288,
      {strings[407], strings[408], strings[409], strings[410], strings[411],
       strings[412], strings[413], strings[414], strings[8], strings[9]});
  IFC4X1_types[297] =
      new enumeration_type(strings[415], 297,
                           {strings[416], strings[417], strings[418],
                            strings[419], strings[8], strings[9]});
  IFC4X1_types[299] = new enumeration_type(
      strings[420], 299,
      {strings[421], strings[422], strings[423], strings[424], strings[425],
       strings[426], strings[427], strings[428], strings[429], strings[430],
       strings[431], strings[432], strings[433], strings[434], strings[435],
       strings[436], strings[437], strings[438], strings[439], strings[274],
       strings[440], strings[441], strings[265], strings[266], strings[442],
       strings[443], strings[444], strings[445], strings[446], strings[447],
       strings[448], strings[449], strings[450], strings[451], strings[452],
       strings[108], strings[453], strings[454], strings[455], strings[456],
       strings[457], strings[458], strings[8],   strings[9]});
  IFC4X1_types[300] =
      new enumeration_type(strings[459], 300,
                           {strings[460], strings[461], strings[462],
                            strings[463], strings[8], strings[9]});
  IFC4X1_types[305] = new enumeration_type(
      strings[464], 305,
      {strings[465], strings[466], strings[467], strings[468], strings[9]});
  IFC4X1_types[308] = new enumeration_type(
      strings[469], 308,
      {strings[470], strings[471], strings[472], strings[473], strings[474],
       strings[475], strings[476], strings[8], strings[9]});
  IFC4X1_types[309] = new enumeration_type(
      strings[477], 309,
      {strings[478], strings[479], strings[480], strings[9]});
  IFC4X1_types[313] = new enumeration_type(
      strings[481], 313,
      {strings[482], strings[483], strings[484], strings[279], strings[485],
       strings[486], strings[278], strings[8], strings[9]});
  IFC4X1_types[314] = new enumeration_type(
      strings[487], 314,
      {strings[488], strings[489], strings[490], strings[491], strings[492],
       strings[493], strings[494], strings[495], strings[496], strings[497],
       strings[498], strings[499], strings[500], strings[501], strings[474],
       strings[475], strings[8], strings[9]});
  IFC4X1_types[316] = new enumeration_type(
      strings[502], 316,
      {strings[503], strings[504], strings[505], strings[8], strings[9]});
  IFC4X1_types[317] = new enumeration_type(
      strings[506], 317,
      {strings[488], strings[489], strings[490], strings[491], strings[492],
       strings[493], strings[494], strings[495], strings[496], strings[497],
       strings[498], strings[499], strings[500], strings[501], strings[474],
       strings[475], strings[507], strings[508], strings[8],   strings[9]});
  IFC4X1_types[318] = new type_declaration(
      strings[509], 318, new simple_type(simple_type::real_type));
  IFC4X1_types[323] = new enumeration_type(
      strings[510], 323,
      {strings[172], strings[182], strings[183], strings[184], strings[185],
       strings[511], strings[186], strings[8], strings[9]});
  IFC4X1_types[326] = new enumeration_type(
      strings[512], 326, {strings[513], strings[514], strings[8], strings[9]});
  IFC4X1_types[329] = new enumeration_type(
      strings[515], 329,
      {strings[516], strings[517], strings[518], strings[8], strings[9]});
  IFC4X1_types[330] = new type_declaration(
      strings[519], 330, new simple_type(simple_type::string_type));
  IFC4X1_types[331] = new type_declaration(
      strings[520], 331, new simple_type(simple_type::real_type));
  IFC4X1_types[337] = new enumeration_type(
      strings[521], 337,
      {strings[522], strings[523], strings[524], strings[525], strings[526],
       strings[527], strings[528], strings[529], strings[530], strings[531],
       strings[532], strings[533], strings[534], strings[535], strings[536],
       strings[537], strings[8], strings[9]});
  IFC4X1_types[338] = new type_declaration(
      strings[538], 338, new simple_type(simple_type::real_type));
  IFC4X1_types[339] = new type_declaration(
      strings[539], 339, new simple_type(simple_type::real_type));
  IFC4X1_types[340] = new type_declaration(
      strings[540], 340, new simple_type(simple_type::real_type));
  IFC4X1_types[341] = new type_declaration(
      strings[541], 341, new simple_type(simple_type::real_type));
  IFC4X1_types[344] =
      new enumeration_type(strings[542], 344,
                           {strings[543], strings[544], strings[545],
                            strings[546], strings[8], strings[9]});
  IFC4X1_types[347] = new enumeration_type(
      strings[547], 347,
      {strings[548], strings[549], strings[550], strings[551], strings[552],
       strings[8], strings[9]});
  IFC4X1_types[350] = new enumeration_type(
      strings[553], 350,
      {strings[554], strings[555], strings[556], strings[8], strings[9]});
  IFC4X1_types[353] = new enumeration_type(
      strings[557], 353,
      {strings[558], strings[559], strings[560], strings[561], strings[562],
       strings[8], strings[9]});
  IFC4X1_types[354] = new type_declaration(
      strings[563], 354, new simple_type(simple_type::real_type));
  IFC4X1_types[357] = new enumeration_type(
      strings[564], 357,
      {strings[565], strings[566], strings[567], strings[8], strings[9]});
  IFC4X1_types[358] = new type_declaration(
      strings[568], 358, new simple_type(simple_type::real_type));
  IFC4X1_types[363] = new enumeration_type(
      strings[569], 363,
      {strings[570], strings[571], strings[572], strings[573], strings[574],
       strings[575], strings[576], strings[577], strings[578], strings[8],
       strings[9]});
  IFC4X1_types[366] = new enumeration_type(
      strings[579], 366, {strings[159], strings[160], strings[161]});
  IFC4X1_types[373] = new type_declaration(
      strings[580], 373, new simple_type(simple_type::real_type));
  IFC4X1_types[376] = new enumeration_type(
      strings[581], 376, {strings[582], strings[583], strings[8], strings[9]});
  IFC4X1_types[379] = new enumeration_type(
      strings[584], 379,
      {strings[585], strings[586], strings[587], strings[588], strings[589],
       strings[590], strings[591], strings[592], strings[593], strings[8],
       strings[9]});
  IFC4X1_types[382] = new enumeration_type(
      strings[594], 382,
      {strings[595], strings[596], strings[597], strings[598], strings[599],
       strings[600], strings[8], strings[9]});
  IFC4X1_types[385] =
      new enumeration_type(strings[601], 385,
                           {strings[602], strings[603], strings[604],
                            strings[605], strings[8], strings[9]});
  IFC4X1_types[387] = new enumeration_type(
      strings[606], 387,
      {strings[607], strings[608], strings[609], strings[8], strings[9]});
  IFC4X1_types[396] =
      new enumeration_type(strings[610], 396,
                           {strings[611], strings[612], strings[613],
                            strings[614], strings[8], strings[9]});
  IFC4X1_types[410] = new enumeration_type(
      strings[615], 410,
      {strings[616], strings[617], strings[618], strings[619], strings[620],
       strings[621], strings[622], strings[8], strings[9]});
  IFC4X1_types[413] = new enumeration_type(
      strings[623], 413,
      {strings[624], strings[625], strings[626], strings[8], strings[9]});
  IFC4X1_types[423] = new enumeration_type(
      strings[627], 423,
      {strings[628], strings[629], strings[630], strings[631], strings[632],
       strings[633], strings[8], strings[9]});
  IFC4X1_types[426] = new enumeration_type(
      strings[634], 426,
      {strings[635], strings[636], strings[637], strings[638], strings[639],
       strings[8], strings[9]});
  IFC4X1_types[430] = new enumeration_type(
      strings[640], 430,
      {strings[641], strings[642], strings[643], strings[9]});
  IFC4X1_types[435] = new enumeration_type(
      strings[644], 435,
      {strings[645], strings[646], strings[647], strings[648], strings[649],
       strings[650], strings[651], strings[652], strings[8], strings[9]});
  IFC4X1_types[438] =
      new enumeration_type(strings[653], 438,
                           {strings[654], strings[655], strings[656],
                            strings[657], strings[8], strings[9]});
  IFC4X1_types[449] = new type_declaration(
      strings[658], 449, new simple_type(simple_type::string_type));
  IFC4X1_types[450] = new type_declaration(
      strings[659], 450, new simple_type(simple_type::string_type));
  IFC4X1_types[451] = new type_declaration(
      strings[660], 451, new simple_type(simple_type::string_type));
  IFC4X1_types[454] = new enumeration_type(
      strings[661], 454,
      {strings[662], strings[663], strings[664], strings[665], strings[666],
       strings[8], strings[9]});
  IFC4X1_types[455] = new type_declaration(
      strings[667], 455, new simple_type(simple_type::real_type));
  IFC4X1_types[456] = new type_declaration(
      strings[668], 456, new simple_type(simple_type::real_type));
  IFC4X1_types[461] = new enumeration_type(
      strings[669], 461,
      {strings[670], strings[671], strings[672], strings[673], strings[674],
       strings[675], strings[676], strings[8], strings[9]});
  IFC4X1_types[464] = new enumeration_type(
      strings[677], 464, {strings[678], strings[8], strings[9]});
  IFC4X1_types[466] = new enumeration_type(
      strings[679], 466,
      {strings[680], strings[681], strings[682], strings[683], strings[684],
       strings[685], strings[686], strings[8], strings[9]});
  IFC4X1_types[473] =
      new enumeration_type(strings[687], 473, {strings[688], strings[689]});
  IFC4X1_types[472] = new type_declaration(
      strings[690], 472, new simple_type(simple_type::string_type));
  IFC4X1_types[478] =
      new enumeration_type(strings[691], 478,
                           {strings[517], strings[692], strings[693],
                            strings[694], strings[8], strings[9]});
  IFC4X1_types[484] = new enumeration_type(
      strings[695], 484, {strings[696], strings[697], strings[8], strings[9]});
  IFC4X1_types[485] = new type_declaration(
      strings[698], 485, new simple_type(simple_type::real_type));
  IFC4X1_types[486] = new type_declaration(
      strings[699], 486, new simple_type(simple_type::real_type));
  IFC4X1_types[489] = new enumeration_type(
      strings[700], 489,
      {strings[701], strings[702], strings[703], strings[704], strings[705],
       strings[706], strings[707], strings[708], strings[709], strings[710],
       strings[711], strings[712], strings[713], strings[8], strings[9]});
  IFC4X1_types[490] = new type_declaration(
      strings[714], 490, new simple_type(simple_type::string_type));
  IFC4X1_types[491] = new type_declaration(
      strings[715], 491, new simple_type(simple_type::real_type));
  IFC4X1_types[499] = new type_declaration(
      strings[716], 499, new simple_type(simple_type::real_type));
  IFC4X1_types[500] = new type_declaration(
      strings[717], 500, new simple_type(simple_type::integer_type));
  IFC4X1_types[501] = new type_declaration(
      strings[718], 501, new simple_type(simple_type::integer_type));
  IFC4X1_types[504] =
      new enumeration_type(strings[719], 504,
                           {strings[720], strings[721], strings[444],
                            strings[722], strings[8], strings[9]});
  IFC4X1_types[505] =
      new enumeration_type(strings[723], 505,
                           {strings[724], strings[611], strings[612],
                            strings[613], strings[614], strings[9]});
  IFC4X1_types[508] = new enumeration_type(
      strings[725], 508,
      {strings[726], strings[727], strings[728], strings[8], strings[9]});
  IFC4X1_types[509] = new type_declaration(
      strings[729], 509, new simple_type(simple_type::real_type));
  IFC4X1_types[513] = new type_declaration(
      strings[730], 513, new simple_type(simple_type::real_type));
  IFC4X1_types[516] = new enumeration_type(
      strings[731], 516, {strings[430], strings[732], strings[8], strings[9]});
  IFC4X1_types[517] = new type_declaration(
      strings[733], 517, new simple_type(simple_type::real_type));
  IFC4X1_types[518] = new enumeration_type(
      strings[734], 518,
      {strings[735], strings[736], strings[737], strings[116]});
  IFC4X1_types[519] = new type_declaration(
      strings[738], 519, new simple_type(simple_type::string_type));
  IFC4X1_types[522] = new enumeration_type(
      strings[739], 522,
      {strings[740], strings[741], strings[742], strings[272], strings[273],
       strings[743], strings[744], strings[309], strings[745], strings[746],
       strings[747], strings[276], strings[748], strings[267], strings[749],
       strings[311], strings[750], strings[751], strings[752], strings[8],
       strings[9]});
  IFC4X1_types[526] = new enumeration_type(
      strings[753], 526,
      {strings[754], strings[755], strings[756], strings[757], strings[758],
       strings[759], strings[760], strings[761], strings[762], strings[8],
       strings[9]});
  IFC4X1_types[527] = new type_declaration(strings[763], 527,
                                           new named_type(IFC4X1_types[490]));
  IFC4X1_types[529] = new enumeration_type(
      strings[764], 529, {strings[765], strings[766], strings[767]});
  IFC4X1_types[530] = new type_declaration(
      strings[768], 530, new simple_type(simple_type::real_type));
  IFC4X1_types[534] = new enumeration_type(
      strings[769], 534,
      {strings[770], strings[771], strings[772], strings[9]});
  IFC4X1_types[537] = new enumeration_type(
      strings[773], 537,
      {strings[754], strings[755], strings[757], strings[758], strings[774],
       strings[775], strings[776], strings[777], strings[760], strings[762],
       strings[9]});
  IFC4X1_types[540] = new enumeration_type(
      strings[778], 540,
      {strings[779], strings[780], strings[781], strings[8], strings[9]});
  IFC4X1_types[549] = new type_declaration(
      strings[782], 549, new simple_type(simple_type::real_type));
  IFC4X1_types[550] = new type_declaration(
      strings[783], 550, new simple_type(simple_type::real_type));
  IFC4X1_types[553] = new type_declaration(
      strings[784], 553, new simple_type(simple_type::real_type));
  IFC4X1_types[554] = new type_declaration(
      strings[785], 554, new simple_type(simple_type::real_type));
  IFC4X1_types[557] = new enumeration_type(
      strings[786], 557,
      {strings[787], strings[788], strings[789], strings[8], strings[9]});
  IFC4X1_types[559] = new type_declaration(
      strings[790], 559, new simple_type(simple_type::logical_type));
  IFC4X1_types[560] = new enumeration_type(
      strings[791], 560,
      {strings[792], strings[793], strings[794], strings[795], strings[796]});
  IFC4X1_types[563] = new type_declaration(
      strings[797], 563, new simple_type(simple_type::real_type));
  IFC4X1_types[564] = new type_declaration(
      strings[798], 564, new simple_type(simple_type::real_type));
  IFC4X1_types[565] = new type_declaration(
      strings[799], 565, new simple_type(simple_type::real_type));
  IFC4X1_types[566] = new type_declaration(
      strings[800], 566, new simple_type(simple_type::real_type));
  IFC4X1_types[567] = new type_declaration(
      strings[801], 567, new simple_type(simple_type::real_type));
  IFC4X1_types[571] = new type_declaration(
      strings[802], 571, new simple_type(simple_type::real_type));
  IFC4X1_types[572] = new type_declaration(
      strings[803], 572, new simple_type(simple_type::real_type));
  IFC4X1_types[573] = new type_declaration(
      strings[804], 573, new simple_type(simple_type::real_type));
  IFC4X1_types[574] = new type_declaration(
      strings[805], 574, new simple_type(simple_type::real_type));
  IFC4X1_types[599] = new enumeration_type(
      strings[806], 599,
      {strings[807], strings[808], strings[809], strings[810], strings[811],
       strings[812], strings[813], strings[814], strings[815], strings[816],
       strings[8], strings[9]});
  IFC4X1_types[602] = new enumeration_type(
      strings[817], 602,
      {strings[818], strings[819], strings[820], strings[821], strings[822],
       strings[8], strings[9]});
  IFC4X1_types[606] = new enumeration_type(
      strings[823], 606,
      {strings[824], strings[825], strings[826], strings[827], strings[828],
       strings[696], strings[6], strings[829], strings[830], strings[831],
       strings[832], strings[833], strings[8], strings[9]});
  IFC4X1_types[610] = new type_declaration(
      strings[834], 610, new simple_type(simple_type::real_type));
  IFC4X1_types[611] = new type_declaration(
      strings[835], 611, new simple_type(simple_type::real_type));
  IFC4X1_types[612] = new type_declaration(
      strings[836], 612, new simple_type(simple_type::real_type));
  IFC4X1_types[613] =
      new select_type(strings[837], 613, {IFC4X1_types[80], IFC4X1_types[612]});
  IFC4X1_types[614] = new type_declaration(
      strings[838], 614, new simple_type(simple_type::real_type));
  IFC4X1_types[615] =
      new select_type(strings[839], 615, {IFC4X1_types[80], IFC4X1_types[614]});
  IFC4X1_types[616] =
      new select_type(strings[840], 616, {IFC4X1_types[80], IFC4X1_types[611]});
  IFC4X1_types[617] = new type_declaration(
      strings[841], 617, new simple_type(simple_type::real_type));
  IFC4X1_types[618] = new type_declaration(
      strings[842], 618, new simple_type(simple_type::real_type));
  IFC4X1_types[619] = new type_declaration(
      strings[843], 619, new simple_type(simple_type::real_type));
  IFC4X1_types[620] = new type_declaration(
      strings[844], 620, new simple_type(simple_type::real_type));
  IFC4X1_types[622] = new type_declaration(
      strings[845], 622, new simple_type(simple_type::integer_type));
  IFC4X1_types[625] = new enumeration_type(
      strings[846], 625,
      {strings[847], strings[848], strings[849], strings[8], strings[9]});
  IFC4X1_types[627] = new type_declaration(strings[850], 627,
                                           new named_type(IFC4X1_types[530]));
  IFC4X1_types[629] = new enumeration_type(strings[851], 629, {strings[852]});
  IFC4X1_types[630] = new type_declaration(
      strings[853], 630, new simple_type(simple_type::number_type));
  IFC4X1_types[637] = new enumeration_type(
      strings[854], 637,
      {strings[855], strings[856], strings[428], strings[857], strings[858],
       strings[859], strings[860], strings[9]});
  IFC4X1_types[634] = new enumeration_type(
      strings[861], 634,
      {strings[862], strings[863], strings[864], strings[611], strings[865],
       strings[866], strings[867], strings[868], strings[869], strings[870],
       strings[871], strings[8], strings[9]});
  IFC4X1_types[639] = new enumeration_type(
      strings[872], 639,
      {strings[873], strings[874], strings[875], strings[876], strings[877],
       strings[878], strings[879], strings[8], strings[9]});
  IFC4X1_types[645] = new enumeration_type(
      strings[880], 645, {strings[881], strings[882], strings[8], strings[9]});
  IFC4X1_types[655] = new enumeration_type(
      strings[883], 655,
      {strings[884], strings[885], strings[886], strings[887], strings[888],
       strings[8], strings[9]});
  IFC4X1_types[669] = new type_declaration(
      strings[889], 669, new simple_type(simple_type::real_type));
  IFC4X1_types[658] = new type_declaration(
      strings[890], 658, new simple_type(simple_type::real_type));
  IFC4X1_types[662] =
      new enumeration_type(strings[891], 662, {strings[8], strings[9]});
  IFC4X1_types[663] = new enumeration_type(
      strings[892], 663,
      {strings[893], strings[894], strings[895], strings[8], strings[9]});
  IFC4X1_types[666] = new enumeration_type(
      strings[896], 666,
      {strings[897], strings[898], strings[899], strings[8], strings[9]});
  IFC4X1_types[671] = new enumeration_type(
      strings[900], 671, {strings[901], strings[902], strings[9]});
  IFC4X1_types[675] =
      new enumeration_type(strings[903], 675,
                           {strings[904], strings[905], strings[906],
                            strings[907], strings[8], strings[9]});
  IFC4X1_types[677] = new enumeration_type(
      strings[908], 677,
      {strings[909], strings[910], strings[911], strings[912], strings[913],
       strings[914], strings[8], strings[9]});
  IFC4X1_types[680] = new enumeration_type(
      strings[915], 680,
      {strings[172], strings[182], strings[183], strings[184], strings[185],
       strings[511], strings[186], strings[8], strings[9]});
  IFC4X1_types[683] = new enumeration_type(
      strings[916], 683,
      {strings[917], strings[514], strings[513], strings[918], strings[919],
       strings[8], strings[9]});
  IFC4X1_types[688] = new type_declaration(
      strings[920], 688, new simple_type(simple_type::real_type));
  IFC4X1_types[690] = new type_declaration(
      strings[921], 690, new simple_type(simple_type::real_type));
  IFC4X1_types[694] = new enumeration_type(
      strings[922], 694, {strings[923], strings[924], strings[8], strings[9]});
  IFC4X1_types[705] = new type_declaration(strings[925], 705,
                                           new named_type(IFC4X1_types[500]));
  IFC4X1_types[706] = new type_declaration(strings[926], 706,
                                           new named_type(IFC4X1_types[530]));
  IFC4X1_types[707] = new type_declaration(strings[927], 707,
                                           new named_type(IFC4X1_types[690]));
  IFC4X1_types[710] = new type_declaration(
      strings[928], 710, new simple_type(simple_type::real_type));
  IFC4X1_types[717] = new enumeration_type(
      strings[929], 717, {strings[930], strings[931], strings[932]});
  IFC4X1_types[718] = new type_declaration(
      strings[933], 718, new simple_type(simple_type::string_type));
  IFC4X1_types[725] = new type_declaration(
      strings[934], 725, new simple_type(simple_type::real_type));
  IFC4X1_types[728] = new enumeration_type(
      strings[935], 728,
      {strings[936], strings[937], strings[938], strings[939], strings[940],
       strings[941], strings[942], strings[8], strings[9]});
  IFC4X1_types[738] =
      new enumeration_type(strings[943], 738, {strings[944], strings[945]});
  IFC4X1_types[746] = new enumeration_type(
      strings[946], 746,
      {strings[947], strings[948], strings[949], strings[950], strings[951],
       strings[8], strings[9]});
  IFC4X1_types[741] =
      new enumeration_type(strings[952], 741, {strings[953], strings[954]});
  IFC4X1_types[743] =
      new enumeration_type(strings[955], 743, {strings[8], strings[9]});
  IFC4X1_types[761] = new enumeration_type(
      strings[956], 761,
      {strings[957], strings[958], strings[959], strings[960], strings[961],
       strings[962], strings[963], strings[9]});
  IFC4X1_types[769] =
      new enumeration_type(strings[964], 769,
                           {strings[965], strings[966], strings[967],
                            strings[968], strings[8], strings[9]});
  IFC4X1_types[771] = new enumeration_type(
      strings[969], 771,
      {strings[970], strings[971], strings[972], strings[973], strings[974],
       strings[975], strings[976], strings[8], strings[9]});
  IFC4X1_types[775] = new enumeration_type(
      strings[977], 775,
      {strings[978], strings[979], strings[980], strings[981], strings[982],
       strings[983], strings[984], strings[8], strings[9]});
  IFC4X1_types[783] = new type_declaration(
      strings[985], 783, new simple_type(simple_type::real_type));
  IFC4X1_types[786] = new enumeration_type(
      strings[986], 786,
      {strings[987], strings[988], strings[989], strings[8], strings[9]});
  IFC4X1_types[790] = new enumeration_type(
      strings[990], 790, {strings[991], strings[992], strings[8], strings[9]});
  IFC4X1_types[792] = new enumeration_type(
      strings[993], 792,
      {strings[994], strings[995], strings[996], strings[997], strings[998],
       strings[999], strings[8], strings[9]});
  IFC4X1_types[793] = new type_declaration(
      strings[1000], 793, new simple_type(simple_type::real_type));
  IFC4X1_types[796] = new type_declaration(
      strings[1001], 796, new simple_type(simple_type::real_type));
  IFC4X1_types[802] = new enumeration_type(
      strings[1002], 802,
      {strings[1003], strings[1004], strings[1005], strings[1006],
       strings[1007], strings[1008], strings[1009], strings[1010]});
  IFC4X1_types[805] = new enumeration_type(
      strings[1011], 805,
      {strings[1012], strings[1013], strings[1014], strings[8], strings[9]});
  IFC4X1_types[806] = new enumeration_type(
      strings[1015], 806,
      {strings[1016], strings[1017], strings[1018], strings[1019], strings[277],
       strings[1020], strings[1021], strings[278], strings[1022], strings[9]});
  IFC4X1_types[811] = new enumeration_type(
      strings[1023], 811,
      {strings[1024], strings[1025], strings[1026], strings[833], strings[1027],
       strings[1028], strings[1029], strings[1030], strings[8], strings[9]});
  IFC4X1_types[812] =
      new enumeration_type(strings[1031], 812, {strings[1032], strings[1033]});
  IFC4X1_types[814] = new enumeration_type(
      strings[1034], 814,
      {strings[1030], strings[1028], strings[1026], strings[1024],
       strings[1027], strings[1029], strings[1025], strings[833], strings[8],
       strings[9]});
  IFC4X1_types[819] =
      new enumeration_type(strings[1035], 819, {strings[8], strings[9]});
  IFC4X1_types[884] = new enumeration_type(
      strings[1036], 884,
      {strings[1037], strings[1038], strings[1039], strings[1040],
       strings[1041], strings[1042], strings[1043], strings[1044],
       strings[1045], strings[1046], strings[1047], strings[1048],
       strings[1049], strings[1050], strings[1051], strings[1052],
       strings[1053], strings[878],  strings[1054], strings[1055],
       strings[1056], strings[1057], strings[8]});
  IFC4X1_types[887] = new enumeration_type(
      strings[1058], 887,
      {strings[1059], strings[1060], strings[1061], strings[1062],
       strings[1063], strings[1064], strings[1065], strings[1066],
       strings[1067], strings[1068], strings[1069], strings[1070],
       strings[1071], strings[8], strings[9]});
  IFC4X1_types[889] = new type_declaration(
      strings[1072], 889, new simple_type(simple_type::real_type));
  IFC4X1_types[890] = new type_declaration(
      strings[1073], 890, new simple_type(simple_type::real_type));
  IFC4X1_types[891] = new type_declaration(
      strings[1074], 891, new simple_type(simple_type::real_type));
  IFC4X1_types[892] = new select_type(strings[1075], 892,
                                      {IFC4X1_types[80], IFC4X1_types[891]});
  IFC4X1_types[925] = new enumeration_type(
      strings[1076], 925,
      {strings[1077], strings[1078], strings[1079], strings[1080],
       strings[1081], strings[1082], strings[1083], strings[1084],
       strings[1085], strings[1086], strings[1087], strings[1088],
       strings[1089], strings[1090], strings[1091], strings[1092]});
  IFC4X1_types[928] = new enumeration_type(
      strings[1093], 928,
      {strings[1094], strings[1095], strings[1096], strings[1097],
       strings[1098], strings[1099], strings[1100], strings[1101],
       strings[1102], strings[1103], strings[1104], strings[1105],
       strings[1106], strings[1107], strings[1108], strings[1109],
       strings[1110], strings[1111], strings[1112], strings[1113],
       strings[1114], strings[1115], strings[1116], strings[1117],
       strings[1118], strings[1119], strings[1120], strings[1121],
       strings[1122], strings[1123]});
  IFC4X1_types[896] = new enumeration_type(
      strings[1124], 896,
      {strings[1125], strings[1126], strings[1127], strings[1128], strings[642],
       strings[1129], strings[1130], strings[1131], strings[1132],
       strings[1133], strings[8], strings[9]});
  IFC4X1_types[903] = new type_declaration(
      strings[1134], 903, new simple_type(simple_type::real_type));
  IFC4X1_types[906] =
      new enumeration_type(strings[1135], 906, {strings[1136], strings[1137]});
  IFC4X1_types[899] = new type_declaration(
      strings[1138], 899, new simple_type(simple_type::real_type));
  IFC4X1_types[910] = new enumeration_type(
      strings[1139], 910,
      {strings[1140], strings[1141], strings[1142], strings[1143],
       strings[1144], strings[1145], strings[1146], strings[1147],
       strings[1148], strings[1149], strings[1150], strings[1151],
       strings[1152], strings[1153], strings[1154], strings[1155],
       strings[1156], strings[1157], strings[1158], strings[1159],
       strings[1160], strings[1161], strings[1162], strings[1163],
       strings[8],    strings[9]});
  IFC4X1_types[911] =
      new enumeration_type(strings[1164], 911,
                           {strings[1165], strings[1166], strings[1167],
                            strings[1168], strings[8], strings[9]});
  IFC4X1_types[914] = new enumeration_type(
      strings[1169], 914,
      {strings[1170], strings[1171], strings[1172], strings[8], strings[9]});
  IFC4X1_types[918] = new type_declaration(
      strings[1173], 918, new simple_type(simple_type::real_type));
  IFC4X1_types[923] = new enumeration_type(
      strings[1174], 923,
      {strings[1175], strings[1176], strings[1177], strings[1178],
       strings[1179], strings[1180], strings[1181], strings[1182],
       strings[1183], strings[1184], strings[1185], strings[1186]});
  IFC4X1_types[934] =
      new enumeration_type(strings[1187], 934,
                           {strings[1188], strings[1189], strings[1190],
                            strings[1191], strings[8], strings[9]});
  IFC4X1_types[938] = new enumeration_type(
      strings[1192], 938,
      {strings[1193], strings[1194], strings[8], strings[9]});
  IFC4X1_types[939] = new type_declaration(
      strings[1195], 939, new simple_type(simple_type::real_type));
  IFC4X1_types[942] = new type_declaration(
      strings[1196], 942, new simple_type(simple_type::real_type));
  IFC4X1_types[943] = new type_declaration(
      strings[1197], 943, new simple_type(simple_type::real_type));
  IFC4X1_types[944] = new type_declaration(
      strings[1198], 944, new simple_type(simple_type::real_type));
  IFC4X1_types[945] = new type_declaration(
      strings[1199], 945, new simple_type(simple_type::real_type));
  IFC4X1_types[950] = new enumeration_type(
      strings[1200], 950,
      {strings[1201], strings[1202], strings[8], strings[9]});
  IFC4X1_types[952] = new enumeration_type(
      strings[1203], 952,
      {strings[1204], strings[1205], strings[1206], strings[724], strings[611],
       strings[8], strings[9]});
  IFC4X1_types[959] = new enumeration_type(
      strings[1207], 959,
      {strings[1208], strings[1209], strings[266], strings[1210], strings[449],
       strings[968], strings[23], strings[456], strings[8], strings[9]});
  IFC4X1_types[960] = new type_declaration(
      strings[1211], 960, new simple_type(simple_type::real_type));
  IFC4X1_types[961] = new type_declaration(
      strings[1212], 961, new simple_type(simple_type::real_type));
  IFC4X1_types[963] = new type_declaration(
      strings[1213], 963, new simple_type(simple_type::real_type));
  IFC4X1_types[968] = new enumeration_type(
      strings[1214], 968,
      {strings[1215], strings[1216], strings[1217], strings[8], strings[9]});
  IFC4X1_types[972] = new enumeration_type(
      strings[1218], 972,
      {strings[991], strings[1219], strings[992], strings[1220], strings[1071],
       strings[8], strings[9]});
  IFC4X1_types[974] = new enumeration_type(
      strings[1221], 974,
      {strings[1222], strings[1223], strings[1224], strings[1225],
       strings[1226], strings[1227], strings[1228], strings[1229],
       strings[1230], strings[1231], strings[1232], strings[1233],
       strings[1234], strings[1235], strings[8], strings[9]});
  IFC4X1_types[975] =
      new enumeration_type(strings[1236], 975,
                           {strings[1237], strings[1238], strings[1239],
                            strings[1240], strings[1241]});
  IFC4X1_types[983] = new enumeration_type(
      strings[1242], 983,
      {strings[1243], strings[321], strings[1244], strings[1245], strings[1246],
       strings[1247], strings[1248], strings[8], strings[9]});
  IFC4X1_types[986] = new enumeration_type(
      strings[1249], 986,
      {strings[1250], strings[1251], strings[416], strings[1252], strings[1253],
       strings[8], strings[9]});
  IFC4X1_types[1012] =
      new enumeration_type(strings[1254], 1012,
                           {strings[1243], strings[1255], strings[1248],
                            strings[1256], strings[8], strings[9]});
  IFC4X1_types[1015] = new enumeration_type(
      strings[1257], 1015,
      {strings[1258], strings[1259], strings[1260], strings[8], strings[9]});
  IFC4X1_types[1024] = new enumeration_type(
      strings[1261], 1024,
      {strings[1262], strings[899], strings[8], strings[9]});
  IFC4X1_types[1030] = new enumeration_type(
      strings[1263], 1030,
      {strings[1264], strings[1265], strings[1266], strings[8], strings[9]});
  IFC4X1_types[1035] = new enumeration_type(
      strings[1267], 1035, {strings[400], strings[401], strings[1268]});
  IFC4X1_types[1050] = new enumeration_type(
      strings[1269], 1050,
      {strings[1270], strings[1271], strings[1272], strings[1273],
       strings[1274], strings[1275], strings[1276], strings[1277],
       strings[1278], strings[8], strings[9]});
  IFC4X1_types[1054] = new enumeration_type(
      strings[1279], 1054,
      {strings[1280], strings[1281], strings[8], strings[9]});
  IFC4X1_types[1060] = new enumeration_type(
      strings[1282], 1060,
      {strings[1283], strings[1284], strings[1285], strings[1286],
       strings[1287], strings[1288], strings[1289], strings[8], strings[9]});
  IFC4X1_types[1062] = new enumeration_type(
      strings[1290], 1062, {strings[1291], strings[1292], strings[9]});
  IFC4X1_types[1066] = new enumeration_type(
      strings[1293], 1066,
      {strings[1294], strings[1208], strings[1295], strings[1296], strings[431],
       strings[1297], strings[1298], strings[1299], strings[1300],
       strings[1301], strings[1302], strings[1303], strings[8], strings[9]});
  IFC4X1_types[1068] = new type_declaration(
      strings[1304], 1068, new simple_type(simple_type::real_type));
  IFC4X1_types[1069] = new type_declaration(
      strings[1305], 1069, new simple_type(simple_type::real_type));
  IFC4X1_types[1073] = new enumeration_type(
      strings[1306], 1073,
      {strings[1307], strings[1308], strings[1309], strings[8], strings[9]});
  IFC4X1_types[1075] =
      new enumeration_type(strings[1310], 1075,
                           {strings[1311], strings[1312], strings[1313],
                            strings[1314], strings[8], strings[9]});
  IFC4X1_types[1078] = new type_declaration(
      strings[1315], 1078, new simple_type(simple_type::string_type));
  IFC4X1_types[1079] = new type_declaration(
      strings[1316], 1079, new simple_type(simple_type::string_type));
  IFC4X1_types[1080] = new type_declaration(
      strings[1317], 1080, new simple_type(simple_type::string_type));
  IFC4X1_types[1081] = new type_declaration(
      strings[1318], 1081, new simple_type(simple_type::string_type));
  IFC4X1_types[1085] = new enumeration_type(
      strings[1319], 1085,
      {strings[478], strings[480], strings[1320], strings[1321]});
  IFC4X1_types[1090] = new type_declaration(
      strings[1322], 1090, new simple_type(simple_type::string_type));
  IFC4X1_types[1096] = new type_declaration(
      strings[1323], 1096, new simple_type(simple_type::real_type));
  IFC4X1_types[1097] = new type_declaration(
      strings[1324], 1097, new simple_type(simple_type::real_type));
  IFC4X1_types[1098] = new type_declaration(
      strings[1325], 1098, new simple_type(simple_type::real_type));
  IFC4X1_types[1099] = new type_declaration(
      strings[1326], 1099, new simple_type(simple_type::real_type));
  IFC4X1_types[1100] = new type_declaration(
      strings[1327], 1100, new simple_type(simple_type::real_type));
  IFC4X1_types[1101] = new type_declaration(
      strings[1328], 1101, new simple_type(simple_type::real_type));
  IFC4X1_types[1102] = new type_declaration(
      strings[1329], 1102, new simple_type(simple_type::string_type));
  IFC4X1_types[1103] = new type_declaration(
      strings[1330], 1103, new simple_type(simple_type::real_type));
  IFC4X1_types[1104] = new select_type(strings[1331], 1104,
                                       {IFC4X1_types[330], IFC4X1_types[793]});
  IFC4X1_types[1107] = new enumeration_type(
      strings[1332], 1107,
      {strings[1333], strings[1248], strings[1334], strings[1335],
       strings[1336], strings[1337], strings[9]});
  IFC4X1_types[1109] = new type_declaration(
      strings[1338], 1109, new simple_type(simple_type::integer_type));
  IFC4X1_types[1113] = new type_declaration(
      strings[1339], 1113, new simple_type(simple_type::real_type));
  IFC4X1_types[1116] = new enumeration_type(
      strings[1340], 1116,
      {strings[32], strings[1341], strings[1342], strings[1343], strings[1344],
       strings[8], strings[9]});
  IFC4X1_types[1117] = new enumeration_type(
      strings[1345], 1117,
      {strings[1346], strings[1333], strings[1347], strings[1348]});
  IFC4X1_types[1119] =
      new enumeration_type(strings[1349], 1119,
                           {strings[1350], strings[1351], strings[1352],
                            strings[1353], strings[1354], strings[1355]});
  IFC4X1_types[1120] = new select_type(strings[1356], 1120,
                                       {IFC4X1_types[80], IFC4X1_types[553]});
  IFC4X1_types[1123] = new enumeration_type(
      strings[1357], 1123,
      {strings[1358], strings[1359], strings[1360], strings[1361],
       strings[1362], strings[8], strings[9]});
  IFC4X1_types[1128] = new enumeration_type(
      strings[1363], 1128, {strings[1364], strings[868], strings[116]});
  IFC4X1_types[1133] = new enumeration_type(
      strings[1365], 1133, {strings[1366], strings[8], strings[9]});
  IFC4X1_types[1147] = new type_declaration(
      strings[1367], 1147, new simple_type(simple_type::string_type));
  IFC4X1_types[1146] = new enumeration_type(
      strings[1368], 1146,
      {strings[1369], strings[1370], strings[1371], strings[1372],
       strings[1373], strings[1374], strings[1375], strings[1376],
       strings[1377], strings[1378], strings[1379], strings[1380],
       strings[1381], strings[1382], strings[1383], strings[1384],
       strings[1385], strings[1386], strings[1387], strings[1388],
       strings[1389], strings[1390], strings[1391], strings[1392],
       strings[1393], strings[1394], strings[1395], strings[1396],
       strings[1397], strings[8]});
  IFC4X1_types[1141] = new enumeration_type(
      strings[1398], 1141,
      {strings[1399], strings[1400], strings[1401], strings[1402],
       strings[1403], strings[1404], strings[1405], strings[1406], strings[8],
       strings[9]});
  IFC4X1_types[1144] = new enumeration_type(
      strings[1407], 1144,
      {strings[1408], strings[1409], strings[1410], strings[1411],
       strings[1412], strings[8], strings[9]});
  IFC4X1_types[1152] = new enumeration_type(
      strings[1413], 1152,
      {strings[1414], strings[1415], strings[1416], strings[1417],
       strings[1418], strings[1419], strings[1420], strings[1421],
       strings[1422], strings[1423], strings[1424], strings[1425],
       strings[1426], strings[1427], strings[1428], strings[1429],
       strings[1430], strings[1431], strings[1432], strings[1433],
       strings[1434], strings[8],    strings[9]});
  IFC4X1_types[1153] = new type_declaration(
      strings[1435], 1153, new simple_type(simple_type::real_type));
  IFC4X1_types[1161] = new enumeration_type(
      strings[1436], 1161,
      {strings[1437], strings[1438], strings[8], strings[9]});
  IFC4X1_types[1165] = new enumeration_type(
      strings[1439], 1165,
      {strings[1440], strings[1441], strings[1442], strings[1443],
       strings[1444], strings[1028], strings[8], strings[9]});
  IFC4X1_types[1166] = new type_declaration(
      strings[1445], 1166, new simple_type(simple_type::real_type));
  IFC4X1_types[1167] = new type_declaration(
      strings[1446], 1167, new simple_type(simple_type::real_type));
  IFC4X1_types[1172] = new enumeration_type(
      strings[1447], 1172,
      {strings[1448], strings[1449], strings[1450], strings[1451],
       strings[1025], strings[1452], strings[1453], strings[1244],
       strings[1454], strings[8], strings[9]});
  IFC4X1_types[1173] = new type_declaration(
      strings[1455], 1173, new simple_type(simple_type::real_type));
  IFC4X1_types[1174] = new type_declaration(
      strings[1456], 1174, new simple_type(simple_type::real_type));
  IFC4X1_types[1175] = new select_type(strings[1457], 1175,
                                       {IFC4X1_types[80], IFC4X1_types[1174]});
  IFC4X1_types[1178] = new enumeration_type(
      strings[1458], 1178,
      {strings[1459], strings[1460], strings[1461], strings[1462],
       strings[1463], strings[1464], strings[1465], strings[8], strings[9]});
  IFC4X1_types[1181] = new enumeration_type(
      strings[1466], 1181,
      {strings[1467], strings[1468], strings[1469], strings[1470],
       strings[1471], strings[1472], strings[1473], strings[1474],
       strings[1475], strings[1476], strings[1477], strings[1478],
       strings[1479], strings[9]});
  IFC4X1_types[1182] =
      new enumeration_type(strings[1480], 1182,
                           {strings[478], strings[479], strings[480],
                            strings[1481], strings[1482], strings[9]});
  IFC4X1_types[1186] = new enumeration_type(
      strings[1483], 1186,
      {strings[482], strings[483], strings[484], strings[279], strings[485],
       strings[278], strings[1484], strings[9]});
  IFC4X1_types[1187] = new enumeration_type(
      strings[1485], 1187,
      {strings[1486], strings[1487], strings[1488], strings[1489],
       strings[1490], strings[1491], strings[1492], strings[1493],
       strings[1494], strings[8], strings[9]});
  IFC4X1_types[1189] = new enumeration_type(
      strings[1495], 1189,
      {strings[1496], strings[1497], strings[1498], strings[8], strings[9]});
  IFC4X1_types[1190] = new enumeration_type(
      strings[1499], 1190,
      {strings[1486], strings[1487], strings[1488], strings[1489],
       strings[1490], strings[1491], strings[1492], strings[1493],
       strings[1494], strings[8], strings[9]});
  IFC4X1_types[1192] = new enumeration_type(
      strings[1500], 1192,
      {strings[1501], strings[1502], strings[1503], strings[8], strings[9]});
  IFC4X1_types[1195] = new enumeration_type(
      strings[1504], 1195,
      {strings[1505], strings[1506], strings[1507], strings[8], strings[9]});
  IFC4X1_types[1197] = new enumeration_type(
      strings[1508], 1197,
      {strings[1505], strings[1506], strings[1507], strings[8], strings[9]});
  IFC4X1_types[7] = new entity(strings[1509], false, 7, (entity *)0);
  IFC4X1_types[12] = new entity(strings[1510], true, 12, (entity *)0);
  IFC4X1_types[46] = new entity(strings[1511], false, 46, (entity *)0);
  IFC4X1_types[47] = new entity(strings[1512], false, 47, (entity *)0);
  IFC4X1_types[49] = new entity(strings[1513], false, 49, (entity *)0);
  IFC4X1_types[85] = new entity(strings[1514], true, 85, (entity *)0);
  IFC4X1_types[87] =
      new entity(strings[1515], false, 87, (entity *)IFC4X1_types[85]);
  IFC4X1_types[88] =
      new entity(strings[1516], false, 88, (entity *)IFC4X1_types[85]);
  IFC4X1_types[89] =
      new entity(strings[1517], false, 89, (entity *)IFC4X1_types[85]);
  IFC4X1_types[90] =
      new entity(strings[1518], false, 90, (entity *)IFC4X1_types[89]);
  IFC4X1_types[191] = new entity(strings[1519], true, 191, (entity *)0);
  IFC4X1_types[193] =
      new entity(strings[1520], false, 193, (entity *)IFC4X1_types[191]);
  IFC4X1_types[194] =
      new entity(strings[1521], false, 194, (entity *)IFC4X1_types[191]);
  IFC4X1_types[196] =
      new entity(strings[1522], false, 196, (entity *)IFC4X1_types[191]);
  IFC4X1_types[197] = new entity(strings[1523], true, 197, (entity *)0);
  IFC4X1_types[225] = new entity(strings[1524], true, 225, (entity *)0);
  IFC4X1_types[226] = new entity(strings[1525], true, 226, (entity *)0);
  IFC4X1_types[232] =
      new entity(strings[1526], false, 232, (entity *)IFC4X1_types[47]);
  IFC4X1_types[274] = new entity(strings[1527], false, 274, (entity *)0);
  IFC4X1_types[275] = new entity(strings[1528], false, 275, (entity *)0);
  IFC4X1_types[278] = new entity(strings[1529], false, 278, (entity *)0);
  IFC4X1_types[389] = new entity(strings[1530], true, 389, (entity *)0);
  IFC4X1_types[393] = new entity(strings[1531], true, 393, (entity *)0);
  IFC4X1_types[390] =
      new entity(strings[1532], false, 390, (entity *)IFC4X1_types[393]);
  IFC4X1_types[391] =
      new entity(strings[1533], false, 391, (entity *)IFC4X1_types[393]);
  IFC4X1_types[392] =
      new entity(strings[1534], false, 392, (entity *)IFC4X1_types[393]);
  IFC4X1_types[475] = new entity(strings[1535], false, 475, (entity *)0);
  IFC4X1_types[511] = new entity(strings[1536], false, 511, (entity *)0);
  IFC4X1_types[531] =
      new entity(strings[1537], false, 531, (entity *)IFC4X1_types[389]);
  IFC4X1_types[532] =
      new entity(strings[1538], false, 532, (entity *)IFC4X1_types[393]);
  IFC4X1_types[535] = new entity(strings[1539], false, 535, (entity *)0);
  IFC4X1_types[541] = new entity(strings[1540], false, 541, (entity *)0);
  IFC4X1_types[569] =
      new entity(strings[1541], false, 569, (entity *)IFC4X1_types[225]);
  IFC4X1_types[576] = new entity(strings[1542], false, 576, (entity *)0);
  IFC4X1_types[579] = new entity(strings[1543], true, 579, (entity *)0);
  IFC4X1_types[581] =
      new entity(strings[1544], false, 581, (entity *)IFC4X1_types[579]);
  IFC4X1_types[582] =
      new entity(strings[1545], false, 582, (entity *)IFC4X1_types[579]);
  IFC4X1_types[584] =
      new entity(strings[1546], false, 584, (entity *)IFC4X1_types[581]);
  IFC4X1_types[585] = new entity(strings[1547], false, 585, (entity *)0);
  IFC4X1_types[586] =
      new entity(strings[1548], false, 586, (entity *)IFC4X1_types[579]);
  IFC4X1_types[587] =
      new entity(strings[1549], false, 587, (entity *)IFC4X1_types[579]);
  IFC4X1_types[590] =
      new entity(strings[1550], false, 590, (entity *)IFC4X1_types[586]);
  IFC4X1_types[594] = new entity(strings[1551], true, 594, (entity *)0);
  IFC4X1_types[596] = new entity(strings[1552], false, 596, (entity *)0);
  IFC4X1_types[607] =
      new entity(strings[1553], false, 607, (entity *)IFC4X1_types[197]);
  IFC4X1_types[621] = new entity(strings[1554], false, 621, (entity *)0);
  IFC4X1_types[626] = new entity(strings[1555], true, 626, (entity *)0);
  IFC4X1_types[635] = new entity(strings[1556], true, 635, (entity *)0);
  IFC4X1_types[633] =
      new entity(strings[1557], false, 633, (entity *)IFC4X1_types[197]);
  IFC4X1_types[648] = new entity(strings[1558], false, 648, (entity *)0);
  IFC4X1_types[656] = new entity(strings[1559], false, 656, (entity *)0);
  IFC4X1_types[667] = new entity(strings[1560], false, 667, (entity *)0);
  IFC4X1_types[668] = new entity(strings[1561], false, 668, (entity *)0);
  IFC4X1_types[672] = new entity(strings[1562], true, 672, (entity *)0);
  IFC4X1_types[673] =
      new entity(strings[1563], true, 673, (entity *)IFC4X1_types[672]);
  IFC4X1_types[709] =
      new entity(strings[1564], false, 709, (entity *)IFC4X1_types[12]);
  IFC4X1_types[719] = new entity(strings[1565], true, 719, (entity *)0);
  IFC4X1_types[720] = new entity(strings[1566], false, 720, (entity *)0);
  IFC4X1_types[721] =
      new entity(strings[1567], false, 721, (entity *)IFC4X1_types[720]);
  IFC4X1_types[722] = new entity(strings[1568], true, 722, (entity *)0);
  IFC4X1_types[723] = new entity(strings[1569], false, 723, (entity *)0);
  IFC4X1_types[733] = new entity(strings[1570], true, 733, (entity *)0);
  IFC4X1_types[736] = new entity(strings[1571], false, 736, (entity *)0);
  IFC4X1_types[740] =
      new entity(strings[1572], false, 740, (entity *)IFC4X1_types[226]);
  IFC4X1_types[748] = new entity(strings[1573], true, 748, (entity *)0);
  IFC4X1_types[753] =
      new entity(strings[1574], false, 753, (entity *)IFC4X1_types[748]);
  IFC4X1_types[776] =
      new entity(strings[1575], false, 776, (entity *)IFC4X1_types[673]);
  IFC4X1_types[777] =
      new entity(strings[1576], false, 777, (entity *)IFC4X1_types[673]);
  IFC4X1_types[778] =
      new entity(strings[1577], false, 778, (entity *)IFC4X1_types[673]);
  IFC4X1_types[780] =
      new entity(strings[1578], false, 780, (entity *)IFC4X1_types[673]);
  IFC4X1_types[781] =
      new entity(strings[1579], false, 781, (entity *)IFC4X1_types[673]);
  IFC4X1_types[782] =
      new entity(strings[1580], false, 782, (entity *)IFC4X1_types[673]);
  IFC4X1_types[801] = new entity(strings[1581], false, 801, (entity *)0);
  IFC4X1_types[803] = new entity(strings[1582], false, 803, (entity *)0);
  IFC4X1_types[869] = new entity(strings[1583], true, 869, (entity *)0);
  IFC4X1_types[870] = new entity(strings[1584], true, 870, (entity *)0);
  IFC4X1_types[871] = new entity(strings[1585], true, 871, (entity *)0);
  IFC4X1_types[872] = new entity(strings[1586], false, 872, (entity *)0);
  IFC4X1_types[876] = new entity(strings[1587], true, 876, (entity *)0);
  IFC4X1_types[888] = new entity(strings[1588], true, 888, (entity *)0);
  IFC4X1_types[927] =
      new entity(strings[1589], false, 927, (entity *)IFC4X1_types[626]);
  IFC4X1_types[897] = new entity(strings[1590], true, 897, (entity *)0);
  IFC4X1_types[915] = new entity(strings[1591], false, 915, (entity *)0);
  IFC4X1_types[916] =
      new entity(strings[1592], true, 916, (entity *)IFC4X1_types[869]);
  IFC4X1_types[917] =
      new entity(strings[1593], false, 917, (entity *)IFC4X1_types[916]);
  IFC4X1_types[981] = new entity(strings[1594], true, 981, (entity *)0);
  IFC4X1_types[991] = new entity(strings[1595], true, 991, (entity *)0);
  IFC4X1_types[993] =
      new entity(strings[1596], false, 993, (entity *)IFC4X1_types[991]);
  IFC4X1_types[996] =
      new entity(strings[1597], true, 996, (entity *)IFC4X1_types[991]);
  IFC4X1_types[1002] =
      new entity(strings[1598], true, 1002, (entity *)IFC4X1_types[996]);
  IFC4X1_types[1003] =
      new entity(strings[1599], false, 1003, (entity *)IFC4X1_types[1002]);
  IFC4X1_types[1021] =
      new entity(strings[1600], true, 1021, (entity *)IFC4X1_types[869]);
  IFC4X1_types[1019] =
      new entity(strings[1601], false, 1019, (entity *)IFC4X1_types[871]);
  IFC4X1_types[1020] =
      new entity(strings[1602], false, 1020, (entity *)IFC4X1_types[1021]);
  IFC4X1_types[1034] =
      new entity(strings[1603], false, 1034, (entity *)IFC4X1_types[996]);
  IFC4X1_types[1036] =
      new entity(strings[1604], false, 1036, (entity *)IFC4X1_types[722]);
  IFC4X1_types[1038] =
      new entity(strings[1605], false, 1038, (entity *)IFC4X1_types[719]);
  IFC4X1_types[1039] =
      new entity(strings[1606], false, 1039, (entity *)IFC4X1_types[719]);
  IFC4X1_types[1041] =
      new entity(strings[1607], false, 1041, (entity *)IFC4X1_types[719]);
  IFC4X1_types[1042] =
      new entity(strings[1608], false, 1042, (entity *)IFC4X1_types[719]);
  IFC4X1_types[1043] =
      new entity(strings[1609], true, 1043, (entity *)IFC4X1_types[719]);
  IFC4X1_types[1055] = new entity(strings[1610], false, 1055, (entity *)0);
  IFC4X1_types[1056] = new entity(strings[1611], false, 1056, (entity *)0);
  IFC4X1_types[1057] = new entity(strings[1612], false, 1057, (entity *)0);
  IFC4X1_types[1063] =
      new entity(strings[1613], false, 1063, (entity *)IFC4X1_types[897]);
  IFC4X1_types[1064] =
      new entity(strings[1614], false, 1064, (entity *)IFC4X1_types[1063]);
  IFC4X1_types[1067] =
      new entity(strings[1615], false, 1067, (entity *)IFC4X1_types[12]);
  IFC4X1_types[1086] =
      new entity(strings[1616], false, 1086, (entity *)IFC4X1_types[722]);
  IFC4X1_types[1088] =
      new entity(strings[1617], false, 1088, (entity *)IFC4X1_types[719]);
  IFC4X1_types[1089] =
      new entity(strings[1618], false, 1089, (entity *)IFC4X1_types[719]);
  IFC4X1_types[1091] =
      new entity(strings[1619], true, 1091, (entity *)IFC4X1_types[719]);
  IFC4X1_types[1092] =
      new entity(strings[1620], false, 1092, (entity *)IFC4X1_types[1091]);
  IFC4X1_types[1093] =
      new entity(strings[1621], false, 1093, (entity *)IFC4X1_types[1091]);
  IFC4X1_types[1094] =
      new entity(strings[1622], false, 1094, (entity *)IFC4X1_types[719]);
  IFC4X1_types[1095] =
      new entity(strings[1623], false, 1095, (entity *)IFC4X1_types[719]);
  IFC4X1_types[1105] = new entity(strings[1624], false, 1105, (entity *)0);
  IFC4X1_types[1106] = new entity(strings[1625], true, 1106, (entity *)0);
  IFC4X1_types[1108] = new entity(strings[1626], false, 1108, (entity *)0);
  IFC4X1_types[1110] =
      new entity(strings[1627], true, 1110, (entity *)IFC4X1_types[871]);
  IFC4X1_types[1111] =
      new entity(strings[1628], false, 1111, (entity *)IFC4X1_types[916]);
  IFC4X1_types[1145] = new entity(strings[1629], false, 1145, (entity *)0);
  IFC4X1_types[1156] =
      new entity(strings[1630], false, 1156, (entity *)IFC4X1_types[1110]);
  IFC4X1_types[1158] =
      new entity(strings[1631], false, 1158, (entity *)IFC4X1_types[1156]);
  IFC4X1_types[1163] = new entity(strings[1632], false, 1163, (entity *)0);
  IFC4X1_types[1198] =
      new entity(strings[1633], false, 1198, (entity *)IFC4X1_types[897]);
  IFC4X1_types[8] = new select_type(
      strings[1634], 8,
      {IFC4X1_types[648], IFC4X1_types[667], IFC4X1_types[668]});
  IFC4X1_types[54] = new type_declaration(
      strings[1635], 54,
      new aggregation_type(aggregation_type::list_type, 3, 3,
                           new named_type(IFC4X1_types[705])));
  IFC4X1_types[73] = new select_type(strings[1636], 73,
                                     {IFC4X1_types[530], IFC4X1_types[690]});
  IFC4X1_types[94] = new type_declaration(strings[1637], 94,
                                          new named_type(IFC4X1_types[519]));
  IFC4X1_types[272] = new select_type(
      strings[1638], 272,
      {IFC4X1_types[0],    IFC4X1_types[1],    IFC4X1_types[43],
       IFC4X1_types[55],   IFC4X1_types[181],  IFC4X1_types[248],
       IFC4X1_types[318],  IFC4X1_types[331],  IFC4X1_types[338],
       IFC4X1_types[339],  IFC4X1_types[340],  IFC4X1_types[354],
       IFC4X1_types[358],  IFC4X1_types[373],  IFC4X1_types[455],
       IFC4X1_types[456],  IFC4X1_types[485],  IFC4X1_types[486],
       IFC4X1_types[491],  IFC4X1_types[499],  IFC4X1_types[501],
       IFC4X1_types[509],  IFC4X1_types[513],  IFC4X1_types[517],
       IFC4X1_types[549],  IFC4X1_types[550],  IFC4X1_types[553],
       IFC4X1_types[554],  IFC4X1_types[563],  IFC4X1_types[564],
       IFC4X1_types[566],  IFC4X1_types[567],  IFC4X1_types[571],
       IFC4X1_types[572],  IFC4X1_types[574],  IFC4X1_types[610],
       IFC4X1_types[611],  IFC4X1_types[612],  IFC4X1_types[614],
       IFC4X1_types[617],  IFC4X1_types[618],  IFC4X1_types[619],
       IFC4X1_types[620],  IFC4X1_types[669],  IFC4X1_types[688],
       IFC4X1_types[710],  IFC4X1_types[725],  IFC4X1_types[783],
       IFC4X1_types[889],  IFC4X1_types[890],  IFC4X1_types[891],
       IFC4X1_types[903],  IFC4X1_types[899],  IFC4X1_types[918],
       IFC4X1_types[942],  IFC4X1_types[943],  IFC4X1_types[944],
       IFC4X1_types[945],  IFC4X1_types[960],  IFC4X1_types[1068],
       IFC4X1_types[1069], IFC4X1_types[1096], IFC4X1_types[1097],
       IFC4X1_types[1098], IFC4X1_types[1099], IFC4X1_types[1100],
       IFC4X1_types[1113], IFC4X1_types[1153], IFC4X1_types[1167],
       IFC4X1_types[1173], IFC4X1_types[1174]});
  IFC4X1_types[528] = new select_type(strings[1639], 528,
                                      {IFC4X1_types[869], IFC4X1_types[871]});
  IFC4X1_types[533] = new select_type(strings[1640], 533,
                                      {IFC4X1_types[531], IFC4X1_types[532]});
  IFC4X1_types[536] = new select_type(strings[1641], 536,
                                      {IFC4X1_types[393], IFC4X1_types[541]});
  IFC4X1_types[555] = new type_declaration(
      strings[1642], 555,
      new aggregation_type(aggregation_type::list_type, 2, -1,
                           new named_type(IFC4X1_types[705])));
  IFC4X1_types[593] = new select_type(
      strings[1643], 593,
      {IFC4X1_types[579], IFC4X1_types[585], IFC4X1_types[594]});
  IFC4X1_types[628] = new type_declaration(strings[1644], 628,
                                           new named_type(IFC4X1_types[793]));
  IFC4X1_types[636] = new select_type(
      strings[1645], 636,
      {IFC4X1_types[12], IFC4X1_types[47], IFC4X1_types[393], IFC4X1_types[579],
       IFC4X1_types[648], IFC4X1_types[667], IFC4X1_types[668],
       IFC4X1_types[1055], IFC4X1_types[1106]});
  IFC4X1_types[708] = new type_declaration(strings[1646], 708,
                                           new named_type(IFC4X1_types[793]));
  IFC4X1_types[907] = new select_type(strings[1647], 907,
                                      {IFC4X1_types[54], IFC4X1_types[555]});
  IFC4X1_types[924] =
      new select_type(strings[1648], 924,
                      {IFC4X1_types[74], IFC4X1_types[80], IFC4X1_types[267],
                       IFC4X1_types[268], IFC4X1_types[330], IFC4X1_types[490],
                       IFC4X1_types[500], IFC4X1_types[519], IFC4X1_types[559],
                       IFC4X1_types[705], IFC4X1_types[796], IFC4X1_types[1078],
                       IFC4X1_types[1102], IFC4X1_types[1109]});
  IFC4X1_types[929] = new select_type(strings[1649], 929,
                                      {IFC4X1_types[277], IFC4X1_types[530],
                                       IFC4X1_types[628], IFC4X1_types[706],
                                       IFC4X1_types[708], IFC4X1_types[793]});
  IFC4X1_types[962] = new select_type(strings[1650], 962,
                                      {IFC4X1_types[961], IFC4X1_types[963]});
  IFC4X1_types[1018] = new select_type(strings[1651], 1018,
                                       {IFC4X1_types[722], IFC4X1_types[723]});
  IFC4X1_types[1037] = new select_type(strings[1652], 1037,
                                       {IFC4X1_types[391], IFC4X1_types[1038],
                                        IFC4X1_types[1039], IFC4X1_types[1041],
                                        IFC4X1_types[1042]});
  IFC4X1_types[1138] = new select_type(
      strings[1653], 1138,
      {IFC4X1_types[274], IFC4X1_types[621], IFC4X1_types[626]});
  IFC4X1_types[50] =
      new entity(strings[1654], false, 50, (entity *)IFC4X1_types[876]);
  IFC4X1_types[51] =
      new entity(strings[1655], false, 51, (entity *)IFC4X1_types[736]);
  IFC4X1_types[52] =
      new entity(strings[1656], false, 52, (entity *)IFC4X1_types[736]);
  IFC4X1_types[53] =
      new entity(strings[1657], false, 53, (entity *)IFC4X1_types[51]);
  IFC4X1_types[75] =
      new entity(strings[1658], false, 75, (entity *)IFC4X1_types[1043]);
  IFC4X1_types[139] =
      new entity(strings[1659], false, 139, (entity *)IFC4X1_types[52]);
  IFC4X1_types[153] =
      new entity(strings[1660], false, 153, (entity *)IFC4X1_types[389]);
  IFC4X1_types[154] =
      new entity(strings[1661], false, 154, (entity *)IFC4X1_types[393]);
  IFC4X1_types[164] =
      new entity(strings[1662], false, 164, (entity *)IFC4X1_types[719]);
  IFC4X1_types[165] =
      new entity(strings[1663], true, 165, (entity *)IFC4X1_types[719]);
  IFC4X1_types[180] =
      new entity(strings[1664], false, 180, (entity *)IFC4X1_types[736]);
  IFC4X1_types[189] =
      new entity(strings[1665], false, 189, (entity *)IFC4X1_types[1110]);
  IFC4X1_types[190] =
      new entity(strings[1666], false, 190, (entity *)IFC4X1_types[191]);
  IFC4X1_types[192] =
      new entity(strings[1667], false, 192, (entity *)IFC4X1_types[193]);
  IFC4X1_types[212] =
      new entity(strings[1668], false, 212, (entity *)IFC4X1_types[626]);
  IFC4X1_types[217] =
      new entity(strings[1669], false, 217, (entity *)IFC4X1_types[626]);
  IFC4X1_types[218] =
      new entity(strings[1670], false, 218, (entity *)IFC4X1_types[217]);
  IFC4X1_types[244] =
      new entity(strings[1671], false, 244, (entity *)IFC4X1_types[876]);
  IFC4X1_types[257] =
      new entity(strings[1672], false, 257, (entity *)IFC4X1_types[722]);
  IFC4X1_types[258] =
      new entity(strings[1673], false, 258, (entity *)IFC4X1_types[719]);
  IFC4X1_types[259] =
      new entity(strings[1674], false, 259, (entity *)IFC4X1_types[719]);
  IFC4X1_types[260] =
      new entity(strings[1675], false, 260, (entity *)IFC4X1_types[719]);
  IFC4X1_types[273] =
      new entity(strings[1676], false, 273, (entity *)IFC4X1_types[736]);
  IFC4X1_types[301] =
      new entity(strings[1677], false, 301, (entity *)IFC4X1_types[389]);
  IFC4X1_types[302] =
      new entity(strings[1678], false, 302, (entity *)IFC4X1_types[876]);
  IFC4X1_types[303] =
      new entity(strings[1679], false, 303, (entity *)IFC4X1_types[393]);
  IFC4X1_types[332] =
      new entity(strings[1680], false, 332, (entity *)IFC4X1_types[1110]);
  IFC4X1_types[333] =
      new entity(strings[1681], false, 333, (entity *)IFC4X1_types[332]);
  IFC4X1_types[384] =
      new entity(strings[1682], false, 384, (entity *)IFC4X1_types[897]);
  IFC4X1_types[388] =
      new entity(strings[1683], true, 388, (entity *)IFC4X1_types[748]);
  IFC4X1_types[394] =
      new entity(strings[1684], false, 394, (entity *)IFC4X1_types[876]);
  IFC4X1_types[400] =
      new entity(strings[1685], false, 400, (entity *)IFC4X1_types[1110]);
  IFC4X1_types[402] =
      new entity(strings[1686], false, 402, (entity *)IFC4X1_types[1110]);
  IFC4X1_types[403] =
      new entity(strings[1687], false, 403, (entity *)IFC4X1_types[402]);
  IFC4X1_types[404] =
      new entity(strings[1688], false, 404, (entity *)IFC4X1_types[400]);
  IFC4X1_types[407] =
      new entity(strings[1689], false, 407, (entity *)IFC4X1_types[981]);
  IFC4X1_types[417] =
      new entity(strings[1690], false, 417, (entity *)IFC4X1_types[722]);
  IFC4X1_types[467] =
      new entity(strings[1691], false, 467, (entity *)IFC4X1_types[870]);
  IFC4X1_types[468] =
      new entity(strings[1692], true, 468, (entity *)IFC4X1_types[871]);
  IFC4X1_types[469] =
      new entity(strings[1693], false, 469, (entity *)IFC4X1_types[467]);
  IFC4X1_types[470] =
      new entity(strings[1694], false, 470, (entity *)IFC4X1_types[468]);
  IFC4X1_types[476] =
      new entity(strings[1695], false, 476, (entity *)IFC4X1_types[635]);
  IFC4X1_types[480] =
      new entity(strings[1696], false, 480, (entity *)IFC4X1_types[468]);
  IFC4X1_types[492] =
      new entity(strings[1697], false, 492, (entity *)IFC4X1_types[1043]);
  IFC4X1_types[493] =
      new entity(strings[1698], false, 493, (entity *)IFC4X1_types[719]);
  IFC4X1_types[497] =
      new entity(strings[1699], true, 497, (entity *)IFC4X1_types[1091]);
  IFC4X1_types[498] =
      new entity(strings[1700], false, 498, (entity *)IFC4X1_types[497]);
  IFC4X1_types[510] =
      new entity(strings[1701], false, 510, (entity *)IFC4X1_types[1106]);
  IFC4X1_types[523] =
      new entity(strings[1702], false, 523, (entity *)IFC4X1_types[897]);
  IFC4X1_types[542] =
      new entity(strings[1703], true, 542, (entity *)IFC4X1_types[468]);
  IFC4X1_types[543] =
      new entity(strings[1704], false, 543, (entity *)IFC4X1_types[542]);
  IFC4X1_types[544] =
      new entity(strings[1705], false, 544, (entity *)IFC4X1_types[542]);
  IFC4X1_types[545] =
      new entity(strings[1706], false, 545, (entity *)IFC4X1_types[542]);
  IFC4X1_types[546] =
      new entity(strings[1707], false, 546, (entity *)IFC4X1_types[542]);
  IFC4X1_types[547] =
      new entity(strings[1708], false, 547, (entity *)IFC4X1_types[546]);
  IFC4X1_types[551] =
      new entity(strings[1709], false, 551, (entity *)IFC4X1_types[635]);
  IFC4X1_types[558] =
      new entity(strings[1710], false, 558, (entity *)IFC4X1_types[635]);
  IFC4X1_types[561] =
      new entity(strings[1711], false, 561, (entity *)IFC4X1_types[1110]);
  IFC4X1_types[570] =
      new entity(strings[1712], false, 570, (entity *)IFC4X1_types[871]);
  IFC4X1_types[575] =
      new entity(strings[1713], false, 575, (entity *)IFC4X1_types[579]);
  IFC4X1_types[577] =
      new entity(strings[1714], false, 577, (entity *)IFC4X1_types[579]);
  IFC4X1_types[578] =
      new entity(strings[1715], false, 578, (entity *)IFC4X1_types[579]);
  IFC4X1_types[580] =
      new entity(strings[1716], false, 580, (entity *)IFC4X1_types[733]);
  IFC4X1_types[583] =
      new entity(strings[1717], false, 583, (entity *)IFC4X1_types[594]);
  IFC4X1_types[588] =
      new entity(strings[1718], false, 588, (entity *)IFC4X1_types[594]);
  IFC4X1_types[589] =
      new entity(strings[1719], false, 589, (entity *)IFC4X1_types[588]);
  IFC4X1_types[591] =
      new entity(strings[1720], false, 591, (entity *)IFC4X1_types[388]);
  IFC4X1_types[592] =
      new entity(strings[1721], false, 592, (entity *)IFC4X1_types[876]);
  IFC4X1_types[609] =
      new entity(strings[1722], false, 609, (entity *)IFC4X1_types[273]);
  IFC4X1_types[632] =
      new entity(strings[1723], true, 632, (entity *)IFC4X1_types[888]);
  IFC4X1_types[647] =
      new entity(strings[1724], false, 647, (entity *)IFC4X1_types[189]);
  IFC4X1_types[649] =
      new entity(strings[1725], false, 649, (entity *)IFC4X1_types[876]);
  IFC4X1_types[650] =
      new entity(strings[1726], false, 650, (entity *)IFC4X1_types[468]);
  IFC4X1_types[651] =
      new entity(strings[1727], false, 651, (entity *)IFC4X1_types[332]);
  IFC4X1_types[657] =
      new entity(strings[1728], true, 657, (entity *)IFC4X1_types[736]);
  IFC4X1_types[659] =
      new entity(strings[1729], false, 659, (entity *)IFC4X1_types[1110]);
  IFC4X1_types[670] =
      new entity(strings[1730], false, 670, (entity *)IFC4X1_types[672]);
  IFC4X1_types[684] =
      new entity(strings[1731], false, 684, (entity *)IFC4X1_types[1043]);
  IFC4X1_types[685] =
      new entity(strings[1732], true, 685, (entity *)IFC4X1_types[468]);
  IFC4X1_types[687] =
      new entity(strings[1733], false, 687, (entity *)IFC4X1_types[468]);
  IFC4X1_types[695] =
      new entity(strings[1734], true, 695, (entity *)IFC4X1_types[468]);
  IFC4X1_types[696] =
      new entity(strings[1735], false, 696, (entity *)IFC4X1_types[695]);
  IFC4X1_types[697] =
      new entity(strings[1736], false, 697, (entity *)IFC4X1_types[695]);
  IFC4X1_types[702] =
      new entity(strings[1737], false, 702, (entity *)IFC4X1_types[561]);
  IFC4X1_types[699] =
      new entity(strings[1738], false, 699, (entity *)IFC4X1_types[480]);
  IFC4X1_types[713] =
      new entity(strings[1739], true, 713, (entity *)IFC4X1_types[719]);
  IFC4X1_types[714] =
      new entity(strings[1740], true, 714, (entity *)IFC4X1_types[748]);
  IFC4X1_types[716] =
      new entity(strings[1741], true, 716, (entity *)IFC4X1_types[713]);
  IFC4X1_types[732] =
      new entity(strings[1742], false, 732, (entity *)IFC4X1_types[733]);
  IFC4X1_types[737] =
      new entity(strings[1743], false, 737, (entity *)IFC4X1_types[388]);
  IFC4X1_types[747] =
      new entity(strings[1744], true, 747, (entity *)IFC4X1_types[748]);
  IFC4X1_types[750] =
      new entity(strings[1745], true, 750, (entity *)IFC4X1_types[888]);
  IFC4X1_types[751] =
      new entity(strings[1746], false, 751, (entity *)IFC4X1_types[876]);
  IFC4X1_types[757] =
      new entity(strings[1747], true, 757, (entity *)IFC4X1_types[750]);
  IFC4X1_types[765] =
      new entity(strings[1748], true, 765, (entity *)IFC4X1_types[750]);
  IFC4X1_types[779] =
      new entity(strings[1749], true, 779, (entity *)IFC4X1_types[757]);
  IFC4X1_types[798] =
      new entity(strings[1750], false, 798, (entity *)IFC4X1_types[657]);
  IFC4X1_types[807] =
      new entity(strings[1751], false, 807, (entity *)IFC4X1_types[1106]);
  IFC4X1_types[808] =
      new entity(strings[1752], false, 808, (entity *)IFC4X1_types[714]);
  IFC4X1_types[836] =
      new entity(strings[1753], true, 836, (entity *)IFC4X1_types[888]);
  IFC4X1_types[874] =
      new entity(strings[1754], false, 874, (entity *)IFC4X1_types[876]);
  IFC4X1_types[875] =
      new entity(strings[1755], false, 875, (entity *)IFC4X1_types[876]);
  IFC4X1_types[879] =
      new entity(strings[1756], false, 879, (entity *)IFC4X1_types[897]);
  IFC4X1_types[893] =
      new entity(strings[1757], false, 893, (entity *)IFC4X1_types[798]);
  IFC4X1_types[904] =
      new entity(strings[1758], false, 904, (entity *)IFC4X1_types[714]);
  IFC4X1_types[905] =
      new entity(strings[1759], false, 905, (entity *)IFC4X1_types[714]);
  IFC4X1_types[902] =
      new entity(strings[1760], false, 902, (entity *)IFC4X1_types[468]);
  IFC4X1_types[920] =
      new entity(strings[1761], false, 920, (entity *)IFC4X1_types[468]);
  IFC4X1_types[921] =
      new entity(strings[1762], true, 921, (entity *)IFC4X1_types[747]);
  IFC4X1_types[935] =
      new entity(strings[1763], false, 935, (entity *)IFC4X1_types[981]);
  IFC4X1_types[940] =
      new entity(strings[1764], true, 940, (entity *)IFC4X1_types[468]);
  IFC4X1_types[995] =
      new entity(strings[1765], false, 995, (entity *)IFC4X1_types[1002]);
  IFC4X1_types[997] =
      new entity(strings[1766], false, 997, (entity *)IFC4X1_types[1002]);
  IFC4X1_types[998] =
      new entity(strings[1767], false, 998, (entity *)IFC4X1_types[1002]);
  IFC4X1_types[999] =
      new entity(strings[1768], false, 999, (entity *)IFC4X1_types[998]);
  IFC4X1_types[1000] =
      new entity(strings[1769], false, 1000, (entity *)IFC4X1_types[1002]);
  IFC4X1_types[1001] =
      new entity(strings[1770], false, 1001, (entity *)IFC4X1_types[1000]);
  IFC4X1_types[1025] =
      new entity(strings[1771], false, 1025, (entity *)IFC4X1_types[332]);
  IFC4X1_types[1026] =
      new entity(strings[1772], true, 1026, (entity *)IFC4X1_types[468]);
  IFC4X1_types[1040] =
      new entity(strings[1773], false, 1040, (entity *)IFC4X1_types[1041]);
  IFC4X1_types[1044] =
      new entity(strings[1774], true, 1044, (entity *)IFC4X1_types[940]);
  IFC4X1_types[1045] =
      new entity(strings[1775], false, 1045, (entity *)IFC4X1_types[940]);
  IFC4X1_types[1046] =
      new entity(strings[1776], false, 1046, (entity *)IFC4X1_types[1045]);
  IFC4X1_types[1047] =
      new entity(strings[1777], true, 1047, (entity *)IFC4X1_types[1026]);
  IFC4X1_types[1130] =
      new entity(strings[1778], false, 1130, (entity *)IFC4X1_types[657]);
  IFC4X1_types[1077] =
      new entity(strings[1779], true, 1077, (entity *)IFC4X1_types[468]);
  IFC4X1_types[1083] =
      new entity(strings[1780], false, 1083, (entity *)IFC4X1_types[468]);
  IFC4X1_types[1084] =
      new entity(strings[1781], false, 1084, (entity *)IFC4X1_types[1083]);
  IFC4X1_types[1087] =
      new entity(strings[1782], false, 1087, (entity *)IFC4X1_types[716]);
  IFC4X1_types[1124] =
      new entity(strings[1783], false, 1124, (entity *)IFC4X1_types[657]);
  IFC4X1_types[1134] =
      new entity(strings[1784], false, 1134, (entity *)IFC4X1_types[632]);
  IFC4X1_types[1135] =
      new entity(strings[1785], true, 1135, (entity *)IFC4X1_types[1134]);
  IFC4X1_types[1136] =
      new entity(strings[1786], false, 1136, (entity *)IFC4X1_types[1134]);
  IFC4X1_types[1137] =
      new entity(strings[1787], true, 1137, (entity *)IFC4X1_types[1134]);
  IFC4X1_types[1148] =
      new entity(strings[1788], false, 1148, (entity *)IFC4X1_types[657]);
  IFC4X1_types[1154] =
      new entity(strings[1789], false, 1154, (entity *)IFC4X1_types[468]);
  IFC4X1_types[1157] =
      new entity(strings[1790], false, 1157, (entity *)IFC4X1_types[561]);
  IFC4X1_types[1185] =
      new entity(strings[1791], false, 1185, (entity *)IFC4X1_types[1136]);
  IFC4X1_types[1200] =
      new entity(strings[1792], false, 1200, (entity *)IFC4X1_types[657]);
  IFC4X1_types[155] = new select_type(strings[1793], 155,
                                      {IFC4X1_types[153], IFC4X1_types[154]});
  IFC4X1_types[156] = new select_type(strings[1794], 156,
                                      {IFC4X1_types[153], IFC4X1_types[154]});
  IFC4X1_types[227] = new select_type(strings[1795], 227,
                                      {IFC4X1_types[226], IFC4X1_types[467]});
  IFC4X1_types[271] = new select_type(strings[1796], 271,
                                      {IFC4X1_types[632], IFC4X1_types[750]});
  IFC4X1_types[304] = new select_type(strings[1797], 304,
                                      {IFC4X1_types[301], IFC4X1_types[303]});
  IFC4X1_types[481] = new select_type(strings[1798], 481,
                                      {IFC4X1_types[706], IFC4X1_types[1154]});
  IFC4X1_types[595] = new select_type(
      strings[1799], 595,
      {IFC4X1_types[40],   IFC4X1_types[56],  IFC4X1_types[173],
       IFC4X1_types[211],  IFC4X1_types[233], IFC4X1_types[277],
       IFC4X1_types[341],  IFC4X1_types[530], IFC4X1_types[565],
       IFC4X1_types[573],  IFC4X1_types[627], IFC4X1_types[628],
       IFC4X1_types[630],  IFC4X1_types[658], IFC4X1_types[690],
       IFC4X1_types[706],  IFC4X1_types[707], IFC4X1_types[708],
       IFC4X1_types[793],  IFC4X1_types[939], IFC4X1_types[1101],
       IFC4X1_types[1103], IFC4X1_types[1166]});
  IFC4X1_types[698] = new select_type(strings[1800], 698,
                                      {IFC4X1_types[695], IFC4X1_types[1158]});
  IFC4X1_types[724] =
      new select_type(strings[1801], 724,
                      {IFC4X1_types[257], IFC4X1_types[417], IFC4X1_types[629],
                       IFC4X1_types[1036], IFC4X1_types[1086]});
  IFC4X1_types[734] = new select_type(strings[1802], 734,
                                      {IFC4X1_types[732], IFC4X1_types[872]});
  IFC4X1_types[759] = new type_declaration(
      strings[1803], 759,
      new aggregation_type(aggregation_type::set_type, 1, -1,
                           new named_type(IFC4X1_types[757])));
  IFC4X1_types[877] =
      new select_type(strings[1804], 877,
                      {IFC4X1_types[7], IFC4X1_types[47], IFC4X1_types[49],
                       IFC4X1_types[197], IFC4X1_types[212], IFC4X1_types[217],
                       IFC4X1_types[389], IFC4X1_types[393], IFC4X1_types[579],
                       IFC4X1_types[648], IFC4X1_types[667], IFC4X1_types[668],
                       IFC4X1_types[672], IFC4X1_types[736], IFC4X1_types[748],
                       IFC4X1_types[915], IFC4X1_types[1106]});
  IFC4X1_types[1082] = new select_type(strings[1805], 1082,
                                       {IFC4X1_types[392], IFC4X1_types[716]});
  IFC4X1_types[1149] = new select_type(
      strings[1806], 1149,
      {IFC4X1_types[272], IFC4X1_types[595], IFC4X1_types[924]});
  IFC4X1_types[16] =
      new entity(strings[1807], false, 16, (entity *)IFC4X1_types[404]);
  IFC4X1_types[30] =
      new entity(strings[1808], false, 30, (entity *)IFC4X1_types[468]);
  IFC4X1_types[32] =
      new entity(strings[1809], true, 32, (entity *)IFC4X1_types[468]);
  IFC4X1_types[36] =
      new entity(strings[1810], false, 36, (entity *)IFC4X1_types[468]);
  IFC4X1_types[37] =
      new entity(strings[1811], true, 37, (entity *)IFC4X1_types[32]);
  IFC4X1_types[45] =
      new entity(strings[1812], false, 45, (entity *)IFC4X1_types[468]);
  IFC4X1_types[60] =
      new entity(strings[1813], false, 60, (entity *)IFC4X1_types[657]);
  IFC4X1_types[64] =
      new entity(strings[1814], false, 64, (entity *)IFC4X1_types[685]);
  IFC4X1_types[66] =
      new entity(strings[1815], false, 66, (entity *)IFC4X1_types[685]);
  IFC4X1_types[67] =
      new entity(strings[1816], false, 67, (entity *)IFC4X1_types[685]);
  IFC4X1_types[84] =
      new entity(strings[1817], false, 84, (entity *)IFC4X1_types[468]);
  IFC4X1_types[92] =
      new entity(strings[1818], true, 92, (entity *)IFC4X1_types[1026]);
  IFC4X1_types[93] =
      new entity(strings[1819], false, 93, (entity *)IFC4X1_types[468]);
  IFC4X1_types[95] =
      new entity(strings[1820], false, 95, (entity *)IFC4X1_types[480]);
  IFC4X1_types[243] =
      new entity(strings[1821], false, 243, (entity *)IFC4X1_types[657]);
  IFC4X1_types[130] =
      new entity(strings[1822], false, 130, (entity *)IFC4X1_types[695]);
  IFC4X1_types[131] =
      new entity(strings[1823], true, 131, (entity *)IFC4X1_types[468]);
  IFC4X1_types[132] =
      new entity(strings[1824], false, 132, (entity *)IFC4X1_types[131]);
  IFC4X1_types[133] =
      new entity(strings[1825], false, 133, (entity *)IFC4X1_types[131]);
  IFC4X1_types[134] =
      new entity(strings[1826], true, 134, (entity *)IFC4X1_types[468]);
  IFC4X1_types[135] =
      new entity(strings[1827], false, 135, (entity *)IFC4X1_types[134]);
  IFC4X1_types[136] =
      new entity(strings[1828], false, 136, (entity *)IFC4X1_types[135]);
  IFC4X1_types[137] =
      new entity(strings[1829], false, 137, (entity *)IFC4X1_types[134]);
  IFC4X1_types[138] =
      new entity(strings[1830], false, 138, (entity *)IFC4X1_types[137]);
  IFC4X1_types[149] =
      new entity(strings[1831], false, 149, (entity *)IFC4X1_types[657]);
  IFC4X1_types[157] =
      new entity(strings[1832], false, 157, (entity *)IFC4X1_types[189]);
  IFC4X1_types[163] =
      new entity(strings[1833], false, 163, (entity *)IFC4X1_types[165]);
  IFC4X1_types[174] =
      new entity(strings[1834], false, 174, (entity *)IFC4X1_types[747]);
  IFC4X1_types[179] =
      new entity(strings[1835], false, 179, (entity *)IFC4X1_types[468]);
  IFC4X1_types[209] =
      new entity(strings[1836], true, 209, (entity *)IFC4X1_types[1137]);
  IFC4X1_types[210] =
      new entity(strings[1837], true, 210, (entity *)IFC4X1_types[632]);
  IFC4X1_types[238] =
      new entity(strings[1838], false, 238, (entity *)IFC4X1_types[209]);
  IFC4X1_types[240] =
      new entity(strings[1839], true, 240, (entity *)IFC4X1_types[468]);
  IFC4X1_types[242] =
      new entity(strings[1840], false, 242, (entity *)IFC4X1_types[940]);
  IFC4X1_types[249] =
      new entity(strings[1841], true, 249, (entity *)IFC4X1_types[468]);
  IFC4X1_types[250] =
      new entity(strings[1842], false, 250, (entity *)IFC4X1_types[92]);
  IFC4X1_types[251] =
      new entity(strings[1843], false, 251, (entity *)IFC4X1_types[92]);
  IFC4X1_types[280] =
      new entity(strings[1844], false, 280, (entity *)IFC4X1_types[468]);
  IFC4X1_types[285] =
      new entity(strings[1845], false, 285, (entity *)IFC4X1_types[468]);
  IFC4X1_types[312] =
      new entity(strings[1846], false, 312, (entity *)IFC4X1_types[1136]);
  IFC4X1_types[334] =
      new entity(strings[1847], false, 334, (entity *)IFC4X1_types[561]);
  IFC4X1_types[367] =
      new entity(strings[1848], false, 367, (entity *)IFC4X1_types[779]);
  IFC4X1_types[368] =
      new entity(strings[1849], true, 368, (entity *)IFC4X1_types[1136]);
  IFC4X1_types[360] =
      new entity(strings[1850], true, 360, (entity *)IFC4X1_types[1026]);
  IFC4X1_types[370] =
      new entity(strings[1851], false, 370, (entity *)IFC4X1_types[657]);
  IFC4X1_types[386] =
      new entity(strings[1852], false, 386, (entity *)IFC4X1_types[1135]);
  IFC4X1_types[398] =
      new entity(strings[1853], false, 398, (entity *)IFC4X1_types[1044]);
  IFC4X1_types[399] =
      new entity(strings[1854], false, 399, (entity *)IFC4X1_types[398]);
  IFC4X1_types[401] =
      new entity(strings[1855], false, 401, (entity *)IFC4X1_types[468]);
  IFC4X1_types[418] =
      new entity(strings[1856], false, 418, (entity *)IFC4X1_types[468]);
  IFC4X1_types[419] =
      new entity(strings[1857], false, 419, (entity *)IFC4X1_types[468]);
  IFC4X1_types[427] =
      new entity(strings[1858], false, 427, (entity *)IFC4X1_types[1044]);
  IFC4X1_types[458] =
      new entity(strings[1859], false, 458, (entity *)IFC4X1_types[368]);
  IFC4X1_types[460] =
      new entity(strings[1860], false, 460, (entity *)IFC4X1_types[458]);
  IFC4X1_types[463] =
      new entity(strings[1861], false, 463, (entity *)IFC4X1_types[368]);
  IFC4X1_types[465] =
      new entity(strings[1862], false, 465, (entity *)IFC4X1_types[470]);
  IFC4X1_types[512] =
      new entity(strings[1863], false, 512, (entity *)IFC4X1_types[657]);
  IFC4X1_types[495] =
      new entity(strings[1864], false, 495, (entity *)IFC4X1_types[1077]);
  IFC4X1_types[496] =
      new entity(strings[1865], false, 496, (entity *)IFC4X1_types[495]);
  IFC4X1_types[562] =
      new entity(strings[1866], false, 562, (entity *)IFC4X1_types[657]);
  IFC4X1_types[521] =
      new entity(strings[1867], false, 521, (entity *)IFC4X1_types[209]);
  IFC4X1_types[548] =
      new entity(strings[1868], false, 548, (entity *)IFC4X1_types[249]);
  IFC4X1_types[568] =
      new entity(strings[1869], true, 568, (entity *)IFC4X1_types[940]);
  IFC4X1_types[631] =
      new entity(strings[1870], true, 631, (entity *)IFC4X1_types[632]);
  IFC4X1_types[640] =
      new entity(strings[1871], true, 640, (entity *)IFC4X1_types[249]);
  IFC4X1_types[641] =
      new entity(strings[1872], false, 641, (entity *)IFC4X1_types[640]);
  IFC4X1_types[642] =
      new entity(strings[1873], false, 642, (entity *)IFC4X1_types[640]);
  IFC4X1_types[643] =
      new entity(strings[1874], false, 643, (entity *)IFC4X1_types[640]);
  IFC4X1_types[660] =
      new entity(strings[1875], false, 660, (entity *)IFC4X1_types[249]);
  IFC4X1_types[686] =
      new entity(strings[1876], false, 686, (entity *)IFC4X1_types[687]);
  IFC4X1_types[689] =
      new entity(strings[1877], false, 689, (entity *)IFC4X1_types[360]);
  IFC4X1_types[711] =
      new entity(strings[1878], true, 711, (entity *)IFC4X1_types[713]);
  IFC4X1_types[712] =
      new entity(strings[1879], true, 712, (entity *)IFC4X1_types[713]);
  IFC4X1_types[715] =
      new entity(strings[1880], true, 715, (entity *)IFC4X1_types[757]);
  IFC4X1_types[727] =
      new entity(strings[1881], false, 727, (entity *)IFC4X1_types[1135]);
  IFC4X1_types[729] =
      new entity(strings[1882], true, 729, (entity *)IFC4X1_types[631]);
  IFC4X1_types[731] =
      new entity(strings[1883], true, 731, (entity *)IFC4X1_types[631]);
  IFC4X1_types[739] =
      new entity(strings[1884], false, 739, (entity *)IFC4X1_types[210]);
  IFC4X1_types[744] =
      new entity(strings[1885], false, 744, (entity *)IFC4X1_types[210]);
  IFC4X1_types[749] =
      new entity(strings[1886], false, 749, (entity *)IFC4X1_types[921]);
  IFC4X1_types[752] =
      new entity(strings[1887], false, 752, (entity *)IFC4X1_types[921]);
  IFC4X1_types[754] =
      new entity(strings[1888], false, 754, (entity *)IFC4X1_types[921]);
  IFC4X1_types[755] =
      new entity(strings[1889], false, 755, (entity *)IFC4X1_types[921]);
  IFC4X1_types[756] =
      new entity(strings[1890], false, 756, (entity *)IFC4X1_types[757]);
  IFC4X1_types[760] =
      new entity(strings[1891], false, 760, (entity *)IFC4X1_types[765]);
  IFC4X1_types[762] =
      new entity(strings[1892], false, 762, (entity *)IFC4X1_types[921]);
  IFC4X1_types[763] =
      new entity(strings[1893], false, 763, (entity *)IFC4X1_types[921]);
  IFC4X1_types[764] =
      new entity(strings[1894], true, 764, (entity *)IFC4X1_types[765]);
  IFC4X1_types[772] =
      new entity(strings[1895], false, 772, (entity *)IFC4X1_types[731]);
  IFC4X1_types[797] =
      new entity(strings[1896], false, 797, (entity *)IFC4X1_types[798]);
  IFC4X1_types[799] =
      new entity(strings[1897], false, 799, (entity *)IFC4X1_types[240]);
  IFC4X1_types[800] =
      new entity(strings[1898], false, 800, (entity *)IFC4X1_types[92]);
  IFC4X1_types[809] =
      new entity(strings[1899], false, 809, (entity *)IFC4X1_types[715]);
  IFC4X1_types[821] =
      new entity(strings[1900], true, 821, (entity *)IFC4X1_types[836]);
  IFC4X1_types[822] =
      new entity(strings[1901], false, 822, (entity *)IFC4X1_types[821]);
  IFC4X1_types[823] =
      new entity(strings[1902], false, 823, (entity *)IFC4X1_types[821]);
  IFC4X1_types[824] =
      new entity(strings[1903], false, 824, (entity *)IFC4X1_types[821]);
  IFC4X1_types[825] =
      new entity(strings[1904], false, 825, (entity *)IFC4X1_types[824]);
  IFC4X1_types[826] =
      new entity(strings[1905], false, 826, (entity *)IFC4X1_types[821]);
  IFC4X1_types[827] =
      new entity(strings[1906], false, 827, (entity *)IFC4X1_types[821]);
  IFC4X1_types[828] =
      new entity(strings[1907], false, 828, (entity *)IFC4X1_types[821]);
  IFC4X1_types[829] =
      new entity(strings[1908], true, 829, (entity *)IFC4X1_types[836]);
  IFC4X1_types[830] =
      new entity(strings[1909], false, 830, (entity *)IFC4X1_types[829]);
  IFC4X1_types[831] =
      new entity(strings[1910], false, 831, (entity *)IFC4X1_types[829]);
  IFC4X1_types[832] =
      new entity(strings[1911], false, 832, (entity *)IFC4X1_types[829]);
  IFC4X1_types[833] =
      new entity(strings[1912], false, 833, (entity *)IFC4X1_types[829]);
  IFC4X1_types[834] =
      new entity(strings[1913], false, 834, (entity *)IFC4X1_types[829]);
  IFC4X1_types[835] =
      new entity(strings[1914], false, 835, (entity *)IFC4X1_types[829]);
  IFC4X1_types[837] =
      new entity(strings[1915], true, 837, (entity *)IFC4X1_types[836]);
  IFC4X1_types[838] =
      new entity(strings[1916], false, 838, (entity *)IFC4X1_types[837]);
  IFC4X1_types[839] =
      new entity(strings[1917], false, 839, (entity *)IFC4X1_types[838]);
  IFC4X1_types[841] =
      new entity(strings[1918], false, 841, (entity *)IFC4X1_types[837]);
  IFC4X1_types[840] =
      new entity(strings[1919], false, 840, (entity *)IFC4X1_types[837]);
  IFC4X1_types[842] =
      new entity(strings[1920], false, 842, (entity *)IFC4X1_types[837]);
  IFC4X1_types[843] =
      new entity(strings[1921], false, 843, (entity *)IFC4X1_types[837]);
  IFC4X1_types[844] =
      new entity(strings[1922], false, 844, (entity *)IFC4X1_types[843]);
  IFC4X1_types[845] =
      new entity(strings[1923], false, 845, (entity *)IFC4X1_types[838]);
  IFC4X1_types[846] =
      new entity(strings[1924], false, 846, (entity *)IFC4X1_types[837]);
  IFC4X1_types[847] =
      new entity(strings[1925], false, 847, (entity *)IFC4X1_types[837]);
  IFC4X1_types[848] =
      new entity(strings[1926], false, 848, (entity *)IFC4X1_types[837]);
  IFC4X1_types[849] =
      new entity(strings[1927], false, 849, (entity *)IFC4X1_types[836]);
  IFC4X1_types[850] =
      new entity(strings[1928], true, 850, (entity *)IFC4X1_types[836]);
  IFC4X1_types[851] =
      new entity(strings[1929], true, 851, (entity *)IFC4X1_types[836]);
  IFC4X1_types[852] =
      new entity(strings[1930], false, 852, (entity *)IFC4X1_types[851]);
  IFC4X1_types[853] =
      new entity(strings[1931], false, 853, (entity *)IFC4X1_types[851]);
  IFC4X1_types[854] =
      new entity(strings[1932], false, 854, (entity *)IFC4X1_types[851]);
  IFC4X1_types[855] =
      new entity(strings[1933], false, 855, (entity *)IFC4X1_types[851]);
  IFC4X1_types[856] =
      new entity(strings[1934], false, 856, (entity *)IFC4X1_types[837]);
  IFC4X1_types[857] =
      new entity(strings[1935], false, 857, (entity *)IFC4X1_types[837]);
  IFC4X1_types[858] =
      new entity(strings[1936], false, 858, (entity *)IFC4X1_types[837]);
  IFC4X1_types[859] =
      new entity(strings[1937], false, 859, (entity *)IFC4X1_types[850]);
  IFC4X1_types[860] =
      new entity(strings[1938], false, 860, (entity *)IFC4X1_types[850]);
  IFC4X1_types[861] =
      new entity(strings[1939], false, 861, (entity *)IFC4X1_types[837]);
  IFC4X1_types[862] =
      new entity(strings[1940], false, 862, (entity *)IFC4X1_types[837]);
  IFC4X1_types[863] =
      new entity(strings[1941], false, 863, (entity *)IFC4X1_types[837]);
  IFC4X1_types[864] =
      new entity(strings[1942], false, 864, (entity *)IFC4X1_types[837]);
  IFC4X1_types[865] =
      new entity(strings[1943], false, 865, (entity *)IFC4X1_types[864]);
  IFC4X1_types[866] =
      new entity(strings[1944], false, 866, (entity *)IFC4X1_types[865]);
  IFC4X1_types[867] =
      new entity(strings[1945], false, 867, (entity *)IFC4X1_types[850]);
  IFC4X1_types[868] =
      new entity(strings[1946], false, 868, (entity *)IFC4X1_types[179]);
  IFC4X1_types[873] =
      new entity(strings[1947], true, 873, (entity *)IFC4X1_types[631]);
  IFC4X1_types[880] =
      new entity(strings[1948], false, 880, (entity *)IFC4X1_types[1044]);
  IFC4X1_types[881] =
      new entity(strings[1949], false, 881, (entity *)IFC4X1_types[880]);
  IFC4X1_types[882] =
      new entity(strings[1950], false, 882, (entity *)IFC4X1_types[240]);
  IFC4X1_types[883] =
      new entity(strings[1951], false, 883, (entity *)IFC4X1_types[240]);
  IFC4X1_types[900] =
      new entity(strings[1952], true, 900, (entity *)IFC4X1_types[940]);
  IFC4X1_types[901] =
      new entity(strings[1953], false, 901, (entity *)IFC4X1_types[900]);
  IFC4X1_types[922] =
      new entity(strings[1954], false, 922, (entity *)IFC4X1_types[764]);
  IFC4X1_types[953] =
      new entity(strings[1955], true, 953, (entity *)IFC4X1_types[731]);
  IFC4X1_types[954] =
      new entity(strings[1956], true, 954, (entity *)IFC4X1_types[1136]);
  IFC4X1_types[955] =
      new entity(strings[1957], true, 955, (entity *)IFC4X1_types[953]);
  IFC4X1_types[956] =
      new entity(strings[1958], true, 956, (entity *)IFC4X1_types[954]);
  IFC4X1_types[957] =
      new entity(strings[1959], false, 957, (entity *)IFC4X1_types[953]);
  IFC4X1_types[958] =
      new entity(strings[1960], false, 958, (entity *)IFC4X1_types[954]);
  IFC4X1_types[964] =
      new entity(strings[1961], false, 964, (entity *)IFC4X1_types[240]);
  IFC4X1_types[965] =
      new entity(strings[1962], false, 965, (entity *)IFC4X1_types[360]);
  IFC4X1_types[977] =
      new entity(strings[1963], true, 977, (entity *)IFC4X1_types[731]);
  IFC4X1_types[989] =
      new entity(strings[1964], true, 989, (entity *)IFC4X1_types[731]);
  IFC4X1_types[1004] =
      new entity(strings[1965], true, 1004, (entity *)IFC4X1_types[989]);
  IFC4X1_types[1009] =
      new entity(strings[1966], true, 1009, (entity *)IFC4X1_types[977]);
  IFC4X1_types[1014] =
      new entity(strings[1967], false, 1014, (entity *)IFC4X1_types[1004]);
  IFC4X1_types[1016] =
      new entity(strings[1968], false, 1016, (entity *)IFC4X1_types[1014]);
  IFC4X1_types[1017] =
      new entity(strings[1969], false, 1017, (entity *)IFC4X1_types[1009]);
  IFC4X1_types[1023] =
      new entity(strings[1970], false, 1023, (entity *)IFC4X1_types[209]);
  IFC4X1_types[1027] =
      new entity(strings[1971], false, 1027, (entity *)IFC4X1_types[249]);
  IFC4X1_types[1028] =
      new entity(strings[1972], false, 1028, (entity *)IFC4X1_types[1044]);
  IFC4X1_types[1031] =
      new entity(strings[1973], false, 1031, (entity *)IFC4X1_types[1047]);
  IFC4X1_types[1032] =
      new entity(strings[1974], false, 1032, (entity *)IFC4X1_types[1047]);
  IFC4X1_types[1053] =
      new entity(strings[1975], false, 1053, (entity *)IFC4X1_types[458]);
  IFC4X1_types[1061] =
      new entity(strings[1976], false, 1061, (entity *)IFC4X1_types[729]);
  IFC4X1_types[1065] =
      new entity(strings[1977], false, 1065, (entity *)IFC4X1_types[1135]);
  IFC4X1_types[1076] =
      new entity(strings[1978], true, 1076, (entity *)IFC4X1_types[1077]);
  IFC4X1_types[1112] =
      new entity(strings[1979], false, 1112, (entity *)IFC4X1_types[360]);
  IFC4X1_types[1122] =
      new entity(strings[1980], false, 1122, (entity *)IFC4X1_types[368]);
  IFC4X1_types[1125] =
      new entity(strings[1981], false, 1125, (entity *)IFC4X1_types[1076]);
  IFC4X1_types[1126] =
      new entity(strings[1982], false, 1126, (entity *)IFC4X1_types[1125]);
  IFC4X1_types[1180] =
      new entity(strings[1983], false, 1180, (entity *)IFC4X1_types[715]);
  IFC4X1_types[1183] =
      new entity(strings[1984], false, 1183, (entity *)IFC4X1_types[715]);
  IFC4X1_types[48] = new select_type(
      strings[1985], 48,
      {IFC4X1_types[596], IFC4X1_types[803], IFC4X1_types[1149]});
  IFC4X1_types[65] =
      new select_type(strings[1986], 65, {IFC4X1_types[66], IFC4X1_types[67]});
  IFC4X1_types[82] =
      new select_type(strings[1987], 82,
                      {IFC4X1_types[84], IFC4X1_types[240], IFC4X1_types[480],
                       IFC4X1_types[940], IFC4X1_types[1076]});
  IFC4X1_types[161] = new select_type(strings[1988], 161,
                                      {IFC4X1_types[165], IFC4X1_types[711]});
  IFC4X1_types[162] = new select_type(strings[1989], 162,
                                      {IFC4X1_types[163], IFC4X1_types[628]});
  IFC4X1_types[241] = new select_type(strings[1990], 241,
                                      {IFC4X1_types[84], IFC4X1_types[240]});
  IFC4X1_types[261] = new select_type(strings[1991], 261,
                                      {IFC4X1_types[258], IFC4X1_types[712]});
  IFC4X1_types[420] = new select_type(strings[1992], 420,
                                      {IFC4X1_types[161], IFC4X1_types[390],
                                       IFC4X1_types[418], IFC4X1_types[419]});
  IFC4X1_types[471] = new select_type(
      strings[1993], 471,
      {IFC4X1_types[249], IFC4X1_types[695], IFC4X1_types[1026]});
  IFC4X1_types[477] = new select_type(strings[1994], 477,
                                      {IFC4X1_types[280], IFC4X1_types[1163]});
  IFC4X1_types[608] = new select_type(strings[1995], 608,
                                      {IFC4X1_types[47], IFC4X1_types[596],
                                       IFC4X1_types[803], IFC4X1_types[1055],
                                       IFC4X1_types[1106], IFC4X1_types[1149]});
  IFC4X1_types[730] = new select_type(strings[1996], 730,
                                      {IFC4X1_types[729], IFC4X1_types[1135]});
  IFC4X1_types[735] = new select_type(strings[1997], 735,
                                      {IFC4X1_types[731], IFC4X1_types[1136]});
  IFC4X1_types[758] = new select_type(strings[1998], 758,
                                      {IFC4X1_types[757], IFC4X1_types[759]});
  IFC4X1_types[878] = new select_type(strings[1999], 878,
                                      {IFC4X1_types[873], IFC4X1_types[1137]});
  IFC4X1_types[919] = new select_type(strings[2000], 919,
                                      {IFC4X1_types[157], IFC4X1_types[647]});
  IFC4X1_types[941] = new select_type(strings[2001], 941,
                                      {IFC4X1_types[157], IFC4X1_types[940]});
  IFC4X1_types[1033] = new select_type(
      strings[2002], 1033,
      {IFC4X1_types[401], IFC4X1_types[404], IFC4X1_types[1026]});
  IFC4X1_types[1129] = new select_type(strings[2003], 1129,
                                       {IFC4X1_types[130], IFC4X1_types[658]});
  IFC4X1_types[1155] = new select_type(strings[2004], 1155,
                                       {IFC4X1_types[280], IFC4X1_types[1154]});
  IFC4X1_types[6] =
      new entity(strings[2005], false, 6, (entity *)IFC4X1_types[631]);
  IFC4X1_types[14] =
      new entity(strings[2006], false, 14, (entity *)IFC4X1_types[568]);
  IFC4X1_types[15] =
      new entity(strings[2007], false, 15, (entity *)IFC4X1_types[14]);
  IFC4X1_types[31] =
      new entity(strings[2008], false, 31, (entity *)IFC4X1_types[32]);
  IFC4X1_types[33] =
      new entity(strings[2009], false, 33, (entity *)IFC4X1_types[37]);
  IFC4X1_types[34] =
      new entity(strings[2010], false, 34, (entity *)IFC4X1_types[37]);
  IFC4X1_types[35] =
      new entity(strings[2011], false, 35, (entity *)IFC4X1_types[37]);
  IFC4X1_types[44] =
      new entity(strings[2012], false, 44, (entity *)IFC4X1_types[731]);
  IFC4X1_types[99] =
      new entity(strings[2013], true, 99, (entity *)IFC4X1_types[92]);
  IFC4X1_types[101] =
      new entity(strings[2014], false, 101, (entity *)IFC4X1_types[99]);
  IFC4X1_types[76] =
      new entity(strings[2015], false, 76, (entity *)IFC4X1_types[240]);
  IFC4X1_types[81] =
      new entity(strings[2016], false, 81, (entity *)IFC4X1_types[84]);
  IFC4X1_types[91] =
      new entity(strings[2017], true, 91, (entity *)IFC4X1_types[249]);
  IFC4X1_types[102] =
      new entity(strings[2018], false, 102, (entity *)IFC4X1_types[955]);
  IFC4X1_types[110] =
      new entity(strings[2019], true, 110, (entity *)IFC4X1_types[368]);
  IFC4X1_types[111] =
      new entity(strings[2020], false, 111, (entity *)IFC4X1_types[955]);
  IFC4X1_types[145] =
      new entity(strings[2021], false, 145, (entity *)IFC4X1_types[110]);
  IFC4X1_types[148] =
      new entity(strings[2022], false, 148, (entity *)IFC4X1_types[149]);
  IFC4X1_types[152] =
      new entity(strings[2023], false, 152, (entity *)IFC4X1_types[368]);
  IFC4X1_types[168] =
      new entity(strings[2024], false, 168, (entity *)IFC4X1_types[110]);
  IFC4X1_types[175] =
      new entity(strings[2025], false, 175, (entity *)IFC4X1_types[764]);
  IFC4X1_types[177] =
      new entity(strings[2026], false, 177, (entity *)IFC4X1_types[91]);
  IFC4X1_types[178] =
      new entity(strings[2027], false, 178, (entity *)IFC4X1_types[177]);
  IFC4X1_types[188] =
      new entity(strings[2028], true, 188, (entity *)IFC4X1_types[249]);
  IFC4X1_types[200] =
      new entity(strings[2029], false, 200, (entity *)IFC4X1_types[209]);
  IFC4X1_types[203] =
      new entity(strings[2030], false, 203, (entity *)IFC4X1_types[209]);
  IFC4X1_types[206] =
      new entity(strings[2031], false, 206, (entity *)IFC4X1_types[209]);
  IFC4X1_types[208] =
      new entity(strings[2032], true, 208, (entity *)IFC4X1_types[873]);
  IFC4X1_types[213] =
      new entity(strings[2033], true, 213, (entity *)IFC4X1_types[631]);
  IFC4X1_types[228] =
      new entity(strings[2034], false, 228, (entity *)IFC4X1_types[213]);
  IFC4X1_types[230] =
      new entity(strings[2035], false, 230, (entity *)IFC4X1_types[213]);
  IFC4X1_types[235] =
      new entity(strings[2036], false, 235, (entity *)IFC4X1_types[110]);
  IFC4X1_types[237] =
      new entity(strings[2037], false, 237, (entity *)IFC4X1_types[208]);
  IFC4X1_types[246] =
      new entity(strings[2038], false, 246, (entity *)IFC4X1_types[110]);
  IFC4X1_types[256] =
      new entity(strings[2039], true, 256, (entity *)IFC4X1_types[91]);
  IFC4X1_types[262] =
      new entity(strings[2040], false, 262, (entity *)IFC4X1_types[360]);
  IFC4X1_types[293] =
      new entity(strings[2041], false, 293, (entity *)IFC4X1_types[368]);
  IFC4X1_types[295] =
      new entity(strings[2042], true, 295, (entity *)IFC4X1_types[293]);
  IFC4X1_types[307] =
      new entity(strings[2043], false, 307, (entity *)IFC4X1_types[715]);
  IFC4X1_types[310] =
      new entity(strings[2044], false, 310, (entity *)IFC4X1_types[715]);
  IFC4X1_types[315] =
      new entity(strings[2045], false, 315, (entity *)IFC4X1_types[110]);
  IFC4X1_types[319] =
      new entity(strings[2046], false, 319, (entity *)IFC4X1_types[711]);
  IFC4X1_types[320] =
      new entity(strings[2047], false, 320, (entity *)IFC4X1_types[712]);
  IFC4X1_types[359] =
      new entity(strings[2048], true, 359, (entity *)IFC4X1_types[731]);
  IFC4X1_types[361] =
      new entity(strings[2049], false, 361, (entity *)IFC4X1_types[359]);
  IFC4X1_types[362] =
      new entity(strings[2050], false, 362, (entity *)IFC4X1_types[368]);
  IFC4X1_types[364] =
      new entity(strings[2051], true, 364, (entity *)IFC4X1_types[359]);
  IFC4X1_types[365] =
      new entity(strings[2052], true, 365, (entity *)IFC4X1_types[368]);
  IFC4X1_types[369] =
      new entity(strings[2053], false, 369, (entity *)IFC4X1_types[188]);
  IFC4X1_types[372] =
      new entity(strings[2054], true, 372, (entity *)IFC4X1_types[295]);
  IFC4X1_types[375] =
      new entity(strings[2055], false, 375, (entity *)IFC4X1_types[372]);
  IFC4X1_types[378] =
      new entity(strings[2056], false, 378, (entity *)IFC4X1_types[372]);
  IFC4X1_types[381] =
      new entity(strings[2057], false, 381, (entity *)IFC4X1_types[372]);
  IFC4X1_types[383] =
      new entity(strings[2058], false, 383, (entity *)IFC4X1_types[729]);
  IFC4X1_types[397] =
      new entity(strings[2059], true, 397, (entity *)IFC4X1_types[953]);
  IFC4X1_types[405] =
      new entity(strings[2060], false, 405, (entity *)IFC4X1_types[568]);
  IFC4X1_types[406] =
      new entity(strings[2061], false, 406, (entity *)IFC4X1_types[405]);
  IFC4X1_types[411] =
      new entity(strings[2062], false, 411, (entity *)IFC4X1_types[364]);
  IFC4X1_types[412] =
      new entity(strings[2063], false, 412, (entity *)IFC4X1_types[365]);
  IFC4X1_types[414] =
      new entity(strings[2064], true, 414, (entity *)IFC4X1_types[359]);
  IFC4X1_types[415] =
      new entity(strings[2065], true, 415, (entity *)IFC4X1_types[414]);
  IFC4X1_types[416] =
      new entity(strings[2066], true, 416, (entity *)IFC4X1_types[414]);
  IFC4X1_types[429] =
      new entity(strings[2067], true, 429, (entity *)IFC4X1_types[295]);
  IFC4X1_types[432] =
      new entity(strings[2068], true, 432, (entity *)IFC4X1_types[295]);
  IFC4X1_types[437] =
      new entity(strings[2069], false, 437, (entity *)IFC4X1_types[429]);
  IFC4X1_types[440] =
      new entity(strings[2070], true, 440, (entity *)IFC4X1_types[295]);
  IFC4X1_types[442] =
      new entity(strings[2071], true, 442, (entity *)IFC4X1_types[295]);
  IFC4X1_types[444] =
      new entity(strings[2072], true, 444, (entity *)IFC4X1_types[295]);
  IFC4X1_types[446] =
      new entity(strings[2073], true, 446, (entity *)IFC4X1_types[295]);
  IFC4X1_types[448] =
      new entity(strings[2074], true, 448, (entity *)IFC4X1_types[295]);
  IFC4X1_types[453] =
      new entity(strings[2075], false, 453, (entity *)IFC4X1_types[110]);
  IFC4X1_types[457] =
      new entity(strings[2076], false, 457, (entity *)IFC4X1_types[359]);
  IFC4X1_types[459] =
      new entity(strings[2077], false, 459, (entity *)IFC4X1_types[457]);
  IFC4X1_types[462] =
      new entity(strings[2078], false, 462, (entity *)IFC4X1_types[359]);
  IFC4X1_types[479] =
      new entity(strings[2079], false, 479, (entity *)IFC4X1_types[631]);
  IFC4X1_types[483] =
      new entity(strings[2080], false, 483, (entity *)IFC4X1_types[372]);
  IFC4X1_types[488] =
      new entity(strings[2081], false, 488, (entity *)IFC4X1_types[372]);
  IFC4X1_types[494] =
      new entity(strings[2082], false, 494, (entity *)IFC4X1_types[91]);
  IFC4X1_types[503] =
      new entity(strings[2083], false, 503, (entity *)IFC4X1_types[448]);
  IFC4X1_types[506] =
      new entity(strings[2084], false, 506, (entity *)IFC4X1_types[1027]);
  IFC4X1_types[507] =
      new entity(strings[2085], false, 507, (entity *)IFC4X1_types[479]);
  IFC4X1_types[515] =
      new entity(strings[2086], false, 515, (entity *)IFC4X1_types[432]);
  IFC4X1_types[520] =
      new entity(strings[2087], false, 520, (entity *)IFC4X1_types[208]);
  IFC4X1_types[525] =
      new entity(strings[2088], false, 525, (entity *)IFC4X1_types[446]);
  IFC4X1_types[539] =
      new entity(strings[2089], false, 539, (entity *)IFC4X1_types[446]);
  IFC4X1_types[556] =
      new entity(strings[2090], false, 556, (entity *)IFC4X1_types[256]);
  IFC4X1_types[597] =
      new entity(strings[2091], false, 597, (entity *)IFC4X1_types[364]);
  IFC4X1_types[598] =
      new entity(strings[2092], false, 598, (entity *)IFC4X1_types[365]);
  IFC4X1_types[601] =
      new entity(strings[2093], false, 601, (entity *)IFC4X1_types[446]);
  IFC4X1_types[605] =
      new entity(strings[2094], false, 605, (entity *)IFC4X1_types[110]);
  IFC4X1_types[624] =
      new entity(strings[2095], false, 624, (entity *)IFC4X1_types[372]);
  IFC4X1_types[638] =
      new entity(strings[2096], false, 638, (entity *)IFC4X1_types[6]);
  IFC4X1_types[644] =
      new entity(strings[2097], false, 644, (entity *)IFC4X1_types[416]);
  IFC4X1_types[646] =
      new entity(strings[2098], false, 646, (entity *)IFC4X1_types[644]);
  IFC4X1_types[654] =
      new entity(strings[2099], false, 654, (entity *)IFC4X1_types[446]);
  IFC4X1_types[661] =
      new entity(strings[2100], false, 661, (entity *)IFC4X1_types[213]);
  IFC4X1_types[664] =
      new entity(strings[2101], false, 664, (entity *)IFC4X1_types[715]);
  IFC4X1_types[665] =
      new entity(strings[2102], false, 665, (entity *)IFC4X1_types[213]);
  IFC4X1_types[676] =
      new entity(strings[2103], false, 676, (entity *)IFC4X1_types[110]);
  IFC4X1_types[679] =
      new entity(strings[2104], false, 679, (entity *)IFC4X1_types[432]);
  IFC4X1_types[682] =
      new entity(strings[2105], false, 682, (entity *)IFC4X1_types[442]);
  IFC4X1_types[693] =
      new entity(strings[2106], false, 693, (entity *)IFC4X1_types[110]);
  IFC4X1_types[700] =
      new entity(strings[2107], false, 700, (entity *)IFC4X1_types[1076]);
  IFC4X1_types[701] =
      new entity(strings[2108], false, 701, (entity *)IFC4X1_types[91]);
  IFC4X1_types[703] =
      new entity(strings[2109], true, 703, (entity *)IFC4X1_types[731]);
  IFC4X1_types[704] =
      new entity(strings[2110], true, 704, (entity *)IFC4X1_types[731]);
  IFC4X1_types[726] =
      new entity(strings[2111], false, 726, (entity *)IFC4X1_types[729]);
  IFC4X1_types[745] =
      new entity(strings[2112], false, 745, (entity *)IFC4X1_types[213]);
  IFC4X1_types[742] =
      new entity(strings[2113], false, 742, (entity *)IFC4X1_types[415]);
  IFC4X1_types[770] =
      new entity(strings[2114], false, 770, (entity *)IFC4X1_types[429]);
  IFC4X1_types[774] =
      new entity(strings[2115], false, 774, (entity *)IFC4X1_types[440]);
  IFC4X1_types[785] =
      new entity(strings[2116], false, 785, (entity *)IFC4X1_types[110]);
  IFC4X1_types[789] =
      new entity(strings[2117], false, 789, (entity *)IFC4X1_types[110]);
  IFC4X1_types[791] =
      new entity(strings[2118], false, 791, (entity *)IFC4X1_types[110]);
  IFC4X1_types[795] =
      new entity(strings[2119], false, 795, (entity *)IFC4X1_types[101]);
  IFC4X1_types[804] =
      new entity(strings[2120], false, 804, (entity *)IFC4X1_types[704]);
  IFC4X1_types[815] =
      new entity(strings[2121], true, 815, (entity *)IFC4X1_types[364]);
  IFC4X1_types[816] =
      new entity(strings[2122], true, 816, (entity *)IFC4X1_types[365]);
  IFC4X1_types[817] =
      new entity(strings[2123], false, 817, (entity *)IFC4X1_types[815]);
  IFC4X1_types[818] =
      new entity(strings[2124], false, 818, (entity *)IFC4X1_types[816]);
  IFC4X1_types[820] =
      new entity(strings[2125], false, 820, (entity *)IFC4X1_types[850]);
  IFC4X1_types[886] =
      new entity(strings[2126], false, 886, (entity *)IFC4X1_types[110]);
  IFC4X1_types[895] =
      new entity(strings[2127], false, 895, (entity *)IFC4X1_types[446]);
  IFC4X1_types[898] =
      new entity(strings[2128], false, 898, (entity *)IFC4X1_types[1027]);
  IFC4X1_types[913] =
      new entity(strings[2129], false, 913, (entity *)IFC4X1_types[110]);
  IFC4X1_types[926] =
      new entity(strings[2130], false, 926, (entity *)IFC4X1_types[955]);
  IFC4X1_types[933] =
      new entity(strings[2131], false, 933, (entity *)IFC4X1_types[110]);
  IFC4X1_types[937] =
      new entity(strings[2132], false, 937, (entity *)IFC4X1_types[372]);
  IFC4X1_types[946] =
      new entity(strings[2133], false, 946, (entity *)IFC4X1_types[955]);
  IFC4X1_types[949] =
      new entity(strings[2134], false, 949, (entity *)IFC4X1_types[446]);
  IFC4X1_types[951] =
      new entity(strings[2135], false, 951, (entity *)IFC4X1_types[956]);
  IFC4X1_types[967] =
      new entity(strings[2136], false, 967, (entity *)IFC4X1_types[446]);
  IFC4X1_types[971] =
      new entity(strings[2137], false, 971, (entity *)IFC4X1_types[110]);
  IFC4X1_types[973] =
      new entity(strings[2138], false, 973, (entity *)IFC4X1_types[110]);
  IFC4X1_types[976] =
      new entity(strings[2139], true, 976, (entity *)IFC4X1_types[977]);
  IFC4X1_types[980] =
      new entity(strings[2140], true, 980, (entity *)IFC4X1_types[989]);
  IFC4X1_types[982] =
      new entity(strings[2141], false, 982, (entity *)IFC4X1_types[976]);
  IFC4X1_types[984] =
      new entity(strings[2142], false, 984, (entity *)IFC4X1_types[980]);
  IFC4X1_types[985] =
      new entity(strings[2143], false, 985, (entity *)IFC4X1_types[1004]);
  IFC4X1_types[987] =
      new entity(strings[2144], false, 987, (entity *)IFC4X1_types[985]);
  IFC4X1_types[988] =
      new entity(strings[2145], false, 988, (entity *)IFC4X1_types[1009]);
  IFC4X1_types[990] =
      new entity(strings[2146], false, 990, (entity *)IFC4X1_types[982]);
  IFC4X1_types[994] =
      new entity(strings[2147], false, 994, (entity *)IFC4X1_types[479]);
  IFC4X1_types[1006] =
      new entity(strings[2148], false, 1006, (entity *)IFC4X1_types[976]);
  IFC4X1_types[1007] =
      new entity(strings[2149], false, 1007, (entity *)IFC4X1_types[980]);
  IFC4X1_types[1008] =
      new entity(strings[2150], false, 1008, (entity *)IFC4X1_types[1009]);
  IFC4X1_types[1010] =
      new entity(strings[2151], false, 1010, (entity *)IFC4X1_types[479]);
  IFC4X1_types[1011] =
      new entity(strings[2152], false, 1011, (entity *)IFC4X1_types[976]);
  IFC4X1_types[1013] =
      new entity(strings[2153], false, 1013, (entity *)IFC4X1_types[980]);
  IFC4X1_types[1022] =
      new entity(strings[2154], false, 1022, (entity *)IFC4X1_types[208]);
  IFC4X1_types[1029] =
      new entity(strings[2155], false, 1029, (entity *)IFC4X1_types[414]);
  IFC4X1_types[1049] =
      new entity(strings[2156], false, 1049, (entity *)IFC4X1_types[429]);
  IFC4X1_types[1051] =
      new entity(strings[2157], false, 1051, (entity *)IFC4X1_types[479]);
  IFC4X1_types[1052] =
      new entity(strings[2158], false, 1052, (entity *)IFC4X1_types[457]);
  IFC4X1_types[1059] =
      new entity(strings[2159], false, 1059, (entity *)IFC4X1_types[444]);
  IFC4X1_types[1070] =
      new entity(strings[2160], false, 1070, (entity *)IFC4X1_types[815]);
  IFC4X1_types[1071] =
      new entity(strings[2161], false, 1071, (entity *)IFC4X1_types[815]);
  IFC4X1_types[1072] =
      new entity(strings[2162], false, 1072, (entity *)IFC4X1_types[816]);
  IFC4X1_types[1074] =
      new entity(strings[2163], false, 1074, (entity *)IFC4X1_types[816]);
  IFC4X1_types[1115] =
      new entity(strings[2164], false, 1115, (entity *)IFC4X1_types[372]);
  IFC4X1_types[1118] =
      new entity(strings[2165], false, 1118, (entity *)IFC4X1_types[256]);
  IFC4X1_types[1121] =
      new entity(strings[2166], false, 1121, (entity *)IFC4X1_types[359]);
  IFC4X1_types[1127] =
      new entity(strings[2167], false, 1127, (entity *)IFC4X1_types[91]);
  IFC4X1_types[1132] =
      new entity(strings[2168], false, 1132, (entity *)IFC4X1_types[372]);
  IFC4X1_types[1143] =
      new entity(strings[2169], false, 1143, (entity *)IFC4X1_types[372]);
  IFC4X1_types[1151] =
      new entity(strings[2170], false, 1151, (entity *)IFC4X1_types[429]);
  IFC4X1_types[1159] =
      new entity(strings[2171], false, 1159, (entity *)IFC4X1_types[364]);
  IFC4X1_types[1160] =
      new entity(strings[2172], false, 1160, (entity *)IFC4X1_types[365]);
  IFC4X1_types[1162] =
      new entity(strings[2173], false, 1162, (entity *)IFC4X1_types[359]);
  IFC4X1_types[1164] =
      new entity(strings[2174], false, 1164, (entity *)IFC4X1_types[416]);
  IFC4X1_types[1171] =
      new entity(strings[2175], false, 1171, (entity *)IFC4X1_types[110]);
  IFC4X1_types[1177] =
      new entity(strings[2176], false, 1177, (entity *)IFC4X1_types[446]);
  IFC4X1_types[1188] =
      new entity(strings[2177], false, 1188, (entity *)IFC4X1_types[110]);
  IFC4X1_types[1191] =
      new entity(strings[2178], false, 1191, (entity *)IFC4X1_types[213]);
  IFC4X1_types[1193] =
      new entity(strings[2179], true, 1193, (entity *)IFC4X1_types[213]);
  IFC4X1_types[1194] =
      new entity(strings[2180], false, 1194, (entity *)IFC4X1_types[1193]);
  IFC4X1_types[1196] =
      new entity(strings[2181], false, 1196, (entity *)IFC4X1_types[1193]);
  IFC4X1_types[1199] =
      new entity(strings[2182], false, 1199, (entity *)IFC4X1_types[1051]);
  IFC4X1_types[252] = new select_type(strings[2183], 252,
                                      {IFC4X1_types[259], IFC4X1_types[261]});
  IFC4X1_types[254] = new select_type(
      strings[2184], 254,
      {IFC4X1_types[178], IFC4X1_types[660], IFC4X1_types[1027]});
  IFC4X1_types[255] = new select_type(strings[2185], 255,
                                      {IFC4X1_types[91], IFC4X1_types[333]});
  IFC4X1_types[978] = new select_type(strings[2186], 978,
                                      {IFC4X1_types[359], IFC4X1_types[989]});
  IFC4X1_types[2] =
      new entity(strings[2187], false, 2, (entity *)IFC4X1_types[213]);
  IFC4X1_types[19] =
      new entity(strings[2188], false, 19, (entity *)IFC4X1_types[429]);
  IFC4X1_types[21] =
      new entity(strings[2189], false, 21, (entity *)IFC4X1_types[446]);
  IFC4X1_types[24] =
      new entity(strings[2190], false, 24, (entity *)IFC4X1_types[372]);
  IFC4X1_types[38] =
      new entity(strings[2191], false, 38, (entity *)IFC4X1_types[91]);
  IFC4X1_types[59] =
      new entity(strings[2192], false, 59, (entity *)IFC4X1_types[479]);
  IFC4X1_types[62] =
      new entity(strings[2193], false, 62, (entity *)IFC4X1_types[446]);
  IFC4X1_types[96] =
      new entity(strings[2194], true, 96, (entity *)IFC4X1_types[91]);
  IFC4X1_types[98] =
      new entity(strings[2195], false, 98, (entity *)IFC4X1_types[96]);
  IFC4X1_types[70] =
      new entity(strings[2196], false, 70, (entity *)IFC4X1_types[110]);
  IFC4X1_types[78] =
      new entity(strings[2197], false, 78, (entity *)IFC4X1_types[372]);
  IFC4X1_types[86] =
      new entity(strings[2198], false, 86, (entity *)IFC4X1_types[178]);
  IFC4X1_types[103] =
      new entity(strings[2199], true, 103, (entity *)IFC4X1_types[359]);
  IFC4X1_types[104] =
      new entity(strings[2200], false, 104, (entity *)IFC4X1_types[364]);
  IFC4X1_types[105] =
      new entity(strings[2201], false, 105, (entity *)IFC4X1_types[365]);
  IFC4X1_types[107] =
      new entity(strings[2202], false, 107, (entity *)IFC4X1_types[103]);
  IFC4X1_types[108] =
      new entity(strings[2203], false, 108, (entity *)IFC4X1_types[110]);
  IFC4X1_types[112] =
      new entity(strings[2204], false, 112, (entity *)IFC4X1_types[1051]);
  IFC4X1_types[115] =
      new entity(strings[2205], false, 115, (entity *)IFC4X1_types[372]);
  IFC4X1_types[118] =
      new entity(strings[2206], false, 118, (entity *)IFC4X1_types[432]);
  IFC4X1_types[121] =
      new entity(strings[2207], false, 121, (entity *)IFC4X1_types[442]);
  IFC4X1_types[124] =
      new entity(strings[2208], false, 124, (entity *)IFC4X1_types[432]);
  IFC4X1_types[127] =
      new entity(strings[2209], false, 127, (entity *)IFC4X1_types[442]);
  IFC4X1_types[142] =
      new entity(strings[2210], false, 142, (entity *)IFC4X1_types[372]);
  IFC4X1_types[144] =
      new entity(strings[2211], false, 144, (entity *)IFC4X1_types[103]);
  IFC4X1_types[147] =
      new entity(strings[2212], false, 147, (entity *)IFC4X1_types[188]);
  IFC4X1_types[150] =
      new entity(strings[2213], false, 150, (entity *)IFC4X1_types[256]);
  IFC4X1_types[151] =
      new entity(strings[2214], false, 151, (entity *)IFC4X1_types[359]);
  IFC4X1_types[159] =
      new entity(strings[2215], false, 159, (entity *)IFC4X1_types[372]);
  IFC4X1_types[166] =
      new entity(strings[2216], false, 166, (entity *)IFC4X1_types[103]);
  IFC4X1_types[167] =
      new entity(strings[2217], false, 167, (entity *)IFC4X1_types[166]);
  IFC4X1_types[171] =
      new entity(strings[2218], false, 171, (entity *)IFC4X1_types[446]);
  IFC4X1_types[183] =
      new entity(strings[2219], false, 183, (entity *)IFC4X1_types[440]);
  IFC4X1_types[186] =
      new entity(strings[2220], false, 186, (entity *)IFC4X1_types[372]);
  IFC4X1_types[199] =
      new entity(strings[2221], false, 199, (entity *)IFC4X1_types[208]);
  IFC4X1_types[202] =
      new entity(strings[2222], false, 202, (entity *)IFC4X1_types[208]);
  IFC4X1_types[205] =
      new entity(strings[2223], false, 205, (entity *)IFC4X1_types[208]);
  IFC4X1_types[220] =
      new entity(strings[2224], false, 220, (entity *)IFC4X1_types[372]);
  IFC4X1_types[223] =
      new entity(strings[2225], false, 223, (entity *)IFC4X1_types[372]);
  IFC4X1_types[234] =
      new entity(strings[2226], false, 234, (entity *)IFC4X1_types[103]);
  IFC4X1_types[245] =
      new entity(strings[2227], false, 245, (entity *)IFC4X1_types[103]);
  IFC4X1_types[264] =
      new entity(strings[2228], false, 264, (entity *)IFC4X1_types[429]);
  IFC4X1_types[282] =
      new entity(strings[2229], false, 282, (entity *)IFC4X1_types[364]);
  IFC4X1_types[283] =
      new entity(strings[2230], false, 283, (entity *)IFC4X1_types[365]);
  IFC4X1_types[287] =
      new entity(strings[2231], false, 287, (entity *)IFC4X1_types[295]);
  IFC4X1_types[291] =
      new entity(strings[2232], true, 291, (entity *)IFC4X1_types[293]);
  IFC4X1_types[292] =
      new entity(strings[2233], false, 292, (entity *)IFC4X1_types[359]);
  IFC4X1_types[294] =
      new entity(strings[2234], false, 294, (entity *)IFC4X1_types[292]);
  IFC4X1_types[296] =
      new entity(strings[2235], false, 296, (entity *)IFC4X1_types[703]);
  IFC4X1_types[298] =
      new entity(strings[2236], false, 298, (entity *)IFC4X1_types[1051]);
  IFC4X1_types[306] =
      new entity(strings[2237], false, 306, (entity *)IFC4X1_types[103]);
  IFC4X1_types[311] =
      new entity(strings[2238], false, 311, (entity *)IFC4X1_types[306]);
  IFC4X1_types[322] =
      new entity(strings[2239], false, 322, (entity *)IFC4X1_types[432]);
  IFC4X1_types[325] =
      new entity(strings[2240], false, 325, (entity *)IFC4X1_types[442]);
  IFC4X1_types[328] =
      new entity(strings[2241], false, 328, (entity *)IFC4X1_types[448]);
  IFC4X1_types[336] =
      new entity(strings[2242], false, 336, (entity *)IFC4X1_types[446]);
  IFC4X1_types[343] =
      new entity(strings[2243], false, 343, (entity *)IFC4X1_types[429]);
  IFC4X1_types[346] =
      new entity(strings[2244], false, 346, (entity *)IFC4X1_types[444]);
  IFC4X1_types[349] =
      new entity(strings[2245], false, 349, (entity *)IFC4X1_types[372]);
  IFC4X1_types[352] =
      new entity(strings[2246], false, 352, (entity *)IFC4X1_types[372]);
  IFC4X1_types[356] =
      new entity(strings[2247], false, 356, (entity *)IFC4X1_types[429]);
  IFC4X1_types[371] =
      new entity(strings[2248], false, 371, (entity *)IFC4X1_types[294]);
  IFC4X1_types[374] =
      new entity(strings[2249], false, 374, (entity *)IFC4X1_types[371]);
  IFC4X1_types[377] =
      new entity(strings[2250], false, 377, (entity *)IFC4X1_types[371]);
  IFC4X1_types[380] =
      new entity(strings[2251], false, 380, (entity *)IFC4X1_types[371]);
  IFC4X1_types[395] =
      new entity(strings[2252], false, 395, (entity *)IFC4X1_types[397]);
  IFC4X1_types[409] =
      new entity(strings[2253], false, 409, (entity *)IFC4X1_types[440]);
  IFC4X1_types[422] =
      new entity(strings[2254], false, 422, (entity *)IFC4X1_types[448]);
  IFC4X1_types[425] =
      new entity(strings[2255], false, 425, (entity *)IFC4X1_types[446]);
  IFC4X1_types[428] =
      new entity(strings[2256], false, 428, (entity *)IFC4X1_types[294]);
  IFC4X1_types[431] =
      new entity(strings[2257], false, 431, (entity *)IFC4X1_types[294]);
  IFC4X1_types[434] =
      new entity(strings[2258], false, 434, (entity *)IFC4X1_types[291]);
  IFC4X1_types[436] =
      new entity(strings[2259], false, 436, (entity *)IFC4X1_types[428]);
  IFC4X1_types[439] =
      new entity(strings[2260], false, 439, (entity *)IFC4X1_types[294]);
  IFC4X1_types[441] =
      new entity(strings[2261], false, 441, (entity *)IFC4X1_types[294]);
  IFC4X1_types[443] =
      new entity(strings[2262], false, 443, (entity *)IFC4X1_types[294]);
  IFC4X1_types[445] =
      new entity(strings[2263], false, 445, (entity *)IFC4X1_types[294]);
  IFC4X1_types[447] =
      new entity(strings[2264], false, 447, (entity *)IFC4X1_types[294]);
  IFC4X1_types[452] =
      new entity(strings[2265], false, 452, (entity *)IFC4X1_types[103]);
  IFC4X1_types[474] =
      new entity(strings[2266], false, 474, (entity *)IFC4X1_types[704]);
  IFC4X1_types[482] =
      new entity(strings[2267], false, 482, (entity *)IFC4X1_types[371]);
  IFC4X1_types[487] =
      new entity(strings[2268], false, 487, (entity *)IFC4X1_types[371]);
  IFC4X1_types[502] =
      new entity(strings[2269], false, 502, (entity *)IFC4X1_types[447]);
  IFC4X1_types[514] =
      new entity(strings[2270], false, 514, (entity *)IFC4X1_types[431]);
  IFC4X1_types[524] =
      new entity(strings[2271], false, 524, (entity *)IFC4X1_types[445]);
  IFC4X1_types[538] =
      new entity(strings[2272], false, 538, (entity *)IFC4X1_types[445]);
  IFC4X1_types[552] =
      new entity(strings[2273], true, 552, (entity *)IFC4X1_types[704]);
  IFC4X1_types[600] =
      new entity(strings[2274], false, 600, (entity *)IFC4X1_types[445]);
  IFC4X1_types[603] =
      new entity(strings[2275], false, 603, (entity *)IFC4X1_types[103]);
  IFC4X1_types[604] =
      new entity(strings[2276], false, 604, (entity *)IFC4X1_types[603]);
  IFC4X1_types[623] =
      new entity(strings[2277], false, 623, (entity *)IFC4X1_types[371]);
  IFC4X1_types[652] =
      new entity(strings[2278], false, 652, (entity *)IFC4X1_types[86]);
  IFC4X1_types[653] =
      new entity(strings[2279], false, 653, (entity *)IFC4X1_types[445]);
  IFC4X1_types[674] =
      new entity(strings[2280], false, 674, (entity *)IFC4X1_types[103]);
  IFC4X1_types[678] =
      new entity(strings[2281], false, 678, (entity *)IFC4X1_types[431]);
  IFC4X1_types[681] =
      new entity(strings[2282], false, 681, (entity *)IFC4X1_types[441]);
  IFC4X1_types[691] =
      new entity(strings[2283], false, 691, (entity *)IFC4X1_types[103]);
  IFC4X1_types[692] =
      new entity(strings[2284], false, 692, (entity *)IFC4X1_types[691]);
  IFC4X1_types[766] =
      new entity(strings[2285], false, 766, (entity *)IFC4X1_types[428]);
  IFC4X1_types[768] =
      new entity(strings[2286], false, 768, (entity *)IFC4X1_types[291]);
  IFC4X1_types[773] =
      new entity(strings[2287], false, 773, (entity *)IFC4X1_types[439]);
  IFC4X1_types[784] =
      new entity(strings[2288], false, 784, (entity *)IFC4X1_types[103]);
  IFC4X1_types[787] =
      new entity(strings[2289], false, 787, (entity *)IFC4X1_types[103]);
  IFC4X1_types[788] =
      new entity(strings[2290], false, 788, (entity *)IFC4X1_types[103]);
  IFC4X1_types[794] =
      new entity(strings[2291], false, 794, (entity *)IFC4X1_types[98]);
  IFC4X1_types[810] =
      new entity(strings[2292], false, 810, (entity *)IFC4X1_types[815]);
  IFC4X1_types[813] =
      new entity(strings[2293], false, 813, (entity *)IFC4X1_types[816]);
  IFC4X1_types[885] =
      new entity(strings[2294], false, 885, (entity *)IFC4X1_types[103]);
  IFC4X1_types[894] =
      new entity(strings[2295], false, 894, (entity *)IFC4X1_types[445]);
  IFC4X1_types[909] =
      new entity(strings[2296], false, 909, (entity *)IFC4X1_types[291]);
  IFC4X1_types[912] =
      new entity(strings[2297], false, 912, (entity *)IFC4X1_types[103]);
  IFC4X1_types[930] =
      new entity(strings[2298], false, 930, (entity *)IFC4X1_types[103]);
  IFC4X1_types[931] =
      new entity(strings[2299], false, 931, (entity *)IFC4X1_types[930]);
  IFC4X1_types[932] =
      new entity(strings[2300], false, 932, (entity *)IFC4X1_types[930]);
  IFC4X1_types[936] =
      new entity(strings[2301], false, 936, (entity *)IFC4X1_types[371]);
  IFC4X1_types[948] =
      new entity(strings[2302], false, 948, (entity *)IFC4X1_types[445]);
  IFC4X1_types[966] =
      new entity(strings[2303], false, 966, (entity *)IFC4X1_types[445]);
  IFC4X1_types[969] =
      new entity(strings[2304], false, 969, (entity *)IFC4X1_types[103]);
  IFC4X1_types[970] =
      new entity(strings[2305], false, 970, (entity *)IFC4X1_types[103]);
  IFC4X1_types[979] =
      new entity(strings[2306], false, 979, (entity *)IFC4X1_types[1051]);
  IFC4X1_types[992] =
      new entity(strings[2307], false, 992, (entity *)IFC4X1_types[994]);
  IFC4X1_types[1005] =
      new entity(strings[2308], false, 1005, (entity *)IFC4X1_types[1011]);
  IFC4X1_types[1048] =
      new entity(strings[2309], false, 1048, (entity *)IFC4X1_types[428]);
  IFC4X1_types[1058] =
      new entity(strings[2310], false, 1058, (entity *)IFC4X1_types[443]);
  IFC4X1_types[1114] =
      new entity(strings[2311], false, 1114, (entity *)IFC4X1_types[371]);
  IFC4X1_types[1131] =
      new entity(strings[2312], false, 1131, (entity *)IFC4X1_types[371]);
  IFC4X1_types[1140] =
      new entity(strings[2313], false, 1140, (entity *)IFC4X1_types[291]);
  IFC4X1_types[1142] =
      new entity(strings[2314], false, 1142, (entity *)IFC4X1_types[371]);
  IFC4X1_types[1150] =
      new entity(strings[2315], false, 1150, (entity *)IFC4X1_types[428]);
  IFC4X1_types[1168] =
      new entity(strings[2316], false, 1168, (entity *)IFC4X1_types[103]);
  IFC4X1_types[1169] =
      new entity(strings[2317], false, 1169, (entity *)IFC4X1_types[1168]);
  IFC4X1_types[1170] =
      new entity(strings[2318], false, 1170, (entity *)IFC4X1_types[1168]);
  IFC4X1_types[1176] =
      new entity(strings[2319], false, 1176, (entity *)IFC4X1_types[445]);
  IFC4X1_types[1179] =
      new entity(strings[2320], false, 1179, (entity *)IFC4X1_types[103]);
  IFC4X1_types[1184] =
      new entity(strings[2321], false, 1184, (entity *)IFC4X1_types[1179]);
  IFC4X1_types[947] = new select_type(strings[2322], 947,
                                      {IFC4X1_types[395], IFC4X1_types[946]});
  IFC4X1_types[10] =
      new entity(strings[2323], false, 10, (entity *)IFC4X1_types[291]);
  IFC4X1_types[17] =
      new entity(strings[2324], false, 17, (entity *)IFC4X1_types[445]);
  IFC4X1_types[18] =
      new entity(strings[2325], false, 18, (entity *)IFC4X1_types[428]);
  IFC4X1_types[23] =
      new entity(strings[2326], false, 23, (entity *)IFC4X1_types[371]);
  IFC4X1_types[27] =
      new entity(strings[2327], false, 27, (entity *)IFC4X1_types[291]);
  IFC4X1_types[29] =
      new entity(strings[2328], false, 29, (entity *)IFC4X1_types[552]);
  IFC4X1_types[61] =
      new entity(strings[2329], false, 61, (entity *)IFC4X1_types[445]);
  IFC4X1_types[68] =
      new entity(strings[2330], false, 68, (entity *)IFC4X1_types[103]);
  IFC4X1_types[69] =
      new entity(strings[2331], false, 69, (entity *)IFC4X1_types[68]);
  IFC4X1_types[77] =
      new entity(strings[2332], false, 77, (entity *)IFC4X1_types[371]);
  IFC4X1_types[114] =
      new entity(strings[2333], false, 114, (entity *)IFC4X1_types[371]);
  IFC4X1_types[117] =
      new entity(strings[2334], false, 117, (entity *)IFC4X1_types[431]);
  IFC4X1_types[120] =
      new entity(strings[2335], false, 120, (entity *)IFC4X1_types[441]);
  IFC4X1_types[123] =
      new entity(strings[2336], false, 123, (entity *)IFC4X1_types[431]);
  IFC4X1_types[126] =
      new entity(strings[2337], false, 126, (entity *)IFC4X1_types[441]);
  IFC4X1_types[141] =
      new entity(strings[2338], false, 141, (entity *)IFC4X1_types[371]);
  IFC4X1_types[158] =
      new entity(strings[2339], false, 158, (entity *)IFC4X1_types[371]);
  IFC4X1_types[170] =
      new entity(strings[2340], false, 170, (entity *)IFC4X1_types[445]);
  IFC4X1_types[182] =
      new entity(strings[2341], false, 182, (entity *)IFC4X1_types[439]);
  IFC4X1_types[185] =
      new entity(strings[2342], false, 185, (entity *)IFC4X1_types[371]);
  IFC4X1_types[215] =
      new entity(strings[2343], false, 215, (entity *)IFC4X1_types[291]);
  IFC4X1_types[219] =
      new entity(strings[2344], false, 219, (entity *)IFC4X1_types[371]);
  IFC4X1_types[222] =
      new entity(strings[2345], false, 222, (entity *)IFC4X1_types[371]);
  IFC4X1_types[263] =
      new entity(strings[2346], false, 263, (entity *)IFC4X1_types[428]);
  IFC4X1_types[286] =
      new entity(strings[2347], false, 286, (entity *)IFC4X1_types[294]);
  IFC4X1_types[289] =
      new entity(strings[2348], false, 289, (entity *)IFC4X1_types[298]);
  IFC4X1_types[290] =
      new entity(strings[2349], false, 290, (entity *)IFC4X1_types[292]);
  IFC4X1_types[321] =
      new entity(strings[2350], false, 321, (entity *)IFC4X1_types[431]);
  IFC4X1_types[324] =
      new entity(strings[2351], false, 324, (entity *)IFC4X1_types[441]);
  IFC4X1_types[327] =
      new entity(strings[2352], false, 327, (entity *)IFC4X1_types[447]);
  IFC4X1_types[335] =
      new entity(strings[2353], false, 335, (entity *)IFC4X1_types[445]);
  IFC4X1_types[342] =
      new entity(strings[2354], false, 342, (entity *)IFC4X1_types[428]);
  IFC4X1_types[345] =
      new entity(strings[2355], false, 345, (entity *)IFC4X1_types[443]);
  IFC4X1_types[348] =
      new entity(strings[2356], false, 348, (entity *)IFC4X1_types[371]);
  IFC4X1_types[351] =
      new entity(strings[2357], false, 351, (entity *)IFC4X1_types[371]);
  IFC4X1_types[355] =
      new entity(strings[2358], false, 355, (entity *)IFC4X1_types[428]);
  IFC4X1_types[408] =
      new entity(strings[2359], false, 408, (entity *)IFC4X1_types[439]);
  IFC4X1_types[421] =
      new entity(strings[2360], false, 421, (entity *)IFC4X1_types[447]);
  IFC4X1_types[424] =
      new entity(strings[2361], false, 424, (entity *)IFC4X1_types[445]);
  IFC4X1_types[433] =
      new entity(strings[2362], false, 433, (entity *)IFC4X1_types[290]);
  IFC4X1_types[767] =
      new entity(strings[2363], false, 767, (entity *)IFC4X1_types[290]);
  IFC4X1_types[908] =
      new entity(strings[2364], false, 908, (entity *)IFC4X1_types[290]);
  IFC4X1_types[1139] =
      new entity(strings[2365], false, 1139, (entity *)IFC4X1_types[290]);
  IFC4X1_types[9] =
      new entity(strings[2366], false, 9, (entity *)IFC4X1_types[290]);
  IFC4X1_types[26] =
      new entity(strings[2367], false, 26, (entity *)IFC4X1_types[290]);
  IFC4X1_types[214] =
      new entity(strings[2368], false, 214, (entity *)IFC4X1_types[290]);
  ((entity *)IFC4X1_types[2])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[3]), true),
           new attribute(strings[2370], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2371], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[6])
      ->set_attributes({new attribute(strings[2372],
                                      new named_type(IFC4X1_types[8]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[7])
      ->set_attributes(
          {new attribute(strings[2373], new named_type(IFC4X1_types[884]),
                         false),
           new attribute(strings[2374], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X1_types[9])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[11]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[10])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[11]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[12])
      ->set_attributes(
          {new attribute(strings[2376], new named_type(IFC4X1_types[13]), true),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[2377], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X1_types[14])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[15])
      ->set_attributes({new attribute(strings[2378],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[157])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X1_types[16])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X1_types[17])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[22]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[18])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[20]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[19])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[20]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[21])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[22]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[23])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[25]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[24])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[25]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[26])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[28]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[27])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[28]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[29])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[39]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[30])
      ->set_attributes({new attribute(strings[2379],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2380],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[31])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X1_types[31])
      ->set_attributes(
          {new attribute(strings[2381], new named_type(IFC4X1_types[256]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[32])
      ->set_attributes(
          {new attribute(strings[2382], new named_type(IFC4X1_types[80]), true),
           new attribute(strings[2383], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2384], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X1_types[33])
      ->set_attributes(
          {new attribute(strings[2385], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2386], new named_type(IFC4X1_types[80]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[34])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[35])
      ->set_attributes(
          {new attribute(strings[2387], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2386], new named_type(IFC4X1_types[80]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[36])
      ->set_attributes({new attribute(strings[2380],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[37])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[37])
      ->set_attributes(
          {new attribute(strings[2379], new named_type(IFC4X1_types[530]),
                         false),
           new attribute(strings[2388], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2389], new named_type(IFC4X1_types[530]),
                         false),
           new attribute(strings[2390], new named_type(IFC4X1_types[793]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[38])
      ->set_attributes(
          {new attribute(strings[2391], new named_type(IFC4X1_types[30]),
                         false),
           new attribute(strings[2392], new named_type(IFC4X1_types[36]), true),
           new attribute(strings[2393], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X1_types[44])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[45])
      ->set_attributes({new attribute(strings[2394],
                                      new named_type(IFC4X1_types[249]), false),
                        new attribute(strings[2395],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[249])),
                                      true)},
                       {false, false});
  ((entity *)IFC4X1_types[46])
      ->set_attributes(
          {new attribute(strings[2396], new named_type(IFC4X1_types[648]),
                         false),
           new attribute(strings[2397], new named_type(IFC4X1_types[519]),
                         false),
           new attribute(strings[2398], new named_type(IFC4X1_types[519]),
                         false),
           new attribute(strings[2399], new named_type(IFC4X1_types[490]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[47])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[2401], new named_type(IFC4X1_types[48]), true),
           new attribute(strings[2402], new named_type(IFC4X1_types[596]),
                         true),
           new attribute(strings[2403], new named_type(IFC4X1_types[267]),
                         true),
           new attribute(strings[2404], new named_type(IFC4X1_types[267]),
                         true),
           new attribute(strings[2405], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2406], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2407], new named_type(IFC4X1_types[57]), true),
           new attribute(strings[2408],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X1_types[47])),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[49])
      ->set_attributes(
          {new attribute(strings[2409], new named_type(IFC4X1_types[490]),
                         true),
           new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[2410], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[2370], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2411], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2412], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[2413], new named_type(IFC4X1_types[8]), true),
           new attribute(strings[2414], new named_type(IFC4X1_types[8]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[50])
      ->set_attributes(
          {new attribute(strings[2415], new named_type(IFC4X1_types[49]),
                         false),
           new attribute(strings[2416],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4X1_types[49])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[51])
      ->set_attributes(
          {new attribute(strings[2417], new named_type(IFC4X1_types[249]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[52])
      ->set_attributes({new attribute(strings[2418],
                                      new named_type(IFC4X1_types[91]), false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[53])
      ->set_attributes({new attribute(strings[2419],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[249])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[59])
      ->set_attributes(
          {new attribute(strings[2420], new named_type(IFC4X1_types[490]),
                         true),
           new attribute(strings[2421], new named_type(IFC4X1_types[232]),
                         true),
           new attribute(strings[2422], new named_type(IFC4X1_types[232]),
                         true),
           new attribute(strings[2423], new named_type(IFC4X1_types[232]),
                         true),
           new attribute(strings[2424], new named_type(IFC4X1_types[8]), true),
           new attribute(strings[2425], new named_type(IFC4X1_types[8]), true),
           new attribute(strings[2426], new named_type(IFC4X1_types[667]),
                         true),
           new attribute(strings[2427], new named_type(IFC4X1_types[267]),
                         true),
           new attribute(strings[2428], new named_type(IFC4X1_types[232]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X1_types[60])
      ->set_attributes({new attribute(strings[2429],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2430],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2431],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2432],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2433],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2434],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2435],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2436],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2437],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2438],
                                      new named_type(IFC4X1_types[690]), true),
                        new attribute(strings[2439],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2440],
                                      new named_type(IFC4X1_types[690]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[61])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[63]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[62])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[63]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[64])
      ->set_attributes({new attribute(strings[2441],
                                      new named_type(IFC4X1_types[280]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[66])
      ->set_attributes({new attribute(strings[2442],
                                      new named_type(IFC4X1_types[280]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[67])
      ->set_attributes({new attribute(strings[2441],
                                      new named_type(IFC4X1_types[280]), true),
                        new attribute(strings[2442],
                                      new named_type(IFC4X1_types[280]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[96])
      ->set_attributes(
          {new attribute(strings[2443], new named_type(IFC4X1_types[500]),
                         false),
           new attribute(
               strings[2444],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X1_types[130])),
               false),
           new attribute(strings[2445], new named_type(IFC4X1_types[97]),
                         false),
           new attribute(strings[2446], new named_type(IFC4X1_types[559]),
                         false),
           new attribute(strings[2447], new named_type(IFC4X1_types[559]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[98])
      ->set_attributes(
          {new attribute(
               strings[2448],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X1_types[500])),
               false),
           new attribute(
               strings[2449],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X1_types[658])),
               false),
           new attribute(strings[2450], new named_type(IFC4X1_types[518]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[99])
      ->set_attributes(
          {new attribute(strings[2451], new named_type(IFC4X1_types[500]),
                         false),
           new attribute(strings[2452], new named_type(IFC4X1_types[500]),
                         false),
           new attribute(
               strings[2444],
               new aggregation_type(
                   aggregation_type::list_type, 2, -1,
                   new aggregation_type(aggregation_type::list_type, 2, -1,
                                        new named_type(IFC4X1_types[130]))),
               false),
           new attribute(strings[2453], new named_type(IFC4X1_types[100]),
                         false),
           new attribute(strings[2454], new named_type(IFC4X1_types[559]),
                         false),
           new attribute(strings[2455], new named_type(IFC4X1_types[559]),
                         false),
           new attribute(strings[2447], new named_type(IFC4X1_types[559]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[101])
      ->set_attributes(
          {new attribute(
               strings[2456],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X1_types[500])),
               false),
           new attribute(
               strings[2457],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X1_types[500])),
               false),
           new attribute(
               strings[2458],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X1_types[658])),
               false),
           new attribute(
               strings[2459],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X1_types[658])),
               false),
           new attribute(strings[2450], new named_type(IFC4X1_types[518]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X1_types[68])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[71]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[69])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[70])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[71]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[75])
      ->set_attributes({new attribute(strings[2460],
                                      new named_type(IFC4X1_types[490]), false),
                        new attribute(strings[2461],
                                      new named_type(IFC4X1_types[74]), false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[76])
      ->set_attributes(
          {new attribute(strings[2462], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2463], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2464], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[77])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[79]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[78])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[79]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[81])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X1_types[84])
      ->set_attributes({new attribute(strings[2465],
                                      new named_type(IFC4X1_types[83]), false),
                        new attribute(strings[2466],
                                      new named_type(IFC4X1_types[82]), false),
                        new attribute(strings[2467],
                                      new named_type(IFC4X1_types[82]), false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[85])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false});
  ((entity *)IFC4X1_types[86])->set_attributes({}, {false, false});
  ((entity *)IFC4X1_types[87])
      ->set_attributes({new attribute(strings[2468],
                                      new named_type(IFC4X1_types[616]), true),
                        new attribute(strings[2469],
                                      new named_type(IFC4X1_types[616]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X1_types[616]), true),
                        new attribute(strings[2471],
                                      new named_type(IFC4X1_types[613]), true),
                        new attribute(strings[2472],
                                      new named_type(IFC4X1_types[613]), true),
                        new attribute(strings[2473],
                                      new named_type(IFC4X1_types[613]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[88])
      ->set_attributes({new attribute(strings[2474],
                                      new named_type(IFC4X1_types[615]), true),
                        new attribute(strings[2475],
                                      new named_type(IFC4X1_types[615]), true),
                        new attribute(strings[2476],
                                      new named_type(IFC4X1_types[615]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[89])
      ->set_attributes({new attribute(strings[2477],
                                      new named_type(IFC4X1_types[1120]), true),
                        new attribute(strings[2478],
                                      new named_type(IFC4X1_types[1120]), true),
                        new attribute(strings[2479],
                                      new named_type(IFC4X1_types[1120]), true),
                        new attribute(strings[2480],
                                      new named_type(IFC4X1_types[892]), true),
                        new attribute(strings[2481],
                                      new named_type(IFC4X1_types[892]), true),
                        new attribute(strings[2482],
                                      new named_type(IFC4X1_types[892]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[90])
      ->set_attributes(
          {new attribute(strings[2483], new named_type(IFC4X1_types[1175]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[91])->set_attributes({}, {});
  ((entity *)IFC4X1_types[92])->set_attributes({}, {});
  ((entity *)IFC4X1_types[93])
      ->set_attributes(
          {new attribute(strings[2484], new named_type(IFC4X1_types[130]),
                         false),
           new attribute(strings[2485], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2486], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2487], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[95])
      ->set_attributes({new attribute(strings[2488],
                                      new named_type(IFC4X1_types[93]), false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[102])
      ->set_attributes({new attribute(strings[2489],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2490],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2491],
                                      new named_type(IFC4X1_types[709]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X1_types[103])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[104])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[106]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[105])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[106]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[107])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[109]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[108])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[109]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[110])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[111])
      ->set_attributes({new attribute(strings[2492],
                                      new named_type(IFC4X1_types[530]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[112])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[113]), true),
                        new attribute(strings[2493],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[114])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[116]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[115])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[116]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[243])
      ->set_attributes(
          {new attribute(strings[2494], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2495], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2496], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2497], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2498], new named_type(IFC4X1_types[627]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[117])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[119]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[118])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[119]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[120])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[122]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[121])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[122]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[123])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[125]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[124])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[125]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[126])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[128]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[127])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[128]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[130])
      ->set_attributes({new attribute(strings[2499],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, 3,
                                          new named_type(IFC4X1_types[530])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[131])->set_attributes({}, {});
  ((entity *)IFC4X1_types[132])
      ->set_attributes(
          {new attribute(
               strings[2500],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 2, 2,
                                        new named_type(IFC4X1_types[530]))),
               false),
           new attribute(
               strings[2501],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[519])),
               true)},
          {false, false});
  ((entity *)IFC4X1_types[133])
      ->set_attributes(
          {new attribute(
               strings[2500],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4X1_types[530]))),
               false),
           new attribute(
               strings[2501],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[519])),
               true)},
          {false, false});
  ((entity *)IFC4X1_types[134])
      ->set_attributes({new attribute(strings[2502],
                                      new named_type(IFC4X1_types[280]), true),
                        new attribute(strings[2503],
                                      new named_type(IFC4X1_types[280]), true),
                        new attribute(strings[2504],
                                      new named_type(IFC4X1_types[130]), false),
                        new attribute(strings[2505],
                                      new named_type(IFC4X1_types[796]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[135])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[136])
      ->set_attributes({new attribute(strings[2506],
                                      new named_type(IFC4X1_types[796]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[137])
      ->set_attributes({new attribute(strings[2507],
                                      new named_type(IFC4X1_types[280]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[138])
      ->set_attributes({new attribute(strings[2506],
                                      new named_type(IFC4X1_types[796]), true),
                        new attribute(strings[2508],
                                      new named_type(IFC4X1_types[796]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[139])
      ->set_attributes(
          {new attribute(strings[2509], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[141])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[143]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[142])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[143]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[144])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[146]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[145])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[146]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[147])
      ->set_attributes(
          {new attribute(strings[2385], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[148])
      ->set_attributes(
          {new attribute(strings[2496], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[149])
      ->set_attributes(
          {new attribute(strings[2385], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[150])
      ->set_attributes({new attribute(strings[2385],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2510],
                                      new named_type(IFC4X1_types[80]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[151])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[152])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[153])
      ->set_attributes({new attribute(strings[2511],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2512],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2513],
                                      new named_type(IFC4X1_types[267]), true),
                        new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), false),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2514],
                                      new named_type(IFC4X1_types[1147]), true),
                        new attribute(strings[2515],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[490])),
                                      true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[154])
      ->set_attributes({new attribute(strings[2516],
                                      new named_type(IFC4X1_types[155]), true),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2517],
                                      new named_type(IFC4X1_types[490]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[157])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[158])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[160]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[159])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[160]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[163])
      ->set_attributes(
          {new attribute(strings[2518], new named_type(IFC4X1_types[628]),
                         false),
           new attribute(strings[2519], new named_type(IFC4X1_types[628]),
                         false),
           new attribute(strings[2520], new named_type(IFC4X1_types[628]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[164])
      ->set_attributes(
          {new attribute(
              strings[2521],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, 3,
                                       new named_type(IFC4X1_types[628]))),
              false)},
          {false});
  ((entity *)IFC4X1_types[165])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false});
  ((entity *)IFC4X1_types[166])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[169]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[167])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[168])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[169]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[170])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[172]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[171])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[172]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[174])
      ->set_attributes({new attribute(strings[2522],
                                      new named_type(IFC4X1_types[490]), false),
                        new attribute(strings[2523],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[747])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[175])
      ->set_attributes({new attribute(strings[2522],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2524],
                                      new named_type(IFC4X1_types[176]), true),
                        new attribute(strings[2525],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[764])),
                                      true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[177])
      ->set_attributes(
          {new attribute(
               strings[2380],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[179])),
               false),
           new attribute(strings[2447], new named_type(IFC4X1_types[559]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[178])->set_attributes({}, {false, false});
  ((entity *)IFC4X1_types[179])
      ->set_attributes(
          {new attribute(strings[2526], new named_type(IFC4X1_types[1117]),
                         false),
           new attribute(strings[2527], new named_type(IFC4X1_types[80]),
                         false),
           new attribute(strings[2528], new named_type(IFC4X1_types[249]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[180])
      ->set_attributes({new attribute(strings[2529],
                                      new aggregation_type(
                                          aggregation_type::set_type, 2, -1,
                                          new named_type(IFC4X1_types[736])),
                                      false),
                        new attribute(strings[2530],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[182])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[184]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[183])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[184]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[185])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[187]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[186])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[187]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[188])
      ->set_attributes({new attribute(strings[2531],
                                      new named_type(IFC4X1_types[65]), false)},
                       {false});
  ((entity *)IFC4X1_types[189])
      ->set_attributes({new attribute(strings[2532],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[400])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[190])
      ->set_attributes({new attribute(strings[2533],
                                      new named_type(IFC4X1_types[255]), false),
                        new attribute(strings[2534],
                                      new named_type(IFC4X1_types[255]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[191])->set_attributes({}, {});
  ((entity *)IFC4X1_types[192])
      ->set_attributes({new attribute(strings[2535],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2536],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2537],
                                      new named_type(IFC4X1_types[530]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[193])
      ->set_attributes({new attribute(strings[2538],
                                      new named_type(IFC4X1_types[698]), false),
                        new attribute(strings[2539],
                                      new named_type(IFC4X1_types[698]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[194])
      ->set_attributes(
          {new attribute(strings[2540], new named_type(IFC4X1_types[1033]),
                         false),
           new attribute(strings[2541], new named_type(IFC4X1_types[1033]),
                         true)},
          {false, false});
  ((entity *)IFC4X1_types[196])
      ->set_attributes({new attribute(strings[2542],
                                      new named_type(IFC4X1_types[941]), false),
                        new attribute(strings[2543],
                                      new named_type(IFC4X1_types[941]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[197])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         false),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[2544], new named_type(IFC4X1_types[198]),
                         false),
           new attribute(strings[2545], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2546], new named_type(IFC4X1_types[8]), true),
           new attribute(strings[2547], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[2548], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[199])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[201]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[200])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[201]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X1_types[202])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[204]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[203])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[204]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X1_types[205])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[207]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[206])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[207]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X1_types[208])
      ->set_attributes({new attribute(strings[2549],
                                      new named_type(IFC4X1_types[879]), true),
                        new attribute(strings[2550],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[47])),
                                      true),
                        new attribute(strings[2551],
                                      new named_type(IFC4X1_types[672]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[209])
      ->set_attributes({new attribute(strings[2550],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[47])),
                                      true),
                        new attribute(strings[2551],
                                      new named_type(IFC4X1_types[672]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[210])
      ->set_attributes(
          {new attribute(strings[2552], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2493], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2553], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(
               strings[2554],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[870])),
               true),
           new attribute(strings[2555], new named_type(IFC4X1_types[1145]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[212])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[213])
      ->set_attributes({new attribute(strings[2420],
                                      new named_type(IFC4X1_types[490]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[214])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[216]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[215])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[216]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[217])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         false),
           new attribute(strings[2556], new named_type(IFC4X1_types[596]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[218])
      ->set_attributes(
          {new attribute(strings[2557], new named_type(IFC4X1_types[796]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[219])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[221]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[220])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[221]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[222])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[224]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[223])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[224]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[225])
      ->set_attributes(
          {new attribute(strings[2558], new named_type(IFC4X1_types[227]),
                         false),
           new attribute(strings[2559], new named_type(IFC4X1_types[226]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[226])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), false),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2560],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[2561],
                                      new named_type(IFC4X1_types[490]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[228])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[229]),
                         true),
           new attribute(
               strings[2562],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[232])),
               true),
           new attribute(
               strings[2563],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[672])),
               true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[230])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[231]), true),
                        new attribute(strings[2370],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2564],
                                      new named_type(IFC4X1_types[268]), true),
                        new attribute(strings[2565],
                                      new named_type(IFC4X1_types[268]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[232])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false});
  ((entity *)IFC4X1_types[234])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[236]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[235])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[236]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[237])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[239]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[238])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[239]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X1_types[240])
      ->set_attributes({new attribute(strings[2531],
                                      new named_type(IFC4X1_types[67]), false)},
                       {false});
  ((entity *)IFC4X1_types[242])
      ->set_attributes(
          {new attribute(strings[2566], new named_type(IFC4X1_types[241]),
                         false)},
          {false});
  ((entity *)IFC4X1_types[244])
      ->set_attributes({new attribute(strings[2567],
                                      new named_type(IFC4X1_types[621]), false),
                        new attribute(strings[2568],
                                      new named_type(IFC4X1_types[621]), false),
                        new attribute(strings[2569],
                                      new named_type(IFC4X1_types[708]), false),
                        new attribute(strings[2570],
                                      new named_type(IFC4X1_types[268]), true),
                        new attribute(strings[2571],
                                      new named_type(IFC4X1_types[531]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[245])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[247]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[246])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[247]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[249])->set_attributes({}, {});
  ((entity *)IFC4X1_types[250])
      ->set_attributes({new attribute(strings[2572],
                                      new named_type(IFC4X1_types[689]), false),
                        new attribute(strings[2394],
                                      new named_type(IFC4X1_types[249]), false),
                        new attribute(strings[2395],
                                      new aggregation_type(
                                          aggregation_type::set_type, 0, -1,
                                          new named_type(IFC4X1_types[249])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[251])
      ->set_attributes(
          {new attribute(strings[2572], new named_type(IFC4X1_types[1026]),
                         false),
           new attribute(strings[2573],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4X1_types[86])),
                         false),
           new attribute(strings[2574], new named_type(IFC4X1_types[80]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[256])
      ->set_attributes(
          {new attribute(strings[2575], new named_type(IFC4X1_types[130]),
                         false),
           new attribute(strings[2576], new named_type(IFC4X1_types[690]),
                         false),
           new attribute(strings[2577], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[257])
      ->set_attributes({new attribute(strings[2578],
                                      new named_type(IFC4X1_types[252]), true),
                        new attribute(strings[2579],
                                      new named_type(IFC4X1_types[929]), true),
                        new attribute(strings[2580],
                                      new named_type(IFC4X1_types[161]), true),
                        new attribute(strings[2581],
                                      new named_type(IFC4X1_types[80]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[258])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2582],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[260])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X1_types[259])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2578], new named_type(IFC4X1_types[261]),
                         false),
           new attribute(strings[2583], new named_type(IFC4X1_types[708]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[260])
      ->set_attributes(
          {new attribute(strings[2584], new named_type(IFC4X1_types[530]),
                         false),
           new attribute(strings[2585], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[262])
      ->set_attributes(
          {new attribute(strings[2385], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[263])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[265]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[264])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[265]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[273])
      ->set_attributes({new attribute(strings[2586],
                                      new named_type(IFC4X1_types[736]), false),
                        new attribute(strings[2465],
                                      new named_type(IFC4X1_types[135]), false),
                        new attribute(strings[2530],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[274])
      ->set_attributes({new attribute(strings[2587],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[275])),
                                      false),
                        new attribute(strings[2588],
                                      new named_type(IFC4X1_types[276]), false),
                        new attribute(strings[2589],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[275])
      ->set_attributes(
          {new attribute(strings[2590], new named_type(IFC4X1_types[626]),
                         false),
           new attribute(strings[2591],
                         new simple_type(simple_type::integer_type), false)},
          {false, false});
  ((entity *)IFC4X1_types[278])
      ->set_attributes(
          {new attribute(strings[2592],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2593],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2594],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2595],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2596],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2597],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2598],
                         new simple_type(simple_type::integer_type), false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[280])
      ->set_attributes({new attribute(strings[2599],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X1_types[796])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[282])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[284]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[283])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[284]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[285])
      ->set_attributes({new attribute(strings[2600],
                                      new named_type(IFC4X1_types[530]), false),
                        new attribute(strings[2601],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2602],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2603],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2604],
                                      new named_type(IFC4X1_types[80]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[286])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[288]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[287])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[288]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[289])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[290])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[291])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[292])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[293])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[294])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[295])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[296])
      ->set_attributes({new attribute(strings[2605],
                                      new named_type(IFC4X1_types[430]), true),
                        new attribute(strings[2369],
                                      new named_type(IFC4X1_types[297]), true),
                        new attribute(strings[2606],
                                      new named_type(IFC4X1_types[299]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[298])
      ->set_attributes({new attribute(strings[2493],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2369],
                                      new named_type(IFC4X1_types[299]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[301])
      ->set_attributes(
          {new attribute(strings[2420], new named_type(IFC4X1_types[490]),
                         false),
           new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         false),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[2514], new named_type(IFC4X1_types[1147]),
                         true),
           new attribute(strings[2376], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[2607], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[2608], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[2609], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2610], new named_type(IFC4X1_types[8]), true),
           new attribute(strings[2611],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4X1_types[8])),
                         true),
           new attribute(strings[2547], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[2612], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[2613], new named_type(IFC4X1_types[490]),
                         true),
           new attribute(strings[2614], new named_type(IFC4X1_types[267]),
                         true),
           new attribute(strings[2615], new named_type(IFC4X1_types[267]),
                         true),
           new attribute(strings[2616], new named_type(IFC4X1_types[300]),
                         true),
           new attribute(strings[2370], new named_type(IFC4X1_types[305]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[302])
      ->set_attributes({new attribute(strings[2617],
                                      new named_type(IFC4X1_types[301]), false),
                        new attribute(strings[2618],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[301])),
                                      false),
                        new attribute(strings[2619],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[303])
      ->set_attributes({new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2620],
                                      new named_type(IFC4X1_types[301]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[306])
      ->set_attributes({new attribute(strings[2621],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2622],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2369],
                                      new named_type(IFC4X1_types[316]), true),
                        new attribute(strings[2623],
                                      new named_type(IFC4X1_types[317]), true),
                        new attribute(strings[2624],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X1_types[307])
      ->set_attributes({new attribute(strings[2625],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2626],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2627],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2628],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2629],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2630],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2631],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2632],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2633],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2634],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2635],
                                      new named_type(IFC4X1_types[915]), true),
                        new attribute(strings[2636],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2637],
                                      new named_type(IFC4X1_types[530]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false, false,
                        false});
  ((entity *)IFC4X1_types[310])
      ->set_attributes(
          {new attribute(strings[2638], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2639], new named_type(IFC4X1_types[308]),
                         false),
           new attribute(strings[2640], new named_type(IFC4X1_types[628]),
                         true),
           new attribute(strings[2641], new named_type(IFC4X1_types[309]),
                         false),
           new attribute(strings[2635], new named_type(IFC4X1_types[915]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[311])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false, false});
  ((entity *)IFC4X1_types[312])
      ->set_attributes({new attribute(strings[2623],
                                      new named_type(IFC4X1_types[314]), false),
                        new attribute(strings[2642],
                                      new named_type(IFC4X1_types[313]), false),
                        new attribute(strings[2643],
                                      new named_type(IFC4X1_types[80]), false),
                        new attribute(strings[2644],
                                      new named_type(IFC4X1_types[80]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X1_types[315])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[316]),
                         false),
           new attribute(strings[2623], new named_type(IFC4X1_types[317]),
                         false),
           new attribute(strings[2643], new named_type(IFC4X1_types[80]), true),
           new attribute(strings[2624], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X1_types[319])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[320])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[321])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[323]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[322])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[323]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[324])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[326]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[325])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[326]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[327])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[329]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[328])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[329]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[332])
      ->set_attributes(
          {new attribute(strings[2645], new named_type(IFC4X1_types[1156]),
                         false),
           new attribute(strings[2646], new named_type(IFC4X1_types[1156]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[333])
      ->set_attributes({new attribute(strings[2647],
                                      new named_type(IFC4X1_types[249]), false),
                        new attribute(strings[2527],
                                      new named_type(IFC4X1_types[80]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[334])
      ->set_attributes({new attribute(strings[2648],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[651])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[335])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[337]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[336])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[337]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[342])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[344]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[343])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[344]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[345])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[347]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[346])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[347]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[348])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[350]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[349])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[350]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[351])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[353]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[352])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[353]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[355])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[357]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[356])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[357]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[359])
      ->set_attributes(
          {new attribute(strings[2393], new named_type(IFC4X1_types[490]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[361])
      ->set_attributes(
          {new attribute(strings[2649], new named_type(IFC4X1_types[58]), true),
           new attribute(strings[2369], new named_type(IFC4X1_types[363]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[362])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[363]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[364])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[365])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[367])
      ->set_attributes({new attribute(strings[2650],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2651],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[672])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[368])
      ->set_attributes(
          {new attribute(strings[2652], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[360])
      ->set_attributes({new attribute(strings[2531],
                                      new named_type(IFC4X1_types[67]), false)},
                       {false});
  ((entity *)IFC4X1_types[369])
      ->set_attributes(
          {new attribute(strings[2653], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2654], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[370])
      ->set_attributes(
          {new attribute(strings[2653], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2654], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[371])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[372])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[374])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[376]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[375])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[376]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[377])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[379]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[378])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[379]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[380])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[382]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[381])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[382]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[383])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[387]), true),
                        new attribute(strings[2655],
                                      new named_type(IFC4X1_types[385]), true),
                        new attribute(strings[2656],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2657],
                                      new named_type(IFC4X1_types[384]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[384])
      ->set_attributes({new attribute(strings[2658],
                                      new named_type(IFC4X1_types[268]), true),
                        new attribute(strings[2659],
                                      new named_type(IFC4X1_types[268]), true),
                        new attribute(strings[2660],
                                      new named_type(IFC4X1_types[268]), true),
                        new attribute(strings[2661],
                                      new named_type(IFC4X1_types[268]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[386])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[387]), false),
                        new attribute(strings[2655],
                                      new named_type(IFC4X1_types[385]), false),
                        new attribute(strings[2656],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X1_types[388])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2662],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[747])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[389])->set_attributes({}, {});
  ((entity *)IFC4X1_types[393])
      ->set_attributes({new attribute(strings[2514],
                                      new named_type(IFC4X1_types[1147]), true),
                        new attribute(strings[2420],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[394])
      ->set_attributes({new attribute(strings[2663],
                                      new named_type(IFC4X1_types[393]), false),
                        new attribute(strings[2664],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[877])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[395])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[396]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[397])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[390])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X1_types[391])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X1_types[392])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X1_types[398])
      ->set_attributes(
          {new attribute(strings[2665], new named_type(IFC4X1_types[280]),
                         false),
           new attribute(strings[2494], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[399])
      ->set_attributes(
          {new attribute(strings[2666], new named_type(IFC4X1_types[736]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[400])
      ->set_attributes({new attribute(strings[2667],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[402])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[401])
      ->set_attributes({new attribute(strings[2668],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[189])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[402])
      ->set_attributes({new attribute(strings[2669],
                                      new named_type(IFC4X1_types[561]), false),
                        new attribute(strings[2670],
                                      new named_type(IFC4X1_types[80]), false)},
                       {false, false});
  ((entity *)IFC4X1_types[403])->set_attributes({}, {false, false});
  ((entity *)IFC4X1_types[404])
      ->set_attributes(
          {new attribute(strings[2671], new named_type(IFC4X1_types[1026]),
                         false),
           new attribute(strings[2527], new named_type(IFC4X1_types[80]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[405])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[406])
      ->set_attributes({new attribute(strings[2378],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[157])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X1_types[407])
      ->set_attributes({new attribute(strings[2672],
                                      new named_type(IFC4X1_types[455]), true),
                        new attribute(strings[2673],
                                      new named_type(IFC4X1_types[455]), true),
                        new attribute(strings[2674],
                                      new named_type(IFC4X1_types[455]), true),
                        new attribute(strings[2675],
                                      new named_type(IFC4X1_types[455]), true),
                        new attribute(strings[2676],
                                      new named_type(IFC4X1_types[455]), true),
                        new attribute(strings[2677],
                                      new named_type(IFC4X1_types[455]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[408])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[410]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[409])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[410]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[411])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[413]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[412])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[413]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[414])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[415])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[416])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[417])
      ->set_attributes({new attribute(strings[2678],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[420])),
                                      false),
                        new attribute(strings[2679],
                                      new named_type(IFC4X1_types[80]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[418])
      ->set_attributes(
          {new attribute(strings[2680], new named_type(IFC4X1_types[257]),
                         false),
           new attribute(strings[2681], new named_type(IFC4X1_types[481]),
                         false),
           new attribute(strings[2682], new named_type(IFC4X1_types[130]),
                         true),
           new attribute(strings[2683], new named_type(IFC4X1_types[130]),
                         true),
           new attribute(strings[2684], new named_type(IFC4X1_types[690]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[419])
      ->set_attributes(
          {new attribute(
               strings[2685],
               new aggregation_type(aggregation_type::list_type, 2, 2,
                                    new named_type(IFC4X1_types[1154])),
               false),
           new attribute(
               strings[2686],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[1019])),
               false),
           new attribute(strings[2687], new named_type(IFC4X1_types[708]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[421])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[423]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[422])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[423]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[424])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[426]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[425])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[426]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[427])
      ->set_attributes(
          {new attribute(strings[2688], new named_type(IFC4X1_types[249]),
                         false),
           new attribute(strings[2689], new named_type(IFC4X1_types[658]),
                         true),
           new attribute(strings[2690], new named_type(IFC4X1_types[658]),
                         true),
           new attribute(strings[2691], new named_type(IFC4X1_types[280]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[428])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[429])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[431])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[432])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[433])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[435]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[434])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[435]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[436])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[438]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[437])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[438]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[439])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[440])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[441])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[442])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[443])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[444])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[445])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[446])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[447])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[448])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[452])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[454]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[453])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[454]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[457])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[458])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[459])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[461]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[460])
      ->set_attributes({new attribute(strings[2649],
                                      new named_type(IFC4X1_types[58]), false),
                        new attribute(strings[2369],
                                      new named_type(IFC4X1_types[461]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[462])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[464]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[463])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[464]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[465])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[467])
      ->set_attributes({new attribute(strings[2692],
                                      new named_type(IFC4X1_types[279]), false),
                        new attribute(strings[2693],
                                      new named_type(IFC4X1_types[796]), true),
                        new attribute(strings[2694],
                                      new named_type(IFC4X1_types[65]), false),
                        new attribute(strings[2695],
                                      new named_type(IFC4X1_types[280]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[468])->set_attributes({}, {});
  ((entity *)IFC4X1_types[469])
      ->set_attributes(
          {new attribute(strings[2696], new named_type(IFC4X1_types[467]),
                         false),
           new attribute(strings[2697], new named_type(IFC4X1_types[708]),
                         true),
           new attribute(strings[2698], new named_type(IFC4X1_types[466]),
                         false),
           new attribute(strings[2699], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, true, true, true, true, false, false, false, false});
  ((entity *)IFC4X1_types[470])
      ->set_attributes({new attribute(strings[2587],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[471])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[474])
      ->set_attributes({new attribute(strings[2700],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[475])),
                                      false),
                        new attribute(strings[2701],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[475])),
                                      false),
                        new attribute(strings[2702],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[475])),
                                      true),
                        new attribute(strings[2369],
                                      new named_type(IFC4X1_types[478]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[475])
      ->set_attributes({new attribute(strings[2703],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2704],
                                      new named_type(IFC4X1_types[249]), false),
                        new attribute(strings[2527],
                                      new named_type(IFC4X1_types[80]), false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[476])
      ->set_attributes(
          {new attribute(strings[2705], new named_type(IFC4X1_types[1163]),
                         false),
           new attribute(strings[2706], new named_type(IFC4X1_types[477]),
                         true)},
          {false, false});
  ((entity *)IFC4X1_types[479])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC4X1_types[480])
      ->set_attributes(
          {new attribute(strings[2707], new named_type(IFC4X1_types[1026]),
                         false),
           new attribute(strings[2708], new named_type(IFC4X1_types[80]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[482])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[484]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[483])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[484]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[487])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[489]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[488])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[489]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[512])
      ->set_attributes({new attribute(strings[2622],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2430],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2431],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2709],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2710],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2711],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2712],
                                      new named_type(IFC4X1_types[690]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[492])
      ->set_attributes(
          {new attribute(strings[2713], new named_type(IFC4X1_types[1147]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[493])
      ->set_attributes(
          {new attribute(strings[2714], new named_type(IFC4X1_types[1076]),
                         false),
           new attribute(strings[2715], new named_type(IFC4X1_types[628]),
                         true),
           new attribute(strings[2716], new named_type(IFC4X1_types[164]),
                         false),
           new attribute(
               strings[2717],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[705])),
               false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[494])
      ->set_attributes({new attribute(strings[2718],
                                      new named_type(IFC4X1_types[131]), false),
                        new attribute(strings[2380],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[907])),
                                      true),
                        new attribute(strings[2447],
                                      new named_type(IFC4X1_types[80]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[495])
      ->set_attributes({new attribute(strings[2719],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC4X1_types[705])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[496])
      ->set_attributes(
          {new attribute(
              strings[2720],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, -1,
                                       new named_type(IFC4X1_types[705]))),
              false)},
          {false, false});
  ((entity *)IFC4X1_types[497])
      ->set_attributes(
          {new attribute(strings[2714], new named_type(IFC4X1_types[1076]),
                         false),
           new attribute(strings[2721], new named_type(IFC4X1_types[1095]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[498])
      ->set_attributes(
          {new attribute(
              strings[2722],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, 3,
                                       new named_type(IFC4X1_types[705]))),
              true)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[502])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[504]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[503])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[504]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[506])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X1_types[507])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[508]),
                         true),
           new attribute(strings[2723], new named_type(IFC4X1_types[8]), true),
           new attribute(
               strings[2724],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[667])),
               true),
           new attribute(strings[2725], new named_type(IFC4X1_types[267]),
                         true),
           new attribute(strings[2422], new named_type(IFC4X1_types[232]),
                         true),
           new attribute(strings[2421], new named_type(IFC4X1_types[232]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[510])
      ->set_attributes(
          {new attribute(
              strings[2726],
              new aggregation_type(aggregation_type::list_type, 1, -1,
                                   new named_type(IFC4X1_types[511])),
              false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[511])
      ->set_attributes({new attribute(strings[2727],
                                      new named_type(IFC4X1_types[268]), false),
                        new attribute(strings[2728],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[1149])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X1_types[514])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[516]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[515])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[516]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[562])
      ->set_attributes(
          {new attribute(strings[2494], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2495], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2509], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2710], new named_type(IFC4X1_types[627]),
                         true),
           new attribute(strings[2729], new named_type(IFC4X1_types[627]),
                         true),
           new attribute(strings[2730], new named_type(IFC4X1_types[690]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[520])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[522]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[521])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[522]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X1_types[523])
      ->set_attributes(
          {new attribute(strings[2731], new named_type(IFC4X1_types[1104]),
                         false),
           new attribute(strings[2732], new named_type(IFC4X1_types[1062]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[524])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[526]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[525])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[526]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[531])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         false),
           new attribute(strings[2397], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2733], new named_type(IFC4X1_types[8]), true),
           new attribute(strings[2734], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[2514], new named_type(IFC4X1_types[1147]),
                         true),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[532])
      ->set_attributes({new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2735],
                                      new named_type(IFC4X1_types[527]), true),
                        new attribute(strings[2736],
                                      new named_type(IFC4X1_types[531]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[535])
      ->set_attributes({new attribute(strings[2737],
                                      new named_type(IFC4X1_types[690]), false),
                        new attribute(strings[2738],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[690])),
                                      false),
                        new attribute(strings[2739],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[564])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[538])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[540]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[539])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[540]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[541])
      ->set_attributes({new attribute(strings[2740],
                                      new named_type(IFC4X1_types[534]), false),
                        new attribute(strings[2741],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[535])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X1_types[542])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2742],
                                      new named_type(IFC4X1_types[163]), false),
                        new attribute(strings[2743],
                                      new named_type(IFC4X1_types[628]), true),
                        new attribute(strings[2744],
                                      new named_type(IFC4X1_types[628]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[543])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[544])
      ->set_attributes(
          {new attribute(strings[2670], new named_type(IFC4X1_types[280]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[545])
      ->set_attributes(
          {new attribute(strings[2531], new named_type(IFC4X1_types[67]),
                         false),
           new attribute(strings[2745], new named_type(IFC4X1_types[163]),
                         true),
           new attribute(strings[2746], new named_type(IFC4X1_types[1101]),
                         false),
           new attribute(strings[2747], new named_type(IFC4X1_types[563]),
                         false),
           new attribute(strings[2748], new named_type(IFC4X1_types[537]),
                         false),
           new attribute(strings[2749], new named_type(IFC4X1_types[536]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[546])
      ->set_attributes(
          {new attribute(strings[2531], new named_type(IFC4X1_types[130]),
                         false),
           new attribute(strings[2385], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2750], new named_type(IFC4X1_types[796]),
                         false),
           new attribute(strings[2751], new named_type(IFC4X1_types[796]),
                         false),
           new attribute(strings[2752], new named_type(IFC4X1_types[796]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[547])
      ->set_attributes(
          {new attribute(strings[2670], new named_type(IFC4X1_types[280]),
                         false),
           new attribute(strings[2753], new named_type(IFC4X1_types[796]),
                         true),
           new attribute(strings[2754], new named_type(IFC4X1_types[707]),
                         false),
           new attribute(strings[2755], new named_type(IFC4X1_types[707]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X1_types[548])
      ->set_attributes(
          {new attribute(strings[2756], new named_type(IFC4X1_types[130]),
                         false),
           new attribute(strings[2757], new named_type(IFC4X1_types[1154]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[556])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X1_types[551])
      ->set_attributes({new attribute(strings[2758],
                                      new named_type(IFC4X1_types[249]), false),
                        new attribute(strings[2759],
                                      new named_type(IFC4X1_types[285]), false),
                        new attribute(strings[2670],
                                      new named_type(IFC4X1_types[650]), true),
                        new attribute(strings[2760],
                                      new named_type(IFC4X1_types[67]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[552])
      ->set_attributes(
          {new attribute(strings[2441], new named_type(IFC4X1_types[249]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[558])
      ->set_attributes({new attribute(strings[2758],
                                      new named_type(IFC4X1_types[635]), true),
                        new attribute(strings[2761],
                                      new named_type(IFC4X1_types[65]), false)},
                       {false, false});
  ((entity *)IFC4X1_types[561])->set_attributes({}, {});
  ((entity *)IFC4X1_types[568])
      ->set_attributes(
          {new attribute(strings[2762], new named_type(IFC4X1_types[157]),
                         false)},
          {false});
  ((entity *)IFC4X1_types[569])
      ->set_attributes(
          {new attribute(strings[2763], new named_type(IFC4X1_types[530]),
                         false),
           new attribute(strings[2764], new named_type(IFC4X1_types[530]),
                         false),
           new attribute(strings[2765], new named_type(IFC4X1_types[530]),
                         false),
           new attribute(strings[2766], new named_type(IFC4X1_types[796]),
                         true),
           new attribute(strings[2767], new named_type(IFC4X1_types[796]),
                         true),
           new attribute(strings[2505], new named_type(IFC4X1_types[796]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[570])
      ->set_attributes(
          {new attribute(strings[2768], new named_type(IFC4X1_types[872]),
                         false),
           new attribute(strings[2769], new named_type(IFC4X1_types[134]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[575])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), false),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2405],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[576])
      ->set_attributes(
          {new attribute(
               strings[2770],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[156])),
               false),
           new attribute(strings[2771], new named_type(IFC4X1_types[575]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[577])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2772],
                                      new named_type(IFC4X1_types[575]), false),
                        new attribute(strings[2773],
                                      new named_type(IFC4X1_types[628]), true),
                        new attribute(strings[2405],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[578])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2774],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[577])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[579])->set_attributes({}, {});
  ((entity *)IFC4X1_types[580])
      ->set_attributes(
          {new attribute(strings[2775], new named_type(IFC4X1_types[575]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[581])
      ->set_attributes({new attribute(strings[2772],
                                      new named_type(IFC4X1_types[575]), true),
                        new attribute(strings[2776],
                                      new named_type(IFC4X1_types[627]), false),
                        new attribute(strings[2777],
                                      new named_type(IFC4X1_types[559]), true),
                        new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2405],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2778],
                                      new named_type(IFC4X1_types[500]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[582])
      ->set_attributes(
          {new attribute(
               strings[2779],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[581])),
               false),
           new attribute(strings[2780], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X1_types[583])
      ->set_attributes({new attribute(strings[2781],
                                      new named_type(IFC4X1_types[582]), false),
                        new attribute(strings[2782],
                                      new named_type(IFC4X1_types[529]), false),
                        new attribute(strings[2783],
                                      new named_type(IFC4X1_types[281]), false),
                        new attribute(strings[2784],
                                      new named_type(IFC4X1_types[530]), false),
                        new attribute(strings[2785],
                                      new named_type(IFC4X1_types[706]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[584])
      ->set_attributes(
          {new attribute(strings[2786], new named_type(IFC4X1_types[529]),
                         false),
           new attribute(
               strings[2787],
               new aggregation_type(aggregation_type::array_type, 1, 2,
                                    new named_type(IFC4X1_types[530])),
               false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[585])
      ->set_attributes({new attribute(strings[2788],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[575])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[586])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2772],
                                      new named_type(IFC4X1_types[575]), true),
                        new attribute(strings[2789],
                                      new named_type(IFC4X1_types[736]), false),
                        new attribute(strings[2778],
                                      new named_type(IFC4X1_types[500]), true),
                        new attribute(strings[2405],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[587])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2790],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[586])),
                                      false),
                        new attribute(strings[2791],
                                      new named_type(IFC4X1_types[180]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[588])
      ->set_attributes({new attribute(strings[2792],
                                      new named_type(IFC4X1_types[587]), false),
                        new attribute(strings[2793],
                                      new named_type(IFC4X1_types[129]), true),
                        new attribute(strings[2785],
                                      new named_type(IFC4X1_types[706]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[589])
      ->set_attributes({new attribute(strings[2794],
                                      new named_type(IFC4X1_types[587]), false),
                        new attribute(strings[2795],
                                      new named_type(IFC4X1_types[129]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[590])
      ->set_attributes({new attribute(strings[2787],
                                      new aggregation_type(
                                          aggregation_type::array_type, 1, 2,
                                          new named_type(IFC4X1_types[530])),
                                      false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[591])
      ->set_attributes(
          {new attribute(strings[2772], new named_type(IFC4X1_types[579]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[592])
      ->set_attributes({new attribute(strings[2796],
                                      new named_type(IFC4X1_types[575]), false),
                        new attribute(strings[2797],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[575])),
                                      false),
                        new attribute(strings[2798],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[594])->set_attributes({}, {});
  ((entity *)IFC4X1_types[596])
      ->set_attributes(
          {new attribute(strings[2799], new named_type(IFC4X1_types[1149]),
                         false),
           new attribute(strings[2800], new named_type(IFC4X1_types[1138]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[597])
      ->set_attributes({new attribute(strings[2801],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2802],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2369],
                                      new named_type(IFC4X1_types[599]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[598])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[599]), false),
                        new attribute(strings[2801],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2802],
                                      new named_type(IFC4X1_types[706]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X1_types[600])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[602]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[601])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[602]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[603])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[606]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[604])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[605])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[606]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[607])
      ->set_attributes({new attribute(strings[2803],
                                      new named_type(IFC4X1_types[72]), false),
                        new attribute(strings[2804],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2805],
                                      new named_type(IFC4X1_types[608]), true),
                        new attribute(strings[2806],
                                      new named_type(IFC4X1_types[803]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[609])
      ->set_attributes({}, {false, false, false, true, false});
  ((entity *)IFC4X1_types[621])
      ->set_attributes(
          {new attribute(strings[2807], new named_type(IFC4X1_types[519]),
                         false)},
          {false});
  ((entity *)IFC4X1_types[623])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[625]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[624])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[625]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[626])
      ->set_attributes(
          {new attribute(strings[2808], new named_type(IFC4X1_types[278]),
                         false),
           new attribute(strings[2588], new named_type(IFC4X1_types[1146]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[631])
      ->set_attributes({new attribute(strings[2552],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[632])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[635])->set_attributes({}, {});
  ((entity *)IFC4X1_types[633])
      ->set_attributes({new attribute(strings[2809],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[197])),
                                      true),
                        new attribute(strings[2810],
                                      new named_type(IFC4X1_types[560]), true),
                        new attribute(strings[2811],
                                      new named_type(IFC4X1_types[634]), false),
                        new attribute(strings[2812],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[638])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[639]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[640])
      ->set_attributes(
          {new attribute(strings[2813], new named_type(IFC4X1_types[249]),
                         false)},
          {false});
  ((entity *)IFC4X1_types[641])
      ->set_attributes(
          {new attribute(strings[2759], new named_type(IFC4X1_types[530]),
                         false),
           new attribute(strings[2447], new named_type(IFC4X1_types[559]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[642])
      ->set_attributes(
          {new attribute(strings[2759], new named_type(IFC4X1_types[530]),
                         false),
           new attribute(strings[2447], new named_type(IFC4X1_types[559]),
                         false),
           new attribute(strings[2442], new named_type(IFC4X1_types[280]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[643])
      ->set_attributes({new attribute(strings[2787],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[285])),
                                      false),
                        new attribute(strings[2393],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[647])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[644])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[645]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[646])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[648])
      ->set_attributes({new attribute(strings[2420],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), false),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2814],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[7])),
                                      true),
                        new attribute(strings[2815],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[12])),
                                      true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[649])
      ->set_attributes({new attribute(strings[2816],
                                      new named_type(IFC4X1_types[648]), false),
                        new attribute(strings[2817],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[648])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[650])
      ->set_attributes(
          {new attribute(strings[2818], new named_type(IFC4X1_types[280]),
                         false),
           new attribute(strings[2819], new named_type(IFC4X1_types[280]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[651])
      ->set_attributes({new attribute(strings[2820],
                                      new named_type(IFC4X1_types[332]), false),
                        new attribute(strings[2670],
                                      new named_type(IFC4X1_types[80]), false)},
                       {true, true, false, false});
  ((entity *)IFC4X1_types[652])->set_attributes({}, {false, false});
  ((entity *)IFC4X1_types[653])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[655]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[654])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[655]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[656])
      ->set_attributes(
          {new attribute(strings[2821], new named_type(IFC4X1_types[668]),
                         false),
           new attribute(strings[2822], new named_type(IFC4X1_types[46]),
                         false),
           new attribute(strings[2823], new named_type(IFC4X1_types[975]),
                         true),
           new attribute(strings[2824], new named_type(IFC4X1_types[140]),
                         true),
           new attribute(strings[2825], new named_type(IFC4X1_types[1109]),
                         true),
           new attribute(strings[2826], new named_type(IFC4X1_types[668]),
                         true),
           new attribute(strings[2827], new named_type(IFC4X1_types[46]), true),
           new attribute(strings[2828], new named_type(IFC4X1_types[1109]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[657])
      ->set_attributes({new attribute(strings[2531],
                                      new named_type(IFC4X1_types[66]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[659])
      ->set_attributes({new attribute(strings[2648],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[651])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[660])
      ->set_attributes(
          {new attribute(strings[2572], new named_type(IFC4X1_types[1026]),
                         false),
           new attribute(strings[2829], new named_type(IFC4X1_types[249]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[661])
      ->set_attributes(
          {new attribute(strings[2830], new named_type(IFC4X1_types[519]),
                         false),
           new attribute(strings[2369], new named_type(IFC4X1_types[662]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[664])
      ->set_attributes(
          {new attribute(strings[2623], new named_type(IFC4X1_types[663]),
                         false),
           new attribute(strings[2641], new named_type(IFC4X1_types[1182]),
                         false),
           new attribute(strings[2831], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2832], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2635], new named_type(IFC4X1_types[915]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[665])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[666]),
                         true),
           new attribute(strings[2370], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2371], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[667])
      ->set_attributes(
          {new attribute(strings[2420], new named_type(IFC4X1_types[490]),
                         true),
           new attribute(strings[2833], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2834], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(
               strings[2835],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[519])),
               true),
           new attribute(
               strings[2836],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[519])),
               true),
           new attribute(
               strings[2837],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[519])),
               true),
           new attribute(strings[2814],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X1_types[7])),
                         true),
           new attribute(strings[2815],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X1_types[12])),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[668])
      ->set_attributes({new attribute(strings[2838],
                                      new named_type(IFC4X1_types[667]), false),
                        new attribute(strings[2839],
                                      new named_type(IFC4X1_types[648]), false),
                        new attribute(strings[2814],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[7])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[670])
      ->set_attributes({new attribute(strings[2840],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[672])),
                                      false),
                        new attribute(strings[2841],
                                      new named_type(IFC4X1_types[519]), false),
                        new attribute(strings[2842],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2549],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[672])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         false),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false});
  ((entity *)IFC4X1_types[673])
      ->set_attributes({new attribute(strings[2590],
                                      new named_type(IFC4X1_types[626]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[674])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[677]), true),
                        new attribute(strings[2642],
                                      new named_type(IFC4X1_types[675]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[676])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[677]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[678])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[680]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[679])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[680]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[681])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[683]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[682])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[683]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[684])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X1_types[500]),
                         false),
           new attribute(strings[2843], new named_type(IFC4X1_types[500]),
                         false),
           new attribute(strings[2844], new named_type(IFC4X1_types[500]),
                         false),
           new attribute(strings[2845],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X1_types[74])),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[685])
      ->set_attributes(
          {new attribute(strings[2514], new named_type(IFC4X1_types[130]),
                         false)},
          {false});
  ((entity *)IFC4X1_types[686])
      ->set_attributes({new attribute(strings[2846],
                                      new named_type(IFC4X1_types[65]), false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[687])
      ->set_attributes(
          {new attribute(strings[2847], new named_type(IFC4X1_types[530]),
                         false),
           new attribute(strings[2848], new named_type(IFC4X1_types[530]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[689])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[691])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[694]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[692])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[693])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[694]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[695])->set_attributes({}, {});
  ((entity *)IFC4X1_types[696])
      ->set_attributes(
          {new attribute(strings[2813], new named_type(IFC4X1_types[249]),
                         false),
           new attribute(strings[2849], new named_type(IFC4X1_types[658]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[697])
      ->set_attributes(
          {new attribute(strings[2572], new named_type(IFC4X1_types[1026]),
                         false),
           new attribute(strings[2850], new named_type(IFC4X1_types[658]),
                         false),
           new attribute(strings[2851], new named_type(IFC4X1_types[658]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[702])
      ->set_attributes({new attribute(strings[2852],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC4X1_types[130])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[699])
      ->set_attributes({new attribute(strings[2531],
                                      new named_type(IFC4X1_types[67]), false),
                        new attribute(strings[2853],
                                      new named_type(IFC4X1_types[91]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[700])
      ->set_attributes(
          {new attribute(strings[2854], new named_type(IFC4X1_types[80]), true),
           new attribute(
               strings[2855],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[495])),
               false),
           new attribute(
               strings[2856],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[705])),
               true)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[701])
      ->set_attributes({new attribute(strings[2718],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X1_types[130])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[703])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[704])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[709])
      ->set_attributes({new attribute(strings[2857],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2858],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[519])),
                                      true),
                        new attribute(strings[2859],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2860],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2861],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2862],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2863],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[711])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[712])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[713])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         false)},
          {false});
  ((entity *)IFC4X1_types[714])->set_attributes({}, {});
  ((entity *)IFC4X1_types[715])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[716])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[719])->set_attributes({}, {});
  ((entity *)IFC4X1_types[720])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), false),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2864],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[528])),
                                      false),
                        new attribute(strings[2409],
                                      new named_type(IFC4X1_types[490]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[721])
      ->set_attributes(
          {new attribute(strings[2865], new named_type(IFC4X1_types[559]),
                         false),
           new attribute(strings[2866], new named_type(IFC4X1_types[559]),
                         false),
           new attribute(strings[2867], new named_type(IFC4X1_types[559]),
                         false),
           new attribute(
               strings[2868],
               new aggregation_type(aggregation_type::set_type, 0, -1,
                                    new named_type(IFC4X1_types[722])),
               false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[722])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false});
  ((entity *)IFC4X1_types[723])
      ->set_attributes({new attribute(strings[2869],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[724])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[726])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[728]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[727])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[728]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[729])
      ->set_attributes(
          {new attribute(strings[2420], new named_type(IFC4X1_types[490]),
                         true),
           new attribute(strings[2371], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[731])
      ->set_attributes({new attribute(strings[2870],
                                      new named_type(IFC4X1_types[635]), true),
                        new attribute(strings[2871],
                                      new named_type(IFC4X1_types[733]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[732])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X1_types[733])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2872],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[869])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[736])
      ->set_attributes({new attribute(strings[2873],
                                      new named_type(IFC4X1_types[738]), false),
                        new attribute(strings[2874],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[737])
      ->set_attributes(
          {new attribute(strings[2875], new named_type(IFC4X1_types[736]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[739])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[744])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[745])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[746]),
                         true),
           new attribute(strings[2370], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2371], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[740])
      ->set_attributes({new attribute(strings[2876],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[2877],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[2878],
                                      new named_type(IFC4X1_types[626]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[742])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[743]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[747])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[490]),
                         false),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false});
  ((entity *)IFC4X1_types[748])->set_attributes({}, {});
  ((entity *)IFC4X1_types[749])
      ->set_attributes(
          {new attribute(strings[2879], new named_type(IFC4X1_types[1149]),
                         true),
           new attribute(strings[2880], new named_type(IFC4X1_types[1149]),
                         true),
           new attribute(strings[2590], new named_type(IFC4X1_types[1138]),
                         true),
           new attribute(strings[2881], new named_type(IFC4X1_types[1149]),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[750])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[751])
      ->set_attributes(
          {new attribute(strings[2882], new named_type(IFC4X1_types[747]),
                         false),
           new attribute(strings[2883], new named_type(IFC4X1_types[747]),
                         false),
           new attribute(strings[2798], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[752])
      ->set_attributes({new attribute(strings[2884],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[1149])),
                                      true),
                        new attribute(strings[2885],
                                      new named_type(IFC4X1_types[753]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[753])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         false),
           new attribute(
               strings[2884],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[1149])),
               false),
           new attribute(strings[2590], new named_type(IFC4X1_types[1138]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X1_types[754])
      ->set_attributes(
          {new attribute(
               strings[2728],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[1149])),
               true),
           new attribute(strings[2590], new named_type(IFC4X1_types[1138]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[755])
      ->set_attributes({new attribute(strings[2522],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2886],
                                      new named_type(IFC4X1_types[636]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[756])
      ->set_attributes({new attribute(strings[2523],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[747])),
                                      false)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[757])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[760])
      ->set_attributes({new attribute(strings[2524],
                                      new named_type(IFC4X1_types[761]), true),
                        new attribute(strings[2887],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[2525],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[764])),
                                      false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[762])
      ->set_attributes(
          {new attribute(strings[2888], new named_type(IFC4X1_types[1149]),
                         true),
           new attribute(strings[2590], new named_type(IFC4X1_types[1138]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[763])
      ->set_attributes(
          {new attribute(
               strings[2889],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[1149])),
               true),
           new attribute(
               strings[2890],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[1149])),
               true),
           new attribute(strings[2798], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[2891], new named_type(IFC4X1_types[1138]),
                         true),
           new attribute(strings[2892], new named_type(IFC4X1_types[1138]),
                         true),
           new attribute(strings[2893], new named_type(IFC4X1_types[253]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[764])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[765])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[766])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[771]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[767])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[769]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[768])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[769]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[770])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[771]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[772])
      ->set_attributes(
          {new attribute(strings[2894], new named_type(IFC4X1_types[637]),
                         false),
           new attribute(strings[2393], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[773])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[775]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[774])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[775]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[776])
      ->set_attributes({new attribute(strings[2895],
                                      new named_type(IFC4X1_types[56]), false),
                        new attribute(strings[2896],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[777])
      ->set_attributes({new attribute(strings[2897],
                                      new named_type(IFC4X1_types[233]), false),
                        new attribute(strings[2896],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[778])
      ->set_attributes({new attribute(strings[2898],
                                      new named_type(IFC4X1_types[530]), false),
                        new attribute(strings[2896],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[779])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[780])
      ->set_attributes(
          {new attribute(strings[2899], new named_type(IFC4X1_types[1103]),
                         false),
           new attribute(strings[2896], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[781])
      ->set_attributes(
          {new attribute(strings[2900], new named_type(IFC4X1_types[1166]),
                         false),
           new attribute(strings[2896], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[782])
      ->set_attributes({new attribute(strings[2901],
                                      new named_type(IFC4X1_types[573]), false),
                        new attribute(strings[2896],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[784])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[786]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[785])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[786]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[787])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[792]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[788])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[790]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[789])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[790]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[791])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[792]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[794])
      ->set_attributes(
          {new attribute(
              strings[2902],
              new aggregation_type(aggregation_type::list_type, 2, -1,
                                   new named_type(IFC4X1_types[796])),
              false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[795])
      ->set_attributes(
          {new attribute(
              strings[2902],
              new aggregation_type(
                  aggregation_type::list_type, 2, -1,
                  new aggregation_type(aggregation_type::list_type, 2, -1,
                                       new named_type(IFC4X1_types[796]))),
              false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X1_types[797])
      ->set_attributes(
          {new attribute(strings[2496], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2903], new named_type(IFC4X1_types[627]),
                         true),
           new attribute(strings[2904], new named_type(IFC4X1_types[627]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[798])
      ->set_attributes(
          {new attribute(strings[2485], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2486], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[799])
      ->set_attributes(
          {new attribute(strings[2462], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2463], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2843], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[800])
      ->set_attributes(
          {new attribute(strings[2572], new named_type(IFC4X1_types[1026]),
                         false),
           new attribute(strings[2905], new named_type(IFC4X1_types[658]),
                         false),
           new attribute(strings[2906], new named_type(IFC4X1_types[658]),
                         false),
           new attribute(strings[2907], new named_type(IFC4X1_types[658]),
                         false),
           new attribute(strings[2908], new named_type(IFC4X1_types[658]),
                         false),
           new attribute(strings[2909], new named_type(IFC4X1_types[80]),
                         false),
           new attribute(strings[2910], new named_type(IFC4X1_types[80]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[801])
      ->set_attributes(
          {new attribute(strings[2911], new named_type(IFC4X1_types[802]),
                         false),
           new attribute(
               strings[2912],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[269])),
               true),
           new attribute(
               strings[2913],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[270])),
               true),
           new attribute(
               strings[2914],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[622])),
               true),
           new attribute(strings[2531], new named_type(IFC4X1_types[500]),
                         true),
           new attribute(strings[2915], new named_type(IFC4X1_types[500]),
                         true),
           new attribute(strings[2916], new named_type(IFC4X1_types[500]),
                         true),
           new attribute(
               strings[2917],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[1105])),
               true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[803])
      ->set_attributes({new attribute(strings[2918],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[2919],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[2920],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2921],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[500])),
                                      true),
                        new attribute(strings[2922],
                                      new named_type(IFC4X1_types[803]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[804])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[805]),
                         true),
           new attribute(strings[2923], new named_type(IFC4X1_types[530]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[807])
      ->set_attributes(
          {new attribute(strings[2924], new named_type(IFC4X1_types[1103]),
                         false),
           new attribute(
               strings[2726],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[1108])),
               false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[808])
      ->set_attributes({new attribute(strings[2925],
                                      new named_type(IFC4X1_types[56]), false),
                        new attribute(strings[2926],
                                      new named_type(IFC4X1_types[519]), false),
                        new attribute(strings[2927],
                                      new named_type(IFC4X1_types[812]), true),
                        new attribute(strings[2928],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2929],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2930],
                                      new named_type(IFC4X1_types[233]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[809])
      ->set_attributes({new attribute(strings[2931],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2932],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[905])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[810])
      ->set_attributes(
          {new attribute(strings[2801], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2933], new named_type(IFC4X1_types[56]), true),
           new attribute(strings[2934], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2369], new named_type(IFC4X1_types[814]),
                         true),
           new attribute(strings[2927], new named_type(IFC4X1_types[812]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X1_types[813])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[814]),
                         false),
           new attribute(strings[2801], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2933], new named_type(IFC4X1_types[56]), true),
           new attribute(strings[2934], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2927], new named_type(IFC4X1_types[812]),
                         true),
           new attribute(strings[2935], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2936],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X1_types[73])),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4X1_types[815])
      ->set_attributes(
          {new attribute(strings[2926], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[816])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[817])
      ->set_attributes(
          {new attribute(strings[2937], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2938], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2939], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2940], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2941], new named_type(IFC4X1_types[56]), true),
           new attribute(strings[2942], new named_type(IFC4X1_types[56]), true),
           new attribute(strings[2943], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2944], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2369], new named_type(IFC4X1_types[819]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[818])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[819]),
                         false),
           new attribute(strings[2937], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2938], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2939], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2940], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2941], new named_type(IFC4X1_types[56]), true),
           new attribute(strings[2942], new named_type(IFC4X1_types[56]), true),
           new attribute(strings[2943], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2944], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2935], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2936],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X1_types[73])),
                         true)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4X1_types[820])
      ->set_attributes({new attribute(strings[2945],
                                      new named_type(IFC4X1_types[632]), false),
                        new attribute(strings[2946],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[632])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[821])
      ->set_attributes({new attribute(strings[2946],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[632])),
                                      false),
                        new attribute(strings[2947],
                                      new named_type(IFC4X1_types[637]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[822])
      ->set_attributes(
          {new attribute(strings[2948], new named_type(IFC4X1_types[6]), false),
           new attribute(strings[2949], new named_type(IFC4X1_types[7]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[823])
      ->set_attributes(
          {new attribute(strings[2950], new named_type(IFC4X1_types[213]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[824])
      ->set_attributes(
          {new attribute(strings[2951], new named_type(IFC4X1_types[479]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[825])
      ->set_attributes(
          {new attribute(strings[2952], new named_type(IFC4X1_types[793]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[826])
      ->set_attributes(
          {new attribute(strings[2953], new named_type(IFC4X1_types[730]),
                         false),
           new attribute(strings[2954], new named_type(IFC4X1_types[596]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[827])
      ->set_attributes(
          {new attribute(strings[2955], new named_type(IFC4X1_types[735]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[828])
      ->set_attributes(
          {new attribute(strings[2956], new named_type(IFC4X1_types[878]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[829])
      ->set_attributes({new attribute(strings[2946],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[271])),
                                      false)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[830])
      ->set_attributes({new attribute(strings[2415],
                                      new named_type(IFC4X1_types[49]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[831])
      ->set_attributes(
          {new attribute(strings[2957], new named_type(IFC4X1_types[156]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[832])
      ->set_attributes(
          {new attribute(strings[2958], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2959], new named_type(IFC4X1_types[197]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[833])
      ->set_attributes(
          {new attribute(strings[2617], new named_type(IFC4X1_types[304]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[834])
      ->set_attributes(
          {new attribute(strings[2960], new named_type(IFC4X1_types[533]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[835])
      ->set_attributes(
          {new attribute(strings[2796], new named_type(IFC4X1_types[593]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[837])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[838])
      ->set_attributes(
          {new attribute(strings[2961], new named_type(IFC4X1_types[191]),
                         true),
           new attribute(strings[2962], new named_type(IFC4X1_types[359]),
                         false),
           new attribute(strings[2963], new named_type(IFC4X1_types[359]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[839])
      ->set_attributes(
          {new attribute(
               strings[2964],
               new aggregation_type(aggregation_type::list_type, 0, -1,
                                    new named_type(IFC4X1_types[500])),
               false),
           new attribute(
               strings[2965],
               new aggregation_type(aggregation_type::list_type, 0, -1,
                                    new named_type(IFC4X1_types[500])),
               false),
           new attribute(strings[2966], new named_type(IFC4X1_types[195]),
                         false),
           new attribute(strings[2967], new named_type(IFC4X1_types[195]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[841])
      ->set_attributes(
          {new attribute(strings[2968], new named_type(IFC4X1_types[703]),
                         false),
           new attribute(strings[2963], new named_type(IFC4X1_types[292]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[840])
      ->set_attributes({new attribute(strings[2968],
                                      new named_type(IFC4X1_types[703]), false),
                        new attribute(strings[2969],
                                      new named_type(IFC4X1_types[703]), false),
                        new attribute(strings[2970],
                                      new named_type(IFC4X1_types[359]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[842])
      ->set_attributes(
          {new attribute(strings[2962], new named_type(IFC4X1_types[978]),
                         false),
           new attribute(strings[2971], new named_type(IFC4X1_types[977]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[843])
      ->set_attributes(
          {new attribute(strings[2972], new named_type(IFC4X1_types[1004]),
                         false),
           new attribute(strings[2973], new named_type(IFC4X1_types[980]),
                         false),
           new attribute(strings[2974], new named_type(IFC4X1_types[85]), true),
           new attribute(strings[2975], new named_type(IFC4X1_types[981]),
                         true),
           new attribute(strings[2976], new named_type(IFC4X1_types[530]),
                         true),
           new attribute(strings[2977], new named_type(IFC4X1_types[67]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[844])
      ->set_attributes(
          {new attribute(strings[2978], new named_type(IFC4X1_types[191]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[845])
      ->set_attributes(
          {new attribute(
               strings[2979],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[359])),
               false),
           new attribute(strings[2980], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[846])
      ->set_attributes(
          {new attribute(
               strings[2981],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[731])),
               false),
           new attribute(strings[2982], new named_type(IFC4X1_types[953]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[847])
      ->set_attributes({new attribute(strings[2983],
                                      new named_type(IFC4X1_types[359]), false),
                        new attribute(strings[2984],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[234])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[848])
      ->set_attributes({new attribute(strings[2985],
                                      new named_type(IFC4X1_types[946]), false),
                        new attribute(strings[2984],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[234])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[849])
      ->set_attributes({new attribute(strings[2986],
                                      new named_type(IFC4X1_types[210]), false),
                        new attribute(strings[2987],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[271])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[850])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[851])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[852])
      ->set_attributes(
          {new attribute(
               strings[2946],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[631])),
               false),
           new attribute(strings[2945], new named_type(IFC4X1_types[631]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[853])
      ->set_attributes(
          {new attribute(
               strings[2946],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[632])),
               false),
           new attribute(strings[2988], new named_type(IFC4X1_types[758]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[854])
      ->set_attributes(
          {new attribute(
               strings[2989],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[757])),
               false),
           new attribute(strings[2990], new named_type(IFC4X1_types[760]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[855])
      ->set_attributes(
          {new attribute(
               strings[2946],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[631])),
               false),
           new attribute(strings[2991], new named_type(IFC4X1_types[1134]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[856])
      ->set_attributes(
          {new attribute(strings[2992], new named_type(IFC4X1_types[644]),
                         false),
           new attribute(strings[2993], new named_type(IFC4X1_types[359]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[857])
      ->set_attributes(
          {new attribute(
               strings[2994],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[290])),
               false),
           new attribute(strings[2995], new named_type(IFC4X1_types[294]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[858])
      ->set_attributes(
          {new attribute(strings[2962], new named_type(IFC4X1_types[359]),
                         false),
           new attribute(strings[2963], new named_type(IFC4X1_types[359]),
                         false),
           new attribute(strings[2996], new named_type(IFC4X1_types[191]),
                         true),
           new attribute(strings[2997], new named_type(IFC4X1_types[490]),
                         true),
           new attribute(strings[2998],
                         new simple_type(simple_type::logical_type), false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[859])
      ->set_attributes({new attribute(strings[2945],
                                      new named_type(IFC4X1_types[632]), false),
                        new attribute(strings[2946],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[632])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[860])
      ->set_attributes(
          {new attribute(strings[2962], new named_type(IFC4X1_types[359]),
                         false),
           new attribute(strings[2999], new named_type(IFC4X1_types[415]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[861])
      ->set_attributes(
          {new attribute(
               strings[2981],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[731])),
               false),
           new attribute(strings[2982], new named_type(IFC4X1_types[953]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[862])
      ->set_attributes(
          {new attribute(strings[2953], new named_type(IFC4X1_types[729]),
                         false),
           new attribute(strings[3000], new named_type(IFC4X1_types[729]),
                         false),
           new attribute(strings[3001], new named_type(IFC4X1_types[523]),
                         true),
           new attribute(strings[3002], new named_type(IFC4X1_types[911]),
                         true),
           new attribute(strings[3003], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[863])
      ->set_attributes(
          {new attribute(strings[3004], new named_type(IFC4X1_types[1051]),
                         false),
           new attribute(
               strings[3005],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[953])),
               false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[864])
      ->set_attributes(
          {new attribute(strings[2985], new named_type(IFC4X1_types[947]),
                         false),
           new attribute(strings[2993], new named_type(IFC4X1_types[359]),
                         false),
           new attribute(strings[2961], new named_type(IFC4X1_types[191]),
                         true),
           new attribute(strings[3006], new named_type(IFC4X1_types[671]),
                         false),
           new attribute(strings[3007], new named_type(IFC4X1_types[505]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[865])
      ->set_attributes({new attribute(strings[3008],
                                      new named_type(IFC4X1_types[865]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[866])
      ->set_attributes({new attribute(strings[3009],
                                      new named_type(IFC4X1_types[866]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[867])
      ->set_attributes(
          {new attribute(strings[2983], new named_type(IFC4X1_types[359]),
                         false),
           new attribute(strings[3010], new named_type(IFC4X1_types[416]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[836])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[868])
      ->set_attributes(
          {new attribute(strings[3011], new named_type(IFC4X1_types[658]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[869])
      ->set_attributes({new attribute(strings[3012],
                                      new named_type(IFC4X1_types[870]), false),
                        new attribute(strings[3013],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[3014],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[3015],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[871])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[870])
      ->set_attributes({new attribute(strings[3016],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[3017],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[871])->set_attributes({}, {});
  ((entity *)IFC4X1_types[872])
      ->set_attributes(
          {new attribute(strings[3018], new named_type(IFC4X1_types[65]),
                         false),
           new attribute(strings[3019], new named_type(IFC4X1_types[869]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[873])
      ->set_attributes(
          {new attribute(strings[2420], new named_type(IFC4X1_types[490]),
                         true),
           new attribute(strings[2371], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[874])
      ->set_attributes({new attribute(strings[2664],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[877])),
                                      false),
                        new attribute(strings[2415],
                                      new named_type(IFC4X1_types[49]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[875])
      ->set_attributes({new attribute(strings[2959],
                                      new named_type(IFC4X1_types[197]), false),
                        new attribute(strings[2664],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[877])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[876])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false});
  ((entity *)IFC4X1_types[879])
      ->set_attributes(
          {new attribute(strings[3020], new named_type(IFC4X1_types[330]),
                         true),
           new attribute(strings[3021], new named_type(IFC4X1_types[708]),
                         true),
           new attribute(strings[3022], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3023], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3024], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[3025], new named_type(IFC4X1_types[330]),
                         true),
           new attribute(strings[3026], new named_type(IFC4X1_types[80]), true),
           new attribute(strings[3027], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3028], new named_type(IFC4X1_types[330]),
                         true),
           new attribute(strings[3029], new named_type(IFC4X1_types[708]),
                         true),
           new attribute(strings[3030], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3031], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3032], new named_type(IFC4X1_types[330]),
                         true),
           new attribute(strings[3033], new named_type(IFC4X1_types[708]),
                         true),
           new attribute(strings[3034], new named_type(IFC4X1_types[708]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[880])
      ->set_attributes(
          {new attribute(strings[2441], new named_type(IFC4X1_types[64]),
                         false),
           new attribute(strings[3035], new named_type(IFC4X1_types[690]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[881])
      ->set_attributes(
          {new attribute(strings[2666], new named_type(IFC4X1_types[736]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[882])
      ->set_attributes(
          {new attribute(strings[2843], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[3036], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[883])
      ->set_attributes(
          {new attribute(strings[2843], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2385], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[885])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[887]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[886])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[887]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[888])
      ->set_attributes(
          {new attribute(strings[3037], new named_type(IFC4X1_types[472]),
                         false),
           new attribute(strings[3038], new named_type(IFC4X1_types[656]),
                         true),
           new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[893])
      ->set_attributes(
          {new attribute(strings[3039], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[927])
      ->set_attributes(
          {new attribute(strings[3040], new named_type(IFC4X1_types[925]),
                         true),
           new attribute(strings[2400], new named_type(IFC4X1_types[928]),
                         false)},
          {true, false, false, false});
  ((entity *)IFC4X1_types[894])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[896]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[895])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[896]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[897])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[3041],
                                      new named_type(IFC4X1_types[266]), true),
                        new attribute(strings[3042],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[898])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X1_types[904])
      ->set_attributes({new attribute(strings[3043],
                                      new named_type(IFC4X1_types[906]), false),
                        new attribute(strings[3044],
                                      new named_type(IFC4X1_types[736]), false),
                        new attribute(strings[3045],
                                      new named_type(IFC4X1_types[736]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[905])
      ->set_attributes({new attribute(strings[3046],
                                      new named_type(IFC4X1_types[530]), false),
                        new attribute(strings[3047],
                                      new named_type(IFC4X1_types[530]), false),
                        new attribute(strings[3048],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[3049],
                                      new named_type(IFC4X1_types[811]), false),
                        new attribute(strings[3050],
                                      new named_type(IFC4X1_types[904]), false),
                        new attribute(strings[3051],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[808])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[900])
      ->set_attributes({new attribute(strings[2688],
                                      new named_type(IFC4X1_types[249]), false),
                        new attribute(strings[3052],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X1_types[736])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X1_types[901])
      ->set_attributes({new attribute(strings[3053],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X1_types[285])),
                                      false),
                        new attribute(strings[3054],
                                      new named_type(IFC4X1_types[80]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[902])
      ->set_attributes({new attribute(strings[3055],
                                      new named_type(IFC4X1_types[177]), false),
                        new attribute(strings[3052],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X1_types[736])),
                                      false),
                        new attribute(strings[3053],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X1_types[67])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[908])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[910]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[909])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[910]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[912])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[914]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[913])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[914]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[915])
      ->set_attributes({new attribute(strings[3056],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[916])),
                                      false),
                        new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[3057],
                                      new named_type(IFC4X1_types[559]), false),
                        new attribute(strings[3058],
                                      new named_type(IFC4X1_types[734]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[916])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[917])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[920])
      ->set_attributes({new attribute(strings[3059],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[919])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[921])->set_attributes({}, {false, false});
  ((entity *)IFC4X1_types[922])
      ->set_attributes({new attribute(strings[2524],
                                      new named_type(IFC4X1_types[923]), true),
                        new attribute(strings[3060],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[3061],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[3062],
                                      new named_type(IFC4X1_types[753]), true),
                        new attribute(strings[3063],
                                      new named_type(IFC4X1_types[1138]), true),
                        new attribute(strings[3064],
                                      new named_type(IFC4X1_types[1138]), true),
                        new attribute(strings[2798],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[3065],
                                      new named_type(IFC4X1_types[975]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X1_types[926])
      ->set_attributes({new attribute(strings[3066],
                                      new named_type(IFC4X1_types[181]), true),
                        new attribute(strings[3067],
                                      new named_type(IFC4X1_types[181]), true),
                        new attribute(strings[3068],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[3069],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[3070],
                                      new named_type(IFC4X1_types[709]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false});
  ((entity *)IFC4X1_types[930])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[934]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[931])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[932])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[933])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[934]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[935])
      ->set_attributes({new attribute(strings[3071],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[3072],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[3073],
                                      new named_type(IFC4X1_types[530]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[936])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[938]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[937])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[938]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[940])->set_attributes({}, {});
  ((entity *)IFC4X1_types[946])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[952]), true),
                        new attribute(strings[3074],
                                      new named_type(IFC4X1_types[530]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[948])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[950]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[949])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[950]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[951])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[952]), false),
                        new attribute(strings[2493],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[953])
      ->set_attributes(
          {new attribute(strings[2493], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[954])
      ->set_attributes(
          {new attribute(strings[2652], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[955])
      ->set_attributes(
          {new attribute(strings[3075], new named_type(IFC4X1_types[366]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[956])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[957])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[959]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[958])
      ->set_attributes({new attribute(strings[2369],
                                      new named_type(IFC4X1_types[959]), false),
                        new attribute(strings[2493],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[964])
      ->set_attributes(
          {new attribute(strings[2385], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[965])
      ->set_attributes(
          {new attribute(strings[2385], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[966])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[968]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[967])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[968]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[969])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[974]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[970])
      ->set_attributes({new attribute(strings[3076],
                                      new named_type(IFC4X1_types[500]), true),
                        new attribute(strings[3077],
                                      new named_type(IFC4X1_types[500]), true),
                        new attribute(strings[3078],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[3079],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2369],
                                      new named_type(IFC4X1_types[972]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X1_types[971])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[972]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[973])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[974]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[976])
      ->set_attributes({new attribute(strings[3080],
                                      new named_type(IFC4X1_types[80]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[977])
      ->set_attributes(
          {new attribute(strings[3081], new named_type(IFC4X1_types[991]),
                         false),
           new attribute(strings[3082], new named_type(IFC4X1_types[473]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[979])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[41]),
                         false),
           new attribute(strings[3083], new named_type(IFC4X1_types[67]), true),
           new attribute(
               strings[3084],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[994])),
               true),
           new attribute(
               strings[3085],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[1010])),
               true),
           new attribute(strings[3086], new named_type(IFC4X1_types[635]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[980])
      ->set_attributes(
          {new attribute(strings[2974], new named_type(IFC4X1_types[85]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[981])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false});
  ((entity *)IFC4X1_types[982])
      ->set_attributes(
          {new attribute(strings[3087], new named_type(IFC4X1_types[741]),
                         true),
           new attribute(strings[2369], new named_type(IFC4X1_types[983]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X1_types[984])
      ->set_attributes(
          {new attribute(strings[2441], new named_type(IFC4X1_types[280]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[985])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[986]),
                         false),
           new attribute(strings[2441], new named_type(IFC4X1_types[280]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[987])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[988])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[983]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[989])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[990])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false});
  ((entity *)IFC4X1_types[991])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false});
  ((entity *)IFC4X1_types[992])
      ->set_attributes({new attribute(strings[3088],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, 3,
                                          new named_type(IFC4X1_types[793])),
                                      true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X1_types[993])
      ->set_attributes(
          {new attribute(
               strings[2726],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[996])),
               false),
           new attribute(
               strings[3089],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 1, 2,
                                        new named_type(IFC4X1_types[530]))),
               true)},
          {false, false, false});
  ((entity *)IFC4X1_types[994])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[557]),
                         false),
           new attribute(strings[3090], new named_type(IFC4X1_types[5]), false),
           new attribute(strings[3091], new named_type(IFC4X1_types[4]), false),
           new attribute(strings[3092], new named_type(IFC4X1_types[793]),
                         true),
           new attribute(strings[2376], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[995])
      ->set_attributes({new attribute(strings[3093],
                                      new named_type(IFC4X1_types[549]), true),
                        new attribute(strings[3094],
                                      new named_type(IFC4X1_types[549]), true),
                        new attribute(strings[3095],
                                      new named_type(IFC4X1_types[549]), true),
                        new attribute(strings[3096],
                                      new named_type(IFC4X1_types[550]), true),
                        new attribute(strings[3097],
                                      new named_type(IFC4X1_types[550]), true),
                        new attribute(strings[3098],
                                      new named_type(IFC4X1_types[550]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[996])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[997])
      ->set_attributes({new attribute(strings[3099],
                                      new named_type(IFC4X1_types[688]), true),
                        new attribute(strings[3100],
                                      new named_type(IFC4X1_types[688]), true),
                        new attribute(strings[3101],
                                      new named_type(IFC4X1_types[688]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[998])
      ->set_attributes({new attribute(strings[3102],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[3103],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[3104],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[3105],
                                      new named_type(IFC4X1_types[690]), true),
                        new attribute(strings[3106],
                                      new named_type(IFC4X1_types[690]), true),
                        new attribute(strings[3107],
                                      new named_type(IFC4X1_types[690]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[999])
      ->set_attributes(
          {new attribute(strings[3108], new named_type(IFC4X1_types[248]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1000])
      ->set_attributes(
          {new attribute(strings[3109], new named_type(IFC4X1_types[455]),
                         true),
           new attribute(strings[3110], new named_type(IFC4X1_types[455]),
                         true),
           new attribute(strings[3111], new named_type(IFC4X1_types[455]),
                         true),
           new attribute(strings[3112], new named_type(IFC4X1_types[1113]),
                         true),
           new attribute(strings[3113], new named_type(IFC4X1_types[1113]),
                         true),
           new attribute(strings[3114], new named_type(IFC4X1_types[1113]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1001])
      ->set_attributes(
          {new attribute(strings[3115], new named_type(IFC4X1_types[1174]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1002])->set_attributes({}, {false});
  ((entity *)IFC4X1_types[1003])
      ->set_attributes(
          {new attribute(strings[3116], new named_type(IFC4X1_types[1101]),
                         true),
           new attribute(strings[3117], new named_type(IFC4X1_types[1101]),
                         true),
           new attribute(strings[3118], new named_type(IFC4X1_types[1101]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[1004])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1005])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false});
  ((entity *)IFC4X1_types[1006])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false});
  ((entity *)IFC4X1_types[1007])
      ->set_attributes(
          {new attribute(strings[2977], new named_type(IFC4X1_types[67]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1008])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1009])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1010])
      ->set_attributes(
          {new attribute(strings[3119], new named_type(IFC4X1_types[42]),
                         false),
           new attribute(strings[3120], new named_type(IFC4X1_types[994]),
                         true),
           new attribute(strings[3121], new named_type(IFC4X1_types[80]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1011])
      ->set_attributes(
          {new attribute(strings[3087], new named_type(IFC4X1_types[741]),
                         true),
           new attribute(strings[2369], new named_type(IFC4X1_types[1012]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X1_types[1013])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1014])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1015]),
                         false),
           new attribute(strings[2509], new named_type(IFC4X1_types[706]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1016])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1017])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1012]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1021])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[1019])
      ->set_attributes({new attribute(strings[3122],
                                      new named_type(IFC4X1_types[871]), true),
                        new attribute(strings[2869],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[1018])),
                                      false),
                        new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[1020])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[1022])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1024]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1023])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1024]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X1_types[1025])
      ->set_attributes(
          {new attribute(strings[3123], new named_type(IFC4X1_types[332]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[1026])->set_attributes({}, {});
  ((entity *)IFC4X1_types[1027])
      ->set_attributes(
          {new attribute(strings[3124], new named_type(IFC4X1_types[249]),
                         false),
           new attribute(
               strings[3125],
               new aggregation_type(aggregation_type::list_type, 1, 2,
                                    new named_type(IFC4X1_types[660])),
               false),
           new attribute(strings[3126], new named_type(IFC4X1_types[717]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[1028])
      ->set_attributes(
          {new attribute(strings[2688], new named_type(IFC4X1_types[249]),
                         false),
           new attribute(strings[2689], new named_type(IFC4X1_types[658]),
                         true),
           new attribute(strings[2690], new named_type(IFC4X1_types[658]),
                         true),
           new attribute(strings[3127], new named_type(IFC4X1_types[1026]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1029])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1030]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1031])
      ->set_attributes(
          {new attribute(strings[2665], new named_type(IFC4X1_types[280]),
                         false),
           new attribute(strings[2494], new named_type(IFC4X1_types[530]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[1032])
      ->set_attributes({new attribute(strings[3128],
                                      new named_type(IFC4X1_types[64]), false)},
                       {false, false, false});
  ((entity *)IFC4X1_types[1034])
      ->set_attributes({new attribute(strings[3129],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X1_types[530])),
                                      true),
                        new attribute(strings[3130],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X1_types[530])),
                                      true),
                        new attribute(strings[3131],
                                      new named_type(IFC4X1_types[793]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X1_types[1036])
      ->set_attributes(
          {new attribute(strings[3132], new named_type(IFC4X1_types[1035]),
                         false),
           new attribute(
               strings[2869],
               new aggregation_type(aggregation_type::set_type, 1, 5,
                                    new named_type(IFC4X1_types[1037])),
               false)},
          {false, false, false});
  ((entity *)IFC4X1_types[1038])
      ->set_attributes(
          {new attribute(strings[3133], new named_type(IFC4X1_types[163]),
                         false),
           new attribute(strings[3134], new named_type(IFC4X1_types[163]),
                         false),
           new attribute(strings[3135], new named_type(IFC4X1_types[163]),
                         false),
           new attribute(strings[3136], new named_type(IFC4X1_types[163]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X1_types[1039])
      ->set_attributes({new attribute(strings[3137],
                                      new named_type(IFC4X1_types[796]), true),
                        new attribute(strings[3138],
                                      new named_type(IFC4X1_types[796]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[1040])
      ->set_attributes(
          {new attribute(strings[3139], new named_type(IFC4X1_types[162]),
                         true),
           new attribute(strings[3135], new named_type(IFC4X1_types[162]),
                         true),
           new attribute(strings[3133], new named_type(IFC4X1_types[162]),
                         true),
           new attribute(strings[3140], new named_type(IFC4X1_types[162]),
                         true),
           new attribute(strings[3141], new named_type(IFC4X1_types[162]),
                         true),
           new attribute(strings[3142], new named_type(IFC4X1_types[962]),
                         true),
           new attribute(strings[3143], new named_type(IFC4X1_types[806]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1041])
      ->set_attributes({new attribute(strings[3144],
                                      new named_type(IFC4X1_types[163]), false),
                        new attribute(strings[3145],
                                      new named_type(IFC4X1_types[628]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[1042])
      ->set_attributes({new attribute(strings[3146],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[1043])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[1043])
      ->set_attributes({new attribute(strings[3147],
                                      new named_type(IFC4X1_types[80]), false),
                        new attribute(strings[3148],
                                      new named_type(IFC4X1_types[80]), false),
                        new attribute(strings[3149],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[3150],
                                      new named_type(IFC4X1_types[135]), true),
                        new attribute(strings[3151],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[490])),
                                      true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[1044])
      ->set_attributes({new attribute(strings[3152],
                                      new named_type(IFC4X1_types[736]), false),
                        new attribute(strings[2531],
                                      new named_type(IFC4X1_types[67]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[1045])
      ->set_attributes({new attribute(strings[2688],
                                      new named_type(IFC4X1_types[249]), false),
                        new attribute(strings[2385],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[3153],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2689],
                                      new named_type(IFC4X1_types[658]), true),
                        new attribute(strings[2690],
                                      new named_type(IFC4X1_types[658]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[1046])
      ->set_attributes({new attribute(strings[2710],
                                      new named_type(IFC4X1_types[706]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1047])
      ->set_attributes({new attribute(strings[3154],
                                      new named_type(IFC4X1_types[736]), false),
                        new attribute(strings[2531],
                                      new named_type(IFC4X1_types[67]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[1048])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1050]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1049])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1050]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1051])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC4X1_types[1052])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1054]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1053])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1054]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1130])
      ->set_attributes({new attribute(strings[2494],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[3155],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2431],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2709],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2710],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2711],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[3156],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[3157],
                                      new named_type(IFC4X1_types[690]), true),
                        new attribute(strings[2712],
                                      new named_type(IFC4X1_types[690]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X1_types[1055])
      ->set_attributes({new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[3158],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[1057])),
                                      true),
                        new attribute(strings[3159],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[1056])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[1056])
      ->set_attributes({new attribute(strings[2409],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[2400],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[2375],
                                      new named_type(IFC4X1_types[1078]), true),
                        new attribute(strings[2590],
                                      new named_type(IFC4X1_types[1138]), true),
                        new attribute(strings[2806],
                                      new named_type(IFC4X1_types[803]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[1057])
      ->set_attributes({new attribute(strings[3160],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[1149])),
                                      true),
                        new attribute(strings[3161],
                                      new named_type(IFC4X1_types[80]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[1058])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1060]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1059])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1060]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1061])
      ->set_attributes(
          {new attribute(strings[2370], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[3162], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[3163], new named_type(IFC4X1_types[80]),
                         false),
           new attribute(strings[2778], new named_type(IFC4X1_types[500]),
                         true),
           new attribute(strings[3164], new named_type(IFC4X1_types[1063]),
                         true),
           new attribute(strings[2369], new named_type(IFC4X1_types[1066]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X1_types[1063])
      ->set_attributes(
          {new attribute(strings[2732], new named_type(IFC4X1_types[1062]),
                         true),
           new attribute(strings[3165], new named_type(IFC4X1_types[330]),
                         true),
           new attribute(strings[3022], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3023], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3166], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3167], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3168], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3169], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3170], new named_type(IFC4X1_types[330]),
                         true),
           new attribute(strings[3171], new named_type(IFC4X1_types[330]),
                         true),
           new attribute(strings[3172], new named_type(IFC4X1_types[80]), true),
           new attribute(strings[3027], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3173], new named_type(IFC4X1_types[330]),
                         true),
           new attribute(strings[3030], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3031], new named_type(IFC4X1_types[268]),
                         true),
           new attribute(strings[3174], new named_type(IFC4X1_types[330]),
                         true),
           new attribute(strings[3034], new named_type(IFC4X1_types[708]),
                         true)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1064])
      ->set_attributes(
          {new attribute(strings[3175], new named_type(IFC4X1_types[801]),
                         false)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1065])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1066]),
                         false),
           new attribute(strings[3162], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1067])
      ->set_attributes(
          {new attribute(
               strings[3176],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[519])),
               true),
           new attribute(
               strings[3177],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[519])),
               true),
           new attribute(strings[3178], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(
               strings[3179],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[519])),
               true),
           new attribute(strings[3180], new named_type(IFC4X1_types[1147]),
                         true),
           new attribute(
               strings[3181],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[1147])),
               true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1070])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1075]),
                         true),
           new attribute(strings[2801], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2933], new named_type(IFC4X1_types[56]), true),
           new attribute(strings[3182], new named_type(IFC4X1_types[455]),
                         true),
           new attribute(strings[3183], new named_type(IFC4X1_types[725]),
                         true),
           new attribute(strings[3184], new named_type(IFC4X1_types[628]),
                         true),
           new attribute(strings[3185], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[3186], new named_type(IFC4X1_types[706]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1071])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1073]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1072])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1073]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1074])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1075]),
                         false),
           new attribute(strings[2801], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2933], new named_type(IFC4X1_types[56]), true),
           new attribute(strings[3187], new named_type(IFC4X1_types[706]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X1_types[1076])
      ->set_attributes(
          {new attribute(strings[2499], new named_type(IFC4X1_types[133]),
                         false)},
          {false});
  ((entity *)IFC4X1_types[1077])->set_attributes({}, {});
  ((entity *)IFC4X1_types[1083])
      ->set_attributes(
          {new attribute(strings[3188], new named_type(IFC4X1_types[718]),
                         false),
           new attribute(strings[2846], new named_type(IFC4X1_types[65]),
                         false),
           new attribute(strings[3189], new named_type(IFC4X1_types[1085]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[1084])
      ->set_attributes({new attribute(strings[3190],
                                      new named_type(IFC4X1_types[687]), false),
                        new attribute(strings[3191],
                                      new named_type(IFC4X1_types[94]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC4X1_types[1086])
      ->set_attributes(
          {new attribute(strings[3192], new named_type(IFC4X1_types[1088]),
                         true),
           new attribute(strings[3193], new named_type(IFC4X1_types[1089]),
                         true),
           new attribute(strings[3194], new named_type(IFC4X1_types[1082]),
                         false),
           new attribute(strings[2581], new named_type(IFC4X1_types[80]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[1087])
      ->set_attributes(
          {new attribute(
               strings[3195],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[1081])),
               false),
           new attribute(strings[3196], new named_type(IFC4X1_types[449]),
                         true),
           new attribute(strings[3197], new named_type(IFC4X1_types[450]),
                         true),
           new attribute(strings[3198], new named_type(IFC4X1_types[451]),
                         true),
           new attribute(strings[3199], new named_type(IFC4X1_types[929]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1088])
      ->set_attributes({new attribute(strings[3200],
                                      new named_type(IFC4X1_types[161]), false),
                        new attribute(strings[3201],
                                      new named_type(IFC4X1_types[161]), true)},
                       {false, false});
  ((entity *)IFC4X1_types[1089])
      ->set_attributes({new attribute(strings[3202],
                                      new named_type(IFC4X1_types[929]), true),
                        new attribute(strings[3203],
                                      new named_type(IFC4X1_types[1079]), true),
                        new attribute(strings[3204],
                                      new named_type(IFC4X1_types[1080]), true),
                        new attribute(strings[3205],
                                      new named_type(IFC4X1_types[929]), true),
                        new attribute(strings[3206],
                                      new named_type(IFC4X1_types[929]), true),
                        new attribute(strings[3207],
                                      new named_type(IFC4X1_types[1090]), true),
                        new attribute(strings[3208],
                                      new named_type(IFC4X1_types[929]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1091])
      ->set_attributes({new attribute(strings[3209],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[1043])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[1092])
      ->set_attributes({new attribute(strings[3149],
                                      new named_type(IFC4X1_types[519]), false),
                        new attribute(strings[3151],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[796])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X1_types[1093])
      ->set_attributes(
          {new attribute(
               strings[3210],
               new aggregation_type(aggregation_type::list_type, 3, -1,
                                    new named_type(IFC4X1_types[1094])),
               false),
           new attribute(strings[2714], new named_type(IFC4X1_types[400]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[1094])
      ->set_attributes({new attribute(strings[2499],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 2,
                                          new named_type(IFC4X1_types[658])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[1095])
      ->set_attributes(
          {new attribute(
              strings[3211],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 2, 2,
                                       new named_type(IFC4X1_types[658]))),
              false)},
          {false});
  ((entity *)IFC4X1_types[1105])
      ->set_attributes(
          {new attribute(strings[3212], new named_type(IFC4X1_types[1102]),
                         false),
           new attribute(strings[3213], new named_type(IFC4X1_types[1102]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[1106])
      ->set_attributes(
          {new attribute(strings[2400], new named_type(IFC4X1_types[519]),
                         false),
           new attribute(strings[2375], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[3212], new named_type(IFC4X1_types[268]),
                         false),
           new attribute(strings[3213], new named_type(IFC4X1_types[268]),
                         false),
           new attribute(strings[3214], new named_type(IFC4X1_types[1107]),
                         false),
           new attribute(strings[3041], new named_type(IFC4X1_types[266]),
                         false),
           new attribute(strings[3042], new named_type(IFC4X1_types[519]),
                         true),
           new attribute(strings[2590], new named_type(IFC4X1_types[1138]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1108])
      ->set_attributes({new attribute(strings[2728],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[1149])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[1110])->set_attributes({}, {});
  ((entity *)IFC4X1_types[1111])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X1_types[1112])
      ->set_attributes(
          {new attribute(strings[3215], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[3216], new named_type(IFC4X1_types[706]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X1_types[1114])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1116]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1115])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1116]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1118])
      ->set_attributes(
          {new attribute(strings[3217], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[3218], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[3219], new named_type(IFC4X1_types[80]),
                         false),
           new attribute(strings[3220], new named_type(IFC4X1_types[80]),
                         false),
           new attribute(strings[3221], new named_type(IFC4X1_types[1119]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1121])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1123]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1122])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1123]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1124])
      ->set_attributes(
          {new attribute(strings[3222], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[3223], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2486], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[3224], new named_type(IFC4X1_types[530]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1125])
      ->set_attributes(
          {new attribute(
               strings[3225],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4X1_types[658]))),
               true),
           new attribute(strings[2854], new named_type(IFC4X1_types[80]), true),
           new attribute(
               strings[2719],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4X1_types[705]))),
               false),
           new attribute(
               strings[2856],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[705])),
               true)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[1126])
      ->set_attributes({new attribute(strings[3226],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X1_types[500])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1127])
      ->set_attributes(
          {new attribute(strings[2813], new named_type(IFC4X1_types[249]),
                         false),
           new attribute(
               strings[3227],
               new aggregation_type(aggregation_type::set_type, 1, 2,
                                    new named_type(IFC4X1_types[1129])),
               false),
           new attribute(
               strings[3228],
               new aggregation_type(aggregation_type::set_type, 1, 2,
                                    new named_type(IFC4X1_types[1129])),
               false),
           new attribute(strings[3229], new named_type(IFC4X1_types[80]),
                         false),
           new attribute(strings[3126], new named_type(IFC4X1_types[1128]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X1_types[1131])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1133]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1132])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1133]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1134])
      ->set_attributes({new attribute(strings[3230],
                                      new named_type(IFC4X1_types[490]), true),
                        new attribute(strings[3231],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[757])),
                                      true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1135])
      ->set_attributes(
          {new attribute(strings[2420], new named_type(IFC4X1_types[490]),
                         true),
           new attribute(strings[2371], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[3232], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1136])
      ->set_attributes(
          {new attribute(
               strings[3233],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X1_types[872])),
               true),
           new attribute(strings[2393], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1137])
      ->set_attributes(
          {new attribute(strings[2420], new named_type(IFC4X1_types[490]),
                         true),
           new attribute(strings[2371], new named_type(IFC4X1_types[1078]),
                         true),
           new attribute(strings[3234], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1148])
      ->set_attributes({new attribute(strings[2494],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[3155],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2431],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2709],
                                      new named_type(IFC4X1_types[706]), false),
                        new attribute(strings[2710],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2729],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2712],
                                      new named_type(IFC4X1_types[690]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X1_types[1145])
      ->set_attributes({new attribute(strings[3235],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[1138])),
                                      false)},
                       {false});
  ((entity *)IFC4X1_types[1139])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1141]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1140])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1141]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1142])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1144]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1143])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1144]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1150])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1152]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1151])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1152]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1154])
      ->set_attributes(
          {new attribute(strings[2670], new named_type(IFC4X1_types[280]),
                         false),
           new attribute(strings[3236], new named_type(IFC4X1_types[530]),
                         false)},
          {false, false});
  ((entity *)IFC4X1_types[1156])->set_attributes({}, {});
  ((entity *)IFC4X1_types[1157])
      ->set_attributes(
          {new attribute(strings[3237], new named_type(IFC4X1_types[1156]),
                         false)},
          {false});
  ((entity *)IFC4X1_types[1158])
      ->set_attributes(
          {new attribute(strings[3238], new named_type(IFC4X1_types[695]),
                         false)},
          {false});
  ((entity *)IFC4X1_types[1159])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1161]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1160])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1161]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1162])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1163])
      ->set_attributes({new attribute(strings[3239],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 2,
                                          new named_type(IFC4X1_types[475])),
                                      false),
                        new attribute(strings[3240],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X1_types[530])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X1_types[1164])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1165]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1168])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1172]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1169])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1170])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1171])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1172]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1176])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1178]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1177])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1178]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X1_types[1179])
      ->set_attributes({new attribute(strings[2621],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2622],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2369],
                                      new named_type(IFC4X1_types[1189]), true),
                        new attribute(strings[3241],
                                      new named_type(IFC4X1_types[1190]), true),
                        new attribute(strings[3242],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X1_types[1180])
      ->set_attributes({new attribute(strings[2625],
                                      new named_type(IFC4X1_types[706]), true),
                        new attribute(strings[2626],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[2629],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[3243],
                                      new named_type(IFC4X1_types[627]), true),
                        new attribute(strings[3244],
                                      new named_type(IFC4X1_types[628]), true),
                        new attribute(strings[3245],
                                      new named_type(IFC4X1_types[628]), true),
                        new attribute(strings[3246],
                                      new named_type(IFC4X1_types[628]), true),
                        new attribute(strings[3247],
                                      new named_type(IFC4X1_types[628]), true),
                        new attribute(strings[2635],
                                      new named_type(IFC4X1_types[915]), true),
                        new attribute(strings[2631],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2636],
                                      new named_type(IFC4X1_types[530]), true),
                        new attribute(strings[2637],
                                      new named_type(IFC4X1_types[530]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false,
                        false});
  ((entity *)IFC4X1_types[1183])
      ->set_attributes(
          {new attribute(strings[2623], new named_type(IFC4X1_types[1181]),
                         false),
           new attribute(strings[2641], new named_type(IFC4X1_types[1182]),
                         false),
           new attribute(strings[2831], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2832], new named_type(IFC4X1_types[706]),
                         true),
           new attribute(strings[2635], new named_type(IFC4X1_types[915]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1184])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1185])
      ->set_attributes(
          {new attribute(strings[2642], new named_type(IFC4X1_types[1186]),
                         false),
           new attribute(strings[2623], new named_type(IFC4X1_types[1187]),
                         false),
           new attribute(strings[2643], new named_type(IFC4X1_types[80]),
                         false),
           new attribute(strings[2644], new named_type(IFC4X1_types[80]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X1_types[1188])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1189]),
                         false),
           new attribute(strings[3241], new named_type(IFC4X1_types[1190]),
                         false),
           new attribute(strings[2643], new named_type(IFC4X1_types[80]), true),
           new attribute(strings[3242], new named_type(IFC4X1_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X1_types[1191])
      ->set_attributes(
          {new attribute(
               strings[3248],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[1198])),
               true),
           new attribute(
               strings[3249],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X1_types[1198])),
               true),
           new attribute(strings[2369], new named_type(IFC4X1_types[1192]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1193])
      ->set_attributes({new attribute(strings[2828],
                                      new named_type(IFC4X1_types[268]), false),
                        new attribute(strings[3250],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X1_types[667])),
                                      true),
                        new attribute(strings[2376],
                                      new named_type(IFC4X1_types[519]), true),
                        new attribute(strings[3251],
                                      new named_type(IFC4X1_types[330]), true),
                        new attribute(strings[3171],
                                      new named_type(IFC4X1_types[330]), true),
                        new attribute(strings[3212],
                                      new named_type(IFC4X1_types[268]), false),
                        new attribute(strings[3252],
                                      new named_type(IFC4X1_types[268]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X1_types[1194])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1195]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X1_types[1196])
      ->set_attributes(
          {new attribute(strings[2369], new named_type(IFC4X1_types[1197]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X1_types[1198])
      ->set_attributes({new attribute(strings[3253],
                                      new named_type(IFC4X1_types[801]), true),
                        new attribute(strings[3254],
                                      new named_type(IFC4X1_types[267]), true),
                        new attribute(strings[3255],
                                      new named_type(IFC4X1_types[267]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1200])
      ->set_attributes(
          {new attribute(strings[2494], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[3155], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2431], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2709], new named_type(IFC4X1_types[706]),
                         false),
           new attribute(strings[2710], new named_type(IFC4X1_types[627]),
                         true),
           new attribute(strings[2729], new named_type(IFC4X1_types[627]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X1_types[1199])
      ->set_attributes({new attribute(strings[2493],
                                      new named_type(IFC4X1_types[519]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X1_types[6])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3256], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[822]),
          ((entity *)IFC4X1_types[822])->attributes()[0])});
  ((entity *)IFC4X1_types[7])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3257], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[394]),
          ((entity *)IFC4X1_types[394])->attributes()[1])});
  ((entity *)IFC4X1_types[12])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3258], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[667]),
               ((entity *)IFC4X1_types[667])->attributes()[7]),
           new inverse_attribute(
               strings[3259], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[648]),
               ((entity *)IFC4X1_types[648])->attributes()[4])});
  ((entity *)IFC4X1_types[30])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3260], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X1_types[38]),
          ((entity *)IFC4X1_types[38])->attributes()[0])});
  ((entity *)IFC4X1_types[31])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3261], inverse_attribute::set_type, 1, 1,
          ((entity *)IFC4X1_types[30]),
          ((entity *)IFC4X1_types[30])->attributes()[1])});
  ((entity *)IFC4X1_types[36])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3260], inverse_attribute::set_type, 1, 1,
          ((entity *)IFC4X1_types[38]),
          ((entity *)IFC4X1_types[38])->attributes()[1])});
  ((entity *)IFC4X1_types[37])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3262], inverse_attribute::set_type, 1, 1,
          ((entity *)IFC4X1_types[36]),
          ((entity *)IFC4X1_types[36])->attributes()[0])});
  ((entity *)IFC4X1_types[44])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3263], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[846]),
          ((entity *)IFC4X1_types[846])->attributes()[0])});
  ((entity *)IFC4X1_types[47])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3257], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[394]),
          ((entity *)IFC4X1_types[394])->attributes()[1])});
  ((entity *)IFC4X1_types[49])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3264], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[394]),
               ((entity *)IFC4X1_types[394])->attributes()[1]),
           new inverse_attribute(
               strings[3265], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[830]),
               ((entity *)IFC4X1_types[830])->attributes()[0]),
           new inverse_attribute(
               strings[3266], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[874]),
               ((entity *)IFC4X1_types[874])->attributes()[1]),
           new inverse_attribute(strings[3267], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4X1_types[50]),
                                 ((entity *)IFC4X1_types[50])->attributes()[1]),
           new inverse_attribute(
               strings[3268], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[50]),
               ((entity *)IFC4X1_types[50])->attributes()[0])});
  ((entity *)IFC4X1_types[153])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3269], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[831]),
               ((entity *)IFC4X1_types[831])->attributes()[0]),
           new inverse_attribute(
               strings[3270], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[154]),
               ((entity *)IFC4X1_types[154])->attributes()[0])});
  ((entity *)IFC4X1_types[154])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3271], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[831]),
               ((entity *)IFC4X1_types[831])->attributes()[0]),
           new inverse_attribute(
               strings[3270], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[154]),
               ((entity *)IFC4X1_types[154])->attributes()[0])});
  ((entity *)IFC4X1_types[179])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3272], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X1_types[177]),
          ((entity *)IFC4X1_types[177])->attributes()[0])});
  ((entity *)IFC4X1_types[197])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3264], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[394]),
               ((entity *)IFC4X1_types[394])->attributes()[1]),
           new inverse_attribute(
               strings[3273], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[875]),
               ((entity *)IFC4X1_types[875])->attributes()[0])});
  ((entity *)IFC4X1_types[210])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3274], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[853]),
               ((entity *)IFC4X1_types[853])->attributes()[0]),
           new inverse_attribute(
               strings[3275], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[849]),
               ((entity *)IFC4X1_types[849])->attributes()[0])});
  ((entity *)IFC4X1_types[212])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3257], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[394]),
          ((entity *)IFC4X1_types[394])->attributes()[1])});
  ((entity *)IFC4X1_types[213])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3276], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[823]),
          ((entity *)IFC4X1_types[823])->attributes()[0])});
  ((entity *)IFC4X1_types[217])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3257], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[394]),
          ((entity *)IFC4X1_types[394])->attributes()[1])});
  ((entity *)IFC4X1_types[226])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3277], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[225]),
          ((entity *)IFC4X1_types[225])->attributes()[0])});
  ((entity *)IFC4X1_types[234])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3278], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[848]),
               ((entity *)IFC4X1_types[848])->attributes()[1]),
           new inverse_attribute(
               strings[3279], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[847]),
               ((entity *)IFC4X1_types[847])->attributes()[1])});
  ((entity *)IFC4X1_types[290])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3280], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[857]),
          ((entity *)IFC4X1_types[857])->attributes()[0])});
  ((entity *)IFC4X1_types[292])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3281], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[841]),
          ((entity *)IFC4X1_types[841])->attributes()[1])});
  ((entity *)IFC4X1_types[294])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3282], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[857]),
          ((entity *)IFC4X1_types[857])->attributes()[1])});
  ((entity *)IFC4X1_types[301])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3283], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[833]),
               ((entity *)IFC4X1_types[833])->attributes()[0]),
           new inverse_attribute(
               strings[3284], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[303]),
               ((entity *)IFC4X1_types[303])->attributes()[1]),
           new inverse_attribute(
               strings[3285], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[302]),
               ((entity *)IFC4X1_types[302])->attributes()[1]),
           new inverse_attribute(
               strings[3286], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[302]),
               ((entity *)IFC4X1_types[302])->attributes()[0])});
  ((entity *)IFC4X1_types[303])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3287], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[833]),
          ((entity *)IFC4X1_types[833])->attributes()[0])});
  ((entity *)IFC4X1_types[359])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3288], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[856]),
               ((entity *)IFC4X1_types[856])->attributes()[1]),
           new inverse_attribute(
               strings[3289], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[838]),
               ((entity *)IFC4X1_types[838])->attributes()[1]),
           new inverse_attribute(
               strings[3290], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[858]),
               ((entity *)IFC4X1_types[858])->attributes()[1]),
           new inverse_attribute(
               strings[3291], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[858]),
               ((entity *)IFC4X1_types[858])->attributes()[0]),
           new inverse_attribute(
               strings[3292], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[860]),
               ((entity *)IFC4X1_types[860])->attributes()[0]),
           new inverse_attribute(
               strings[3293], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[861]),
               ((entity *)IFC4X1_types[861])->attributes()[0]),
           new inverse_attribute(
               strings[3294], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[867]),
               ((entity *)IFC4X1_types[867])->attributes()[0]),
           new inverse_attribute(
               strings[3295], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[845]),
               ((entity *)IFC4X1_types[845])->attributes()[0]),
           new inverse_attribute(
               strings[3296], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[864]),
               ((entity *)IFC4X1_types[864])->attributes()[1]),
           new inverse_attribute(
               strings[3297], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[838]),
               ((entity *)IFC4X1_types[838])->attributes()[2]),
           new inverse_attribute(
               strings[3263], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[846]),
               ((entity *)IFC4X1_types[846])->attributes()[0]),
           new inverse_attribute(
               strings[3298], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[847]),
               ((entity *)IFC4X1_types[847])->attributes()[0])});
  ((entity *)IFC4X1_types[393])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3299], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[394]),
          ((entity *)IFC4X1_types[394])->attributes()[0])});
  ((entity *)IFC4X1_types[395])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3300], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[864]),
          ((entity *)IFC4X1_types[864])->attributes()[0])});
  ((entity *)IFC4X1_types[400])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3301], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[1093]),
          ((entity *)IFC4X1_types[1093])->attributes()[1])});
  ((entity *)IFC4X1_types[415])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3302], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X1_types[860]),
          ((entity *)IFC4X1_types[860])->attributes()[1])});
  ((entity *)IFC4X1_types[416])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3303], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X1_types[867]),
          ((entity *)IFC4X1_types[867])->attributes()[1])});
  ((entity *)IFC4X1_types[467])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3304], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[469]),
               ((entity *)IFC4X1_types[469])->attributes()[0]),
           new inverse_attribute(
               strings[3277], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[225]),
               ((entity *)IFC4X1_types[225])->attributes()[0])});
  ((entity *)IFC4X1_types[475])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3305], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[474]),
               ((entity *)IFC4X1_types[474])->attributes()[2]),
           new inverse_attribute(
               strings[3306], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[474]),
               ((entity *)IFC4X1_types[474])->attributes()[1]),
           new inverse_attribute(
               strings[3307], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[474]),
               ((entity *)IFC4X1_types[474])->attributes()[0]),
           new inverse_attribute(
               strings[3308], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[1163]),
               ((entity *)IFC4X1_types[1163])->attributes()[0])});
  ((entity *)IFC4X1_types[479])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3309], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[824]),
          ((entity *)IFC4X1_types[824])->attributes()[0])});
  ((entity *)IFC4X1_types[495])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3310], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X1_types[700]),
          ((entity *)IFC4X1_types[700])->attributes()[1])});
  ((entity *)IFC4X1_types[531])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3311], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[834]),
               ((entity *)IFC4X1_types[834])->attributes()[0]),
           new inverse_attribute(
               strings[3312], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[532]),
               ((entity *)IFC4X1_types[532])->attributes()[2])});
  ((entity *)IFC4X1_types[532])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3313], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[834]),
          ((entity *)IFC4X1_types[834])->attributes()[0])});
  ((entity *)IFC4X1_types[575])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3314], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[580]),
               ((entity *)IFC4X1_types[580])->attributes()[0]),
           new inverse_attribute(
               strings[3267], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[592]),
               ((entity *)IFC4X1_types[592])->attributes()[1]),
           new inverse_attribute(
               strings[3315], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[592]),
               ((entity *)IFC4X1_types[592])->attributes()[0])});
  ((entity *)IFC4X1_types[577])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3316], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X1_types[578]),
          ((entity *)IFC4X1_types[578])->attributes()[2])});
  ((entity *)IFC4X1_types[579])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3317], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[835]),
               ((entity *)IFC4X1_types[835])->attributes()[0]),
           new inverse_attribute(
               strings[3264], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[394]),
               ((entity *)IFC4X1_types[394])->attributes()[1]),
           new inverse_attribute(
               strings[2523], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[591]),
               ((entity *)IFC4X1_types[591])->attributes()[0])});
  ((entity *)IFC4X1_types[581])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3318], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X1_types[582]),
          ((entity *)IFC4X1_types[582])->attributes()[0])});
  ((entity *)IFC4X1_types[586])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3319], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X1_types[587]),
          ((entity *)IFC4X1_types[587])->attributes()[2])});
  ((entity *)IFC4X1_types[594])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3317], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X1_types[835]),
          ((entity *)IFC4X1_types[835])->attributes()[0])});
  ((entity *)IFC4X1_types[631])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3320], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[852]),
               ((entity *)IFC4X1_types[852])->attributes()[0]),
           new inverse_attribute(
               strings[3275], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[852]),
               ((entity *)IFC4X1_types[852])->attributes()[1]),
           new inverse_attribute(
               strings[3321], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[855]),
               ((entity *)IFC4X1_types[855])->attributes()[0]),
           new inverse_attribute(
               strings[3274], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[853]),
               ((entity *)IFC4X1_types[853])->attributes()[0])});
  ((entity *)IFC4X1_types[632])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3322], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[821]),
               ((entity *)IFC4X1_types[821])->attributes()[0]),
           new inverse_attribute(
               strings[3323], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[859]),
               ((entity *)IFC4X1_types[859])->attributes()[1]),
           new inverse_attribute(
               strings[3324], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[859]),
               ((entity *)IFC4X1_types[859])->attributes()[0]),
           new inverse_attribute(
               strings[3325], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[849]),
               ((entity *)IFC4X1_types[849])->attributes()[1]),
           new inverse_attribute(
               strings[3326], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[820]),
               ((entity *)IFC4X1_types[820])->attributes()[0]),
           new inverse_attribute(
               strings[3327], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[820]),
               ((entity *)IFC4X1_types[820])->attributes()[1]),
           new inverse_attribute(
               strings[3328], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[829]),
               ((entity *)IFC4X1_types[829])->attributes()[0])});
  ((entity *)IFC4X1_types[635])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3329], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[731]),
               ((entity *)IFC4X1_types[731])->attributes()[0]),
           new inverse_attribute(
               strings[3330], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[558]),
               ((entity *)IFC4X1_types[558])->attributes()[0])});
  ((entity *)IFC4X1_types[644])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3331], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[856]),
          ((entity *)IFC4X1_types[856])->attributes()[0])});
  ((entity *)IFC4X1_types[648])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3332], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[649]),
               ((entity *)IFC4X1_types[649])->attributes()[1]),
           new inverse_attribute(
               strings[3268], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[649]),
               ((entity *)IFC4X1_types[649])->attributes()[0]),
           new inverse_attribute(
               strings[3333], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[668]),
               ((entity *)IFC4X1_types[668])->attributes()[1])});
  ((entity *)IFC4X1_types[667])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3334], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[668]),
          ((entity *)IFC4X1_types[668])->attributes()[0])});
  ((entity *)IFC4X1_types[672])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3264], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[394]),
               ((entity *)IFC4X1_types[394])->attributes()[1]),
           new inverse_attribute(
               strings[3335], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[670]),
               ((entity *)IFC4X1_types[670])->attributes()[0])});
  ((entity *)IFC4X1_types[703])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3336], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[841]),
               ((entity *)IFC4X1_types[841])->attributes()[0]),
           new inverse_attribute(
               strings[3297], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[840]),
               ((entity *)IFC4X1_types[840])->attributes()[1]),
           new inverse_attribute(
               strings[3289], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[840]),
               ((entity *)IFC4X1_types[840])->attributes()[0])});
  ((entity *)IFC4X1_types[704])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3263], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[846]),
          ((entity *)IFC4X1_types[846])->attributes()[0])});
  ((entity *)IFC4X1_types[729])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3337], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[862]),
               ((entity *)IFC4X1_types[862])->attributes()[0]),
           new inverse_attribute(
               strings[3338], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[862]),
               ((entity *)IFC4X1_types[862])->attributes()[1]),
           new inverse_attribute(
               strings[3339], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[826]),
               ((entity *)IFC4X1_types[826])->attributes()[0])});
  ((entity *)IFC4X1_types[731])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3340], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[827]),
          ((entity *)IFC4X1_types[827])->attributes()[0])});
  ((entity *)IFC4X1_types[732])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3341], inverse_attribute::set_type, 1, -1,
               ((entity *)IFC4X1_types[731]),
               ((entity *)IFC4X1_types[731])->attributes()[1]),
           new inverse_attribute(
               strings[3342], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[915]),
               ((entity *)IFC4X1_types[915])->attributes()[4])});
  ((entity *)IFC4X1_types[736])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3257], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[394]),
               ((entity *)IFC4X1_types[394])->attributes()[1]),
           new inverse_attribute(
               strings[2523], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[737]),
               ((entity *)IFC4X1_types[737])->attributes()[0])});
  ((entity *)IFC4X1_types[747])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3343], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[756]),
               ((entity *)IFC4X1_types[756])->attributes()[0]),
           new inverse_attribute(
               strings[3344], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[751]),
               ((entity *)IFC4X1_types[751])->attributes()[0]),
           new inverse_attribute(
               strings[3345], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[751]),
               ((entity *)IFC4X1_types[751])->attributes()[1]),
           new inverse_attribute(
               strings[3335], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[174]),
               ((entity *)IFC4X1_types[174])->attributes()[1]),
           new inverse_attribute(
               strings[3346], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[875]),
               ((entity *)IFC4X1_types[875])->attributes()[1]),
           new inverse_attribute(
               strings[3347], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[874]),
               ((entity *)IFC4X1_types[874])->attributes()[0])});
  ((entity *)IFC4X1_types[748])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3264], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[394]),
          ((entity *)IFC4X1_types[394])->attributes()[1])});
  ((entity *)IFC4X1_types[750])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3325], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[849]),
               ((entity *)IFC4X1_types[849])->attributes()[1]),
           new inverse_attribute(
               strings[3328], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[829]),
               ((entity *)IFC4X1_types[829])->attributes()[0])});
  ((entity *)IFC4X1_types[757])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3348], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[1134]),
               ((entity *)IFC4X1_types[1134])->attributes()[1]),
           new inverse_attribute(
               strings[3274], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[854]),
               ((entity *)IFC4X1_types[854])->attributes()[0]),
           new inverse_attribute(
               strings[3349], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[853]),
               ((entity *)IFC4X1_types[853])->attributes()[1])});
  ((entity *)IFC4X1_types[760])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3350], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[854]),
          ((entity *)IFC4X1_types[854])->attributes()[1])});
  ((entity *)IFC4X1_types[764])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3351], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[175]),
               ((entity *)IFC4X1_types[175])->attributes()[2]),
           new inverse_attribute(
               strings[3352], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[760]),
               ((entity *)IFC4X1_types[760])->attributes()[2])});
  ((entity *)IFC4X1_types[865])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2395], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[865]),
          ((entity *)IFC4X1_types[865])->attributes()[0])});
  ((entity *)IFC4X1_types[866])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3353], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[866]),
          ((entity *)IFC4X1_types[866])->attributes()[0])});
  ((entity *)IFC4X1_types[869])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3354], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[872]),
               ((entity *)IFC4X1_types[872])->attributes()[1]),
           new inverse_attribute(
               strings[3355], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[720]),
               ((entity *)IFC4X1_types[720])->attributes()[2]),
           new inverse_attribute(
               strings[3356], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[733]),
               ((entity *)IFC4X1_types[733])->attributes()[2])});
  ((entity *)IFC4X1_types[870])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3357], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[869]),
          ((entity *)IFC4X1_types[869])->attributes()[0])});
  ((entity *)IFC4X1_types[871])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3358], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[720]),
               ((entity *)IFC4X1_types[720])->attributes()[2]),
           new inverse_attribute(
               strings[3359], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[1019]),
               ((entity *)IFC4X1_types[1019])->attributes()[0])});
  ((entity *)IFC4X1_types[872])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3342], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[915]),
               ((entity *)IFC4X1_types[915])->attributes()[4]),
           new inverse_attribute(
               strings[3360], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[570]),
               ((entity *)IFC4X1_types[570])->attributes()[0])});
  ((entity *)IFC4X1_types[873])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3361], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[828]),
          ((entity *)IFC4X1_types[828])->attributes()[0])});
  ((entity *)IFC4X1_types[915])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3264], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[394]),
          ((entity *)IFC4X1_types[394])->attributes()[1])});
  ((entity *)IFC4X1_types[916])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3362], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[915]),
          ((entity *)IFC4X1_types[915])->attributes()[0])});
  ((entity *)IFC4X1_types[946])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3298], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[848]),
               ((entity *)IFC4X1_types[848])->attributes()[0]),
           new inverse_attribute(
               strings[3300], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[864]),
               ((entity *)IFC4X1_types[864])->attributes()[0])});
  ((entity *)IFC4X1_types[953])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3363], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[846]),
               ((entity *)IFC4X1_types[846])->attributes()[1]),
           new inverse_attribute(
               strings[3364], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[863]),
               ((entity *)IFC4X1_types[863])->attributes()[1]),
           new inverse_attribute(
               strings[3365], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[861]),
               ((entity *)IFC4X1_types[861])->attributes()[1])});
  ((entity *)IFC4X1_types[977])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3366], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[842]),
          ((entity *)IFC4X1_types[842])->attributes()[1])});
  ((entity *)IFC4X1_types[980])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3367], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X1_types[843]),
          ((entity *)IFC4X1_types[843])->attributes()[1])});
  ((entity *)IFC4X1_types[989])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3368], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[842]),
          ((entity *)IFC4X1_types[842])->attributes()[0])});
  ((entity *)IFC4X1_types[994])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3369], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[1010]),
               ((entity *)IFC4X1_types[1010])->attributes()[1]),
           new inverse_attribute(
               strings[3370], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[979]),
               ((entity *)IFC4X1_types[979])->attributes()[2])});
  ((entity *)IFC4X1_types[1004])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3371], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[843]),
          ((entity *)IFC4X1_types[843])->attributes()[0])});
  ((entity *)IFC4X1_types[1010])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3372], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[979]),
          ((entity *)IFC4X1_types[979])->attributes()[3])});
  ((entity *)IFC4X1_types[1043])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3373], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[1091]),
               ((entity *)IFC4X1_types[1091])->attributes()[0]),
           new inverse_attribute(
               strings[3374], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[1042]),
               ((entity *)IFC4X1_types[1042])->attributes()[0])});
  ((entity *)IFC4X1_types[1051])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3375], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[863]),
          ((entity *)IFC4X1_types[863])->attributes()[0])});
  ((entity *)IFC4X1_types[1076])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3376], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X1_types[493]),
               ((entity *)IFC4X1_types[493])->attributes()[0]),
           new inverse_attribute(
               strings[3377], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X1_types[497]),
               ((entity *)IFC4X1_types[497])->attributes()[0])});
  ((entity *)IFC4X1_types[1106])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3257], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X1_types[394]),
          ((entity *)IFC4X1_types[394])->attributes()[1])});
  ((entity *)IFC4X1_types[1134])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3378], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X1_types[855]),
          ((entity *)IFC4X1_types[855])->attributes()[1])});
  ((entity *)IFC4X1_types[1135])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3339], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[826]),
          ((entity *)IFC4X1_types[826])->attributes()[0])});
  ((entity *)IFC4X1_types[1136])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3340], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[827]),
          ((entity *)IFC4X1_types[827])->attributes()[0])});
  ((entity *)IFC4X1_types[1137])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3361], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X1_types[828]),
          ((entity *)IFC4X1_types[828])->attributes()[0])});
  ((entity *)IFC4X1_types[213])
      ->set_subtypes(
          {((entity *)IFC4X1_types[2]), ((entity *)IFC4X1_types[228]),
           ((entity *)IFC4X1_types[230]), ((entity *)IFC4X1_types[661]),
           ((entity *)IFC4X1_types[665]), ((entity *)IFC4X1_types[745]),
           ((entity *)IFC4X1_types[1191]), ((entity *)IFC4X1_types[1193])});
  ((entity *)IFC4X1_types[631])
      ->set_subtypes(
          {((entity *)IFC4X1_types[6]), ((entity *)IFC4X1_types[213]),
           ((entity *)IFC4X1_types[479]), ((entity *)IFC4X1_types[729]),
           ((entity *)IFC4X1_types[731]), ((entity *)IFC4X1_types[873])});
  ((entity *)IFC4X1_types[290])
      ->set_subtypes(
          {((entity *)IFC4X1_types[9]), ((entity *)IFC4X1_types[26]),
           ((entity *)IFC4X1_types[214]), ((entity *)IFC4X1_types[433]),
           ((entity *)IFC4X1_types[767]), ((entity *)IFC4X1_types[908]),
           ((entity *)IFC4X1_types[1139])});
  ((entity *)IFC4X1_types[291])
      ->set_subtypes(
          {((entity *)IFC4X1_types[10]), ((entity *)IFC4X1_types[27]),
           ((entity *)IFC4X1_types[215]), ((entity *)IFC4X1_types[434]),
           ((entity *)IFC4X1_types[768]), ((entity *)IFC4X1_types[909]),
           ((entity *)IFC4X1_types[1140])});
  ((entity *)IFC4X1_types[568])
      ->set_subtypes(
          {((entity *)IFC4X1_types[14]), ((entity *)IFC4X1_types[405])});
  ((entity *)IFC4X1_types[14])->set_subtypes({((entity *)IFC4X1_types[15])});
  ((entity *)IFC4X1_types[404])->set_subtypes({((entity *)IFC4X1_types[16])});
  ((entity *)IFC4X1_types[445])
      ->set_subtypes(
          {((entity *)IFC4X1_types[17]), ((entity *)IFC4X1_types[61]),
           ((entity *)IFC4X1_types[170]), ((entity *)IFC4X1_types[335]),
           ((entity *)IFC4X1_types[424]), ((entity *)IFC4X1_types[524]),
           ((entity *)IFC4X1_types[538]), ((entity *)IFC4X1_types[600]),
           ((entity *)IFC4X1_types[653]), ((entity *)IFC4X1_types[894]),
           ((entity *)IFC4X1_types[948]), ((entity *)IFC4X1_types[966]),
           ((entity *)IFC4X1_types[1176])});
  ((entity *)IFC4X1_types[428])
      ->set_subtypes(
          {((entity *)IFC4X1_types[18]), ((entity *)IFC4X1_types[263]),
           ((entity *)IFC4X1_types[342]), ((entity *)IFC4X1_types[355]),
           ((entity *)IFC4X1_types[436]), ((entity *)IFC4X1_types[766]),
           ((entity *)IFC4X1_types[1048]), ((entity *)IFC4X1_types[1150])});
  ((entity *)IFC4X1_types[429])
      ->set_subtypes(
          {((entity *)IFC4X1_types[19]), ((entity *)IFC4X1_types[264]),
           ((entity *)IFC4X1_types[343]), ((entity *)IFC4X1_types[356]),
           ((entity *)IFC4X1_types[437]), ((entity *)IFC4X1_types[770]),
           ((entity *)IFC4X1_types[1049]), ((entity *)IFC4X1_types[1151])});
  ((entity *)IFC4X1_types[446])
      ->set_subtypes(
          {((entity *)IFC4X1_types[21]), ((entity *)IFC4X1_types[62]),
           ((entity *)IFC4X1_types[171]), ((entity *)IFC4X1_types[336]),
           ((entity *)IFC4X1_types[425]), ((entity *)IFC4X1_types[525]),
           ((entity *)IFC4X1_types[539]), ((entity *)IFC4X1_types[601]),
           ((entity *)IFC4X1_types[654]), ((entity *)IFC4X1_types[895]),
           ((entity *)IFC4X1_types[949]), ((entity *)IFC4X1_types[967]),
           ((entity *)IFC4X1_types[1177])});
  ((entity *)IFC4X1_types[371])
      ->set_subtypes(
          {((entity *)IFC4X1_types[23]),   ((entity *)IFC4X1_types[77]),
           ((entity *)IFC4X1_types[114]),  ((entity *)IFC4X1_types[141]),
           ((entity *)IFC4X1_types[158]),  ((entity *)IFC4X1_types[185]),
           ((entity *)IFC4X1_types[219]),  ((entity *)IFC4X1_types[222]),
           ((entity *)IFC4X1_types[348]),  ((entity *)IFC4X1_types[351]),
           ((entity *)IFC4X1_types[374]),  ((entity *)IFC4X1_types[377]),
           ((entity *)IFC4X1_types[380]),  ((entity *)IFC4X1_types[482]),
           ((entity *)IFC4X1_types[487]),  ((entity *)IFC4X1_types[623]),
           ((entity *)IFC4X1_types[936]),  ((entity *)IFC4X1_types[1114]),
           ((entity *)IFC4X1_types[1131]), ((entity *)IFC4X1_types[1142])});
  ((entity *)IFC4X1_types[372])
      ->set_subtypes(
          {((entity *)IFC4X1_types[24]),   ((entity *)IFC4X1_types[78]),
           ((entity *)IFC4X1_types[115]),  ((entity *)IFC4X1_types[142]),
           ((entity *)IFC4X1_types[159]),  ((entity *)IFC4X1_types[186]),
           ((entity *)IFC4X1_types[220]),  ((entity *)IFC4X1_types[223]),
           ((entity *)IFC4X1_types[349]),  ((entity *)IFC4X1_types[352]),
           ((entity *)IFC4X1_types[375]),  ((entity *)IFC4X1_types[378]),
           ((entity *)IFC4X1_types[381]),  ((entity *)IFC4X1_types[483]),
           ((entity *)IFC4X1_types[488]),  ((entity *)IFC4X1_types[624]),
           ((entity *)IFC4X1_types[937]),  ((entity *)IFC4X1_types[1115]),
           ((entity *)IFC4X1_types[1132]), ((entity *)IFC4X1_types[1143])});
  ((entity *)IFC4X1_types[552])->set_subtypes({((entity *)IFC4X1_types[29])});
  ((entity *)IFC4X1_types[468])
      ->set_subtypes(
          {((entity *)IFC4X1_types[30]),   ((entity *)IFC4X1_types[32]),
           ((entity *)IFC4X1_types[36]),   ((entity *)IFC4X1_types[45]),
           ((entity *)IFC4X1_types[84]),   ((entity *)IFC4X1_types[93]),
           ((entity *)IFC4X1_types[131]),  ((entity *)IFC4X1_types[134]),
           ((entity *)IFC4X1_types[179]),  ((entity *)IFC4X1_types[240]),
           ((entity *)IFC4X1_types[249]),  ((entity *)IFC4X1_types[280]),
           ((entity *)IFC4X1_types[285]),  ((entity *)IFC4X1_types[401]),
           ((entity *)IFC4X1_types[418]),  ((entity *)IFC4X1_types[419]),
           ((entity *)IFC4X1_types[470]),  ((entity *)IFC4X1_types[480]),
           ((entity *)IFC4X1_types[542]),  ((entity *)IFC4X1_types[650]),
           ((entity *)IFC4X1_types[685]),  ((entity *)IFC4X1_types[687]),
           ((entity *)IFC4X1_types[695]),  ((entity *)IFC4X1_types[902]),
           ((entity *)IFC4X1_types[920]),  ((entity *)IFC4X1_types[940]),
           ((entity *)IFC4X1_types[1026]), ((entity *)IFC4X1_types[1077]),
           ((entity *)IFC4X1_types[1083]), ((entity *)IFC4X1_types[1154])});
  ((entity *)IFC4X1_types[32])
      ->set_subtypes(
          {((entity *)IFC4X1_types[31]), ((entity *)IFC4X1_types[37])});
  ((entity *)IFC4X1_types[37])
      ->set_subtypes({((entity *)IFC4X1_types[33]),
                      ((entity *)IFC4X1_types[34]),
                      ((entity *)IFC4X1_types[35])});
  ((entity *)IFC4X1_types[91])
      ->set_subtypes(
          {((entity *)IFC4X1_types[38]), ((entity *)IFC4X1_types[96]),
           ((entity *)IFC4X1_types[177]), ((entity *)IFC4X1_types[256]),
           ((entity *)IFC4X1_types[494]), ((entity *)IFC4X1_types[701]),
           ((entity *)IFC4X1_types[1127])});
  ((entity *)IFC4X1_types[731])
      ->set_subtypes(
          {((entity *)IFC4X1_types[44]), ((entity *)IFC4X1_types[359]),
           ((entity *)IFC4X1_types[703]), ((entity *)IFC4X1_types[704]),
           ((entity *)IFC4X1_types[772]), ((entity *)IFC4X1_types[953]),
           ((entity *)IFC4X1_types[977]), ((entity *)IFC4X1_types[989])});
  ((entity *)IFC4X1_types[876])
      ->set_subtypes(
          {((entity *)IFC4X1_types[50]), ((entity *)IFC4X1_types[244]),
           ((entity *)IFC4X1_types[302]), ((entity *)IFC4X1_types[394]),
           ((entity *)IFC4X1_types[592]), ((entity *)IFC4X1_types[649]),
           ((entity *)IFC4X1_types[751]), ((entity *)IFC4X1_types[874]),
           ((entity *)IFC4X1_types[875])});
  ((entity *)IFC4X1_types[736])
      ->set_subtypes(
          {((entity *)IFC4X1_types[51]), ((entity *)IFC4X1_types[52]),
           ((entity *)IFC4X1_types[180]), ((entity *)IFC4X1_types[273]),
           ((entity *)IFC4X1_types[657])});
  ((entity *)IFC4X1_types[51])->set_subtypes({((entity *)IFC4X1_types[53])});
  ((entity *)IFC4X1_types[479])
      ->set_subtypes(
          {((entity *)IFC4X1_types[59]), ((entity *)IFC4X1_types[507]),
           ((entity *)IFC4X1_types[994]), ((entity *)IFC4X1_types[1010]),
           ((entity *)IFC4X1_types[1051])});
  ((entity *)IFC4X1_types[657])
      ->set_subtypes(
          {((entity *)IFC4X1_types[60]), ((entity *)IFC4X1_types[243]),
           ((entity *)IFC4X1_types[149]), ((entity *)IFC4X1_types[370]),
           ((entity *)IFC4X1_types[512]), ((entity *)IFC4X1_types[562]),
           ((entity *)IFC4X1_types[798]), ((entity *)IFC4X1_types[1130]),
           ((entity *)IFC4X1_types[1124]), ((entity *)IFC4X1_types[1148]),
           ((entity *)IFC4X1_types[1200])});
  ((entity *)IFC4X1_types[685])
      ->set_subtypes({((entity *)IFC4X1_types[64]),
                      ((entity *)IFC4X1_types[66]),
                      ((entity *)IFC4X1_types[67])});
  ((entity *)IFC4X1_types[96])->set_subtypes({((entity *)IFC4X1_types[98])});
  ((entity *)IFC4X1_types[92])
      ->set_subtypes(
          {((entity *)IFC4X1_types[99]), ((entity *)IFC4X1_types[250]),
           ((entity *)IFC4X1_types[251]), ((entity *)IFC4X1_types[800])});
  ((entity *)IFC4X1_types[99])->set_subtypes({((entity *)IFC4X1_types[101])});
  ((entity *)IFC4X1_types[103])
      ->set_subtypes(
          {((entity *)IFC4X1_types[68]),  ((entity *)IFC4X1_types[107]),
           ((entity *)IFC4X1_types[144]), ((entity *)IFC4X1_types[166]),
           ((entity *)IFC4X1_types[234]), ((entity *)IFC4X1_types[245]),
           ((entity *)IFC4X1_types[306]), ((entity *)IFC4X1_types[452]),
           ((entity *)IFC4X1_types[603]), ((entity *)IFC4X1_types[674]),
           ((entity *)IFC4X1_types[691]), ((entity *)IFC4X1_types[784]),
           ((entity *)IFC4X1_types[787]), ((entity *)IFC4X1_types[788]),
           ((entity *)IFC4X1_types[885]), ((entity *)IFC4X1_types[912]),
           ((entity *)IFC4X1_types[930]), ((entity *)IFC4X1_types[969]),
           ((entity *)IFC4X1_types[970]), ((entity *)IFC4X1_types[1168]),
           ((entity *)IFC4X1_types[1179])});
  ((entity *)IFC4X1_types[68])->set_subtypes({((entity *)IFC4X1_types[69])});
  ((entity *)IFC4X1_types[110])
      ->set_subtypes(
          {((entity *)IFC4X1_types[70]),  ((entity *)IFC4X1_types[108]),
           ((entity *)IFC4X1_types[145]), ((entity *)IFC4X1_types[168]),
           ((entity *)IFC4X1_types[235]), ((entity *)IFC4X1_types[246]),
           ((entity *)IFC4X1_types[315]), ((entity *)IFC4X1_types[453]),
           ((entity *)IFC4X1_types[605]), ((entity *)IFC4X1_types[676]),
           ((entity *)IFC4X1_types[693]), ((entity *)IFC4X1_types[785]),
           ((entity *)IFC4X1_types[789]), ((entity *)IFC4X1_types[791]),
           ((entity *)IFC4X1_types[886]), ((entity *)IFC4X1_types[913]),
           ((entity *)IFC4X1_types[933]), ((entity *)IFC4X1_types[971]),
           ((entity *)IFC4X1_types[973]), ((entity *)IFC4X1_types[1171]),
           ((entity *)IFC4X1_types[1188])});
  ((entity *)IFC4X1_types[1043])
      ->set_subtypes({((entity *)IFC4X1_types[75]),
                      ((entity *)IFC4X1_types[492]),
                      ((entity *)IFC4X1_types[684])});
  ((entity *)IFC4X1_types[240])
      ->set_subtypes(
          {((entity *)IFC4X1_types[76]), ((entity *)IFC4X1_types[799]),
           ((entity *)IFC4X1_types[882]), ((entity *)IFC4X1_types[883]),
           ((entity *)IFC4X1_types[964])});
  ((entity *)IFC4X1_types[84])->set_subtypes({((entity *)IFC4X1_types[81])});
  ((entity *)IFC4X1_types[178])->set_subtypes({((entity *)IFC4X1_types[86])});
  ((entity *)IFC4X1_types[85])
      ->set_subtypes({((entity *)IFC4X1_types[87]),
                      ((entity *)IFC4X1_types[88]),
                      ((entity *)IFC4X1_types[89])});
  ((entity *)IFC4X1_types[89])->set_subtypes({((entity *)IFC4X1_types[90])});
  ((entity *)IFC4X1_types[249])
      ->set_subtypes(
          {((entity *)IFC4X1_types[91]), ((entity *)IFC4X1_types[188]),
           ((entity *)IFC4X1_types[548]), ((entity *)IFC4X1_types[640]),
           ((entity *)IFC4X1_types[660]), ((entity *)IFC4X1_types[1027])});
  ((entity *)IFC4X1_types[1026])
      ->set_subtypes({((entity *)IFC4X1_types[92]),
                      ((entity *)IFC4X1_types[360]),
                      ((entity *)IFC4X1_types[1047])});
  ((entity *)IFC4X1_types[480])
      ->set_subtypes(
          {((entity *)IFC4X1_types[95]), ((entity *)IFC4X1_types[699])});
  ((entity *)IFC4X1_types[955])
      ->set_subtypes(
          {((entity *)IFC4X1_types[102]), ((entity *)IFC4X1_types[111]),
           ((entity *)IFC4X1_types[926]), ((entity *)IFC4X1_types[946])});
  ((entity *)IFC4X1_types[359])
      ->set_subtypes(
          {((entity *)IFC4X1_types[103]), ((entity *)IFC4X1_types[151]),
           ((entity *)IFC4X1_types[292]), ((entity *)IFC4X1_types[361]),
           ((entity *)IFC4X1_types[364]), ((entity *)IFC4X1_types[414]),
           ((entity *)IFC4X1_types[457]), ((entity *)IFC4X1_types[462]),
           ((entity *)IFC4X1_types[1121]), ((entity *)IFC4X1_types[1162])});
  ((entity *)IFC4X1_types[364])
      ->set_subtypes(
          {((entity *)IFC4X1_types[104]), ((entity *)IFC4X1_types[282]),
           ((entity *)IFC4X1_types[411]), ((entity *)IFC4X1_types[597]),
           ((entity *)IFC4X1_types[815]), ((entity *)IFC4X1_types[1159])});
  ((entity *)IFC4X1_types[365])
      ->set_subtypes(
          {((entity *)IFC4X1_types[105]), ((entity *)IFC4X1_types[283]),
           ((entity *)IFC4X1_types[412]), ((entity *)IFC4X1_types[598]),
           ((entity *)IFC4X1_types[816]), ((entity *)IFC4X1_types[1160])});
  ((entity *)IFC4X1_types[368])
      ->set_subtypes(
          {((entity *)IFC4X1_types[110]), ((entity *)IFC4X1_types[152]),
           ((entity *)IFC4X1_types[293]), ((entity *)IFC4X1_types[362]),
           ((entity *)IFC4X1_types[365]), ((entity *)IFC4X1_types[458]),
           ((entity *)IFC4X1_types[463]), ((entity *)IFC4X1_types[1122])});
  ((entity *)IFC4X1_types[1051])
      ->set_subtypes(
          {((entity *)IFC4X1_types[112]), ((entity *)IFC4X1_types[298]),
           ((entity *)IFC4X1_types[979]), ((entity *)IFC4X1_types[1199])});
  ((entity *)IFC4X1_types[431])
      ->set_subtypes(
          {((entity *)IFC4X1_types[117]), ((entity *)IFC4X1_types[123]),
           ((entity *)IFC4X1_types[321]), ((entity *)IFC4X1_types[514]),
           ((entity *)IFC4X1_types[678])});
  ((entity *)IFC4X1_types[432])
      ->set_subtypes(
          {((entity *)IFC4X1_types[118]), ((entity *)IFC4X1_types[124]),
           ((entity *)IFC4X1_types[322]), ((entity *)IFC4X1_types[515]),
           ((entity *)IFC4X1_types[679])});
  ((entity *)IFC4X1_types[441])
      ->set_subtypes(
          {((entity *)IFC4X1_types[120]), ((entity *)IFC4X1_types[126]),
           ((entity *)IFC4X1_types[324]), ((entity *)IFC4X1_types[681])});
  ((entity *)IFC4X1_types[442])
      ->set_subtypes(
          {((entity *)IFC4X1_types[121]), ((entity *)IFC4X1_types[127]),
           ((entity *)IFC4X1_types[325]), ((entity *)IFC4X1_types[682])});
  ((entity *)IFC4X1_types[695])
      ->set_subtypes({((entity *)IFC4X1_types[130]),
                      ((entity *)IFC4X1_types[696]),
                      ((entity *)IFC4X1_types[697])});
  ((entity *)IFC4X1_types[131])
      ->set_subtypes(
          {((entity *)IFC4X1_types[132]), ((entity *)IFC4X1_types[133])});
  ((entity *)IFC4X1_types[134])
      ->set_subtypes(
          {((entity *)IFC4X1_types[135]), ((entity *)IFC4X1_types[137])});
  ((entity *)IFC4X1_types[135])->set_subtypes({((entity *)IFC4X1_types[136])});
  ((entity *)IFC4X1_types[137])->set_subtypes({((entity *)IFC4X1_types[138])});
  ((entity *)IFC4X1_types[52])->set_subtypes({((entity *)IFC4X1_types[139])});
  ((entity *)IFC4X1_types[188])
      ->set_subtypes(
          {((entity *)IFC4X1_types[147]), ((entity *)IFC4X1_types[369])});
  ((entity *)IFC4X1_types[149])->set_subtypes({((entity *)IFC4X1_types[148])});
  ((entity *)IFC4X1_types[256])
      ->set_subtypes({((entity *)IFC4X1_types[150]),
                      ((entity *)IFC4X1_types[556]),
                      ((entity *)IFC4X1_types[1118])});
  ((entity *)IFC4X1_types[389])
      ->set_subtypes({((entity *)IFC4X1_types[153]),
                      ((entity *)IFC4X1_types[301]),
                      ((entity *)IFC4X1_types[531])});
  ((entity *)IFC4X1_types[393])
      ->set_subtypes(
          {((entity *)IFC4X1_types[154]), ((entity *)IFC4X1_types[303]),
           ((entity *)IFC4X1_types[390]), ((entity *)IFC4X1_types[391]),
           ((entity *)IFC4X1_types[392]), ((entity *)IFC4X1_types[532])});
  ((entity *)IFC4X1_types[189])
      ->set_subtypes(
          {((entity *)IFC4X1_types[157]), ((entity *)IFC4X1_types[647])});
  ((entity *)IFC4X1_types[165])->set_subtypes({((entity *)IFC4X1_types[163])});
  ((entity *)IFC4X1_types[719])
      ->set_subtypes(
          {((entity *)IFC4X1_types[164]), ((entity *)IFC4X1_types[165]),
           ((entity *)IFC4X1_types[258]), ((entity *)IFC4X1_types[259]),
           ((entity *)IFC4X1_types[260]), ((entity *)IFC4X1_types[493]),
           ((entity *)IFC4X1_types[713]), ((entity *)IFC4X1_types[1038]),
           ((entity *)IFC4X1_types[1039]), ((entity *)IFC4X1_types[1041]),
           ((entity *)IFC4X1_types[1042]), ((entity *)IFC4X1_types[1043]),
           ((entity *)IFC4X1_types[1088]), ((entity *)IFC4X1_types[1089]),
           ((entity *)IFC4X1_types[1091]), ((entity *)IFC4X1_types[1094]),
           ((entity *)IFC4X1_types[1095])});
  ((entity *)IFC4X1_types[166])->set_subtypes({((entity *)IFC4X1_types[167])});
  ((entity *)IFC4X1_types[747])
      ->set_subtypes(
          {((entity *)IFC4X1_types[174]), ((entity *)IFC4X1_types[921])});
  ((entity *)IFC4X1_types[764])
      ->set_subtypes(
          {((entity *)IFC4X1_types[175]), ((entity *)IFC4X1_types[922])});
  ((entity *)IFC4X1_types[177])->set_subtypes({((entity *)IFC4X1_types[178])});
  ((entity *)IFC4X1_types[439])
      ->set_subtypes({((entity *)IFC4X1_types[182]),
                      ((entity *)IFC4X1_types[408]),
                      ((entity *)IFC4X1_types[773])});
  ((entity *)IFC4X1_types[440])
      ->set_subtypes({((entity *)IFC4X1_types[183]),
                      ((entity *)IFC4X1_types[409]),
                      ((entity *)IFC4X1_types[774])});
  ((entity *)IFC4X1_types[1110])
      ->set_subtypes(
          {((entity *)IFC4X1_types[189]), ((entity *)IFC4X1_types[332]),
           ((entity *)IFC4X1_types[400]), ((entity *)IFC4X1_types[402]),
           ((entity *)IFC4X1_types[561]), ((entity *)IFC4X1_types[659]),
           ((entity *)IFC4X1_types[1156])});
  ((entity *)IFC4X1_types[191])
      ->set_subtypes(
          {((entity *)IFC4X1_types[190]), ((entity *)IFC4X1_types[193]),
           ((entity *)IFC4X1_types[194]), ((entity *)IFC4X1_types[196])});
  ((entity *)IFC4X1_types[193])->set_subtypes({((entity *)IFC4X1_types[192])});
  ((entity *)IFC4X1_types[208])
      ->set_subtypes(
          {((entity *)IFC4X1_types[199]), ((entity *)IFC4X1_types[202]),
           ((entity *)IFC4X1_types[205]), ((entity *)IFC4X1_types[237]),
           ((entity *)IFC4X1_types[520]), ((entity *)IFC4X1_types[1022])});
  ((entity *)IFC4X1_types[209])
      ->set_subtypes(
          {((entity *)IFC4X1_types[200]), ((entity *)IFC4X1_types[203]),
           ((entity *)IFC4X1_types[206]), ((entity *)IFC4X1_types[238]),
           ((entity *)IFC4X1_types[521]), ((entity *)IFC4X1_types[1023])});
  ((entity *)IFC4X1_types[873])->set_subtypes({((entity *)IFC4X1_types[208])});
  ((entity *)IFC4X1_types[1137])->set_subtypes({((entity *)IFC4X1_types[209])});
  ((entity *)IFC4X1_types[632])
      ->set_subtypes({((entity *)IFC4X1_types[210]),
                      ((entity *)IFC4X1_types[631]),
                      ((entity *)IFC4X1_types[1134])});
  ((entity *)IFC4X1_types[626])
      ->set_subtypes({((entity *)IFC4X1_types[212]),
                      ((entity *)IFC4X1_types[217]),
                      ((entity *)IFC4X1_types[927])});
  ((entity *)IFC4X1_types[217])->set_subtypes({((entity *)IFC4X1_types[218])});
  ((entity *)IFC4X1_types[47])->set_subtypes({((entity *)IFC4X1_types[232])});
  ((entity *)IFC4X1_types[940])
      ->set_subtypes(
          {((entity *)IFC4X1_types[242]), ((entity *)IFC4X1_types[568]),
           ((entity *)IFC4X1_types[900]), ((entity *)IFC4X1_types[1044]),
           ((entity *)IFC4X1_types[1045])});
  ((entity *)IFC4X1_types[722])
      ->set_subtypes(
          {((entity *)IFC4X1_types[257]), ((entity *)IFC4X1_types[417]),
           ((entity *)IFC4X1_types[1036]), ((entity *)IFC4X1_types[1086])});
  ((entity *)IFC4X1_types[360])
      ->set_subtypes(
          {((entity *)IFC4X1_types[262]), ((entity *)IFC4X1_types[689]),
           ((entity *)IFC4X1_types[965]), ((entity *)IFC4X1_types[1112])});
  ((entity *)IFC4X1_types[294])
      ->set_subtypes(
          {((entity *)IFC4X1_types[286]), ((entity *)IFC4X1_types[371]),
           ((entity *)IFC4X1_types[428]), ((entity *)IFC4X1_types[431]),
           ((entity *)IFC4X1_types[439]), ((entity *)IFC4X1_types[441]),
           ((entity *)IFC4X1_types[443]), ((entity *)IFC4X1_types[445]),
           ((entity *)IFC4X1_types[447])});
  ((entity *)IFC4X1_types[295])
      ->set_subtypes(
          {((entity *)IFC4X1_types[287]), ((entity *)IFC4X1_types[372]),
           ((entity *)IFC4X1_types[429]), ((entity *)IFC4X1_types[432]),
           ((entity *)IFC4X1_types[440]), ((entity *)IFC4X1_types[442]),
           ((entity *)IFC4X1_types[444]), ((entity *)IFC4X1_types[446]),
           ((entity *)IFC4X1_types[448])});
  ((entity *)IFC4X1_types[298])->set_subtypes({((entity *)IFC4X1_types[289])});
  ((entity *)IFC4X1_types[292])
      ->set_subtypes(
          {((entity *)IFC4X1_types[290]), ((entity *)IFC4X1_types[294])});
  ((entity *)IFC4X1_types[293])
      ->set_subtypes(
          {((entity *)IFC4X1_types[291]), ((entity *)IFC4X1_types[295])});
  ((entity *)IFC4X1_types[703])->set_subtypes({((entity *)IFC4X1_types[296])});
  ((entity *)IFC4X1_types[715])
      ->set_subtypes(
          {((entity *)IFC4X1_types[307]), ((entity *)IFC4X1_types[310]),
           ((entity *)IFC4X1_types[664]), ((entity *)IFC4X1_types[809]),
           ((entity *)IFC4X1_types[1180]), ((entity *)IFC4X1_types[1183])});
  ((entity *)IFC4X1_types[306])->set_subtypes({((entity *)IFC4X1_types[311])});
  ((entity *)IFC4X1_types[1136])
      ->set_subtypes(
          {((entity *)IFC4X1_types[312]), ((entity *)IFC4X1_types[368]),
           ((entity *)IFC4X1_types[954]), ((entity *)IFC4X1_types[1185])});
  ((entity *)IFC4X1_types[711])->set_subtypes({((entity *)IFC4X1_types[319])});
  ((entity *)IFC4X1_types[712])->set_subtypes({((entity *)IFC4X1_types[320])});
  ((entity *)IFC4X1_types[447])
      ->set_subtypes({((entity *)IFC4X1_types[327]),
                      ((entity *)IFC4X1_types[421]),
                      ((entity *)IFC4X1_types[502])});
  ((entity *)IFC4X1_types[448])
      ->set_subtypes({((entity *)IFC4X1_types[328]),
                      ((entity *)IFC4X1_types[422]),
                      ((entity *)IFC4X1_types[503])});
  ((entity *)IFC4X1_types[332])
      ->set_subtypes({((entity *)IFC4X1_types[333]),
                      ((entity *)IFC4X1_types[651]),
                      ((entity *)IFC4X1_types[1025])});
  ((entity *)IFC4X1_types[561])
      ->set_subtypes({((entity *)IFC4X1_types[334]),
                      ((entity *)IFC4X1_types[702]),
                      ((entity *)IFC4X1_types[1157])});
  ((entity *)IFC4X1_types[443])
      ->set_subtypes(
          {((entity *)IFC4X1_types[345]), ((entity *)IFC4X1_types[1058])});
  ((entity *)IFC4X1_types[444])
      ->set_subtypes(
          {((entity *)IFC4X1_types[346]), ((entity *)IFC4X1_types[1059])});
  ((entity *)IFC4X1_types[779])->set_subtypes({((entity *)IFC4X1_types[367])});
  ((entity *)IFC4X1_types[729])
      ->set_subtypes({((entity *)IFC4X1_types[383]),
                      ((entity *)IFC4X1_types[726]),
                      ((entity *)IFC4X1_types[1061])});
  ((entity *)IFC4X1_types[897])
      ->set_subtypes(
          {((entity *)IFC4X1_types[384]), ((entity *)IFC4X1_types[523]),
           ((entity *)IFC4X1_types[879]), ((entity *)IFC4X1_types[1063]),
           ((entity *)IFC4X1_types[1198])});
  ((entity *)IFC4X1_types[1135])
      ->set_subtypes({((entity *)IFC4X1_types[386]),
                      ((entity *)IFC4X1_types[727]),
                      ((entity *)IFC4X1_types[1065])});
  ((entity *)IFC4X1_types[748])
      ->set_subtypes(
          {((entity *)IFC4X1_types[388]), ((entity *)IFC4X1_types[714]),
           ((entity *)IFC4X1_types[747]), ((entity *)IFC4X1_types[753])});
  ((entity *)IFC4X1_types[397])->set_subtypes({((entity *)IFC4X1_types[395])});
  ((entity *)IFC4X1_types[953])
      ->set_subtypes({((entity *)IFC4X1_types[397]),
                      ((entity *)IFC4X1_types[955]),
                      ((entity *)IFC4X1_types[957])});
  ((entity *)IFC4X1_types[1044])
      ->set_subtypes(
          {((entity *)IFC4X1_types[398]), ((entity *)IFC4X1_types[427]),
           ((entity *)IFC4X1_types[880]), ((entity *)IFC4X1_types[1028])});
  ((entity *)IFC4X1_types[398])->set_subtypes({((entity *)IFC4X1_types[399])});
  ((entity *)IFC4X1_types[402])->set_subtypes({((entity *)IFC4X1_types[403])});
  ((entity *)IFC4X1_types[400])->set_subtypes({((entity *)IFC4X1_types[404])});
  ((entity *)IFC4X1_types[405])->set_subtypes({((entity *)IFC4X1_types[406])});
  ((entity *)IFC4X1_types[981])
      ->set_subtypes(
          {((entity *)IFC4X1_types[407]), ((entity *)IFC4X1_types[935])});
  ((entity *)IFC4X1_types[414])
      ->set_subtypes({((entity *)IFC4X1_types[415]),
                      ((entity *)IFC4X1_types[416]),
                      ((entity *)IFC4X1_types[1029])});
  ((entity *)IFC4X1_types[457])
      ->set_subtypes(
          {((entity *)IFC4X1_types[459]), ((entity *)IFC4X1_types[1052])});
  ((entity *)IFC4X1_types[458])
      ->set_subtypes(
          {((entity *)IFC4X1_types[460]), ((entity *)IFC4X1_types[1053])});
  ((entity *)IFC4X1_types[470])->set_subtypes({((entity *)IFC4X1_types[465])});
  ((entity *)IFC4X1_types[870])->set_subtypes({((entity *)IFC4X1_types[467])});
  ((entity *)IFC4X1_types[871])
      ->set_subtypes(
          {((entity *)IFC4X1_types[468]), ((entity *)IFC4X1_types[570]),
           ((entity *)IFC4X1_types[1019]), ((entity *)IFC4X1_types[1110])});
  ((entity *)IFC4X1_types[467])->set_subtypes({((entity *)IFC4X1_types[469])});
  ((entity *)IFC4X1_types[704])
      ->set_subtypes({((entity *)IFC4X1_types[474]),
                      ((entity *)IFC4X1_types[552]),
                      ((entity *)IFC4X1_types[804])});
  ((entity *)IFC4X1_types[635])
      ->set_subtypes({((entity *)IFC4X1_types[476]),
                      ((entity *)IFC4X1_types[551]),
                      ((entity *)IFC4X1_types[558])});
  ((entity *)IFC4X1_types[1077])
      ->set_subtypes(
          {((entity *)IFC4X1_types[495]), ((entity *)IFC4X1_types[1076])});
  ((entity *)IFC4X1_types[495])->set_subtypes({((entity *)IFC4X1_types[496])});
  ((entity *)IFC4X1_types[1091])
      ->set_subtypes({((entity *)IFC4X1_types[497]),
                      ((entity *)IFC4X1_types[1092]),
                      ((entity *)IFC4X1_types[1093])});
  ((entity *)IFC4X1_types[497])->set_subtypes({((entity *)IFC4X1_types[498])});
  ((entity *)IFC4X1_types[1027])
      ->set_subtypes(
          {((entity *)IFC4X1_types[506]), ((entity *)IFC4X1_types[898])});
  ((entity *)IFC4X1_types[1106])
      ->set_subtypes(
          {((entity *)IFC4X1_types[510]), ((entity *)IFC4X1_types[807])});
  ((entity *)IFC4X1_types[542])
      ->set_subtypes(
          {((entity *)IFC4X1_types[543]), ((entity *)IFC4X1_types[544]),
           ((entity *)IFC4X1_types[545]), ((entity *)IFC4X1_types[546])});
  ((entity *)IFC4X1_types[546])->set_subtypes({((entity *)IFC4X1_types[547])});
  ((entity *)IFC4X1_types[225])->set_subtypes({((entity *)IFC4X1_types[569])});
  ((entity *)IFC4X1_types[579])
      ->set_subtypes(
          {((entity *)IFC4X1_types[575]), ((entity *)IFC4X1_types[577]),
           ((entity *)IFC4X1_types[578]), ((entity *)IFC4X1_types[581]),
           ((entity *)IFC4X1_types[582]), ((entity *)IFC4X1_types[586]),
           ((entity *)IFC4X1_types[587])});
  ((entity *)IFC4X1_types[733])
      ->set_subtypes(
          {((entity *)IFC4X1_types[580]), ((entity *)IFC4X1_types[732])});
  ((entity *)IFC4X1_types[594])
      ->set_subtypes(
          {((entity *)IFC4X1_types[583]), ((entity *)IFC4X1_types[588])});
  ((entity *)IFC4X1_types[581])->set_subtypes({((entity *)IFC4X1_types[584])});
  ((entity *)IFC4X1_types[588])->set_subtypes({((entity *)IFC4X1_types[589])});
  ((entity *)IFC4X1_types[586])->set_subtypes({((entity *)IFC4X1_types[590])});
  ((entity *)IFC4X1_types[388])
      ->set_subtypes(
          {((entity *)IFC4X1_types[591]), ((entity *)IFC4X1_types[737])});
  ((entity *)IFC4X1_types[603])->set_subtypes({((entity *)IFC4X1_types[604])});
  ((entity *)IFC4X1_types[197])
      ->set_subtypes(
          {((entity *)IFC4X1_types[607]), ((entity *)IFC4X1_types[633])});
  ((entity *)IFC4X1_types[273])->set_subtypes({((entity *)IFC4X1_types[609])});
  ((entity *)IFC4X1_types[888])
      ->set_subtypes({((entity *)IFC4X1_types[632]),
                      ((entity *)IFC4X1_types[750]),
                      ((entity *)IFC4X1_types[836])});
  ((entity *)IFC4X1_types[6])->set_subtypes({((entity *)IFC4X1_types[638])});
  ((entity *)IFC4X1_types[640])
      ->set_subtypes({((entity *)IFC4X1_types[641]),
                      ((entity *)IFC4X1_types[642]),
                      ((entity *)IFC4X1_types[643])});
  ((entity *)IFC4X1_types[416])
      ->set_subtypes(
          {((entity *)IFC4X1_types[644]), ((entity *)IFC4X1_types[1164])});
  ((entity *)IFC4X1_types[644])->set_subtypes({((entity *)IFC4X1_types[646])});
  ((entity *)IFC4X1_types[86])->set_subtypes({((entity *)IFC4X1_types[652])});
  ((entity *)IFC4X1_types[672])
      ->set_subtypes(
          {((entity *)IFC4X1_types[670]), ((entity *)IFC4X1_types[673])});
  ((entity *)IFC4X1_types[687])->set_subtypes({((entity *)IFC4X1_types[686])});
  ((entity *)IFC4X1_types[691])->set_subtypes({((entity *)IFC4X1_types[692])});
  ((entity *)IFC4X1_types[1076])
      ->set_subtypes(
          {((entity *)IFC4X1_types[700]), ((entity *)IFC4X1_types[1125])});
  ((entity *)IFC4X1_types[12])
      ->set_subtypes(
          {((entity *)IFC4X1_types[709]), ((entity *)IFC4X1_types[1067])});
  ((entity *)IFC4X1_types[713])
      ->set_subtypes({((entity *)IFC4X1_types[711]),
                      ((entity *)IFC4X1_types[712]),
                      ((entity *)IFC4X1_types[716])});
  ((entity *)IFC4X1_types[757])
      ->set_subtypes({((entity *)IFC4X1_types[715]),
                      ((entity *)IFC4X1_types[756]),
                      ((entity *)IFC4X1_types[779])});
  ((entity *)IFC4X1_types[720])->set_subtypes({((entity *)IFC4X1_types[721])});
  ((entity *)IFC4X1_types[210])
      ->set_subtypes(
          {((entity *)IFC4X1_types[739]), ((entity *)IFC4X1_types[744])});
  ((entity *)IFC4X1_types[226])->set_subtypes({((entity *)IFC4X1_types[740])});
  ((entity *)IFC4X1_types[415])->set_subtypes({((entity *)IFC4X1_types[742])});
  ((entity *)IFC4X1_types[921])
      ->set_subtypes(
          {((entity *)IFC4X1_types[749]), ((entity *)IFC4X1_types[752]),
           ((entity *)IFC4X1_types[754]), ((entity *)IFC4X1_types[755]),
           ((entity *)IFC4X1_types[762]), ((entity *)IFC4X1_types[763])});
  ((entity *)IFC4X1_types[750])
      ->set_subtypes(
          {((entity *)IFC4X1_types[757]), ((entity *)IFC4X1_types[765])});
  ((entity *)IFC4X1_types[765])
      ->set_subtypes(
          {((entity *)IFC4X1_types[760]), ((entity *)IFC4X1_types[764])});
  ((entity *)IFC4X1_types[673])
      ->set_subtypes(
          {((entity *)IFC4X1_types[776]), ((entity *)IFC4X1_types[777]),
           ((entity *)IFC4X1_types[778]), ((entity *)IFC4X1_types[780]),
           ((entity *)IFC4X1_types[781]), ((entity *)IFC4X1_types[782])});
  ((entity *)IFC4X1_types[98])->set_subtypes({((entity *)IFC4X1_types[794])});
  ((entity *)IFC4X1_types[101])->set_subtypes({((entity *)IFC4X1_types[795])});
  ((entity *)IFC4X1_types[798])
      ->set_subtypes(
          {((entity *)IFC4X1_types[797]), ((entity *)IFC4X1_types[893])});
  ((entity *)IFC4X1_types[714])
      ->set_subtypes({((entity *)IFC4X1_types[808]),
                      ((entity *)IFC4X1_types[904]),
                      ((entity *)IFC4X1_types[905])});
  ((entity *)IFC4X1_types[815])
      ->set_subtypes(
          {((entity *)IFC4X1_types[810]), ((entity *)IFC4X1_types[817]),
           ((entity *)IFC4X1_types[1070]), ((entity *)IFC4X1_types[1071])});
  ((entity *)IFC4X1_types[816])
      ->set_subtypes(
          {((entity *)IFC4X1_types[813]), ((entity *)IFC4X1_types[818]),
           ((entity *)IFC4X1_types[1072]), ((entity *)IFC4X1_types[1074])});
  ((entity *)IFC4X1_types[850])
      ->set_subtypes(
          {((entity *)IFC4X1_types[820]), ((entity *)IFC4X1_types[859]),
           ((entity *)IFC4X1_types[860]), ((entity *)IFC4X1_types[867])});
  ((entity *)IFC4X1_types[836])
      ->set_subtypes(
          {((entity *)IFC4X1_types[821]), ((entity *)IFC4X1_types[829]),
           ((entity *)IFC4X1_types[837]), ((entity *)IFC4X1_types[849]),
           ((entity *)IFC4X1_types[850]), ((entity *)IFC4X1_types[851])});
  ((entity *)IFC4X1_types[821])
      ->set_subtypes(
          {((entity *)IFC4X1_types[822]), ((entity *)IFC4X1_types[823]),
           ((entity *)IFC4X1_types[824]), ((entity *)IFC4X1_types[826]),
           ((entity *)IFC4X1_types[827]), ((entity *)IFC4X1_types[828])});
  ((entity *)IFC4X1_types[824])->set_subtypes({((entity *)IFC4X1_types[825])});
  ((entity *)IFC4X1_types[829])
      ->set_subtypes(
          {((entity *)IFC4X1_types[830]), ((entity *)IFC4X1_types[831]),
           ((entity *)IFC4X1_types[832]), ((entity *)IFC4X1_types[833]),
           ((entity *)IFC4X1_types[834]), ((entity *)IFC4X1_types[835])});
  ((entity *)IFC4X1_types[837])
      ->set_subtypes(
          {((entity *)IFC4X1_types[838]), ((entity *)IFC4X1_types[841]),
           ((entity *)IFC4X1_types[840]), ((entity *)IFC4X1_types[842]),
           ((entity *)IFC4X1_types[843]), ((entity *)IFC4X1_types[846]),
           ((entity *)IFC4X1_types[847]), ((entity *)IFC4X1_types[848]),
           ((entity *)IFC4X1_types[856]), ((entity *)IFC4X1_types[857]),
           ((entity *)IFC4X1_types[858]), ((entity *)IFC4X1_types[861]),
           ((entity *)IFC4X1_types[862]), ((entity *)IFC4X1_types[863]),
           ((entity *)IFC4X1_types[864])});
  ((entity *)IFC4X1_types[838])
      ->set_subtypes(
          {((entity *)IFC4X1_types[839]), ((entity *)IFC4X1_types[845])});
  ((entity *)IFC4X1_types[843])->set_subtypes({((entity *)IFC4X1_types[844])});
  ((entity *)IFC4X1_types[851])
      ->set_subtypes(
          {((entity *)IFC4X1_types[852]), ((entity *)IFC4X1_types[853]),
           ((entity *)IFC4X1_types[854]), ((entity *)IFC4X1_types[855])});
  ((entity *)IFC4X1_types[864])->set_subtypes({((entity *)IFC4X1_types[865])});
  ((entity *)IFC4X1_types[865])->set_subtypes({((entity *)IFC4X1_types[866])});
  ((entity *)IFC4X1_types[179])->set_subtypes({((entity *)IFC4X1_types[868])});
  ((entity *)IFC4X1_types[880])->set_subtypes({((entity *)IFC4X1_types[881])});
  ((entity *)IFC4X1_types[900])->set_subtypes({((entity *)IFC4X1_types[901])});
  ((entity *)IFC4X1_types[869])
      ->set_subtypes(
          {((entity *)IFC4X1_types[916]), ((entity *)IFC4X1_types[1021])});
  ((entity *)IFC4X1_types[916])
      ->set_subtypes(
          {((entity *)IFC4X1_types[917]), ((entity *)IFC4X1_types[1111])});
  ((entity *)IFC4X1_types[930])
      ->set_subtypes(
          {((entity *)IFC4X1_types[931]), ((entity *)IFC4X1_types[932])});
  ((entity *)IFC4X1_types[956])->set_subtypes({((entity *)IFC4X1_types[951])});
  ((entity *)IFC4X1_types[954])
      ->set_subtypes(
          {((entity *)IFC4X1_types[956]), ((entity *)IFC4X1_types[958])});
  ((entity *)IFC4X1_types[977])
      ->set_subtypes(
          {((entity *)IFC4X1_types[976]), ((entity *)IFC4X1_types[1009])});
  ((entity *)IFC4X1_types[989])
      ->set_subtypes(
          {((entity *)IFC4X1_types[980]), ((entity *)IFC4X1_types[1004])});
  ((entity *)IFC4X1_types[976])
      ->set_subtypes({((entity *)IFC4X1_types[982]),
                      ((entity *)IFC4X1_types[1006]),
                      ((entity *)IFC4X1_types[1011])});
  ((entity *)IFC4X1_types[980])
      ->set_subtypes({((entity *)IFC4X1_types[984]),
                      ((entity *)IFC4X1_types[1007]),
                      ((entity *)IFC4X1_types[1013])});
  ((entity *)IFC4X1_types[1004])
      ->set_subtypes(
          {((entity *)IFC4X1_types[985]), ((entity *)IFC4X1_types[1014])});
  ((entity *)IFC4X1_types[985])->set_subtypes({((entity *)IFC4X1_types[987])});
  ((entity *)IFC4X1_types[1009])
      ->set_subtypes({((entity *)IFC4X1_types[988]),
                      ((entity *)IFC4X1_types[1008]),
                      ((entity *)IFC4X1_types[1017])});
  ((entity *)IFC4X1_types[982])->set_subtypes({((entity *)IFC4X1_types[990])});
  ((entity *)IFC4X1_types[994])->set_subtypes({((entity *)IFC4X1_types[992])});
  ((entity *)IFC4X1_types[991])
      ->set_subtypes(
          {((entity *)IFC4X1_types[993]), ((entity *)IFC4X1_types[996])});
  ((entity *)IFC4X1_types[1002])
      ->set_subtypes(
          {((entity *)IFC4X1_types[995]), ((entity *)IFC4X1_types[997]),
           ((entity *)IFC4X1_types[998]), ((entity *)IFC4X1_types[1000]),
           ((entity *)IFC4X1_types[1003])});
  ((entity *)IFC4X1_types[998])->set_subtypes({((entity *)IFC4X1_types[999])});
  ((entity *)IFC4X1_types[1000])
      ->set_subtypes({((entity *)IFC4X1_types[1001])});
  ((entity *)IFC4X1_types[996])
      ->set_subtypes(
          {((entity *)IFC4X1_types[1002]), ((entity *)IFC4X1_types[1034])});
  ((entity *)IFC4X1_types[1011])
      ->set_subtypes({((entity *)IFC4X1_types[1005])});
  ((entity *)IFC4X1_types[1014])
      ->set_subtypes({((entity *)IFC4X1_types[1016])});
  ((entity *)IFC4X1_types[1021])
      ->set_subtypes({((entity *)IFC4X1_types[1020])});
  ((entity *)IFC4X1_types[1047])
      ->set_subtypes(
          {((entity *)IFC4X1_types[1031]), ((entity *)IFC4X1_types[1032])});
  ((entity *)IFC4X1_types[1041])
      ->set_subtypes({((entity *)IFC4X1_types[1040])});
  ((entity *)IFC4X1_types[1045])
      ->set_subtypes({((entity *)IFC4X1_types[1046])});
  ((entity *)IFC4X1_types[1063])
      ->set_subtypes({((entity *)IFC4X1_types[1064])});
  ((entity *)IFC4X1_types[1083])
      ->set_subtypes({((entity *)IFC4X1_types[1084])});
  ((entity *)IFC4X1_types[716])->set_subtypes({((entity *)IFC4X1_types[1087])});
  ((entity *)IFC4X1_types[1125])
      ->set_subtypes({((entity *)IFC4X1_types[1126])});
  ((entity *)IFC4X1_types[1134])
      ->set_subtypes({((entity *)IFC4X1_types[1135]),
                      ((entity *)IFC4X1_types[1136]),
                      ((entity *)IFC4X1_types[1137])});
  ((entity *)IFC4X1_types[1156])
      ->set_subtypes({((entity *)IFC4X1_types[1158])});
  ((entity *)IFC4X1_types[1168])
      ->set_subtypes(
          {((entity *)IFC4X1_types[1169]), ((entity *)IFC4X1_types[1170])});
  ((entity *)IFC4X1_types[1179])
      ->set_subtypes({((entity *)IFC4X1_types[1184])});
  ((entity *)IFC4X1_types[1193])
      ->set_subtypes(
          {((entity *)IFC4X1_types[1194]), ((entity *)IFC4X1_types[1196])});
  return new schema_definition(
      strings[3379],
      {IFC4X1_types[0],    IFC4X1_types[1],    IFC4X1_types[2],
       IFC4X1_types[3],    IFC4X1_types[4],    IFC4X1_types[5],
       IFC4X1_types[6],    IFC4X1_types[7],    IFC4X1_types[8],
       IFC4X1_types[9],    IFC4X1_types[10],   IFC4X1_types[11],
       IFC4X1_types[12],   IFC4X1_types[13],   IFC4X1_types[14],
       IFC4X1_types[15],   IFC4X1_types[16],   IFC4X1_types[17],
       IFC4X1_types[18],   IFC4X1_types[19],   IFC4X1_types[20],
       IFC4X1_types[21],   IFC4X1_types[22],   IFC4X1_types[23],
       IFC4X1_types[24],   IFC4X1_types[25],   IFC4X1_types[26],
       IFC4X1_types[27],   IFC4X1_types[28],   IFC4X1_types[29],
       IFC4X1_types[30],   IFC4X1_types[31],   IFC4X1_types[32],
       IFC4X1_types[33],   IFC4X1_types[34],   IFC4X1_types[35],
       IFC4X1_types[36],   IFC4X1_types[37],   IFC4X1_types[38],
       IFC4X1_types[39],   IFC4X1_types[40],   IFC4X1_types[41],
       IFC4X1_types[42],   IFC4X1_types[43],   IFC4X1_types[44],
       IFC4X1_types[45],   IFC4X1_types[46],   IFC4X1_types[47],
       IFC4X1_types[48],   IFC4X1_types[49],   IFC4X1_types[50],
       IFC4X1_types[51],   IFC4X1_types[52],   IFC4X1_types[53],
       IFC4X1_types[54],   IFC4X1_types[55],   IFC4X1_types[56],
       IFC4X1_types[57],   IFC4X1_types[58],   IFC4X1_types[59],
       IFC4X1_types[60],   IFC4X1_types[61],   IFC4X1_types[62],
       IFC4X1_types[63],   IFC4X1_types[64],   IFC4X1_types[65],
       IFC4X1_types[66],   IFC4X1_types[67],   IFC4X1_types[68],
       IFC4X1_types[69],   IFC4X1_types[70],   IFC4X1_types[71],
       IFC4X1_types[72],   IFC4X1_types[73],   IFC4X1_types[74],
       IFC4X1_types[75],   IFC4X1_types[76],   IFC4X1_types[77],
       IFC4X1_types[78],   IFC4X1_types[79],   IFC4X1_types[80],
       IFC4X1_types[81],   IFC4X1_types[82],   IFC4X1_types[83],
       IFC4X1_types[84],   IFC4X1_types[85],   IFC4X1_types[86],
       IFC4X1_types[87],   IFC4X1_types[88],   IFC4X1_types[89],
       IFC4X1_types[90],   IFC4X1_types[91],   IFC4X1_types[92],
       IFC4X1_types[93],   IFC4X1_types[94],   IFC4X1_types[95],
       IFC4X1_types[96],   IFC4X1_types[97],   IFC4X1_types[98],
       IFC4X1_types[99],   IFC4X1_types[100],  IFC4X1_types[101],
       IFC4X1_types[102],  IFC4X1_types[103],  IFC4X1_types[104],
       IFC4X1_types[105],  IFC4X1_types[106],  IFC4X1_types[107],
       IFC4X1_types[108],  IFC4X1_types[109],  IFC4X1_types[110],
       IFC4X1_types[111],  IFC4X1_types[112],  IFC4X1_types[113],
       IFC4X1_types[114],  IFC4X1_types[115],  IFC4X1_types[116],
       IFC4X1_types[117],  IFC4X1_types[118],  IFC4X1_types[119],
       IFC4X1_types[120],  IFC4X1_types[121],  IFC4X1_types[122],
       IFC4X1_types[123],  IFC4X1_types[124],  IFC4X1_types[125],
       IFC4X1_types[126],  IFC4X1_types[127],  IFC4X1_types[128],
       IFC4X1_types[129],  IFC4X1_types[130],  IFC4X1_types[131],
       IFC4X1_types[132],  IFC4X1_types[133],  IFC4X1_types[134],
       IFC4X1_types[135],  IFC4X1_types[136],  IFC4X1_types[137],
       IFC4X1_types[138],  IFC4X1_types[139],  IFC4X1_types[140],
       IFC4X1_types[141],  IFC4X1_types[142],  IFC4X1_types[143],
       IFC4X1_types[144],  IFC4X1_types[145],  IFC4X1_types[146],
       IFC4X1_types[147],  IFC4X1_types[148],  IFC4X1_types[149],
       IFC4X1_types[150],  IFC4X1_types[151],  IFC4X1_types[152],
       IFC4X1_types[153],  IFC4X1_types[154],  IFC4X1_types[155],
       IFC4X1_types[156],  IFC4X1_types[157],  IFC4X1_types[158],
       IFC4X1_types[159],  IFC4X1_types[160],  IFC4X1_types[161],
       IFC4X1_types[162],  IFC4X1_types[163],  IFC4X1_types[164],
       IFC4X1_types[165],  IFC4X1_types[166],  IFC4X1_types[167],
       IFC4X1_types[168],  IFC4X1_types[169],  IFC4X1_types[170],
       IFC4X1_types[171],  IFC4X1_types[172],  IFC4X1_types[173],
       IFC4X1_types[174],  IFC4X1_types[175],  IFC4X1_types[176],
       IFC4X1_types[177],  IFC4X1_types[178],  IFC4X1_types[179],
       IFC4X1_types[180],  IFC4X1_types[181],  IFC4X1_types[182],
       IFC4X1_types[183],  IFC4X1_types[184],  IFC4X1_types[185],
       IFC4X1_types[186],  IFC4X1_types[187],  IFC4X1_types[188],
       IFC4X1_types[189],  IFC4X1_types[190],  IFC4X1_types[191],
       IFC4X1_types[192],  IFC4X1_types[193],  IFC4X1_types[194],
       IFC4X1_types[195],  IFC4X1_types[196],  IFC4X1_types[197],
       IFC4X1_types[198],  IFC4X1_types[199],  IFC4X1_types[200],
       IFC4X1_types[201],  IFC4X1_types[202],  IFC4X1_types[203],
       IFC4X1_types[204],  IFC4X1_types[205],  IFC4X1_types[206],
       IFC4X1_types[207],  IFC4X1_types[208],  IFC4X1_types[209],
       IFC4X1_types[210],  IFC4X1_types[211],  IFC4X1_types[212],
       IFC4X1_types[213],  IFC4X1_types[214],  IFC4X1_types[215],
       IFC4X1_types[216],  IFC4X1_types[217],  IFC4X1_types[218],
       IFC4X1_types[219],  IFC4X1_types[220],  IFC4X1_types[221],
       IFC4X1_types[222],  IFC4X1_types[223],  IFC4X1_types[224],
       IFC4X1_types[225],  IFC4X1_types[226],  IFC4X1_types[227],
       IFC4X1_types[228],  IFC4X1_types[229],  IFC4X1_types[230],
       IFC4X1_types[231],  IFC4X1_types[232],  IFC4X1_types[233],
       IFC4X1_types[234],  IFC4X1_types[235],  IFC4X1_types[236],
       IFC4X1_types[237],  IFC4X1_types[238],  IFC4X1_types[239],
       IFC4X1_types[240],  IFC4X1_types[241],  IFC4X1_types[242],
       IFC4X1_types[243],  IFC4X1_types[244],  IFC4X1_types[245],
       IFC4X1_types[246],  IFC4X1_types[247],  IFC4X1_types[248],
       IFC4X1_types[249],  IFC4X1_types[250],  IFC4X1_types[251],
       IFC4X1_types[252],  IFC4X1_types[253],  IFC4X1_types[254],
       IFC4X1_types[255],  IFC4X1_types[256],  IFC4X1_types[257],
       IFC4X1_types[258],  IFC4X1_types[259],  IFC4X1_types[260],
       IFC4X1_types[261],  IFC4X1_types[262],  IFC4X1_types[263],
       IFC4X1_types[264],  IFC4X1_types[265],  IFC4X1_types[266],
       IFC4X1_types[267],  IFC4X1_types[268],  IFC4X1_types[269],
       IFC4X1_types[270],  IFC4X1_types[271],  IFC4X1_types[272],
       IFC4X1_types[273],  IFC4X1_types[274],  IFC4X1_types[275],
       IFC4X1_types[276],  IFC4X1_types[277],  IFC4X1_types[278],
       IFC4X1_types[279],  IFC4X1_types[280],  IFC4X1_types[281],
       IFC4X1_types[282],  IFC4X1_types[283],  IFC4X1_types[284],
       IFC4X1_types[285],  IFC4X1_types[286],  IFC4X1_types[287],
       IFC4X1_types[288],  IFC4X1_types[289],  IFC4X1_types[290],
       IFC4X1_types[291],  IFC4X1_types[292],  IFC4X1_types[293],
       IFC4X1_types[294],  IFC4X1_types[295],  IFC4X1_types[296],
       IFC4X1_types[297],  IFC4X1_types[298],  IFC4X1_types[299],
       IFC4X1_types[300],  IFC4X1_types[301],  IFC4X1_types[302],
       IFC4X1_types[303],  IFC4X1_types[304],  IFC4X1_types[305],
       IFC4X1_types[306],  IFC4X1_types[307],  IFC4X1_types[308],
       IFC4X1_types[309],  IFC4X1_types[310],  IFC4X1_types[311],
       IFC4X1_types[312],  IFC4X1_types[313],  IFC4X1_types[314],
       IFC4X1_types[315],  IFC4X1_types[316],  IFC4X1_types[317],
       IFC4X1_types[318],  IFC4X1_types[319],  IFC4X1_types[320],
       IFC4X1_types[321],  IFC4X1_types[322],  IFC4X1_types[323],
       IFC4X1_types[324],  IFC4X1_types[325],  IFC4X1_types[326],
       IFC4X1_types[327],  IFC4X1_types[328],  IFC4X1_types[329],
       IFC4X1_types[330],  IFC4X1_types[331],  IFC4X1_types[332],
       IFC4X1_types[333],  IFC4X1_types[334],  IFC4X1_types[335],
       IFC4X1_types[336],  IFC4X1_types[337],  IFC4X1_types[338],
       IFC4X1_types[339],  IFC4X1_types[340],  IFC4X1_types[341],
       IFC4X1_types[342],  IFC4X1_types[343],  IFC4X1_types[344],
       IFC4X1_types[345],  IFC4X1_types[346],  IFC4X1_types[347],
       IFC4X1_types[348],  IFC4X1_types[349],  IFC4X1_types[350],
       IFC4X1_types[351],  IFC4X1_types[352],  IFC4X1_types[353],
       IFC4X1_types[354],  IFC4X1_types[355],  IFC4X1_types[356],
       IFC4X1_types[357],  IFC4X1_types[358],  IFC4X1_types[359],
       IFC4X1_types[360],  IFC4X1_types[361],  IFC4X1_types[362],
       IFC4X1_types[363],  IFC4X1_types[364],  IFC4X1_types[365],
       IFC4X1_types[366],  IFC4X1_types[367],  IFC4X1_types[368],
       IFC4X1_types[369],  IFC4X1_types[370],  IFC4X1_types[371],
       IFC4X1_types[372],  IFC4X1_types[373],  IFC4X1_types[374],
       IFC4X1_types[375],  IFC4X1_types[376],  IFC4X1_types[377],
       IFC4X1_types[378],  IFC4X1_types[379],  IFC4X1_types[380],
       IFC4X1_types[381],  IFC4X1_types[382],  IFC4X1_types[383],
       IFC4X1_types[384],  IFC4X1_types[385],  IFC4X1_types[386],
       IFC4X1_types[387],  IFC4X1_types[388],  IFC4X1_types[389],
       IFC4X1_types[390],  IFC4X1_types[391],  IFC4X1_types[392],
       IFC4X1_types[393],  IFC4X1_types[394],  IFC4X1_types[395],
       IFC4X1_types[396],  IFC4X1_types[397],  IFC4X1_types[398],
       IFC4X1_types[399],  IFC4X1_types[400],  IFC4X1_types[401],
       IFC4X1_types[402],  IFC4X1_types[403],  IFC4X1_types[404],
       IFC4X1_types[405],  IFC4X1_types[406],  IFC4X1_types[407],
       IFC4X1_types[408],  IFC4X1_types[409],  IFC4X1_types[410],
       IFC4X1_types[411],  IFC4X1_types[412],  IFC4X1_types[413],
       IFC4X1_types[414],  IFC4X1_types[415],  IFC4X1_types[416],
       IFC4X1_types[417],  IFC4X1_types[418],  IFC4X1_types[419],
       IFC4X1_types[420],  IFC4X1_types[421],  IFC4X1_types[422],
       IFC4X1_types[423],  IFC4X1_types[424],  IFC4X1_types[425],
       IFC4X1_types[426],  IFC4X1_types[427],  IFC4X1_types[428],
       IFC4X1_types[429],  IFC4X1_types[430],  IFC4X1_types[431],
       IFC4X1_types[432],  IFC4X1_types[433],  IFC4X1_types[434],
       IFC4X1_types[435],  IFC4X1_types[436],  IFC4X1_types[437],
       IFC4X1_types[438],  IFC4X1_types[439],  IFC4X1_types[440],
       IFC4X1_types[441],  IFC4X1_types[442],  IFC4X1_types[443],
       IFC4X1_types[444],  IFC4X1_types[445],  IFC4X1_types[446],
       IFC4X1_types[447],  IFC4X1_types[448],  IFC4X1_types[449],
       IFC4X1_types[450],  IFC4X1_types[451],  IFC4X1_types[452],
       IFC4X1_types[453],  IFC4X1_types[454],  IFC4X1_types[455],
       IFC4X1_types[456],  IFC4X1_types[457],  IFC4X1_types[458],
       IFC4X1_types[459],  IFC4X1_types[460],  IFC4X1_types[461],
       IFC4X1_types[462],  IFC4X1_types[463],  IFC4X1_types[464],
       IFC4X1_types[465],  IFC4X1_types[466],  IFC4X1_types[467],
       IFC4X1_types[468],  IFC4X1_types[469],  IFC4X1_types[470],
       IFC4X1_types[471],  IFC4X1_types[472],  IFC4X1_types[473],
       IFC4X1_types[474],  IFC4X1_types[475],  IFC4X1_types[476],
       IFC4X1_types[477],  IFC4X1_types[478],  IFC4X1_types[479],
       IFC4X1_types[480],  IFC4X1_types[481],  IFC4X1_types[482],
       IFC4X1_types[483],  IFC4X1_types[484],  IFC4X1_types[485],
       IFC4X1_types[486],  IFC4X1_types[487],  IFC4X1_types[488],
       IFC4X1_types[489],  IFC4X1_types[490],  IFC4X1_types[491],
       IFC4X1_types[492],  IFC4X1_types[493],  IFC4X1_types[494],
       IFC4X1_types[495],  IFC4X1_types[496],  IFC4X1_types[497],
       IFC4X1_types[498],  IFC4X1_types[499],  IFC4X1_types[500],
       IFC4X1_types[501],  IFC4X1_types[502],  IFC4X1_types[503],
       IFC4X1_types[504],  IFC4X1_types[505],  IFC4X1_types[506],
       IFC4X1_types[507],  IFC4X1_types[508],  IFC4X1_types[509],
       IFC4X1_types[510],  IFC4X1_types[511],  IFC4X1_types[512],
       IFC4X1_types[513],  IFC4X1_types[514],  IFC4X1_types[515],
       IFC4X1_types[516],  IFC4X1_types[517],  IFC4X1_types[518],
       IFC4X1_types[519],  IFC4X1_types[520],  IFC4X1_types[521],
       IFC4X1_types[522],  IFC4X1_types[523],  IFC4X1_types[524],
       IFC4X1_types[525],  IFC4X1_types[526],  IFC4X1_types[527],
       IFC4X1_types[528],  IFC4X1_types[529],  IFC4X1_types[530],
       IFC4X1_types[531],  IFC4X1_types[532],  IFC4X1_types[533],
       IFC4X1_types[534],  IFC4X1_types[535],  IFC4X1_types[536],
       IFC4X1_types[537],  IFC4X1_types[538],  IFC4X1_types[539],
       IFC4X1_types[540],  IFC4X1_types[541],  IFC4X1_types[542],
       IFC4X1_types[543],  IFC4X1_types[544],  IFC4X1_types[545],
       IFC4X1_types[546],  IFC4X1_types[547],  IFC4X1_types[548],
       IFC4X1_types[549],  IFC4X1_types[550],  IFC4X1_types[551],
       IFC4X1_types[552],  IFC4X1_types[553],  IFC4X1_types[554],
       IFC4X1_types[555],  IFC4X1_types[556],  IFC4X1_types[557],
       IFC4X1_types[558],  IFC4X1_types[559],  IFC4X1_types[560],
       IFC4X1_types[561],  IFC4X1_types[562],  IFC4X1_types[563],
       IFC4X1_types[564],  IFC4X1_types[565],  IFC4X1_types[566],
       IFC4X1_types[567],  IFC4X1_types[568],  IFC4X1_types[569],
       IFC4X1_types[570],  IFC4X1_types[571],  IFC4X1_types[572],
       IFC4X1_types[573],  IFC4X1_types[574],  IFC4X1_types[575],
       IFC4X1_types[576],  IFC4X1_types[577],  IFC4X1_types[578],
       IFC4X1_types[579],  IFC4X1_types[580],  IFC4X1_types[581],
       IFC4X1_types[582],  IFC4X1_types[583],  IFC4X1_types[584],
       IFC4X1_types[585],  IFC4X1_types[586],  IFC4X1_types[587],
       IFC4X1_types[588],  IFC4X1_types[589],  IFC4X1_types[590],
       IFC4X1_types[591],  IFC4X1_types[592],  IFC4X1_types[593],
       IFC4X1_types[594],  IFC4X1_types[595],  IFC4X1_types[596],
       IFC4X1_types[597],  IFC4X1_types[598],  IFC4X1_types[599],
       IFC4X1_types[600],  IFC4X1_types[601],  IFC4X1_types[602],
       IFC4X1_types[603],  IFC4X1_types[604],  IFC4X1_types[605],
       IFC4X1_types[606],  IFC4X1_types[607],  IFC4X1_types[608],
       IFC4X1_types[609],  IFC4X1_types[610],  IFC4X1_types[611],
       IFC4X1_types[612],  IFC4X1_types[613],  IFC4X1_types[614],
       IFC4X1_types[615],  IFC4X1_types[616],  IFC4X1_types[617],
       IFC4X1_types[618],  IFC4X1_types[619],  IFC4X1_types[620],
       IFC4X1_types[621],  IFC4X1_types[622],  IFC4X1_types[623],
       IFC4X1_types[624],  IFC4X1_types[625],  IFC4X1_types[626],
       IFC4X1_types[627],  IFC4X1_types[628],  IFC4X1_types[629],
       IFC4X1_types[630],  IFC4X1_types[631],  IFC4X1_types[632],
       IFC4X1_types[633],  IFC4X1_types[634],  IFC4X1_types[635],
       IFC4X1_types[636],  IFC4X1_types[637],  IFC4X1_types[638],
       IFC4X1_types[639],  IFC4X1_types[640],  IFC4X1_types[641],
       IFC4X1_types[642],  IFC4X1_types[643],  IFC4X1_types[644],
       IFC4X1_types[645],  IFC4X1_types[646],  IFC4X1_types[647],
       IFC4X1_types[648],  IFC4X1_types[649],  IFC4X1_types[650],
       IFC4X1_types[651],  IFC4X1_types[652],  IFC4X1_types[653],
       IFC4X1_types[654],  IFC4X1_types[655],  IFC4X1_types[656],
       IFC4X1_types[657],  IFC4X1_types[658],  IFC4X1_types[659],
       IFC4X1_types[660],  IFC4X1_types[661],  IFC4X1_types[662],
       IFC4X1_types[663],  IFC4X1_types[664],  IFC4X1_types[665],
       IFC4X1_types[666],  IFC4X1_types[667],  IFC4X1_types[668],
       IFC4X1_types[669],  IFC4X1_types[670],  IFC4X1_types[671],
       IFC4X1_types[672],  IFC4X1_types[673],  IFC4X1_types[674],
       IFC4X1_types[675],  IFC4X1_types[676],  IFC4X1_types[677],
       IFC4X1_types[678],  IFC4X1_types[679],  IFC4X1_types[680],
       IFC4X1_types[681],  IFC4X1_types[682],  IFC4X1_types[683],
       IFC4X1_types[684],  IFC4X1_types[685],  IFC4X1_types[686],
       IFC4X1_types[687],  IFC4X1_types[688],  IFC4X1_types[689],
       IFC4X1_types[690],  IFC4X1_types[691],  IFC4X1_types[692],
       IFC4X1_types[693],  IFC4X1_types[694],  IFC4X1_types[695],
       IFC4X1_types[696],  IFC4X1_types[697],  IFC4X1_types[698],
       IFC4X1_types[699],  IFC4X1_types[700],  IFC4X1_types[701],
       IFC4X1_types[702],  IFC4X1_types[703],  IFC4X1_types[704],
       IFC4X1_types[705],  IFC4X1_types[706],  IFC4X1_types[707],
       IFC4X1_types[708],  IFC4X1_types[709],  IFC4X1_types[710],
       IFC4X1_types[711],  IFC4X1_types[712],  IFC4X1_types[713],
       IFC4X1_types[714],  IFC4X1_types[715],  IFC4X1_types[716],
       IFC4X1_types[717],  IFC4X1_types[718],  IFC4X1_types[719],
       IFC4X1_types[720],  IFC4X1_types[721],  IFC4X1_types[722],
       IFC4X1_types[723],  IFC4X1_types[724],  IFC4X1_types[725],
       IFC4X1_types[726],  IFC4X1_types[727],  IFC4X1_types[728],
       IFC4X1_types[729],  IFC4X1_types[730],  IFC4X1_types[731],
       IFC4X1_types[732],  IFC4X1_types[733],  IFC4X1_types[734],
       IFC4X1_types[735],  IFC4X1_types[736],  IFC4X1_types[737],
       IFC4X1_types[738],  IFC4X1_types[739],  IFC4X1_types[740],
       IFC4X1_types[741],  IFC4X1_types[742],  IFC4X1_types[743],
       IFC4X1_types[744],  IFC4X1_types[745],  IFC4X1_types[746],
       IFC4X1_types[747],  IFC4X1_types[748],  IFC4X1_types[749],
       IFC4X1_types[750],  IFC4X1_types[751],  IFC4X1_types[752],
       IFC4X1_types[753],  IFC4X1_types[754],  IFC4X1_types[755],
       IFC4X1_types[756],  IFC4X1_types[757],  IFC4X1_types[758],
       IFC4X1_types[759],  IFC4X1_types[760],  IFC4X1_types[761],
       IFC4X1_types[762],  IFC4X1_types[763],  IFC4X1_types[764],
       IFC4X1_types[765],  IFC4X1_types[766],  IFC4X1_types[767],
       IFC4X1_types[768],  IFC4X1_types[769],  IFC4X1_types[770],
       IFC4X1_types[771],  IFC4X1_types[772],  IFC4X1_types[773],
       IFC4X1_types[774],  IFC4X1_types[775],  IFC4X1_types[776],
       IFC4X1_types[777],  IFC4X1_types[778],  IFC4X1_types[779],
       IFC4X1_types[780],  IFC4X1_types[781],  IFC4X1_types[782],
       IFC4X1_types[783],  IFC4X1_types[784],  IFC4X1_types[785],
       IFC4X1_types[786],  IFC4X1_types[787],  IFC4X1_types[788],
       IFC4X1_types[789],  IFC4X1_types[790],  IFC4X1_types[791],
       IFC4X1_types[792],  IFC4X1_types[793],  IFC4X1_types[794],
       IFC4X1_types[795],  IFC4X1_types[796],  IFC4X1_types[797],
       IFC4X1_types[798],  IFC4X1_types[799],  IFC4X1_types[800],
       IFC4X1_types[801],  IFC4X1_types[802],  IFC4X1_types[803],
       IFC4X1_types[804],  IFC4X1_types[805],  IFC4X1_types[806],
       IFC4X1_types[807],  IFC4X1_types[808],  IFC4X1_types[809],
       IFC4X1_types[810],  IFC4X1_types[811],  IFC4X1_types[812],
       IFC4X1_types[813],  IFC4X1_types[814],  IFC4X1_types[815],
       IFC4X1_types[816],  IFC4X1_types[817],  IFC4X1_types[818],
       IFC4X1_types[819],  IFC4X1_types[820],  IFC4X1_types[821],
       IFC4X1_types[822],  IFC4X1_types[823],  IFC4X1_types[824],
       IFC4X1_types[825],  IFC4X1_types[826],  IFC4X1_types[827],
       IFC4X1_types[828],  IFC4X1_types[829],  IFC4X1_types[830],
       IFC4X1_types[831],  IFC4X1_types[832],  IFC4X1_types[833],
       IFC4X1_types[834],  IFC4X1_types[835],  IFC4X1_types[836],
       IFC4X1_types[837],  IFC4X1_types[838],  IFC4X1_types[839],
       IFC4X1_types[840],  IFC4X1_types[841],  IFC4X1_types[842],
       IFC4X1_types[843],  IFC4X1_types[844],  IFC4X1_types[845],
       IFC4X1_types[846],  IFC4X1_types[847],  IFC4X1_types[848],
       IFC4X1_types[849],  IFC4X1_types[850],  IFC4X1_types[851],
       IFC4X1_types[852],  IFC4X1_types[853],  IFC4X1_types[854],
       IFC4X1_types[855],  IFC4X1_types[856],  IFC4X1_types[857],
       IFC4X1_types[858],  IFC4X1_types[859],  IFC4X1_types[860],
       IFC4X1_types[861],  IFC4X1_types[862],  IFC4X1_types[863],
       IFC4X1_types[864],  IFC4X1_types[865],  IFC4X1_types[866],
       IFC4X1_types[867],  IFC4X1_types[868],  IFC4X1_types[869],
       IFC4X1_types[870],  IFC4X1_types[871],  IFC4X1_types[872],
       IFC4X1_types[873],  IFC4X1_types[874],  IFC4X1_types[875],
       IFC4X1_types[876],  IFC4X1_types[877],  IFC4X1_types[878],
       IFC4X1_types[879],  IFC4X1_types[880],  IFC4X1_types[881],
       IFC4X1_types[882],  IFC4X1_types[883],  IFC4X1_types[884],
       IFC4X1_types[885],  IFC4X1_types[886],  IFC4X1_types[887],
       IFC4X1_types[888],  IFC4X1_types[889],  IFC4X1_types[890],
       IFC4X1_types[891],  IFC4X1_types[892],  IFC4X1_types[893],
       IFC4X1_types[894],  IFC4X1_types[895],  IFC4X1_types[896],
       IFC4X1_types[897],  IFC4X1_types[898],  IFC4X1_types[899],
       IFC4X1_types[900],  IFC4X1_types[901],  IFC4X1_types[902],
       IFC4X1_types[903],  IFC4X1_types[904],  IFC4X1_types[905],
       IFC4X1_types[906],  IFC4X1_types[907],  IFC4X1_types[908],
       IFC4X1_types[909],  IFC4X1_types[910],  IFC4X1_types[911],
       IFC4X1_types[912],  IFC4X1_types[913],  IFC4X1_types[914],
       IFC4X1_types[915],  IFC4X1_types[916],  IFC4X1_types[917],
       IFC4X1_types[918],  IFC4X1_types[919],  IFC4X1_types[920],
       IFC4X1_types[921],  IFC4X1_types[922],  IFC4X1_types[923],
       IFC4X1_types[924],  IFC4X1_types[925],  IFC4X1_types[926],
       IFC4X1_types[927],  IFC4X1_types[928],  IFC4X1_types[929],
       IFC4X1_types[930],  IFC4X1_types[931],  IFC4X1_types[932],
       IFC4X1_types[933],  IFC4X1_types[934],  IFC4X1_types[935],
       IFC4X1_types[936],  IFC4X1_types[937],  IFC4X1_types[938],
       IFC4X1_types[939],  IFC4X1_types[940],  IFC4X1_types[941],
       IFC4X1_types[942],  IFC4X1_types[943],  IFC4X1_types[944],
       IFC4X1_types[945],  IFC4X1_types[946],  IFC4X1_types[947],
       IFC4X1_types[948],  IFC4X1_types[949],  IFC4X1_types[950],
       IFC4X1_types[951],  IFC4X1_types[952],  IFC4X1_types[953],
       IFC4X1_types[954],  IFC4X1_types[955],  IFC4X1_types[956],
       IFC4X1_types[957],  IFC4X1_types[958],  IFC4X1_types[959],
       IFC4X1_types[960],  IFC4X1_types[961],  IFC4X1_types[962],
       IFC4X1_types[963],  IFC4X1_types[964],  IFC4X1_types[965],
       IFC4X1_types[966],  IFC4X1_types[967],  IFC4X1_types[968],
       IFC4X1_types[969],  IFC4X1_types[970],  IFC4X1_types[971],
       IFC4X1_types[972],  IFC4X1_types[973],  IFC4X1_types[974],
       IFC4X1_types[975],  IFC4X1_types[976],  IFC4X1_types[977],
       IFC4X1_types[978],  IFC4X1_types[979],  IFC4X1_types[980],
       IFC4X1_types[981],  IFC4X1_types[982],  IFC4X1_types[983],
       IFC4X1_types[984],  IFC4X1_types[985],  IFC4X1_types[986],
       IFC4X1_types[987],  IFC4X1_types[988],  IFC4X1_types[989],
       IFC4X1_types[990],  IFC4X1_types[991],  IFC4X1_types[992],
       IFC4X1_types[993],  IFC4X1_types[994],  IFC4X1_types[995],
       IFC4X1_types[996],  IFC4X1_types[997],  IFC4X1_types[998],
       IFC4X1_types[999],  IFC4X1_types[1000], IFC4X1_types[1001],
       IFC4X1_types[1002], IFC4X1_types[1003], IFC4X1_types[1004],
       IFC4X1_types[1005], IFC4X1_types[1006], IFC4X1_types[1007],
       IFC4X1_types[1008], IFC4X1_types[1009], IFC4X1_types[1010],
       IFC4X1_types[1011], IFC4X1_types[1012], IFC4X1_types[1013],
       IFC4X1_types[1014], IFC4X1_types[1015], IFC4X1_types[1016],
       IFC4X1_types[1017], IFC4X1_types[1018], IFC4X1_types[1019],
       IFC4X1_types[1020], IFC4X1_types[1021], IFC4X1_types[1022],
       IFC4X1_types[1023], IFC4X1_types[1024], IFC4X1_types[1025],
       IFC4X1_types[1026], IFC4X1_types[1027], IFC4X1_types[1028],
       IFC4X1_types[1029], IFC4X1_types[1030], IFC4X1_types[1031],
       IFC4X1_types[1032], IFC4X1_types[1033], IFC4X1_types[1034],
       IFC4X1_types[1035], IFC4X1_types[1036], IFC4X1_types[1037],
       IFC4X1_types[1038], IFC4X1_types[1039], IFC4X1_types[1040],
       IFC4X1_types[1041], IFC4X1_types[1042], IFC4X1_types[1043],
       IFC4X1_types[1044], IFC4X1_types[1045], IFC4X1_types[1046],
       IFC4X1_types[1047], IFC4X1_types[1048], IFC4X1_types[1049],
       IFC4X1_types[1050], IFC4X1_types[1051], IFC4X1_types[1052],
       IFC4X1_types[1053], IFC4X1_types[1054], IFC4X1_types[1055],
       IFC4X1_types[1056], IFC4X1_types[1057], IFC4X1_types[1058],
       IFC4X1_types[1059], IFC4X1_types[1060], IFC4X1_types[1061],
       IFC4X1_types[1062], IFC4X1_types[1063], IFC4X1_types[1064],
       IFC4X1_types[1065], IFC4X1_types[1066], IFC4X1_types[1067],
       IFC4X1_types[1068], IFC4X1_types[1069], IFC4X1_types[1070],
       IFC4X1_types[1071], IFC4X1_types[1072], IFC4X1_types[1073],
       IFC4X1_types[1074], IFC4X1_types[1075], IFC4X1_types[1076],
       IFC4X1_types[1077], IFC4X1_types[1078], IFC4X1_types[1079],
       IFC4X1_types[1080], IFC4X1_types[1081], IFC4X1_types[1082],
       IFC4X1_types[1083], IFC4X1_types[1084], IFC4X1_types[1085],
       IFC4X1_types[1086], IFC4X1_types[1087], IFC4X1_types[1088],
       IFC4X1_types[1089], IFC4X1_types[1090], IFC4X1_types[1091],
       IFC4X1_types[1092], IFC4X1_types[1093], IFC4X1_types[1094],
       IFC4X1_types[1095], IFC4X1_types[1096], IFC4X1_types[1097],
       IFC4X1_types[1098], IFC4X1_types[1099], IFC4X1_types[1100],
       IFC4X1_types[1101], IFC4X1_types[1102], IFC4X1_types[1103],
       IFC4X1_types[1104], IFC4X1_types[1105], IFC4X1_types[1106],
       IFC4X1_types[1107], IFC4X1_types[1108], IFC4X1_types[1109],
       IFC4X1_types[1110], IFC4X1_types[1111], IFC4X1_types[1112],
       IFC4X1_types[1113], IFC4X1_types[1114], IFC4X1_types[1115],
       IFC4X1_types[1116], IFC4X1_types[1117], IFC4X1_types[1118],
       IFC4X1_types[1119], IFC4X1_types[1120], IFC4X1_types[1121],
       IFC4X1_types[1122], IFC4X1_types[1123], IFC4X1_types[1124],
       IFC4X1_types[1125], IFC4X1_types[1126], IFC4X1_types[1127],
       IFC4X1_types[1128], IFC4X1_types[1129], IFC4X1_types[1130],
       IFC4X1_types[1131], IFC4X1_types[1132], IFC4X1_types[1133],
       IFC4X1_types[1134], IFC4X1_types[1135], IFC4X1_types[1136],
       IFC4X1_types[1137], IFC4X1_types[1138], IFC4X1_types[1139],
       IFC4X1_types[1140], IFC4X1_types[1141], IFC4X1_types[1142],
       IFC4X1_types[1143], IFC4X1_types[1144], IFC4X1_types[1145],
       IFC4X1_types[1146], IFC4X1_types[1147], IFC4X1_types[1148],
       IFC4X1_types[1149], IFC4X1_types[1150], IFC4X1_types[1151],
       IFC4X1_types[1152], IFC4X1_types[1153], IFC4X1_types[1154],
       IFC4X1_types[1155], IFC4X1_types[1156], IFC4X1_types[1157],
       IFC4X1_types[1158], IFC4X1_types[1159], IFC4X1_types[1160],
       IFC4X1_types[1161], IFC4X1_types[1162], IFC4X1_types[1163],
       IFC4X1_types[1164], IFC4X1_types[1165], IFC4X1_types[1166],
       IFC4X1_types[1167], IFC4X1_types[1168], IFC4X1_types[1169],
       IFC4X1_types[1170], IFC4X1_types[1171], IFC4X1_types[1172],
       IFC4X1_types[1173], IFC4X1_types[1174], IFC4X1_types[1175],
       IFC4X1_types[1176], IFC4X1_types[1177], IFC4X1_types[1178],
       IFC4X1_types[1179], IFC4X1_types[1180], IFC4X1_types[1181],
       IFC4X1_types[1182], IFC4X1_types[1183], IFC4X1_types[1184],
       IFC4X1_types[1185], IFC4X1_types[1186], IFC4X1_types[1187],
       IFC4X1_types[1188], IFC4X1_types[1189], IFC4X1_types[1190],
       IFC4X1_types[1191], IFC4X1_types[1192], IFC4X1_types[1193],
       IFC4X1_types[1194], IFC4X1_types[1195], IFC4X1_types[1196],
       IFC4X1_types[1197], IFC4X1_types[1198], IFC4X1_types[1199],
       IFC4X1_types[1200]},
      new IFC4X1_instance_factory());
}
static std::unique_ptr<schema_definition> schema;

void Ifc4x1::clear_schema() { schema.reset(); }

const schema_definition &Ifc4x1::get_schema() {
  if (!schema) {
    schema.reset(IFC4X1_populate_schema());
  }
  return *schema;
}
