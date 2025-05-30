#include <ifcparse/Ifc4x2.h>
#include <ifcparse/IfcSchema.h>
#include <string>

using namespace std::string_literals;
using namespace IfcParse;

declaration *IFC4X2_types[1223] = {nullptr};

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
    "GIRDER_SEGMENT"s,
    "DIAPHRAGM"s,
    "PIERCAP"s,
    "HATSTONE"s,
    "CORNICE"s,
    "EDGEBEAM"s,
    "IfcBearingTypeDisplacementEnum"s,
    "FIXED_MOVEMENT"s,
    "GUIDED_LONGITUDINAL"s,
    "GUIDED_TRANSVERSAL"s,
    "FREE_MOVEMENT"s,
    "IfcBearingTypeEnum"s,
    "CYLINDRICAL"s,
    "SPHERICAL"s,
    "ELASTOMERIC"s,
    "POT"s,
    "GUIDE"s,
    "ROCKER"s,
    "ROLLER"s,
    "DISK"s,
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
    "IfcBridgePartTypeEnum"s,
    "ABUTMENT"s,
    "DECK"s,
    "DECK_SEGMENT"s,
    "FOUNDATION"s,
    "PIER"s,
    "PIER_SEGMENT"s,
    "PYLON"s,
    "SUBSTRUCTURE"s,
    "SUPERSTRUCTURE"s,
    "SURFACESTRUCTURE"s,
    "IfcBridgeTypeEnum"s,
    "ARCHED"s,
    "CABLE_STAYED"s,
    "CANTILEVER"s,
    "CULVERT"s,
    "FRAMEWORK"s,
    "GIRDER"s,
    "SUSPENSION"s,
    "TRUSS"s,
    "IfcBuildingElementPartTypeEnum"s,
    "INSULATION"s,
    "PRECASTPANEL"s,
    "APRON"s,
    "IfcBuildingElementProxyTypeEnum"s,
    "COMPLEX"s,
    "ELEMENT"s,
    "PARTIAL"s,
    "PROVISIONFORVOID"s,
    "PROVISIONFORSPACE"s,
    "IfcBuildingSystemTypeEnum"s,
    "FENESTRATION"s,
    "LOADBEARING"s,
    "OUTERSHELL"s,
    "SHADING"s,
    "REINFORCING"s,
    "PRESTRESSING"s,
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
    "IfcCaissonFoundationTypeEnum"s,
    "WELL"s,
    "CAISSON"s,
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
    "PIERSTEM"s,
    "PIERSTEM_SEGMENT"s,
    "STANDCOLUMN"s,
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
    "COPING"s,
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
    "EXPANSION_JOINT_DEVICE"s,
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
    "REINFORCEMENT_UNIT"s,
    "RIGID_FRAME"s,
    "SLAB_FIELD"s,
    "CROSS_BRACING"s,
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
    "SOIL_BORING_POINT"s,
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
    "COUPLER"s,
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
    "STIFFENING_RIB"s,
    "ARCH_SEGMENT"s,
    "SUSPENSION_CABLE"s,
    "SUSPENDER"s,
    "STAY_CABLE"s,
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
    "GUTTER"s,
    "SPOOL"s,
    "IfcPlanarForceMeasure"s,
    "IfcPlaneAngleMeasure"s,
    "IfcPlateTypeEnum"s,
    "CURTAIN_PANEL"s,
    "SHEET"s,
    "FLANGE_PLATE"s,
    "WEB_PLATE"s,
    "STIFFENER_PLATE"s,
    "GUSSET_PLATE"s,
    "COVER_PLATE"s,
    "SPLICE_PLATE"s,
    "BASE_PLATE"s,
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
    "BLISTER"s,
    "DEVIATOR"s,
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
    "SPACEBAR"s,
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
    "APPROACH_SLAB"s,
    "WEARING"s,
    "SIDEWALK"s,
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
    "DEFECT"s,
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
    "FIXED_END"s,
    "TENSIONING_END"s,
    "IfcTendonConduitTypeEnum"s,
    "GROUTING_DUCT"s,
    "TRUMPET"s,
    "DIABOLO"s,
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
    "IfcVibrationDamperTypeEnum"s,
    "BENDING_YIELD"s,
    "SHEAR_YIELD"s,
    "AXIAL_YIELD"s,
    "VISCOUS"s,
    "RUBBER"s,
    "IfcVibrationIsolatorTypeEnum"s,
    "COMPRESSION"s,
    "SPRING"s,
    "BASE"s,
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
    "RETAININGWALL"s,
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
    "IfcRelPositions"s,
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
    "IfcBuildingElementType"s,
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
    "IfcDeepFoundationType"s,
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
    "IfcFacility"s,
    "IfcFacilityPart"s,
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
    "IfcTendonConduit"s,
    "IfcTendonConduitType"s,
    "IfcTendonType"s,
    "IfcTransformerType"s,
    "IfcTransitionCurveSegment2D"s,
    "IfcTransportElement"s,
    "IfcTrimmedCurve"s,
    "IfcTubeBundleType"s,
    "IfcUnitaryEquipmentType"s,
    "IfcValveType"s,
    "IfcVibrationDamper"s,
    "IfcVibrationDamperType"s,
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
    "IfcBearingType"s,
    "IfcBoilerType"s,
    "IfcBoundaryCurve"s,
    "IfcBridge"s,
    "IfcBridgePart"s,
    "IfcBuilding"s,
    "IfcBuildingElement"s,
    "IfcBuildingElementPart"s,
    "IfcBuildingElementPartType"s,
    "IfcBuildingElementProxy"s,
    "IfcBuildingElementProxyType"s,
    "IfcBuildingStorey"s,
    "IfcBuildingSystem"s,
    "IfcBurnerType"s,
    "IfcCableCarrierFittingType"s,
    "IfcCableCarrierSegmentType"s,
    "IfcCableFittingType"s,
    "IfcCableSegmentType"s,
    "IfcCaissonFoundationType"s,
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
    "IfcDeepFoundation"s,
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
    "IfcBearing"s,
    "IfcBoiler"s,
    "IfcBurner"s,
    "IfcCableCarrierFitting"s,
    "IfcCableCarrierSegment"s,
    "IfcCableFitting"s,
    "IfcCableSegment"s,
    "IfcCaissonFoundation"s,
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
    "PlacementMeasuredAlong"s,
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
    "PlacementRelTo"s,
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
    "RelatingPositioningElement"s,
    "RelatedProducts"s,
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
    "PositioningElement"s,
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
    "HasFillings"s,
    "IsRelatedBy"s,
    "Engages"s,
    "EngagedIn"s,
    "PartOfComplex"s,
    "ContainedIn"s,
    "Positions"s,
    "IsPredecessorTo"s,
    "IsSuccessorFrom"s,
    "OperatesOn"s,
    "ReferencedBy"s,
    "PositionedRelativeTo"s,
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
    "IFC4X2"s};

class IFC4X2_instance_factory : public IfcParse::instance_factory {
  virtual IfcUtil::IfcBaseClass *
  operator()(const IfcParse::declaration *decl,
             IfcEntityInstanceData &&data) const {
    switch (decl->index_in_schema()) {
    case 0:
      return new ::Ifc4x2::IfcAbsorbedDoseMeasure(std::move(data));
    case 1:
      return new ::Ifc4x2::IfcAccelerationMeasure(std::move(data));
    case 2:
      return new ::Ifc4x2::IfcActionRequest(std::move(data));
    case 3:
      return new ::Ifc4x2::IfcActionRequestTypeEnum(std::move(data));
    case 4:
      return new ::Ifc4x2::IfcActionSourceTypeEnum(std::move(data));
    case 5:
      return new ::Ifc4x2::IfcActionTypeEnum(std::move(data));
    case 6:
      return new ::Ifc4x2::IfcActor(std::move(data));
    case 7:
      return new ::Ifc4x2::IfcActorRole(std::move(data));
    case 9:
      return new ::Ifc4x2::IfcActuator(std::move(data));
    case 10:
      return new ::Ifc4x2::IfcActuatorType(std::move(data));
    case 11:
      return new ::Ifc4x2::IfcActuatorTypeEnum(std::move(data));
    case 12:
      return new ::Ifc4x2::IfcAddress(std::move(data));
    case 13:
      return new ::Ifc4x2::IfcAddressTypeEnum(std::move(data));
    case 14:
      return new ::Ifc4x2::IfcAdvancedBrep(std::move(data));
    case 15:
      return new ::Ifc4x2::IfcAdvancedBrepWithVoids(std::move(data));
    case 16:
      return new ::Ifc4x2::IfcAdvancedFace(std::move(data));
    case 17:
      return new ::Ifc4x2::IfcAirTerminal(std::move(data));
    case 18:
      return new ::Ifc4x2::IfcAirTerminalBox(std::move(data));
    case 19:
      return new ::Ifc4x2::IfcAirTerminalBoxType(std::move(data));
    case 20:
      return new ::Ifc4x2::IfcAirTerminalBoxTypeEnum(std::move(data));
    case 21:
      return new ::Ifc4x2::IfcAirTerminalType(std::move(data));
    case 22:
      return new ::Ifc4x2::IfcAirTerminalTypeEnum(std::move(data));
    case 23:
      return new ::Ifc4x2::IfcAirToAirHeatRecovery(std::move(data));
    case 24:
      return new ::Ifc4x2::IfcAirToAirHeatRecoveryType(std::move(data));
    case 25:
      return new ::Ifc4x2::IfcAirToAirHeatRecoveryTypeEnum(std::move(data));
    case 26:
      return new ::Ifc4x2::IfcAlarm(std::move(data));
    case 27:
      return new ::Ifc4x2::IfcAlarmType(std::move(data));
    case 28:
      return new ::Ifc4x2::IfcAlarmTypeEnum(std::move(data));
    case 29:
      return new ::Ifc4x2::IfcAlignment(std::move(data));
    case 30:
      return new ::Ifc4x2::IfcAlignment2DHorizontal(std::move(data));
    case 31:
      return new ::Ifc4x2::IfcAlignment2DHorizontalSegment(std::move(data));
    case 32:
      return new ::Ifc4x2::IfcAlignment2DSegment(std::move(data));
    case 33:
      return new ::Ifc4x2::IfcAlignment2DVerSegCircularArc(std::move(data));
    case 34:
      return new ::Ifc4x2::IfcAlignment2DVerSegLine(std::move(data));
    case 35:
      return new ::Ifc4x2::IfcAlignment2DVerSegParabolicArc(std::move(data));
    case 36:
      return new ::Ifc4x2::IfcAlignment2DVertical(std::move(data));
    case 37:
      return new ::Ifc4x2::IfcAlignment2DVerticalSegment(std::move(data));
    case 38:
      return new ::Ifc4x2::IfcAlignmentCurve(std::move(data));
    case 39:
      return new ::Ifc4x2::IfcAlignmentTypeEnum(std::move(data));
    case 40:
      return new ::Ifc4x2::IfcAmountOfSubstanceMeasure(std::move(data));
    case 41:
      return new ::Ifc4x2::IfcAnalysisModelTypeEnum(std::move(data));
    case 42:
      return new ::Ifc4x2::IfcAnalysisTheoryTypeEnum(std::move(data));
    case 43:
      return new ::Ifc4x2::IfcAngularVelocityMeasure(std::move(data));
    case 44:
      return new ::Ifc4x2::IfcAnnotation(std::move(data));
    case 45:
      return new ::Ifc4x2::IfcAnnotationFillArea(std::move(data));
    case 46:
      return new ::Ifc4x2::IfcApplication(std::move(data));
    case 47:
      return new ::Ifc4x2::IfcAppliedValue(std::move(data));
    case 49:
      return new ::Ifc4x2::IfcApproval(std::move(data));
    case 50:
      return new ::Ifc4x2::IfcApprovalRelationship(std::move(data));
    case 51:
      return new ::Ifc4x2::IfcArbitraryClosedProfileDef(std::move(data));
    case 52:
      return new ::Ifc4x2::IfcArbitraryOpenProfileDef(std::move(data));
    case 53:
      return new ::Ifc4x2::IfcArbitraryProfileDefWithVoids(std::move(data));
    case 54:
      return new ::Ifc4x2::IfcArcIndex(std::move(data));
    case 55:
      return new ::Ifc4x2::IfcAreaDensityMeasure(std::move(data));
    case 56:
      return new ::Ifc4x2::IfcAreaMeasure(std::move(data));
    case 57:
      return new ::Ifc4x2::IfcArithmeticOperatorEnum(std::move(data));
    case 58:
      return new ::Ifc4x2::IfcAssemblyPlaceEnum(std::move(data));
    case 59:
      return new ::Ifc4x2::IfcAsset(std::move(data));
    case 60:
      return new ::Ifc4x2::IfcAsymmetricIShapeProfileDef(std::move(data));
    case 61:
      return new ::Ifc4x2::IfcAudioVisualAppliance(std::move(data));
    case 62:
      return new ::Ifc4x2::IfcAudioVisualApplianceType(std::move(data));
    case 63:
      return new ::Ifc4x2::IfcAudioVisualApplianceTypeEnum(std::move(data));
    case 64:
      return new ::Ifc4x2::IfcAxis1Placement(std::move(data));
    case 66:
      return new ::Ifc4x2::IfcAxis2Placement2D(std::move(data));
    case 67:
      return new ::Ifc4x2::IfcAxis2Placement3D(std::move(data));
    case 68:
      return new ::Ifc4x2::IfcBeam(std::move(data));
    case 69:
      return new ::Ifc4x2::IfcBeamStandardCase(std::move(data));
    case 70:
      return new ::Ifc4x2::IfcBeamType(std::move(data));
    case 71:
      return new ::Ifc4x2::IfcBeamTypeEnum(std::move(data));
    case 72:
      return new ::Ifc4x2::IfcBearing(std::move(data));
    case 73:
      return new ::Ifc4x2::IfcBearingType(std::move(data));
    case 74:
      return new ::Ifc4x2::IfcBearingTypeDisplacementEnum(std::move(data));
    case 75:
      return new ::Ifc4x2::IfcBearingTypeEnum(std::move(data));
    case 76:
      return new ::Ifc4x2::IfcBenchmarkEnum(std::move(data));
    case 78:
      return new ::Ifc4x2::IfcBinary(std::move(data));
    case 79:
      return new ::Ifc4x2::IfcBlobTexture(std::move(data));
    case 80:
      return new ::Ifc4x2::IfcBlock(std::move(data));
    case 81:
      return new ::Ifc4x2::IfcBoiler(std::move(data));
    case 82:
      return new ::Ifc4x2::IfcBoilerType(std::move(data));
    case 83:
      return new ::Ifc4x2::IfcBoilerTypeEnum(std::move(data));
    case 84:
      return new ::Ifc4x2::IfcBoolean(std::move(data));
    case 85:
      return new ::Ifc4x2::IfcBooleanClippingResult(std::move(data));
    case 87:
      return new ::Ifc4x2::IfcBooleanOperator(std::move(data));
    case 88:
      return new ::Ifc4x2::IfcBooleanResult(std::move(data));
    case 89:
      return new ::Ifc4x2::IfcBoundaryCondition(std::move(data));
    case 90:
      return new ::Ifc4x2::IfcBoundaryCurve(std::move(data));
    case 91:
      return new ::Ifc4x2::IfcBoundaryEdgeCondition(std::move(data));
    case 92:
      return new ::Ifc4x2::IfcBoundaryFaceCondition(std::move(data));
    case 93:
      return new ::Ifc4x2::IfcBoundaryNodeCondition(std::move(data));
    case 94:
      return new ::Ifc4x2::IfcBoundaryNodeConditionWarping(std::move(data));
    case 95:
      return new ::Ifc4x2::IfcBoundedCurve(std::move(data));
    case 96:
      return new ::Ifc4x2::IfcBoundedSurface(std::move(data));
    case 97:
      return new ::Ifc4x2::IfcBoundingBox(std::move(data));
    case 98:
      return new ::Ifc4x2::IfcBoxAlignment(std::move(data));
    case 99:
      return new ::Ifc4x2::IfcBoxedHalfSpace(std::move(data));
    case 100:
      return new ::Ifc4x2::IfcBridge(std::move(data));
    case 101:
      return new ::Ifc4x2::IfcBridgePart(std::move(data));
    case 102:
      return new ::Ifc4x2::IfcBridgePartTypeEnum(std::move(data));
    case 103:
      return new ::Ifc4x2::IfcBridgeTypeEnum(std::move(data));
    case 104:
      return new ::Ifc4x2::IfcBSplineCurve(std::move(data));
    case 105:
      return new ::Ifc4x2::IfcBSplineCurveForm(std::move(data));
    case 106:
      return new ::Ifc4x2::IfcBSplineCurveWithKnots(std::move(data));
    case 107:
      return new ::Ifc4x2::IfcBSplineSurface(std::move(data));
    case 108:
      return new ::Ifc4x2::IfcBSplineSurfaceForm(std::move(data));
    case 109:
      return new ::Ifc4x2::IfcBSplineSurfaceWithKnots(std::move(data));
    case 110:
      return new ::Ifc4x2::IfcBuilding(std::move(data));
    case 111:
      return new ::Ifc4x2::IfcBuildingElement(std::move(data));
    case 112:
      return new ::Ifc4x2::IfcBuildingElementPart(std::move(data));
    case 113:
      return new ::Ifc4x2::IfcBuildingElementPartType(std::move(data));
    case 114:
      return new ::Ifc4x2::IfcBuildingElementPartTypeEnum(std::move(data));
    case 115:
      return new ::Ifc4x2::IfcBuildingElementProxy(std::move(data));
    case 116:
      return new ::Ifc4x2::IfcBuildingElementProxyType(std::move(data));
    case 117:
      return new ::Ifc4x2::IfcBuildingElementProxyTypeEnum(std::move(data));
    case 118:
      return new ::Ifc4x2::IfcBuildingElementType(std::move(data));
    case 119:
      return new ::Ifc4x2::IfcBuildingStorey(std::move(data));
    case 120:
      return new ::Ifc4x2::IfcBuildingSystem(std::move(data));
    case 121:
      return new ::Ifc4x2::IfcBuildingSystemTypeEnum(std::move(data));
    case 122:
      return new ::Ifc4x2::IfcBurner(std::move(data));
    case 123:
      return new ::Ifc4x2::IfcBurnerType(std::move(data));
    case 124:
      return new ::Ifc4x2::IfcBurnerTypeEnum(std::move(data));
    case 125:
      return new ::Ifc4x2::IfcCableCarrierFitting(std::move(data));
    case 126:
      return new ::Ifc4x2::IfcCableCarrierFittingType(std::move(data));
    case 127:
      return new ::Ifc4x2::IfcCableCarrierFittingTypeEnum(std::move(data));
    case 128:
      return new ::Ifc4x2::IfcCableCarrierSegment(std::move(data));
    case 129:
      return new ::Ifc4x2::IfcCableCarrierSegmentType(std::move(data));
    case 130:
      return new ::Ifc4x2::IfcCableCarrierSegmentTypeEnum(std::move(data));
    case 131:
      return new ::Ifc4x2::IfcCableFitting(std::move(data));
    case 132:
      return new ::Ifc4x2::IfcCableFittingType(std::move(data));
    case 133:
      return new ::Ifc4x2::IfcCableFittingTypeEnum(std::move(data));
    case 134:
      return new ::Ifc4x2::IfcCableSegment(std::move(data));
    case 135:
      return new ::Ifc4x2::IfcCableSegmentType(std::move(data));
    case 136:
      return new ::Ifc4x2::IfcCableSegmentTypeEnum(std::move(data));
    case 137:
      return new ::Ifc4x2::IfcCaissonFoundation(std::move(data));
    case 138:
      return new ::Ifc4x2::IfcCaissonFoundationType(std::move(data));
    case 139:
      return new ::Ifc4x2::IfcCaissonFoundationTypeEnum(std::move(data));
    case 140:
      return new ::Ifc4x2::IfcCardinalPointReference(std::move(data));
    case 141:
      return new ::Ifc4x2::IfcCartesianPoint(std::move(data));
    case 142:
      return new ::Ifc4x2::IfcCartesianPointList(std::move(data));
    case 143:
      return new ::Ifc4x2::IfcCartesianPointList2D(std::move(data));
    case 144:
      return new ::Ifc4x2::IfcCartesianPointList3D(std::move(data));
    case 145:
      return new ::Ifc4x2::IfcCartesianTransformationOperator(std::move(data));
    case 146:
      return new ::Ifc4x2::IfcCartesianTransformationOperator2D(
          std::move(data));
    case 147:
      return new ::Ifc4x2::IfcCartesianTransformationOperator2DnonUniform(
          std::move(data));
    case 148:
      return new ::Ifc4x2::IfcCartesianTransformationOperator3D(
          std::move(data));
    case 149:
      return new ::Ifc4x2::IfcCartesianTransformationOperator3DnonUniform(
          std::move(data));
    case 150:
      return new ::Ifc4x2::IfcCenterLineProfileDef(std::move(data));
    case 151:
      return new ::Ifc4x2::IfcChangeActionEnum(std::move(data));
    case 152:
      return new ::Ifc4x2::IfcChiller(std::move(data));
    case 153:
      return new ::Ifc4x2::IfcChillerType(std::move(data));
    case 154:
      return new ::Ifc4x2::IfcChillerTypeEnum(std::move(data));
    case 155:
      return new ::Ifc4x2::IfcChimney(std::move(data));
    case 156:
      return new ::Ifc4x2::IfcChimneyType(std::move(data));
    case 157:
      return new ::Ifc4x2::IfcChimneyTypeEnum(std::move(data));
    case 158:
      return new ::Ifc4x2::IfcCircle(std::move(data));
    case 159:
      return new ::Ifc4x2::IfcCircleHollowProfileDef(std::move(data));
    case 160:
      return new ::Ifc4x2::IfcCircleProfileDef(std::move(data));
    case 161:
      return new ::Ifc4x2::IfcCircularArcSegment2D(std::move(data));
    case 162:
      return new ::Ifc4x2::IfcCivilElement(std::move(data));
    case 163:
      return new ::Ifc4x2::IfcCivilElementType(std::move(data));
    case 164:
      return new ::Ifc4x2::IfcClassification(std::move(data));
    case 165:
      return new ::Ifc4x2::IfcClassificationReference(std::move(data));
    case 168:
      return new ::Ifc4x2::IfcClosedShell(std::move(data));
    case 169:
      return new ::Ifc4x2::IfcCoil(std::move(data));
    case 170:
      return new ::Ifc4x2::IfcCoilType(std::move(data));
    case 171:
      return new ::Ifc4x2::IfcCoilTypeEnum(std::move(data));
    case 174:
      return new ::Ifc4x2::IfcColourRgb(std::move(data));
    case 175:
      return new ::Ifc4x2::IfcColourRgbList(std::move(data));
    case 176:
      return new ::Ifc4x2::IfcColourSpecification(std::move(data));
    case 177:
      return new ::Ifc4x2::IfcColumn(std::move(data));
    case 178:
      return new ::Ifc4x2::IfcColumnStandardCase(std::move(data));
    case 179:
      return new ::Ifc4x2::IfcColumnType(std::move(data));
    case 180:
      return new ::Ifc4x2::IfcColumnTypeEnum(std::move(data));
    case 181:
      return new ::Ifc4x2::IfcCommunicationsAppliance(std::move(data));
    case 182:
      return new ::Ifc4x2::IfcCommunicationsApplianceType(std::move(data));
    case 183:
      return new ::Ifc4x2::IfcCommunicationsApplianceTypeEnum(std::move(data));
    case 184:
      return new ::Ifc4x2::IfcComplexNumber(std::move(data));
    case 185:
      return new ::Ifc4x2::IfcComplexProperty(std::move(data));
    case 186:
      return new ::Ifc4x2::IfcComplexPropertyTemplate(std::move(data));
    case 187:
      return new ::Ifc4x2::IfcComplexPropertyTemplateTypeEnum(std::move(data));
    case 188:
      return new ::Ifc4x2::IfcCompositeCurve(std::move(data));
    case 189:
      return new ::Ifc4x2::IfcCompositeCurveOnSurface(std::move(data));
    case 190:
      return new ::Ifc4x2::IfcCompositeCurveSegment(std::move(data));
    case 191:
      return new ::Ifc4x2::IfcCompositeProfileDef(std::move(data));
    case 192:
      return new ::Ifc4x2::IfcCompoundPlaneAngleMeasure(std::move(data));
    case 193:
      return new ::Ifc4x2::IfcCompressor(std::move(data));
    case 194:
      return new ::Ifc4x2::IfcCompressorType(std::move(data));
    case 195:
      return new ::Ifc4x2::IfcCompressorTypeEnum(std::move(data));
    case 196:
      return new ::Ifc4x2::IfcCondenser(std::move(data));
    case 197:
      return new ::Ifc4x2::IfcCondenserType(std::move(data));
    case 198:
      return new ::Ifc4x2::IfcCondenserTypeEnum(std::move(data));
    case 199:
      return new ::Ifc4x2::IfcConic(std::move(data));
    case 200:
      return new ::Ifc4x2::IfcConnectedFaceSet(std::move(data));
    case 201:
      return new ::Ifc4x2::IfcConnectionCurveGeometry(std::move(data));
    case 202:
      return new ::Ifc4x2::IfcConnectionGeometry(std::move(data));
    case 203:
      return new ::Ifc4x2::IfcConnectionPointEccentricity(std::move(data));
    case 204:
      return new ::Ifc4x2::IfcConnectionPointGeometry(std::move(data));
    case 205:
      return new ::Ifc4x2::IfcConnectionSurfaceGeometry(std::move(data));
    case 206:
      return new ::Ifc4x2::IfcConnectionTypeEnum(std::move(data));
    case 207:
      return new ::Ifc4x2::IfcConnectionVolumeGeometry(std::move(data));
    case 208:
      return new ::Ifc4x2::IfcConstraint(std::move(data));
    case 209:
      return new ::Ifc4x2::IfcConstraintEnum(std::move(data));
    case 210:
      return new ::Ifc4x2::IfcConstructionEquipmentResource(std::move(data));
    case 211:
      return new ::Ifc4x2::IfcConstructionEquipmentResourceType(
          std::move(data));
    case 212:
      return new ::Ifc4x2::IfcConstructionEquipmentResourceTypeEnum(
          std::move(data));
    case 213:
      return new ::Ifc4x2::IfcConstructionMaterialResource(std::move(data));
    case 214:
      return new ::Ifc4x2::IfcConstructionMaterialResourceType(std::move(data));
    case 215:
      return new ::Ifc4x2::IfcConstructionMaterialResourceTypeEnum(
          std::move(data));
    case 216:
      return new ::Ifc4x2::IfcConstructionProductResource(std::move(data));
    case 217:
      return new ::Ifc4x2::IfcConstructionProductResourceType(std::move(data));
    case 218:
      return new ::Ifc4x2::IfcConstructionProductResourceTypeEnum(
          std::move(data));
    case 219:
      return new ::Ifc4x2::IfcConstructionResource(std::move(data));
    case 220:
      return new ::Ifc4x2::IfcConstructionResourceType(std::move(data));
    case 221:
      return new ::Ifc4x2::IfcContext(std::move(data));
    case 222:
      return new ::Ifc4x2::IfcContextDependentMeasure(std::move(data));
    case 223:
      return new ::Ifc4x2::IfcContextDependentUnit(std::move(data));
    case 224:
      return new ::Ifc4x2::IfcControl(std::move(data));
    case 225:
      return new ::Ifc4x2::IfcController(std::move(data));
    case 226:
      return new ::Ifc4x2::IfcControllerType(std::move(data));
    case 227:
      return new ::Ifc4x2::IfcControllerTypeEnum(std::move(data));
    case 228:
      return new ::Ifc4x2::IfcConversionBasedUnit(std::move(data));
    case 229:
      return new ::Ifc4x2::IfcConversionBasedUnitWithOffset(std::move(data));
    case 230:
      return new ::Ifc4x2::IfcCooledBeam(std::move(data));
    case 231:
      return new ::Ifc4x2::IfcCooledBeamType(std::move(data));
    case 232:
      return new ::Ifc4x2::IfcCooledBeamTypeEnum(std::move(data));
    case 233:
      return new ::Ifc4x2::IfcCoolingTower(std::move(data));
    case 234:
      return new ::Ifc4x2::IfcCoolingTowerType(std::move(data));
    case 235:
      return new ::Ifc4x2::IfcCoolingTowerTypeEnum(std::move(data));
    case 236:
      return new ::Ifc4x2::IfcCoordinateOperation(std::move(data));
    case 237:
      return new ::Ifc4x2::IfcCoordinateReferenceSystem(std::move(data));
    case 239:
      return new ::Ifc4x2::IfcCostItem(std::move(data));
    case 240:
      return new ::Ifc4x2::IfcCostItemTypeEnum(std::move(data));
    case 241:
      return new ::Ifc4x2::IfcCostSchedule(std::move(data));
    case 242:
      return new ::Ifc4x2::IfcCostScheduleTypeEnum(std::move(data));
    case 243:
      return new ::Ifc4x2::IfcCostValue(std::move(data));
    case 244:
      return new ::Ifc4x2::IfcCountMeasure(std::move(data));
    case 245:
      return new ::Ifc4x2::IfcCovering(std::move(data));
    case 246:
      return new ::Ifc4x2::IfcCoveringType(std::move(data));
    case 247:
      return new ::Ifc4x2::IfcCoveringTypeEnum(std::move(data));
    case 248:
      return new ::Ifc4x2::IfcCrewResource(std::move(data));
    case 249:
      return new ::Ifc4x2::IfcCrewResourceType(std::move(data));
    case 250:
      return new ::Ifc4x2::IfcCrewResourceTypeEnum(std::move(data));
    case 251:
      return new ::Ifc4x2::IfcCsgPrimitive3D(std::move(data));
    case 253:
      return new ::Ifc4x2::IfcCsgSolid(std::move(data));
    case 254:
      return new ::Ifc4x2::IfcCShapeProfileDef(std::move(data));
    case 255:
      return new ::Ifc4x2::IfcCurrencyRelationship(std::move(data));
    case 256:
      return new ::Ifc4x2::IfcCurtainWall(std::move(data));
    case 257:
      return new ::Ifc4x2::IfcCurtainWallType(std::move(data));
    case 258:
      return new ::Ifc4x2::IfcCurtainWallTypeEnum(std::move(data));
    case 259:
      return new ::Ifc4x2::IfcCurvatureMeasure(std::move(data));
    case 260:
      return new ::Ifc4x2::IfcCurve(std::move(data));
    case 261:
      return new ::Ifc4x2::IfcCurveBoundedPlane(std::move(data));
    case 262:
      return new ::Ifc4x2::IfcCurveBoundedSurface(std::move(data));
    case 264:
      return new ::Ifc4x2::IfcCurveInterpolationEnum(std::move(data));
    case 267:
      return new ::Ifc4x2::IfcCurveSegment2D(std::move(data));
    case 268:
      return new ::Ifc4x2::IfcCurveStyle(std::move(data));
    case 269:
      return new ::Ifc4x2::IfcCurveStyleFont(std::move(data));
    case 270:
      return new ::Ifc4x2::IfcCurveStyleFontAndScaling(std::move(data));
    case 271:
      return new ::Ifc4x2::IfcCurveStyleFontPattern(std::move(data));
    case 273:
      return new ::Ifc4x2::IfcCylindricalSurface(std::move(data));
    case 274:
      return new ::Ifc4x2::IfcDamper(std::move(data));
    case 275:
      return new ::Ifc4x2::IfcDamperType(std::move(data));
    case 276:
      return new ::Ifc4x2::IfcDamperTypeEnum(std::move(data));
    case 277:
      return new ::Ifc4x2::IfcDataOriginEnum(std::move(data));
    case 278:
      return new ::Ifc4x2::IfcDate(std::move(data));
    case 279:
      return new ::Ifc4x2::IfcDateTime(std::move(data));
    case 280:
      return new ::Ifc4x2::IfcDayInMonthNumber(std::move(data));
    case 281:
      return new ::Ifc4x2::IfcDayInWeekNumber(std::move(data));
    case 282:
      return new ::Ifc4x2::IfcDeepFoundation(std::move(data));
    case 283:
      return new ::Ifc4x2::IfcDeepFoundationType(std::move(data));
    case 286:
      return new ::Ifc4x2::IfcDerivedProfileDef(std::move(data));
    case 287:
      return new ::Ifc4x2::IfcDerivedUnit(std::move(data));
    case 288:
      return new ::Ifc4x2::IfcDerivedUnitElement(std::move(data));
    case 289:
      return new ::Ifc4x2::IfcDerivedUnitEnum(std::move(data));
    case 290:
      return new ::Ifc4x2::IfcDescriptiveMeasure(std::move(data));
    case 291:
      return new ::Ifc4x2::IfcDimensionalExponents(std::move(data));
    case 292:
      return new ::Ifc4x2::IfcDimensionCount(std::move(data));
    case 293:
      return new ::Ifc4x2::IfcDirection(std::move(data));
    case 294:
      return new ::Ifc4x2::IfcDirectionSenseEnum(std::move(data));
    case 295:
      return new ::Ifc4x2::IfcDiscreteAccessory(std::move(data));
    case 296:
      return new ::Ifc4x2::IfcDiscreteAccessoryType(std::move(data));
    case 297:
      return new ::Ifc4x2::IfcDiscreteAccessoryTypeEnum(std::move(data));
    case 298:
      return new ::Ifc4x2::IfcDistanceExpression(std::move(data));
    case 299:
      return new ::Ifc4x2::IfcDistributionChamberElement(std::move(data));
    case 300:
      return new ::Ifc4x2::IfcDistributionChamberElementType(std::move(data));
    case 301:
      return new ::Ifc4x2::IfcDistributionChamberElementTypeEnum(
          std::move(data));
    case 302:
      return new ::Ifc4x2::IfcDistributionCircuit(std::move(data));
    case 303:
      return new ::Ifc4x2::IfcDistributionControlElement(std::move(data));
    case 304:
      return new ::Ifc4x2::IfcDistributionControlElementType(std::move(data));
    case 305:
      return new ::Ifc4x2::IfcDistributionElement(std::move(data));
    case 306:
      return new ::Ifc4x2::IfcDistributionElementType(std::move(data));
    case 307:
      return new ::Ifc4x2::IfcDistributionFlowElement(std::move(data));
    case 308:
      return new ::Ifc4x2::IfcDistributionFlowElementType(std::move(data));
    case 309:
      return new ::Ifc4x2::IfcDistributionPort(std::move(data));
    case 310:
      return new ::Ifc4x2::IfcDistributionPortTypeEnum(std::move(data));
    case 311:
      return new ::Ifc4x2::IfcDistributionSystem(std::move(data));
    case 312:
      return new ::Ifc4x2::IfcDistributionSystemEnum(std::move(data));
    case 313:
      return new ::Ifc4x2::IfcDocumentConfidentialityEnum(std::move(data));
    case 314:
      return new ::Ifc4x2::IfcDocumentInformation(std::move(data));
    case 315:
      return new ::Ifc4x2::IfcDocumentInformationRelationship(std::move(data));
    case 316:
      return new ::Ifc4x2::IfcDocumentReference(std::move(data));
    case 318:
      return new ::Ifc4x2::IfcDocumentStatusEnum(std::move(data));
    case 319:
      return new ::Ifc4x2::IfcDoor(std::move(data));
    case 320:
      return new ::Ifc4x2::IfcDoorLiningProperties(std::move(data));
    case 321:
      return new ::Ifc4x2::IfcDoorPanelOperationEnum(std::move(data));
    case 322:
      return new ::Ifc4x2::IfcDoorPanelPositionEnum(std::move(data));
    case 323:
      return new ::Ifc4x2::IfcDoorPanelProperties(std::move(data));
    case 324:
      return new ::Ifc4x2::IfcDoorStandardCase(std::move(data));
    case 325:
      return new ::Ifc4x2::IfcDoorStyle(std::move(data));
    case 326:
      return new ::Ifc4x2::IfcDoorStyleConstructionEnum(std::move(data));
    case 327:
      return new ::Ifc4x2::IfcDoorStyleOperationEnum(std::move(data));
    case 328:
      return new ::Ifc4x2::IfcDoorType(std::move(data));
    case 329:
      return new ::Ifc4x2::IfcDoorTypeEnum(std::move(data));
    case 330:
      return new ::Ifc4x2::IfcDoorTypeOperationEnum(std::move(data));
    case 331:
      return new ::Ifc4x2::IfcDoseEquivalentMeasure(std::move(data));
    case 332:
      return new ::Ifc4x2::IfcDraughtingPreDefinedColour(std::move(data));
    case 333:
      return new ::Ifc4x2::IfcDraughtingPreDefinedCurveFont(std::move(data));
    case 334:
      return new ::Ifc4x2::IfcDuctFitting(std::move(data));
    case 335:
      return new ::Ifc4x2::IfcDuctFittingType(std::move(data));
    case 336:
      return new ::Ifc4x2::IfcDuctFittingTypeEnum(std::move(data));
    case 337:
      return new ::Ifc4x2::IfcDuctSegment(std::move(data));
    case 338:
      return new ::Ifc4x2::IfcDuctSegmentType(std::move(data));
    case 339:
      return new ::Ifc4x2::IfcDuctSegmentTypeEnum(std::move(data));
    case 340:
      return new ::Ifc4x2::IfcDuctSilencer(std::move(data));
    case 341:
      return new ::Ifc4x2::IfcDuctSilencerType(std::move(data));
    case 342:
      return new ::Ifc4x2::IfcDuctSilencerTypeEnum(std::move(data));
    case 343:
      return new ::Ifc4x2::IfcDuration(std::move(data));
    case 344:
      return new ::Ifc4x2::IfcDynamicViscosityMeasure(std::move(data));
    case 345:
      return new ::Ifc4x2::IfcEdge(std::move(data));
    case 346:
      return new ::Ifc4x2::IfcEdgeCurve(std::move(data));
    case 347:
      return new ::Ifc4x2::IfcEdgeLoop(std::move(data));
    case 348:
      return new ::Ifc4x2::IfcElectricAppliance(std::move(data));
    case 349:
      return new ::Ifc4x2::IfcElectricApplianceType(std::move(data));
    case 350:
      return new ::Ifc4x2::IfcElectricApplianceTypeEnum(std::move(data));
    case 351:
      return new ::Ifc4x2::IfcElectricCapacitanceMeasure(std::move(data));
    case 352:
      return new ::Ifc4x2::IfcElectricChargeMeasure(std::move(data));
    case 353:
      return new ::Ifc4x2::IfcElectricConductanceMeasure(std::move(data));
    case 354:
      return new ::Ifc4x2::IfcElectricCurrentMeasure(std::move(data));
    case 355:
      return new ::Ifc4x2::IfcElectricDistributionBoard(std::move(data));
    case 356:
      return new ::Ifc4x2::IfcElectricDistributionBoardType(std::move(data));
    case 357:
      return new ::Ifc4x2::IfcElectricDistributionBoardTypeEnum(
          std::move(data));
    case 358:
      return new ::Ifc4x2::IfcElectricFlowStorageDevice(std::move(data));
    case 359:
      return new ::Ifc4x2::IfcElectricFlowStorageDeviceType(std::move(data));
    case 360:
      return new ::Ifc4x2::IfcElectricFlowStorageDeviceTypeEnum(
          std::move(data));
    case 361:
      return new ::Ifc4x2::IfcElectricGenerator(std::move(data));
    case 362:
      return new ::Ifc4x2::IfcElectricGeneratorType(std::move(data));
    case 363:
      return new ::Ifc4x2::IfcElectricGeneratorTypeEnum(std::move(data));
    case 364:
      return new ::Ifc4x2::IfcElectricMotor(std::move(data));
    case 365:
      return new ::Ifc4x2::IfcElectricMotorType(std::move(data));
    case 366:
      return new ::Ifc4x2::IfcElectricMotorTypeEnum(std::move(data));
    case 367:
      return new ::Ifc4x2::IfcElectricResistanceMeasure(std::move(data));
    case 368:
      return new ::Ifc4x2::IfcElectricTimeControl(std::move(data));
    case 369:
      return new ::Ifc4x2::IfcElectricTimeControlType(std::move(data));
    case 370:
      return new ::Ifc4x2::IfcElectricTimeControlTypeEnum(std::move(data));
    case 371:
      return new ::Ifc4x2::IfcElectricVoltageMeasure(std::move(data));
    case 372:
      return new ::Ifc4x2::IfcElement(std::move(data));
    case 373:
      return new ::Ifc4x2::IfcElementarySurface(std::move(data));
    case 374:
      return new ::Ifc4x2::IfcElementAssembly(std::move(data));
    case 375:
      return new ::Ifc4x2::IfcElementAssemblyType(std::move(data));
    case 376:
      return new ::Ifc4x2::IfcElementAssemblyTypeEnum(std::move(data));
    case 377:
      return new ::Ifc4x2::IfcElementComponent(std::move(data));
    case 378:
      return new ::Ifc4x2::IfcElementComponentType(std::move(data));
    case 379:
      return new ::Ifc4x2::IfcElementCompositionEnum(std::move(data));
    case 380:
      return new ::Ifc4x2::IfcElementQuantity(std::move(data));
    case 381:
      return new ::Ifc4x2::IfcElementType(std::move(data));
    case 382:
      return new ::Ifc4x2::IfcEllipse(std::move(data));
    case 383:
      return new ::Ifc4x2::IfcEllipseProfileDef(std::move(data));
    case 384:
      return new ::Ifc4x2::IfcEnergyConversionDevice(std::move(data));
    case 385:
      return new ::Ifc4x2::IfcEnergyConversionDeviceType(std::move(data));
    case 386:
      return new ::Ifc4x2::IfcEnergyMeasure(std::move(data));
    case 387:
      return new ::Ifc4x2::IfcEngine(std::move(data));
    case 388:
      return new ::Ifc4x2::IfcEngineType(std::move(data));
    case 389:
      return new ::Ifc4x2::IfcEngineTypeEnum(std::move(data));
    case 390:
      return new ::Ifc4x2::IfcEvaporativeCooler(std::move(data));
    case 391:
      return new ::Ifc4x2::IfcEvaporativeCoolerType(std::move(data));
    case 392:
      return new ::Ifc4x2::IfcEvaporativeCoolerTypeEnum(std::move(data));
    case 393:
      return new ::Ifc4x2::IfcEvaporator(std::move(data));
    case 394:
      return new ::Ifc4x2::IfcEvaporatorType(std::move(data));
    case 395:
      return new ::Ifc4x2::IfcEvaporatorTypeEnum(std::move(data));
    case 396:
      return new ::Ifc4x2::IfcEvent(std::move(data));
    case 397:
      return new ::Ifc4x2::IfcEventTime(std::move(data));
    case 398:
      return new ::Ifc4x2::IfcEventTriggerTypeEnum(std::move(data));
    case 399:
      return new ::Ifc4x2::IfcEventType(std::move(data));
    case 400:
      return new ::Ifc4x2::IfcEventTypeEnum(std::move(data));
    case 401:
      return new ::Ifc4x2::IfcExtendedProperties(std::move(data));
    case 402:
      return new ::Ifc4x2::IfcExternalInformation(std::move(data));
    case 403:
      return new ::Ifc4x2::IfcExternallyDefinedHatchStyle(std::move(data));
    case 404:
      return new ::Ifc4x2::IfcExternallyDefinedSurfaceStyle(std::move(data));
    case 405:
      return new ::Ifc4x2::IfcExternallyDefinedTextFont(std::move(data));
    case 406:
      return new ::Ifc4x2::IfcExternalReference(std::move(data));
    case 407:
      return new ::Ifc4x2::IfcExternalReferenceRelationship(std::move(data));
    case 408:
      return new ::Ifc4x2::IfcExternalSpatialElement(std::move(data));
    case 409:
      return new ::Ifc4x2::IfcExternalSpatialElementTypeEnum(std::move(data));
    case 410:
      return new ::Ifc4x2::IfcExternalSpatialStructureElement(std::move(data));
    case 411:
      return new ::Ifc4x2::IfcExtrudedAreaSolid(std::move(data));
    case 412:
      return new ::Ifc4x2::IfcExtrudedAreaSolidTapered(std::move(data));
    case 413:
      return new ::Ifc4x2::IfcFace(std::move(data));
    case 414:
      return new ::Ifc4x2::IfcFaceBasedSurfaceModel(std::move(data));
    case 415:
      return new ::Ifc4x2::IfcFaceBound(std::move(data));
    case 416:
      return new ::Ifc4x2::IfcFaceOuterBound(std::move(data));
    case 417:
      return new ::Ifc4x2::IfcFaceSurface(std::move(data));
    case 418:
      return new ::Ifc4x2::IfcFacetedBrep(std::move(data));
    case 419:
      return new ::Ifc4x2::IfcFacetedBrepWithVoids(std::move(data));
    case 420:
      return new ::Ifc4x2::IfcFacility(std::move(data));
    case 421:
      return new ::Ifc4x2::IfcFacilityPart(std::move(data));
    case 422:
      return new ::Ifc4x2::IfcFailureConnectionCondition(std::move(data));
    case 423:
      return new ::Ifc4x2::IfcFan(std::move(data));
    case 424:
      return new ::Ifc4x2::IfcFanType(std::move(data));
    case 425:
      return new ::Ifc4x2::IfcFanTypeEnum(std::move(data));
    case 426:
      return new ::Ifc4x2::IfcFastener(std::move(data));
    case 427:
      return new ::Ifc4x2::IfcFastenerType(std::move(data));
    case 428:
      return new ::Ifc4x2::IfcFastenerTypeEnum(std::move(data));
    case 429:
      return new ::Ifc4x2::IfcFeatureElement(std::move(data));
    case 430:
      return new ::Ifc4x2::IfcFeatureElementAddition(std::move(data));
    case 431:
      return new ::Ifc4x2::IfcFeatureElementSubtraction(std::move(data));
    case 432:
      return new ::Ifc4x2::IfcFillAreaStyle(std::move(data));
    case 433:
      return new ::Ifc4x2::IfcFillAreaStyleHatching(std::move(data));
    case 434:
      return new ::Ifc4x2::IfcFillAreaStyleTiles(std::move(data));
    case 436:
      return new ::Ifc4x2::IfcFilter(std::move(data));
    case 437:
      return new ::Ifc4x2::IfcFilterType(std::move(data));
    case 438:
      return new ::Ifc4x2::IfcFilterTypeEnum(std::move(data));
    case 439:
      return new ::Ifc4x2::IfcFireSuppressionTerminal(std::move(data));
    case 440:
      return new ::Ifc4x2::IfcFireSuppressionTerminalType(std::move(data));
    case 441:
      return new ::Ifc4x2::IfcFireSuppressionTerminalTypeEnum(std::move(data));
    case 442:
      return new ::Ifc4x2::IfcFixedReferenceSweptAreaSolid(std::move(data));
    case 443:
      return new ::Ifc4x2::IfcFlowController(std::move(data));
    case 444:
      return new ::Ifc4x2::IfcFlowControllerType(std::move(data));
    case 445:
      return new ::Ifc4x2::IfcFlowDirectionEnum(std::move(data));
    case 446:
      return new ::Ifc4x2::IfcFlowFitting(std::move(data));
    case 447:
      return new ::Ifc4x2::IfcFlowFittingType(std::move(data));
    case 448:
      return new ::Ifc4x2::IfcFlowInstrument(std::move(data));
    case 449:
      return new ::Ifc4x2::IfcFlowInstrumentType(std::move(data));
    case 450:
      return new ::Ifc4x2::IfcFlowInstrumentTypeEnum(std::move(data));
    case 451:
      return new ::Ifc4x2::IfcFlowMeter(std::move(data));
    case 452:
      return new ::Ifc4x2::IfcFlowMeterType(std::move(data));
    case 453:
      return new ::Ifc4x2::IfcFlowMeterTypeEnum(std::move(data));
    case 454:
      return new ::Ifc4x2::IfcFlowMovingDevice(std::move(data));
    case 455:
      return new ::Ifc4x2::IfcFlowMovingDeviceType(std::move(data));
    case 456:
      return new ::Ifc4x2::IfcFlowSegment(std::move(data));
    case 457:
      return new ::Ifc4x2::IfcFlowSegmentType(std::move(data));
    case 458:
      return new ::Ifc4x2::IfcFlowStorageDevice(std::move(data));
    case 459:
      return new ::Ifc4x2::IfcFlowStorageDeviceType(std::move(data));
    case 460:
      return new ::Ifc4x2::IfcFlowTerminal(std::move(data));
    case 461:
      return new ::Ifc4x2::IfcFlowTerminalType(std::move(data));
    case 462:
      return new ::Ifc4x2::IfcFlowTreatmentDevice(std::move(data));
    case 463:
      return new ::Ifc4x2::IfcFlowTreatmentDeviceType(std::move(data));
    case 464:
      return new ::Ifc4x2::IfcFontStyle(std::move(data));
    case 465:
      return new ::Ifc4x2::IfcFontVariant(std::move(data));
    case 466:
      return new ::Ifc4x2::IfcFontWeight(std::move(data));
    case 467:
      return new ::Ifc4x2::IfcFooting(std::move(data));
    case 468:
      return new ::Ifc4x2::IfcFootingType(std::move(data));
    case 469:
      return new ::Ifc4x2::IfcFootingTypeEnum(std::move(data));
    case 470:
      return new ::Ifc4x2::IfcForceMeasure(std::move(data));
    case 471:
      return new ::Ifc4x2::IfcFrequencyMeasure(std::move(data));
    case 472:
      return new ::Ifc4x2::IfcFurnishingElement(std::move(data));
    case 473:
      return new ::Ifc4x2::IfcFurnishingElementType(std::move(data));
    case 474:
      return new ::Ifc4x2::IfcFurniture(std::move(data));
    case 475:
      return new ::Ifc4x2::IfcFurnitureType(std::move(data));
    case 476:
      return new ::Ifc4x2::IfcFurnitureTypeEnum(std::move(data));
    case 477:
      return new ::Ifc4x2::IfcGeographicElement(std::move(data));
    case 478:
      return new ::Ifc4x2::IfcGeographicElementType(std::move(data));
    case 479:
      return new ::Ifc4x2::IfcGeographicElementTypeEnum(std::move(data));
    case 480:
      return new ::Ifc4x2::IfcGeometricCurveSet(std::move(data));
    case 481:
      return new ::Ifc4x2::IfcGeometricProjectionEnum(std::move(data));
    case 482:
      return new ::Ifc4x2::IfcGeometricRepresentationContext(std::move(data));
    case 483:
      return new ::Ifc4x2::IfcGeometricRepresentationItem(std::move(data));
    case 484:
      return new ::Ifc4x2::IfcGeometricRepresentationSubContext(
          std::move(data));
    case 485:
      return new ::Ifc4x2::IfcGeometricSet(std::move(data));
    case 487:
      return new ::Ifc4x2::IfcGloballyUniqueId(std::move(data));
    case 488:
      return new ::Ifc4x2::IfcGlobalOrLocalEnum(std::move(data));
    case 489:
      return new ::Ifc4x2::IfcGrid(std::move(data));
    case 490:
      return new ::Ifc4x2::IfcGridAxis(std::move(data));
    case 491:
      return new ::Ifc4x2::IfcGridPlacement(std::move(data));
    case 493:
      return new ::Ifc4x2::IfcGridTypeEnum(std::move(data));
    case 494:
      return new ::Ifc4x2::IfcGroup(std::move(data));
    case 495:
      return new ::Ifc4x2::IfcHalfSpaceSolid(std::move(data));
    case 497:
      return new ::Ifc4x2::IfcHeatExchanger(std::move(data));
    case 498:
      return new ::Ifc4x2::IfcHeatExchangerType(std::move(data));
    case 499:
      return new ::Ifc4x2::IfcHeatExchangerTypeEnum(std::move(data));
    case 500:
      return new ::Ifc4x2::IfcHeatFluxDensityMeasure(std::move(data));
    case 501:
      return new ::Ifc4x2::IfcHeatingValueMeasure(std::move(data));
    case 502:
      return new ::Ifc4x2::IfcHumidifier(std::move(data));
    case 503:
      return new ::Ifc4x2::IfcHumidifierType(std::move(data));
    case 504:
      return new ::Ifc4x2::IfcHumidifierTypeEnum(std::move(data));
    case 505:
      return new ::Ifc4x2::IfcIdentifier(std::move(data));
    case 506:
      return new ::Ifc4x2::IfcIlluminanceMeasure(std::move(data));
    case 507:
      return new ::Ifc4x2::IfcImageTexture(std::move(data));
    case 508:
      return new ::Ifc4x2::IfcIndexedColourMap(std::move(data));
    case 509:
      return new ::Ifc4x2::IfcIndexedPolyCurve(std::move(data));
    case 510:
      return new ::Ifc4x2::IfcIndexedPolygonalFace(std::move(data));
    case 511:
      return new ::Ifc4x2::IfcIndexedPolygonalFaceWithVoids(std::move(data));
    case 512:
      return new ::Ifc4x2::IfcIndexedTextureMap(std::move(data));
    case 513:
      return new ::Ifc4x2::IfcIndexedTriangleTextureMap(std::move(data));
    case 514:
      return new ::Ifc4x2::IfcInductanceMeasure(std::move(data));
    case 515:
      return new ::Ifc4x2::IfcInteger(std::move(data));
    case 516:
      return new ::Ifc4x2::IfcIntegerCountRateMeasure(std::move(data));
    case 517:
      return new ::Ifc4x2::IfcInterceptor(std::move(data));
    case 518:
      return new ::Ifc4x2::IfcInterceptorType(std::move(data));
    case 519:
      return new ::Ifc4x2::IfcInterceptorTypeEnum(std::move(data));
    case 520:
      return new ::Ifc4x2::IfcInternalOrExternalEnum(std::move(data));
    case 521:
      return new ::Ifc4x2::IfcIntersectionCurve(std::move(data));
    case 522:
      return new ::Ifc4x2::IfcInventory(std::move(data));
    case 523:
      return new ::Ifc4x2::IfcInventoryTypeEnum(std::move(data));
    case 524:
      return new ::Ifc4x2::IfcIonConcentrationMeasure(std::move(data));
    case 525:
      return new ::Ifc4x2::IfcIrregularTimeSeries(std::move(data));
    case 526:
      return new ::Ifc4x2::IfcIrregularTimeSeriesValue(std::move(data));
    case 527:
      return new ::Ifc4x2::IfcIShapeProfileDef(std::move(data));
    case 528:
      return new ::Ifc4x2::IfcIsothermalMoistureCapacityMeasure(
          std::move(data));
    case 529:
      return new ::Ifc4x2::IfcJunctionBox(std::move(data));
    case 530:
      return new ::Ifc4x2::IfcJunctionBoxType(std::move(data));
    case 531:
      return new ::Ifc4x2::IfcJunctionBoxTypeEnum(std::move(data));
    case 532:
      return new ::Ifc4x2::IfcKinematicViscosityMeasure(std::move(data));
    case 533:
      return new ::Ifc4x2::IfcKnotType(std::move(data));
    case 534:
      return new ::Ifc4x2::IfcLabel(std::move(data));
    case 535:
      return new ::Ifc4x2::IfcLaborResource(std::move(data));
    case 536:
      return new ::Ifc4x2::IfcLaborResourceType(std::move(data));
    case 537:
      return new ::Ifc4x2::IfcLaborResourceTypeEnum(std::move(data));
    case 538:
      return new ::Ifc4x2::IfcLagTime(std::move(data));
    case 539:
      return new ::Ifc4x2::IfcLamp(std::move(data));
    case 540:
      return new ::Ifc4x2::IfcLampType(std::move(data));
    case 541:
      return new ::Ifc4x2::IfcLampTypeEnum(std::move(data));
    case 542:
      return new ::Ifc4x2::IfcLanguageId(std::move(data));
    case 544:
      return new ::Ifc4x2::IfcLayerSetDirectionEnum(std::move(data));
    case 545:
      return new ::Ifc4x2::IfcLengthMeasure(std::move(data));
    case 546:
      return new ::Ifc4x2::IfcLibraryInformation(std::move(data));
    case 547:
      return new ::Ifc4x2::IfcLibraryReference(std::move(data));
    case 549:
      return new ::Ifc4x2::IfcLightDistributionCurveEnum(std::move(data));
    case 550:
      return new ::Ifc4x2::IfcLightDistributionData(std::move(data));
    case 552:
      return new ::Ifc4x2::IfcLightEmissionSourceEnum(std::move(data));
    case 553:
      return new ::Ifc4x2::IfcLightFixture(std::move(data));
    case 554:
      return new ::Ifc4x2::IfcLightFixtureType(std::move(data));
    case 555:
      return new ::Ifc4x2::IfcLightFixtureTypeEnum(std::move(data));
    case 556:
      return new ::Ifc4x2::IfcLightIntensityDistribution(std::move(data));
    case 557:
      return new ::Ifc4x2::IfcLightSource(std::move(data));
    case 558:
      return new ::Ifc4x2::IfcLightSourceAmbient(std::move(data));
    case 559:
      return new ::Ifc4x2::IfcLightSourceDirectional(std::move(data));
    case 560:
      return new ::Ifc4x2::IfcLightSourceGoniometric(std::move(data));
    case 561:
      return new ::Ifc4x2::IfcLightSourcePositional(std::move(data));
    case 562:
      return new ::Ifc4x2::IfcLightSourceSpot(std::move(data));
    case 563:
      return new ::Ifc4x2::IfcLine(std::move(data));
    case 564:
      return new ::Ifc4x2::IfcLinearForceMeasure(std::move(data));
    case 565:
      return new ::Ifc4x2::IfcLinearMomentMeasure(std::move(data));
    case 566:
      return new ::Ifc4x2::IfcLinearPlacement(std::move(data));
    case 567:
      return new ::Ifc4x2::IfcLinearPositioningElement(std::move(data));
    case 568:
      return new ::Ifc4x2::IfcLinearStiffnessMeasure(std::move(data));
    case 569:
      return new ::Ifc4x2::IfcLinearVelocityMeasure(std::move(data));
    case 570:
      return new ::Ifc4x2::IfcLineIndex(std::move(data));
    case 571:
      return new ::Ifc4x2::IfcLineSegment2D(std::move(data));
    case 572:
      return new ::Ifc4x2::IfcLoadGroupTypeEnum(std::move(data));
    case 573:
      return new ::Ifc4x2::IfcLocalPlacement(std::move(data));
    case 574:
      return new ::Ifc4x2::IfcLogical(std::move(data));
    case 575:
      return new ::Ifc4x2::IfcLogicalOperatorEnum(std::move(data));
    case 576:
      return new ::Ifc4x2::IfcLoop(std::move(data));
    case 577:
      return new ::Ifc4x2::IfcLShapeProfileDef(std::move(data));
    case 578:
      return new ::Ifc4x2::IfcLuminousFluxMeasure(std::move(data));
    case 579:
      return new ::Ifc4x2::IfcLuminousIntensityDistributionMeasure(
          std::move(data));
    case 580:
      return new ::Ifc4x2::IfcLuminousIntensityMeasure(std::move(data));
    case 581:
      return new ::Ifc4x2::IfcMagneticFluxDensityMeasure(std::move(data));
    case 582:
      return new ::Ifc4x2::IfcMagneticFluxMeasure(std::move(data));
    case 583:
      return new ::Ifc4x2::IfcManifoldSolidBrep(std::move(data));
    case 584:
      return new ::Ifc4x2::IfcMapConversion(std::move(data));
    case 585:
      return new ::Ifc4x2::IfcMappedItem(std::move(data));
    case 586:
      return new ::Ifc4x2::IfcMassDensityMeasure(std::move(data));
    case 587:
      return new ::Ifc4x2::IfcMassFlowRateMeasure(std::move(data));
    case 588:
      return new ::Ifc4x2::IfcMassMeasure(std::move(data));
    case 589:
      return new ::Ifc4x2::IfcMassPerLengthMeasure(std::move(data));
    case 590:
      return new ::Ifc4x2::IfcMaterial(std::move(data));
    case 591:
      return new ::Ifc4x2::IfcMaterialClassificationRelationship(
          std::move(data));
    case 592:
      return new ::Ifc4x2::IfcMaterialConstituent(std::move(data));
    case 593:
      return new ::Ifc4x2::IfcMaterialConstituentSet(std::move(data));
    case 594:
      return new ::Ifc4x2::IfcMaterialDefinition(std::move(data));
    case 595:
      return new ::Ifc4x2::IfcMaterialDefinitionRepresentation(std::move(data));
    case 596:
      return new ::Ifc4x2::IfcMaterialLayer(std::move(data));
    case 597:
      return new ::Ifc4x2::IfcMaterialLayerSet(std::move(data));
    case 598:
      return new ::Ifc4x2::IfcMaterialLayerSetUsage(std::move(data));
    case 599:
      return new ::Ifc4x2::IfcMaterialLayerWithOffsets(std::move(data));
    case 600:
      return new ::Ifc4x2::IfcMaterialList(std::move(data));
    case 601:
      return new ::Ifc4x2::IfcMaterialProfile(std::move(data));
    case 602:
      return new ::Ifc4x2::IfcMaterialProfileSet(std::move(data));
    case 603:
      return new ::Ifc4x2::IfcMaterialProfileSetUsage(std::move(data));
    case 604:
      return new ::Ifc4x2::IfcMaterialProfileSetUsageTapering(std::move(data));
    case 605:
      return new ::Ifc4x2::IfcMaterialProfileWithOffsets(std::move(data));
    case 606:
      return new ::Ifc4x2::IfcMaterialProperties(std::move(data));
    case 607:
      return new ::Ifc4x2::IfcMaterialRelationship(std::move(data));
    case 609:
      return new ::Ifc4x2::IfcMaterialUsageDefinition(std::move(data));
    case 611:
      return new ::Ifc4x2::IfcMeasureWithUnit(std::move(data));
    case 612:
      return new ::Ifc4x2::IfcMechanicalFastener(std::move(data));
    case 613:
      return new ::Ifc4x2::IfcMechanicalFastenerType(std::move(data));
    case 614:
      return new ::Ifc4x2::IfcMechanicalFastenerTypeEnum(std::move(data));
    case 615:
      return new ::Ifc4x2::IfcMedicalDevice(std::move(data));
    case 616:
      return new ::Ifc4x2::IfcMedicalDeviceType(std::move(data));
    case 617:
      return new ::Ifc4x2::IfcMedicalDeviceTypeEnum(std::move(data));
    case 618:
      return new ::Ifc4x2::IfcMember(std::move(data));
    case 619:
      return new ::Ifc4x2::IfcMemberStandardCase(std::move(data));
    case 620:
      return new ::Ifc4x2::IfcMemberType(std::move(data));
    case 621:
      return new ::Ifc4x2::IfcMemberTypeEnum(std::move(data));
    case 622:
      return new ::Ifc4x2::IfcMetric(std::move(data));
    case 624:
      return new ::Ifc4x2::IfcMirroredProfileDef(std::move(data));
    case 625:
      return new ::Ifc4x2::IfcModulusOfElasticityMeasure(std::move(data));
    case 626:
      return new ::Ifc4x2::IfcModulusOfLinearSubgradeReactionMeasure(
          std::move(data));
    case 627:
      return new ::Ifc4x2::IfcModulusOfRotationalSubgradeReactionMeasure(
          std::move(data));
    case 629:
      return new ::Ifc4x2::IfcModulusOfSubgradeReactionMeasure(std::move(data));
    case 632:
      return new ::Ifc4x2::IfcMoistureDiffusivityMeasure(std::move(data));
    case 633:
      return new ::Ifc4x2::IfcMolecularWeightMeasure(std::move(data));
    case 634:
      return new ::Ifc4x2::IfcMomentOfInertiaMeasure(std::move(data));
    case 635:
      return new ::Ifc4x2::IfcMonetaryMeasure(std::move(data));
    case 636:
      return new ::Ifc4x2::IfcMonetaryUnit(std::move(data));
    case 637:
      return new ::Ifc4x2::IfcMonthInYearNumber(std::move(data));
    case 638:
      return new ::Ifc4x2::IfcMotorConnection(std::move(data));
    case 639:
      return new ::Ifc4x2::IfcMotorConnectionType(std::move(data));
    case 640:
      return new ::Ifc4x2::IfcMotorConnectionTypeEnum(std::move(data));
    case 641:
      return new ::Ifc4x2::IfcNamedUnit(std::move(data));
    case 642:
      return new ::Ifc4x2::IfcNonNegativeLengthMeasure(std::move(data));
    case 643:
      return new ::Ifc4x2::IfcNormalisedRatioMeasure(std::move(data));
    case 644:
      return new ::Ifc4x2::IfcNullStyle(std::move(data));
    case 645:
      return new ::Ifc4x2::IfcNumericMeasure(std::move(data));
    case 646:
      return new ::Ifc4x2::IfcObject(std::move(data));
    case 647:
      return new ::Ifc4x2::IfcObjectDefinition(std::move(data));
    case 648:
      return new ::Ifc4x2::IfcObjective(std::move(data));
    case 649:
      return new ::Ifc4x2::IfcObjectiveEnum(std::move(data));
    case 650:
      return new ::Ifc4x2::IfcObjectPlacement(std::move(data));
    case 652:
      return new ::Ifc4x2::IfcObjectTypeEnum(std::move(data));
    case 653:
      return new ::Ifc4x2::IfcOccupant(std::move(data));
    case 654:
      return new ::Ifc4x2::IfcOccupantTypeEnum(std::move(data));
    case 655:
      return new ::Ifc4x2::IfcOffsetCurve(std::move(data));
    case 656:
      return new ::Ifc4x2::IfcOffsetCurve2D(std::move(data));
    case 657:
      return new ::Ifc4x2::IfcOffsetCurve3D(std::move(data));
    case 658:
      return new ::Ifc4x2::IfcOffsetCurveByDistances(std::move(data));
    case 659:
      return new ::Ifc4x2::IfcOpeningElement(std::move(data));
    case 660:
      return new ::Ifc4x2::IfcOpeningElementTypeEnum(std::move(data));
    case 661:
      return new ::Ifc4x2::IfcOpeningStandardCase(std::move(data));
    case 662:
      return new ::Ifc4x2::IfcOpenShell(std::move(data));
    case 663:
      return new ::Ifc4x2::IfcOrganization(std::move(data));
    case 664:
      return new ::Ifc4x2::IfcOrganizationRelationship(std::move(data));
    case 665:
      return new ::Ifc4x2::IfcOrientationExpression(std::move(data));
    case 666:
      return new ::Ifc4x2::IfcOrientedEdge(std::move(data));
    case 667:
      return new ::Ifc4x2::IfcOuterBoundaryCurve(std::move(data));
    case 668:
      return new ::Ifc4x2::IfcOutlet(std::move(data));
    case 669:
      return new ::Ifc4x2::IfcOutletType(std::move(data));
    case 670:
      return new ::Ifc4x2::IfcOutletTypeEnum(std::move(data));
    case 671:
      return new ::Ifc4x2::IfcOwnerHistory(std::move(data));
    case 672:
      return new ::Ifc4x2::IfcParameterizedProfileDef(std::move(data));
    case 673:
      return new ::Ifc4x2::IfcParameterValue(std::move(data));
    case 674:
      return new ::Ifc4x2::IfcPath(std::move(data));
    case 675:
      return new ::Ifc4x2::IfcPcurve(std::move(data));
    case 676:
      return new ::Ifc4x2::IfcPerformanceHistory(std::move(data));
    case 677:
      return new ::Ifc4x2::IfcPerformanceHistoryTypeEnum(std::move(data));
    case 678:
      return new ::Ifc4x2::IfcPermeableCoveringOperationEnum(std::move(data));
    case 679:
      return new ::Ifc4x2::IfcPermeableCoveringProperties(std::move(data));
    case 680:
      return new ::Ifc4x2::IfcPermit(std::move(data));
    case 681:
      return new ::Ifc4x2::IfcPermitTypeEnum(std::move(data));
    case 682:
      return new ::Ifc4x2::IfcPerson(std::move(data));
    case 683:
      return new ::Ifc4x2::IfcPersonAndOrganization(std::move(data));
    case 684:
      return new ::Ifc4x2::IfcPHMeasure(std::move(data));
    case 685:
      return new ::Ifc4x2::IfcPhysicalComplexQuantity(std::move(data));
    case 686:
      return new ::Ifc4x2::IfcPhysicalOrVirtualEnum(std::move(data));
    case 687:
      return new ::Ifc4x2::IfcPhysicalQuantity(std::move(data));
    case 688:
      return new ::Ifc4x2::IfcPhysicalSimpleQuantity(std::move(data));
    case 689:
      return new ::Ifc4x2::IfcPile(std::move(data));
    case 690:
      return new ::Ifc4x2::IfcPileConstructionEnum(std::move(data));
    case 691:
      return new ::Ifc4x2::IfcPileType(std::move(data));
    case 692:
      return new ::Ifc4x2::IfcPileTypeEnum(std::move(data));
    case 693:
      return new ::Ifc4x2::IfcPipeFitting(std::move(data));
    case 694:
      return new ::Ifc4x2::IfcPipeFittingType(std::move(data));
    case 695:
      return new ::Ifc4x2::IfcPipeFittingTypeEnum(std::move(data));
    case 696:
      return new ::Ifc4x2::IfcPipeSegment(std::move(data));
    case 697:
      return new ::Ifc4x2::IfcPipeSegmentType(std::move(data));
    case 698:
      return new ::Ifc4x2::IfcPipeSegmentTypeEnum(std::move(data));
    case 699:
      return new ::Ifc4x2::IfcPixelTexture(std::move(data));
    case 700:
      return new ::Ifc4x2::IfcPlacement(std::move(data));
    case 701:
      return new ::Ifc4x2::IfcPlanarBox(std::move(data));
    case 702:
      return new ::Ifc4x2::IfcPlanarExtent(std::move(data));
    case 703:
      return new ::Ifc4x2::IfcPlanarForceMeasure(std::move(data));
    case 704:
      return new ::Ifc4x2::IfcPlane(std::move(data));
    case 705:
      return new ::Ifc4x2::IfcPlaneAngleMeasure(std::move(data));
    case 706:
      return new ::Ifc4x2::IfcPlate(std::move(data));
    case 707:
      return new ::Ifc4x2::IfcPlateStandardCase(std::move(data));
    case 708:
      return new ::Ifc4x2::IfcPlateType(std::move(data));
    case 709:
      return new ::Ifc4x2::IfcPlateTypeEnum(std::move(data));
    case 710:
      return new ::Ifc4x2::IfcPoint(std::move(data));
    case 711:
      return new ::Ifc4x2::IfcPointOnCurve(std::move(data));
    case 712:
      return new ::Ifc4x2::IfcPointOnSurface(std::move(data));
    case 714:
      return new ::Ifc4x2::IfcPolygonalBoundedHalfSpace(std::move(data));
    case 715:
      return new ::Ifc4x2::IfcPolygonalFaceSet(std::move(data));
    case 716:
      return new ::Ifc4x2::IfcPolyline(std::move(data));
    case 717:
      return new ::Ifc4x2::IfcPolyLoop(std::move(data));
    case 718:
      return new ::Ifc4x2::IfcPort(std::move(data));
    case 719:
      return new ::Ifc4x2::IfcPositioningElement(std::move(data));
    case 720:
      return new ::Ifc4x2::IfcPositiveInteger(std::move(data));
    case 721:
      return new ::Ifc4x2::IfcPositiveLengthMeasure(std::move(data));
    case 722:
      return new ::Ifc4x2::IfcPositivePlaneAngleMeasure(std::move(data));
    case 723:
      return new ::Ifc4x2::IfcPositiveRatioMeasure(std::move(data));
    case 724:
      return new ::Ifc4x2::IfcPostalAddress(std::move(data));
    case 725:
      return new ::Ifc4x2::IfcPowerMeasure(std::move(data));
    case 726:
      return new ::Ifc4x2::IfcPreDefinedColour(std::move(data));
    case 727:
      return new ::Ifc4x2::IfcPreDefinedCurveFont(std::move(data));
    case 728:
      return new ::Ifc4x2::IfcPreDefinedItem(std::move(data));
    case 729:
      return new ::Ifc4x2::IfcPreDefinedProperties(std::move(data));
    case 730:
      return new ::Ifc4x2::IfcPreDefinedPropertySet(std::move(data));
    case 731:
      return new ::Ifc4x2::IfcPreDefinedTextFont(std::move(data));
    case 732:
      return new ::Ifc4x2::IfcPreferredSurfaceCurveRepresentation(
          std::move(data));
    case 733:
      return new ::Ifc4x2::IfcPresentableText(std::move(data));
    case 734:
      return new ::Ifc4x2::IfcPresentationItem(std::move(data));
    case 735:
      return new ::Ifc4x2::IfcPresentationLayerAssignment(std::move(data));
    case 736:
      return new ::Ifc4x2::IfcPresentationLayerWithStyle(std::move(data));
    case 737:
      return new ::Ifc4x2::IfcPresentationStyle(std::move(data));
    case 738:
      return new ::Ifc4x2::IfcPresentationStyleAssignment(std::move(data));
    case 740:
      return new ::Ifc4x2::IfcPressureMeasure(std::move(data));
    case 741:
      return new ::Ifc4x2::IfcProcedure(std::move(data));
    case 742:
      return new ::Ifc4x2::IfcProcedureType(std::move(data));
    case 743:
      return new ::Ifc4x2::IfcProcedureTypeEnum(std::move(data));
    case 744:
      return new ::Ifc4x2::IfcProcess(std::move(data));
    case 746:
      return new ::Ifc4x2::IfcProduct(std::move(data));
    case 747:
      return new ::Ifc4x2::IfcProductDefinitionShape(std::move(data));
    case 748:
      return new ::Ifc4x2::IfcProductRepresentation(std::move(data));
    case 751:
      return new ::Ifc4x2::IfcProfileDef(std::move(data));
    case 752:
      return new ::Ifc4x2::IfcProfileProperties(std::move(data));
    case 753:
      return new ::Ifc4x2::IfcProfileTypeEnum(std::move(data));
    case 754:
      return new ::Ifc4x2::IfcProject(std::move(data));
    case 755:
      return new ::Ifc4x2::IfcProjectedCRS(std::move(data));
    case 756:
      return new ::Ifc4x2::IfcProjectedOrTrueLengthEnum(std::move(data));
    case 757:
      return new ::Ifc4x2::IfcProjectionElement(std::move(data));
    case 758:
      return new ::Ifc4x2::IfcProjectionElementTypeEnum(std::move(data));
    case 759:
      return new ::Ifc4x2::IfcProjectLibrary(std::move(data));
    case 760:
      return new ::Ifc4x2::IfcProjectOrder(std::move(data));
    case 761:
      return new ::Ifc4x2::IfcProjectOrderTypeEnum(std::move(data));
    case 762:
      return new ::Ifc4x2::IfcProperty(std::move(data));
    case 763:
      return new ::Ifc4x2::IfcPropertyAbstraction(std::move(data));
    case 764:
      return new ::Ifc4x2::IfcPropertyBoundedValue(std::move(data));
    case 765:
      return new ::Ifc4x2::IfcPropertyDefinition(std::move(data));
    case 766:
      return new ::Ifc4x2::IfcPropertyDependencyRelationship(std::move(data));
    case 767:
      return new ::Ifc4x2::IfcPropertyEnumeratedValue(std::move(data));
    case 768:
      return new ::Ifc4x2::IfcPropertyEnumeration(std::move(data));
    case 769:
      return new ::Ifc4x2::IfcPropertyListValue(std::move(data));
    case 770:
      return new ::Ifc4x2::IfcPropertyReferenceValue(std::move(data));
    case 771:
      return new ::Ifc4x2::IfcPropertySet(std::move(data));
    case 772:
      return new ::Ifc4x2::IfcPropertySetDefinition(std::move(data));
    case 774:
      return new ::Ifc4x2::IfcPropertySetDefinitionSet(std::move(data));
    case 775:
      return new ::Ifc4x2::IfcPropertySetTemplate(std::move(data));
    case 776:
      return new ::Ifc4x2::IfcPropertySetTemplateTypeEnum(std::move(data));
    case 777:
      return new ::Ifc4x2::IfcPropertySingleValue(std::move(data));
    case 778:
      return new ::Ifc4x2::IfcPropertyTableValue(std::move(data));
    case 779:
      return new ::Ifc4x2::IfcPropertyTemplate(std::move(data));
    case 780:
      return new ::Ifc4x2::IfcPropertyTemplateDefinition(std::move(data));
    case 781:
      return new ::Ifc4x2::IfcProtectiveDevice(std::move(data));
    case 782:
      return new ::Ifc4x2::IfcProtectiveDeviceTrippingUnit(std::move(data));
    case 783:
      return new ::Ifc4x2::IfcProtectiveDeviceTrippingUnitType(std::move(data));
    case 784:
      return new ::Ifc4x2::IfcProtectiveDeviceTrippingUnitTypeEnum(
          std::move(data));
    case 785:
      return new ::Ifc4x2::IfcProtectiveDeviceType(std::move(data));
    case 786:
      return new ::Ifc4x2::IfcProtectiveDeviceTypeEnum(std::move(data));
    case 787:
      return new ::Ifc4x2::IfcProxy(std::move(data));
    case 788:
      return new ::Ifc4x2::IfcPump(std::move(data));
    case 789:
      return new ::Ifc4x2::IfcPumpType(std::move(data));
    case 790:
      return new ::Ifc4x2::IfcPumpTypeEnum(std::move(data));
    case 791:
      return new ::Ifc4x2::IfcQuantityArea(std::move(data));
    case 792:
      return new ::Ifc4x2::IfcQuantityCount(std::move(data));
    case 793:
      return new ::Ifc4x2::IfcQuantityLength(std::move(data));
    case 794:
      return new ::Ifc4x2::IfcQuantitySet(std::move(data));
    case 795:
      return new ::Ifc4x2::IfcQuantityTime(std::move(data));
    case 796:
      return new ::Ifc4x2::IfcQuantityVolume(std::move(data));
    case 797:
      return new ::Ifc4x2::IfcQuantityWeight(std::move(data));
    case 798:
      return new ::Ifc4x2::IfcRadioActivityMeasure(std::move(data));
    case 799:
      return new ::Ifc4x2::IfcRailing(std::move(data));
    case 800:
      return new ::Ifc4x2::IfcRailingType(std::move(data));
    case 801:
      return new ::Ifc4x2::IfcRailingTypeEnum(std::move(data));
    case 802:
      return new ::Ifc4x2::IfcRamp(std::move(data));
    case 803:
      return new ::Ifc4x2::IfcRampFlight(std::move(data));
    case 804:
      return new ::Ifc4x2::IfcRampFlightType(std::move(data));
    case 805:
      return new ::Ifc4x2::IfcRampFlightTypeEnum(std::move(data));
    case 806:
      return new ::Ifc4x2::IfcRampType(std::move(data));
    case 807:
      return new ::Ifc4x2::IfcRampTypeEnum(std::move(data));
    case 808:
      return new ::Ifc4x2::IfcRatioMeasure(std::move(data));
    case 809:
      return new ::Ifc4x2::IfcRationalBSplineCurveWithKnots(std::move(data));
    case 810:
      return new ::Ifc4x2::IfcRationalBSplineSurfaceWithKnots(std::move(data));
    case 811:
      return new ::Ifc4x2::IfcReal(std::move(data));
    case 812:
      return new ::Ifc4x2::IfcRectangleHollowProfileDef(std::move(data));
    case 813:
      return new ::Ifc4x2::IfcRectangleProfileDef(std::move(data));
    case 814:
      return new ::Ifc4x2::IfcRectangularPyramid(std::move(data));
    case 815:
      return new ::Ifc4x2::IfcRectangularTrimmedSurface(std::move(data));
    case 816:
      return new ::Ifc4x2::IfcRecurrencePattern(std::move(data));
    case 817:
      return new ::Ifc4x2::IfcRecurrenceTypeEnum(std::move(data));
    case 818:
      return new ::Ifc4x2::IfcReference(std::move(data));
    case 819:
      return new ::Ifc4x2::IfcReferent(std::move(data));
    case 820:
      return new ::Ifc4x2::IfcReferentTypeEnum(std::move(data));
    case 821:
      return new ::Ifc4x2::IfcReflectanceMethodEnum(std::move(data));
    case 822:
      return new ::Ifc4x2::IfcRegularTimeSeries(std::move(data));
    case 823:
      return new ::Ifc4x2::IfcReinforcementBarProperties(std::move(data));
    case 824:
      return new ::Ifc4x2::IfcReinforcementDefinitionProperties(
          std::move(data));
    case 825:
      return new ::Ifc4x2::IfcReinforcingBar(std::move(data));
    case 826:
      return new ::Ifc4x2::IfcReinforcingBarRoleEnum(std::move(data));
    case 827:
      return new ::Ifc4x2::IfcReinforcingBarSurfaceEnum(std::move(data));
    case 828:
      return new ::Ifc4x2::IfcReinforcingBarType(std::move(data));
    case 829:
      return new ::Ifc4x2::IfcReinforcingBarTypeEnum(std::move(data));
    case 830:
      return new ::Ifc4x2::IfcReinforcingElement(std::move(data));
    case 831:
      return new ::Ifc4x2::IfcReinforcingElementType(std::move(data));
    case 832:
      return new ::Ifc4x2::IfcReinforcingMesh(std::move(data));
    case 833:
      return new ::Ifc4x2::IfcReinforcingMeshType(std::move(data));
    case 834:
      return new ::Ifc4x2::IfcReinforcingMeshTypeEnum(std::move(data));
    case 835:
      return new ::Ifc4x2::IfcRelAggregates(std::move(data));
    case 836:
      return new ::Ifc4x2::IfcRelAssigns(std::move(data));
    case 837:
      return new ::Ifc4x2::IfcRelAssignsToActor(std::move(data));
    case 838:
      return new ::Ifc4x2::IfcRelAssignsToControl(std::move(data));
    case 839:
      return new ::Ifc4x2::IfcRelAssignsToGroup(std::move(data));
    case 840:
      return new ::Ifc4x2::IfcRelAssignsToGroupByFactor(std::move(data));
    case 841:
      return new ::Ifc4x2::IfcRelAssignsToProcess(std::move(data));
    case 842:
      return new ::Ifc4x2::IfcRelAssignsToProduct(std::move(data));
    case 843:
      return new ::Ifc4x2::IfcRelAssignsToResource(std::move(data));
    case 844:
      return new ::Ifc4x2::IfcRelAssociates(std::move(data));
    case 845:
      return new ::Ifc4x2::IfcRelAssociatesApproval(std::move(data));
    case 846:
      return new ::Ifc4x2::IfcRelAssociatesClassification(std::move(data));
    case 847:
      return new ::Ifc4x2::IfcRelAssociatesConstraint(std::move(data));
    case 848:
      return new ::Ifc4x2::IfcRelAssociatesDocument(std::move(data));
    case 849:
      return new ::Ifc4x2::IfcRelAssociatesLibrary(std::move(data));
    case 850:
      return new ::Ifc4x2::IfcRelAssociatesMaterial(std::move(data));
    case 851:
      return new ::Ifc4x2::IfcRelationship(std::move(data));
    case 852:
      return new ::Ifc4x2::IfcRelConnects(std::move(data));
    case 853:
      return new ::Ifc4x2::IfcRelConnectsElements(std::move(data));
    case 854:
      return new ::Ifc4x2::IfcRelConnectsPathElements(std::move(data));
    case 855:
      return new ::Ifc4x2::IfcRelConnectsPorts(std::move(data));
    case 856:
      return new ::Ifc4x2::IfcRelConnectsPortToElement(std::move(data));
    case 857:
      return new ::Ifc4x2::IfcRelConnectsStructuralActivity(std::move(data));
    case 858:
      return new ::Ifc4x2::IfcRelConnectsStructuralMember(std::move(data));
    case 859:
      return new ::Ifc4x2::IfcRelConnectsWithEccentricity(std::move(data));
    case 860:
      return new ::Ifc4x2::IfcRelConnectsWithRealizingElements(std::move(data));
    case 861:
      return new ::Ifc4x2::IfcRelContainedInSpatialStructure(std::move(data));
    case 862:
      return new ::Ifc4x2::IfcRelCoversBldgElements(std::move(data));
    case 863:
      return new ::Ifc4x2::IfcRelCoversSpaces(std::move(data));
    case 864:
      return new ::Ifc4x2::IfcRelDeclares(std::move(data));
    case 865:
      return new ::Ifc4x2::IfcRelDecomposes(std::move(data));
    case 866:
      return new ::Ifc4x2::IfcRelDefines(std::move(data));
    case 867:
      return new ::Ifc4x2::IfcRelDefinesByObject(std::move(data));
    case 868:
      return new ::Ifc4x2::IfcRelDefinesByProperties(std::move(data));
    case 869:
      return new ::Ifc4x2::IfcRelDefinesByTemplate(std::move(data));
    case 870:
      return new ::Ifc4x2::IfcRelDefinesByType(std::move(data));
    case 871:
      return new ::Ifc4x2::IfcRelFillsElement(std::move(data));
    case 872:
      return new ::Ifc4x2::IfcRelFlowControlElements(std::move(data));
    case 873:
      return new ::Ifc4x2::IfcRelInterferesElements(std::move(data));
    case 874:
      return new ::Ifc4x2::IfcRelNests(std::move(data));
    case 875:
      return new ::Ifc4x2::IfcRelPositions(std::move(data));
    case 876:
      return new ::Ifc4x2::IfcRelProjectsElement(std::move(data));
    case 877:
      return new ::Ifc4x2::IfcRelReferencedInSpatialStructure(std::move(data));
    case 878:
      return new ::Ifc4x2::IfcRelSequence(std::move(data));
    case 879:
      return new ::Ifc4x2::IfcRelServicesBuildings(std::move(data));
    case 880:
      return new ::Ifc4x2::IfcRelSpaceBoundary(std::move(data));
    case 881:
      return new ::Ifc4x2::IfcRelSpaceBoundary1stLevel(std::move(data));
    case 882:
      return new ::Ifc4x2::IfcRelSpaceBoundary2ndLevel(std::move(data));
    case 883:
      return new ::Ifc4x2::IfcRelVoidsElement(std::move(data));
    case 884:
      return new ::Ifc4x2::IfcReparametrisedCompositeCurveSegment(
          std::move(data));
    case 885:
      return new ::Ifc4x2::IfcRepresentation(std::move(data));
    case 886:
      return new ::Ifc4x2::IfcRepresentationContext(std::move(data));
    case 887:
      return new ::Ifc4x2::IfcRepresentationItem(std::move(data));
    case 888:
      return new ::Ifc4x2::IfcRepresentationMap(std::move(data));
    case 889:
      return new ::Ifc4x2::IfcResource(std::move(data));
    case 890:
      return new ::Ifc4x2::IfcResourceApprovalRelationship(std::move(data));
    case 891:
      return new ::Ifc4x2::IfcResourceConstraintRelationship(std::move(data));
    case 892:
      return new ::Ifc4x2::IfcResourceLevelRelationship(std::move(data));
    case 895:
      return new ::Ifc4x2::IfcResourceTime(std::move(data));
    case 896:
      return new ::Ifc4x2::IfcRevolvedAreaSolid(std::move(data));
    case 897:
      return new ::Ifc4x2::IfcRevolvedAreaSolidTapered(std::move(data));
    case 898:
      return new ::Ifc4x2::IfcRightCircularCone(std::move(data));
    case 899:
      return new ::Ifc4x2::IfcRightCircularCylinder(std::move(data));
    case 900:
      return new ::Ifc4x2::IfcRoleEnum(std::move(data));
    case 901:
      return new ::Ifc4x2::IfcRoof(std::move(data));
    case 902:
      return new ::Ifc4x2::IfcRoofType(std::move(data));
    case 903:
      return new ::Ifc4x2::IfcRoofTypeEnum(std::move(data));
    case 904:
      return new ::Ifc4x2::IfcRoot(std::move(data));
    case 905:
      return new ::Ifc4x2::IfcRotationalFrequencyMeasure(std::move(data));
    case 906:
      return new ::Ifc4x2::IfcRotationalMassMeasure(std::move(data));
    case 907:
      return new ::Ifc4x2::IfcRotationalStiffnessMeasure(std::move(data));
    case 909:
      return new ::Ifc4x2::IfcRoundedRectangleProfileDef(std::move(data));
    case 910:
      return new ::Ifc4x2::IfcSanitaryTerminal(std::move(data));
    case 911:
      return new ::Ifc4x2::IfcSanitaryTerminalType(std::move(data));
    case 912:
      return new ::Ifc4x2::IfcSanitaryTerminalTypeEnum(std::move(data));
    case 913:
      return new ::Ifc4x2::IfcSchedulingTime(std::move(data));
    case 914:
      return new ::Ifc4x2::IfcSeamCurve(std::move(data));
    case 915:
      return new ::Ifc4x2::IfcSectionalAreaIntegralMeasure(std::move(data));
    case 916:
      return new ::Ifc4x2::IfcSectionedSolid(std::move(data));
    case 917:
      return new ::Ifc4x2::IfcSectionedSolidHorizontal(std::move(data));
    case 918:
      return new ::Ifc4x2::IfcSectionedSpine(std::move(data));
    case 919:
      return new ::Ifc4x2::IfcSectionModulusMeasure(std::move(data));
    case 920:
      return new ::Ifc4x2::IfcSectionProperties(std::move(data));
    case 921:
      return new ::Ifc4x2::IfcSectionReinforcementProperties(std::move(data));
    case 922:
      return new ::Ifc4x2::IfcSectionTypeEnum(std::move(data));
    case 924:
      return new ::Ifc4x2::IfcSensor(std::move(data));
    case 925:
      return new ::Ifc4x2::IfcSensorType(std::move(data));
    case 926:
      return new ::Ifc4x2::IfcSensorTypeEnum(std::move(data));
    case 927:
      return new ::Ifc4x2::IfcSequenceEnum(std::move(data));
    case 928:
      return new ::Ifc4x2::IfcShadingDevice(std::move(data));
    case 929:
      return new ::Ifc4x2::IfcShadingDeviceType(std::move(data));
    case 930:
      return new ::Ifc4x2::IfcShadingDeviceTypeEnum(std::move(data));
    case 931:
      return new ::Ifc4x2::IfcShapeAspect(std::move(data));
    case 932:
      return new ::Ifc4x2::IfcShapeModel(std::move(data));
    case 933:
      return new ::Ifc4x2::IfcShapeRepresentation(std::move(data));
    case 934:
      return new ::Ifc4x2::IfcShearModulusMeasure(std::move(data));
    case 936:
      return new ::Ifc4x2::IfcShellBasedSurfaceModel(std::move(data));
    case 937:
      return new ::Ifc4x2::IfcSimpleProperty(std::move(data));
    case 938:
      return new ::Ifc4x2::IfcSimplePropertyTemplate(std::move(data));
    case 939:
      return new ::Ifc4x2::IfcSimplePropertyTemplateTypeEnum(std::move(data));
    case 941:
      return new ::Ifc4x2::IfcSIPrefix(std::move(data));
    case 942:
      return new ::Ifc4x2::IfcSite(std::move(data));
    case 943:
      return new ::Ifc4x2::IfcSIUnit(std::move(data));
    case 944:
      return new ::Ifc4x2::IfcSIUnitName(std::move(data));
    case 946:
      return new ::Ifc4x2::IfcSlab(std::move(data));
    case 947:
      return new ::Ifc4x2::IfcSlabElementedCase(std::move(data));
    case 948:
      return new ::Ifc4x2::IfcSlabStandardCase(std::move(data));
    case 949:
      return new ::Ifc4x2::IfcSlabType(std::move(data));
    case 950:
      return new ::Ifc4x2::IfcSlabTypeEnum(std::move(data));
    case 951:
      return new ::Ifc4x2::IfcSlippageConnectionCondition(std::move(data));
    case 952:
      return new ::Ifc4x2::IfcSolarDevice(std::move(data));
    case 953:
      return new ::Ifc4x2::IfcSolarDeviceType(std::move(data));
    case 954:
      return new ::Ifc4x2::IfcSolarDeviceTypeEnum(std::move(data));
    case 955:
      return new ::Ifc4x2::IfcSolidAngleMeasure(std::move(data));
    case 956:
      return new ::Ifc4x2::IfcSolidModel(std::move(data));
    case 958:
      return new ::Ifc4x2::IfcSoundPowerLevelMeasure(std::move(data));
    case 959:
      return new ::Ifc4x2::IfcSoundPowerMeasure(std::move(data));
    case 960:
      return new ::Ifc4x2::IfcSoundPressureLevelMeasure(std::move(data));
    case 961:
      return new ::Ifc4x2::IfcSoundPressureMeasure(std::move(data));
    case 962:
      return new ::Ifc4x2::IfcSpace(std::move(data));
    case 964:
      return new ::Ifc4x2::IfcSpaceHeater(std::move(data));
    case 965:
      return new ::Ifc4x2::IfcSpaceHeaterType(std::move(data));
    case 966:
      return new ::Ifc4x2::IfcSpaceHeaterTypeEnum(std::move(data));
    case 967:
      return new ::Ifc4x2::IfcSpaceType(std::move(data));
    case 968:
      return new ::Ifc4x2::IfcSpaceTypeEnum(std::move(data));
    case 969:
      return new ::Ifc4x2::IfcSpatialElement(std::move(data));
    case 970:
      return new ::Ifc4x2::IfcSpatialElementType(std::move(data));
    case 971:
      return new ::Ifc4x2::IfcSpatialStructureElement(std::move(data));
    case 972:
      return new ::Ifc4x2::IfcSpatialStructureElementType(std::move(data));
    case 973:
      return new ::Ifc4x2::IfcSpatialZone(std::move(data));
    case 974:
      return new ::Ifc4x2::IfcSpatialZoneType(std::move(data));
    case 975:
      return new ::Ifc4x2::IfcSpatialZoneTypeEnum(std::move(data));
    case 976:
      return new ::Ifc4x2::IfcSpecificHeatCapacityMeasure(std::move(data));
    case 977:
      return new ::Ifc4x2::IfcSpecularExponent(std::move(data));
    case 979:
      return new ::Ifc4x2::IfcSpecularRoughness(std::move(data));
    case 980:
      return new ::Ifc4x2::IfcSphere(std::move(data));
    case 981:
      return new ::Ifc4x2::IfcSphericalSurface(std::move(data));
    case 982:
      return new ::Ifc4x2::IfcStackTerminal(std::move(data));
    case 983:
      return new ::Ifc4x2::IfcStackTerminalType(std::move(data));
    case 984:
      return new ::Ifc4x2::IfcStackTerminalTypeEnum(std::move(data));
    case 985:
      return new ::Ifc4x2::IfcStair(std::move(data));
    case 986:
      return new ::Ifc4x2::IfcStairFlight(std::move(data));
    case 987:
      return new ::Ifc4x2::IfcStairFlightType(std::move(data));
    case 988:
      return new ::Ifc4x2::IfcStairFlightTypeEnum(std::move(data));
    case 989:
      return new ::Ifc4x2::IfcStairType(std::move(data));
    case 990:
      return new ::Ifc4x2::IfcStairTypeEnum(std::move(data));
    case 991:
      return new ::Ifc4x2::IfcStateEnum(std::move(data));
    case 992:
      return new ::Ifc4x2::IfcStructuralAction(std::move(data));
    case 993:
      return new ::Ifc4x2::IfcStructuralActivity(std::move(data));
    case 995:
      return new ::Ifc4x2::IfcStructuralAnalysisModel(std::move(data));
    case 996:
      return new ::Ifc4x2::IfcStructuralConnection(std::move(data));
    case 997:
      return new ::Ifc4x2::IfcStructuralConnectionCondition(std::move(data));
    case 998:
      return new ::Ifc4x2::IfcStructuralCurveAction(std::move(data));
    case 999:
      return new ::Ifc4x2::IfcStructuralCurveActivityTypeEnum(std::move(data));
    case 1000:
      return new ::Ifc4x2::IfcStructuralCurveConnection(std::move(data));
    case 1001:
      return new ::Ifc4x2::IfcStructuralCurveMember(std::move(data));
    case 1002:
      return new ::Ifc4x2::IfcStructuralCurveMemberTypeEnum(std::move(data));
    case 1003:
      return new ::Ifc4x2::IfcStructuralCurveMemberVarying(std::move(data));
    case 1004:
      return new ::Ifc4x2::IfcStructuralCurveReaction(std::move(data));
    case 1005:
      return new ::Ifc4x2::IfcStructuralItem(std::move(data));
    case 1006:
      return new ::Ifc4x2::IfcStructuralLinearAction(std::move(data));
    case 1007:
      return new ::Ifc4x2::IfcStructuralLoad(std::move(data));
    case 1008:
      return new ::Ifc4x2::IfcStructuralLoadCase(std::move(data));
    case 1009:
      return new ::Ifc4x2::IfcStructuralLoadConfiguration(std::move(data));
    case 1010:
      return new ::Ifc4x2::IfcStructuralLoadGroup(std::move(data));
    case 1011:
      return new ::Ifc4x2::IfcStructuralLoadLinearForce(std::move(data));
    case 1012:
      return new ::Ifc4x2::IfcStructuralLoadOrResult(std::move(data));
    case 1013:
      return new ::Ifc4x2::IfcStructuralLoadPlanarForce(std::move(data));
    case 1014:
      return new ::Ifc4x2::IfcStructuralLoadSingleDisplacement(std::move(data));
    case 1015:
      return new ::Ifc4x2::IfcStructuralLoadSingleDisplacementDistortion(
          std::move(data));
    case 1016:
      return new ::Ifc4x2::IfcStructuralLoadSingleForce(std::move(data));
    case 1017:
      return new ::Ifc4x2::IfcStructuralLoadSingleForceWarping(std::move(data));
    case 1018:
      return new ::Ifc4x2::IfcStructuralLoadStatic(std::move(data));
    case 1019:
      return new ::Ifc4x2::IfcStructuralLoadTemperature(std::move(data));
    case 1020:
      return new ::Ifc4x2::IfcStructuralMember(std::move(data));
    case 1021:
      return new ::Ifc4x2::IfcStructuralPlanarAction(std::move(data));
    case 1022:
      return new ::Ifc4x2::IfcStructuralPointAction(std::move(data));
    case 1023:
      return new ::Ifc4x2::IfcStructuralPointConnection(std::move(data));
    case 1024:
      return new ::Ifc4x2::IfcStructuralPointReaction(std::move(data));
    case 1025:
      return new ::Ifc4x2::IfcStructuralReaction(std::move(data));
    case 1026:
      return new ::Ifc4x2::IfcStructuralResultGroup(std::move(data));
    case 1027:
      return new ::Ifc4x2::IfcStructuralSurfaceAction(std::move(data));
    case 1028:
      return new ::Ifc4x2::IfcStructuralSurfaceActivityTypeEnum(
          std::move(data));
    case 1029:
      return new ::Ifc4x2::IfcStructuralSurfaceConnection(std::move(data));
    case 1030:
      return new ::Ifc4x2::IfcStructuralSurfaceMember(std::move(data));
    case 1031:
      return new ::Ifc4x2::IfcStructuralSurfaceMemberTypeEnum(std::move(data));
    case 1032:
      return new ::Ifc4x2::IfcStructuralSurfaceMemberVarying(std::move(data));
    case 1033:
      return new ::Ifc4x2::IfcStructuralSurfaceReaction(std::move(data));
    case 1035:
      return new ::Ifc4x2::IfcStyledItem(std::move(data));
    case 1036:
      return new ::Ifc4x2::IfcStyledRepresentation(std::move(data));
    case 1037:
      return new ::Ifc4x2::IfcStyleModel(std::move(data));
    case 1038:
      return new ::Ifc4x2::IfcSubContractResource(std::move(data));
    case 1039:
      return new ::Ifc4x2::IfcSubContractResourceType(std::move(data));
    case 1040:
      return new ::Ifc4x2::IfcSubContractResourceTypeEnum(std::move(data));
    case 1041:
      return new ::Ifc4x2::IfcSubedge(std::move(data));
    case 1042:
      return new ::Ifc4x2::IfcSurface(std::move(data));
    case 1043:
      return new ::Ifc4x2::IfcSurfaceCurve(std::move(data));
    case 1044:
      return new ::Ifc4x2::IfcSurfaceCurveSweptAreaSolid(std::move(data));
    case 1045:
      return new ::Ifc4x2::IfcSurfaceFeature(std::move(data));
    case 1046:
      return new ::Ifc4x2::IfcSurfaceFeatureTypeEnum(std::move(data));
    case 1047:
      return new ::Ifc4x2::IfcSurfaceOfLinearExtrusion(std::move(data));
    case 1048:
      return new ::Ifc4x2::IfcSurfaceOfRevolution(std::move(data));
    case 1050:
      return new ::Ifc4x2::IfcSurfaceReinforcementArea(std::move(data));
    case 1051:
      return new ::Ifc4x2::IfcSurfaceSide(std::move(data));
    case 1052:
      return new ::Ifc4x2::IfcSurfaceStyle(std::move(data));
    case 1054:
      return new ::Ifc4x2::IfcSurfaceStyleLighting(std::move(data));
    case 1055:
      return new ::Ifc4x2::IfcSurfaceStyleRefraction(std::move(data));
    case 1056:
      return new ::Ifc4x2::IfcSurfaceStyleRendering(std::move(data));
    case 1057:
      return new ::Ifc4x2::IfcSurfaceStyleShading(std::move(data));
    case 1058:
      return new ::Ifc4x2::IfcSurfaceStyleWithTextures(std::move(data));
    case 1059:
      return new ::Ifc4x2::IfcSurfaceTexture(std::move(data));
    case 1060:
      return new ::Ifc4x2::IfcSweptAreaSolid(std::move(data));
    case 1061:
      return new ::Ifc4x2::IfcSweptDiskSolid(std::move(data));
    case 1062:
      return new ::Ifc4x2::IfcSweptDiskSolidPolygonal(std::move(data));
    case 1063:
      return new ::Ifc4x2::IfcSweptSurface(std::move(data));
    case 1064:
      return new ::Ifc4x2::IfcSwitchingDevice(std::move(data));
    case 1065:
      return new ::Ifc4x2::IfcSwitchingDeviceType(std::move(data));
    case 1066:
      return new ::Ifc4x2::IfcSwitchingDeviceTypeEnum(std::move(data));
    case 1067:
      return new ::Ifc4x2::IfcSystem(std::move(data));
    case 1068:
      return new ::Ifc4x2::IfcSystemFurnitureElement(std::move(data));
    case 1069:
      return new ::Ifc4x2::IfcSystemFurnitureElementType(std::move(data));
    case 1070:
      return new ::Ifc4x2::IfcSystemFurnitureElementTypeEnum(std::move(data));
    case 1071:
      return new ::Ifc4x2::IfcTable(std::move(data));
    case 1072:
      return new ::Ifc4x2::IfcTableColumn(std::move(data));
    case 1073:
      return new ::Ifc4x2::IfcTableRow(std::move(data));
    case 1074:
      return new ::Ifc4x2::IfcTank(std::move(data));
    case 1075:
      return new ::Ifc4x2::IfcTankType(std::move(data));
    case 1076:
      return new ::Ifc4x2::IfcTankTypeEnum(std::move(data));
    case 1077:
      return new ::Ifc4x2::IfcTask(std::move(data));
    case 1078:
      return new ::Ifc4x2::IfcTaskDurationEnum(std::move(data));
    case 1079:
      return new ::Ifc4x2::IfcTaskTime(std::move(data));
    case 1080:
      return new ::Ifc4x2::IfcTaskTimeRecurring(std::move(data));
    case 1081:
      return new ::Ifc4x2::IfcTaskType(std::move(data));
    case 1082:
      return new ::Ifc4x2::IfcTaskTypeEnum(std::move(data));
    case 1083:
      return new ::Ifc4x2::IfcTelecomAddress(std::move(data));
    case 1084:
      return new ::Ifc4x2::IfcTemperatureGradientMeasure(std::move(data));
    case 1085:
      return new ::Ifc4x2::IfcTemperatureRateOfChangeMeasure(std::move(data));
    case 1086:
      return new ::Ifc4x2::IfcTendon(std::move(data));
    case 1087:
      return new ::Ifc4x2::IfcTendonAnchor(std::move(data));
    case 1088:
      return new ::Ifc4x2::IfcTendonAnchorType(std::move(data));
    case 1089:
      return new ::Ifc4x2::IfcTendonAnchorTypeEnum(std::move(data));
    case 1090:
      return new ::Ifc4x2::IfcTendonConduit(std::move(data));
    case 1091:
      return new ::Ifc4x2::IfcTendonConduitType(std::move(data));
    case 1092:
      return new ::Ifc4x2::IfcTendonConduitTypeEnum(std::move(data));
    case 1093:
      return new ::Ifc4x2::IfcTendonType(std::move(data));
    case 1094:
      return new ::Ifc4x2::IfcTendonTypeEnum(std::move(data));
    case 1095:
      return new ::Ifc4x2::IfcTessellatedFaceSet(std::move(data));
    case 1096:
      return new ::Ifc4x2::IfcTessellatedItem(std::move(data));
    case 1097:
      return new ::Ifc4x2::IfcText(std::move(data));
    case 1098:
      return new ::Ifc4x2::IfcTextAlignment(std::move(data));
    case 1099:
      return new ::Ifc4x2::IfcTextDecoration(std::move(data));
    case 1100:
      return new ::Ifc4x2::IfcTextFontName(std::move(data));
    case 1102:
      return new ::Ifc4x2::IfcTextLiteral(std::move(data));
    case 1103:
      return new ::Ifc4x2::IfcTextLiteralWithExtent(std::move(data));
    case 1104:
      return new ::Ifc4x2::IfcTextPath(std::move(data));
    case 1105:
      return new ::Ifc4x2::IfcTextStyle(std::move(data));
    case 1106:
      return new ::Ifc4x2::IfcTextStyleFontModel(std::move(data));
    case 1107:
      return new ::Ifc4x2::IfcTextStyleForDefinedFont(std::move(data));
    case 1108:
      return new ::Ifc4x2::IfcTextStyleTextModel(std::move(data));
    case 1109:
      return new ::Ifc4x2::IfcTextTransformation(std::move(data));
    case 1110:
      return new ::Ifc4x2::IfcTextureCoordinate(std::move(data));
    case 1111:
      return new ::Ifc4x2::IfcTextureCoordinateGenerator(std::move(data));
    case 1112:
      return new ::Ifc4x2::IfcTextureMap(std::move(data));
    case 1113:
      return new ::Ifc4x2::IfcTextureVertex(std::move(data));
    case 1114:
      return new ::Ifc4x2::IfcTextureVertexList(std::move(data));
    case 1115:
      return new ::Ifc4x2::IfcThermalAdmittanceMeasure(std::move(data));
    case 1116:
      return new ::Ifc4x2::IfcThermalConductivityMeasure(std::move(data));
    case 1117:
      return new ::Ifc4x2::IfcThermalExpansionCoefficientMeasure(
          std::move(data));
    case 1118:
      return new ::Ifc4x2::IfcThermalResistanceMeasure(std::move(data));
    case 1119:
      return new ::Ifc4x2::IfcThermalTransmittanceMeasure(std::move(data));
    case 1120:
      return new ::Ifc4x2::IfcThermodynamicTemperatureMeasure(std::move(data));
    case 1121:
      return new ::Ifc4x2::IfcTime(std::move(data));
    case 1122:
      return new ::Ifc4x2::IfcTimeMeasure(std::move(data));
    case 1124:
      return new ::Ifc4x2::IfcTimePeriod(std::move(data));
    case 1125:
      return new ::Ifc4x2::IfcTimeSeries(std::move(data));
    case 1126:
      return new ::Ifc4x2::IfcTimeSeriesDataTypeEnum(std::move(data));
    case 1127:
      return new ::Ifc4x2::IfcTimeSeriesValue(std::move(data));
    case 1128:
      return new ::Ifc4x2::IfcTimeStamp(std::move(data));
    case 1129:
      return new ::Ifc4x2::IfcTopologicalRepresentationItem(std::move(data));
    case 1130:
      return new ::Ifc4x2::IfcTopologyRepresentation(std::move(data));
    case 1131:
      return new ::Ifc4x2::IfcToroidalSurface(std::move(data));
    case 1132:
      return new ::Ifc4x2::IfcTorqueMeasure(std::move(data));
    case 1133:
      return new ::Ifc4x2::IfcTransformer(std::move(data));
    case 1134:
      return new ::Ifc4x2::IfcTransformerType(std::move(data));
    case 1135:
      return new ::Ifc4x2::IfcTransformerTypeEnum(std::move(data));
    case 1136:
      return new ::Ifc4x2::IfcTransitionCode(std::move(data));
    case 1137:
      return new ::Ifc4x2::IfcTransitionCurveSegment2D(std::move(data));
    case 1138:
      return new ::Ifc4x2::IfcTransitionCurveType(std::move(data));
    case 1140:
      return new ::Ifc4x2::IfcTransportElement(std::move(data));
    case 1141:
      return new ::Ifc4x2::IfcTransportElementType(std::move(data));
    case 1142:
      return new ::Ifc4x2::IfcTransportElementTypeEnum(std::move(data));
    case 1143:
      return new ::Ifc4x2::IfcTrapeziumProfileDef(std::move(data));
    case 1144:
      return new ::Ifc4x2::IfcTriangulatedFaceSet(std::move(data));
    case 1145:
      return new ::Ifc4x2::IfcTriangulatedIrregularNetwork(std::move(data));
    case 1146:
      return new ::Ifc4x2::IfcTrimmedCurve(std::move(data));
    case 1147:
      return new ::Ifc4x2::IfcTrimmingPreference(std::move(data));
    case 1149:
      return new ::Ifc4x2::IfcTShapeProfileDef(std::move(data));
    case 1150:
      return new ::Ifc4x2::IfcTubeBundle(std::move(data));
    case 1151:
      return new ::Ifc4x2::IfcTubeBundleType(std::move(data));
    case 1152:
      return new ::Ifc4x2::IfcTubeBundleTypeEnum(std::move(data));
    case 1153:
      return new ::Ifc4x2::IfcTypeObject(std::move(data));
    case 1154:
      return new ::Ifc4x2::IfcTypeProcess(std::move(data));
    case 1155:
      return new ::Ifc4x2::IfcTypeProduct(std::move(data));
    case 1156:
      return new ::Ifc4x2::IfcTypeResource(std::move(data));
    case 1158:
      return new ::Ifc4x2::IfcUnitaryControlElement(std::move(data));
    case 1159:
      return new ::Ifc4x2::IfcUnitaryControlElementType(std::move(data));
    case 1160:
      return new ::Ifc4x2::IfcUnitaryControlElementTypeEnum(std::move(data));
    case 1161:
      return new ::Ifc4x2::IfcUnitaryEquipment(std::move(data));
    case 1162:
      return new ::Ifc4x2::IfcUnitaryEquipmentType(std::move(data));
    case 1163:
      return new ::Ifc4x2::IfcUnitaryEquipmentTypeEnum(std::move(data));
    case 1164:
      return new ::Ifc4x2::IfcUnitAssignment(std::move(data));
    case 1165:
      return new ::Ifc4x2::IfcUnitEnum(std::move(data));
    case 1166:
      return new ::Ifc4x2::IfcURIReference(std::move(data));
    case 1167:
      return new ::Ifc4x2::IfcUShapeProfileDef(std::move(data));
    case 1169:
      return new ::Ifc4x2::IfcValve(std::move(data));
    case 1170:
      return new ::Ifc4x2::IfcValveType(std::move(data));
    case 1171:
      return new ::Ifc4x2::IfcValveTypeEnum(std::move(data));
    case 1172:
      return new ::Ifc4x2::IfcVaporPermeabilityMeasure(std::move(data));
    case 1173:
      return new ::Ifc4x2::IfcVector(std::move(data));
    case 1175:
      return new ::Ifc4x2::IfcVertex(std::move(data));
    case 1176:
      return new ::Ifc4x2::IfcVertexLoop(std::move(data));
    case 1177:
      return new ::Ifc4x2::IfcVertexPoint(std::move(data));
    case 1178:
      return new ::Ifc4x2::IfcVibrationDamper(std::move(data));
    case 1179:
      return new ::Ifc4x2::IfcVibrationDamperType(std::move(data));
    case 1180:
      return new ::Ifc4x2::IfcVibrationDamperTypeEnum(std::move(data));
    case 1181:
      return new ::Ifc4x2::IfcVibrationIsolator(std::move(data));
    case 1182:
      return new ::Ifc4x2::IfcVibrationIsolatorType(std::move(data));
    case 1183:
      return new ::Ifc4x2::IfcVibrationIsolatorTypeEnum(std::move(data));
    case 1184:
      return new ::Ifc4x2::IfcVirtualElement(std::move(data));
    case 1185:
      return new ::Ifc4x2::IfcVirtualGridIntersection(std::move(data));
    case 1186:
      return new ::Ifc4x2::IfcVoidingFeature(std::move(data));
    case 1187:
      return new ::Ifc4x2::IfcVoidingFeatureTypeEnum(std::move(data));
    case 1188:
      return new ::Ifc4x2::IfcVolumeMeasure(std::move(data));
    case 1189:
      return new ::Ifc4x2::IfcVolumetricFlowRateMeasure(std::move(data));
    case 1190:
      return new ::Ifc4x2::IfcWall(std::move(data));
    case 1191:
      return new ::Ifc4x2::IfcWallElementedCase(std::move(data));
    case 1192:
      return new ::Ifc4x2::IfcWallStandardCase(std::move(data));
    case 1193:
      return new ::Ifc4x2::IfcWallType(std::move(data));
    case 1194:
      return new ::Ifc4x2::IfcWallTypeEnum(std::move(data));
    case 1195:
      return new ::Ifc4x2::IfcWarpingConstantMeasure(std::move(data));
    case 1196:
      return new ::Ifc4x2::IfcWarpingMomentMeasure(std::move(data));
    case 1198:
      return new ::Ifc4x2::IfcWasteTerminal(std::move(data));
    case 1199:
      return new ::Ifc4x2::IfcWasteTerminalType(std::move(data));
    case 1200:
      return new ::Ifc4x2::IfcWasteTerminalTypeEnum(std::move(data));
    case 1201:
      return new ::Ifc4x2::IfcWindow(std::move(data));
    case 1202:
      return new ::Ifc4x2::IfcWindowLiningProperties(std::move(data));
    case 1203:
      return new ::Ifc4x2::IfcWindowPanelOperationEnum(std::move(data));
    case 1204:
      return new ::Ifc4x2::IfcWindowPanelPositionEnum(std::move(data));
    case 1205:
      return new ::Ifc4x2::IfcWindowPanelProperties(std::move(data));
    case 1206:
      return new ::Ifc4x2::IfcWindowStandardCase(std::move(data));
    case 1207:
      return new ::Ifc4x2::IfcWindowStyle(std::move(data));
    case 1208:
      return new ::Ifc4x2::IfcWindowStyleConstructionEnum(std::move(data));
    case 1209:
      return new ::Ifc4x2::IfcWindowStyleOperationEnum(std::move(data));
    case 1210:
      return new ::Ifc4x2::IfcWindowType(std::move(data));
    case 1211:
      return new ::Ifc4x2::IfcWindowTypeEnum(std::move(data));
    case 1212:
      return new ::Ifc4x2::IfcWindowTypePartitioningEnum(std::move(data));
    case 1213:
      return new ::Ifc4x2::IfcWorkCalendar(std::move(data));
    case 1214:
      return new ::Ifc4x2::IfcWorkCalendarTypeEnum(std::move(data));
    case 1215:
      return new ::Ifc4x2::IfcWorkControl(std::move(data));
    case 1216:
      return new ::Ifc4x2::IfcWorkPlan(std::move(data));
    case 1217:
      return new ::Ifc4x2::IfcWorkPlanTypeEnum(std::move(data));
    case 1218:
      return new ::Ifc4x2::IfcWorkSchedule(std::move(data));
    case 1219:
      return new ::Ifc4x2::IfcWorkScheduleTypeEnum(std::move(data));
    case 1220:
      return new ::Ifc4x2::IfcWorkTime(std::move(data));
    case 1221:
      return new ::Ifc4x2::IfcZone(std::move(data));
    case 1222:
      return new ::Ifc4x2::IfcZShapeProfileDef(std::move(data));
    default:
      throw IfcParse::IfcException(decl->name() + " cannot be instantiated");
    }
  }
};

IfcParse::schema_definition *IFC4X2_populate_schema() {
  IFC4X2_types[0] = new type_declaration(
      strings[0], 0, new simple_type(simple_type::real_type));
  IFC4X2_types[1] = new type_declaration(
      strings[1], 1, new simple_type(simple_type::real_type));
  IFC4X2_types[3] =
      new enumeration_type(strings[2], 3,
                           {strings[3], strings[4], strings[5], strings[6],
                            strings[7], strings[8], strings[9]});
  IFC4X2_types[4] = new enumeration_type(
      strings[10], 4,
      {strings[11], strings[12], strings[13], strings[14], strings[15],
       strings[16], strings[17], strings[18], strings[19], strings[20],
       strings[21], strings[22], strings[23], strings[24], strings[25],
       strings[26], strings[27], strings[28], strings[29], strings[30],
       strings[31], strings[32], strings[33], strings[34], strings[35],
       strings[8],  strings[9]});
  IFC4X2_types[5] = new enumeration_type(
      strings[36], 5,
      {strings[37], strings[38], strings[39], strings[8], strings[9]});
  IFC4X2_types[11] =
      new enumeration_type(strings[40], 11,
                           {strings[41], strings[42], strings[43], strings[44],
                            strings[45], strings[8], strings[9]});
  IFC4X2_types[13] = new enumeration_type(
      strings[46], 13,
      {strings[47], strings[48], strings[49], strings[50], strings[8]});
  IFC4X2_types[20] = new enumeration_type(
      strings[51], 20,
      {strings[52], strings[53], strings[54], strings[8], strings[9]});
  IFC4X2_types[22] =
      new enumeration_type(strings[55], 22,
                           {strings[56], strings[57], strings[58], strings[59],
                            strings[8], strings[9]});
  IFC4X2_types[25] =
      new enumeration_type(strings[60], 25,
                           {strings[61], strings[62], strings[63], strings[64],
                            strings[65], strings[66], strings[67], strings[68],
                            strings[69], strings[8], strings[9]});
  IFC4X2_types[28] =
      new enumeration_type(strings[70], 28,
                           {strings[71], strings[72], strings[73], strings[74],
                            strings[75], strings[76], strings[8], strings[9]});
  IFC4X2_types[39] =
      new enumeration_type(strings[77], 39, {strings[8], strings[9]});
  IFC4X2_types[40] = new type_declaration(
      strings[78], 40, new simple_type(simple_type::real_type));
  IFC4X2_types[41] = new enumeration_type(
      strings[79], 41,
      {strings[80], strings[81], strings[82], strings[8], strings[9]});
  IFC4X2_types[42] =
      new enumeration_type(strings[83], 42,
                           {strings[84], strings[85], strings[86], strings[87],
                            strings[8], strings[9]});
  IFC4X2_types[43] = new type_declaration(
      strings[88], 43, new simple_type(simple_type::real_type));
  IFC4X2_types[55] = new type_declaration(
      strings[89], 55, new simple_type(simple_type::real_type));
  IFC4X2_types[56] = new type_declaration(
      strings[90], 56, new simple_type(simple_type::real_type));
  IFC4X2_types[57] = new enumeration_type(
      strings[91], 57, {strings[92], strings[93], strings[94], strings[95]});
  IFC4X2_types[58] = new enumeration_type(
      strings[96], 58, {strings[48], strings[97], strings[9]});
  IFC4X2_types[63] = new enumeration_type(
      strings[98], 63,
      {strings[99], strings[100], strings[101], strings[102], strings[103],
       strings[104], strings[105], strings[106], strings[107], strings[108],
       strings[109], strings[8], strings[9]});
  IFC4X2_types[105] =
      new enumeration_type(strings[110], 105,
                           {strings[111], strings[112], strings[113],
                            strings[114], strings[115], strings[116]});
  IFC4X2_types[108] = new enumeration_type(
      strings[117], 108,
      {strings[118], strings[119], strings[120], strings[121], strings[122],
       strings[123], strings[124], strings[125], strings[126], strings[127],
       strings[116]});
  IFC4X2_types[71] = new enumeration_type(
      strings[128], 71,
      {strings[129], strings[130], strings[131], strings[132], strings[133],
       strings[134], strings[135], strings[136], strings[137], strings[138],
       strings[139], strings[140], strings[8], strings[9]});
  IFC4X2_types[74] = new enumeration_type(
      strings[141], 74,
      {strings[142], strings[143], strings[144], strings[145], strings[9]});
  IFC4X2_types[75] = new enumeration_type(
      strings[146], 75,
      {strings[147], strings[148], strings[149], strings[150], strings[151],
       strings[152], strings[153], strings[154], strings[8], strings[9]});
  IFC4X2_types[76] = new enumeration_type(
      strings[155], 76,
      {strings[156], strings[157], strings[158], strings[159], strings[160],
       strings[161], strings[162], strings[163], strings[164], strings[165]});
  IFC4X2_types[78] = new type_declaration(
      strings[166], 78, new simple_type(simple_type::binary_type));
  IFC4X2_types[83] = new enumeration_type(
      strings[167], 83, {strings[168], strings[169], strings[8], strings[9]});
  IFC4X2_types[84] = new type_declaration(
      strings[170], 84, new simple_type(simple_type::boolean_type));
  IFC4X2_types[87] = new enumeration_type(
      strings[171], 87, {strings[172], strings[173], strings[174]});
  IFC4X2_types[102] = new enumeration_type(
      strings[175], 102,
      {strings[176], strings[177], strings[178], strings[179], strings[180],
       strings[181], strings[182], strings[183], strings[184], strings[185],
       strings[8], strings[9]});
  IFC4X2_types[103] = new enumeration_type(
      strings[186], 103,
      {strings[187], strings[188], strings[189], strings[190], strings[191],
       strings[192], strings[193], strings[194], strings[8], strings[9]});
  IFC4X2_types[114] = new enumeration_type(
      strings[195], 114,
      {strings[196], strings[197], strings[198], strings[8], strings[9]});
  IFC4X2_types[117] = new enumeration_type(
      strings[199], 117,
      {strings[200], strings[201], strings[202], strings[203], strings[204],
       strings[8], strings[9]});
  IFC4X2_types[121] = new enumeration_type(
      strings[205], 121,
      {strings[206], strings[179], strings[207], strings[208], strings[209],
       strings[23], strings[210], strings[211], strings[8], strings[9]});
  IFC4X2_types[124] =
      new enumeration_type(strings[212], 124, {strings[8], strings[9]});
  IFC4X2_types[127] =
      new enumeration_type(strings[213], 127,
                           {strings[214], strings[215], strings[216],
                            strings[217], strings[8], strings[9]});
  IFC4X2_types[130] =
      new enumeration_type(strings[218], 130,
                           {strings[219], strings[220], strings[221],
                            strings[222], strings[8], strings[9]});
  IFC4X2_types[133] = new enumeration_type(
      strings[223], 133,
      {strings[224], strings[225], strings[226], strings[227], strings[228],
       strings[8], strings[9]});
  IFC4X2_types[136] =
      new enumeration_type(strings[229], 136,
                           {strings[230], strings[231], strings[232],
                            strings[233], strings[8], strings[9]});
  IFC4X2_types[139] = new enumeration_type(
      strings[234], 139, {strings[235], strings[236], strings[8], strings[9]});
  IFC4X2_types[140] = new type_declaration(
      strings[237], 140, new simple_type(simple_type::integer_type));
  IFC4X2_types[151] = new enumeration_type(
      strings[238], 151,
      {strings[239], strings[240], strings[241], strings[242], strings[9]});
  IFC4X2_types[154] = new enumeration_type(
      strings[243], 154,
      {strings[244], strings[245], strings[246], strings[8], strings[9]});
  IFC4X2_types[157] =
      new enumeration_type(strings[247], 157, {strings[8], strings[9]});
  IFC4X2_types[171] = new enumeration_type(
      strings[248], 171,
      {strings[249], strings[250], strings[251], strings[252], strings[253],
       strings[254], strings[255], strings[8], strings[9]});
  IFC4X2_types[180] = new enumeration_type(
      strings[256], 180,
      {strings[257], strings[258], strings[259], strings[260], strings[261],
       strings[8], strings[9]});
  IFC4X2_types[183] = new enumeration_type(
      strings[262], 183,
      {strings[263], strings[264], strings[4], strings[265], strings[266],
       strings[267], strings[268], strings[269], strings[270], strings[271],
       strings[272], strings[273], strings[8], strings[9]});
  IFC4X2_types[184] = new type_declaration(
      strings[274], 184,
      new aggregation_type(aggregation_type::array_type, 1, 2,
                           new simple_type(simple_type::real_type)));
  IFC4X2_types[187] =
      new enumeration_type(strings[275], 187, {strings[276], strings[277]});
  IFC4X2_types[192] = new type_declaration(
      strings[278], 192,
      new aggregation_type(aggregation_type::list_type, 3, 4,
                           new simple_type(simple_type::integer_type)));
  IFC4X2_types[195] = new enumeration_type(
      strings[279], 195,
      {strings[280], strings[281], strings[282], strings[283], strings[284],
       strings[285], strings[286], strings[287], strings[288], strings[289],
       strings[290], strings[291], strings[292], strings[293], strings[294],
       strings[8], strings[9]});
  IFC4X2_types[198] = new enumeration_type(
      strings[295], 198,
      {strings[244], strings[296], strings[245], strings[297], strings[298],
       strings[299], strings[300], strings[8], strings[9]});
  IFC4X2_types[206] = new enumeration_type(
      strings[301], 206,
      {strings[302], strings[303], strings[304], strings[9]});
  IFC4X2_types[209] = new enumeration_type(
      strings[305], 209,
      {strings[306], strings[307], strings[308], strings[8], strings[9]});
  IFC4X2_types[212] = new enumeration_type(
      strings[309], 212,
      {strings[310], strings[311], strings[312], strings[313], strings[314],
       strings[315], strings[316], strings[317], strings[8], strings[9]});
  IFC4X2_types[215] = new enumeration_type(
      strings[318], 215,
      {strings[319], strings[320], strings[321], strings[322], strings[323],
       strings[324], strings[325], strings[326], strings[327], strings[9],
       strings[8]});
  IFC4X2_types[218] = new enumeration_type(
      strings[328], 218, {strings[329], strings[330], strings[8], strings[9]});
  IFC4X2_types[222] = new type_declaration(
      strings[331], 222, new simple_type(simple_type::real_type));
  IFC4X2_types[227] = new enumeration_type(
      strings[332], 227,
      {strings[333], strings[334], strings[335], strings[336], strings[337],
       strings[8], strings[9]});
  IFC4X2_types[232] = new enumeration_type(
      strings[338], 232, {strings[339], strings[340], strings[8], strings[9]});
  IFC4X2_types[235] = new enumeration_type(
      strings[341], 235,
      {strings[342], strings[343], strings[344], strings[8], strings[9]});
  IFC4X2_types[240] =
      new enumeration_type(strings[345], 240, {strings[8], strings[9]});
  IFC4X2_types[242] = new enumeration_type(
      strings[346], 242,
      {strings[347], strings[348], strings[349], strings[350], strings[351],
       strings[352], strings[353], strings[8], strings[9]});
  IFC4X2_types[244] = new type_declaration(
      strings[354], 244, new simple_type(simple_type::number_type));
  IFC4X2_types[247] = new enumeration_type(
      strings[355], 247,
      {strings[356], strings[357], strings[358], strings[359], strings[360],
       strings[361], strings[196], strings[362], strings[363], strings[364],
       strings[365], strings[8], strings[9]});
  IFC4X2_types[250] = new enumeration_type(
      strings[366], 250, {strings[47], strings[48], strings[8], strings[9]});
  IFC4X2_types[258] =
      new enumeration_type(strings[367], 258, {strings[8], strings[9]});
  IFC4X2_types[259] = new type_declaration(
      strings[368], 259, new simple_type(simple_type::real_type));
  IFC4X2_types[264] = new enumeration_type(
      strings[369], 264,
      {strings[370], strings[371], strings[372], strings[9]});
  IFC4X2_types[276] = new enumeration_type(
      strings[373], 276,
      {strings[374], strings[375], strings[376], strings[377], strings[378],
       strings[379], strings[380], strings[381], strings[382], strings[383],
       strings[384], strings[8], strings[9]});
  IFC4X2_types[277] = new enumeration_type(
      strings[385], 277,
      {strings[386], strings[387], strings[388], strings[8], strings[9]});
  IFC4X2_types[278] = new type_declaration(
      strings[389], 278, new simple_type(simple_type::string_type));
  IFC4X2_types[279] = new type_declaration(
      strings[390], 279, new simple_type(simple_type::string_type));
  IFC4X2_types[280] = new type_declaration(
      strings[391], 280, new simple_type(simple_type::integer_type));
  IFC4X2_types[281] = new type_declaration(
      strings[392], 281, new simple_type(simple_type::integer_type));
  IFC4X2_types[289] = new enumeration_type(
      strings[393], 289,
      {strings[394], strings[395], strings[396], strings[397], strings[398],
       strings[399], strings[400], strings[401], strings[402], strings[403],
       strings[404], strings[405], strings[406], strings[407], strings[408],
       strings[409], strings[410], strings[411], strings[412], strings[413],
       strings[414], strings[415], strings[416], strings[417], strings[418],
       strings[419], strings[420], strings[421], strings[422], strings[423],
       strings[424], strings[425], strings[426], strings[427], strings[428],
       strings[429], strings[430], strings[431], strings[432], strings[433],
       strings[434], strings[435], strings[436], strings[437], strings[438],
       strings[439], strings[440], strings[441], strings[442], strings[443],
       strings[444], strings[445], strings[8]});
  IFC4X2_types[290] = new type_declaration(
      strings[446], 290, new simple_type(simple_type::string_type));
  IFC4X2_types[292] = new type_declaration(
      strings[447], 292, new simple_type(simple_type::integer_type));
  IFC4X2_types[294] =
      new enumeration_type(strings[448], 294, {strings[449], strings[450]});
  IFC4X2_types[297] =
      new enumeration_type(strings[451], 297,
                           {strings[452], strings[453], strings[454],
                            strings[455], strings[8], strings[9]});
  IFC4X2_types[301] = new enumeration_type(
      strings[456], 301,
      {strings[457], strings[458], strings[459], strings[460], strings[461],
       strings[462], strings[463], strings[464], strings[8], strings[9]});
  IFC4X2_types[310] =
      new enumeration_type(strings[465], 310,
                           {strings[466], strings[467], strings[468],
                            strings[469], strings[8], strings[9]});
  IFC4X2_types[312] = new enumeration_type(
      strings[470], 312,
      {strings[471], strings[472], strings[473], strings[474], strings[475],
       strings[476], strings[477], strings[478], strings[479], strings[480],
       strings[481], strings[482], strings[483], strings[484], strings[485],
       strings[486], strings[487], strings[488], strings[489], strings[322],
       strings[490], strings[491], strings[313], strings[314], strings[492],
       strings[493], strings[494], strings[495], strings[496], strings[497],
       strings[498], strings[499], strings[500], strings[501], strings[502],
       strings[108], strings[503], strings[504], strings[505], strings[506],
       strings[507], strings[508], strings[8],   strings[9]});
  IFC4X2_types[313] =
      new enumeration_type(strings[509], 313,
                           {strings[510], strings[511], strings[512],
                            strings[513], strings[8], strings[9]});
  IFC4X2_types[318] = new enumeration_type(
      strings[514], 318,
      {strings[515], strings[516], strings[517], strings[518], strings[9]});
  IFC4X2_types[321] = new enumeration_type(
      strings[519], 321,
      {strings[520], strings[521], strings[522], strings[523], strings[524],
       strings[525], strings[526], strings[8], strings[9]});
  IFC4X2_types[322] = new enumeration_type(
      strings[527], 322,
      {strings[528], strings[529], strings[530], strings[9]});
  IFC4X2_types[326] = new enumeration_type(
      strings[531], 326,
      {strings[532], strings[533], strings[534], strings[327], strings[535],
       strings[536], strings[326], strings[8], strings[9]});
  IFC4X2_types[327] = new enumeration_type(
      strings[537], 327,
      {strings[538], strings[539], strings[540], strings[541], strings[542],
       strings[543], strings[544], strings[545], strings[546], strings[547],
       strings[548], strings[549], strings[550], strings[551], strings[524],
       strings[525], strings[8], strings[9]});
  IFC4X2_types[329] = new enumeration_type(
      strings[552], 329,
      {strings[553], strings[554], strings[555], strings[8], strings[9]});
  IFC4X2_types[330] = new enumeration_type(
      strings[556], 330,
      {strings[538], strings[539], strings[540], strings[541], strings[542],
       strings[543], strings[544], strings[545], strings[546], strings[547],
       strings[548], strings[549], strings[550], strings[551], strings[524],
       strings[525], strings[557], strings[558], strings[8],   strings[9]});
  IFC4X2_types[331] = new type_declaration(
      strings[559], 331, new simple_type(simple_type::real_type));
  IFC4X2_types[336] = new enumeration_type(
      strings[560], 336,
      {strings[214], strings[224], strings[225], strings[226], strings[227],
       strings[561], strings[228], strings[8], strings[9]});
  IFC4X2_types[339] = new enumeration_type(
      strings[562], 339, {strings[563], strings[564], strings[8], strings[9]});
  IFC4X2_types[342] = new enumeration_type(
      strings[565], 342,
      {strings[566], strings[567], strings[568], strings[8], strings[9]});
  IFC4X2_types[343] = new type_declaration(
      strings[569], 343, new simple_type(simple_type::string_type));
  IFC4X2_types[344] = new type_declaration(
      strings[570], 344, new simple_type(simple_type::real_type));
  IFC4X2_types[350] = new enumeration_type(
      strings[571], 350,
      {strings[572], strings[573], strings[574], strings[575], strings[576],
       strings[577], strings[578], strings[579], strings[580], strings[581],
       strings[582], strings[583], strings[584], strings[585], strings[586],
       strings[587], strings[8], strings[9]});
  IFC4X2_types[351] = new type_declaration(
      strings[588], 351, new simple_type(simple_type::real_type));
  IFC4X2_types[352] = new type_declaration(
      strings[589], 352, new simple_type(simple_type::real_type));
  IFC4X2_types[353] = new type_declaration(
      strings[590], 353, new simple_type(simple_type::real_type));
  IFC4X2_types[354] = new type_declaration(
      strings[591], 354, new simple_type(simple_type::real_type));
  IFC4X2_types[357] =
      new enumeration_type(strings[592], 357,
                           {strings[593], strings[594], strings[595],
                            strings[596], strings[8], strings[9]});
  IFC4X2_types[360] = new enumeration_type(
      strings[597], 360,
      {strings[598], strings[599], strings[600], strings[601], strings[602],
       strings[8], strings[9]});
  IFC4X2_types[363] = new enumeration_type(
      strings[603], 363,
      {strings[604], strings[605], strings[606], strings[8], strings[9]});
  IFC4X2_types[366] = new enumeration_type(
      strings[607], 366,
      {strings[608], strings[609], strings[610], strings[611], strings[612],
       strings[8], strings[9]});
  IFC4X2_types[367] = new type_declaration(
      strings[613], 367, new simple_type(simple_type::real_type));
  IFC4X2_types[370] = new enumeration_type(
      strings[614], 370,
      {strings[615], strings[616], strings[617], strings[8], strings[9]});
  IFC4X2_types[371] = new type_declaration(
      strings[618], 371, new simple_type(simple_type::real_type));
  IFC4X2_types[376] = new enumeration_type(
      strings[619], 376,
      {strings[620], strings[621], strings[622], strings[623], strings[192],
       strings[624], strings[625], strings[626], strings[194], strings[176],
       strings[180], strings[182], strings[627], strings[177], strings[8],
       strings[9]});
  IFC4X2_types[379] = new enumeration_type(
      strings[628], 379, {strings[200], strings[201], strings[202]});
  IFC4X2_types[386] = new type_declaration(
      strings[629], 386, new simple_type(simple_type::real_type));
  IFC4X2_types[389] = new enumeration_type(
      strings[630], 389, {strings[631], strings[632], strings[8], strings[9]});
  IFC4X2_types[392] = new enumeration_type(
      strings[633], 392,
      {strings[634], strings[635], strings[636], strings[637], strings[638],
       strings[639], strings[640], strings[641], strings[642], strings[8],
       strings[9]});
  IFC4X2_types[395] = new enumeration_type(
      strings[643], 395,
      {strings[644], strings[645], strings[646], strings[647], strings[648],
       strings[649], strings[8], strings[9]});
  IFC4X2_types[398] =
      new enumeration_type(strings[650], 398,
                           {strings[651], strings[652], strings[653],
                            strings[654], strings[8], strings[9]});
  IFC4X2_types[400] = new enumeration_type(
      strings[655], 400,
      {strings[656], strings[657], strings[658], strings[8], strings[9]});
  IFC4X2_types[409] =
      new enumeration_type(strings[659], 409,
                           {strings[660], strings[661], strings[662],
                            strings[663], strings[8], strings[9]});
  IFC4X2_types[425] = new enumeration_type(
      strings[664], 425,
      {strings[665], strings[666], strings[667], strings[668], strings[669],
       strings[670], strings[671], strings[8], strings[9]});
  IFC4X2_types[428] = new enumeration_type(
      strings[672], 428,
      {strings[673], strings[674], strings[675], strings[8], strings[9]});
  IFC4X2_types[438] = new enumeration_type(
      strings[676], 438,
      {strings[677], strings[678], strings[679], strings[680], strings[681],
       strings[682], strings[8], strings[9]});
  IFC4X2_types[441] = new enumeration_type(
      strings[683], 441,
      {strings[684], strings[685], strings[686], strings[687], strings[688],
       strings[8], strings[9]});
  IFC4X2_types[445] = new enumeration_type(
      strings[689], 445,
      {strings[690], strings[691], strings[692], strings[9]});
  IFC4X2_types[450] = new enumeration_type(
      strings[693], 450,
      {strings[694], strings[695], strings[696], strings[697], strings[698],
       strings[699], strings[700], strings[701], strings[8], strings[9]});
  IFC4X2_types[453] =
      new enumeration_type(strings[702], 453,
                           {strings[703], strings[704], strings[705],
                            strings[706], strings[8], strings[9]});
  IFC4X2_types[464] = new type_declaration(
      strings[707], 464, new simple_type(simple_type::string_type));
  IFC4X2_types[465] = new type_declaration(
      strings[708], 465, new simple_type(simple_type::string_type));
  IFC4X2_types[466] = new type_declaration(
      strings[709], 466, new simple_type(simple_type::string_type));
  IFC4X2_types[469] = new enumeration_type(
      strings[710], 469,
      {strings[711], strings[712], strings[713], strings[714], strings[715],
       strings[8], strings[9]});
  IFC4X2_types[470] = new type_declaration(
      strings[716], 470, new simple_type(simple_type::real_type));
  IFC4X2_types[471] = new type_declaration(
      strings[717], 471, new simple_type(simple_type::real_type));
  IFC4X2_types[476] = new enumeration_type(
      strings[718], 476,
      {strings[719], strings[720], strings[721], strings[722], strings[723],
       strings[724], strings[725], strings[8], strings[9]});
  IFC4X2_types[479] = new enumeration_type(
      strings[726], 479, {strings[727], strings[728], strings[8], strings[9]});
  IFC4X2_types[481] = new enumeration_type(
      strings[729], 481,
      {strings[730], strings[731], strings[732], strings[733], strings[734],
       strings[735], strings[736], strings[8], strings[9]});
  IFC4X2_types[488] =
      new enumeration_type(strings[737], 488, {strings[738], strings[739]});
  IFC4X2_types[487] = new type_declaration(
      strings[740], 487, new simple_type(simple_type::string_type));
  IFC4X2_types[493] =
      new enumeration_type(strings[741], 493,
                           {strings[567], strings[742], strings[743],
                            strings[744], strings[8], strings[9]});
  IFC4X2_types[499] = new enumeration_type(
      strings[745], 499, {strings[746], strings[747], strings[8], strings[9]});
  IFC4X2_types[500] = new type_declaration(
      strings[748], 500, new simple_type(simple_type::real_type));
  IFC4X2_types[501] = new type_declaration(
      strings[749], 501, new simple_type(simple_type::real_type));
  IFC4X2_types[504] = new enumeration_type(
      strings[750], 504,
      {strings[751], strings[752], strings[753], strings[754], strings[755],
       strings[756], strings[757], strings[758], strings[759], strings[760],
       strings[761], strings[762], strings[763], strings[8], strings[9]});
  IFC4X2_types[505] = new type_declaration(
      strings[764], 505, new simple_type(simple_type::string_type));
  IFC4X2_types[506] = new type_declaration(
      strings[765], 506, new simple_type(simple_type::real_type));
  IFC4X2_types[514] = new type_declaration(
      strings[766], 514, new simple_type(simple_type::real_type));
  IFC4X2_types[515] = new type_declaration(
      strings[767], 515, new simple_type(simple_type::integer_type));
  IFC4X2_types[516] = new type_declaration(
      strings[768], 516, new simple_type(simple_type::integer_type));
  IFC4X2_types[519] =
      new enumeration_type(strings[769], 519,
                           {strings[770], strings[771], strings[494],
                            strings[772], strings[8], strings[9]});
  IFC4X2_types[520] =
      new enumeration_type(strings[773], 520,
                           {strings[774], strings[660], strings[661],
                            strings[662], strings[663], strings[9]});
  IFC4X2_types[523] = new enumeration_type(
      strings[775], 523,
      {strings[776], strings[777], strings[778], strings[8], strings[9]});
  IFC4X2_types[524] = new type_declaration(
      strings[779], 524, new simple_type(simple_type::real_type));
  IFC4X2_types[528] = new type_declaration(
      strings[780], 528, new simple_type(simple_type::real_type));
  IFC4X2_types[531] = new enumeration_type(
      strings[781], 531, {strings[480], strings[782], strings[8], strings[9]});
  IFC4X2_types[532] = new type_declaration(
      strings[783], 532, new simple_type(simple_type::real_type));
  IFC4X2_types[533] = new enumeration_type(
      strings[784], 533,
      {strings[785], strings[786], strings[787], strings[116]});
  IFC4X2_types[534] = new type_declaration(
      strings[788], 534, new simple_type(simple_type::string_type));
  IFC4X2_types[537] = new enumeration_type(
      strings[789], 537,
      {strings[790], strings[791], strings[792], strings[320], strings[321],
       strings[793], strings[794], strings[357], strings[795], strings[796],
       strings[797], strings[324], strings[798], strings[315], strings[799],
       strings[359], strings[800], strings[801], strings[802], strings[8],
       strings[9]});
  IFC4X2_types[541] = new enumeration_type(
      strings[803], 541,
      {strings[804], strings[805], strings[806], strings[807], strings[808],
       strings[809], strings[810], strings[811], strings[812], strings[8],
       strings[9]});
  IFC4X2_types[542] = new type_declaration(strings[813], 542,
                                           new named_type(IFC4X2_types[505]));
  IFC4X2_types[544] = new enumeration_type(
      strings[814], 544, {strings[815], strings[816], strings[817]});
  IFC4X2_types[545] = new type_declaration(
      strings[818], 545, new simple_type(simple_type::real_type));
  IFC4X2_types[549] = new enumeration_type(
      strings[819], 549,
      {strings[820], strings[821], strings[822], strings[9]});
  IFC4X2_types[552] = new enumeration_type(
      strings[823], 552,
      {strings[804], strings[805], strings[807], strings[808], strings[824],
       strings[825], strings[826], strings[827], strings[810], strings[812],
       strings[9]});
  IFC4X2_types[555] = new enumeration_type(
      strings[828], 555,
      {strings[829], strings[830], strings[831], strings[8], strings[9]});
  IFC4X2_types[564] = new type_declaration(
      strings[832], 564, new simple_type(simple_type::real_type));
  IFC4X2_types[565] = new type_declaration(
      strings[833], 565, new simple_type(simple_type::real_type));
  IFC4X2_types[568] = new type_declaration(
      strings[834], 568, new simple_type(simple_type::real_type));
  IFC4X2_types[569] = new type_declaration(
      strings[835], 569, new simple_type(simple_type::real_type));
  IFC4X2_types[572] = new enumeration_type(
      strings[836], 572,
      {strings[837], strings[838], strings[839], strings[8], strings[9]});
  IFC4X2_types[574] = new type_declaration(
      strings[840], 574, new simple_type(simple_type::logical_type));
  IFC4X2_types[575] = new enumeration_type(
      strings[841], 575,
      {strings[842], strings[843], strings[844], strings[845], strings[846]});
  IFC4X2_types[578] = new type_declaration(
      strings[847], 578, new simple_type(simple_type::real_type));
  IFC4X2_types[579] = new type_declaration(
      strings[848], 579, new simple_type(simple_type::real_type));
  IFC4X2_types[580] = new type_declaration(
      strings[849], 580, new simple_type(simple_type::real_type));
  IFC4X2_types[581] = new type_declaration(
      strings[850], 581, new simple_type(simple_type::real_type));
  IFC4X2_types[582] = new type_declaration(
      strings[851], 582, new simple_type(simple_type::real_type));
  IFC4X2_types[586] = new type_declaration(
      strings[852], 586, new simple_type(simple_type::real_type));
  IFC4X2_types[587] = new type_declaration(
      strings[853], 587, new simple_type(simple_type::real_type));
  IFC4X2_types[588] = new type_declaration(
      strings[854], 588, new simple_type(simple_type::real_type));
  IFC4X2_types[589] = new type_declaration(
      strings[855], 589, new simple_type(simple_type::real_type));
  IFC4X2_types[614] = new enumeration_type(
      strings[856], 614,
      {strings[857], strings[858], strings[859], strings[860], strings[861],
       strings[862], strings[863], strings[864], strings[865], strings[866],
       strings[867], strings[8], strings[9]});
  IFC4X2_types[617] = new enumeration_type(
      strings[868], 617,
      {strings[869], strings[870], strings[871], strings[872], strings[873],
       strings[8], strings[9]});
  IFC4X2_types[621] = new enumeration_type(
      strings[874], 621,
      {strings[875], strings[876], strings[877], strings[878], strings[879],
       strings[746], strings[6], strings[880], strings[881], strings[882],
       strings[883], strings[884], strings[885], strings[886], strings[887],
       strings[888], strings[889], strings[8], strings[9]});
  IFC4X2_types[625] = new type_declaration(
      strings[890], 625, new simple_type(simple_type::real_type));
  IFC4X2_types[626] = new type_declaration(
      strings[891], 626, new simple_type(simple_type::real_type));
  IFC4X2_types[627] = new type_declaration(
      strings[892], 627, new simple_type(simple_type::real_type));
  IFC4X2_types[628] =
      new select_type(strings[893], 628, {IFC4X2_types[84], IFC4X2_types[627]});
  IFC4X2_types[629] = new type_declaration(
      strings[894], 629, new simple_type(simple_type::real_type));
  IFC4X2_types[630] =
      new select_type(strings[895], 630, {IFC4X2_types[84], IFC4X2_types[629]});
  IFC4X2_types[631] =
      new select_type(strings[896], 631, {IFC4X2_types[84], IFC4X2_types[626]});
  IFC4X2_types[632] = new type_declaration(
      strings[897], 632, new simple_type(simple_type::real_type));
  IFC4X2_types[633] = new type_declaration(
      strings[898], 633, new simple_type(simple_type::real_type));
  IFC4X2_types[634] = new type_declaration(
      strings[899], 634, new simple_type(simple_type::real_type));
  IFC4X2_types[635] = new type_declaration(
      strings[900], 635, new simple_type(simple_type::real_type));
  IFC4X2_types[637] = new type_declaration(
      strings[901], 637, new simple_type(simple_type::integer_type));
  IFC4X2_types[640] = new enumeration_type(
      strings[902], 640,
      {strings[903], strings[904], strings[905], strings[8], strings[9]});
  IFC4X2_types[642] = new type_declaration(strings[906], 642,
                                           new named_type(IFC4X2_types[545]));
  IFC4X2_types[644] = new enumeration_type(strings[907], 644, {strings[908]});
  IFC4X2_types[645] = new type_declaration(
      strings[909], 645, new simple_type(simple_type::number_type));
  IFC4X2_types[652] = new enumeration_type(
      strings[910], 652,
      {strings[911], strings[912], strings[478], strings[913], strings[914],
       strings[915], strings[916], strings[9]});
  IFC4X2_types[649] = new enumeration_type(
      strings[917], 649,
      {strings[918], strings[919], strings[920], strings[660], strings[921],
       strings[922], strings[923], strings[924], strings[925], strings[926],
       strings[927], strings[8], strings[9]});
  IFC4X2_types[654] = new enumeration_type(
      strings[928], 654,
      {strings[929], strings[930], strings[931], strings[932], strings[933],
       strings[934], strings[935], strings[8], strings[9]});
  IFC4X2_types[660] = new enumeration_type(
      strings[936], 660, {strings[937], strings[938], strings[8], strings[9]});
  IFC4X2_types[670] = new enumeration_type(
      strings[939], 670,
      {strings[940], strings[941], strings[942], strings[943], strings[944],
       strings[8], strings[9]});
  IFC4X2_types[684] = new type_declaration(
      strings[945], 684, new simple_type(simple_type::real_type));
  IFC4X2_types[673] = new type_declaration(
      strings[946], 673, new simple_type(simple_type::real_type));
  IFC4X2_types[677] =
      new enumeration_type(strings[947], 677, {strings[8], strings[9]});
  IFC4X2_types[678] = new enumeration_type(
      strings[948], 678,
      {strings[949], strings[950], strings[951], strings[8], strings[9]});
  IFC4X2_types[681] = new enumeration_type(
      strings[952], 681,
      {strings[953], strings[954], strings[955], strings[8], strings[9]});
  IFC4X2_types[686] = new enumeration_type(
      strings[956], 686, {strings[957], strings[958], strings[9]});
  IFC4X2_types[690] =
      new enumeration_type(strings[959], 690,
                           {strings[960], strings[961], strings[962],
                            strings[963], strings[8], strings[9]});
  IFC4X2_types[692] = new enumeration_type(
      strings[964], 692,
      {strings[965], strings[966], strings[967], strings[968], strings[969],
       strings[970], strings[8], strings[9]});
  IFC4X2_types[695] = new enumeration_type(
      strings[971], 695,
      {strings[214], strings[224], strings[225], strings[226], strings[227],
       strings[561], strings[228], strings[8], strings[9]});
  IFC4X2_types[698] = new enumeration_type(
      strings[972], 698,
      {strings[190], strings[564], strings[563], strings[973], strings[974],
       strings[8], strings[9]});
  IFC4X2_types[703] = new type_declaration(
      strings[975], 703, new simple_type(simple_type::real_type));
  IFC4X2_types[705] = new type_declaration(
      strings[976], 705, new simple_type(simple_type::real_type));
  IFC4X2_types[709] = new enumeration_type(
      strings[977], 709,
      {strings[978], strings[979], strings[980], strings[981], strings[982],
       strings[983], strings[984], strings[985], strings[986], strings[8],
       strings[9]});
  IFC4X2_types[720] = new type_declaration(strings[987], 720,
                                           new named_type(IFC4X2_types[515]));
  IFC4X2_types[721] = new type_declaration(strings[988], 721,
                                           new named_type(IFC4X2_types[545]));
  IFC4X2_types[722] = new type_declaration(strings[989], 722,
                                           new named_type(IFC4X2_types[705]));
  IFC4X2_types[725] = new type_declaration(
      strings[990], 725, new simple_type(simple_type::real_type));
  IFC4X2_types[732] = new enumeration_type(
      strings[991], 732, {strings[992], strings[993], strings[994]});
  IFC4X2_types[733] = new type_declaration(
      strings[995], 733, new simple_type(simple_type::string_type));
  IFC4X2_types[740] = new type_declaration(
      strings[996], 740, new simple_type(simple_type::real_type));
  IFC4X2_types[743] = new enumeration_type(
      strings[997], 743,
      {strings[998], strings[999], strings[1000], strings[1001], strings[1002],
       strings[1003], strings[1004], strings[8], strings[9]});
  IFC4X2_types[753] =
      new enumeration_type(strings[1005], 753, {strings[1006], strings[1007]});
  IFC4X2_types[761] = new enumeration_type(
      strings[1008], 761,
      {strings[1009], strings[1010], strings[1011], strings[1012],
       strings[1013], strings[8], strings[9]});
  IFC4X2_types[756] =
      new enumeration_type(strings[1014], 756, {strings[1015], strings[1016]});
  IFC4X2_types[758] = new enumeration_type(
      strings[1017], 758,
      {strings[1018], strings[1019], strings[8], strings[9]});
  IFC4X2_types[776] = new enumeration_type(
      strings[1020], 776,
      {strings[1021], strings[1022], strings[1023], strings[1024],
       strings[1025], strings[1026], strings[1027], strings[9]});
  IFC4X2_types[784] =
      new enumeration_type(strings[1028], 784,
                           {strings[1029], strings[1030], strings[1031],
                            strings[1032], strings[8], strings[9]});
  IFC4X2_types[786] = new enumeration_type(
      strings[1033], 786,
      {strings[1034], strings[1035], strings[1036], strings[1037],
       strings[1038], strings[1039], strings[1040], strings[8], strings[9]});
  IFC4X2_types[790] = new enumeration_type(
      strings[1041], 790,
      {strings[1042], strings[1043], strings[1044], strings[1045],
       strings[1046], strings[1047], strings[1048], strings[8], strings[9]});
  IFC4X2_types[798] = new type_declaration(
      strings[1049], 798, new simple_type(simple_type::real_type));
  IFC4X2_types[801] = new enumeration_type(
      strings[1050], 801,
      {strings[1051], strings[1052], strings[1053], strings[8], strings[9]});
  IFC4X2_types[805] = new enumeration_type(
      strings[1054], 805,
      {strings[1055], strings[1056], strings[8], strings[9]});
  IFC4X2_types[807] = new enumeration_type(
      strings[1057], 807,
      {strings[1058], strings[1059], strings[1060], strings[1061],
       strings[1062], strings[1063], strings[8], strings[9]});
  IFC4X2_types[808] = new type_declaration(
      strings[1064], 808, new simple_type(simple_type::real_type));
  IFC4X2_types[811] = new type_declaration(
      strings[1065], 811, new simple_type(simple_type::real_type));
  IFC4X2_types[817] = new enumeration_type(
      strings[1066], 817,
      {strings[1067], strings[1068], strings[1069], strings[1070],
       strings[1071], strings[1072], strings[1073], strings[1074]});
  IFC4X2_types[820] = new enumeration_type(
      strings[1075], 820,
      {strings[1076], strings[1077], strings[1078], strings[8], strings[9]});
  IFC4X2_types[821] = new enumeration_type(
      strings[1079], 821,
      {strings[1080], strings[1081], strings[1082], strings[1083], strings[325],
       strings[1084], strings[1085], strings[326], strings[1086], strings[9]});
  IFC4X2_types[826] = new enumeration_type(
      strings[1087], 826,
      {strings[1088], strings[1089], strings[1090], strings[884], strings[1091],
       strings[1092], strings[1093], strings[1094], strings[8], strings[9]});
  IFC4X2_types[827] =
      new enumeration_type(strings[1095], 827, {strings[1096], strings[1097]});
  IFC4X2_types[829] = new enumeration_type(
      strings[1098], 829,
      {strings[1094], strings[1092], strings[1090], strings[1088],
       strings[1091], strings[1093], strings[1089], strings[884], strings[1099],
       strings[8], strings[9]});
  IFC4X2_types[834] =
      new enumeration_type(strings[1100], 834, {strings[8], strings[9]});
  IFC4X2_types[900] = new enumeration_type(
      strings[1101], 900,
      {strings[1102], strings[1103], strings[1104], strings[1105],
       strings[1106], strings[1107], strings[1108], strings[1109],
       strings[1110], strings[1111], strings[1112], strings[1113],
       strings[1114], strings[1115], strings[1116], strings[1117],
       strings[1118], strings[934],  strings[1119], strings[1120],
       strings[1121], strings[1122], strings[8]});
  IFC4X2_types[903] = new enumeration_type(
      strings[1123], 903,
      {strings[1124], strings[1125], strings[1126], strings[1127],
       strings[1128], strings[1129], strings[1130], strings[1131],
       strings[1132], strings[1133], strings[1134], strings[1135],
       strings[1136], strings[8], strings[9]});
  IFC4X2_types[905] = new type_declaration(
      strings[1137], 905, new simple_type(simple_type::real_type));
  IFC4X2_types[906] = new type_declaration(
      strings[1138], 906, new simple_type(simple_type::real_type));
  IFC4X2_types[907] = new type_declaration(
      strings[1139], 907, new simple_type(simple_type::real_type));
  IFC4X2_types[908] = new select_type(strings[1140], 908,
                                      {IFC4X2_types[84], IFC4X2_types[907]});
  IFC4X2_types[941] = new enumeration_type(
      strings[1141], 941,
      {strings[1142], strings[1143], strings[1144], strings[1145],
       strings[1146], strings[1147], strings[1148], strings[1149],
       strings[1150], strings[1151], strings[1152], strings[1153],
       strings[1154], strings[1155], strings[1156], strings[1157]});
  IFC4X2_types[944] = new enumeration_type(
      strings[1158], 944,
      {strings[1159], strings[1160], strings[1161], strings[1162],
       strings[1163], strings[1164], strings[1165], strings[1166],
       strings[1167], strings[1168], strings[1169], strings[1170],
       strings[1171], strings[1172], strings[1173], strings[1174],
       strings[1175], strings[1176], strings[1177], strings[1178],
       strings[1179], strings[1180], strings[1181], strings[1182],
       strings[1183], strings[1184], strings[1185], strings[1186],
       strings[1187], strings[1188]});
  IFC4X2_types[912] = new enumeration_type(
      strings[1189], 912,
      {strings[1190], strings[1191], strings[1192], strings[1193], strings[691],
       strings[1194], strings[1195], strings[1196], strings[1197],
       strings[1198], strings[8], strings[9]});
  IFC4X2_types[919] = new type_declaration(
      strings[1199], 919, new simple_type(simple_type::real_type));
  IFC4X2_types[922] =
      new enumeration_type(strings[1200], 922, {strings[1201], strings[1202]});
  IFC4X2_types[915] = new type_declaration(
      strings[1203], 915, new simple_type(simple_type::real_type));
  IFC4X2_types[926] = new enumeration_type(
      strings[1204], 926,
      {strings[1205], strings[1206], strings[1207], strings[1208],
       strings[1209], strings[1210], strings[1211], strings[1212],
       strings[1213], strings[1214], strings[1215], strings[1216],
       strings[1217], strings[1218], strings[1219], strings[1220],
       strings[1221], strings[1222], strings[1223], strings[1224],
       strings[1225], strings[1226], strings[1227], strings[1228],
       strings[8],    strings[9]});
  IFC4X2_types[927] =
      new enumeration_type(strings[1229], 927,
                           {strings[1230], strings[1231], strings[1232],
                            strings[1233], strings[8], strings[9]});
  IFC4X2_types[930] = new enumeration_type(
      strings[1234], 930,
      {strings[1235], strings[1236], strings[1237], strings[8], strings[9]});
  IFC4X2_types[934] = new type_declaration(
      strings[1238], 934, new simple_type(simple_type::real_type));
  IFC4X2_types[939] = new enumeration_type(
      strings[1239], 939,
      {strings[1240], strings[1241], strings[1242], strings[1243],
       strings[1244], strings[1245], strings[1246], strings[1247],
       strings[1248], strings[1249], strings[1250], strings[1251]});
  IFC4X2_types[950] = new enumeration_type(
      strings[1252], 950,
      {strings[1253], strings[1254], strings[1255], strings[1256],
       strings[1257], strings[315], strings[1258], strings[1259], strings[8],
       strings[9]});
  IFC4X2_types[954] = new enumeration_type(
      strings[1260], 954,
      {strings[1261], strings[1262], strings[8], strings[9]});
  IFC4X2_types[955] = new type_declaration(
      strings[1263], 955, new simple_type(simple_type::real_type));
  IFC4X2_types[958] = new type_declaration(
      strings[1264], 958, new simple_type(simple_type::real_type));
  IFC4X2_types[959] = new type_declaration(
      strings[1265], 959, new simple_type(simple_type::real_type));
  IFC4X2_types[960] = new type_declaration(
      strings[1266], 960, new simple_type(simple_type::real_type));
  IFC4X2_types[961] = new type_declaration(
      strings[1267], 961, new simple_type(simple_type::real_type));
  IFC4X2_types[966] = new enumeration_type(
      strings[1268], 966,
      {strings[1269], strings[1270], strings[8], strings[9]});
  IFC4X2_types[968] = new enumeration_type(
      strings[1271], 968,
      {strings[1272], strings[1273], strings[1274], strings[774], strings[660],
       strings[8], strings[9]});
  IFC4X2_types[975] = new enumeration_type(
      strings[1275], 975,
      {strings[1276], strings[1277], strings[314], strings[1278], strings[499],
       strings[1032], strings[23], strings[506], strings[8], strings[9]});
  IFC4X2_types[976] = new type_declaration(
      strings[1279], 976, new simple_type(simple_type::real_type));
  IFC4X2_types[977] = new type_declaration(
      strings[1280], 977, new simple_type(simple_type::real_type));
  IFC4X2_types[979] = new type_declaration(
      strings[1281], 979, new simple_type(simple_type::real_type));
  IFC4X2_types[984] = new enumeration_type(
      strings[1282], 984,
      {strings[1283], strings[1284], strings[1285], strings[8], strings[9]});
  IFC4X2_types[988] = new enumeration_type(
      strings[1286], 988,
      {strings[1055], strings[1287], strings[1056], strings[1288],
       strings[1136], strings[8], strings[9]});
  IFC4X2_types[990] = new enumeration_type(
      strings[1289], 990,
      {strings[1290], strings[1291], strings[1292], strings[1293],
       strings[1294], strings[1295], strings[1296], strings[1297],
       strings[1298], strings[1299], strings[1300], strings[1301],
       strings[1302], strings[1303], strings[8], strings[9]});
  IFC4X2_types[991] =
      new enumeration_type(strings[1304], 991,
                           {strings[1305], strings[1306], strings[1307],
                            strings[1308], strings[1309]});
  IFC4X2_types[999] = new enumeration_type(
      strings[1310], 999,
      {strings[1311], strings[370], strings[1312], strings[1313], strings[1314],
       strings[1315], strings[1316], strings[8], strings[9]});
  IFC4X2_types[1002] = new enumeration_type(
      strings[1317], 1002,
      {strings[1318], strings[1319], strings[466], strings[1320], strings[1321],
       strings[8], strings[9]});
  IFC4X2_types[1028] =
      new enumeration_type(strings[1322], 1028,
                           {strings[1311], strings[1323], strings[1316],
                            strings[1324], strings[8], strings[9]});
  IFC4X2_types[1031] = new enumeration_type(
      strings[1325], 1031,
      {strings[1326], strings[1327], strings[1328], strings[8], strings[9]});
  IFC4X2_types[1040] = new enumeration_type(
      strings[1329], 1040,
      {strings[1330], strings[955], strings[8], strings[9]});
  IFC4X2_types[1046] =
      new enumeration_type(strings[1331], 1046,
                           {strings[1332], strings[1333], strings[1334],
                            strings[1335], strings[8], strings[9]});
  IFC4X2_types[1051] = new enumeration_type(
      strings[1336], 1051, {strings[449], strings[450], strings[1337]});
  IFC4X2_types[1066] = new enumeration_type(
      strings[1338], 1066,
      {strings[1339], strings[1340], strings[1341], strings[1342],
       strings[1343], strings[1344], strings[1345], strings[1346],
       strings[1347], strings[8], strings[9]});
  IFC4X2_types[1070] = new enumeration_type(
      strings[1348], 1070,
      {strings[1349], strings[1350], strings[8], strings[9]});
  IFC4X2_types[1076] = new enumeration_type(
      strings[1351], 1076,
      {strings[1352], strings[1353], strings[1354], strings[1355],
       strings[1356], strings[1357], strings[1358], strings[8], strings[9]});
  IFC4X2_types[1078] = new enumeration_type(
      strings[1359], 1078, {strings[1360], strings[1361], strings[9]});
  IFC4X2_types[1082] = new enumeration_type(
      strings[1362], 1082,
      {strings[1363], strings[1276], strings[1364], strings[1365], strings[481],
       strings[1366], strings[1367], strings[1368], strings[1369],
       strings[1370], strings[1371], strings[1372], strings[8], strings[9]});
  IFC4X2_types[1084] = new type_declaration(
      strings[1373], 1084, new simple_type(simple_type::real_type));
  IFC4X2_types[1085] = new type_declaration(
      strings[1374], 1085, new simple_type(simple_type::real_type));
  IFC4X2_types[1089] = new enumeration_type(
      strings[1375], 1089,
      {strings[867], strings[1376], strings[1377], strings[8], strings[9]});
  IFC4X2_types[1092] = new enumeration_type(
      strings[1378], 1092,
      {strings[468], strings[867], strings[1379], strings[1380], strings[1381],
       strings[8], strings[9]});
  IFC4X2_types[1094] =
      new enumeration_type(strings[1382], 1094,
                           {strings[1383], strings[1384], strings[1385],
                            strings[1386], strings[8], strings[9]});
  IFC4X2_types[1097] = new type_declaration(
      strings[1387], 1097, new simple_type(simple_type::string_type));
  IFC4X2_types[1098] = new type_declaration(
      strings[1388], 1098, new simple_type(simple_type::string_type));
  IFC4X2_types[1099] = new type_declaration(
      strings[1389], 1099, new simple_type(simple_type::string_type));
  IFC4X2_types[1100] = new type_declaration(
      strings[1390], 1100, new simple_type(simple_type::string_type));
  IFC4X2_types[1104] = new enumeration_type(
      strings[1391], 1104,
      {strings[528], strings[530], strings[1392], strings[1393]});
  IFC4X2_types[1109] = new type_declaration(
      strings[1394], 1109, new simple_type(simple_type::string_type));
  IFC4X2_types[1115] = new type_declaration(
      strings[1395], 1115, new simple_type(simple_type::real_type));
  IFC4X2_types[1116] = new type_declaration(
      strings[1396], 1116, new simple_type(simple_type::real_type));
  IFC4X2_types[1117] = new type_declaration(
      strings[1397], 1117, new simple_type(simple_type::real_type));
  IFC4X2_types[1118] = new type_declaration(
      strings[1398], 1118, new simple_type(simple_type::real_type));
  IFC4X2_types[1119] = new type_declaration(
      strings[1399], 1119, new simple_type(simple_type::real_type));
  IFC4X2_types[1120] = new type_declaration(
      strings[1400], 1120, new simple_type(simple_type::real_type));
  IFC4X2_types[1121] = new type_declaration(
      strings[1401], 1121, new simple_type(simple_type::string_type));
  IFC4X2_types[1122] = new type_declaration(
      strings[1402], 1122, new simple_type(simple_type::real_type));
  IFC4X2_types[1123] = new select_type(strings[1403], 1123,
                                       {IFC4X2_types[343], IFC4X2_types[808]});
  IFC4X2_types[1126] = new enumeration_type(
      strings[1404], 1126,
      {strings[1405], strings[1316], strings[1406], strings[1407],
       strings[1408], strings[1409], strings[9]});
  IFC4X2_types[1128] = new type_declaration(
      strings[1410], 1128, new simple_type(simple_type::integer_type));
  IFC4X2_types[1132] = new type_declaration(
      strings[1411], 1132, new simple_type(simple_type::real_type));
  IFC4X2_types[1135] = new enumeration_type(
      strings[1412], 1135,
      {strings[32], strings[1413], strings[1414], strings[1415], strings[1416],
       strings[8], strings[9]});
  IFC4X2_types[1136] = new enumeration_type(
      strings[1417], 1136,
      {strings[1418], strings[1405], strings[1419], strings[1420]});
  IFC4X2_types[1138] =
      new enumeration_type(strings[1421], 1138,
                           {strings[1422], strings[1423], strings[1424],
                            strings[1425], strings[1426], strings[1427]});
  IFC4X2_types[1139] = new select_type(strings[1428], 1139,
                                       {IFC4X2_types[84], IFC4X2_types[568]});
  IFC4X2_types[1142] = new enumeration_type(
      strings[1429], 1142,
      {strings[1430], strings[1431], strings[1432], strings[1433],
       strings[1434], strings[8], strings[9]});
  IFC4X2_types[1147] = new enumeration_type(
      strings[1435], 1147, {strings[1436], strings[924], strings[116]});
  IFC4X2_types[1152] = new enumeration_type(
      strings[1437], 1152, {strings[1438], strings[8], strings[9]});
  IFC4X2_types[1166] = new type_declaration(
      strings[1439], 1166, new simple_type(simple_type::string_type));
  IFC4X2_types[1165] = new enumeration_type(
      strings[1440], 1165,
      {strings[1441], strings[1442], strings[1443], strings[1444],
       strings[1445], strings[1446], strings[1447], strings[1448],
       strings[1449], strings[1450], strings[1451], strings[1452],
       strings[1453], strings[1454], strings[1455], strings[1456],
       strings[1457], strings[1458], strings[1459], strings[1460],
       strings[1461], strings[1462], strings[1463], strings[1464],
       strings[1465], strings[1466], strings[1467], strings[1468],
       strings[1469], strings[8]});
  IFC4X2_types[1160] = new enumeration_type(
      strings[1470], 1160,
      {strings[1471], strings[1472], strings[1473], strings[1474],
       strings[1475], strings[1476], strings[1477], strings[1478], strings[8],
       strings[9]});
  IFC4X2_types[1163] = new enumeration_type(
      strings[1479], 1163,
      {strings[1480], strings[1481], strings[1482], strings[1483],
       strings[1484], strings[8], strings[9]});
  IFC4X2_types[1171] = new enumeration_type(
      strings[1485], 1171,
      {strings[1486], strings[1487], strings[1488], strings[1489],
       strings[1490], strings[1491], strings[1492], strings[1493],
       strings[1494], strings[1495], strings[1496], strings[1497],
       strings[1498], strings[1499], strings[1500], strings[1501],
       strings[1502], strings[1503], strings[1504], strings[1505],
       strings[1506], strings[8],    strings[9]});
  IFC4X2_types[1172] = new type_declaration(
      strings[1507], 1172, new simple_type(simple_type::real_type));
  IFC4X2_types[1180] = new enumeration_type(
      strings[1508], 1180,
      {strings[1509], strings[1510], strings[1511], strings[969], strings[1512],
       strings[1513], strings[8], strings[9]});
  IFC4X2_types[1183] = new enumeration_type(
      strings[1514], 1183,
      {strings[1515], strings[1516], strings[1517], strings[8], strings[9]});
  IFC4X2_types[1187] = new enumeration_type(
      strings[1518], 1187,
      {strings[1519], strings[1520], strings[1521], strings[1522],
       strings[1523], strings[1092], strings[8], strings[9]});
  IFC4X2_types[1188] = new type_declaration(
      strings[1524], 1188, new simple_type(simple_type::real_type));
  IFC4X2_types[1189] = new type_declaration(
      strings[1525], 1189, new simple_type(simple_type::real_type));
  IFC4X2_types[1194] = new enumeration_type(
      strings[1526], 1194,
      {strings[1527], strings[1528], strings[1529], strings[1530],
       strings[1089], strings[1531], strings[1532], strings[1312],
       strings[1533], strings[1534], strings[8], strings[9]});
  IFC4X2_types[1195] = new type_declaration(
      strings[1535], 1195, new simple_type(simple_type::real_type));
  IFC4X2_types[1196] = new type_declaration(
      strings[1536], 1196, new simple_type(simple_type::real_type));
  IFC4X2_types[1197] = new select_type(strings[1537], 1197,
                                       {IFC4X2_types[84], IFC4X2_types[1196]});
  IFC4X2_types[1200] = new enumeration_type(
      strings[1538], 1200,
      {strings[1539], strings[1540], strings[1541], strings[1542],
       strings[1543], strings[1544], strings[1545], strings[8], strings[9]});
  IFC4X2_types[1203] = new enumeration_type(
      strings[1546], 1203,
      {strings[1547], strings[1548], strings[1549], strings[1550],
       strings[1551], strings[1552], strings[1553], strings[1554],
       strings[1555], strings[1556], strings[1557], strings[1558],
       strings[1559], strings[9]});
  IFC4X2_types[1204] =
      new enumeration_type(strings[1560], 1204,
                           {strings[528], strings[529], strings[530],
                            strings[1561], strings[1562], strings[9]});
  IFC4X2_types[1208] = new enumeration_type(
      strings[1563], 1208,
      {strings[532], strings[533], strings[534], strings[327], strings[535],
       strings[326], strings[1564], strings[9]});
  IFC4X2_types[1209] = new enumeration_type(
      strings[1565], 1209,
      {strings[1566], strings[1567], strings[1568], strings[1569],
       strings[1570], strings[1571], strings[1572], strings[1573],
       strings[1574], strings[8], strings[9]});
  IFC4X2_types[1211] = new enumeration_type(
      strings[1575], 1211,
      {strings[1576], strings[1577], strings[1578], strings[8], strings[9]});
  IFC4X2_types[1212] = new enumeration_type(
      strings[1579], 1212,
      {strings[1566], strings[1567], strings[1568], strings[1569],
       strings[1570], strings[1571], strings[1572], strings[1573],
       strings[1574], strings[8], strings[9]});
  IFC4X2_types[1214] = new enumeration_type(
      strings[1580], 1214,
      {strings[1581], strings[1582], strings[1583], strings[8], strings[9]});
  IFC4X2_types[1217] = new enumeration_type(
      strings[1584], 1217,
      {strings[1585], strings[1586], strings[1587], strings[8], strings[9]});
  IFC4X2_types[1219] = new enumeration_type(
      strings[1588], 1219,
      {strings[1585], strings[1586], strings[1587], strings[8], strings[9]});
  IFC4X2_types[7] = new entity(strings[1589], false, 7, (entity *)0);
  IFC4X2_types[12] = new entity(strings[1590], true, 12, (entity *)0);
  IFC4X2_types[46] = new entity(strings[1591], false, 46, (entity *)0);
  IFC4X2_types[47] = new entity(strings[1592], false, 47, (entity *)0);
  IFC4X2_types[49] = new entity(strings[1593], false, 49, (entity *)0);
  IFC4X2_types[89] = new entity(strings[1594], true, 89, (entity *)0);
  IFC4X2_types[91] =
      new entity(strings[1595], false, 91, (entity *)IFC4X2_types[89]);
  IFC4X2_types[92] =
      new entity(strings[1596], false, 92, (entity *)IFC4X2_types[89]);
  IFC4X2_types[93] =
      new entity(strings[1597], false, 93, (entity *)IFC4X2_types[89]);
  IFC4X2_types[94] =
      new entity(strings[1598], false, 94, (entity *)IFC4X2_types[93]);
  IFC4X2_types[202] = new entity(strings[1599], true, 202, (entity *)0);
  IFC4X2_types[204] =
      new entity(strings[1600], false, 204, (entity *)IFC4X2_types[202]);
  IFC4X2_types[205] =
      new entity(strings[1601], false, 205, (entity *)IFC4X2_types[202]);
  IFC4X2_types[207] =
      new entity(strings[1602], false, 207, (entity *)IFC4X2_types[202]);
  IFC4X2_types[208] = new entity(strings[1603], true, 208, (entity *)0);
  IFC4X2_types[236] = new entity(strings[1604], true, 236, (entity *)0);
  IFC4X2_types[237] = new entity(strings[1605], true, 237, (entity *)0);
  IFC4X2_types[243] =
      new entity(strings[1606], false, 243, (entity *)IFC4X2_types[47]);
  IFC4X2_types[287] = new entity(strings[1607], false, 287, (entity *)0);
  IFC4X2_types[288] = new entity(strings[1608], false, 288, (entity *)0);
  IFC4X2_types[291] = new entity(strings[1609], false, 291, (entity *)0);
  IFC4X2_types[402] = new entity(strings[1610], true, 402, (entity *)0);
  IFC4X2_types[406] = new entity(strings[1611], true, 406, (entity *)0);
  IFC4X2_types[403] =
      new entity(strings[1612], false, 403, (entity *)IFC4X2_types[406]);
  IFC4X2_types[404] =
      new entity(strings[1613], false, 404, (entity *)IFC4X2_types[406]);
  IFC4X2_types[405] =
      new entity(strings[1614], false, 405, (entity *)IFC4X2_types[406]);
  IFC4X2_types[490] = new entity(strings[1615], false, 490, (entity *)0);
  IFC4X2_types[526] = new entity(strings[1616], false, 526, (entity *)0);
  IFC4X2_types[546] =
      new entity(strings[1617], false, 546, (entity *)IFC4X2_types[402]);
  IFC4X2_types[547] =
      new entity(strings[1618], false, 547, (entity *)IFC4X2_types[406]);
  IFC4X2_types[550] = new entity(strings[1619], false, 550, (entity *)0);
  IFC4X2_types[556] = new entity(strings[1620], false, 556, (entity *)0);
  IFC4X2_types[584] =
      new entity(strings[1621], false, 584, (entity *)IFC4X2_types[236]);
  IFC4X2_types[591] = new entity(strings[1622], false, 591, (entity *)0);
  IFC4X2_types[594] = new entity(strings[1623], true, 594, (entity *)0);
  IFC4X2_types[596] =
      new entity(strings[1624], false, 596, (entity *)IFC4X2_types[594]);
  IFC4X2_types[597] =
      new entity(strings[1625], false, 597, (entity *)IFC4X2_types[594]);
  IFC4X2_types[599] =
      new entity(strings[1626], false, 599, (entity *)IFC4X2_types[596]);
  IFC4X2_types[600] = new entity(strings[1627], false, 600, (entity *)0);
  IFC4X2_types[601] =
      new entity(strings[1628], false, 601, (entity *)IFC4X2_types[594]);
  IFC4X2_types[602] =
      new entity(strings[1629], false, 602, (entity *)IFC4X2_types[594]);
  IFC4X2_types[605] =
      new entity(strings[1630], false, 605, (entity *)IFC4X2_types[601]);
  IFC4X2_types[609] = new entity(strings[1631], true, 609, (entity *)0);
  IFC4X2_types[611] = new entity(strings[1632], false, 611, (entity *)0);
  IFC4X2_types[622] =
      new entity(strings[1633], false, 622, (entity *)IFC4X2_types[208]);
  IFC4X2_types[636] = new entity(strings[1634], false, 636, (entity *)0);
  IFC4X2_types[641] = new entity(strings[1635], true, 641, (entity *)0);
  IFC4X2_types[650] = new entity(strings[1636], true, 650, (entity *)0);
  IFC4X2_types[648] =
      new entity(strings[1637], false, 648, (entity *)IFC4X2_types[208]);
  IFC4X2_types[663] = new entity(strings[1638], false, 663, (entity *)0);
  IFC4X2_types[671] = new entity(strings[1639], false, 671, (entity *)0);
  IFC4X2_types[682] = new entity(strings[1640], false, 682, (entity *)0);
  IFC4X2_types[683] = new entity(strings[1641], false, 683, (entity *)0);
  IFC4X2_types[687] = new entity(strings[1642], true, 687, (entity *)0);
  IFC4X2_types[688] =
      new entity(strings[1643], true, 688, (entity *)IFC4X2_types[687]);
  IFC4X2_types[724] =
      new entity(strings[1644], false, 724, (entity *)IFC4X2_types[12]);
  IFC4X2_types[734] = new entity(strings[1645], true, 734, (entity *)0);
  IFC4X2_types[735] = new entity(strings[1646], false, 735, (entity *)0);
  IFC4X2_types[736] =
      new entity(strings[1647], false, 736, (entity *)IFC4X2_types[735]);
  IFC4X2_types[737] = new entity(strings[1648], true, 737, (entity *)0);
  IFC4X2_types[738] = new entity(strings[1649], false, 738, (entity *)0);
  IFC4X2_types[748] = new entity(strings[1650], true, 748, (entity *)0);
  IFC4X2_types[751] = new entity(strings[1651], false, 751, (entity *)0);
  IFC4X2_types[755] =
      new entity(strings[1652], false, 755, (entity *)IFC4X2_types[237]);
  IFC4X2_types[763] = new entity(strings[1653], true, 763, (entity *)0);
  IFC4X2_types[768] =
      new entity(strings[1654], false, 768, (entity *)IFC4X2_types[763]);
  IFC4X2_types[791] =
      new entity(strings[1655], false, 791, (entity *)IFC4X2_types[688]);
  IFC4X2_types[792] =
      new entity(strings[1656], false, 792, (entity *)IFC4X2_types[688]);
  IFC4X2_types[793] =
      new entity(strings[1657], false, 793, (entity *)IFC4X2_types[688]);
  IFC4X2_types[795] =
      new entity(strings[1658], false, 795, (entity *)IFC4X2_types[688]);
  IFC4X2_types[796] =
      new entity(strings[1659], false, 796, (entity *)IFC4X2_types[688]);
  IFC4X2_types[797] =
      new entity(strings[1660], false, 797, (entity *)IFC4X2_types[688]);
  IFC4X2_types[816] = new entity(strings[1661], false, 816, (entity *)0);
  IFC4X2_types[818] = new entity(strings[1662], false, 818, (entity *)0);
  IFC4X2_types[885] = new entity(strings[1663], true, 885, (entity *)0);
  IFC4X2_types[886] = new entity(strings[1664], true, 886, (entity *)0);
  IFC4X2_types[887] = new entity(strings[1665], true, 887, (entity *)0);
  IFC4X2_types[888] = new entity(strings[1666], false, 888, (entity *)0);
  IFC4X2_types[892] = new entity(strings[1667], true, 892, (entity *)0);
  IFC4X2_types[904] = new entity(strings[1668], true, 904, (entity *)0);
  IFC4X2_types[943] =
      new entity(strings[1669], false, 943, (entity *)IFC4X2_types[641]);
  IFC4X2_types[913] = new entity(strings[1670], true, 913, (entity *)0);
  IFC4X2_types[931] = new entity(strings[1671], false, 931, (entity *)0);
  IFC4X2_types[932] =
      new entity(strings[1672], true, 932, (entity *)IFC4X2_types[885]);
  IFC4X2_types[933] =
      new entity(strings[1673], false, 933, (entity *)IFC4X2_types[932]);
  IFC4X2_types[997] = new entity(strings[1674], true, 997, (entity *)0);
  IFC4X2_types[1007] = new entity(strings[1675], true, 1007, (entity *)0);
  IFC4X2_types[1009] =
      new entity(strings[1676], false, 1009, (entity *)IFC4X2_types[1007]);
  IFC4X2_types[1012] =
      new entity(strings[1677], true, 1012, (entity *)IFC4X2_types[1007]);
  IFC4X2_types[1018] =
      new entity(strings[1678], true, 1018, (entity *)IFC4X2_types[1012]);
  IFC4X2_types[1019] =
      new entity(strings[1679], false, 1019, (entity *)IFC4X2_types[1018]);
  IFC4X2_types[1037] =
      new entity(strings[1680], true, 1037, (entity *)IFC4X2_types[885]);
  IFC4X2_types[1035] =
      new entity(strings[1681], false, 1035, (entity *)IFC4X2_types[887]);
  IFC4X2_types[1036] =
      new entity(strings[1682], false, 1036, (entity *)IFC4X2_types[1037]);
  IFC4X2_types[1050] =
      new entity(strings[1683], false, 1050, (entity *)IFC4X2_types[1012]);
  IFC4X2_types[1052] =
      new entity(strings[1684], false, 1052, (entity *)IFC4X2_types[737]);
  IFC4X2_types[1054] =
      new entity(strings[1685], false, 1054, (entity *)IFC4X2_types[734]);
  IFC4X2_types[1055] =
      new entity(strings[1686], false, 1055, (entity *)IFC4X2_types[734]);
  IFC4X2_types[1057] =
      new entity(strings[1687], false, 1057, (entity *)IFC4X2_types[734]);
  IFC4X2_types[1058] =
      new entity(strings[1688], false, 1058, (entity *)IFC4X2_types[734]);
  IFC4X2_types[1059] =
      new entity(strings[1689], true, 1059, (entity *)IFC4X2_types[734]);
  IFC4X2_types[1071] = new entity(strings[1690], false, 1071, (entity *)0);
  IFC4X2_types[1072] = new entity(strings[1691], false, 1072, (entity *)0);
  IFC4X2_types[1073] = new entity(strings[1692], false, 1073, (entity *)0);
  IFC4X2_types[1079] =
      new entity(strings[1693], false, 1079, (entity *)IFC4X2_types[913]);
  IFC4X2_types[1080] =
      new entity(strings[1694], false, 1080, (entity *)IFC4X2_types[1079]);
  IFC4X2_types[1083] =
      new entity(strings[1695], false, 1083, (entity *)IFC4X2_types[12]);
  IFC4X2_types[1105] =
      new entity(strings[1696], false, 1105, (entity *)IFC4X2_types[737]);
  IFC4X2_types[1107] =
      new entity(strings[1697], false, 1107, (entity *)IFC4X2_types[734]);
  IFC4X2_types[1108] =
      new entity(strings[1698], false, 1108, (entity *)IFC4X2_types[734]);
  IFC4X2_types[1110] =
      new entity(strings[1699], true, 1110, (entity *)IFC4X2_types[734]);
  IFC4X2_types[1111] =
      new entity(strings[1700], false, 1111, (entity *)IFC4X2_types[1110]);
  IFC4X2_types[1112] =
      new entity(strings[1701], false, 1112, (entity *)IFC4X2_types[1110]);
  IFC4X2_types[1113] =
      new entity(strings[1702], false, 1113, (entity *)IFC4X2_types[734]);
  IFC4X2_types[1114] =
      new entity(strings[1703], false, 1114, (entity *)IFC4X2_types[734]);
  IFC4X2_types[1124] = new entity(strings[1704], false, 1124, (entity *)0);
  IFC4X2_types[1125] = new entity(strings[1705], true, 1125, (entity *)0);
  IFC4X2_types[1127] = new entity(strings[1706], false, 1127, (entity *)0);
  IFC4X2_types[1129] =
      new entity(strings[1707], true, 1129, (entity *)IFC4X2_types[887]);
  IFC4X2_types[1130] =
      new entity(strings[1708], false, 1130, (entity *)IFC4X2_types[932]);
  IFC4X2_types[1164] = new entity(strings[1709], false, 1164, (entity *)0);
  IFC4X2_types[1175] =
      new entity(strings[1710], false, 1175, (entity *)IFC4X2_types[1129]);
  IFC4X2_types[1177] =
      new entity(strings[1711], false, 1177, (entity *)IFC4X2_types[1175]);
  IFC4X2_types[1185] = new entity(strings[1712], false, 1185, (entity *)0);
  IFC4X2_types[1220] =
      new entity(strings[1713], false, 1220, (entity *)IFC4X2_types[913]);
  IFC4X2_types[8] = new select_type(
      strings[1714], 8,
      {IFC4X2_types[663], IFC4X2_types[682], IFC4X2_types[683]});
  IFC4X2_types[54] = new type_declaration(
      strings[1715], 54,
      new aggregation_type(aggregation_type::list_type, 3, 3,
                           new named_type(IFC4X2_types[720])));
  IFC4X2_types[77] = new select_type(strings[1716], 77,
                                     {IFC4X2_types[545], IFC4X2_types[705]});
  IFC4X2_types[98] = new type_declaration(strings[1717], 98,
                                          new named_type(IFC4X2_types[534]));
  IFC4X2_types[285] = new select_type(
      strings[1718], 285,
      {IFC4X2_types[0],    IFC4X2_types[1],    IFC4X2_types[43],
       IFC4X2_types[55],   IFC4X2_types[192],  IFC4X2_types[259],
       IFC4X2_types[331],  IFC4X2_types[344],  IFC4X2_types[351],
       IFC4X2_types[352],  IFC4X2_types[353],  IFC4X2_types[367],
       IFC4X2_types[371],  IFC4X2_types[386],  IFC4X2_types[470],
       IFC4X2_types[471],  IFC4X2_types[500],  IFC4X2_types[501],
       IFC4X2_types[506],  IFC4X2_types[514],  IFC4X2_types[516],
       IFC4X2_types[524],  IFC4X2_types[528],  IFC4X2_types[532],
       IFC4X2_types[564],  IFC4X2_types[565],  IFC4X2_types[568],
       IFC4X2_types[569],  IFC4X2_types[578],  IFC4X2_types[579],
       IFC4X2_types[581],  IFC4X2_types[582],  IFC4X2_types[586],
       IFC4X2_types[587],  IFC4X2_types[589],  IFC4X2_types[625],
       IFC4X2_types[626],  IFC4X2_types[627],  IFC4X2_types[629],
       IFC4X2_types[632],  IFC4X2_types[633],  IFC4X2_types[634],
       IFC4X2_types[635],  IFC4X2_types[684],  IFC4X2_types[703],
       IFC4X2_types[725],  IFC4X2_types[740],  IFC4X2_types[798],
       IFC4X2_types[905],  IFC4X2_types[906],  IFC4X2_types[907],
       IFC4X2_types[919],  IFC4X2_types[915],  IFC4X2_types[934],
       IFC4X2_types[958],  IFC4X2_types[959],  IFC4X2_types[960],
       IFC4X2_types[961],  IFC4X2_types[976],  IFC4X2_types[1084],
       IFC4X2_types[1085], IFC4X2_types[1115], IFC4X2_types[1116],
       IFC4X2_types[1117], IFC4X2_types[1118], IFC4X2_types[1119],
       IFC4X2_types[1132], IFC4X2_types[1172], IFC4X2_types[1189],
       IFC4X2_types[1195], IFC4X2_types[1196]});
  IFC4X2_types[543] = new select_type(strings[1719], 543,
                                      {IFC4X2_types[885], IFC4X2_types[887]});
  IFC4X2_types[548] = new select_type(strings[1720], 548,
                                      {IFC4X2_types[546], IFC4X2_types[547]});
  IFC4X2_types[551] = new select_type(strings[1721], 551,
                                      {IFC4X2_types[406], IFC4X2_types[556]});
  IFC4X2_types[570] = new type_declaration(
      strings[1722], 570,
      new aggregation_type(aggregation_type::list_type, 2, -1,
                           new named_type(IFC4X2_types[720])));
  IFC4X2_types[608] = new select_type(
      strings[1723], 608,
      {IFC4X2_types[594], IFC4X2_types[600], IFC4X2_types[609]});
  IFC4X2_types[643] = new type_declaration(strings[1724], 643,
                                           new named_type(IFC4X2_types[808]));
  IFC4X2_types[651] = new select_type(
      strings[1725], 651,
      {IFC4X2_types[12], IFC4X2_types[47], IFC4X2_types[406], IFC4X2_types[594],
       IFC4X2_types[663], IFC4X2_types[682], IFC4X2_types[683],
       IFC4X2_types[1071], IFC4X2_types[1125]});
  IFC4X2_types[723] = new type_declaration(strings[1726], 723,
                                           new named_type(IFC4X2_types[808]));
  IFC4X2_types[923] = new select_type(strings[1727], 923,
                                      {IFC4X2_types[54], IFC4X2_types[570]});
  IFC4X2_types[940] =
      new select_type(strings[1728], 940,
                      {IFC4X2_types[78], IFC4X2_types[84], IFC4X2_types[278],
                       IFC4X2_types[279], IFC4X2_types[343], IFC4X2_types[505],
                       IFC4X2_types[515], IFC4X2_types[534], IFC4X2_types[574],
                       IFC4X2_types[720], IFC4X2_types[811], IFC4X2_types[1097],
                       IFC4X2_types[1121], IFC4X2_types[1128]});
  IFC4X2_types[945] = new select_type(strings[1729], 945,
                                      {IFC4X2_types[290], IFC4X2_types[545],
                                       IFC4X2_types[643], IFC4X2_types[721],
                                       IFC4X2_types[723], IFC4X2_types[808]});
  IFC4X2_types[978] = new select_type(strings[1730], 978,
                                      {IFC4X2_types[977], IFC4X2_types[979]});
  IFC4X2_types[1034] = new select_type(strings[1731], 1034,
                                       {IFC4X2_types[737], IFC4X2_types[738]});
  IFC4X2_types[1053] = new select_type(strings[1732], 1053,
                                       {IFC4X2_types[404], IFC4X2_types[1054],
                                        IFC4X2_types[1055], IFC4X2_types[1057],
                                        IFC4X2_types[1058]});
  IFC4X2_types[1157] = new select_type(
      strings[1733], 1157,
      {IFC4X2_types[287], IFC4X2_types[636], IFC4X2_types[641]});
  IFC4X2_types[50] =
      new entity(strings[1734], false, 50, (entity *)IFC4X2_types[892]);
  IFC4X2_types[51] =
      new entity(strings[1735], false, 51, (entity *)IFC4X2_types[751]);
  IFC4X2_types[52] =
      new entity(strings[1736], false, 52, (entity *)IFC4X2_types[751]);
  IFC4X2_types[53] =
      new entity(strings[1737], false, 53, (entity *)IFC4X2_types[51]);
  IFC4X2_types[79] =
      new entity(strings[1738], false, 79, (entity *)IFC4X2_types[1059]);
  IFC4X2_types[150] =
      new entity(strings[1739], false, 150, (entity *)IFC4X2_types[52]);
  IFC4X2_types[164] =
      new entity(strings[1740], false, 164, (entity *)IFC4X2_types[402]);
  IFC4X2_types[165] =
      new entity(strings[1741], false, 165, (entity *)IFC4X2_types[406]);
  IFC4X2_types[175] =
      new entity(strings[1742], false, 175, (entity *)IFC4X2_types[734]);
  IFC4X2_types[176] =
      new entity(strings[1743], true, 176, (entity *)IFC4X2_types[734]);
  IFC4X2_types[191] =
      new entity(strings[1744], false, 191, (entity *)IFC4X2_types[751]);
  IFC4X2_types[200] =
      new entity(strings[1745], false, 200, (entity *)IFC4X2_types[1129]);
  IFC4X2_types[201] =
      new entity(strings[1746], false, 201, (entity *)IFC4X2_types[202]);
  IFC4X2_types[203] =
      new entity(strings[1747], false, 203, (entity *)IFC4X2_types[204]);
  IFC4X2_types[223] =
      new entity(strings[1748], false, 223, (entity *)IFC4X2_types[641]);
  IFC4X2_types[228] =
      new entity(strings[1749], false, 228, (entity *)IFC4X2_types[641]);
  IFC4X2_types[229] =
      new entity(strings[1750], false, 229, (entity *)IFC4X2_types[228]);
  IFC4X2_types[255] =
      new entity(strings[1751], false, 255, (entity *)IFC4X2_types[892]);
  IFC4X2_types[268] =
      new entity(strings[1752], false, 268, (entity *)IFC4X2_types[737]);
  IFC4X2_types[269] =
      new entity(strings[1753], false, 269, (entity *)IFC4X2_types[734]);
  IFC4X2_types[270] =
      new entity(strings[1754], false, 270, (entity *)IFC4X2_types[734]);
  IFC4X2_types[271] =
      new entity(strings[1755], false, 271, (entity *)IFC4X2_types[734]);
  IFC4X2_types[286] =
      new entity(strings[1756], false, 286, (entity *)IFC4X2_types[751]);
  IFC4X2_types[314] =
      new entity(strings[1757], false, 314, (entity *)IFC4X2_types[402]);
  IFC4X2_types[315] =
      new entity(strings[1758], false, 315, (entity *)IFC4X2_types[892]);
  IFC4X2_types[316] =
      new entity(strings[1759], false, 316, (entity *)IFC4X2_types[406]);
  IFC4X2_types[345] =
      new entity(strings[1760], false, 345, (entity *)IFC4X2_types[1129]);
  IFC4X2_types[346] =
      new entity(strings[1761], false, 346, (entity *)IFC4X2_types[345]);
  IFC4X2_types[397] =
      new entity(strings[1762], false, 397, (entity *)IFC4X2_types[913]);
  IFC4X2_types[401] =
      new entity(strings[1763], true, 401, (entity *)IFC4X2_types[763]);
  IFC4X2_types[407] =
      new entity(strings[1764], false, 407, (entity *)IFC4X2_types[892]);
  IFC4X2_types[413] =
      new entity(strings[1765], false, 413, (entity *)IFC4X2_types[1129]);
  IFC4X2_types[415] =
      new entity(strings[1766], false, 415, (entity *)IFC4X2_types[1129]);
  IFC4X2_types[416] =
      new entity(strings[1767], false, 416, (entity *)IFC4X2_types[415]);
  IFC4X2_types[417] =
      new entity(strings[1768], false, 417, (entity *)IFC4X2_types[413]);
  IFC4X2_types[422] =
      new entity(strings[1769], false, 422, (entity *)IFC4X2_types[997]);
  IFC4X2_types[432] =
      new entity(strings[1770], false, 432, (entity *)IFC4X2_types[737]);
  IFC4X2_types[482] =
      new entity(strings[1771], false, 482, (entity *)IFC4X2_types[886]);
  IFC4X2_types[483] =
      new entity(strings[1772], true, 483, (entity *)IFC4X2_types[887]);
  IFC4X2_types[484] =
      new entity(strings[1773], false, 484, (entity *)IFC4X2_types[482]);
  IFC4X2_types[485] =
      new entity(strings[1774], false, 485, (entity *)IFC4X2_types[483]);
  IFC4X2_types[491] =
      new entity(strings[1775], false, 491, (entity *)IFC4X2_types[650]);
  IFC4X2_types[495] =
      new entity(strings[1776], false, 495, (entity *)IFC4X2_types[483]);
  IFC4X2_types[507] =
      new entity(strings[1777], false, 507, (entity *)IFC4X2_types[1059]);
  IFC4X2_types[508] =
      new entity(strings[1778], false, 508, (entity *)IFC4X2_types[734]);
  IFC4X2_types[512] =
      new entity(strings[1779], true, 512, (entity *)IFC4X2_types[1110]);
  IFC4X2_types[513] =
      new entity(strings[1780], false, 513, (entity *)IFC4X2_types[512]);
  IFC4X2_types[525] =
      new entity(strings[1781], false, 525, (entity *)IFC4X2_types[1125]);
  IFC4X2_types[538] =
      new entity(strings[1782], false, 538, (entity *)IFC4X2_types[913]);
  IFC4X2_types[557] =
      new entity(strings[1783], true, 557, (entity *)IFC4X2_types[483]);
  IFC4X2_types[558] =
      new entity(strings[1784], false, 558, (entity *)IFC4X2_types[557]);
  IFC4X2_types[559] =
      new entity(strings[1785], false, 559, (entity *)IFC4X2_types[557]);
  IFC4X2_types[560] =
      new entity(strings[1786], false, 560, (entity *)IFC4X2_types[557]);
  IFC4X2_types[561] =
      new entity(strings[1787], false, 561, (entity *)IFC4X2_types[557]);
  IFC4X2_types[562] =
      new entity(strings[1788], false, 562, (entity *)IFC4X2_types[561]);
  IFC4X2_types[566] =
      new entity(strings[1789], false, 566, (entity *)IFC4X2_types[650]);
  IFC4X2_types[573] =
      new entity(strings[1790], false, 573, (entity *)IFC4X2_types[650]);
  IFC4X2_types[576] =
      new entity(strings[1791], false, 576, (entity *)IFC4X2_types[1129]);
  IFC4X2_types[585] =
      new entity(strings[1792], false, 585, (entity *)IFC4X2_types[887]);
  IFC4X2_types[590] =
      new entity(strings[1793], false, 590, (entity *)IFC4X2_types[594]);
  IFC4X2_types[592] =
      new entity(strings[1794], false, 592, (entity *)IFC4X2_types[594]);
  IFC4X2_types[593] =
      new entity(strings[1795], false, 593, (entity *)IFC4X2_types[594]);
  IFC4X2_types[595] =
      new entity(strings[1796], false, 595, (entity *)IFC4X2_types[748]);
  IFC4X2_types[598] =
      new entity(strings[1797], false, 598, (entity *)IFC4X2_types[609]);
  IFC4X2_types[603] =
      new entity(strings[1798], false, 603, (entity *)IFC4X2_types[609]);
  IFC4X2_types[604] =
      new entity(strings[1799], false, 604, (entity *)IFC4X2_types[603]);
  IFC4X2_types[606] =
      new entity(strings[1800], false, 606, (entity *)IFC4X2_types[401]);
  IFC4X2_types[607] =
      new entity(strings[1801], false, 607, (entity *)IFC4X2_types[892]);
  IFC4X2_types[624] =
      new entity(strings[1802], false, 624, (entity *)IFC4X2_types[286]);
  IFC4X2_types[647] =
      new entity(strings[1803], true, 647, (entity *)IFC4X2_types[904]);
  IFC4X2_types[662] =
      new entity(strings[1804], false, 662, (entity *)IFC4X2_types[200]);
  IFC4X2_types[664] =
      new entity(strings[1805], false, 664, (entity *)IFC4X2_types[892]);
  IFC4X2_types[665] =
      new entity(strings[1806], false, 665, (entity *)IFC4X2_types[483]);
  IFC4X2_types[666] =
      new entity(strings[1807], false, 666, (entity *)IFC4X2_types[345]);
  IFC4X2_types[672] =
      new entity(strings[1808], true, 672, (entity *)IFC4X2_types[751]);
  IFC4X2_types[674] =
      new entity(strings[1809], false, 674, (entity *)IFC4X2_types[1129]);
  IFC4X2_types[685] =
      new entity(strings[1810], false, 685, (entity *)IFC4X2_types[687]);
  IFC4X2_types[699] =
      new entity(strings[1811], false, 699, (entity *)IFC4X2_types[1059]);
  IFC4X2_types[700] =
      new entity(strings[1812], true, 700, (entity *)IFC4X2_types[483]);
  IFC4X2_types[702] =
      new entity(strings[1813], false, 702, (entity *)IFC4X2_types[483]);
  IFC4X2_types[710] =
      new entity(strings[1814], true, 710, (entity *)IFC4X2_types[483]);
  IFC4X2_types[711] =
      new entity(strings[1815], false, 711, (entity *)IFC4X2_types[710]);
  IFC4X2_types[712] =
      new entity(strings[1816], false, 712, (entity *)IFC4X2_types[710]);
  IFC4X2_types[717] =
      new entity(strings[1817], false, 717, (entity *)IFC4X2_types[576]);
  IFC4X2_types[714] =
      new entity(strings[1818], false, 714, (entity *)IFC4X2_types[495]);
  IFC4X2_types[728] =
      new entity(strings[1819], true, 728, (entity *)IFC4X2_types[734]);
  IFC4X2_types[729] =
      new entity(strings[1820], true, 729, (entity *)IFC4X2_types[763]);
  IFC4X2_types[731] =
      new entity(strings[1821], true, 731, (entity *)IFC4X2_types[728]);
  IFC4X2_types[747] =
      new entity(strings[1822], false, 747, (entity *)IFC4X2_types[748]);
  IFC4X2_types[752] =
      new entity(strings[1823], false, 752, (entity *)IFC4X2_types[401]);
  IFC4X2_types[762] =
      new entity(strings[1824], true, 762, (entity *)IFC4X2_types[763]);
  IFC4X2_types[765] =
      new entity(strings[1825], true, 765, (entity *)IFC4X2_types[904]);
  IFC4X2_types[766] =
      new entity(strings[1826], false, 766, (entity *)IFC4X2_types[892]);
  IFC4X2_types[772] =
      new entity(strings[1827], true, 772, (entity *)IFC4X2_types[765]);
  IFC4X2_types[780] =
      new entity(strings[1828], true, 780, (entity *)IFC4X2_types[765]);
  IFC4X2_types[794] =
      new entity(strings[1829], true, 794, (entity *)IFC4X2_types[772]);
  IFC4X2_types[813] =
      new entity(strings[1830], false, 813, (entity *)IFC4X2_types[672]);
  IFC4X2_types[822] =
      new entity(strings[1831], false, 822, (entity *)IFC4X2_types[1125]);
  IFC4X2_types[823] =
      new entity(strings[1832], false, 823, (entity *)IFC4X2_types[729]);
  IFC4X2_types[851] =
      new entity(strings[1833], true, 851, (entity *)IFC4X2_types[904]);
  IFC4X2_types[890] =
      new entity(strings[1834], false, 890, (entity *)IFC4X2_types[892]);
  IFC4X2_types[891] =
      new entity(strings[1835], false, 891, (entity *)IFC4X2_types[892]);
  IFC4X2_types[895] =
      new entity(strings[1836], false, 895, (entity *)IFC4X2_types[913]);
  IFC4X2_types[909] =
      new entity(strings[1837], false, 909, (entity *)IFC4X2_types[813]);
  IFC4X2_types[920] =
      new entity(strings[1838], false, 920, (entity *)IFC4X2_types[729]);
  IFC4X2_types[921] =
      new entity(strings[1839], false, 921, (entity *)IFC4X2_types[729]);
  IFC4X2_types[918] =
      new entity(strings[1840], false, 918, (entity *)IFC4X2_types[483]);
  IFC4X2_types[936] =
      new entity(strings[1841], false, 936, (entity *)IFC4X2_types[483]);
  IFC4X2_types[937] =
      new entity(strings[1842], true, 937, (entity *)IFC4X2_types[762]);
  IFC4X2_types[951] =
      new entity(strings[1843], false, 951, (entity *)IFC4X2_types[997]);
  IFC4X2_types[956] =
      new entity(strings[1844], true, 956, (entity *)IFC4X2_types[483]);
  IFC4X2_types[1011] =
      new entity(strings[1845], false, 1011, (entity *)IFC4X2_types[1018]);
  IFC4X2_types[1013] =
      new entity(strings[1846], false, 1013, (entity *)IFC4X2_types[1018]);
  IFC4X2_types[1014] =
      new entity(strings[1847], false, 1014, (entity *)IFC4X2_types[1018]);
  IFC4X2_types[1015] =
      new entity(strings[1848], false, 1015, (entity *)IFC4X2_types[1014]);
  IFC4X2_types[1016] =
      new entity(strings[1849], false, 1016, (entity *)IFC4X2_types[1018]);
  IFC4X2_types[1017] =
      new entity(strings[1850], false, 1017, (entity *)IFC4X2_types[1016]);
  IFC4X2_types[1041] =
      new entity(strings[1851], false, 1041, (entity *)IFC4X2_types[345]);
  IFC4X2_types[1042] =
      new entity(strings[1852], true, 1042, (entity *)IFC4X2_types[483]);
  IFC4X2_types[1056] =
      new entity(strings[1853], false, 1056, (entity *)IFC4X2_types[1057]);
  IFC4X2_types[1060] =
      new entity(strings[1854], true, 1060, (entity *)IFC4X2_types[956]);
  IFC4X2_types[1061] =
      new entity(strings[1855], false, 1061, (entity *)IFC4X2_types[956]);
  IFC4X2_types[1062] =
      new entity(strings[1856], false, 1062, (entity *)IFC4X2_types[1061]);
  IFC4X2_types[1063] =
      new entity(strings[1857], true, 1063, (entity *)IFC4X2_types[1042]);
  IFC4X2_types[1149] =
      new entity(strings[1858], false, 1149, (entity *)IFC4X2_types[672]);
  IFC4X2_types[1096] =
      new entity(strings[1859], true, 1096, (entity *)IFC4X2_types[483]);
  IFC4X2_types[1102] =
      new entity(strings[1860], false, 1102, (entity *)IFC4X2_types[483]);
  IFC4X2_types[1103] =
      new entity(strings[1861], false, 1103, (entity *)IFC4X2_types[1102]);
  IFC4X2_types[1106] =
      new entity(strings[1862], false, 1106, (entity *)IFC4X2_types[731]);
  IFC4X2_types[1143] =
      new entity(strings[1863], false, 1143, (entity *)IFC4X2_types[672]);
  IFC4X2_types[1153] =
      new entity(strings[1864], false, 1153, (entity *)IFC4X2_types[647]);
  IFC4X2_types[1154] =
      new entity(strings[1865], true, 1154, (entity *)IFC4X2_types[1153]);
  IFC4X2_types[1155] =
      new entity(strings[1866], false, 1155, (entity *)IFC4X2_types[1153]);
  IFC4X2_types[1156] =
      new entity(strings[1867], true, 1156, (entity *)IFC4X2_types[1153]);
  IFC4X2_types[1167] =
      new entity(strings[1868], false, 1167, (entity *)IFC4X2_types[672]);
  IFC4X2_types[1173] =
      new entity(strings[1869], false, 1173, (entity *)IFC4X2_types[483]);
  IFC4X2_types[1176] =
      new entity(strings[1870], false, 1176, (entity *)IFC4X2_types[576]);
  IFC4X2_types[1207] =
      new entity(strings[1871], false, 1207, (entity *)IFC4X2_types[1155]);
  IFC4X2_types[1222] =
      new entity(strings[1872], false, 1222, (entity *)IFC4X2_types[672]);
  IFC4X2_types[166] = new select_type(strings[1873], 166,
                                      {IFC4X2_types[164], IFC4X2_types[165]});
  IFC4X2_types[167] = new select_type(strings[1874], 167,
                                      {IFC4X2_types[164], IFC4X2_types[165]});
  IFC4X2_types[238] = new select_type(strings[1875], 238,
                                      {IFC4X2_types[237], IFC4X2_types[482]});
  IFC4X2_types[284] = new select_type(strings[1876], 284,
                                      {IFC4X2_types[647], IFC4X2_types[765]});
  IFC4X2_types[317] = new select_type(strings[1877], 317,
                                      {IFC4X2_types[314], IFC4X2_types[316]});
  IFC4X2_types[496] = new select_type(strings[1878], 496,
                                      {IFC4X2_types[721], IFC4X2_types[1173]});
  IFC4X2_types[610] = new select_type(
      strings[1879], 610,
      {IFC4X2_types[40],   IFC4X2_types[56],  IFC4X2_types[184],
       IFC4X2_types[222],  IFC4X2_types[244], IFC4X2_types[290],
       IFC4X2_types[354],  IFC4X2_types[545], IFC4X2_types[580],
       IFC4X2_types[588],  IFC4X2_types[642], IFC4X2_types[643],
       IFC4X2_types[645],  IFC4X2_types[673], IFC4X2_types[705],
       IFC4X2_types[721],  IFC4X2_types[722], IFC4X2_types[723],
       IFC4X2_types[808],  IFC4X2_types[955], IFC4X2_types[1120],
       IFC4X2_types[1122], IFC4X2_types[1188]});
  IFC4X2_types[713] = new select_type(strings[1880], 713,
                                      {IFC4X2_types[710], IFC4X2_types[1177]});
  IFC4X2_types[739] =
      new select_type(strings[1881], 739,
                      {IFC4X2_types[268], IFC4X2_types[432], IFC4X2_types[644],
                       IFC4X2_types[1052], IFC4X2_types[1105]});
  IFC4X2_types[749] = new select_type(strings[1882], 749,
                                      {IFC4X2_types[747], IFC4X2_types[888]});
  IFC4X2_types[774] = new type_declaration(
      strings[1883], 774,
      new aggregation_type(aggregation_type::set_type, 1, -1,
                           new named_type(IFC4X2_types[772])));
  IFC4X2_types[893] =
      new select_type(strings[1884], 893,
                      {IFC4X2_types[7], IFC4X2_types[47], IFC4X2_types[49],
                       IFC4X2_types[208], IFC4X2_types[223], IFC4X2_types[228],
                       IFC4X2_types[402], IFC4X2_types[406], IFC4X2_types[594],
                       IFC4X2_types[663], IFC4X2_types[682], IFC4X2_types[683],
                       IFC4X2_types[687], IFC4X2_types[751], IFC4X2_types[763],
                       IFC4X2_types[931], IFC4X2_types[1125]});
  IFC4X2_types[1101] = new select_type(strings[1885], 1101,
                                       {IFC4X2_types[405], IFC4X2_types[731]});
  IFC4X2_types[1168] = new select_type(
      strings[1886], 1168,
      {IFC4X2_types[285], IFC4X2_types[610], IFC4X2_types[940]});
  IFC4X2_types[16] =
      new entity(strings[1887], false, 16, (entity *)IFC4X2_types[417]);
  IFC4X2_types[30] =
      new entity(strings[1888], false, 30, (entity *)IFC4X2_types[483]);
  IFC4X2_types[32] =
      new entity(strings[1889], true, 32, (entity *)IFC4X2_types[483]);
  IFC4X2_types[36] =
      new entity(strings[1890], false, 36, (entity *)IFC4X2_types[483]);
  IFC4X2_types[37] =
      new entity(strings[1891], true, 37, (entity *)IFC4X2_types[32]);
  IFC4X2_types[45] =
      new entity(strings[1892], false, 45, (entity *)IFC4X2_types[483]);
  IFC4X2_types[60] =
      new entity(strings[1893], false, 60, (entity *)IFC4X2_types[672]);
  IFC4X2_types[64] =
      new entity(strings[1894], false, 64, (entity *)IFC4X2_types[700]);
  IFC4X2_types[66] =
      new entity(strings[1895], false, 66, (entity *)IFC4X2_types[700]);
  IFC4X2_types[67] =
      new entity(strings[1896], false, 67, (entity *)IFC4X2_types[700]);
  IFC4X2_types[88] =
      new entity(strings[1897], false, 88, (entity *)IFC4X2_types[483]);
  IFC4X2_types[96] =
      new entity(strings[1898], true, 96, (entity *)IFC4X2_types[1042]);
  IFC4X2_types[97] =
      new entity(strings[1899], false, 97, (entity *)IFC4X2_types[483]);
  IFC4X2_types[99] =
      new entity(strings[1900], false, 99, (entity *)IFC4X2_types[495]);
  IFC4X2_types[254] =
      new entity(strings[1901], false, 254, (entity *)IFC4X2_types[672]);
  IFC4X2_types[141] =
      new entity(strings[1902], false, 141, (entity *)IFC4X2_types[710]);
  IFC4X2_types[142] =
      new entity(strings[1903], true, 142, (entity *)IFC4X2_types[483]);
  IFC4X2_types[143] =
      new entity(strings[1904], false, 143, (entity *)IFC4X2_types[142]);
  IFC4X2_types[144] =
      new entity(strings[1905], false, 144, (entity *)IFC4X2_types[142]);
  IFC4X2_types[145] =
      new entity(strings[1906], true, 145, (entity *)IFC4X2_types[483]);
  IFC4X2_types[146] =
      new entity(strings[1907], false, 146, (entity *)IFC4X2_types[145]);
  IFC4X2_types[147] =
      new entity(strings[1908], false, 147, (entity *)IFC4X2_types[146]);
  IFC4X2_types[148] =
      new entity(strings[1909], false, 148, (entity *)IFC4X2_types[145]);
  IFC4X2_types[149] =
      new entity(strings[1910], false, 149, (entity *)IFC4X2_types[148]);
  IFC4X2_types[160] =
      new entity(strings[1911], false, 160, (entity *)IFC4X2_types[672]);
  IFC4X2_types[168] =
      new entity(strings[1912], false, 168, (entity *)IFC4X2_types[200]);
  IFC4X2_types[174] =
      new entity(strings[1913], false, 174, (entity *)IFC4X2_types[176]);
  IFC4X2_types[185] =
      new entity(strings[1914], false, 185, (entity *)IFC4X2_types[762]);
  IFC4X2_types[190] =
      new entity(strings[1915], false, 190, (entity *)IFC4X2_types[483]);
  IFC4X2_types[220] =
      new entity(strings[1916], true, 220, (entity *)IFC4X2_types[1156]);
  IFC4X2_types[221] =
      new entity(strings[1917], true, 221, (entity *)IFC4X2_types[647]);
  IFC4X2_types[249] =
      new entity(strings[1918], false, 249, (entity *)IFC4X2_types[220]);
  IFC4X2_types[251] =
      new entity(strings[1919], true, 251, (entity *)IFC4X2_types[483]);
  IFC4X2_types[253] =
      new entity(strings[1920], false, 253, (entity *)IFC4X2_types[956]);
  IFC4X2_types[260] =
      new entity(strings[1921], true, 260, (entity *)IFC4X2_types[483]);
  IFC4X2_types[261] =
      new entity(strings[1922], false, 261, (entity *)IFC4X2_types[96]);
  IFC4X2_types[262] =
      new entity(strings[1923], false, 262, (entity *)IFC4X2_types[96]);
  IFC4X2_types[293] =
      new entity(strings[1924], false, 293, (entity *)IFC4X2_types[483]);
  IFC4X2_types[298] =
      new entity(strings[1925], false, 298, (entity *)IFC4X2_types[483]);
  IFC4X2_types[325] =
      new entity(strings[1926], false, 325, (entity *)IFC4X2_types[1155]);
  IFC4X2_types[347] =
      new entity(strings[1927], false, 347, (entity *)IFC4X2_types[576]);
  IFC4X2_types[380] =
      new entity(strings[1928], false, 380, (entity *)IFC4X2_types[794]);
  IFC4X2_types[381] =
      new entity(strings[1929], true, 381, (entity *)IFC4X2_types[1155]);
  IFC4X2_types[373] =
      new entity(strings[1930], true, 373, (entity *)IFC4X2_types[1042]);
  IFC4X2_types[383] =
      new entity(strings[1931], false, 383, (entity *)IFC4X2_types[672]);
  IFC4X2_types[399] =
      new entity(strings[1932], false, 399, (entity *)IFC4X2_types[1154]);
  IFC4X2_types[411] =
      new entity(strings[1933], false, 411, (entity *)IFC4X2_types[1060]);
  IFC4X2_types[412] =
      new entity(strings[1934], false, 412, (entity *)IFC4X2_types[411]);
  IFC4X2_types[414] =
      new entity(strings[1935], false, 414, (entity *)IFC4X2_types[483]);
  IFC4X2_types[433] =
      new entity(strings[1936], false, 433, (entity *)IFC4X2_types[483]);
  IFC4X2_types[434] =
      new entity(strings[1937], false, 434, (entity *)IFC4X2_types[483]);
  IFC4X2_types[442] =
      new entity(strings[1938], false, 442, (entity *)IFC4X2_types[1060]);
  IFC4X2_types[473] =
      new entity(strings[1939], false, 473, (entity *)IFC4X2_types[381]);
  IFC4X2_types[475] =
      new entity(strings[1940], false, 475, (entity *)IFC4X2_types[473]);
  IFC4X2_types[478] =
      new entity(strings[1941], false, 478, (entity *)IFC4X2_types[381]);
  IFC4X2_types[480] =
      new entity(strings[1942], false, 480, (entity *)IFC4X2_types[485]);
  IFC4X2_types[527] =
      new entity(strings[1943], false, 527, (entity *)IFC4X2_types[672]);
  IFC4X2_types[510] =
      new entity(strings[1944], false, 510, (entity *)IFC4X2_types[1096]);
  IFC4X2_types[511] =
      new entity(strings[1945], false, 511, (entity *)IFC4X2_types[510]);
  IFC4X2_types[577] =
      new entity(strings[1946], false, 577, (entity *)IFC4X2_types[672]);
  IFC4X2_types[536] =
      new entity(strings[1947], false, 536, (entity *)IFC4X2_types[220]);
  IFC4X2_types[563] =
      new entity(strings[1948], false, 563, (entity *)IFC4X2_types[260]);
  IFC4X2_types[583] =
      new entity(strings[1949], true, 583, (entity *)IFC4X2_types[956]);
  IFC4X2_types[646] =
      new entity(strings[1950], true, 646, (entity *)IFC4X2_types[647]);
  IFC4X2_types[655] =
      new entity(strings[1951], true, 655, (entity *)IFC4X2_types[260]);
  IFC4X2_types[656] =
      new entity(strings[1952], false, 656, (entity *)IFC4X2_types[655]);
  IFC4X2_types[657] =
      new entity(strings[1953], false, 657, (entity *)IFC4X2_types[655]);
  IFC4X2_types[658] =
      new entity(strings[1954], false, 658, (entity *)IFC4X2_types[655]);
  IFC4X2_types[675] =
      new entity(strings[1955], false, 675, (entity *)IFC4X2_types[260]);
  IFC4X2_types[701] =
      new entity(strings[1956], false, 701, (entity *)IFC4X2_types[702]);
  IFC4X2_types[704] =
      new entity(strings[1957], false, 704, (entity *)IFC4X2_types[373]);
  IFC4X2_types[726] =
      new entity(strings[1958], true, 726, (entity *)IFC4X2_types[728]);
  IFC4X2_types[727] =
      new entity(strings[1959], true, 727, (entity *)IFC4X2_types[728]);
  IFC4X2_types[730] =
      new entity(strings[1960], true, 730, (entity *)IFC4X2_types[772]);
  IFC4X2_types[742] =
      new entity(strings[1961], false, 742, (entity *)IFC4X2_types[1154]);
  IFC4X2_types[744] =
      new entity(strings[1962], true, 744, (entity *)IFC4X2_types[646]);
  IFC4X2_types[746] =
      new entity(strings[1963], true, 746, (entity *)IFC4X2_types[646]);
  IFC4X2_types[754] =
      new entity(strings[1964], false, 754, (entity *)IFC4X2_types[221]);
  IFC4X2_types[759] =
      new entity(strings[1965], false, 759, (entity *)IFC4X2_types[221]);
  IFC4X2_types[764] =
      new entity(strings[1966], false, 764, (entity *)IFC4X2_types[937]);
  IFC4X2_types[767] =
      new entity(strings[1967], false, 767, (entity *)IFC4X2_types[937]);
  IFC4X2_types[769] =
      new entity(strings[1968], false, 769, (entity *)IFC4X2_types[937]);
  IFC4X2_types[770] =
      new entity(strings[1969], false, 770, (entity *)IFC4X2_types[937]);
  IFC4X2_types[771] =
      new entity(strings[1970], false, 771, (entity *)IFC4X2_types[772]);
  IFC4X2_types[775] =
      new entity(strings[1971], false, 775, (entity *)IFC4X2_types[780]);
  IFC4X2_types[777] =
      new entity(strings[1972], false, 777, (entity *)IFC4X2_types[937]);
  IFC4X2_types[778] =
      new entity(strings[1973], false, 778, (entity *)IFC4X2_types[937]);
  IFC4X2_types[779] =
      new entity(strings[1974], true, 779, (entity *)IFC4X2_types[780]);
  IFC4X2_types[787] =
      new entity(strings[1975], false, 787, (entity *)IFC4X2_types[746]);
  IFC4X2_types[812] =
      new entity(strings[1976], false, 812, (entity *)IFC4X2_types[813]);
  IFC4X2_types[814] =
      new entity(strings[1977], false, 814, (entity *)IFC4X2_types[251]);
  IFC4X2_types[815] =
      new entity(strings[1978], false, 815, (entity *)IFC4X2_types[96]);
  IFC4X2_types[824] =
      new entity(strings[1979], false, 824, (entity *)IFC4X2_types[730]);
  IFC4X2_types[836] =
      new entity(strings[1980], true, 836, (entity *)IFC4X2_types[851]);
  IFC4X2_types[837] =
      new entity(strings[1981], false, 837, (entity *)IFC4X2_types[836]);
  IFC4X2_types[838] =
      new entity(strings[1982], false, 838, (entity *)IFC4X2_types[836]);
  IFC4X2_types[839] =
      new entity(strings[1983], false, 839, (entity *)IFC4X2_types[836]);
  IFC4X2_types[840] =
      new entity(strings[1984], false, 840, (entity *)IFC4X2_types[839]);
  IFC4X2_types[841] =
      new entity(strings[1985], false, 841, (entity *)IFC4X2_types[836]);
  IFC4X2_types[842] =
      new entity(strings[1986], false, 842, (entity *)IFC4X2_types[836]);
  IFC4X2_types[843] =
      new entity(strings[1987], false, 843, (entity *)IFC4X2_types[836]);
  IFC4X2_types[844] =
      new entity(strings[1988], true, 844, (entity *)IFC4X2_types[851]);
  IFC4X2_types[845] =
      new entity(strings[1989], false, 845, (entity *)IFC4X2_types[844]);
  IFC4X2_types[846] =
      new entity(strings[1990], false, 846, (entity *)IFC4X2_types[844]);
  IFC4X2_types[847] =
      new entity(strings[1991], false, 847, (entity *)IFC4X2_types[844]);
  IFC4X2_types[848] =
      new entity(strings[1992], false, 848, (entity *)IFC4X2_types[844]);
  IFC4X2_types[849] =
      new entity(strings[1993], false, 849, (entity *)IFC4X2_types[844]);
  IFC4X2_types[850] =
      new entity(strings[1994], false, 850, (entity *)IFC4X2_types[844]);
  IFC4X2_types[852] =
      new entity(strings[1995], true, 852, (entity *)IFC4X2_types[851]);
  IFC4X2_types[853] =
      new entity(strings[1996], false, 853, (entity *)IFC4X2_types[852]);
  IFC4X2_types[854] =
      new entity(strings[1997], false, 854, (entity *)IFC4X2_types[853]);
  IFC4X2_types[856] =
      new entity(strings[1998], false, 856, (entity *)IFC4X2_types[852]);
  IFC4X2_types[855] =
      new entity(strings[1999], false, 855, (entity *)IFC4X2_types[852]);
  IFC4X2_types[857] =
      new entity(strings[2000], false, 857, (entity *)IFC4X2_types[852]);
  IFC4X2_types[858] =
      new entity(strings[2001], false, 858, (entity *)IFC4X2_types[852]);
  IFC4X2_types[859] =
      new entity(strings[2002], false, 859, (entity *)IFC4X2_types[858]);
  IFC4X2_types[860] =
      new entity(strings[2003], false, 860, (entity *)IFC4X2_types[853]);
  IFC4X2_types[861] =
      new entity(strings[2004], false, 861, (entity *)IFC4X2_types[852]);
  IFC4X2_types[862] =
      new entity(strings[2005], false, 862, (entity *)IFC4X2_types[852]);
  IFC4X2_types[863] =
      new entity(strings[2006], false, 863, (entity *)IFC4X2_types[852]);
  IFC4X2_types[864] =
      new entity(strings[2007], false, 864, (entity *)IFC4X2_types[851]);
  IFC4X2_types[865] =
      new entity(strings[2008], true, 865, (entity *)IFC4X2_types[851]);
  IFC4X2_types[866] =
      new entity(strings[2009], true, 866, (entity *)IFC4X2_types[851]);
  IFC4X2_types[867] =
      new entity(strings[2010], false, 867, (entity *)IFC4X2_types[866]);
  IFC4X2_types[868] =
      new entity(strings[2011], false, 868, (entity *)IFC4X2_types[866]);
  IFC4X2_types[869] =
      new entity(strings[2012], false, 869, (entity *)IFC4X2_types[866]);
  IFC4X2_types[870] =
      new entity(strings[2013], false, 870, (entity *)IFC4X2_types[866]);
  IFC4X2_types[871] =
      new entity(strings[2014], false, 871, (entity *)IFC4X2_types[852]);
  IFC4X2_types[872] =
      new entity(strings[2015], false, 872, (entity *)IFC4X2_types[852]);
  IFC4X2_types[873] =
      new entity(strings[2016], false, 873, (entity *)IFC4X2_types[852]);
  IFC4X2_types[874] =
      new entity(strings[2017], false, 874, (entity *)IFC4X2_types[865]);
  IFC4X2_types[875] =
      new entity(strings[2018], false, 875, (entity *)IFC4X2_types[852]);
  IFC4X2_types[876] =
      new entity(strings[2019], false, 876, (entity *)IFC4X2_types[865]);
  IFC4X2_types[877] =
      new entity(strings[2020], false, 877, (entity *)IFC4X2_types[852]);
  IFC4X2_types[878] =
      new entity(strings[2021], false, 878, (entity *)IFC4X2_types[852]);
  IFC4X2_types[879] =
      new entity(strings[2022], false, 879, (entity *)IFC4X2_types[852]);
  IFC4X2_types[880] =
      new entity(strings[2023], false, 880, (entity *)IFC4X2_types[852]);
  IFC4X2_types[881] =
      new entity(strings[2024], false, 881, (entity *)IFC4X2_types[880]);
  IFC4X2_types[882] =
      new entity(strings[2025], false, 882, (entity *)IFC4X2_types[881]);
  IFC4X2_types[883] =
      new entity(strings[2026], false, 883, (entity *)IFC4X2_types[865]);
  IFC4X2_types[884] =
      new entity(strings[2027], false, 884, (entity *)IFC4X2_types[190]);
  IFC4X2_types[889] =
      new entity(strings[2028], true, 889, (entity *)IFC4X2_types[646]);
  IFC4X2_types[896] =
      new entity(strings[2029], false, 896, (entity *)IFC4X2_types[1060]);
  IFC4X2_types[897] =
      new entity(strings[2030], false, 897, (entity *)IFC4X2_types[896]);
  IFC4X2_types[898] =
      new entity(strings[2031], false, 898, (entity *)IFC4X2_types[251]);
  IFC4X2_types[899] =
      new entity(strings[2032], false, 899, (entity *)IFC4X2_types[251]);
  IFC4X2_types[916] =
      new entity(strings[2033], true, 916, (entity *)IFC4X2_types[956]);
  IFC4X2_types[917] =
      new entity(strings[2034], false, 917, (entity *)IFC4X2_types[916]);
  IFC4X2_types[938] =
      new entity(strings[2035], false, 938, (entity *)IFC4X2_types[779]);
  IFC4X2_types[969] =
      new entity(strings[2036], true, 969, (entity *)IFC4X2_types[746]);
  IFC4X2_types[970] =
      new entity(strings[2037], true, 970, (entity *)IFC4X2_types[1155]);
  IFC4X2_types[971] =
      new entity(strings[2038], true, 971, (entity *)IFC4X2_types[969]);
  IFC4X2_types[972] =
      new entity(strings[2039], true, 972, (entity *)IFC4X2_types[970]);
  IFC4X2_types[973] =
      new entity(strings[2040], false, 973, (entity *)IFC4X2_types[969]);
  IFC4X2_types[974] =
      new entity(strings[2041], false, 974, (entity *)IFC4X2_types[970]);
  IFC4X2_types[980] =
      new entity(strings[2042], false, 980, (entity *)IFC4X2_types[251]);
  IFC4X2_types[981] =
      new entity(strings[2043], false, 981, (entity *)IFC4X2_types[373]);
  IFC4X2_types[993] =
      new entity(strings[2044], true, 993, (entity *)IFC4X2_types[746]);
  IFC4X2_types[1005] =
      new entity(strings[2045], true, 1005, (entity *)IFC4X2_types[746]);
  IFC4X2_types[1020] =
      new entity(strings[2046], true, 1020, (entity *)IFC4X2_types[1005]);
  IFC4X2_types[1025] =
      new entity(strings[2047], true, 1025, (entity *)IFC4X2_types[993]);
  IFC4X2_types[1030] =
      new entity(strings[2048], false, 1030, (entity *)IFC4X2_types[1020]);
  IFC4X2_types[1032] =
      new entity(strings[2049], false, 1032, (entity *)IFC4X2_types[1030]);
  IFC4X2_types[1033] =
      new entity(strings[2050], false, 1033, (entity *)IFC4X2_types[1025]);
  IFC4X2_types[1039] =
      new entity(strings[2051], false, 1039, (entity *)IFC4X2_types[220]);
  IFC4X2_types[1043] =
      new entity(strings[2052], false, 1043, (entity *)IFC4X2_types[260]);
  IFC4X2_types[1044] =
      new entity(strings[2053], false, 1044, (entity *)IFC4X2_types[1060]);
  IFC4X2_types[1047] =
      new entity(strings[2054], false, 1047, (entity *)IFC4X2_types[1063]);
  IFC4X2_types[1048] =
      new entity(strings[2055], false, 1048, (entity *)IFC4X2_types[1063]);
  IFC4X2_types[1069] =
      new entity(strings[2056], false, 1069, (entity *)IFC4X2_types[473]);
  IFC4X2_types[1077] =
      new entity(strings[2057], false, 1077, (entity *)IFC4X2_types[744]);
  IFC4X2_types[1081] =
      new entity(strings[2058], false, 1081, (entity *)IFC4X2_types[1154]);
  IFC4X2_types[1095] =
      new entity(strings[2059], true, 1095, (entity *)IFC4X2_types[1096]);
  IFC4X2_types[1131] =
      new entity(strings[2060], false, 1131, (entity *)IFC4X2_types[373]);
  IFC4X2_types[1141] =
      new entity(strings[2061], false, 1141, (entity *)IFC4X2_types[381]);
  IFC4X2_types[1144] =
      new entity(strings[2062], false, 1144, (entity *)IFC4X2_types[1095]);
  IFC4X2_types[1145] =
      new entity(strings[2063], false, 1145, (entity *)IFC4X2_types[1144]);
  IFC4X2_types[1202] =
      new entity(strings[2064], false, 1202, (entity *)IFC4X2_types[730]);
  IFC4X2_types[1205] =
      new entity(strings[2065], false, 1205, (entity *)IFC4X2_types[730]);
  IFC4X2_types[48] = new select_type(
      strings[2066], 48,
      {IFC4X2_types[611], IFC4X2_types[818], IFC4X2_types[1168]});
  IFC4X2_types[65] =
      new select_type(strings[2067], 65, {IFC4X2_types[66], IFC4X2_types[67]});
  IFC4X2_types[86] =
      new select_type(strings[2068], 86,
                      {IFC4X2_types[88], IFC4X2_types[251], IFC4X2_types[495],
                       IFC4X2_types[956], IFC4X2_types[1095]});
  IFC4X2_types[172] = new select_type(strings[2069], 172,
                                      {IFC4X2_types[176], IFC4X2_types[726]});
  IFC4X2_types[173] = new select_type(strings[2070], 173,
                                      {IFC4X2_types[174], IFC4X2_types[643]});
  IFC4X2_types[252] = new select_type(strings[2071], 252,
                                      {IFC4X2_types[88], IFC4X2_types[251]});
  IFC4X2_types[272] = new select_type(strings[2072], 272,
                                      {IFC4X2_types[269], IFC4X2_types[727]});
  IFC4X2_types[435] = new select_type(strings[2073], 435,
                                      {IFC4X2_types[172], IFC4X2_types[403],
                                       IFC4X2_types[433], IFC4X2_types[434]});
  IFC4X2_types[486] = new select_type(
      strings[2074], 486,
      {IFC4X2_types[260], IFC4X2_types[710], IFC4X2_types[1042]});
  IFC4X2_types[492] = new select_type(strings[2075], 492,
                                      {IFC4X2_types[293], IFC4X2_types[1185]});
  IFC4X2_types[623] = new select_type(strings[2076], 623,
                                      {IFC4X2_types[47], IFC4X2_types[611],
                                       IFC4X2_types[818], IFC4X2_types[1071],
                                       IFC4X2_types[1125], IFC4X2_types[1168]});
  IFC4X2_types[745] = new select_type(strings[2077], 745,
                                      {IFC4X2_types[744], IFC4X2_types[1154]});
  IFC4X2_types[750] = new select_type(strings[2078], 750,
                                      {IFC4X2_types[746], IFC4X2_types[1155]});
  IFC4X2_types[773] = new select_type(strings[2079], 773,
                                      {IFC4X2_types[772], IFC4X2_types[774]});
  IFC4X2_types[894] = new select_type(strings[2080], 894,
                                      {IFC4X2_types[889], IFC4X2_types[1156]});
  IFC4X2_types[935] = new select_type(strings[2081], 935,
                                      {IFC4X2_types[168], IFC4X2_types[662]});
  IFC4X2_types[957] = new select_type(strings[2082], 957,
                                      {IFC4X2_types[168], IFC4X2_types[956]});
  IFC4X2_types[1049] = new select_type(
      strings[2083], 1049,
      {IFC4X2_types[414], IFC4X2_types[417], IFC4X2_types[1042]});
  IFC4X2_types[1148] = new select_type(strings[2084], 1148,
                                       {IFC4X2_types[141], IFC4X2_types[673]});
  IFC4X2_types[1174] = new select_type(strings[2085], 1174,
                                       {IFC4X2_types[293], IFC4X2_types[1173]});
  IFC4X2_types[6] =
      new entity(strings[2086], false, 6, (entity *)IFC4X2_types[646]);
  IFC4X2_types[14] =
      new entity(strings[2087], false, 14, (entity *)IFC4X2_types[583]);
  IFC4X2_types[15] =
      new entity(strings[2088], false, 15, (entity *)IFC4X2_types[14]);
  IFC4X2_types[31] =
      new entity(strings[2089], false, 31, (entity *)IFC4X2_types[32]);
  IFC4X2_types[33] =
      new entity(strings[2090], false, 33, (entity *)IFC4X2_types[37]);
  IFC4X2_types[34] =
      new entity(strings[2091], false, 34, (entity *)IFC4X2_types[37]);
  IFC4X2_types[35] =
      new entity(strings[2092], false, 35, (entity *)IFC4X2_types[37]);
  IFC4X2_types[44] =
      new entity(strings[2093], false, 44, (entity *)IFC4X2_types[746]);
  IFC4X2_types[107] =
      new entity(strings[2094], true, 107, (entity *)IFC4X2_types[96]);
  IFC4X2_types[109] =
      new entity(strings[2095], false, 109, (entity *)IFC4X2_types[107]);
  IFC4X2_types[80] =
      new entity(strings[2096], false, 80, (entity *)IFC4X2_types[251]);
  IFC4X2_types[85] =
      new entity(strings[2097], false, 85, (entity *)IFC4X2_types[88]);
  IFC4X2_types[95] =
      new entity(strings[2098], true, 95, (entity *)IFC4X2_types[260]);
  IFC4X2_types[118] =
      new entity(strings[2099], true, 118, (entity *)IFC4X2_types[381]);
  IFC4X2_types[156] =
      new entity(strings[2100], false, 156, (entity *)IFC4X2_types[118]);
  IFC4X2_types[159] =
      new entity(strings[2101], false, 159, (entity *)IFC4X2_types[160]);
  IFC4X2_types[163] =
      new entity(strings[2102], false, 163, (entity *)IFC4X2_types[381]);
  IFC4X2_types[179] =
      new entity(strings[2103], false, 179, (entity *)IFC4X2_types[118]);
  IFC4X2_types[186] =
      new entity(strings[2104], false, 186, (entity *)IFC4X2_types[779]);
  IFC4X2_types[188] =
      new entity(strings[2105], false, 188, (entity *)IFC4X2_types[95]);
  IFC4X2_types[189] =
      new entity(strings[2106], false, 189, (entity *)IFC4X2_types[188]);
  IFC4X2_types[199] =
      new entity(strings[2107], true, 199, (entity *)IFC4X2_types[260]);
  IFC4X2_types[211] =
      new entity(strings[2108], false, 211, (entity *)IFC4X2_types[220]);
  IFC4X2_types[214] =
      new entity(strings[2109], false, 214, (entity *)IFC4X2_types[220]);
  IFC4X2_types[217] =
      new entity(strings[2110], false, 217, (entity *)IFC4X2_types[220]);
  IFC4X2_types[219] =
      new entity(strings[2111], true, 219, (entity *)IFC4X2_types[889]);
  IFC4X2_types[224] =
      new entity(strings[2112], true, 224, (entity *)IFC4X2_types[646]);
  IFC4X2_types[239] =
      new entity(strings[2113], false, 239, (entity *)IFC4X2_types[224]);
  IFC4X2_types[241] =
      new entity(strings[2114], false, 241, (entity *)IFC4X2_types[224]);
  IFC4X2_types[246] =
      new entity(strings[2115], false, 246, (entity *)IFC4X2_types[118]);
  IFC4X2_types[248] =
      new entity(strings[2116], false, 248, (entity *)IFC4X2_types[219]);
  IFC4X2_types[257] =
      new entity(strings[2117], false, 257, (entity *)IFC4X2_types[118]);
  IFC4X2_types[267] =
      new entity(strings[2118], true, 267, (entity *)IFC4X2_types[95]);
  IFC4X2_types[273] =
      new entity(strings[2119], false, 273, (entity *)IFC4X2_types[373]);
  IFC4X2_types[283] =
      new entity(strings[2120], false, 283, (entity *)IFC4X2_types[118]);
  IFC4X2_types[306] =
      new entity(strings[2121], false, 306, (entity *)IFC4X2_types[381]);
  IFC4X2_types[308] =
      new entity(strings[2122], true, 308, (entity *)IFC4X2_types[306]);
  IFC4X2_types[320] =
      new entity(strings[2123], false, 320, (entity *)IFC4X2_types[730]);
  IFC4X2_types[323] =
      new entity(strings[2124], false, 323, (entity *)IFC4X2_types[730]);
  IFC4X2_types[328] =
      new entity(strings[2125], false, 328, (entity *)IFC4X2_types[118]);
  IFC4X2_types[332] =
      new entity(strings[2126], false, 332, (entity *)IFC4X2_types[726]);
  IFC4X2_types[333] =
      new entity(strings[2127], false, 333, (entity *)IFC4X2_types[727]);
  IFC4X2_types[372] =
      new entity(strings[2128], true, 372, (entity *)IFC4X2_types[746]);
  IFC4X2_types[374] =
      new entity(strings[2129], false, 374, (entity *)IFC4X2_types[372]);
  IFC4X2_types[375] =
      new entity(strings[2130], false, 375, (entity *)IFC4X2_types[381]);
  IFC4X2_types[377] =
      new entity(strings[2131], true, 377, (entity *)IFC4X2_types[372]);
  IFC4X2_types[378] =
      new entity(strings[2132], true, 378, (entity *)IFC4X2_types[381]);
  IFC4X2_types[382] =
      new entity(strings[2133], false, 382, (entity *)IFC4X2_types[199]);
  IFC4X2_types[385] =
      new entity(strings[2134], true, 385, (entity *)IFC4X2_types[308]);
  IFC4X2_types[388] =
      new entity(strings[2135], false, 388, (entity *)IFC4X2_types[385]);
  IFC4X2_types[391] =
      new entity(strings[2136], false, 391, (entity *)IFC4X2_types[385]);
  IFC4X2_types[394] =
      new entity(strings[2137], false, 394, (entity *)IFC4X2_types[385]);
  IFC4X2_types[396] =
      new entity(strings[2138], false, 396, (entity *)IFC4X2_types[744]);
  IFC4X2_types[410] =
      new entity(strings[2139], true, 410, (entity *)IFC4X2_types[969]);
  IFC4X2_types[418] =
      new entity(strings[2140], false, 418, (entity *)IFC4X2_types[583]);
  IFC4X2_types[419] =
      new entity(strings[2141], false, 419, (entity *)IFC4X2_types[418]);
  IFC4X2_types[420] =
      new entity(strings[2142], false, 420, (entity *)IFC4X2_types[971]);
  IFC4X2_types[421] =
      new entity(strings[2143], false, 421, (entity *)IFC4X2_types[971]);
  IFC4X2_types[426] =
      new entity(strings[2144], false, 426, (entity *)IFC4X2_types[377]);
  IFC4X2_types[427] =
      new entity(strings[2145], false, 427, (entity *)IFC4X2_types[378]);
  IFC4X2_types[429] =
      new entity(strings[2146], true, 429, (entity *)IFC4X2_types[372]);
  IFC4X2_types[430] =
      new entity(strings[2147], true, 430, (entity *)IFC4X2_types[429]);
  IFC4X2_types[431] =
      new entity(strings[2148], true, 431, (entity *)IFC4X2_types[429]);
  IFC4X2_types[444] =
      new entity(strings[2149], true, 444, (entity *)IFC4X2_types[308]);
  IFC4X2_types[447] =
      new entity(strings[2150], true, 447, (entity *)IFC4X2_types[308]);
  IFC4X2_types[452] =
      new entity(strings[2151], false, 452, (entity *)IFC4X2_types[444]);
  IFC4X2_types[455] =
      new entity(strings[2152], true, 455, (entity *)IFC4X2_types[308]);
  IFC4X2_types[457] =
      new entity(strings[2153], true, 457, (entity *)IFC4X2_types[308]);
  IFC4X2_types[459] =
      new entity(strings[2154], true, 459, (entity *)IFC4X2_types[308]);
  IFC4X2_types[461] =
      new entity(strings[2155], true, 461, (entity *)IFC4X2_types[308]);
  IFC4X2_types[463] =
      new entity(strings[2156], true, 463, (entity *)IFC4X2_types[308]);
  IFC4X2_types[468] =
      new entity(strings[2157], false, 468, (entity *)IFC4X2_types[118]);
  IFC4X2_types[472] =
      new entity(strings[2158], false, 472, (entity *)IFC4X2_types[372]);
  IFC4X2_types[474] =
      new entity(strings[2159], false, 474, (entity *)IFC4X2_types[472]);
  IFC4X2_types[477] =
      new entity(strings[2160], false, 477, (entity *)IFC4X2_types[372]);
  IFC4X2_types[494] =
      new entity(strings[2161], false, 494, (entity *)IFC4X2_types[646]);
  IFC4X2_types[498] =
      new entity(strings[2162], false, 498, (entity *)IFC4X2_types[385]);
  IFC4X2_types[503] =
      new entity(strings[2163], false, 503, (entity *)IFC4X2_types[385]);
  IFC4X2_types[509] =
      new entity(strings[2164], false, 509, (entity *)IFC4X2_types[95]);
  IFC4X2_types[518] =
      new entity(strings[2165], false, 518, (entity *)IFC4X2_types[463]);
  IFC4X2_types[521] =
      new entity(strings[2166], false, 521, (entity *)IFC4X2_types[1043]);
  IFC4X2_types[522] =
      new entity(strings[2167], false, 522, (entity *)IFC4X2_types[494]);
  IFC4X2_types[530] =
      new entity(strings[2168], false, 530, (entity *)IFC4X2_types[447]);
  IFC4X2_types[535] =
      new entity(strings[2169], false, 535, (entity *)IFC4X2_types[219]);
  IFC4X2_types[540] =
      new entity(strings[2170], false, 540, (entity *)IFC4X2_types[461]);
  IFC4X2_types[554] =
      new entity(strings[2171], false, 554, (entity *)IFC4X2_types[461]);
  IFC4X2_types[571] =
      new entity(strings[2172], false, 571, (entity *)IFC4X2_types[267]);
  IFC4X2_types[612] =
      new entity(strings[2173], false, 612, (entity *)IFC4X2_types[377]);
  IFC4X2_types[613] =
      new entity(strings[2174], false, 613, (entity *)IFC4X2_types[378]);
  IFC4X2_types[616] =
      new entity(strings[2175], false, 616, (entity *)IFC4X2_types[461]);
  IFC4X2_types[620] =
      new entity(strings[2176], false, 620, (entity *)IFC4X2_types[118]);
  IFC4X2_types[639] =
      new entity(strings[2177], false, 639, (entity *)IFC4X2_types[385]);
  IFC4X2_types[653] =
      new entity(strings[2178], false, 653, (entity *)IFC4X2_types[6]);
  IFC4X2_types[659] =
      new entity(strings[2179], false, 659, (entity *)IFC4X2_types[431]);
  IFC4X2_types[661] =
      new entity(strings[2180], false, 661, (entity *)IFC4X2_types[659]);
  IFC4X2_types[669] =
      new entity(strings[2181], false, 669, (entity *)IFC4X2_types[461]);
  IFC4X2_types[676] =
      new entity(strings[2182], false, 676, (entity *)IFC4X2_types[224]);
  IFC4X2_types[679] =
      new entity(strings[2183], false, 679, (entity *)IFC4X2_types[730]);
  IFC4X2_types[680] =
      new entity(strings[2184], false, 680, (entity *)IFC4X2_types[224]);
  IFC4X2_types[691] =
      new entity(strings[2185], false, 691, (entity *)IFC4X2_types[283]);
  IFC4X2_types[694] =
      new entity(strings[2186], false, 694, (entity *)IFC4X2_types[447]);
  IFC4X2_types[697] =
      new entity(strings[2187], false, 697, (entity *)IFC4X2_types[457]);
  IFC4X2_types[708] =
      new entity(strings[2188], false, 708, (entity *)IFC4X2_types[118]);
  IFC4X2_types[715] =
      new entity(strings[2189], false, 715, (entity *)IFC4X2_types[1095]);
  IFC4X2_types[716] =
      new entity(strings[2190], false, 716, (entity *)IFC4X2_types[95]);
  IFC4X2_types[718] =
      new entity(strings[2191], true, 718, (entity *)IFC4X2_types[746]);
  IFC4X2_types[719] =
      new entity(strings[2192], true, 719, (entity *)IFC4X2_types[746]);
  IFC4X2_types[741] =
      new entity(strings[2193], false, 741, (entity *)IFC4X2_types[744]);
  IFC4X2_types[760] =
      new entity(strings[2194], false, 760, (entity *)IFC4X2_types[224]);
  IFC4X2_types[757] =
      new entity(strings[2195], false, 757, (entity *)IFC4X2_types[430]);
  IFC4X2_types[785] =
      new entity(strings[2196], false, 785, (entity *)IFC4X2_types[444]);
  IFC4X2_types[789] =
      new entity(strings[2197], false, 789, (entity *)IFC4X2_types[455]);
  IFC4X2_types[800] =
      new entity(strings[2198], false, 800, (entity *)IFC4X2_types[118]);
  IFC4X2_types[804] =
      new entity(strings[2199], false, 804, (entity *)IFC4X2_types[118]);
  IFC4X2_types[806] =
      new entity(strings[2200], false, 806, (entity *)IFC4X2_types[118]);
  IFC4X2_types[810] =
      new entity(strings[2201], false, 810, (entity *)IFC4X2_types[109]);
  IFC4X2_types[819] =
      new entity(strings[2202], false, 819, (entity *)IFC4X2_types[719]);
  IFC4X2_types[830] =
      new entity(strings[2203], true, 830, (entity *)IFC4X2_types[377]);
  IFC4X2_types[831] =
      new entity(strings[2204], true, 831, (entity *)IFC4X2_types[378]);
  IFC4X2_types[832] =
      new entity(strings[2205], false, 832, (entity *)IFC4X2_types[830]);
  IFC4X2_types[833] =
      new entity(strings[2206], false, 833, (entity *)IFC4X2_types[831]);
  IFC4X2_types[835] =
      new entity(strings[2207], false, 835, (entity *)IFC4X2_types[865]);
  IFC4X2_types[902] =
      new entity(strings[2208], false, 902, (entity *)IFC4X2_types[118]);
  IFC4X2_types[911] =
      new entity(strings[2209], false, 911, (entity *)IFC4X2_types[461]);
  IFC4X2_types[914] =
      new entity(strings[2210], false, 914, (entity *)IFC4X2_types[1043]);
  IFC4X2_types[929] =
      new entity(strings[2211], false, 929, (entity *)IFC4X2_types[118]);
  IFC4X2_types[942] =
      new entity(strings[2212], false, 942, (entity *)IFC4X2_types[971]);
  IFC4X2_types[949] =
      new entity(strings[2213], false, 949, (entity *)IFC4X2_types[118]);
  IFC4X2_types[953] =
      new entity(strings[2214], false, 953, (entity *)IFC4X2_types[385]);
  IFC4X2_types[962] =
      new entity(strings[2215], false, 962, (entity *)IFC4X2_types[971]);
  IFC4X2_types[965] =
      new entity(strings[2216], false, 965, (entity *)IFC4X2_types[461]);
  IFC4X2_types[967] =
      new entity(strings[2217], false, 967, (entity *)IFC4X2_types[972]);
  IFC4X2_types[983] =
      new entity(strings[2218], false, 983, (entity *)IFC4X2_types[461]);
  IFC4X2_types[987] =
      new entity(strings[2219], false, 987, (entity *)IFC4X2_types[118]);
  IFC4X2_types[989] =
      new entity(strings[2220], false, 989, (entity *)IFC4X2_types[118]);
  IFC4X2_types[992] =
      new entity(strings[2221], true, 992, (entity *)IFC4X2_types[993]);
  IFC4X2_types[996] =
      new entity(strings[2222], true, 996, (entity *)IFC4X2_types[1005]);
  IFC4X2_types[998] =
      new entity(strings[2223], false, 998, (entity *)IFC4X2_types[992]);
  IFC4X2_types[1000] =
      new entity(strings[2224], false, 1000, (entity *)IFC4X2_types[996]);
  IFC4X2_types[1001] =
      new entity(strings[2225], false, 1001, (entity *)IFC4X2_types[1020]);
  IFC4X2_types[1003] =
      new entity(strings[2226], false, 1003, (entity *)IFC4X2_types[1001]);
  IFC4X2_types[1004] =
      new entity(strings[2227], false, 1004, (entity *)IFC4X2_types[1025]);
  IFC4X2_types[1006] =
      new entity(strings[2228], false, 1006, (entity *)IFC4X2_types[998]);
  IFC4X2_types[1010] =
      new entity(strings[2229], false, 1010, (entity *)IFC4X2_types[494]);
  IFC4X2_types[1022] =
      new entity(strings[2230], false, 1022, (entity *)IFC4X2_types[992]);
  IFC4X2_types[1023] =
      new entity(strings[2231], false, 1023, (entity *)IFC4X2_types[996]);
  IFC4X2_types[1024] =
      new entity(strings[2232], false, 1024, (entity *)IFC4X2_types[1025]);
  IFC4X2_types[1026] =
      new entity(strings[2233], false, 1026, (entity *)IFC4X2_types[494]);
  IFC4X2_types[1027] =
      new entity(strings[2234], false, 1027, (entity *)IFC4X2_types[992]);
  IFC4X2_types[1029] =
      new entity(strings[2235], false, 1029, (entity *)IFC4X2_types[996]);
  IFC4X2_types[1038] =
      new entity(strings[2236], false, 1038, (entity *)IFC4X2_types[219]);
  IFC4X2_types[1045] =
      new entity(strings[2237], false, 1045, (entity *)IFC4X2_types[429]);
  IFC4X2_types[1065] =
      new entity(strings[2238], false, 1065, (entity *)IFC4X2_types[444]);
  IFC4X2_types[1067] =
      new entity(strings[2239], false, 1067, (entity *)IFC4X2_types[494]);
  IFC4X2_types[1068] =
      new entity(strings[2240], false, 1068, (entity *)IFC4X2_types[472]);
  IFC4X2_types[1075] =
      new entity(strings[2241], false, 1075, (entity *)IFC4X2_types[459]);
  IFC4X2_types[1086] =
      new entity(strings[2242], false, 1086, (entity *)IFC4X2_types[830]);
  IFC4X2_types[1087] =
      new entity(strings[2243], false, 1087, (entity *)IFC4X2_types[830]);
  IFC4X2_types[1088] =
      new entity(strings[2244], false, 1088, (entity *)IFC4X2_types[831]);
  IFC4X2_types[1090] =
      new entity(strings[2245], false, 1090, (entity *)IFC4X2_types[830]);
  IFC4X2_types[1091] =
      new entity(strings[2246], false, 1091, (entity *)IFC4X2_types[831]);
  IFC4X2_types[1093] =
      new entity(strings[2247], false, 1093, (entity *)IFC4X2_types[831]);
  IFC4X2_types[1134] =
      new entity(strings[2248], false, 1134, (entity *)IFC4X2_types[385]);
  IFC4X2_types[1137] =
      new entity(strings[2249], false, 1137, (entity *)IFC4X2_types[267]);
  IFC4X2_types[1140] =
      new entity(strings[2250], false, 1140, (entity *)IFC4X2_types[372]);
  IFC4X2_types[1146] =
      new entity(strings[2251], false, 1146, (entity *)IFC4X2_types[95]);
  IFC4X2_types[1151] =
      new entity(strings[2252], false, 1151, (entity *)IFC4X2_types[385]);
  IFC4X2_types[1162] =
      new entity(strings[2253], false, 1162, (entity *)IFC4X2_types[385]);
  IFC4X2_types[1170] =
      new entity(strings[2254], false, 1170, (entity *)IFC4X2_types[444]);
  IFC4X2_types[1178] =
      new entity(strings[2255], false, 1178, (entity *)IFC4X2_types[377]);
  IFC4X2_types[1179] =
      new entity(strings[2256], false, 1179, (entity *)IFC4X2_types[378]);
  IFC4X2_types[1181] =
      new entity(strings[2257], false, 1181, (entity *)IFC4X2_types[377]);
  IFC4X2_types[1182] =
      new entity(strings[2258], false, 1182, (entity *)IFC4X2_types[378]);
  IFC4X2_types[1184] =
      new entity(strings[2259], false, 1184, (entity *)IFC4X2_types[372]);
  IFC4X2_types[1186] =
      new entity(strings[2260], false, 1186, (entity *)IFC4X2_types[431]);
  IFC4X2_types[1193] =
      new entity(strings[2261], false, 1193, (entity *)IFC4X2_types[118]);
  IFC4X2_types[1199] =
      new entity(strings[2262], false, 1199, (entity *)IFC4X2_types[461]);
  IFC4X2_types[1210] =
      new entity(strings[2263], false, 1210, (entity *)IFC4X2_types[118]);
  IFC4X2_types[1213] =
      new entity(strings[2264], false, 1213, (entity *)IFC4X2_types[224]);
  IFC4X2_types[1215] =
      new entity(strings[2265], true, 1215, (entity *)IFC4X2_types[224]);
  IFC4X2_types[1216] =
      new entity(strings[2266], false, 1216, (entity *)IFC4X2_types[1215]);
  IFC4X2_types[1218] =
      new entity(strings[2267], false, 1218, (entity *)IFC4X2_types[1215]);
  IFC4X2_types[1221] =
      new entity(strings[2268], false, 1221, (entity *)IFC4X2_types[1067]);
  IFC4X2_types[263] = new select_type(strings[2269], 263,
                                      {IFC4X2_types[270], IFC4X2_types[272]});
  IFC4X2_types[265] = new select_type(
      strings[2270], 265,
      {IFC4X2_types[189], IFC4X2_types[675], IFC4X2_types[1043]});
  IFC4X2_types[266] = new select_type(strings[2271], 266,
                                      {IFC4X2_types[95], IFC4X2_types[346]});
  IFC4X2_types[994] = new select_type(strings[2272], 994,
                                      {IFC4X2_types[372], IFC4X2_types[1005]});
  IFC4X2_types[2] =
      new entity(strings[2273], false, 2, (entity *)IFC4X2_types[224]);
  IFC4X2_types[19] =
      new entity(strings[2274], false, 19, (entity *)IFC4X2_types[444]);
  IFC4X2_types[21] =
      new entity(strings[2275], false, 21, (entity *)IFC4X2_types[461]);
  IFC4X2_types[24] =
      new entity(strings[2276], false, 24, (entity *)IFC4X2_types[385]);
  IFC4X2_types[38] =
      new entity(strings[2277], false, 38, (entity *)IFC4X2_types[95]);
  IFC4X2_types[59] =
      new entity(strings[2278], false, 59, (entity *)IFC4X2_types[494]);
  IFC4X2_types[62] =
      new entity(strings[2279], false, 62, (entity *)IFC4X2_types[461]);
  IFC4X2_types[104] =
      new entity(strings[2280], true, 104, (entity *)IFC4X2_types[95]);
  IFC4X2_types[106] =
      new entity(strings[2281], false, 106, (entity *)IFC4X2_types[104]);
  IFC4X2_types[70] =
      new entity(strings[2282], false, 70, (entity *)IFC4X2_types[118]);
  IFC4X2_types[73] =
      new entity(strings[2283], false, 73, (entity *)IFC4X2_types[118]);
  IFC4X2_types[82] =
      new entity(strings[2284], false, 82, (entity *)IFC4X2_types[385]);
  IFC4X2_types[90] =
      new entity(strings[2285], false, 90, (entity *)IFC4X2_types[189]);
  IFC4X2_types[100] =
      new entity(strings[2286], false, 100, (entity *)IFC4X2_types[420]);
  IFC4X2_types[101] =
      new entity(strings[2287], false, 101, (entity *)IFC4X2_types[421]);
  IFC4X2_types[110] =
      new entity(strings[2288], false, 110, (entity *)IFC4X2_types[420]);
  IFC4X2_types[111] =
      new entity(strings[2289], true, 111, (entity *)IFC4X2_types[372]);
  IFC4X2_types[112] =
      new entity(strings[2290], false, 112, (entity *)IFC4X2_types[377]);
  IFC4X2_types[113] =
      new entity(strings[2291], false, 113, (entity *)IFC4X2_types[378]);
  IFC4X2_types[115] =
      new entity(strings[2292], false, 115, (entity *)IFC4X2_types[111]);
  IFC4X2_types[116] =
      new entity(strings[2293], false, 116, (entity *)IFC4X2_types[118]);
  IFC4X2_types[119] =
      new entity(strings[2294], false, 119, (entity *)IFC4X2_types[421]);
  IFC4X2_types[120] =
      new entity(strings[2295], false, 120, (entity *)IFC4X2_types[1067]);
  IFC4X2_types[123] =
      new entity(strings[2296], false, 123, (entity *)IFC4X2_types[385]);
  IFC4X2_types[126] =
      new entity(strings[2297], false, 126, (entity *)IFC4X2_types[447]);
  IFC4X2_types[129] =
      new entity(strings[2298], false, 129, (entity *)IFC4X2_types[457]);
  IFC4X2_types[132] =
      new entity(strings[2299], false, 132, (entity *)IFC4X2_types[447]);
  IFC4X2_types[135] =
      new entity(strings[2300], false, 135, (entity *)IFC4X2_types[457]);
  IFC4X2_types[138] =
      new entity(strings[2301], false, 138, (entity *)IFC4X2_types[283]);
  IFC4X2_types[153] =
      new entity(strings[2302], false, 153, (entity *)IFC4X2_types[385]);
  IFC4X2_types[155] =
      new entity(strings[2303], false, 155, (entity *)IFC4X2_types[111]);
  IFC4X2_types[158] =
      new entity(strings[2304], false, 158, (entity *)IFC4X2_types[199]);
  IFC4X2_types[161] =
      new entity(strings[2305], false, 161, (entity *)IFC4X2_types[267]);
  IFC4X2_types[162] =
      new entity(strings[2306], false, 162, (entity *)IFC4X2_types[372]);
  IFC4X2_types[170] =
      new entity(strings[2307], false, 170, (entity *)IFC4X2_types[385]);
  IFC4X2_types[177] =
      new entity(strings[2308], false, 177, (entity *)IFC4X2_types[111]);
  IFC4X2_types[178] =
      new entity(strings[2309], false, 178, (entity *)IFC4X2_types[177]);
  IFC4X2_types[182] =
      new entity(strings[2310], false, 182, (entity *)IFC4X2_types[461]);
  IFC4X2_types[194] =
      new entity(strings[2311], false, 194, (entity *)IFC4X2_types[455]);
  IFC4X2_types[197] =
      new entity(strings[2312], false, 197, (entity *)IFC4X2_types[385]);
  IFC4X2_types[210] =
      new entity(strings[2313], false, 210, (entity *)IFC4X2_types[219]);
  IFC4X2_types[213] =
      new entity(strings[2314], false, 213, (entity *)IFC4X2_types[219]);
  IFC4X2_types[216] =
      new entity(strings[2315], false, 216, (entity *)IFC4X2_types[219]);
  IFC4X2_types[231] =
      new entity(strings[2316], false, 231, (entity *)IFC4X2_types[385]);
  IFC4X2_types[234] =
      new entity(strings[2317], false, 234, (entity *)IFC4X2_types[385]);
  IFC4X2_types[245] =
      new entity(strings[2318], false, 245, (entity *)IFC4X2_types[111]);
  IFC4X2_types[256] =
      new entity(strings[2319], false, 256, (entity *)IFC4X2_types[111]);
  IFC4X2_types[275] =
      new entity(strings[2320], false, 275, (entity *)IFC4X2_types[444]);
  IFC4X2_types[282] =
      new entity(strings[2321], false, 282, (entity *)IFC4X2_types[111]);
  IFC4X2_types[295] =
      new entity(strings[2322], false, 295, (entity *)IFC4X2_types[377]);
  IFC4X2_types[296] =
      new entity(strings[2323], false, 296, (entity *)IFC4X2_types[378]);
  IFC4X2_types[300] =
      new entity(strings[2324], false, 300, (entity *)IFC4X2_types[308]);
  IFC4X2_types[304] =
      new entity(strings[2325], true, 304, (entity *)IFC4X2_types[306]);
  IFC4X2_types[305] =
      new entity(strings[2326], false, 305, (entity *)IFC4X2_types[372]);
  IFC4X2_types[307] =
      new entity(strings[2327], false, 307, (entity *)IFC4X2_types[305]);
  IFC4X2_types[309] =
      new entity(strings[2328], false, 309, (entity *)IFC4X2_types[718]);
  IFC4X2_types[311] =
      new entity(strings[2329], false, 311, (entity *)IFC4X2_types[1067]);
  IFC4X2_types[319] =
      new entity(strings[2330], false, 319, (entity *)IFC4X2_types[111]);
  IFC4X2_types[324] =
      new entity(strings[2331], false, 324, (entity *)IFC4X2_types[319]);
  IFC4X2_types[335] =
      new entity(strings[2332], false, 335, (entity *)IFC4X2_types[447]);
  IFC4X2_types[338] =
      new entity(strings[2333], false, 338, (entity *)IFC4X2_types[457]);
  IFC4X2_types[341] =
      new entity(strings[2334], false, 341, (entity *)IFC4X2_types[463]);
  IFC4X2_types[349] =
      new entity(strings[2335], false, 349, (entity *)IFC4X2_types[461]);
  IFC4X2_types[356] =
      new entity(strings[2336], false, 356, (entity *)IFC4X2_types[444]);
  IFC4X2_types[359] =
      new entity(strings[2337], false, 359, (entity *)IFC4X2_types[459]);
  IFC4X2_types[362] =
      new entity(strings[2338], false, 362, (entity *)IFC4X2_types[385]);
  IFC4X2_types[365] =
      new entity(strings[2339], false, 365, (entity *)IFC4X2_types[385]);
  IFC4X2_types[369] =
      new entity(strings[2340], false, 369, (entity *)IFC4X2_types[444]);
  IFC4X2_types[384] =
      new entity(strings[2341], false, 384, (entity *)IFC4X2_types[307]);
  IFC4X2_types[387] =
      new entity(strings[2342], false, 387, (entity *)IFC4X2_types[384]);
  IFC4X2_types[390] =
      new entity(strings[2343], false, 390, (entity *)IFC4X2_types[384]);
  IFC4X2_types[393] =
      new entity(strings[2344], false, 393, (entity *)IFC4X2_types[384]);
  IFC4X2_types[408] =
      new entity(strings[2345], false, 408, (entity *)IFC4X2_types[410]);
  IFC4X2_types[424] =
      new entity(strings[2346], false, 424, (entity *)IFC4X2_types[455]);
  IFC4X2_types[437] =
      new entity(strings[2347], false, 437, (entity *)IFC4X2_types[463]);
  IFC4X2_types[440] =
      new entity(strings[2348], false, 440, (entity *)IFC4X2_types[461]);
  IFC4X2_types[443] =
      new entity(strings[2349], false, 443, (entity *)IFC4X2_types[307]);
  IFC4X2_types[446] =
      new entity(strings[2350], false, 446, (entity *)IFC4X2_types[307]);
  IFC4X2_types[449] =
      new entity(strings[2351], false, 449, (entity *)IFC4X2_types[304]);
  IFC4X2_types[451] =
      new entity(strings[2352], false, 451, (entity *)IFC4X2_types[443]);
  IFC4X2_types[454] =
      new entity(strings[2353], false, 454, (entity *)IFC4X2_types[307]);
  IFC4X2_types[456] =
      new entity(strings[2354], false, 456, (entity *)IFC4X2_types[307]);
  IFC4X2_types[458] =
      new entity(strings[2355], false, 458, (entity *)IFC4X2_types[307]);
  IFC4X2_types[460] =
      new entity(strings[2356], false, 460, (entity *)IFC4X2_types[307]);
  IFC4X2_types[462] =
      new entity(strings[2357], false, 462, (entity *)IFC4X2_types[307]);
  IFC4X2_types[467] =
      new entity(strings[2358], false, 467, (entity *)IFC4X2_types[111]);
  IFC4X2_types[489] =
      new entity(strings[2359], false, 489, (entity *)IFC4X2_types[719]);
  IFC4X2_types[497] =
      new entity(strings[2360], false, 497, (entity *)IFC4X2_types[384]);
  IFC4X2_types[502] =
      new entity(strings[2361], false, 502, (entity *)IFC4X2_types[384]);
  IFC4X2_types[517] =
      new entity(strings[2362], false, 517, (entity *)IFC4X2_types[462]);
  IFC4X2_types[529] =
      new entity(strings[2363], false, 529, (entity *)IFC4X2_types[446]);
  IFC4X2_types[539] =
      new entity(strings[2364], false, 539, (entity *)IFC4X2_types[460]);
  IFC4X2_types[553] =
      new entity(strings[2365], false, 553, (entity *)IFC4X2_types[460]);
  IFC4X2_types[567] =
      new entity(strings[2366], false, 567, (entity *)IFC4X2_types[719]);
  IFC4X2_types[615] =
      new entity(strings[2367], false, 615, (entity *)IFC4X2_types[460]);
  IFC4X2_types[618] =
      new entity(strings[2368], false, 618, (entity *)IFC4X2_types[111]);
  IFC4X2_types[619] =
      new entity(strings[2369], false, 619, (entity *)IFC4X2_types[618]);
  IFC4X2_types[638] =
      new entity(strings[2370], false, 638, (entity *)IFC4X2_types[384]);
  IFC4X2_types[667] =
      new entity(strings[2371], false, 667, (entity *)IFC4X2_types[90]);
  IFC4X2_types[668] =
      new entity(strings[2372], false, 668, (entity *)IFC4X2_types[460]);
  IFC4X2_types[689] =
      new entity(strings[2373], false, 689, (entity *)IFC4X2_types[282]);
  IFC4X2_types[693] =
      new entity(strings[2374], false, 693, (entity *)IFC4X2_types[446]);
  IFC4X2_types[696] =
      new entity(strings[2375], false, 696, (entity *)IFC4X2_types[456]);
  IFC4X2_types[706] =
      new entity(strings[2376], false, 706, (entity *)IFC4X2_types[111]);
  IFC4X2_types[707] =
      new entity(strings[2377], false, 707, (entity *)IFC4X2_types[706]);
  IFC4X2_types[781] =
      new entity(strings[2378], false, 781, (entity *)IFC4X2_types[443]);
  IFC4X2_types[783] =
      new entity(strings[2379], false, 783, (entity *)IFC4X2_types[304]);
  IFC4X2_types[788] =
      new entity(strings[2380], false, 788, (entity *)IFC4X2_types[454]);
  IFC4X2_types[799] =
      new entity(strings[2381], false, 799, (entity *)IFC4X2_types[111]);
  IFC4X2_types[802] =
      new entity(strings[2382], false, 802, (entity *)IFC4X2_types[111]);
  IFC4X2_types[803] =
      new entity(strings[2383], false, 803, (entity *)IFC4X2_types[111]);
  IFC4X2_types[809] =
      new entity(strings[2384], false, 809, (entity *)IFC4X2_types[106]);
  IFC4X2_types[825] =
      new entity(strings[2385], false, 825, (entity *)IFC4X2_types[830]);
  IFC4X2_types[828] =
      new entity(strings[2386], false, 828, (entity *)IFC4X2_types[831]);
  IFC4X2_types[901] =
      new entity(strings[2387], false, 901, (entity *)IFC4X2_types[111]);
  IFC4X2_types[910] =
      new entity(strings[2388], false, 910, (entity *)IFC4X2_types[460]);
  IFC4X2_types[925] =
      new entity(strings[2389], false, 925, (entity *)IFC4X2_types[304]);
  IFC4X2_types[928] =
      new entity(strings[2390], false, 928, (entity *)IFC4X2_types[111]);
  IFC4X2_types[946] =
      new entity(strings[2391], false, 946, (entity *)IFC4X2_types[111]);
  IFC4X2_types[947] =
      new entity(strings[2392], false, 947, (entity *)IFC4X2_types[946]);
  IFC4X2_types[948] =
      new entity(strings[2393], false, 948, (entity *)IFC4X2_types[946]);
  IFC4X2_types[952] =
      new entity(strings[2394], false, 952, (entity *)IFC4X2_types[384]);
  IFC4X2_types[964] =
      new entity(strings[2395], false, 964, (entity *)IFC4X2_types[460]);
  IFC4X2_types[982] =
      new entity(strings[2396], false, 982, (entity *)IFC4X2_types[460]);
  IFC4X2_types[985] =
      new entity(strings[2397], false, 985, (entity *)IFC4X2_types[111]);
  IFC4X2_types[986] =
      new entity(strings[2398], false, 986, (entity *)IFC4X2_types[111]);
  IFC4X2_types[995] =
      new entity(strings[2399], false, 995, (entity *)IFC4X2_types[1067]);
  IFC4X2_types[1008] =
      new entity(strings[2400], false, 1008, (entity *)IFC4X2_types[1010]);
  IFC4X2_types[1021] =
      new entity(strings[2401], false, 1021, (entity *)IFC4X2_types[1027]);
  IFC4X2_types[1064] =
      new entity(strings[2402], false, 1064, (entity *)IFC4X2_types[443]);
  IFC4X2_types[1074] =
      new entity(strings[2403], false, 1074, (entity *)IFC4X2_types[458]);
  IFC4X2_types[1133] =
      new entity(strings[2404], false, 1133, (entity *)IFC4X2_types[384]);
  IFC4X2_types[1150] =
      new entity(strings[2405], false, 1150, (entity *)IFC4X2_types[384]);
  IFC4X2_types[1159] =
      new entity(strings[2406], false, 1159, (entity *)IFC4X2_types[304]);
  IFC4X2_types[1161] =
      new entity(strings[2407], false, 1161, (entity *)IFC4X2_types[384]);
  IFC4X2_types[1169] =
      new entity(strings[2408], false, 1169, (entity *)IFC4X2_types[443]);
  IFC4X2_types[1190] =
      new entity(strings[2409], false, 1190, (entity *)IFC4X2_types[111]);
  IFC4X2_types[1191] =
      new entity(strings[2410], false, 1191, (entity *)IFC4X2_types[1190]);
  IFC4X2_types[1192] =
      new entity(strings[2411], false, 1192, (entity *)IFC4X2_types[1190]);
  IFC4X2_types[1198] =
      new entity(strings[2412], false, 1198, (entity *)IFC4X2_types[460]);
  IFC4X2_types[1201] =
      new entity(strings[2413], false, 1201, (entity *)IFC4X2_types[111]);
  IFC4X2_types[1206] =
      new entity(strings[2414], false, 1206, (entity *)IFC4X2_types[1201]);
  IFC4X2_types[963] = new select_type(strings[2415], 963,
                                      {IFC4X2_types[408], IFC4X2_types[962]});
  IFC4X2_types[10] =
      new entity(strings[2416], false, 10, (entity *)IFC4X2_types[304]);
  IFC4X2_types[17] =
      new entity(strings[2417], false, 17, (entity *)IFC4X2_types[460]);
  IFC4X2_types[18] =
      new entity(strings[2418], false, 18, (entity *)IFC4X2_types[443]);
  IFC4X2_types[23] =
      new entity(strings[2419], false, 23, (entity *)IFC4X2_types[384]);
  IFC4X2_types[27] =
      new entity(strings[2420], false, 27, (entity *)IFC4X2_types[304]);
  IFC4X2_types[29] =
      new entity(strings[2421], false, 29, (entity *)IFC4X2_types[567]);
  IFC4X2_types[61] =
      new entity(strings[2422], false, 61, (entity *)IFC4X2_types[460]);
  IFC4X2_types[68] =
      new entity(strings[2423], false, 68, (entity *)IFC4X2_types[111]);
  IFC4X2_types[69] =
      new entity(strings[2424], false, 69, (entity *)IFC4X2_types[68]);
  IFC4X2_types[72] =
      new entity(strings[2425], false, 72, (entity *)IFC4X2_types[111]);
  IFC4X2_types[81] =
      new entity(strings[2426], false, 81, (entity *)IFC4X2_types[384]);
  IFC4X2_types[122] =
      new entity(strings[2427], false, 122, (entity *)IFC4X2_types[384]);
  IFC4X2_types[125] =
      new entity(strings[2428], false, 125, (entity *)IFC4X2_types[446]);
  IFC4X2_types[128] =
      new entity(strings[2429], false, 128, (entity *)IFC4X2_types[456]);
  IFC4X2_types[131] =
      new entity(strings[2430], false, 131, (entity *)IFC4X2_types[446]);
  IFC4X2_types[134] =
      new entity(strings[2431], false, 134, (entity *)IFC4X2_types[456]);
  IFC4X2_types[137] =
      new entity(strings[2432], false, 137, (entity *)IFC4X2_types[282]);
  IFC4X2_types[152] =
      new entity(strings[2433], false, 152, (entity *)IFC4X2_types[384]);
  IFC4X2_types[169] =
      new entity(strings[2434], false, 169, (entity *)IFC4X2_types[384]);
  IFC4X2_types[181] =
      new entity(strings[2435], false, 181, (entity *)IFC4X2_types[460]);
  IFC4X2_types[193] =
      new entity(strings[2436], false, 193, (entity *)IFC4X2_types[454]);
  IFC4X2_types[196] =
      new entity(strings[2437], false, 196, (entity *)IFC4X2_types[384]);
  IFC4X2_types[226] =
      new entity(strings[2438], false, 226, (entity *)IFC4X2_types[304]);
  IFC4X2_types[230] =
      new entity(strings[2439], false, 230, (entity *)IFC4X2_types[384]);
  IFC4X2_types[233] =
      new entity(strings[2440], false, 233, (entity *)IFC4X2_types[384]);
  IFC4X2_types[274] =
      new entity(strings[2441], false, 274, (entity *)IFC4X2_types[443]);
  IFC4X2_types[299] =
      new entity(strings[2442], false, 299, (entity *)IFC4X2_types[307]);
  IFC4X2_types[302] =
      new entity(strings[2443], false, 302, (entity *)IFC4X2_types[311]);
  IFC4X2_types[303] =
      new entity(strings[2444], false, 303, (entity *)IFC4X2_types[305]);
  IFC4X2_types[334] =
      new entity(strings[2445], false, 334, (entity *)IFC4X2_types[446]);
  IFC4X2_types[337] =
      new entity(strings[2446], false, 337, (entity *)IFC4X2_types[456]);
  IFC4X2_types[340] =
      new entity(strings[2447], false, 340, (entity *)IFC4X2_types[462]);
  IFC4X2_types[348] =
      new entity(strings[2448], false, 348, (entity *)IFC4X2_types[460]);
  IFC4X2_types[355] =
      new entity(strings[2449], false, 355, (entity *)IFC4X2_types[443]);
  IFC4X2_types[358] =
      new entity(strings[2450], false, 358, (entity *)IFC4X2_types[458]);
  IFC4X2_types[361] =
      new entity(strings[2451], false, 361, (entity *)IFC4X2_types[384]);
  IFC4X2_types[364] =
      new entity(strings[2452], false, 364, (entity *)IFC4X2_types[384]);
  IFC4X2_types[368] =
      new entity(strings[2453], false, 368, (entity *)IFC4X2_types[443]);
  IFC4X2_types[423] =
      new entity(strings[2454], false, 423, (entity *)IFC4X2_types[454]);
  IFC4X2_types[436] =
      new entity(strings[2455], false, 436, (entity *)IFC4X2_types[462]);
  IFC4X2_types[439] =
      new entity(strings[2456], false, 439, (entity *)IFC4X2_types[460]);
  IFC4X2_types[448] =
      new entity(strings[2457], false, 448, (entity *)IFC4X2_types[303]);
  IFC4X2_types[782] =
      new entity(strings[2458], false, 782, (entity *)IFC4X2_types[303]);
  IFC4X2_types[924] =
      new entity(strings[2459], false, 924, (entity *)IFC4X2_types[303]);
  IFC4X2_types[1158] =
      new entity(strings[2460], false, 1158, (entity *)IFC4X2_types[303]);
  IFC4X2_types[9] =
      new entity(strings[2461], false, 9, (entity *)IFC4X2_types[303]);
  IFC4X2_types[26] =
      new entity(strings[2462], false, 26, (entity *)IFC4X2_types[303]);
  IFC4X2_types[225] =
      new entity(strings[2463], false, 225, (entity *)IFC4X2_types[303]);
  ((entity *)IFC4X2_types[2])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[3]), true),
           new attribute(strings[2465], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2466], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[6])
      ->set_attributes({new attribute(strings[2467],
                                      new named_type(IFC4X2_types[8]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[7])
      ->set_attributes(
          {new attribute(strings[2468], new named_type(IFC4X2_types[900]),
                         false),
           new attribute(strings[2469], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X2_types[9])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[11]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[10])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[11]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[12])
      ->set_attributes(
          {new attribute(strings[2471], new named_type(IFC4X2_types[13]), true),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[2472], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X2_types[14])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[15])
      ->set_attributes({new attribute(strings[2473],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[168])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X2_types[16])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X2_types[17])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[22]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[18])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[20]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[19])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[20]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[21])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[22]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[23])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[25]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[24])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[25]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[26])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[28]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[27])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[28]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[29])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[39]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[30])
      ->set_attributes({new attribute(strings[2474],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2475],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[31])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X2_types[31])
      ->set_attributes(
          {new attribute(strings[2476], new named_type(IFC4X2_types[267]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[32])
      ->set_attributes(
          {new attribute(strings[2477], new named_type(IFC4X2_types[84]), true),
           new attribute(strings[2478], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2479], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X2_types[33])
      ->set_attributes(
          {new attribute(strings[2480], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2481], new named_type(IFC4X2_types[84]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[34])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[35])
      ->set_attributes(
          {new attribute(strings[2482], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2481], new named_type(IFC4X2_types[84]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[36])
      ->set_attributes({new attribute(strings[2475],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[37])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[37])
      ->set_attributes(
          {new attribute(strings[2474], new named_type(IFC4X2_types[545]),
                         false),
           new attribute(strings[2483], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2484], new named_type(IFC4X2_types[545]),
                         false),
           new attribute(strings[2485], new named_type(IFC4X2_types[808]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[38])
      ->set_attributes(
          {new attribute(strings[2486], new named_type(IFC4X2_types[30]),
                         false),
           new attribute(strings[2487], new named_type(IFC4X2_types[36]), true),
           new attribute(strings[2488], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X2_types[44])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[45])
      ->set_attributes({new attribute(strings[2489],
                                      new named_type(IFC4X2_types[260]), false),
                        new attribute(strings[2490],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[260])),
                                      true)},
                       {false, false});
  ((entity *)IFC4X2_types[46])
      ->set_attributes(
          {new attribute(strings[2491], new named_type(IFC4X2_types[663]),
                         false),
           new attribute(strings[2492], new named_type(IFC4X2_types[534]),
                         false),
           new attribute(strings[2493], new named_type(IFC4X2_types[534]),
                         false),
           new attribute(strings[2494], new named_type(IFC4X2_types[505]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[47])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[2496], new named_type(IFC4X2_types[48]), true),
           new attribute(strings[2497], new named_type(IFC4X2_types[611]),
                         true),
           new attribute(strings[2498], new named_type(IFC4X2_types[278]),
                         true),
           new attribute(strings[2499], new named_type(IFC4X2_types[278]),
                         true),
           new attribute(strings[2500], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2501], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2502], new named_type(IFC4X2_types[57]), true),
           new attribute(strings[2503],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X2_types[47])),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[49])
      ->set_attributes(
          {new attribute(strings[2504], new named_type(IFC4X2_types[505]),
                         true),
           new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[2505], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[2465], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2506], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2507], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[2508], new named_type(IFC4X2_types[8]), true),
           new attribute(strings[2509], new named_type(IFC4X2_types[8]), true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[50])
      ->set_attributes(
          {new attribute(strings[2510], new named_type(IFC4X2_types[49]),
                         false),
           new attribute(strings[2511],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4X2_types[49])),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[51])
      ->set_attributes(
          {new attribute(strings[2512], new named_type(IFC4X2_types[260]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[52])
      ->set_attributes({new attribute(strings[2513],
                                      new named_type(IFC4X2_types[95]), false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[53])
      ->set_attributes({new attribute(strings[2514],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[260])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[59])
      ->set_attributes(
          {new attribute(strings[2515], new named_type(IFC4X2_types[505]),
                         true),
           new attribute(strings[2516], new named_type(IFC4X2_types[243]),
                         true),
           new attribute(strings[2517], new named_type(IFC4X2_types[243]),
                         true),
           new attribute(strings[2518], new named_type(IFC4X2_types[243]),
                         true),
           new attribute(strings[2519], new named_type(IFC4X2_types[8]), true),
           new attribute(strings[2520], new named_type(IFC4X2_types[8]), true),
           new attribute(strings[2521], new named_type(IFC4X2_types[682]),
                         true),
           new attribute(strings[2522], new named_type(IFC4X2_types[278]),
                         true),
           new attribute(strings[2523], new named_type(IFC4X2_types[243]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X2_types[60])
      ->set_attributes({new attribute(strings[2524],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2525],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2526],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2527],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2528],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2529],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2530],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2531],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2532],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2533],
                                      new named_type(IFC4X2_types[705]), true),
                        new attribute(strings[2534],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2535],
                                      new named_type(IFC4X2_types[705]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[61])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[63]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[62])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[63]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[64])
      ->set_attributes({new attribute(strings[2536],
                                      new named_type(IFC4X2_types[293]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[66])
      ->set_attributes({new attribute(strings[2537],
                                      new named_type(IFC4X2_types[293]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[67])
      ->set_attributes({new attribute(strings[2536],
                                      new named_type(IFC4X2_types[293]), true),
                        new attribute(strings[2537],
                                      new named_type(IFC4X2_types[293]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[104])
      ->set_attributes(
          {new attribute(strings[2538], new named_type(IFC4X2_types[515]),
                         false),
           new attribute(
               strings[2539],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X2_types[141])),
               false),
           new attribute(strings[2540], new named_type(IFC4X2_types[105]),
                         false),
           new attribute(strings[2541], new named_type(IFC4X2_types[574]),
                         false),
           new attribute(strings[2542], new named_type(IFC4X2_types[574]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[106])
      ->set_attributes(
          {new attribute(
               strings[2543],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X2_types[515])),
               false),
           new attribute(
               strings[2544],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X2_types[673])),
               false),
           new attribute(strings[2545], new named_type(IFC4X2_types[533]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[107])
      ->set_attributes(
          {new attribute(strings[2546], new named_type(IFC4X2_types[515]),
                         false),
           new attribute(strings[2547], new named_type(IFC4X2_types[515]),
                         false),
           new attribute(
               strings[2539],
               new aggregation_type(
                   aggregation_type::list_type, 2, -1,
                   new aggregation_type(aggregation_type::list_type, 2, -1,
                                        new named_type(IFC4X2_types[141]))),
               false),
           new attribute(strings[2548], new named_type(IFC4X2_types[108]),
                         false),
           new attribute(strings[2549], new named_type(IFC4X2_types[574]),
                         false),
           new attribute(strings[2550], new named_type(IFC4X2_types[574]),
                         false),
           new attribute(strings[2542], new named_type(IFC4X2_types[574]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[109])
      ->set_attributes(
          {new attribute(
               strings[2551],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X2_types[515])),
               false),
           new attribute(
               strings[2552],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X2_types[515])),
               false),
           new attribute(
               strings[2553],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X2_types[673])),
               false),
           new attribute(
               strings[2554],
               new aggregation_type(aggregation_type::list_type, 2, -1,
                                    new named_type(IFC4X2_types[673])),
               false),
           new attribute(strings[2545], new named_type(IFC4X2_types[533]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X2_types[68])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[71]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[69])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[70])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[71]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[72])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[75]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[73])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[75]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[79])
      ->set_attributes({new attribute(strings[2555],
                                      new named_type(IFC4X2_types[505]), false),
                        new attribute(strings[2556],
                                      new named_type(IFC4X2_types[78]), false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[80])
      ->set_attributes(
          {new attribute(strings[2557], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2558], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2559], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[81])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[83]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[82])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[83]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[85])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X2_types[88])
      ->set_attributes({new attribute(strings[2560],
                                      new named_type(IFC4X2_types[87]), false),
                        new attribute(strings[2561],
                                      new named_type(IFC4X2_types[86]), false),
                        new attribute(strings[2562],
                                      new named_type(IFC4X2_types[86]), false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[89])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false});
  ((entity *)IFC4X2_types[90])->set_attributes({}, {false, false});
  ((entity *)IFC4X2_types[91])
      ->set_attributes({new attribute(strings[2563],
                                      new named_type(IFC4X2_types[631]), true),
                        new attribute(strings[2564],
                                      new named_type(IFC4X2_types[631]), true),
                        new attribute(strings[2565],
                                      new named_type(IFC4X2_types[631]), true),
                        new attribute(strings[2566],
                                      new named_type(IFC4X2_types[628]), true),
                        new attribute(strings[2567],
                                      new named_type(IFC4X2_types[628]), true),
                        new attribute(strings[2568],
                                      new named_type(IFC4X2_types[628]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[92])
      ->set_attributes({new attribute(strings[2569],
                                      new named_type(IFC4X2_types[630]), true),
                        new attribute(strings[2570],
                                      new named_type(IFC4X2_types[630]), true),
                        new attribute(strings[2571],
                                      new named_type(IFC4X2_types[630]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[93])
      ->set_attributes({new attribute(strings[2572],
                                      new named_type(IFC4X2_types[1139]), true),
                        new attribute(strings[2573],
                                      new named_type(IFC4X2_types[1139]), true),
                        new attribute(strings[2574],
                                      new named_type(IFC4X2_types[1139]), true),
                        new attribute(strings[2575],
                                      new named_type(IFC4X2_types[908]), true),
                        new attribute(strings[2576],
                                      new named_type(IFC4X2_types[908]), true),
                        new attribute(strings[2577],
                                      new named_type(IFC4X2_types[908]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[94])
      ->set_attributes(
          {new attribute(strings[2578], new named_type(IFC4X2_types[1197]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[95])->set_attributes({}, {});
  ((entity *)IFC4X2_types[96])->set_attributes({}, {});
  ((entity *)IFC4X2_types[97])
      ->set_attributes(
          {new attribute(strings[2579], new named_type(IFC4X2_types[141]),
                         false),
           new attribute(strings[2580], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2581], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2582], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[99])
      ->set_attributes({new attribute(strings[2583],
                                      new named_type(IFC4X2_types[97]), false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[100])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[103]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[101])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[102]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[110])
      ->set_attributes({new attribute(strings[2584],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2585],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2586],
                                      new named_type(IFC4X2_types[724]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X2_types[111])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[112])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[114]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[113])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[114]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[115])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[117]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[116])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[117]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[118])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[119])
      ->set_attributes({new attribute(strings[2587],
                                      new named_type(IFC4X2_types[545]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[120])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[121]), true),
                        new attribute(strings[2588],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[122])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[124]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[123])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[124]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[254])
      ->set_attributes(
          {new attribute(strings[2589], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2590], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2591], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2592], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2593], new named_type(IFC4X2_types[642]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[125])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[127]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[126])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[127]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[128])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[130]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[129])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[130]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[131])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[133]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[132])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[133]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[134])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[136]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[135])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[136]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[137])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[139]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[138])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[139]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[141])
      ->set_attributes({new attribute(strings[2594],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, 3,
                                          new named_type(IFC4X2_types[545])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[142])->set_attributes({}, {});
  ((entity *)IFC4X2_types[143])
      ->set_attributes(
          {new attribute(
               strings[2595],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 2, 2,
                                        new named_type(IFC4X2_types[545]))),
               false),
           new attribute(
               strings[2596],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[534])),
               true)},
          {false, false});
  ((entity *)IFC4X2_types[144])
      ->set_attributes(
          {new attribute(
               strings[2595],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4X2_types[545]))),
               false),
           new attribute(
               strings[2596],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[534])),
               true)},
          {false, false});
  ((entity *)IFC4X2_types[145])
      ->set_attributes({new attribute(strings[2597],
                                      new named_type(IFC4X2_types[293]), true),
                        new attribute(strings[2598],
                                      new named_type(IFC4X2_types[293]), true),
                        new attribute(strings[2599],
                                      new named_type(IFC4X2_types[141]), false),
                        new attribute(strings[2600],
                                      new named_type(IFC4X2_types[811]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[146])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[147])
      ->set_attributes({new attribute(strings[2601],
                                      new named_type(IFC4X2_types[811]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[148])
      ->set_attributes({new attribute(strings[2602],
                                      new named_type(IFC4X2_types[293]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[149])
      ->set_attributes({new attribute(strings[2601],
                                      new named_type(IFC4X2_types[811]), true),
                        new attribute(strings[2603],
                                      new named_type(IFC4X2_types[811]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[150])
      ->set_attributes(
          {new attribute(strings[2604], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[152])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[154]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[153])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[154]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[155])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[157]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[156])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[157]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[158])
      ->set_attributes(
          {new attribute(strings[2480], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[159])
      ->set_attributes(
          {new attribute(strings[2591], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[160])
      ->set_attributes(
          {new attribute(strings[2480], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[161])
      ->set_attributes({new attribute(strings[2480],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2605],
                                      new named_type(IFC4X2_types[84]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[162])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[163])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[164])
      ->set_attributes({new attribute(strings[2606],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2607],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2608],
                                      new named_type(IFC4X2_types[278]), true),
                        new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), false),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2609],
                                      new named_type(IFC4X2_types[1166]), true),
                        new attribute(strings[2610],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[505])),
                                      true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[165])
      ->set_attributes({new attribute(strings[2611],
                                      new named_type(IFC4X2_types[166]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2612],
                                      new named_type(IFC4X2_types[505]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[168])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[169])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[171]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[170])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[171]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[174])
      ->set_attributes(
          {new attribute(strings[2613], new named_type(IFC4X2_types[643]),
                         false),
           new attribute(strings[2614], new named_type(IFC4X2_types[643]),
                         false),
           new attribute(strings[2615], new named_type(IFC4X2_types[643]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[175])
      ->set_attributes(
          {new attribute(
              strings[2616],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, 3,
                                       new named_type(IFC4X2_types[643]))),
              false)},
          {false});
  ((entity *)IFC4X2_types[176])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false});
  ((entity *)IFC4X2_types[177])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[180]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[178])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[179])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[180]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[181])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[183]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[182])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[183]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[185])
      ->set_attributes({new attribute(strings[2617],
                                      new named_type(IFC4X2_types[505]), false),
                        new attribute(strings[2618],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[762])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[186])
      ->set_attributes({new attribute(strings[2617],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2619],
                                      new named_type(IFC4X2_types[187]), true),
                        new attribute(strings[2620],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[779])),
                                      true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[188])
      ->set_attributes(
          {new attribute(
               strings[2475],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[190])),
               false),
           new attribute(strings[2542], new named_type(IFC4X2_types[574]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[189])->set_attributes({}, {false, false});
  ((entity *)IFC4X2_types[190])
      ->set_attributes(
          {new attribute(strings[2621], new named_type(IFC4X2_types[1136]),
                         false),
           new attribute(strings[2622], new named_type(IFC4X2_types[84]),
                         false),
           new attribute(strings[2623], new named_type(IFC4X2_types[260]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[191])
      ->set_attributes({new attribute(strings[2624],
                                      new aggregation_type(
                                          aggregation_type::set_type, 2, -1,
                                          new named_type(IFC4X2_types[751])),
                                      false),
                        new attribute(strings[2625],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[193])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[195]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[194])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[195]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[196])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[198]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[197])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[198]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[199])
      ->set_attributes({new attribute(strings[2626],
                                      new named_type(IFC4X2_types[65]), false)},
                       {false});
  ((entity *)IFC4X2_types[200])
      ->set_attributes({new attribute(strings[2627],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[413])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[201])
      ->set_attributes({new attribute(strings[2628],
                                      new named_type(IFC4X2_types[266]), false),
                        new attribute(strings[2629],
                                      new named_type(IFC4X2_types[266]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[202])->set_attributes({}, {});
  ((entity *)IFC4X2_types[203])
      ->set_attributes({new attribute(strings[2630],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2631],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2632],
                                      new named_type(IFC4X2_types[545]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[204])
      ->set_attributes({new attribute(strings[2633],
                                      new named_type(IFC4X2_types[713]), false),
                        new attribute(strings[2634],
                                      new named_type(IFC4X2_types[713]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[205])
      ->set_attributes(
          {new attribute(strings[2635], new named_type(IFC4X2_types[1049]),
                         false),
           new attribute(strings[2636], new named_type(IFC4X2_types[1049]),
                         true)},
          {false, false});
  ((entity *)IFC4X2_types[207])
      ->set_attributes({new attribute(strings[2637],
                                      new named_type(IFC4X2_types[957]), false),
                        new attribute(strings[2638],
                                      new named_type(IFC4X2_types[957]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[208])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         false),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[2639], new named_type(IFC4X2_types[209]),
                         false),
           new attribute(strings[2640], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2641], new named_type(IFC4X2_types[8]), true),
           new attribute(strings[2642], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[2643], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[210])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[212]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[211])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[212]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X2_types[213])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[215]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[214])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[215]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X2_types[216])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[218]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[217])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[218]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X2_types[219])
      ->set_attributes({new attribute(strings[2644],
                                      new named_type(IFC4X2_types[895]), true),
                        new attribute(strings[2645],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[47])),
                                      true),
                        new attribute(strings[2646],
                                      new named_type(IFC4X2_types[687]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[220])
      ->set_attributes({new attribute(strings[2645],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[47])),
                                      true),
                        new attribute(strings[2646],
                                      new named_type(IFC4X2_types[687]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[221])
      ->set_attributes(
          {new attribute(strings[2647], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2588], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2648], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(
               strings[2649],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[886])),
               true),
           new attribute(strings[2650], new named_type(IFC4X2_types[1164]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[223])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[224])
      ->set_attributes({new attribute(strings[2515],
                                      new named_type(IFC4X2_types[505]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[225])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[227]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[226])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[227]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[228])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         false),
           new attribute(strings[2651], new named_type(IFC4X2_types[611]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[229])
      ->set_attributes(
          {new attribute(strings[2652], new named_type(IFC4X2_types[811]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[230])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[232]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[231])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[232]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[233])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[235]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[234])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[235]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[236])
      ->set_attributes(
          {new attribute(strings[2653], new named_type(IFC4X2_types[238]),
                         false),
           new attribute(strings[2654], new named_type(IFC4X2_types[237]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[237])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), false),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2655],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[2656],
                                      new named_type(IFC4X2_types[505]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[239])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[240]),
                         true),
           new attribute(
               strings[2657],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[243])),
               true),
           new attribute(
               strings[2658],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[687])),
               true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[241])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[242]), true),
                        new attribute(strings[2465],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2659],
                                      new named_type(IFC4X2_types[279]), true),
                        new attribute(strings[2660],
                                      new named_type(IFC4X2_types[279]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[243])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false});
  ((entity *)IFC4X2_types[245])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[247]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[246])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[247]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[248])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[250]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[249])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[250]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X2_types[251])
      ->set_attributes({new attribute(strings[2626],
                                      new named_type(IFC4X2_types[67]), false)},
                       {false});
  ((entity *)IFC4X2_types[253])
      ->set_attributes(
          {new attribute(strings[2661], new named_type(IFC4X2_types[252]),
                         false)},
          {false});
  ((entity *)IFC4X2_types[255])
      ->set_attributes({new attribute(strings[2662],
                                      new named_type(IFC4X2_types[636]), false),
                        new attribute(strings[2663],
                                      new named_type(IFC4X2_types[636]), false),
                        new attribute(strings[2664],
                                      new named_type(IFC4X2_types[723]), false),
                        new attribute(strings[2665],
                                      new named_type(IFC4X2_types[279]), true),
                        new attribute(strings[2666],
                                      new named_type(IFC4X2_types[546]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[256])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[258]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[257])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[258]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[260])->set_attributes({}, {});
  ((entity *)IFC4X2_types[261])
      ->set_attributes({new attribute(strings[2667],
                                      new named_type(IFC4X2_types[704]), false),
                        new attribute(strings[2489],
                                      new named_type(IFC4X2_types[260]), false),
                        new attribute(strings[2490],
                                      new aggregation_type(
                                          aggregation_type::set_type, 0, -1,
                                          new named_type(IFC4X2_types[260])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[262])
      ->set_attributes(
          {new attribute(strings[2667], new named_type(IFC4X2_types[1042]),
                         false),
           new attribute(strings[2668],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4X2_types[90])),
                         false),
           new attribute(strings[2669], new named_type(IFC4X2_types[84]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[267])
      ->set_attributes(
          {new attribute(strings[2670], new named_type(IFC4X2_types[141]),
                         false),
           new attribute(strings[2671], new named_type(IFC4X2_types[705]),
                         false),
           new attribute(strings[2672], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[268])
      ->set_attributes({new attribute(strings[2673],
                                      new named_type(IFC4X2_types[263]), true),
                        new attribute(strings[2674],
                                      new named_type(IFC4X2_types[945]), true),
                        new attribute(strings[2675],
                                      new named_type(IFC4X2_types[172]), true),
                        new attribute(strings[2676],
                                      new named_type(IFC4X2_types[84]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[269])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2677],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[271])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X2_types[270])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2673], new named_type(IFC4X2_types[272]),
                         false),
           new attribute(strings[2678], new named_type(IFC4X2_types[723]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[271])
      ->set_attributes(
          {new attribute(strings[2679], new named_type(IFC4X2_types[545]),
                         false),
           new attribute(strings[2680], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[273])
      ->set_attributes(
          {new attribute(strings[2480], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[274])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[276]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[275])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[276]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[282])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[283])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[286])
      ->set_attributes({new attribute(strings[2681],
                                      new named_type(IFC4X2_types[751]), false),
                        new attribute(strings[2560],
                                      new named_type(IFC4X2_types[146]), false),
                        new attribute(strings[2625],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[287])
      ->set_attributes({new attribute(strings[2682],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[288])),
                                      false),
                        new attribute(strings[2683],
                                      new named_type(IFC4X2_types[289]), false),
                        new attribute(strings[2684],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[288])
      ->set_attributes(
          {new attribute(strings[2685], new named_type(IFC4X2_types[641]),
                         false),
           new attribute(strings[2686],
                         new simple_type(simple_type::integer_type), false)},
          {false, false});
  ((entity *)IFC4X2_types[291])
      ->set_attributes(
          {new attribute(strings[2687],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2688],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2689],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2690],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2691],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2692],
                         new simple_type(simple_type::integer_type), false),
           new attribute(strings[2693],
                         new simple_type(simple_type::integer_type), false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[293])
      ->set_attributes({new attribute(strings[2694],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X2_types[811])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[295])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[297]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[296])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[297]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[298])
      ->set_attributes({new attribute(strings[2695],
                                      new named_type(IFC4X2_types[545]), false),
                        new attribute(strings[2696],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2697],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2698],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2699],
                                      new named_type(IFC4X2_types[84]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[299])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[301]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[300])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[301]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[302])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[303])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[304])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[305])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[306])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[307])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[308])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[309])
      ->set_attributes({new attribute(strings[2700],
                                      new named_type(IFC4X2_types[445]), true),
                        new attribute(strings[2464],
                                      new named_type(IFC4X2_types[310]), true),
                        new attribute(strings[2701],
                                      new named_type(IFC4X2_types[312]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[311])
      ->set_attributes({new attribute(strings[2588],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2464],
                                      new named_type(IFC4X2_types[312]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[314])
      ->set_attributes(
          {new attribute(strings[2515], new named_type(IFC4X2_types[505]),
                         false),
           new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         false),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[2609], new named_type(IFC4X2_types[1166]),
                         true),
           new attribute(strings[2471], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[2702], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[2703], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[2704], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2705], new named_type(IFC4X2_types[8]), true),
           new attribute(strings[2706],
                         new aggregation_type(aggregation_type::set_type, 1, -1,
                                              new named_type(IFC4X2_types[8])),
                         true),
           new attribute(strings[2642], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[2707], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[2708], new named_type(IFC4X2_types[505]),
                         true),
           new attribute(strings[2709], new named_type(IFC4X2_types[278]),
                         true),
           new attribute(strings[2710], new named_type(IFC4X2_types[278]),
                         true),
           new attribute(strings[2711], new named_type(IFC4X2_types[313]),
                         true),
           new attribute(strings[2465], new named_type(IFC4X2_types[318]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[315])
      ->set_attributes({new attribute(strings[2712],
                                      new named_type(IFC4X2_types[314]), false),
                        new attribute(strings[2713],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[314])),
                                      false),
                        new attribute(strings[2714],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[316])
      ->set_attributes({new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2715],
                                      new named_type(IFC4X2_types[314]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[319])
      ->set_attributes({new attribute(strings[2716],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2717],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2464],
                                      new named_type(IFC4X2_types[329]), true),
                        new attribute(strings[2718],
                                      new named_type(IFC4X2_types[330]), true),
                        new attribute(strings[2719],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X2_types[320])
      ->set_attributes({new attribute(strings[2720],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2721],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2722],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2723],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2724],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2725],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2726],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2727],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2728],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2729],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2730],
                                      new named_type(IFC4X2_types[931]), true),
                        new attribute(strings[2731],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2732],
                                      new named_type(IFC4X2_types[545]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false, false,
                        false});
  ((entity *)IFC4X2_types[323])
      ->set_attributes(
          {new attribute(strings[2733], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[2734], new named_type(IFC4X2_types[321]),
                         false),
           new attribute(strings[2735], new named_type(IFC4X2_types[643]),
                         true),
           new attribute(strings[2736], new named_type(IFC4X2_types[322]),
                         false),
           new attribute(strings[2730], new named_type(IFC4X2_types[931]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[324])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false, false});
  ((entity *)IFC4X2_types[325])
      ->set_attributes({new attribute(strings[2718],
                                      new named_type(IFC4X2_types[327]), false),
                        new attribute(strings[2737],
                                      new named_type(IFC4X2_types[326]), false),
                        new attribute(strings[2738],
                                      new named_type(IFC4X2_types[84]), false),
                        new attribute(strings[2739],
                                      new named_type(IFC4X2_types[84]), false)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X2_types[328])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[329]),
                         false),
           new attribute(strings[2718], new named_type(IFC4X2_types[330]),
                         false),
           new attribute(strings[2738], new named_type(IFC4X2_types[84]), true),
           new attribute(strings[2719], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X2_types[332])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[333])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[334])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[336]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[335])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[336]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[337])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[339]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[338])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[339]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[340])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[342]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[341])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[342]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[345])
      ->set_attributes(
          {new attribute(strings[2740], new named_type(IFC4X2_types[1175]),
                         false),
           new attribute(strings[2741], new named_type(IFC4X2_types[1175]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[346])
      ->set_attributes({new attribute(strings[2742],
                                      new named_type(IFC4X2_types[260]), false),
                        new attribute(strings[2622],
                                      new named_type(IFC4X2_types[84]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[347])
      ->set_attributes({new attribute(strings[2743],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[666])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[348])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[350]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[349])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[350]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[355])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[357]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[356])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[357]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[358])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[360]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[359])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[360]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[361])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[363]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[362])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[363]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[364])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[366]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[365])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[366]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[368])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[370]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[369])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[370]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[372])
      ->set_attributes(
          {new attribute(strings[2488], new named_type(IFC4X2_types[505]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[374])
      ->set_attributes(
          {new attribute(strings[2744], new named_type(IFC4X2_types[58]), true),
           new attribute(strings[2464], new named_type(IFC4X2_types[376]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[375])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[376]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[377])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[378])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[380])
      ->set_attributes({new attribute(strings[2745],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2746],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[687])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[381])
      ->set_attributes(
          {new attribute(strings[2747], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[373])
      ->set_attributes({new attribute(strings[2626],
                                      new named_type(IFC4X2_types[67]), false)},
                       {false});
  ((entity *)IFC4X2_types[382])
      ->set_attributes(
          {new attribute(strings[2748], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2749], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[383])
      ->set_attributes(
          {new attribute(strings[2748], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2749], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[384])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[385])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[387])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[389]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[388])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[389]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[390])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[392]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[391])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[392]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[393])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[395]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[394])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[395]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[396])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[400]), true),
                        new attribute(strings[2750],
                                      new named_type(IFC4X2_types[398]), true),
                        new attribute(strings[2751],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2752],
                                      new named_type(IFC4X2_types[397]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[397])
      ->set_attributes({new attribute(strings[2753],
                                      new named_type(IFC4X2_types[279]), true),
                        new attribute(strings[2754],
                                      new named_type(IFC4X2_types[279]), true),
                        new attribute(strings[2755],
                                      new named_type(IFC4X2_types[279]), true),
                        new attribute(strings[2756],
                                      new named_type(IFC4X2_types[279]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[399])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[400]), false),
                        new attribute(strings[2750],
                                      new named_type(IFC4X2_types[398]), false),
                        new attribute(strings[2751],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X2_types[401])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2757],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[762])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[402])->set_attributes({}, {});
  ((entity *)IFC4X2_types[406])
      ->set_attributes({new attribute(strings[2609],
                                      new named_type(IFC4X2_types[1166]), true),
                        new attribute(strings[2515],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[407])
      ->set_attributes({new attribute(strings[2758],
                                      new named_type(IFC4X2_types[406]), false),
                        new attribute(strings[2759],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[893])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[408])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[409]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[410])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[403])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X2_types[404])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X2_types[405])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X2_types[411])
      ->set_attributes(
          {new attribute(strings[2760], new named_type(IFC4X2_types[293]),
                         false),
           new attribute(strings[2589], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[412])
      ->set_attributes(
          {new attribute(strings[2761], new named_type(IFC4X2_types[751]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[413])
      ->set_attributes({new attribute(strings[2762],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[415])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[414])
      ->set_attributes({new attribute(strings[2763],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[200])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[415])
      ->set_attributes({new attribute(strings[2764],
                                      new named_type(IFC4X2_types[576]), false),
                        new attribute(strings[2765],
                                      new named_type(IFC4X2_types[84]), false)},
                       {false, false});
  ((entity *)IFC4X2_types[416])->set_attributes({}, {false, false});
  ((entity *)IFC4X2_types[417])
      ->set_attributes(
          {new attribute(strings[2766], new named_type(IFC4X2_types[1042]),
                         false),
           new attribute(strings[2622], new named_type(IFC4X2_types[84]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[418])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[419])
      ->set_attributes({new attribute(strings[2473],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[168])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X2_types[420])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[421])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[422])
      ->set_attributes({new attribute(strings[2767],
                                      new named_type(IFC4X2_types[470]), true),
                        new attribute(strings[2768],
                                      new named_type(IFC4X2_types[470]), true),
                        new attribute(strings[2769],
                                      new named_type(IFC4X2_types[470]), true),
                        new attribute(strings[2770],
                                      new named_type(IFC4X2_types[470]), true),
                        new attribute(strings[2771],
                                      new named_type(IFC4X2_types[470]), true),
                        new attribute(strings[2772],
                                      new named_type(IFC4X2_types[470]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[423])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[425]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[424])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[425]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[426])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[428]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[427])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[428]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[429])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[430])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[431])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[432])
      ->set_attributes({new attribute(strings[2773],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[435])),
                                      false),
                        new attribute(strings[2774],
                                      new named_type(IFC4X2_types[84]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[433])
      ->set_attributes(
          {new attribute(strings[2775], new named_type(IFC4X2_types[268]),
                         false),
           new attribute(strings[2776], new named_type(IFC4X2_types[496]),
                         false),
           new attribute(strings[2777], new named_type(IFC4X2_types[141]),
                         true),
           new attribute(strings[2778], new named_type(IFC4X2_types[141]),
                         true),
           new attribute(strings[2779], new named_type(IFC4X2_types[705]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[434])
      ->set_attributes(
          {new attribute(
               strings[2780],
               new aggregation_type(aggregation_type::list_type, 2, 2,
                                    new named_type(IFC4X2_types[1173])),
               false),
           new attribute(
               strings[2781],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[1035])),
               false),
           new attribute(strings[2782], new named_type(IFC4X2_types[723]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[436])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[438]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[437])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[438]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[439])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[441]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[440])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[441]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[442])
      ->set_attributes(
          {new attribute(strings[2783], new named_type(IFC4X2_types[260]),
                         false),
           new attribute(strings[2784], new named_type(IFC4X2_types[673]),
                         true),
           new attribute(strings[2785], new named_type(IFC4X2_types[673]),
                         true),
           new attribute(strings[2786], new named_type(IFC4X2_types[293]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[443])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[444])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[446])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[447])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[448])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[450]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[449])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[450]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[451])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[453]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[452])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[453]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[454])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[455])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[456])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[457])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[458])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[459])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[460])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[461])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[462])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[463])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[467])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[469]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[468])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[469]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[472])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[473])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[474])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[476]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[475])
      ->set_attributes({new attribute(strings[2744],
                                      new named_type(IFC4X2_types[58]), false),
                        new attribute(strings[2464],
                                      new named_type(IFC4X2_types[476]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[477])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[479]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[478])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[479]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[480])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[482])
      ->set_attributes({new attribute(strings[2787],
                                      new named_type(IFC4X2_types[292]), false),
                        new attribute(strings[2788],
                                      new named_type(IFC4X2_types[811]), true),
                        new attribute(strings[2789],
                                      new named_type(IFC4X2_types[65]), false),
                        new attribute(strings[2790],
                                      new named_type(IFC4X2_types[293]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[483])->set_attributes({}, {});
  ((entity *)IFC4X2_types[484])
      ->set_attributes(
          {new attribute(strings[2791], new named_type(IFC4X2_types[482]),
                         false),
           new attribute(strings[2792], new named_type(IFC4X2_types[723]),
                         true),
           new attribute(strings[2793], new named_type(IFC4X2_types[481]),
                         false),
           new attribute(strings[2794], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, true, true, true, true, false, false, false, false});
  ((entity *)IFC4X2_types[485])
      ->set_attributes({new attribute(strings[2682],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[486])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[489])
      ->set_attributes({new attribute(strings[2795],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[490])),
                                      false),
                        new attribute(strings[2796],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[490])),
                                      false),
                        new attribute(strings[2797],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[490])),
                                      true),
                        new attribute(strings[2464],
                                      new named_type(IFC4X2_types[493]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[490])
      ->set_attributes({new attribute(strings[2798],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2799],
                                      new named_type(IFC4X2_types[260]), false),
                        new attribute(strings[2622],
                                      new named_type(IFC4X2_types[84]), false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[491])
      ->set_attributes(
          {new attribute(strings[2800], new named_type(IFC4X2_types[1185]),
                         false),
           new attribute(strings[2801], new named_type(IFC4X2_types[492]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X2_types[494])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC4X2_types[495])
      ->set_attributes(
          {new attribute(strings[2802], new named_type(IFC4X2_types[1042]),
                         false),
           new attribute(strings[2803], new named_type(IFC4X2_types[84]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[497])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[499]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[498])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[499]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[502])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[504]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[503])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[504]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[527])
      ->set_attributes({new attribute(strings[2717],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2525],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2526],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2804],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2805],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2806],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2807],
                                      new named_type(IFC4X2_types[705]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[507])
      ->set_attributes(
          {new attribute(strings[2808], new named_type(IFC4X2_types[1166]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[508])
      ->set_attributes(
          {new attribute(strings[2809], new named_type(IFC4X2_types[1095]),
                         false),
           new attribute(strings[2810], new named_type(IFC4X2_types[643]),
                         true),
           new attribute(strings[2811], new named_type(IFC4X2_types[175]),
                         false),
           new attribute(
               strings[2812],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[720])),
               false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[509])
      ->set_attributes({new attribute(strings[2813],
                                      new named_type(IFC4X2_types[142]), false),
                        new attribute(strings[2475],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[923])),
                                      true),
                        new attribute(strings[2542],
                                      new named_type(IFC4X2_types[84]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[510])
      ->set_attributes({new attribute(strings[2814],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC4X2_types[720])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[511])
      ->set_attributes(
          {new attribute(
              strings[2815],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, -1,
                                       new named_type(IFC4X2_types[720]))),
              false)},
          {false, false});
  ((entity *)IFC4X2_types[512])
      ->set_attributes(
          {new attribute(strings[2809], new named_type(IFC4X2_types[1095]),
                         false),
           new attribute(strings[2816], new named_type(IFC4X2_types[1114]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[513])
      ->set_attributes(
          {new attribute(
              strings[2817],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 3, 3,
                                       new named_type(IFC4X2_types[720]))),
              true)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[517])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[519]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[518])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[519]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[521])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X2_types[522])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[523]),
                         true),
           new attribute(strings[2818], new named_type(IFC4X2_types[8]), true),
           new attribute(
               strings[2819],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[682])),
               true),
           new attribute(strings[2820], new named_type(IFC4X2_types[278]),
                         true),
           new attribute(strings[2517], new named_type(IFC4X2_types[243]),
                         true),
           new attribute(strings[2516], new named_type(IFC4X2_types[243]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[525])
      ->set_attributes(
          {new attribute(
              strings[2821],
              new aggregation_type(aggregation_type::list_type, 1, -1,
                                   new named_type(IFC4X2_types[526])),
              false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[526])
      ->set_attributes({new attribute(strings[2822],
                                      new named_type(IFC4X2_types[279]), false),
                        new attribute(strings[2823],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[1168])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X2_types[529])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[531]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[530])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[531]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[577])
      ->set_attributes(
          {new attribute(strings[2589], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2590], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[2604], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2805], new named_type(IFC4X2_types[642]),
                         true),
           new attribute(strings[2824], new named_type(IFC4X2_types[642]),
                         true),
           new attribute(strings[2825], new named_type(IFC4X2_types[705]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[535])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[537]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[536])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[537]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X2_types[538])
      ->set_attributes(
          {new attribute(strings[2826], new named_type(IFC4X2_types[1123]),
                         false),
           new attribute(strings[2827], new named_type(IFC4X2_types[1078]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[539])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[541]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[540])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[541]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[546])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         false),
           new attribute(strings[2492], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2828], new named_type(IFC4X2_types[8]), true),
           new attribute(strings[2829], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[2609], new named_type(IFC4X2_types[1166]),
                         true),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[547])
      ->set_attributes({new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2830],
                                      new named_type(IFC4X2_types[542]), true),
                        new attribute(strings[2831],
                                      new named_type(IFC4X2_types[546]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[550])
      ->set_attributes({new attribute(strings[2832],
                                      new named_type(IFC4X2_types[705]), false),
                        new attribute(strings[2833],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[705])),
                                      false),
                        new attribute(strings[2834],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[579])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[553])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[555]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[554])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[555]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[556])
      ->set_attributes({new attribute(strings[2835],
                                      new named_type(IFC4X2_types[549]), false),
                        new attribute(strings[2836],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[550])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X2_types[557])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2837],
                                      new named_type(IFC4X2_types[174]), false),
                        new attribute(strings[2838],
                                      new named_type(IFC4X2_types[643]), true),
                        new attribute(strings[2839],
                                      new named_type(IFC4X2_types[643]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[558])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[559])
      ->set_attributes(
          {new attribute(strings[2765], new named_type(IFC4X2_types[293]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[560])
      ->set_attributes(
          {new attribute(strings[2626], new named_type(IFC4X2_types[67]),
                         false),
           new attribute(strings[2840], new named_type(IFC4X2_types[174]),
                         true),
           new attribute(strings[2841], new named_type(IFC4X2_types[1120]),
                         false),
           new attribute(strings[2842], new named_type(IFC4X2_types[578]),
                         false),
           new attribute(strings[2843], new named_type(IFC4X2_types[552]),
                         false),
           new attribute(strings[2844], new named_type(IFC4X2_types[551]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[561])
      ->set_attributes(
          {new attribute(strings[2626], new named_type(IFC4X2_types[141]),
                         false),
           new attribute(strings[2480], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2845], new named_type(IFC4X2_types[811]),
                         false),
           new attribute(strings[2846], new named_type(IFC4X2_types[811]),
                         false),
           new attribute(strings[2847], new named_type(IFC4X2_types[811]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[562])
      ->set_attributes(
          {new attribute(strings[2765], new named_type(IFC4X2_types[293]),
                         false),
           new attribute(strings[2848], new named_type(IFC4X2_types[811]),
                         true),
           new attribute(strings[2849], new named_type(IFC4X2_types[722]),
                         false),
           new attribute(strings[2850], new named_type(IFC4X2_types[722]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X2_types[563])
      ->set_attributes(
          {new attribute(strings[2851], new named_type(IFC4X2_types[141]),
                         false),
           new attribute(strings[2852], new named_type(IFC4X2_types[1173]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[571])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X2_types[566])
      ->set_attributes({new attribute(strings[2853],
                                      new named_type(IFC4X2_types[260]), false),
                        new attribute(strings[2854],
                                      new named_type(IFC4X2_types[298]), false),
                        new attribute(strings[2765],
                                      new named_type(IFC4X2_types[665]), true),
                        new attribute(strings[2855],
                                      new named_type(IFC4X2_types[67]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[567])
      ->set_attributes(
          {new attribute(strings[2536], new named_type(IFC4X2_types[260]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[573])
      ->set_attributes({new attribute(strings[2856],
                                      new named_type(IFC4X2_types[65]), false)},
                       {false, false});
  ((entity *)IFC4X2_types[576])->set_attributes({}, {});
  ((entity *)IFC4X2_types[583])
      ->set_attributes(
          {new attribute(strings[2857], new named_type(IFC4X2_types[168]),
                         false)},
          {false});
  ((entity *)IFC4X2_types[584])
      ->set_attributes(
          {new attribute(strings[2858], new named_type(IFC4X2_types[545]),
                         false),
           new attribute(strings[2859], new named_type(IFC4X2_types[545]),
                         false),
           new attribute(strings[2860], new named_type(IFC4X2_types[545]),
                         false),
           new attribute(strings[2861], new named_type(IFC4X2_types[811]),
                         true),
           new attribute(strings[2862], new named_type(IFC4X2_types[811]),
                         true),
           new attribute(strings[2600], new named_type(IFC4X2_types[811]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[585])
      ->set_attributes(
          {new attribute(strings[2863], new named_type(IFC4X2_types[888]),
                         false),
           new attribute(strings[2864], new named_type(IFC4X2_types[145]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[590])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), false),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2500],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[591])
      ->set_attributes(
          {new attribute(
               strings[2865],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[167])),
               false),
           new attribute(strings[2866], new named_type(IFC4X2_types[590]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[592])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2867],
                                      new named_type(IFC4X2_types[590]), false),
                        new attribute(strings[2868],
                                      new named_type(IFC4X2_types[643]), true),
                        new attribute(strings[2500],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[593])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2869],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[592])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[594])->set_attributes({}, {});
  ((entity *)IFC4X2_types[595])
      ->set_attributes(
          {new attribute(strings[2870], new named_type(IFC4X2_types[590]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[596])
      ->set_attributes({new attribute(strings[2867],
                                      new named_type(IFC4X2_types[590]), true),
                        new attribute(strings[2871],
                                      new named_type(IFC4X2_types[642]), false),
                        new attribute(strings[2872],
                                      new named_type(IFC4X2_types[574]), true),
                        new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2500],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2873],
                                      new named_type(IFC4X2_types[515]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[597])
      ->set_attributes(
          {new attribute(
               strings[2874],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[596])),
               false),
           new attribute(strings[2875], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X2_types[598])
      ->set_attributes({new attribute(strings[2876],
                                      new named_type(IFC4X2_types[597]), false),
                        new attribute(strings[2877],
                                      new named_type(IFC4X2_types[544]), false),
                        new attribute(strings[2878],
                                      new named_type(IFC4X2_types[294]), false),
                        new attribute(strings[2879],
                                      new named_type(IFC4X2_types[545]), false),
                        new attribute(strings[2880],
                                      new named_type(IFC4X2_types[721]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[599])
      ->set_attributes(
          {new attribute(strings[2881], new named_type(IFC4X2_types[544]),
                         false),
           new attribute(
               strings[2882],
               new aggregation_type(aggregation_type::array_type, 1, 2,
                                    new named_type(IFC4X2_types[545])),
               false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[600])
      ->set_attributes({new attribute(strings[2883],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[590])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[601])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2867],
                                      new named_type(IFC4X2_types[590]), true),
                        new attribute(strings[2884],
                                      new named_type(IFC4X2_types[751]), false),
                        new attribute(strings[2873],
                                      new named_type(IFC4X2_types[515]), true),
                        new attribute(strings[2500],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[602])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2885],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[601])),
                                      false),
                        new attribute(strings[2886],
                                      new named_type(IFC4X2_types[191]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[603])
      ->set_attributes({new attribute(strings[2887],
                                      new named_type(IFC4X2_types[602]), false),
                        new attribute(strings[2888],
                                      new named_type(IFC4X2_types[140]), true),
                        new attribute(strings[2880],
                                      new named_type(IFC4X2_types[721]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[604])
      ->set_attributes({new attribute(strings[2889],
                                      new named_type(IFC4X2_types[602]), false),
                        new attribute(strings[2890],
                                      new named_type(IFC4X2_types[140]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[605])
      ->set_attributes({new attribute(strings[2882],
                                      new aggregation_type(
                                          aggregation_type::array_type, 1, 2,
                                          new named_type(IFC4X2_types[545])),
                                      false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[606])
      ->set_attributes(
          {new attribute(strings[2867], new named_type(IFC4X2_types[594]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[607])
      ->set_attributes({new attribute(strings[2891],
                                      new named_type(IFC4X2_types[590]), false),
                        new attribute(strings[2892],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[590])),
                                      false),
                        new attribute(strings[2893],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[609])->set_attributes({}, {});
  ((entity *)IFC4X2_types[611])
      ->set_attributes(
          {new attribute(strings[2894], new named_type(IFC4X2_types[1168]),
                         false),
           new attribute(strings[2895], new named_type(IFC4X2_types[1157]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[612])
      ->set_attributes({new attribute(strings[2896],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2897],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2464],
                                      new named_type(IFC4X2_types[614]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[613])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[614]), false),
                        new attribute(strings[2896],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2897],
                                      new named_type(IFC4X2_types[721]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X2_types[615])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[617]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[616])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[617]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[618])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[621]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[619])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[620])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[621]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[622])
      ->set_attributes({new attribute(strings[2898],
                                      new named_type(IFC4X2_types[76]), false),
                        new attribute(strings[2899],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2900],
                                      new named_type(IFC4X2_types[623]), true),
                        new attribute(strings[2901],
                                      new named_type(IFC4X2_types[818]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[624])
      ->set_attributes({}, {false, false, false, true, false});
  ((entity *)IFC4X2_types[636])
      ->set_attributes(
          {new attribute(strings[2902], new named_type(IFC4X2_types[534]),
                         false)},
          {false});
  ((entity *)IFC4X2_types[638])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[640]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[639])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[640]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[641])
      ->set_attributes(
          {new attribute(strings[2903], new named_type(IFC4X2_types[291]),
                         false),
           new attribute(strings[2683], new named_type(IFC4X2_types[1165]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[646])
      ->set_attributes({new attribute(strings[2647],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[647])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[650])
      ->set_attributes({new attribute(strings[2904],
                                      new named_type(IFC4X2_types[650]), true)},
                       {false});
  ((entity *)IFC4X2_types[648])
      ->set_attributes({new attribute(strings[2905],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[208])),
                                      true),
                        new attribute(strings[2906],
                                      new named_type(IFC4X2_types[575]), true),
                        new attribute(strings[2907],
                                      new named_type(IFC4X2_types[649]), false),
                        new attribute(strings[2908],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[653])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[654]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[655])
      ->set_attributes(
          {new attribute(strings[2909], new named_type(IFC4X2_types[260]),
                         false)},
          {false});
  ((entity *)IFC4X2_types[656])
      ->set_attributes(
          {new attribute(strings[2854], new named_type(IFC4X2_types[545]),
                         false),
           new attribute(strings[2542], new named_type(IFC4X2_types[574]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[657])
      ->set_attributes(
          {new attribute(strings[2854], new named_type(IFC4X2_types[545]),
                         false),
           new attribute(strings[2542], new named_type(IFC4X2_types[574]),
                         false),
           new attribute(strings[2537], new named_type(IFC4X2_types[293]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[658])
      ->set_attributes({new attribute(strings[2882],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[298])),
                                      false),
                        new attribute(strings[2488],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[662])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[659])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[660]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[661])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[663])
      ->set_attributes({new attribute(strings[2515],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), false),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2910],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[7])),
                                      true),
                        new attribute(strings[2911],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[12])),
                                      true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[664])
      ->set_attributes({new attribute(strings[2912],
                                      new named_type(IFC4X2_types[663]), false),
                        new attribute(strings[2913],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[663])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[665])
      ->set_attributes(
          {new attribute(strings[2914], new named_type(IFC4X2_types[293]),
                         false),
           new attribute(strings[2915], new named_type(IFC4X2_types[293]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[666])
      ->set_attributes({new attribute(strings[2916],
                                      new named_type(IFC4X2_types[345]), false),
                        new attribute(strings[2765],
                                      new named_type(IFC4X2_types[84]), false)},
                       {true, true, false, false});
  ((entity *)IFC4X2_types[667])->set_attributes({}, {false, false});
  ((entity *)IFC4X2_types[668])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[670]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[669])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[670]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[671])
      ->set_attributes(
          {new attribute(strings[2917], new named_type(IFC4X2_types[683]),
                         false),
           new attribute(strings[2918], new named_type(IFC4X2_types[46]),
                         false),
           new attribute(strings[2919], new named_type(IFC4X2_types[991]),
                         true),
           new attribute(strings[2920], new named_type(IFC4X2_types[151]),
                         true),
           new attribute(strings[2921], new named_type(IFC4X2_types[1128]),
                         true),
           new attribute(strings[2922], new named_type(IFC4X2_types[683]),
                         true),
           new attribute(strings[2923], new named_type(IFC4X2_types[46]), true),
           new attribute(strings[2924], new named_type(IFC4X2_types[1128]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[672])
      ->set_attributes({new attribute(strings[2626],
                                      new named_type(IFC4X2_types[66]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[674])
      ->set_attributes({new attribute(strings[2743],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[666])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[675])
      ->set_attributes(
          {new attribute(strings[2667], new named_type(IFC4X2_types[1042]),
                         false),
           new attribute(strings[2925], new named_type(IFC4X2_types[260]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[676])
      ->set_attributes(
          {new attribute(strings[2926], new named_type(IFC4X2_types[534]),
                         false),
           new attribute(strings[2464], new named_type(IFC4X2_types[677]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[679])
      ->set_attributes(
          {new attribute(strings[2718], new named_type(IFC4X2_types[678]),
                         false),
           new attribute(strings[2736], new named_type(IFC4X2_types[1204]),
                         false),
           new attribute(strings[2927], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[2928], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[2730], new named_type(IFC4X2_types[931]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[680])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[681]),
                         true),
           new attribute(strings[2465], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2466], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[682])
      ->set_attributes(
          {new attribute(strings[2515], new named_type(IFC4X2_types[505]),
                         true),
           new attribute(strings[2929], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2930], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(
               strings[2931],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[534])),
               true),
           new attribute(
               strings[2932],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[534])),
               true),
           new attribute(
               strings[2933],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[534])),
               true),
           new attribute(strings[2910],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X2_types[7])),
                         true),
           new attribute(strings[2911],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X2_types[12])),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[683])
      ->set_attributes({new attribute(strings[2934],
                                      new named_type(IFC4X2_types[682]), false),
                        new attribute(strings[2935],
                                      new named_type(IFC4X2_types[663]), false),
                        new attribute(strings[2910],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[7])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[685])
      ->set_attributes({new attribute(strings[2936],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[687])),
                                      false),
                        new attribute(strings[2937],
                                      new named_type(IFC4X2_types[534]), false),
                        new attribute(strings[2938],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2644],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[687])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         false),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false});
  ((entity *)IFC4X2_types[688])
      ->set_attributes({new attribute(strings[2685],
                                      new named_type(IFC4X2_types[641]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[689])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[692]), true),
                        new attribute(strings[2737],
                                      new named_type(IFC4X2_types[690]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[691])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[692]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[693])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[695]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[694])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[695]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[696])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[698]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[697])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[698]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[699])
      ->set_attributes(
          {new attribute(strings[2590], new named_type(IFC4X2_types[515]),
                         false),
           new attribute(strings[2939], new named_type(IFC4X2_types[515]),
                         false),
           new attribute(strings[2940], new named_type(IFC4X2_types[515]),
                         false),
           new attribute(strings[2941],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X2_types[78])),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[700])
      ->set_attributes(
          {new attribute(strings[2609], new named_type(IFC4X2_types[141]),
                         false)},
          {false});
  ((entity *)IFC4X2_types[701])
      ->set_attributes({new attribute(strings[2942],
                                      new named_type(IFC4X2_types[65]), false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[702])
      ->set_attributes(
          {new attribute(strings[2943], new named_type(IFC4X2_types[545]),
                         false),
           new attribute(strings[2944], new named_type(IFC4X2_types[545]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[704])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[706])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[709]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[707])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[708])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[709]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[710])->set_attributes({}, {});
  ((entity *)IFC4X2_types[711])
      ->set_attributes(
          {new attribute(strings[2909], new named_type(IFC4X2_types[260]),
                         false),
           new attribute(strings[2945], new named_type(IFC4X2_types[673]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[712])
      ->set_attributes(
          {new attribute(strings[2667], new named_type(IFC4X2_types[1042]),
                         false),
           new attribute(strings[2946], new named_type(IFC4X2_types[673]),
                         false),
           new attribute(strings[2947], new named_type(IFC4X2_types[673]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[717])
      ->set_attributes({new attribute(strings[2948],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, -1,
                                          new named_type(IFC4X2_types[141])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[714])
      ->set_attributes({new attribute(strings[2626],
                                      new named_type(IFC4X2_types[67]), false),
                        new attribute(strings[2949],
                                      new named_type(IFC4X2_types[95]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[715])
      ->set_attributes(
          {new attribute(strings[2950], new named_type(IFC4X2_types[84]), true),
           new attribute(
               strings[2951],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[510])),
               false),
           new attribute(
               strings[2952],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[720])),
               true)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[716])
      ->set_attributes({new attribute(strings[2813],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X2_types[141])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[718])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[719])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[724])
      ->set_attributes({new attribute(strings[2953],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2954],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[534])),
                                      true),
                        new attribute(strings[2955],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2956],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2957],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2958],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2959],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[726])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[727])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[728])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         false)},
          {false});
  ((entity *)IFC4X2_types[729])->set_attributes({}, {});
  ((entity *)IFC4X2_types[730])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[731])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[734])->set_attributes({}, {});
  ((entity *)IFC4X2_types[735])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), false),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2960],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[543])),
                                      false),
                        new attribute(strings[2504],
                                      new named_type(IFC4X2_types[505]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[736])
      ->set_attributes(
          {new attribute(strings[2961], new named_type(IFC4X2_types[574]),
                         false),
           new attribute(strings[2962], new named_type(IFC4X2_types[574]),
                         false),
           new attribute(strings[2963], new named_type(IFC4X2_types[574]),
                         false),
           new attribute(
               strings[2964],
               new aggregation_type(aggregation_type::set_type, 0, -1,
                                    new named_type(IFC4X2_types[737])),
               false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[737])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false});
  ((entity *)IFC4X2_types[738])
      ->set_attributes({new attribute(strings[2965],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[739])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[741])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[743]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[742])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[743]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[744])
      ->set_attributes(
          {new attribute(strings[2515], new named_type(IFC4X2_types[505]),
                         true),
           new attribute(strings[2466], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[746])
      ->set_attributes({new attribute(strings[2966],
                                      new named_type(IFC4X2_types[650]), true),
                        new attribute(strings[2967],
                                      new named_type(IFC4X2_types[748]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[747])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X2_types[748])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2968],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[885])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[751])
      ->set_attributes({new attribute(strings[2969],
                                      new named_type(IFC4X2_types[753]), false),
                        new attribute(strings[2970],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[752])
      ->set_attributes(
          {new attribute(strings[2971], new named_type(IFC4X2_types[751]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[754])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[759])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[760])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[761]),
                         true),
           new attribute(strings[2465], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2466], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[755])
      ->set_attributes({new attribute(strings[2972],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[2973],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[2974],
                                      new named_type(IFC4X2_types[641]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[757])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[758]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[762])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[505]),
                         false),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false});
  ((entity *)IFC4X2_types[763])->set_attributes({}, {});
  ((entity *)IFC4X2_types[764])
      ->set_attributes(
          {new attribute(strings[2975], new named_type(IFC4X2_types[1168]),
                         true),
           new attribute(strings[2976], new named_type(IFC4X2_types[1168]),
                         true),
           new attribute(strings[2685], new named_type(IFC4X2_types[1157]),
                         true),
           new attribute(strings[2977], new named_type(IFC4X2_types[1168]),
                         true)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[765])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[766])
      ->set_attributes(
          {new attribute(strings[2978], new named_type(IFC4X2_types[762]),
                         false),
           new attribute(strings[2979], new named_type(IFC4X2_types[762]),
                         false),
           new attribute(strings[2893], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[767])
      ->set_attributes({new attribute(strings[2980],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[1168])),
                                      true),
                        new attribute(strings[2981],
                                      new named_type(IFC4X2_types[768]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[768])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         false),
           new attribute(
               strings[2980],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[1168])),
               false),
           new attribute(strings[2685], new named_type(IFC4X2_types[1157]),
                         true)},
          {false, false, false});
  ((entity *)IFC4X2_types[769])
      ->set_attributes(
          {new attribute(
               strings[2823],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[1168])),
               true),
           new attribute(strings[2685], new named_type(IFC4X2_types[1157]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[770])
      ->set_attributes({new attribute(strings[2617],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2982],
                                      new named_type(IFC4X2_types[651]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[771])
      ->set_attributes({new attribute(strings[2618],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[762])),
                                      false)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[772])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[775])
      ->set_attributes({new attribute(strings[2619],
                                      new named_type(IFC4X2_types[776]), true),
                        new attribute(strings[2983],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[2620],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[779])),
                                      false)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[777])
      ->set_attributes(
          {new attribute(strings[2984], new named_type(IFC4X2_types[1168]),
                         true),
           new attribute(strings[2685], new named_type(IFC4X2_types[1157]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[778])
      ->set_attributes(
          {new attribute(
               strings[2985],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[1168])),
               true),
           new attribute(
               strings[2986],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[1168])),
               true),
           new attribute(strings[2893], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[2987], new named_type(IFC4X2_types[1157]),
                         true),
           new attribute(strings[2988], new named_type(IFC4X2_types[1157]),
                         true),
           new attribute(strings[2989], new named_type(IFC4X2_types[264]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[779])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[780])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[781])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[786]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[782])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[784]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[783])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[784]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[785])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[786]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[787])
      ->set_attributes(
          {new attribute(strings[2990], new named_type(IFC4X2_types[652]),
                         false),
           new attribute(strings[2488], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[788])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[790]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[789])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[790]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[791])
      ->set_attributes({new attribute(strings[2991],
                                      new named_type(IFC4X2_types[56]), false),
                        new attribute(strings[2992],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[792])
      ->set_attributes({new attribute(strings[2993],
                                      new named_type(IFC4X2_types[244]), false),
                        new attribute(strings[2992],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[793])
      ->set_attributes({new attribute(strings[2994],
                                      new named_type(IFC4X2_types[545]), false),
                        new attribute(strings[2992],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[794])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[795])
      ->set_attributes(
          {new attribute(strings[2995], new named_type(IFC4X2_types[1122]),
                         false),
           new attribute(strings[2992], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[796])
      ->set_attributes(
          {new attribute(strings[2996], new named_type(IFC4X2_types[1188]),
                         false),
           new attribute(strings[2992], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[797])
      ->set_attributes({new attribute(strings[2997],
                                      new named_type(IFC4X2_types[588]), false),
                        new attribute(strings[2992],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[799])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[801]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[800])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[801]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[802])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[807]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[803])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[805]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[804])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[805]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[806])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[807]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[809])
      ->set_attributes(
          {new attribute(
              strings[2998],
              new aggregation_type(aggregation_type::list_type, 2, -1,
                                   new named_type(IFC4X2_types[811])),
              false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[810])
      ->set_attributes(
          {new attribute(
              strings[2998],
              new aggregation_type(
                  aggregation_type::list_type, 2, -1,
                  new aggregation_type(aggregation_type::list_type, 2, -1,
                                       new named_type(IFC4X2_types[811]))),
              false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X2_types[812])
      ->set_attributes(
          {new attribute(strings[2591], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2999], new named_type(IFC4X2_types[642]),
                         true),
           new attribute(strings[3000], new named_type(IFC4X2_types[642]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[813])
      ->set_attributes(
          {new attribute(strings[2580], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2581], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[814])
      ->set_attributes(
          {new attribute(strings[2557], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2558], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2939], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[815])
      ->set_attributes(
          {new attribute(strings[2667], new named_type(IFC4X2_types[1042]),
                         false),
           new attribute(strings[3001], new named_type(IFC4X2_types[673]),
                         false),
           new attribute(strings[3002], new named_type(IFC4X2_types[673]),
                         false),
           new attribute(strings[3003], new named_type(IFC4X2_types[673]),
                         false),
           new attribute(strings[3004], new named_type(IFC4X2_types[673]),
                         false),
           new attribute(strings[3005], new named_type(IFC4X2_types[84]),
                         false),
           new attribute(strings[3006], new named_type(IFC4X2_types[84]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[816])
      ->set_attributes(
          {new attribute(strings[3007], new named_type(IFC4X2_types[817]),
                         false),
           new attribute(
               strings[3008],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[280])),
               true),
           new attribute(
               strings[3009],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[281])),
               true),
           new attribute(
               strings[3010],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[637])),
               true),
           new attribute(strings[2626], new named_type(IFC4X2_types[515]),
                         true),
           new attribute(strings[3011], new named_type(IFC4X2_types[515]),
                         true),
           new attribute(strings[3012], new named_type(IFC4X2_types[515]),
                         true),
           new attribute(
               strings[3013],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[1124])),
               true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[818])
      ->set_attributes({new attribute(strings[3014],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[3015],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[3016],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3017],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[515])),
                                      true),
                        new attribute(strings[3018],
                                      new named_type(IFC4X2_types[818]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[819])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[820]),
                         true),
           new attribute(strings[3019], new named_type(IFC4X2_types[545]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[822])
      ->set_attributes(
          {new attribute(strings[3020], new named_type(IFC4X2_types[1122]),
                         false),
           new attribute(
               strings[2821],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[1127])),
               false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[823])
      ->set_attributes({new attribute(strings[3021],
                                      new named_type(IFC4X2_types[56]), false),
                        new attribute(strings[3022],
                                      new named_type(IFC4X2_types[534]), false),
                        new attribute(strings[3023],
                                      new named_type(IFC4X2_types[827]), true),
                        new attribute(strings[3024],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[3025],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[3026],
                                      new named_type(IFC4X2_types[244]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[824])
      ->set_attributes({new attribute(strings[3027],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3028],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[921])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[825])
      ->set_attributes(
          {new attribute(strings[2896], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3029], new named_type(IFC4X2_types[56]), true),
           new attribute(strings[3030], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[2464], new named_type(IFC4X2_types[829]),
                         true),
           new attribute(strings[3023], new named_type(IFC4X2_types[827]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X2_types[828])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[829]),
                         false),
           new attribute(strings[2896], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3029], new named_type(IFC4X2_types[56]), true),
           new attribute(strings[3030], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3023], new named_type(IFC4X2_types[827]),
                         true),
           new attribute(strings[3031], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[3032],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X2_types[77])),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4X2_types[830])
      ->set_attributes(
          {new attribute(strings[3022], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[831])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[832])
      ->set_attributes(
          {new attribute(strings[3033], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3034], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3035], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3036], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3037], new named_type(IFC4X2_types[56]), true),
           new attribute(strings[3038], new named_type(IFC4X2_types[56]), true),
           new attribute(strings[3039], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3040], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[2464], new named_type(IFC4X2_types[834]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[833])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[834]),
                         false),
           new attribute(strings[3033], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3034], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3035], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3036], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3037], new named_type(IFC4X2_types[56]), true),
           new attribute(strings[3038], new named_type(IFC4X2_types[56]), true),
           new attribute(strings[3039], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3040], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3031], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[3032],
                         new aggregation_type(aggregation_type::list_type, 1,
                                              -1,
                                              new named_type(IFC4X2_types[77])),
                         true)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4X2_types[835])
      ->set_attributes({new attribute(strings[3041],
                                      new named_type(IFC4X2_types[647]), false),
                        new attribute(strings[3042],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[647])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[836])
      ->set_attributes({new attribute(strings[3042],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[647])),
                                      false),
                        new attribute(strings[3043],
                                      new named_type(IFC4X2_types[652]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[837])
      ->set_attributes(
          {new attribute(strings[3044], new named_type(IFC4X2_types[6]), false),
           new attribute(strings[3045], new named_type(IFC4X2_types[7]), true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[838])
      ->set_attributes(
          {new attribute(strings[3046], new named_type(IFC4X2_types[224]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[839])
      ->set_attributes(
          {new attribute(strings[3047], new named_type(IFC4X2_types[494]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[840])
      ->set_attributes(
          {new attribute(strings[3048], new named_type(IFC4X2_types[808]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[841])
      ->set_attributes(
          {new attribute(strings[3049], new named_type(IFC4X2_types[745]),
                         false),
           new attribute(strings[3050], new named_type(IFC4X2_types[611]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[842])
      ->set_attributes(
          {new attribute(strings[3051], new named_type(IFC4X2_types[750]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[843])
      ->set_attributes(
          {new attribute(strings[3052], new named_type(IFC4X2_types[894]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[844])
      ->set_attributes({new attribute(strings[3042],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[284])),
                                      false)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[845])
      ->set_attributes({new attribute(strings[2510],
                                      new named_type(IFC4X2_types[49]), false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[846])
      ->set_attributes(
          {new attribute(strings[3053], new named_type(IFC4X2_types[167]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[847])
      ->set_attributes(
          {new attribute(strings[3054], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[3055], new named_type(IFC4X2_types[208]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[848])
      ->set_attributes(
          {new attribute(strings[2712], new named_type(IFC4X2_types[317]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[849])
      ->set_attributes(
          {new attribute(strings[3056], new named_type(IFC4X2_types[548]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[850])
      ->set_attributes(
          {new attribute(strings[2891], new named_type(IFC4X2_types[608]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[852])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[853])
      ->set_attributes(
          {new attribute(strings[3057], new named_type(IFC4X2_types[202]),
                         true),
           new attribute(strings[3058], new named_type(IFC4X2_types[372]),
                         false),
           new attribute(strings[3059], new named_type(IFC4X2_types[372]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[854])
      ->set_attributes(
          {new attribute(
               strings[3060],
               new aggregation_type(aggregation_type::list_type, 0, -1,
                                    new named_type(IFC4X2_types[515])),
               false),
           new attribute(
               strings[3061],
               new aggregation_type(aggregation_type::list_type, 0, -1,
                                    new named_type(IFC4X2_types[515])),
               false),
           new attribute(strings[3062], new named_type(IFC4X2_types[206]),
                         false),
           new attribute(strings[3063], new named_type(IFC4X2_types[206]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[856])
      ->set_attributes(
          {new attribute(strings[3064], new named_type(IFC4X2_types[718]),
                         false),
           new attribute(strings[3059], new named_type(IFC4X2_types[305]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[855])
      ->set_attributes({new attribute(strings[3064],
                                      new named_type(IFC4X2_types[718]), false),
                        new attribute(strings[3065],
                                      new named_type(IFC4X2_types[718]), false),
                        new attribute(strings[3066],
                                      new named_type(IFC4X2_types[372]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[857])
      ->set_attributes(
          {new attribute(strings[3058], new named_type(IFC4X2_types[994]),
                         false),
           new attribute(strings[3067], new named_type(IFC4X2_types[993]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[858])
      ->set_attributes(
          {new attribute(strings[3068], new named_type(IFC4X2_types[1020]),
                         false),
           new attribute(strings[3069], new named_type(IFC4X2_types[996]),
                         false),
           new attribute(strings[3070], new named_type(IFC4X2_types[89]), true),
           new attribute(strings[3071], new named_type(IFC4X2_types[997]),
                         true),
           new attribute(strings[3072], new named_type(IFC4X2_types[545]),
                         true),
           new attribute(strings[3073], new named_type(IFC4X2_types[67]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[859])
      ->set_attributes(
          {new attribute(strings[3074], new named_type(IFC4X2_types[202]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[860])
      ->set_attributes(
          {new attribute(
               strings[3075],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[372])),
               false),
           new attribute(strings[3076], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[861])
      ->set_attributes(
          {new attribute(
               strings[3077],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[746])),
               false),
           new attribute(strings[3078], new named_type(IFC4X2_types[969]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[862])
      ->set_attributes({new attribute(strings[3079],
                                      new named_type(IFC4X2_types[372]), false),
                        new attribute(strings[3080],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[245])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[863])
      ->set_attributes({new attribute(strings[3081],
                                      new named_type(IFC4X2_types[962]), false),
                        new attribute(strings[3080],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[245])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[864])
      ->set_attributes({new attribute(strings[3082],
                                      new named_type(IFC4X2_types[221]), false),
                        new attribute(strings[3083],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[284])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[865])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[866])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[867])
      ->set_attributes(
          {new attribute(
               strings[3042],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[646])),
               false),
           new attribute(strings[3041], new named_type(IFC4X2_types[646]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[868])
      ->set_attributes(
          {new attribute(
               strings[3042],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[647])),
               false),
           new attribute(strings[3084], new named_type(IFC4X2_types[773]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[869])
      ->set_attributes(
          {new attribute(
               strings[3085],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[772])),
               false),
           new attribute(strings[3086], new named_type(IFC4X2_types[775]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[870])
      ->set_attributes(
          {new attribute(
               strings[3042],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[646])),
               false),
           new attribute(strings[3087], new named_type(IFC4X2_types[1153]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[871])
      ->set_attributes(
          {new attribute(strings[3088], new named_type(IFC4X2_types[659]),
                         false),
           new attribute(strings[3089], new named_type(IFC4X2_types[372]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[872])
      ->set_attributes(
          {new attribute(
               strings[3090],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[303])),
               false),
           new attribute(strings[3091], new named_type(IFC4X2_types[307]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[873])
      ->set_attributes(
          {new attribute(strings[3058], new named_type(IFC4X2_types[372]),
                         false),
           new attribute(strings[3059], new named_type(IFC4X2_types[372]),
                         false),
           new attribute(strings[3092], new named_type(IFC4X2_types[202]),
                         true),
           new attribute(strings[3093], new named_type(IFC4X2_types[505]),
                         true),
           new attribute(strings[3094],
                         new simple_type(simple_type::logical_type), false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[874])
      ->set_attributes({new attribute(strings[3041],
                                      new named_type(IFC4X2_types[647]), false),
                        new attribute(strings[3042],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[647])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[875])
      ->set_attributes({new attribute(strings[3095],
                                      new named_type(IFC4X2_types[719]), false),
                        new attribute(strings[3096],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[746])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[876])
      ->set_attributes(
          {new attribute(strings[3058], new named_type(IFC4X2_types[372]),
                         false),
           new attribute(strings[3097], new named_type(IFC4X2_types[430]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[877])
      ->set_attributes(
          {new attribute(
               strings[3077],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[746])),
               false),
           new attribute(strings[3078], new named_type(IFC4X2_types[969]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[878])
      ->set_attributes(
          {new attribute(strings[3049], new named_type(IFC4X2_types[744]),
                         false),
           new attribute(strings[3098], new named_type(IFC4X2_types[744]),
                         false),
           new attribute(strings[3099], new named_type(IFC4X2_types[538]),
                         true),
           new attribute(strings[3100], new named_type(IFC4X2_types[927]),
                         true),
           new attribute(strings[3101], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[879])
      ->set_attributes(
          {new attribute(strings[3102], new named_type(IFC4X2_types[1067]),
                         false),
           new attribute(
               strings[3103],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[969])),
               false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[880])
      ->set_attributes(
          {new attribute(strings[3081], new named_type(IFC4X2_types[963]),
                         false),
           new attribute(strings[3089], new named_type(IFC4X2_types[372]),
                         false),
           new attribute(strings[3057], new named_type(IFC4X2_types[202]),
                         true),
           new attribute(strings[3104], new named_type(IFC4X2_types[686]),
                         false),
           new attribute(strings[3105], new named_type(IFC4X2_types[520]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[881])
      ->set_attributes({new attribute(strings[3106],
                                      new named_type(IFC4X2_types[881]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[882])
      ->set_attributes({new attribute(strings[3107],
                                      new named_type(IFC4X2_types[882]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[883])
      ->set_attributes(
          {new attribute(strings[3079], new named_type(IFC4X2_types[372]),
                         false),
           new attribute(strings[3108], new named_type(IFC4X2_types[431]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[851])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[884])
      ->set_attributes(
          {new attribute(strings[3109], new named_type(IFC4X2_types[673]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[885])
      ->set_attributes({new attribute(strings[3110],
                                      new named_type(IFC4X2_types[886]), false),
                        new attribute(strings[3111],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3112],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3113],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[887])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[886])
      ->set_attributes({new attribute(strings[3114],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3115],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[887])->set_attributes({}, {});
  ((entity *)IFC4X2_types[888])
      ->set_attributes(
          {new attribute(strings[3116], new named_type(IFC4X2_types[65]),
                         false),
           new attribute(strings[3117], new named_type(IFC4X2_types[885]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[889])
      ->set_attributes(
          {new attribute(strings[2515], new named_type(IFC4X2_types[505]),
                         true),
           new attribute(strings[2466], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[890])
      ->set_attributes({new attribute(strings[2759],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[893])),
                                      false),
                        new attribute(strings[2510],
                                      new named_type(IFC4X2_types[49]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[891])
      ->set_attributes({new attribute(strings[3055],
                                      new named_type(IFC4X2_types[208]), false),
                        new attribute(strings[2759],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[893])),
                                      false)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[892])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false});
  ((entity *)IFC4X2_types[895])
      ->set_attributes(
          {new attribute(strings[3118], new named_type(IFC4X2_types[343]),
                         true),
           new attribute(strings[3119], new named_type(IFC4X2_types[723]),
                         true),
           new attribute(strings[3120], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3121], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3122], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[3123], new named_type(IFC4X2_types[343]),
                         true),
           new attribute(strings[3124], new named_type(IFC4X2_types[84]), true),
           new attribute(strings[3125], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3126], new named_type(IFC4X2_types[343]),
                         true),
           new attribute(strings[3127], new named_type(IFC4X2_types[723]),
                         true),
           new attribute(strings[3128], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3129], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3130], new named_type(IFC4X2_types[343]),
                         true),
           new attribute(strings[3131], new named_type(IFC4X2_types[723]),
                         true),
           new attribute(strings[3132], new named_type(IFC4X2_types[723]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[896])
      ->set_attributes(
          {new attribute(strings[2536], new named_type(IFC4X2_types[64]),
                         false),
           new attribute(strings[3133], new named_type(IFC4X2_types[705]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[897])
      ->set_attributes(
          {new attribute(strings[2761], new named_type(IFC4X2_types[751]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[898])
      ->set_attributes(
          {new attribute(strings[2939], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[3134], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[899])
      ->set_attributes(
          {new attribute(strings[2939], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2480], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[901])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[903]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[902])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[903]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[904])
      ->set_attributes(
          {new attribute(strings[3135], new named_type(IFC4X2_types[487]),
                         false),
           new attribute(strings[3136], new named_type(IFC4X2_types[671]),
                         true),
           new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[909])
      ->set_attributes(
          {new attribute(strings[3137], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[943])
      ->set_attributes(
          {new attribute(strings[3138], new named_type(IFC4X2_types[941]),
                         true),
           new attribute(strings[2495], new named_type(IFC4X2_types[944]),
                         false)},
          {true, false, false, false});
  ((entity *)IFC4X2_types[910])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[912]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[911])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[912]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[913])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3139],
                                      new named_type(IFC4X2_types[277]), true),
                        new attribute(strings[3140],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[914])->set_attributes({}, {false, false, false});
  ((entity *)IFC4X2_types[920])
      ->set_attributes({new attribute(strings[3141],
                                      new named_type(IFC4X2_types[922]), false),
                        new attribute(strings[3142],
                                      new named_type(IFC4X2_types[751]), false),
                        new attribute(strings[3143],
                                      new named_type(IFC4X2_types[751]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[921])
      ->set_attributes({new attribute(strings[3144],
                                      new named_type(IFC4X2_types[545]), false),
                        new attribute(strings[3145],
                                      new named_type(IFC4X2_types[545]), false),
                        new attribute(strings[3146],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[3147],
                                      new named_type(IFC4X2_types[826]), false),
                        new attribute(strings[3148],
                                      new named_type(IFC4X2_types[920]), false),
                        new attribute(strings[3149],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[823])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[916])
      ->set_attributes({new attribute(strings[2783],
                                      new named_type(IFC4X2_types[260]), false),
                        new attribute(strings[3150],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X2_types[751])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X2_types[917])
      ->set_attributes({new attribute(strings[3151],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X2_types[298])),
                                      false),
                        new attribute(strings[3152],
                                      new named_type(IFC4X2_types[84]), false)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[918])
      ->set_attributes({new attribute(strings[3153],
                                      new named_type(IFC4X2_types[188]), false),
                        new attribute(strings[3150],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X2_types[751])),
                                      false),
                        new attribute(strings[3151],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, -1,
                                          new named_type(IFC4X2_types[67])),
                                      false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[924])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[926]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[925])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[926]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[928])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[930]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[929])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[930]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[931])
      ->set_attributes({new attribute(strings[3154],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[932])),
                                      false),
                        new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[3155],
                                      new named_type(IFC4X2_types[574]), false),
                        new attribute(strings[3156],
                                      new named_type(IFC4X2_types[749]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[932])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[933])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[936])
      ->set_attributes({new attribute(strings[3157],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[935])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[937])->set_attributes({}, {false, false});
  ((entity *)IFC4X2_types[938])
      ->set_attributes({new attribute(strings[2619],
                                      new named_type(IFC4X2_types[939]), true),
                        new attribute(strings[3158],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3159],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3160],
                                      new named_type(IFC4X2_types[768]), true),
                        new attribute(strings[3161],
                                      new named_type(IFC4X2_types[1157]), true),
                        new attribute(strings[3162],
                                      new named_type(IFC4X2_types[1157]), true),
                        new attribute(strings[2893],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3163],
                                      new named_type(IFC4X2_types[991]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X2_types[942])
      ->set_attributes({new attribute(strings[3164],
                                      new named_type(IFC4X2_types[192]), true),
                        new attribute(strings[3165],
                                      new named_type(IFC4X2_types[192]), true),
                        new attribute(strings[3166],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[3167],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3168],
                                      new named_type(IFC4X2_types[724]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false});
  ((entity *)IFC4X2_types[946])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[950]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[947])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[948])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[949])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[950]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[951])
      ->set_attributes({new attribute(strings[3169],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[3170],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[3171],
                                      new named_type(IFC4X2_types[545]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[952])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[954]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[953])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[954]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[956])->set_attributes({}, {});
  ((entity *)IFC4X2_types[962])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[968]), true),
                        new attribute(strings[3172],
                                      new named_type(IFC4X2_types[545]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[964])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[966]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[965])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[966]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[967])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[968]), false),
                        new attribute(strings[2588],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[969])
      ->set_attributes(
          {new attribute(strings[2588], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[970])
      ->set_attributes(
          {new attribute(strings[2747], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[971])
      ->set_attributes(
          {new attribute(strings[3173], new named_type(IFC4X2_types[379]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[972])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[973])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[975]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[974])
      ->set_attributes({new attribute(strings[2464],
                                      new named_type(IFC4X2_types[975]), false),
                        new attribute(strings[2588],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[980])
      ->set_attributes(
          {new attribute(strings[2480], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[981])
      ->set_attributes(
          {new attribute(strings[2480], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[982])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[984]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[983])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[984]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[985])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[990]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[986])
      ->set_attributes({new attribute(strings[3174],
                                      new named_type(IFC4X2_types[515]), true),
                        new attribute(strings[3175],
                                      new named_type(IFC4X2_types[515]), true),
                        new attribute(strings[3176],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[3177],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2464],
                                      new named_type(IFC4X2_types[988]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X2_types[987])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[988]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[989])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[990]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[992])
      ->set_attributes({new attribute(strings[3178],
                                      new named_type(IFC4X2_types[84]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[993])
      ->set_attributes(
          {new attribute(strings[3179], new named_type(IFC4X2_types[1007]),
                         false),
           new attribute(strings[3180], new named_type(IFC4X2_types[488]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[995])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[41]),
                         false),
           new attribute(strings[3181], new named_type(IFC4X2_types[67]), true),
           new attribute(
               strings[3182],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[1010])),
               true),
           new attribute(
               strings[3183],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[1026])),
               true),
           new attribute(strings[3184], new named_type(IFC4X2_types[650]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[996])
      ->set_attributes(
          {new attribute(strings[3070], new named_type(IFC4X2_types[89]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[997])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false});
  ((entity *)IFC4X2_types[998])
      ->set_attributes(
          {new attribute(strings[3185], new named_type(IFC4X2_types[756]),
                         true),
           new attribute(strings[2464], new named_type(IFC4X2_types[999]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X2_types[1000])
      ->set_attributes(
          {new attribute(strings[2536], new named_type(IFC4X2_types[293]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1001])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1002]),
                         false),
           new attribute(strings[2536], new named_type(IFC4X2_types[293]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1003])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1004])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[999]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1005])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1006])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false});
  ((entity *)IFC4X2_types[1007])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false});
  ((entity *)IFC4X2_types[1008])
      ->set_attributes({new attribute(strings[3186],
                                      new aggregation_type(
                                          aggregation_type::list_type, 3, 3,
                                          new named_type(IFC4X2_types[808])),
                                      true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false});
  ((entity *)IFC4X2_types[1009])
      ->set_attributes(
          {new attribute(
               strings[2821],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[1012])),
               false),
           new attribute(
               strings[3187],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 1, 2,
                                        new named_type(IFC4X2_types[545]))),
               true)},
          {false, false, false});
  ((entity *)IFC4X2_types[1010])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[572]),
                         false),
           new attribute(strings[3188], new named_type(IFC4X2_types[5]), false),
           new attribute(strings[3189], new named_type(IFC4X2_types[4]), false),
           new attribute(strings[3190], new named_type(IFC4X2_types[808]),
                         true),
           new attribute(strings[2471], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1011])
      ->set_attributes({new attribute(strings[3191],
                                      new named_type(IFC4X2_types[564]), true),
                        new attribute(strings[3192],
                                      new named_type(IFC4X2_types[564]), true),
                        new attribute(strings[3193],
                                      new named_type(IFC4X2_types[564]), true),
                        new attribute(strings[3194],
                                      new named_type(IFC4X2_types[565]), true),
                        new attribute(strings[3195],
                                      new named_type(IFC4X2_types[565]), true),
                        new attribute(strings[3196],
                                      new named_type(IFC4X2_types[565]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1012])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[1013])
      ->set_attributes({new attribute(strings[3197],
                                      new named_type(IFC4X2_types[703]), true),
                        new attribute(strings[3198],
                                      new named_type(IFC4X2_types[703]), true),
                        new attribute(strings[3199],
                                      new named_type(IFC4X2_types[703]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[1014])
      ->set_attributes({new attribute(strings[3200],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[3201],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[3202],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[3203],
                                      new named_type(IFC4X2_types[705]), true),
                        new attribute(strings[3204],
                                      new named_type(IFC4X2_types[705]), true),
                        new attribute(strings[3205],
                                      new named_type(IFC4X2_types[705]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1015])
      ->set_attributes(
          {new attribute(strings[3206], new named_type(IFC4X2_types[259]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1016])
      ->set_attributes(
          {new attribute(strings[3207], new named_type(IFC4X2_types[470]),
                         true),
           new attribute(strings[3208], new named_type(IFC4X2_types[470]),
                         true),
           new attribute(strings[3209], new named_type(IFC4X2_types[470]),
                         true),
           new attribute(strings[3210], new named_type(IFC4X2_types[1132]),
                         true),
           new attribute(strings[3211], new named_type(IFC4X2_types[1132]),
                         true),
           new attribute(strings[3212], new named_type(IFC4X2_types[1132]),
                         true)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1017])
      ->set_attributes(
          {new attribute(strings[3213], new named_type(IFC4X2_types[1196]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1018])->set_attributes({}, {false});
  ((entity *)IFC4X2_types[1019])
      ->set_attributes(
          {new attribute(strings[3214], new named_type(IFC4X2_types[1120]),
                         true),
           new attribute(strings[3215], new named_type(IFC4X2_types[1120]),
                         true),
           new attribute(strings[3216], new named_type(IFC4X2_types[1120]),
                         true)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[1020])
      ->set_attributes({}, {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1021])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false});
  ((entity *)IFC4X2_types[1022])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false});
  ((entity *)IFC4X2_types[1023])
      ->set_attributes(
          {new attribute(strings[3073], new named_type(IFC4X2_types[67]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1024])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1025])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1026])
      ->set_attributes(
          {new attribute(strings[3217], new named_type(IFC4X2_types[42]),
                         false),
           new attribute(strings[3218], new named_type(IFC4X2_types[1010]),
                         true),
           new attribute(strings[3219], new named_type(IFC4X2_types[84]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1027])
      ->set_attributes(
          {new attribute(strings[3185], new named_type(IFC4X2_types[756]),
                         true),
           new attribute(strings[2464], new named_type(IFC4X2_types[1028]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X2_types[1029])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1030])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1031]),
                         false),
           new attribute(strings[2604], new named_type(IFC4X2_types[721]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1032])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1033])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1028]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1037])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[1035])
      ->set_attributes({new attribute(strings[3220],
                                      new named_type(IFC4X2_types[887]), true),
                        new attribute(strings[2965],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[1034])),
                                      false),
                        new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[1036])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[1038])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1040]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1039])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1040]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X2_types[1041])
      ->set_attributes(
          {new attribute(strings[3221], new named_type(IFC4X2_types[345]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[1042])->set_attributes({}, {});
  ((entity *)IFC4X2_types[1043])
      ->set_attributes(
          {new attribute(strings[3222], new named_type(IFC4X2_types[260]),
                         false),
           new attribute(
               strings[3223],
               new aggregation_type(aggregation_type::list_type, 1, 2,
                                    new named_type(IFC4X2_types[675])),
               false),
           new attribute(strings[3224], new named_type(IFC4X2_types[732]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[1044])
      ->set_attributes(
          {new attribute(strings[2783], new named_type(IFC4X2_types[260]),
                         false),
           new attribute(strings[2784], new named_type(IFC4X2_types[673]),
                         true),
           new attribute(strings[2785], new named_type(IFC4X2_types[673]),
                         true),
           new attribute(strings[3225], new named_type(IFC4X2_types[1042]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1045])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1046]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1047])
      ->set_attributes(
          {new attribute(strings[2760], new named_type(IFC4X2_types[293]),
                         false),
           new attribute(strings[2589], new named_type(IFC4X2_types[545]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[1048])
      ->set_attributes({new attribute(strings[3226],
                                      new named_type(IFC4X2_types[64]), false)},
                       {false, false, false});
  ((entity *)IFC4X2_types[1050])
      ->set_attributes({new attribute(strings[3227],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X2_types[545])),
                                      true),
                        new attribute(strings[3228],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X2_types[545])),
                                      true),
                        new attribute(strings[3229],
                                      new named_type(IFC4X2_types[808]), true)},
                       {false, false, false, false});
  ((entity *)IFC4X2_types[1052])
      ->set_attributes(
          {new attribute(strings[3230], new named_type(IFC4X2_types[1051]),
                         false),
           new attribute(
               strings[2965],
               new aggregation_type(aggregation_type::set_type, 1, 5,
                                    new named_type(IFC4X2_types[1053])),
               false)},
          {false, false, false});
  ((entity *)IFC4X2_types[1054])
      ->set_attributes(
          {new attribute(strings[3231], new named_type(IFC4X2_types[174]),
                         false),
           new attribute(strings[3232], new named_type(IFC4X2_types[174]),
                         false),
           new attribute(strings[3233], new named_type(IFC4X2_types[174]),
                         false),
           new attribute(strings[3234], new named_type(IFC4X2_types[174]),
                         false)},
          {false, false, false, false});
  ((entity *)IFC4X2_types[1055])
      ->set_attributes({new attribute(strings[3235],
                                      new named_type(IFC4X2_types[811]), true),
                        new attribute(strings[3236],
                                      new named_type(IFC4X2_types[811]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[1056])
      ->set_attributes(
          {new attribute(strings[3237], new named_type(IFC4X2_types[173]),
                         true),
           new attribute(strings[3233], new named_type(IFC4X2_types[173]),
                         true),
           new attribute(strings[3231], new named_type(IFC4X2_types[173]),
                         true),
           new attribute(strings[3238], new named_type(IFC4X2_types[173]),
                         true),
           new attribute(strings[3239], new named_type(IFC4X2_types[173]),
                         true),
           new attribute(strings[3240], new named_type(IFC4X2_types[978]),
                         true),
           new attribute(strings[3241], new named_type(IFC4X2_types[821]),
                         false)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1057])
      ->set_attributes({new attribute(strings[3242],
                                      new named_type(IFC4X2_types[174]), false),
                        new attribute(strings[3243],
                                      new named_type(IFC4X2_types[643]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[1058])
      ->set_attributes({new attribute(strings[3244],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[1059])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[1059])
      ->set_attributes({new attribute(strings[3245],
                                      new named_type(IFC4X2_types[84]), false),
                        new attribute(strings[3246],
                                      new named_type(IFC4X2_types[84]), false),
                        new attribute(strings[3247],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[3248],
                                      new named_type(IFC4X2_types[146]), true),
                        new attribute(strings[3249],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[505])),
                                      true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[1060])
      ->set_attributes({new attribute(strings[3250],
                                      new named_type(IFC4X2_types[751]), false),
                        new attribute(strings[2626],
                                      new named_type(IFC4X2_types[67]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[1061])
      ->set_attributes({new attribute(strings[2783],
                                      new named_type(IFC4X2_types[260]), false),
                        new attribute(strings[2480],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[3251],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2784],
                                      new named_type(IFC4X2_types[673]), true),
                        new attribute(strings[2785],
                                      new named_type(IFC4X2_types[673]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[1062])
      ->set_attributes({new attribute(strings[2805],
                                      new named_type(IFC4X2_types[721]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1063])
      ->set_attributes({new attribute(strings[3252],
                                      new named_type(IFC4X2_types[751]), false),
                        new attribute(strings[2626],
                                      new named_type(IFC4X2_types[67]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[1064])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1066]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1065])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1066]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1067])
      ->set_attributes({}, {false, false, false, false, false});
  ((entity *)IFC4X2_types[1068])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1070]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1069])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1070]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1149])
      ->set_attributes({new attribute(strings[2589],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[3253],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2526],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2804],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2805],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2806],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[3254],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[3255],
                                      new named_type(IFC4X2_types[705]), true),
                        new attribute(strings[2807],
                                      new named_type(IFC4X2_types[705]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false});
  ((entity *)IFC4X2_types[1071])
      ->set_attributes({new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3256],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[1073])),
                                      true),
                        new attribute(strings[3257],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[1072])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[1072])
      ->set_attributes({new attribute(strings[2504],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[2495],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[2470],
                                      new named_type(IFC4X2_types[1097]), true),
                        new attribute(strings[2685],
                                      new named_type(IFC4X2_types[1157]), true),
                        new attribute(strings[2901],
                                      new named_type(IFC4X2_types[818]), true)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[1073])
      ->set_attributes({new attribute(strings[3258],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[1168])),
                                      true),
                        new attribute(strings[3259],
                                      new named_type(IFC4X2_types[84]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[1074])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1076]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1075])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1076]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1077])
      ->set_attributes(
          {new attribute(strings[2465], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[3260], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[3261], new named_type(IFC4X2_types[84]),
                         false),
           new attribute(strings[2873], new named_type(IFC4X2_types[515]),
                         true),
           new attribute(strings[3262], new named_type(IFC4X2_types[1079]),
                         true),
           new attribute(strings[2464], new named_type(IFC4X2_types[1082]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X2_types[1079])
      ->set_attributes(
          {new attribute(strings[2827], new named_type(IFC4X2_types[1078]),
                         true),
           new attribute(strings[3263], new named_type(IFC4X2_types[343]),
                         true),
           new attribute(strings[3120], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3121], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3264], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3265], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3266], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3267], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3268], new named_type(IFC4X2_types[343]),
                         true),
           new attribute(strings[3269], new named_type(IFC4X2_types[343]),
                         true),
           new attribute(strings[3270], new named_type(IFC4X2_types[84]), true),
           new attribute(strings[3125], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3271], new named_type(IFC4X2_types[343]),
                         true),
           new attribute(strings[3128], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3129], new named_type(IFC4X2_types[279]),
                         true),
           new attribute(strings[3272], new named_type(IFC4X2_types[343]),
                         true),
           new attribute(strings[3132], new named_type(IFC4X2_types[723]),
                         true)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1080])
      ->set_attributes(
          {new attribute(strings[3273], new named_type(IFC4X2_types[816]),
                         false)},
          {false, false, false, false, false, false, false,
           false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1081])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1082]),
                         false),
           new attribute(strings[3260], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1083])
      ->set_attributes(
          {new attribute(
               strings[3274],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[534])),
               true),
           new attribute(
               strings[3275],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[534])),
               true),
           new attribute(strings[3276], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(
               strings[3277],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[534])),
               true),
           new attribute(strings[3278], new named_type(IFC4X2_types[1166]),
                         true),
           new attribute(
               strings[3279],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[1166])),
               true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1086])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1094]),
                         true),
           new attribute(strings[2896], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3029], new named_type(IFC4X2_types[56]), true),
           new attribute(strings[3280], new named_type(IFC4X2_types[470]),
                         true),
           new attribute(strings[3281], new named_type(IFC4X2_types[740]),
                         true),
           new attribute(strings[3282], new named_type(IFC4X2_types[643]),
                         true),
           new attribute(strings[3283], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3284], new named_type(IFC4X2_types[721]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1087])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1089]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1088])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1089]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1090])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1092]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1091])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1092]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1093])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1094]),
                         false),
           new attribute(strings[2896], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3029], new named_type(IFC4X2_types[56]), true),
           new attribute(strings[3285], new named_type(IFC4X2_types[721]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X2_types[1095])
      ->set_attributes(
          {new attribute(strings[2594], new named_type(IFC4X2_types[144]),
                         false)},
          {false});
  ((entity *)IFC4X2_types[1096])->set_attributes({}, {});
  ((entity *)IFC4X2_types[1102])
      ->set_attributes(
          {new attribute(strings[3286], new named_type(IFC4X2_types[733]),
                         false),
           new attribute(strings[2942], new named_type(IFC4X2_types[65]),
                         false),
           new attribute(strings[3287], new named_type(IFC4X2_types[1104]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[1103])
      ->set_attributes({new attribute(strings[3288],
                                      new named_type(IFC4X2_types[702]), false),
                        new attribute(strings[3289],
                                      new named_type(IFC4X2_types[98]), false)},
                       {false, false, false, false, false});
  ((entity *)IFC4X2_types[1105])
      ->set_attributes(
          {new attribute(strings[3290], new named_type(IFC4X2_types[1107]),
                         true),
           new attribute(strings[3291], new named_type(IFC4X2_types[1108]),
                         true),
           new attribute(strings[3292], new named_type(IFC4X2_types[1101]),
                         false),
           new attribute(strings[2676], new named_type(IFC4X2_types[84]),
                         true)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[1106])
      ->set_attributes(
          {new attribute(
               strings[3293],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[1100])),
               false),
           new attribute(strings[3294], new named_type(IFC4X2_types[464]),
                         true),
           new attribute(strings[3295], new named_type(IFC4X2_types[465]),
                         true),
           new attribute(strings[3296], new named_type(IFC4X2_types[466]),
                         true),
           new attribute(strings[3297], new named_type(IFC4X2_types[945]),
                         false)},
          {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1107])
      ->set_attributes({new attribute(strings[3298],
                                      new named_type(IFC4X2_types[172]), false),
                        new attribute(strings[3299],
                                      new named_type(IFC4X2_types[172]), true)},
                       {false, false});
  ((entity *)IFC4X2_types[1108])
      ->set_attributes({new attribute(strings[3300],
                                      new named_type(IFC4X2_types[945]), true),
                        new attribute(strings[3301],
                                      new named_type(IFC4X2_types[1098]), true),
                        new attribute(strings[3302],
                                      new named_type(IFC4X2_types[1099]), true),
                        new attribute(strings[3303],
                                      new named_type(IFC4X2_types[945]), true),
                        new attribute(strings[3304],
                                      new named_type(IFC4X2_types[945]), true),
                        new attribute(strings[3305],
                                      new named_type(IFC4X2_types[1109]), true),
                        new attribute(strings[3306],
                                      new named_type(IFC4X2_types[945]), true)},
                       {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1110])
      ->set_attributes({new attribute(strings[3307],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[1059])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[1111])
      ->set_attributes({new attribute(strings[3247],
                                      new named_type(IFC4X2_types[534]), false),
                        new attribute(strings[3249],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[811])),
                                      true)},
                       {false, false, false});
  ((entity *)IFC4X2_types[1112])
      ->set_attributes(
          {new attribute(
               strings[3308],
               new aggregation_type(aggregation_type::list_type, 3, -1,
                                    new named_type(IFC4X2_types[1113])),
               false),
           new attribute(strings[2809], new named_type(IFC4X2_types[413]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[1113])
      ->set_attributes({new attribute(strings[2594],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 2,
                                          new named_type(IFC4X2_types[673])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[1114])
      ->set_attributes(
          {new attribute(
              strings[3309],
              new aggregation_type(
                  aggregation_type::list_type, 1, -1,
                  new aggregation_type(aggregation_type::list_type, 2, 2,
                                       new named_type(IFC4X2_types[673]))),
              false)},
          {false});
  ((entity *)IFC4X2_types[1124])
      ->set_attributes(
          {new attribute(strings[3310], new named_type(IFC4X2_types[1121]),
                         false),
           new attribute(strings[3311], new named_type(IFC4X2_types[1121]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[1125])
      ->set_attributes(
          {new attribute(strings[2495], new named_type(IFC4X2_types[534]),
                         false),
           new attribute(strings[2470], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[3310], new named_type(IFC4X2_types[279]),
                         false),
           new attribute(strings[3311], new named_type(IFC4X2_types[279]),
                         false),
           new attribute(strings[3312], new named_type(IFC4X2_types[1126]),
                         false),
           new attribute(strings[3139], new named_type(IFC4X2_types[277]),
                         false),
           new attribute(strings[3140], new named_type(IFC4X2_types[534]),
                         true),
           new attribute(strings[2685], new named_type(IFC4X2_types[1157]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1127])
      ->set_attributes({new attribute(strings[2823],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[1168])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[1129])->set_attributes({}, {});
  ((entity *)IFC4X2_types[1130])
      ->set_attributes({}, {false, false, false, false});
  ((entity *)IFC4X2_types[1131])
      ->set_attributes(
          {new attribute(strings[3313], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[3314], new named_type(IFC4X2_types[721]),
                         false)},
          {false, false, false});
  ((entity *)IFC4X2_types[1133])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1135]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1134])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1135]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1137])
      ->set_attributes(
          {new attribute(strings[3315], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3316], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[3317], new named_type(IFC4X2_types[84]),
                         false),
           new attribute(strings[3318], new named_type(IFC4X2_types[84]),
                         false),
           new attribute(strings[3319], new named_type(IFC4X2_types[1138]),
                         false)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1140])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1142]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1141])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1142]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1143])
      ->set_attributes(
          {new attribute(strings[3320], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[3321], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2581], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[3322], new named_type(IFC4X2_types[545]),
                         false)},
          {false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1144])
      ->set_attributes(
          {new attribute(
               strings[3323],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4X2_types[673]))),
               true),
           new attribute(strings[2950], new named_type(IFC4X2_types[84]), true),
           new attribute(
               strings[2814],
               new aggregation_type(
                   aggregation_type::list_type, 1, -1,
                   new aggregation_type(aggregation_type::list_type, 3, 3,
                                        new named_type(IFC4X2_types[720]))),
               false),
           new attribute(
               strings[2952],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[720])),
               true)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[1145])
      ->set_attributes({new attribute(strings[3324],
                                      new aggregation_type(
                                          aggregation_type::list_type, 1, -1,
                                          new named_type(IFC4X2_types[515])),
                                      false)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1146])
      ->set_attributes(
          {new attribute(strings[2909], new named_type(IFC4X2_types[260]),
                         false),
           new attribute(
               strings[3325],
               new aggregation_type(aggregation_type::set_type, 1, 2,
                                    new named_type(IFC4X2_types[1148])),
               false),
           new attribute(
               strings[3326],
               new aggregation_type(aggregation_type::set_type, 1, 2,
                                    new named_type(IFC4X2_types[1148])),
               false),
           new attribute(strings[3327], new named_type(IFC4X2_types[84]),
                         false),
           new attribute(strings[3224], new named_type(IFC4X2_types[1147]),
                         false)},
          {false, false, false, false, false});
  ((entity *)IFC4X2_types[1150])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1152]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1151])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1152]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1153])
      ->set_attributes({new attribute(strings[3328],
                                      new named_type(IFC4X2_types[505]), true),
                        new attribute(strings[3329],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[772])),
                                      true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1154])
      ->set_attributes(
          {new attribute(strings[2515], new named_type(IFC4X2_types[505]),
                         true),
           new attribute(strings[2466], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[3330], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1155])
      ->set_attributes(
          {new attribute(
               strings[3331],
               new aggregation_type(aggregation_type::list_type, 1, -1,
                                    new named_type(IFC4X2_types[888])),
               true),
           new attribute(strings[2488], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1156])
      ->set_attributes(
          {new attribute(strings[2515], new named_type(IFC4X2_types[505]),
                         true),
           new attribute(strings[2466], new named_type(IFC4X2_types[1097]),
                         true),
           new attribute(strings[3332], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1167])
      ->set_attributes({new attribute(strings[2589],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[3253],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2526],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2804],
                                      new named_type(IFC4X2_types[721]), false),
                        new attribute(strings[2805],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2824],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2807],
                                      new named_type(IFC4X2_types[705]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false});
  ((entity *)IFC4X2_types[1164])
      ->set_attributes({new attribute(strings[3333],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[1157])),
                                      false)},
                       {false});
  ((entity *)IFC4X2_types[1158])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1160]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1159])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1160]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1161])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1163]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1162])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1163]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1169])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1171]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1170])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1171]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1173])
      ->set_attributes(
          {new attribute(strings[2765], new named_type(IFC4X2_types[293]),
                         false),
           new attribute(strings[3334], new named_type(IFC4X2_types[545]),
                         false)},
          {false, false});
  ((entity *)IFC4X2_types[1175])->set_attributes({}, {});
  ((entity *)IFC4X2_types[1176])
      ->set_attributes(
          {new attribute(strings[3335], new named_type(IFC4X2_types[1175]),
                         false)},
          {false});
  ((entity *)IFC4X2_types[1177])
      ->set_attributes(
          {new attribute(strings[3336], new named_type(IFC4X2_types[710]),
                         false)},
          {false});
  ((entity *)IFC4X2_types[1178])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1180]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1179])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1180]),
                         true)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1181])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1183]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1182])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1183]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1184])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1185])
      ->set_attributes({new attribute(strings[3337],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 2,
                                          new named_type(IFC4X2_types[490])),
                                      false),
                        new attribute(strings[3338],
                                      new aggregation_type(
                                          aggregation_type::list_type, 2, 3,
                                          new named_type(IFC4X2_types[545])),
                                      false)},
                       {false, false});
  ((entity *)IFC4X2_types[1186])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1187]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1190])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1194]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1191])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1192])
      ->set_attributes(
          {}, {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1193])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1194]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1198])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1200]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1199])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1200]),
                         false)},
          {false, false, false, false, false, false, false, false, false,
           false});
  ((entity *)IFC4X2_types[1201])
      ->set_attributes({new attribute(strings[2716],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2717],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2464],
                                      new named_type(IFC4X2_types[1211]), true),
                        new attribute(strings[3339],
                                      new named_type(IFC4X2_types[1212]), true),
                        new attribute(strings[3340],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X2_types[1202])
      ->set_attributes({new attribute(strings[2720],
                                      new named_type(IFC4X2_types[721]), true),
                        new attribute(strings[2721],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[2724],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[3341],
                                      new named_type(IFC4X2_types[642]), true),
                        new attribute(strings[3342],
                                      new named_type(IFC4X2_types[643]), true),
                        new attribute(strings[3343],
                                      new named_type(IFC4X2_types[643]), true),
                        new attribute(strings[3344],
                                      new named_type(IFC4X2_types[643]), true),
                        new attribute(strings[3345],
                                      new named_type(IFC4X2_types[643]), true),
                        new attribute(strings[2730],
                                      new named_type(IFC4X2_types[931]), true),
                        new attribute(strings[2726],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2731],
                                      new named_type(IFC4X2_types[545]), true),
                        new attribute(strings[2732],
                                      new named_type(IFC4X2_types[545]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false, false, false,
                        false});
  ((entity *)IFC4X2_types[1205])
      ->set_attributes(
          {new attribute(strings[2718], new named_type(IFC4X2_types[1203]),
                         false),
           new attribute(strings[2736], new named_type(IFC4X2_types[1204]),
                         false),
           new attribute(strings[2927], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[2928], new named_type(IFC4X2_types[721]),
                         true),
           new attribute(strings[2730], new named_type(IFC4X2_types[931]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1206])
      ->set_attributes({}, {false, false, false, false, false, false, false,
                            false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1207])
      ->set_attributes(
          {new attribute(strings[2737], new named_type(IFC4X2_types[1208]),
                         false),
           new attribute(strings[2718], new named_type(IFC4X2_types[1209]),
                         false),
           new attribute(strings[2738], new named_type(IFC4X2_types[84]),
                         false),
           new attribute(strings[2739], new named_type(IFC4X2_types[84]),
                         false)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false});
  ((entity *)IFC4X2_types[1210])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1211]),
                         false),
           new attribute(strings[3339], new named_type(IFC4X2_types[1212]),
                         false),
           new attribute(strings[2738], new named_type(IFC4X2_types[84]), true),
           new attribute(strings[3340], new named_type(IFC4X2_types[534]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false});
  ((entity *)IFC4X2_types[1213])
      ->set_attributes(
          {new attribute(
               strings[3346],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[1220])),
               true),
           new attribute(
               strings[3347],
               new aggregation_type(aggregation_type::set_type, 1, -1,
                                    new named_type(IFC4X2_types[1220])),
               true),
           new attribute(strings[2464], new named_type(IFC4X2_types[1214]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1215])
      ->set_attributes({new attribute(strings[2924],
                                      new named_type(IFC4X2_types[279]), false),
                        new attribute(strings[3348],
                                      new aggregation_type(
                                          aggregation_type::set_type, 1, -1,
                                          new named_type(IFC4X2_types[682])),
                                      true),
                        new attribute(strings[2471],
                                      new named_type(IFC4X2_types[534]), true),
                        new attribute(strings[3349],
                                      new named_type(IFC4X2_types[343]), true),
                        new attribute(strings[3269],
                                      new named_type(IFC4X2_types[343]), true),
                        new attribute(strings[3310],
                                      new named_type(IFC4X2_types[279]), false),
                        new attribute(strings[3350],
                                      new named_type(IFC4X2_types[279]), true)},
                       {false, false, false, false, false, false, false, false,
                        false, false, false, false, false});
  ((entity *)IFC4X2_types[1216])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1217]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X2_types[1218])
      ->set_attributes(
          {new attribute(strings[2464], new named_type(IFC4X2_types[1219]),
                         true)},
          {false, false, false, false, false, false, false, false, false, false,
           false, false, false, false});
  ((entity *)IFC4X2_types[1220])
      ->set_attributes({new attribute(strings[3351],
                                      new named_type(IFC4X2_types[816]), true),
                        new attribute(strings[3352],
                                      new named_type(IFC4X2_types[278]), true),
                        new attribute(strings[3353],
                                      new named_type(IFC4X2_types[278]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1222])
      ->set_attributes(
          {new attribute(strings[2589], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[3253], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2526], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2804], new named_type(IFC4X2_types[721]),
                         false),
           new attribute(strings[2805], new named_type(IFC4X2_types[642]),
                         true),
           new attribute(strings[2824], new named_type(IFC4X2_types[642]),
                         true)},
          {false, false, false, false, false, false, false, false, false});
  ((entity *)IFC4X2_types[1221])
      ->set_attributes({new attribute(strings[2588],
                                      new named_type(IFC4X2_types[534]), true)},
                       {false, false, false, false, false, false});
  ((entity *)IFC4X2_types[6])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3354], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[837]),
          ((entity *)IFC4X2_types[837])->attributes()[0])});
  ((entity *)IFC4X2_types[7])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3355], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[407]),
          ((entity *)IFC4X2_types[407])->attributes()[1])});
  ((entity *)IFC4X2_types[12])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3356], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[682]),
               ((entity *)IFC4X2_types[682])->attributes()[7]),
           new inverse_attribute(
               strings[3357], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[663]),
               ((entity *)IFC4X2_types[663])->attributes()[4])});
  ((entity *)IFC4X2_types[30])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3358], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X2_types[38]),
          ((entity *)IFC4X2_types[38])->attributes()[0])});
  ((entity *)IFC4X2_types[31])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3359], inverse_attribute::set_type, 1, 1,
          ((entity *)IFC4X2_types[30]),
          ((entity *)IFC4X2_types[30])->attributes()[1])});
  ((entity *)IFC4X2_types[36])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3358], inverse_attribute::set_type, 1, 1,
          ((entity *)IFC4X2_types[38]),
          ((entity *)IFC4X2_types[38])->attributes()[1])});
  ((entity *)IFC4X2_types[37])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3360], inverse_attribute::set_type, 1, 1,
          ((entity *)IFC4X2_types[36]),
          ((entity *)IFC4X2_types[36])->attributes()[0])});
  ((entity *)IFC4X2_types[44])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3361], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X2_types[861]),
          ((entity *)IFC4X2_types[861])->attributes()[0])});
  ((entity *)IFC4X2_types[47])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3355], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[407]),
          ((entity *)IFC4X2_types[407])->attributes()[1])});
  ((entity *)IFC4X2_types[49])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3362], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[407]),
               ((entity *)IFC4X2_types[407])->attributes()[1]),
           new inverse_attribute(
               strings[3363], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[845]),
               ((entity *)IFC4X2_types[845])->attributes()[0]),
           new inverse_attribute(
               strings[3364], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[890]),
               ((entity *)IFC4X2_types[890])->attributes()[1]),
           new inverse_attribute(strings[3365], inverse_attribute::set_type, 0,
                                 -1, ((entity *)IFC4X2_types[50]),
                                 ((entity *)IFC4X2_types[50])->attributes()[1]),
           new inverse_attribute(
               strings[3366], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[50]),
               ((entity *)IFC4X2_types[50])->attributes()[0])});
  ((entity *)IFC4X2_types[95])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3367], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X2_types[567]),
          ((entity *)IFC4X2_types[567])->attributes()[0])});
  ((entity *)IFC4X2_types[164])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3368], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[846]),
               ((entity *)IFC4X2_types[846])->attributes()[0]),
           new inverse_attribute(
               strings[3369], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[165]),
               ((entity *)IFC4X2_types[165])->attributes()[0])});
  ((entity *)IFC4X2_types[165])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3370], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[846]),
               ((entity *)IFC4X2_types[846])->attributes()[0]),
           new inverse_attribute(
               strings[3369], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[165]),
               ((entity *)IFC4X2_types[165])->attributes()[0])});
  ((entity *)IFC4X2_types[190])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3371], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X2_types[188]),
          ((entity *)IFC4X2_types[188])->attributes()[0])});
  ((entity *)IFC4X2_types[208])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3362], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[407]),
               ((entity *)IFC4X2_types[407])->attributes()[1]),
           new inverse_attribute(
               strings[3372], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[891]),
               ((entity *)IFC4X2_types[891])->attributes()[0])});
  ((entity *)IFC4X2_types[221])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3373], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[868]),
               ((entity *)IFC4X2_types[868])->attributes()[0]),
           new inverse_attribute(
               strings[3374], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[864]),
               ((entity *)IFC4X2_types[864])->attributes()[0])});
  ((entity *)IFC4X2_types[223])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3355], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[407]),
          ((entity *)IFC4X2_types[407])->attributes()[1])});
  ((entity *)IFC4X2_types[224])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3375], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[838]),
          ((entity *)IFC4X2_types[838])->attributes()[0])});
  ((entity *)IFC4X2_types[228])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3355], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[407]),
          ((entity *)IFC4X2_types[407])->attributes()[1])});
  ((entity *)IFC4X2_types[237])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3376], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X2_types[236]),
          ((entity *)IFC4X2_types[236])->attributes()[0])});
  ((entity *)IFC4X2_types[245])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3377], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[863]),
               ((entity *)IFC4X2_types[863])->attributes()[1]),
           new inverse_attribute(
               strings[3378], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[862]),
               ((entity *)IFC4X2_types[862])->attributes()[1])});
  ((entity *)IFC4X2_types[303])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3379], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X2_types[872]),
          ((entity *)IFC4X2_types[872])->attributes()[0])});
  ((entity *)IFC4X2_types[305])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3380], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[856]),
          ((entity *)IFC4X2_types[856])->attributes()[1])});
  ((entity *)IFC4X2_types[307])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3381], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X2_types[872]),
          ((entity *)IFC4X2_types[872])->attributes()[1])});
  ((entity *)IFC4X2_types[314])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3382], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[848]),
               ((entity *)IFC4X2_types[848])->attributes()[0]),
           new inverse_attribute(
               strings[3383], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[316]),
               ((entity *)IFC4X2_types[316])->attributes()[1]),
           new inverse_attribute(
               strings[3384], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[315]),
               ((entity *)IFC4X2_types[315])->attributes()[1]),
           new inverse_attribute(
               strings[3385], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[315]),
               ((entity *)IFC4X2_types[315])->attributes()[0])});
  ((entity *)IFC4X2_types[316])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3386], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[848]),
          ((entity *)IFC4X2_types[848])->attributes()[0])});
  ((entity *)IFC4X2_types[372])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3387], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[871]),
               ((entity *)IFC4X2_types[871])->attributes()[1]),
           new inverse_attribute(
               strings[3388], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[853]),
               ((entity *)IFC4X2_types[853])->attributes()[1]),
           new inverse_attribute(
               strings[3389], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[873]),
               ((entity *)IFC4X2_types[873])->attributes()[1]),
           new inverse_attribute(
               strings[3390], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[873]),
               ((entity *)IFC4X2_types[873])->attributes()[0]),
           new inverse_attribute(
               strings[3391], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[876]),
               ((entity *)IFC4X2_types[876])->attributes()[0]),
           new inverse_attribute(
               strings[3392], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[877]),
               ((entity *)IFC4X2_types[877])->attributes()[0]),
           new inverse_attribute(
               strings[3393], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[883]),
               ((entity *)IFC4X2_types[883])->attributes()[0]),
           new inverse_attribute(
               strings[3394], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[860]),
               ((entity *)IFC4X2_types[860])->attributes()[0]),
           new inverse_attribute(
               strings[3395], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[880]),
               ((entity *)IFC4X2_types[880])->attributes()[1]),
           new inverse_attribute(
               strings[3396], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[853]),
               ((entity *)IFC4X2_types[853])->attributes()[2]),
           new inverse_attribute(
               strings[3361], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[861]),
               ((entity *)IFC4X2_types[861])->attributes()[0]),
           new inverse_attribute(
               strings[3397], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[862]),
               ((entity *)IFC4X2_types[862])->attributes()[0])});
  ((entity *)IFC4X2_types[406])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3398], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[407]),
          ((entity *)IFC4X2_types[407])->attributes()[0])});
  ((entity *)IFC4X2_types[408])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3399], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[880]),
          ((entity *)IFC4X2_types[880])->attributes()[0])});
  ((entity *)IFC4X2_types[413])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3400], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[1112]),
          ((entity *)IFC4X2_types[1112])->attributes()[1])});
  ((entity *)IFC4X2_types[430])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3401], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X2_types[876]),
          ((entity *)IFC4X2_types[876])->attributes()[1])});
  ((entity *)IFC4X2_types[431])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3402], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X2_types[883]),
          ((entity *)IFC4X2_types[883])->attributes()[1])});
  ((entity *)IFC4X2_types[482])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3403], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[484]),
               ((entity *)IFC4X2_types[484])->attributes()[0]),
           new inverse_attribute(
               strings[3376], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[236]),
               ((entity *)IFC4X2_types[236])->attributes()[0])});
  ((entity *)IFC4X2_types[490])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3404], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[489]),
               ((entity *)IFC4X2_types[489])->attributes()[2]),
           new inverse_attribute(
               strings[3405], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[489]),
               ((entity *)IFC4X2_types[489])->attributes()[1]),
           new inverse_attribute(
               strings[3406], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[489]),
               ((entity *)IFC4X2_types[489])->attributes()[0]),
           new inverse_attribute(
               strings[3407], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[1185]),
               ((entity *)IFC4X2_types[1185])->attributes()[0])});
  ((entity *)IFC4X2_types[494])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3408], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[839]),
          ((entity *)IFC4X2_types[839])->attributes()[0])});
  ((entity *)IFC4X2_types[510])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3409], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X2_types[715]),
          ((entity *)IFC4X2_types[715])->attributes()[1])});
  ((entity *)IFC4X2_types[546])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3410], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[849]),
               ((entity *)IFC4X2_types[849])->attributes()[0]),
           new inverse_attribute(
               strings[3411], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[547]),
               ((entity *)IFC4X2_types[547])->attributes()[2])});
  ((entity *)IFC4X2_types[547])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3412], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[849]),
          ((entity *)IFC4X2_types[849])->attributes()[0])});
  ((entity *)IFC4X2_types[590])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3413], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[595]),
               ((entity *)IFC4X2_types[595])->attributes()[0]),
           new inverse_attribute(
               strings[3365], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[607]),
               ((entity *)IFC4X2_types[607])->attributes()[1]),
           new inverse_attribute(
               strings[3414], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[607]),
               ((entity *)IFC4X2_types[607])->attributes()[0])});
  ((entity *)IFC4X2_types[592])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3415], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X2_types[593]),
          ((entity *)IFC4X2_types[593])->attributes()[2])});
  ((entity *)IFC4X2_types[594])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3416], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[850]),
               ((entity *)IFC4X2_types[850])->attributes()[0]),
           new inverse_attribute(
               strings[3362], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[407]),
               ((entity *)IFC4X2_types[407])->attributes()[1]),
           new inverse_attribute(
               strings[2618], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[606]),
               ((entity *)IFC4X2_types[606])->attributes()[0])});
  ((entity *)IFC4X2_types[596])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3417], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X2_types[597]),
          ((entity *)IFC4X2_types[597])->attributes()[0])});
  ((entity *)IFC4X2_types[601])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3418], inverse_attribute::unspecified_type, -1, -1,
          ((entity *)IFC4X2_types[602]),
          ((entity *)IFC4X2_types[602])->attributes()[2])});
  ((entity *)IFC4X2_types[609])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3416], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X2_types[850]),
          ((entity *)IFC4X2_types[850])->attributes()[0])});
  ((entity *)IFC4X2_types[646])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3419], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[867]),
               ((entity *)IFC4X2_types[867])->attributes()[0]),
           new inverse_attribute(
               strings[3374], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[867]),
               ((entity *)IFC4X2_types[867])->attributes()[1]),
           new inverse_attribute(
               strings[3420], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[870]),
               ((entity *)IFC4X2_types[870])->attributes()[0]),
           new inverse_attribute(
               strings[3373], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[868]),
               ((entity *)IFC4X2_types[868])->attributes()[0])});
  ((entity *)IFC4X2_types[647])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3421], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[836]),
               ((entity *)IFC4X2_types[836])->attributes()[0]),
           new inverse_attribute(
               strings[3422], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[874]),
               ((entity *)IFC4X2_types[874])->attributes()[1]),
           new inverse_attribute(
               strings[3423], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[874]),
               ((entity *)IFC4X2_types[874])->attributes()[0]),
           new inverse_attribute(
               strings[3424], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[864]),
               ((entity *)IFC4X2_types[864])->attributes()[1]),
           new inverse_attribute(
               strings[3425], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[835]),
               ((entity *)IFC4X2_types[835])->attributes()[0]),
           new inverse_attribute(
               strings[3426], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[835]),
               ((entity *)IFC4X2_types[835])->attributes()[1]),
           new inverse_attribute(
               strings[3427], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[844]),
               ((entity *)IFC4X2_types[844])->attributes()[0])});
  ((entity *)IFC4X2_types[650])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3428], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[746]),
          ((entity *)IFC4X2_types[746])->attributes()[0])});
  ((entity *)IFC4X2_types[659])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3429], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[871]),
          ((entity *)IFC4X2_types[871])->attributes()[0])});
  ((entity *)IFC4X2_types[663])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3430], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[664]),
               ((entity *)IFC4X2_types[664])->attributes()[1]),
           new inverse_attribute(
               strings[3366], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[664]),
               ((entity *)IFC4X2_types[664])->attributes()[0]),
           new inverse_attribute(
               strings[3431], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[683]),
               ((entity *)IFC4X2_types[683])->attributes()[1])});
  ((entity *)IFC4X2_types[682])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3432], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[683]),
          ((entity *)IFC4X2_types[683])->attributes()[0])});
  ((entity *)IFC4X2_types[687])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3362], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[407]),
               ((entity *)IFC4X2_types[407])->attributes()[1]),
           new inverse_attribute(
               strings[3433], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[685]),
               ((entity *)IFC4X2_types[685])->attributes()[0])});
  ((entity *)IFC4X2_types[718])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3434], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[856]),
               ((entity *)IFC4X2_types[856])->attributes()[0]),
           new inverse_attribute(
               strings[3396], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[855]),
               ((entity *)IFC4X2_types[855])->attributes()[1]),
           new inverse_attribute(
               strings[3388], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[855]),
               ((entity *)IFC4X2_types[855])->attributes()[0])});
  ((entity *)IFC4X2_types[719])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3361], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[861]),
               ((entity *)IFC4X2_types[861])->attributes()[0]),
           new inverse_attribute(
               strings[3435], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[875]),
               ((entity *)IFC4X2_types[875])->attributes()[0])});
  ((entity *)IFC4X2_types[744])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3436], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[878]),
               ((entity *)IFC4X2_types[878])->attributes()[0]),
           new inverse_attribute(
               strings[3437], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[878]),
               ((entity *)IFC4X2_types[878])->attributes()[1]),
           new inverse_attribute(
               strings[3438], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[841]),
               ((entity *)IFC4X2_types[841])->attributes()[0])});
  ((entity *)IFC4X2_types[746])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3439], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[842]),
               ((entity *)IFC4X2_types[842])->attributes()[0]),
           new inverse_attribute(
               strings[3440], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[875]),
               ((entity *)IFC4X2_types[875])->attributes()[1])});
  ((entity *)IFC4X2_types[747])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3441], inverse_attribute::set_type, 1, -1,
               ((entity *)IFC4X2_types[746]),
               ((entity *)IFC4X2_types[746])->attributes()[1]),
           new inverse_attribute(
               strings[3442], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[931]),
               ((entity *)IFC4X2_types[931])->attributes()[4])});
  ((entity *)IFC4X2_types[751])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3355], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[407]),
               ((entity *)IFC4X2_types[407])->attributes()[1]),
           new inverse_attribute(
               strings[2618], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[752]),
               ((entity *)IFC4X2_types[752])->attributes()[0])});
  ((entity *)IFC4X2_types[762])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3443], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[771]),
               ((entity *)IFC4X2_types[771])->attributes()[0]),
           new inverse_attribute(
               strings[3444], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[766]),
               ((entity *)IFC4X2_types[766])->attributes()[0]),
           new inverse_attribute(
               strings[3445], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[766]),
               ((entity *)IFC4X2_types[766])->attributes()[1]),
           new inverse_attribute(
               strings[3433], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[185]),
               ((entity *)IFC4X2_types[185])->attributes()[1]),
           new inverse_attribute(
               strings[3446], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[891]),
               ((entity *)IFC4X2_types[891])->attributes()[1]),
           new inverse_attribute(
               strings[3447], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[890]),
               ((entity *)IFC4X2_types[890])->attributes()[0])});
  ((entity *)IFC4X2_types[763])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3362], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[407]),
          ((entity *)IFC4X2_types[407])->attributes()[1])});
  ((entity *)IFC4X2_types[765])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3424], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[864]),
               ((entity *)IFC4X2_types[864])->attributes()[1]),
           new inverse_attribute(
               strings[3427], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[844]),
               ((entity *)IFC4X2_types[844])->attributes()[0])});
  ((entity *)IFC4X2_types[772])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3448], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[1153]),
               ((entity *)IFC4X2_types[1153])->attributes()[1]),
           new inverse_attribute(
               strings[3373], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[869]),
               ((entity *)IFC4X2_types[869])->attributes()[0]),
           new inverse_attribute(
               strings[3449], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[868]),
               ((entity *)IFC4X2_types[868])->attributes()[1])});
  ((entity *)IFC4X2_types[775])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3450], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[869]),
          ((entity *)IFC4X2_types[869])->attributes()[1])});
  ((entity *)IFC4X2_types[779])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3451], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[186]),
               ((entity *)IFC4X2_types[186])->attributes()[2]),
           new inverse_attribute(
               strings[3452], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[775]),
               ((entity *)IFC4X2_types[775])->attributes()[2])});
  ((entity *)IFC4X2_types[881])
      ->set_inverse_attributes({new inverse_attribute(
          strings[2490], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[881]),
          ((entity *)IFC4X2_types[881])->attributes()[0])});
  ((entity *)IFC4X2_types[882])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3453], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X2_types[882]),
          ((entity *)IFC4X2_types[882])->attributes()[0])});
  ((entity *)IFC4X2_types[885])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3454], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[888]),
               ((entity *)IFC4X2_types[888])->attributes()[1]),
           new inverse_attribute(
               strings[3455], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[735]),
               ((entity *)IFC4X2_types[735])->attributes()[2]),
           new inverse_attribute(
               strings[3456], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[748]),
               ((entity *)IFC4X2_types[748])->attributes()[2])});
  ((entity *)IFC4X2_types[886])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3457], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[885]),
          ((entity *)IFC4X2_types[885])->attributes()[0])});
  ((entity *)IFC4X2_types[887])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3458], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[735]),
               ((entity *)IFC4X2_types[735])->attributes()[2]),
           new inverse_attribute(
               strings[3459], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[1035]),
               ((entity *)IFC4X2_types[1035])->attributes()[0])});
  ((entity *)IFC4X2_types[888])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3442], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[931]),
               ((entity *)IFC4X2_types[931])->attributes()[4]),
           new inverse_attribute(
               strings[3460], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[585]),
               ((entity *)IFC4X2_types[585])->attributes()[0])});
  ((entity *)IFC4X2_types[889])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3461], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[843]),
          ((entity *)IFC4X2_types[843])->attributes()[0])});
  ((entity *)IFC4X2_types[931])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3362], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[407]),
          ((entity *)IFC4X2_types[407])->attributes()[1])});
  ((entity *)IFC4X2_types[932])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3462], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X2_types[931]),
          ((entity *)IFC4X2_types[931])->attributes()[0])});
  ((entity *)IFC4X2_types[962])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3397], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[863]),
               ((entity *)IFC4X2_types[863])->attributes()[0]),
           new inverse_attribute(
               strings[3399], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[880]),
               ((entity *)IFC4X2_types[880])->attributes()[0])});
  ((entity *)IFC4X2_types[969])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3463], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[861]),
               ((entity *)IFC4X2_types[861])->attributes()[1]),
           new inverse_attribute(
               strings[3464], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[879]),
               ((entity *)IFC4X2_types[879])->attributes()[1]),
           new inverse_attribute(
               strings[3465], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[877]),
               ((entity *)IFC4X2_types[877])->attributes()[1])});
  ((entity *)IFC4X2_types[993])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3466], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X2_types[857]),
          ((entity *)IFC4X2_types[857])->attributes()[1])});
  ((entity *)IFC4X2_types[996])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3467], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X2_types[858]),
          ((entity *)IFC4X2_types[858])->attributes()[1])});
  ((entity *)IFC4X2_types[1005])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3468], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[857]),
          ((entity *)IFC4X2_types[857])->attributes()[0])});
  ((entity *)IFC4X2_types[1010])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3469], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[1026]),
               ((entity *)IFC4X2_types[1026])->attributes()[1]),
           new inverse_attribute(
               strings[3470], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[995]),
               ((entity *)IFC4X2_types[995])->attributes()[2])});
  ((entity *)IFC4X2_types[1020])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3471], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[858]),
          ((entity *)IFC4X2_types[858])->attributes()[0])});
  ((entity *)IFC4X2_types[1026])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3472], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X2_types[995]),
          ((entity *)IFC4X2_types[995])->attributes()[3])});
  ((entity *)IFC4X2_types[1059])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3473], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[1110]),
               ((entity *)IFC4X2_types[1110])->attributes()[0]),
           new inverse_attribute(
               strings[3474], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[1058]),
               ((entity *)IFC4X2_types[1058])->attributes()[0])});
  ((entity *)IFC4X2_types[1067])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3475], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X2_types[879]),
          ((entity *)IFC4X2_types[879])->attributes()[0])});
  ((entity *)IFC4X2_types[1095])
      ->set_inverse_attributes(
          {new inverse_attribute(
               strings[3476], inverse_attribute::set_type, 0, 1,
               ((entity *)IFC4X2_types[508]),
               ((entity *)IFC4X2_types[508])->attributes()[0]),
           new inverse_attribute(
               strings[3477], inverse_attribute::set_type, 0, -1,
               ((entity *)IFC4X2_types[512]),
               ((entity *)IFC4X2_types[512])->attributes()[0])});
  ((entity *)IFC4X2_types[1125])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3355], inverse_attribute::set_type, 1, -1,
          ((entity *)IFC4X2_types[407]),
          ((entity *)IFC4X2_types[407])->attributes()[1])});
  ((entity *)IFC4X2_types[1153])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3478], inverse_attribute::set_type, 0, 1,
          ((entity *)IFC4X2_types[870]),
          ((entity *)IFC4X2_types[870])->attributes()[1])});
  ((entity *)IFC4X2_types[1154])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3438], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[841]),
          ((entity *)IFC4X2_types[841])->attributes()[0])});
  ((entity *)IFC4X2_types[1155])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3439], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[842]),
          ((entity *)IFC4X2_types[842])->attributes()[0])});
  ((entity *)IFC4X2_types[1156])
      ->set_inverse_attributes({new inverse_attribute(
          strings[3461], inverse_attribute::set_type, 0, -1,
          ((entity *)IFC4X2_types[843]),
          ((entity *)IFC4X2_types[843])->attributes()[0])});
  ((entity *)IFC4X2_types[224])
      ->set_subtypes(
          {((entity *)IFC4X2_types[2]), ((entity *)IFC4X2_types[239]),
           ((entity *)IFC4X2_types[241]), ((entity *)IFC4X2_types[676]),
           ((entity *)IFC4X2_types[680]), ((entity *)IFC4X2_types[760]),
           ((entity *)IFC4X2_types[1213]), ((entity *)IFC4X2_types[1215])});
  ((entity *)IFC4X2_types[646])
      ->set_subtypes(
          {((entity *)IFC4X2_types[6]), ((entity *)IFC4X2_types[224]),
           ((entity *)IFC4X2_types[494]), ((entity *)IFC4X2_types[744]),
           ((entity *)IFC4X2_types[746]), ((entity *)IFC4X2_types[889])});
  ((entity *)IFC4X2_types[303])
      ->set_subtypes(
          {((entity *)IFC4X2_types[9]), ((entity *)IFC4X2_types[26]),
           ((entity *)IFC4X2_types[225]), ((entity *)IFC4X2_types[448]),
           ((entity *)IFC4X2_types[782]), ((entity *)IFC4X2_types[924]),
           ((entity *)IFC4X2_types[1158])});
  ((entity *)IFC4X2_types[304])
      ->set_subtypes(
          {((entity *)IFC4X2_types[10]), ((entity *)IFC4X2_types[27]),
           ((entity *)IFC4X2_types[226]), ((entity *)IFC4X2_types[449]),
           ((entity *)IFC4X2_types[783]), ((entity *)IFC4X2_types[925]),
           ((entity *)IFC4X2_types[1159])});
  ((entity *)IFC4X2_types[583])
      ->set_subtypes(
          {((entity *)IFC4X2_types[14]), ((entity *)IFC4X2_types[418])});
  ((entity *)IFC4X2_types[14])->set_subtypes({((entity *)IFC4X2_types[15])});
  ((entity *)IFC4X2_types[417])->set_subtypes({((entity *)IFC4X2_types[16])});
  ((entity *)IFC4X2_types[460])
      ->set_subtypes(
          {((entity *)IFC4X2_types[17]), ((entity *)IFC4X2_types[61]),
           ((entity *)IFC4X2_types[181]), ((entity *)IFC4X2_types[348]),
           ((entity *)IFC4X2_types[439]), ((entity *)IFC4X2_types[539]),
           ((entity *)IFC4X2_types[553]), ((entity *)IFC4X2_types[615]),
           ((entity *)IFC4X2_types[668]), ((entity *)IFC4X2_types[910]),
           ((entity *)IFC4X2_types[964]), ((entity *)IFC4X2_types[982]),
           ((entity *)IFC4X2_types[1198])});
  ((entity *)IFC4X2_types[443])
      ->set_subtypes(
          {((entity *)IFC4X2_types[18]), ((entity *)IFC4X2_types[274]),
           ((entity *)IFC4X2_types[355]), ((entity *)IFC4X2_types[368]),
           ((entity *)IFC4X2_types[451]), ((entity *)IFC4X2_types[781]),
           ((entity *)IFC4X2_types[1064]), ((entity *)IFC4X2_types[1169])});
  ((entity *)IFC4X2_types[444])
      ->set_subtypes(
          {((entity *)IFC4X2_types[19]), ((entity *)IFC4X2_types[275]),
           ((entity *)IFC4X2_types[356]), ((entity *)IFC4X2_types[369]),
           ((entity *)IFC4X2_types[452]), ((entity *)IFC4X2_types[785]),
           ((entity *)IFC4X2_types[1065]), ((entity *)IFC4X2_types[1170])});
  ((entity *)IFC4X2_types[461])
      ->set_subtypes(
          {((entity *)IFC4X2_types[21]), ((entity *)IFC4X2_types[62]),
           ((entity *)IFC4X2_types[182]), ((entity *)IFC4X2_types[349]),
           ((entity *)IFC4X2_types[440]), ((entity *)IFC4X2_types[540]),
           ((entity *)IFC4X2_types[554]), ((entity *)IFC4X2_types[616]),
           ((entity *)IFC4X2_types[669]), ((entity *)IFC4X2_types[911]),
           ((entity *)IFC4X2_types[965]), ((entity *)IFC4X2_types[983]),
           ((entity *)IFC4X2_types[1199])});
  ((entity *)IFC4X2_types[384])
      ->set_subtypes(
          {((entity *)IFC4X2_types[23]),   ((entity *)IFC4X2_types[81]),
           ((entity *)IFC4X2_types[122]),  ((entity *)IFC4X2_types[152]),
           ((entity *)IFC4X2_types[169]),  ((entity *)IFC4X2_types[196]),
           ((entity *)IFC4X2_types[230]),  ((entity *)IFC4X2_types[233]),
           ((entity *)IFC4X2_types[361]),  ((entity *)IFC4X2_types[364]),
           ((entity *)IFC4X2_types[387]),  ((entity *)IFC4X2_types[390]),
           ((entity *)IFC4X2_types[393]),  ((entity *)IFC4X2_types[497]),
           ((entity *)IFC4X2_types[502]),  ((entity *)IFC4X2_types[638]),
           ((entity *)IFC4X2_types[952]),  ((entity *)IFC4X2_types[1133]),
           ((entity *)IFC4X2_types[1150]), ((entity *)IFC4X2_types[1161])});
  ((entity *)IFC4X2_types[385])
      ->set_subtypes(
          {((entity *)IFC4X2_types[24]),   ((entity *)IFC4X2_types[82]),
           ((entity *)IFC4X2_types[123]),  ((entity *)IFC4X2_types[153]),
           ((entity *)IFC4X2_types[170]),  ((entity *)IFC4X2_types[197]),
           ((entity *)IFC4X2_types[231]),  ((entity *)IFC4X2_types[234]),
           ((entity *)IFC4X2_types[362]),  ((entity *)IFC4X2_types[365]),
           ((entity *)IFC4X2_types[388]),  ((entity *)IFC4X2_types[391]),
           ((entity *)IFC4X2_types[394]),  ((entity *)IFC4X2_types[498]),
           ((entity *)IFC4X2_types[503]),  ((entity *)IFC4X2_types[639]),
           ((entity *)IFC4X2_types[953]),  ((entity *)IFC4X2_types[1134]),
           ((entity *)IFC4X2_types[1151]), ((entity *)IFC4X2_types[1162])});
  ((entity *)IFC4X2_types[567])->set_subtypes({((entity *)IFC4X2_types[29])});
  ((entity *)IFC4X2_types[483])
      ->set_subtypes(
          {((entity *)IFC4X2_types[30]),   ((entity *)IFC4X2_types[32]),
           ((entity *)IFC4X2_types[36]),   ((entity *)IFC4X2_types[45]),
           ((entity *)IFC4X2_types[88]),   ((entity *)IFC4X2_types[97]),
           ((entity *)IFC4X2_types[142]),  ((entity *)IFC4X2_types[145]),
           ((entity *)IFC4X2_types[190]),  ((entity *)IFC4X2_types[251]),
           ((entity *)IFC4X2_types[260]),  ((entity *)IFC4X2_types[293]),
           ((entity *)IFC4X2_types[298]),  ((entity *)IFC4X2_types[414]),
           ((entity *)IFC4X2_types[433]),  ((entity *)IFC4X2_types[434]),
           ((entity *)IFC4X2_types[485]),  ((entity *)IFC4X2_types[495]),
           ((entity *)IFC4X2_types[557]),  ((entity *)IFC4X2_types[665]),
           ((entity *)IFC4X2_types[700]),  ((entity *)IFC4X2_types[702]),
           ((entity *)IFC4X2_types[710]),  ((entity *)IFC4X2_types[918]),
           ((entity *)IFC4X2_types[936]),  ((entity *)IFC4X2_types[956]),
           ((entity *)IFC4X2_types[1042]), ((entity *)IFC4X2_types[1096]),
           ((entity *)IFC4X2_types[1102]), ((entity *)IFC4X2_types[1173])});
  ((entity *)IFC4X2_types[32])
      ->set_subtypes(
          {((entity *)IFC4X2_types[31]), ((entity *)IFC4X2_types[37])});
  ((entity *)IFC4X2_types[37])
      ->set_subtypes({((entity *)IFC4X2_types[33]),
                      ((entity *)IFC4X2_types[34]),
                      ((entity *)IFC4X2_types[35])});
  ((entity *)IFC4X2_types[95])
      ->set_subtypes(
          {((entity *)IFC4X2_types[38]), ((entity *)IFC4X2_types[104]),
           ((entity *)IFC4X2_types[188]), ((entity *)IFC4X2_types[267]),
           ((entity *)IFC4X2_types[509]), ((entity *)IFC4X2_types[716]),
           ((entity *)IFC4X2_types[1146])});
  ((entity *)IFC4X2_types[746])
      ->set_subtypes(
          {((entity *)IFC4X2_types[44]), ((entity *)IFC4X2_types[372]),
           ((entity *)IFC4X2_types[718]), ((entity *)IFC4X2_types[719]),
           ((entity *)IFC4X2_types[787]), ((entity *)IFC4X2_types[969]),
           ((entity *)IFC4X2_types[993]), ((entity *)IFC4X2_types[1005])});
  ((entity *)IFC4X2_types[892])
      ->set_subtypes(
          {((entity *)IFC4X2_types[50]), ((entity *)IFC4X2_types[255]),
           ((entity *)IFC4X2_types[315]), ((entity *)IFC4X2_types[407]),
           ((entity *)IFC4X2_types[607]), ((entity *)IFC4X2_types[664]),
           ((entity *)IFC4X2_types[766]), ((entity *)IFC4X2_types[890]),
           ((entity *)IFC4X2_types[891])});
  ((entity *)IFC4X2_types[751])
      ->set_subtypes(
          {((entity *)IFC4X2_types[51]), ((entity *)IFC4X2_types[52]),
           ((entity *)IFC4X2_types[191]), ((entity *)IFC4X2_types[286]),
           ((entity *)IFC4X2_types[672])});
  ((entity *)IFC4X2_types[51])->set_subtypes({((entity *)IFC4X2_types[53])});
  ((entity *)IFC4X2_types[494])
      ->set_subtypes(
          {((entity *)IFC4X2_types[59]), ((entity *)IFC4X2_types[522]),
           ((entity *)IFC4X2_types[1010]), ((entity *)IFC4X2_types[1026]),
           ((entity *)IFC4X2_types[1067])});
  ((entity *)IFC4X2_types[672])
      ->set_subtypes(
          {((entity *)IFC4X2_types[60]), ((entity *)IFC4X2_types[254]),
           ((entity *)IFC4X2_types[160]), ((entity *)IFC4X2_types[383]),
           ((entity *)IFC4X2_types[527]), ((entity *)IFC4X2_types[577]),
           ((entity *)IFC4X2_types[813]), ((entity *)IFC4X2_types[1149]),
           ((entity *)IFC4X2_types[1143]), ((entity *)IFC4X2_types[1167]),
           ((entity *)IFC4X2_types[1222])});
  ((entity *)IFC4X2_types[700])
      ->set_subtypes({((entity *)IFC4X2_types[64]),
                      ((entity *)IFC4X2_types[66]),
                      ((entity *)IFC4X2_types[67])});
  ((entity *)IFC4X2_types[104])->set_subtypes({((entity *)IFC4X2_types[106])});
  ((entity *)IFC4X2_types[96])
      ->set_subtypes(
          {((entity *)IFC4X2_types[107]), ((entity *)IFC4X2_types[261]),
           ((entity *)IFC4X2_types[262]), ((entity *)IFC4X2_types[815])});
  ((entity *)IFC4X2_types[107])->set_subtypes({((entity *)IFC4X2_types[109])});
  ((entity *)IFC4X2_types[111])
      ->set_subtypes(
          {((entity *)IFC4X2_types[68]),   ((entity *)IFC4X2_types[72]),
           ((entity *)IFC4X2_types[115]),  ((entity *)IFC4X2_types[155]),
           ((entity *)IFC4X2_types[177]),  ((entity *)IFC4X2_types[245]),
           ((entity *)IFC4X2_types[256]),  ((entity *)IFC4X2_types[282]),
           ((entity *)IFC4X2_types[319]),  ((entity *)IFC4X2_types[467]),
           ((entity *)IFC4X2_types[618]),  ((entity *)IFC4X2_types[706]),
           ((entity *)IFC4X2_types[799]),  ((entity *)IFC4X2_types[802]),
           ((entity *)IFC4X2_types[803]),  ((entity *)IFC4X2_types[901]),
           ((entity *)IFC4X2_types[928]),  ((entity *)IFC4X2_types[946]),
           ((entity *)IFC4X2_types[985]),  ((entity *)IFC4X2_types[986]),
           ((entity *)IFC4X2_types[1190]), ((entity *)IFC4X2_types[1201])});
  ((entity *)IFC4X2_types[68])->set_subtypes({((entity *)IFC4X2_types[69])});
  ((entity *)IFC4X2_types[118])
      ->set_subtypes(
          {((entity *)IFC4X2_types[70]),   ((entity *)IFC4X2_types[73]),
           ((entity *)IFC4X2_types[116]),  ((entity *)IFC4X2_types[156]),
           ((entity *)IFC4X2_types[179]),  ((entity *)IFC4X2_types[246]),
           ((entity *)IFC4X2_types[257]),  ((entity *)IFC4X2_types[283]),
           ((entity *)IFC4X2_types[328]),  ((entity *)IFC4X2_types[468]),
           ((entity *)IFC4X2_types[620]),  ((entity *)IFC4X2_types[708]),
           ((entity *)IFC4X2_types[800]),  ((entity *)IFC4X2_types[804]),
           ((entity *)IFC4X2_types[806]),  ((entity *)IFC4X2_types[902]),
           ((entity *)IFC4X2_types[929]),  ((entity *)IFC4X2_types[949]),
           ((entity *)IFC4X2_types[987]),  ((entity *)IFC4X2_types[989]),
           ((entity *)IFC4X2_types[1193]), ((entity *)IFC4X2_types[1210])});
  ((entity *)IFC4X2_types[1059])
      ->set_subtypes({((entity *)IFC4X2_types[79]),
                      ((entity *)IFC4X2_types[507]),
                      ((entity *)IFC4X2_types[699])});
  ((entity *)IFC4X2_types[251])
      ->set_subtypes(
          {((entity *)IFC4X2_types[80]), ((entity *)IFC4X2_types[814]),
           ((entity *)IFC4X2_types[898]), ((entity *)IFC4X2_types[899]),
           ((entity *)IFC4X2_types[980])});
  ((entity *)IFC4X2_types[88])->set_subtypes({((entity *)IFC4X2_types[85])});
  ((entity *)IFC4X2_types[189])->set_subtypes({((entity *)IFC4X2_types[90])});
  ((entity *)IFC4X2_types[89])
      ->set_subtypes({((entity *)IFC4X2_types[91]),
                      ((entity *)IFC4X2_types[92]),
                      ((entity *)IFC4X2_types[93])});
  ((entity *)IFC4X2_types[93])->set_subtypes({((entity *)IFC4X2_types[94])});
  ((entity *)IFC4X2_types[260])
      ->set_subtypes(
          {((entity *)IFC4X2_types[95]), ((entity *)IFC4X2_types[199]),
           ((entity *)IFC4X2_types[563]), ((entity *)IFC4X2_types[655]),
           ((entity *)IFC4X2_types[675]), ((entity *)IFC4X2_types[1043])});
  ((entity *)IFC4X2_types[1042])
      ->set_subtypes({((entity *)IFC4X2_types[96]),
                      ((entity *)IFC4X2_types[373]),
                      ((entity *)IFC4X2_types[1063])});
  ((entity *)IFC4X2_types[495])
      ->set_subtypes(
          {((entity *)IFC4X2_types[99]), ((entity *)IFC4X2_types[714])});
  ((entity *)IFC4X2_types[420])
      ->set_subtypes(
          {((entity *)IFC4X2_types[100]), ((entity *)IFC4X2_types[110])});
  ((entity *)IFC4X2_types[421])
      ->set_subtypes(
          {((entity *)IFC4X2_types[101]), ((entity *)IFC4X2_types[119])});
  ((entity *)IFC4X2_types[372])
      ->set_subtypes(
          {((entity *)IFC4X2_types[111]), ((entity *)IFC4X2_types[162]),
           ((entity *)IFC4X2_types[305]), ((entity *)IFC4X2_types[374]),
           ((entity *)IFC4X2_types[377]), ((entity *)IFC4X2_types[429]),
           ((entity *)IFC4X2_types[472]), ((entity *)IFC4X2_types[477]),
           ((entity *)IFC4X2_types[1140]), ((entity *)IFC4X2_types[1184])});
  ((entity *)IFC4X2_types[377])
      ->set_subtypes(
          {((entity *)IFC4X2_types[112]), ((entity *)IFC4X2_types[295]),
           ((entity *)IFC4X2_types[426]), ((entity *)IFC4X2_types[612]),
           ((entity *)IFC4X2_types[830]), ((entity *)IFC4X2_types[1178]),
           ((entity *)IFC4X2_types[1181])});
  ((entity *)IFC4X2_types[378])
      ->set_subtypes(
          {((entity *)IFC4X2_types[113]), ((entity *)IFC4X2_types[296]),
           ((entity *)IFC4X2_types[427]), ((entity *)IFC4X2_types[613]),
           ((entity *)IFC4X2_types[831]), ((entity *)IFC4X2_types[1179]),
           ((entity *)IFC4X2_types[1182])});
  ((entity *)IFC4X2_types[381])
      ->set_subtypes(
          {((entity *)IFC4X2_types[118]), ((entity *)IFC4X2_types[163]),
           ((entity *)IFC4X2_types[306]), ((entity *)IFC4X2_types[375]),
           ((entity *)IFC4X2_types[378]), ((entity *)IFC4X2_types[473]),
           ((entity *)IFC4X2_types[478]), ((entity *)IFC4X2_types[1141])});
  ((entity *)IFC4X2_types[1067])
      ->set_subtypes(
          {((entity *)IFC4X2_types[120]), ((entity *)IFC4X2_types[311]),
           ((entity *)IFC4X2_types[995]), ((entity *)IFC4X2_types[1221])});
  ((entity *)IFC4X2_types[446])
      ->set_subtypes(
          {((entity *)IFC4X2_types[125]), ((entity *)IFC4X2_types[131]),
           ((entity *)IFC4X2_types[334]), ((entity *)IFC4X2_types[529]),
           ((entity *)IFC4X2_types[693])});
  ((entity *)IFC4X2_types[447])
      ->set_subtypes(
          {((entity *)IFC4X2_types[126]), ((entity *)IFC4X2_types[132]),
           ((entity *)IFC4X2_types[335]), ((entity *)IFC4X2_types[530]),
           ((entity *)IFC4X2_types[694])});
  ((entity *)IFC4X2_types[456])
      ->set_subtypes(
          {((entity *)IFC4X2_types[128]), ((entity *)IFC4X2_types[134]),
           ((entity *)IFC4X2_types[337]), ((entity *)IFC4X2_types[696])});
  ((entity *)IFC4X2_types[457])
      ->set_subtypes(
          {((entity *)IFC4X2_types[129]), ((entity *)IFC4X2_types[135]),
           ((entity *)IFC4X2_types[338]), ((entity *)IFC4X2_types[697])});
  ((entity *)IFC4X2_types[282])
      ->set_subtypes(
          {((entity *)IFC4X2_types[137]), ((entity *)IFC4X2_types[689])});
  ((entity *)IFC4X2_types[283])
      ->set_subtypes(
          {((entity *)IFC4X2_types[138]), ((entity *)IFC4X2_types[691])});
  ((entity *)IFC4X2_types[710])
      ->set_subtypes({((entity *)IFC4X2_types[141]),
                      ((entity *)IFC4X2_types[711]),
                      ((entity *)IFC4X2_types[712])});
  ((entity *)IFC4X2_types[142])
      ->set_subtypes(
          {((entity *)IFC4X2_types[143]), ((entity *)IFC4X2_types[144])});
  ((entity *)IFC4X2_types[145])
      ->set_subtypes(
          {((entity *)IFC4X2_types[146]), ((entity *)IFC4X2_types[148])});
  ((entity *)IFC4X2_types[146])->set_subtypes({((entity *)IFC4X2_types[147])});
  ((entity *)IFC4X2_types[148])->set_subtypes({((entity *)IFC4X2_types[149])});
  ((entity *)IFC4X2_types[52])->set_subtypes({((entity *)IFC4X2_types[150])});
  ((entity *)IFC4X2_types[199])
      ->set_subtypes(
          {((entity *)IFC4X2_types[158]), ((entity *)IFC4X2_types[382])});
  ((entity *)IFC4X2_types[160])->set_subtypes({((entity *)IFC4X2_types[159])});
  ((entity *)IFC4X2_types[267])
      ->set_subtypes({((entity *)IFC4X2_types[161]),
                      ((entity *)IFC4X2_types[571]),
                      ((entity *)IFC4X2_types[1137])});
  ((entity *)IFC4X2_types[402])
      ->set_subtypes({((entity *)IFC4X2_types[164]),
                      ((entity *)IFC4X2_types[314]),
                      ((entity *)IFC4X2_types[546])});
  ((entity *)IFC4X2_types[406])
      ->set_subtypes(
          {((entity *)IFC4X2_types[165]), ((entity *)IFC4X2_types[316]),
           ((entity *)IFC4X2_types[403]), ((entity *)IFC4X2_types[404]),
           ((entity *)IFC4X2_types[405]), ((entity *)IFC4X2_types[547])});
  ((entity *)IFC4X2_types[200])
      ->set_subtypes(
          {((entity *)IFC4X2_types[168]), ((entity *)IFC4X2_types[662])});
  ((entity *)IFC4X2_types[176])->set_subtypes({((entity *)IFC4X2_types[174])});
  ((entity *)IFC4X2_types[734])
      ->set_subtypes(
          {((entity *)IFC4X2_types[175]), ((entity *)IFC4X2_types[176]),
           ((entity *)IFC4X2_types[269]), ((entity *)IFC4X2_types[270]),
           ((entity *)IFC4X2_types[271]), ((entity *)IFC4X2_types[508]),
           ((entity *)IFC4X2_types[728]), ((entity *)IFC4X2_types[1054]),
           ((entity *)IFC4X2_types[1055]), ((entity *)IFC4X2_types[1057]),
           ((entity *)IFC4X2_types[1058]), ((entity *)IFC4X2_types[1059]),
           ((entity *)IFC4X2_types[1107]), ((entity *)IFC4X2_types[1108]),
           ((entity *)IFC4X2_types[1110]), ((entity *)IFC4X2_types[1113]),
           ((entity *)IFC4X2_types[1114])});
  ((entity *)IFC4X2_types[177])->set_subtypes({((entity *)IFC4X2_types[178])});
  ((entity *)IFC4X2_types[762])
      ->set_subtypes(
          {((entity *)IFC4X2_types[185]), ((entity *)IFC4X2_types[937])});
  ((entity *)IFC4X2_types[779])
      ->set_subtypes(
          {((entity *)IFC4X2_types[186]), ((entity *)IFC4X2_types[938])});
  ((entity *)IFC4X2_types[188])->set_subtypes({((entity *)IFC4X2_types[189])});
  ((entity *)IFC4X2_types[454])
      ->set_subtypes({((entity *)IFC4X2_types[193]),
                      ((entity *)IFC4X2_types[423]),
                      ((entity *)IFC4X2_types[788])});
  ((entity *)IFC4X2_types[455])
      ->set_subtypes({((entity *)IFC4X2_types[194]),
                      ((entity *)IFC4X2_types[424]),
                      ((entity *)IFC4X2_types[789])});
  ((entity *)IFC4X2_types[1129])
      ->set_subtypes(
          {((entity *)IFC4X2_types[200]), ((entity *)IFC4X2_types[345]),
           ((entity *)IFC4X2_types[413]), ((entity *)IFC4X2_types[415]),
           ((entity *)IFC4X2_types[576]), ((entity *)IFC4X2_types[674]),
           ((entity *)IFC4X2_types[1175])});
  ((entity *)IFC4X2_types[202])
      ->set_subtypes(
          {((entity *)IFC4X2_types[201]), ((entity *)IFC4X2_types[204]),
           ((entity *)IFC4X2_types[205]), ((entity *)IFC4X2_types[207])});
  ((entity *)IFC4X2_types[204])->set_subtypes({((entity *)IFC4X2_types[203])});
  ((entity *)IFC4X2_types[219])
      ->set_subtypes(
          {((entity *)IFC4X2_types[210]), ((entity *)IFC4X2_types[213]),
           ((entity *)IFC4X2_types[216]), ((entity *)IFC4X2_types[248]),
           ((entity *)IFC4X2_types[535]), ((entity *)IFC4X2_types[1038])});
  ((entity *)IFC4X2_types[220])
      ->set_subtypes(
          {((entity *)IFC4X2_types[211]), ((entity *)IFC4X2_types[214]),
           ((entity *)IFC4X2_types[217]), ((entity *)IFC4X2_types[249]),
           ((entity *)IFC4X2_types[536]), ((entity *)IFC4X2_types[1039])});
  ((entity *)IFC4X2_types[889])->set_subtypes({((entity *)IFC4X2_types[219])});
  ((entity *)IFC4X2_types[1156])->set_subtypes({((entity *)IFC4X2_types[220])});
  ((entity *)IFC4X2_types[647])
      ->set_subtypes({((entity *)IFC4X2_types[221]),
                      ((entity *)IFC4X2_types[646]),
                      ((entity *)IFC4X2_types[1153])});
  ((entity *)IFC4X2_types[641])
      ->set_subtypes({((entity *)IFC4X2_types[223]),
                      ((entity *)IFC4X2_types[228]),
                      ((entity *)IFC4X2_types[943])});
  ((entity *)IFC4X2_types[228])->set_subtypes({((entity *)IFC4X2_types[229])});
  ((entity *)IFC4X2_types[47])->set_subtypes({((entity *)IFC4X2_types[243])});
  ((entity *)IFC4X2_types[956])
      ->set_subtypes(
          {((entity *)IFC4X2_types[253]), ((entity *)IFC4X2_types[583]),
           ((entity *)IFC4X2_types[916]), ((entity *)IFC4X2_types[1060]),
           ((entity *)IFC4X2_types[1061])});
  ((entity *)IFC4X2_types[737])
      ->set_subtypes(
          {((entity *)IFC4X2_types[268]), ((entity *)IFC4X2_types[432]),
           ((entity *)IFC4X2_types[1052]), ((entity *)IFC4X2_types[1105])});
  ((entity *)IFC4X2_types[373])
      ->set_subtypes(
          {((entity *)IFC4X2_types[273]), ((entity *)IFC4X2_types[704]),
           ((entity *)IFC4X2_types[981]), ((entity *)IFC4X2_types[1131])});
  ((entity *)IFC4X2_types[307])
      ->set_subtypes(
          {((entity *)IFC4X2_types[299]), ((entity *)IFC4X2_types[384]),
           ((entity *)IFC4X2_types[443]), ((entity *)IFC4X2_types[446]),
           ((entity *)IFC4X2_types[454]), ((entity *)IFC4X2_types[456]),
           ((entity *)IFC4X2_types[458]), ((entity *)IFC4X2_types[460]),
           ((entity *)IFC4X2_types[462])});
  ((entity *)IFC4X2_types[308])
      ->set_subtypes(
          {((entity *)IFC4X2_types[300]), ((entity *)IFC4X2_types[385]),
           ((entity *)IFC4X2_types[444]), ((entity *)IFC4X2_types[447]),
           ((entity *)IFC4X2_types[455]), ((entity *)IFC4X2_types[457]),
           ((entity *)IFC4X2_types[459]), ((entity *)IFC4X2_types[461]),
           ((entity *)IFC4X2_types[463])});
  ((entity *)IFC4X2_types[311])->set_subtypes({((entity *)IFC4X2_types[302])});
  ((entity *)IFC4X2_types[305])
      ->set_subtypes(
          {((entity *)IFC4X2_types[303]), ((entity *)IFC4X2_types[307])});
  ((entity *)IFC4X2_types[306])
      ->set_subtypes(
          {((entity *)IFC4X2_types[304]), ((entity *)IFC4X2_types[308])});
  ((entity *)IFC4X2_types[718])->set_subtypes({((entity *)IFC4X2_types[309])});
  ((entity *)IFC4X2_types[730])
      ->set_subtypes(
          {((entity *)IFC4X2_types[320]), ((entity *)IFC4X2_types[323]),
           ((entity *)IFC4X2_types[679]), ((entity *)IFC4X2_types[824]),
           ((entity *)IFC4X2_types[1202]), ((entity *)IFC4X2_types[1205])});
  ((entity *)IFC4X2_types[319])->set_subtypes({((entity *)IFC4X2_types[324])});
  ((entity *)IFC4X2_types[1155])
      ->set_subtypes(
          {((entity *)IFC4X2_types[325]), ((entity *)IFC4X2_types[381]),
           ((entity *)IFC4X2_types[970]), ((entity *)IFC4X2_types[1207])});
  ((entity *)IFC4X2_types[726])->set_subtypes({((entity *)IFC4X2_types[332])});
  ((entity *)IFC4X2_types[727])->set_subtypes({((entity *)IFC4X2_types[333])});
  ((entity *)IFC4X2_types[462])
      ->set_subtypes({((entity *)IFC4X2_types[340]),
                      ((entity *)IFC4X2_types[436]),
                      ((entity *)IFC4X2_types[517])});
  ((entity *)IFC4X2_types[463])
      ->set_subtypes({((entity *)IFC4X2_types[341]),
                      ((entity *)IFC4X2_types[437]),
                      ((entity *)IFC4X2_types[518])});
  ((entity *)IFC4X2_types[345])
      ->set_subtypes({((entity *)IFC4X2_types[346]),
                      ((entity *)IFC4X2_types[666]),
                      ((entity *)IFC4X2_types[1041])});
  ((entity *)IFC4X2_types[576])
      ->set_subtypes({((entity *)IFC4X2_types[347]),
                      ((entity *)IFC4X2_types[717]),
                      ((entity *)IFC4X2_types[1176])});
  ((entity *)IFC4X2_types[458])
      ->set_subtypes(
          {((entity *)IFC4X2_types[358]), ((entity *)IFC4X2_types[1074])});
  ((entity *)IFC4X2_types[459])
      ->set_subtypes(
          {((entity *)IFC4X2_types[359]), ((entity *)IFC4X2_types[1075])});
  ((entity *)IFC4X2_types[794])->set_subtypes({((entity *)IFC4X2_types[380])});
  ((entity *)IFC4X2_types[744])
      ->set_subtypes({((entity *)IFC4X2_types[396]),
                      ((entity *)IFC4X2_types[741]),
                      ((entity *)IFC4X2_types[1077])});
  ((entity *)IFC4X2_types[913])
      ->set_subtypes(
          {((entity *)IFC4X2_types[397]), ((entity *)IFC4X2_types[538]),
           ((entity *)IFC4X2_types[895]), ((entity *)IFC4X2_types[1079]),
           ((entity *)IFC4X2_types[1220])});
  ((entity *)IFC4X2_types[1154])
      ->set_subtypes({((entity *)IFC4X2_types[399]),
                      ((entity *)IFC4X2_types[742]),
                      ((entity *)IFC4X2_types[1081])});
  ((entity *)IFC4X2_types[763])
      ->set_subtypes(
          {((entity *)IFC4X2_types[401]), ((entity *)IFC4X2_types[729]),
           ((entity *)IFC4X2_types[762]), ((entity *)IFC4X2_types[768])});
  ((entity *)IFC4X2_types[410])->set_subtypes({((entity *)IFC4X2_types[408])});
  ((entity *)IFC4X2_types[969])
      ->set_subtypes({((entity *)IFC4X2_types[410]),
                      ((entity *)IFC4X2_types[971]),
                      ((entity *)IFC4X2_types[973])});
  ((entity *)IFC4X2_types[1060])
      ->set_subtypes(
          {((entity *)IFC4X2_types[411]), ((entity *)IFC4X2_types[442]),
           ((entity *)IFC4X2_types[896]), ((entity *)IFC4X2_types[1044])});
  ((entity *)IFC4X2_types[411])->set_subtypes({((entity *)IFC4X2_types[412])});
  ((entity *)IFC4X2_types[415])->set_subtypes({((entity *)IFC4X2_types[416])});
  ((entity *)IFC4X2_types[413])->set_subtypes({((entity *)IFC4X2_types[417])});
  ((entity *)IFC4X2_types[418])->set_subtypes({((entity *)IFC4X2_types[419])});
  ((entity *)IFC4X2_types[971])
      ->set_subtypes(
          {((entity *)IFC4X2_types[420]), ((entity *)IFC4X2_types[421]),
           ((entity *)IFC4X2_types[942]), ((entity *)IFC4X2_types[962])});
  ((entity *)IFC4X2_types[997])
      ->set_subtypes(
          {((entity *)IFC4X2_types[422]), ((entity *)IFC4X2_types[951])});
  ((entity *)IFC4X2_types[429])
      ->set_subtypes({((entity *)IFC4X2_types[430]),
                      ((entity *)IFC4X2_types[431]),
                      ((entity *)IFC4X2_types[1045])});
  ((entity *)IFC4X2_types[472])
      ->set_subtypes(
          {((entity *)IFC4X2_types[474]), ((entity *)IFC4X2_types[1068])});
  ((entity *)IFC4X2_types[473])
      ->set_subtypes(
          {((entity *)IFC4X2_types[475]), ((entity *)IFC4X2_types[1069])});
  ((entity *)IFC4X2_types[485])->set_subtypes({((entity *)IFC4X2_types[480])});
  ((entity *)IFC4X2_types[886])->set_subtypes({((entity *)IFC4X2_types[482])});
  ((entity *)IFC4X2_types[887])
      ->set_subtypes(
          {((entity *)IFC4X2_types[483]), ((entity *)IFC4X2_types[585]),
           ((entity *)IFC4X2_types[1035]), ((entity *)IFC4X2_types[1129])});
  ((entity *)IFC4X2_types[482])->set_subtypes({((entity *)IFC4X2_types[484])});
  ((entity *)IFC4X2_types[719])
      ->set_subtypes({((entity *)IFC4X2_types[489]),
                      ((entity *)IFC4X2_types[567]),
                      ((entity *)IFC4X2_types[819])});
  ((entity *)IFC4X2_types[650])
      ->set_subtypes({((entity *)IFC4X2_types[491]),
                      ((entity *)IFC4X2_types[566]),
                      ((entity *)IFC4X2_types[573])});
  ((entity *)IFC4X2_types[1096])
      ->set_subtypes(
          {((entity *)IFC4X2_types[510]), ((entity *)IFC4X2_types[1095])});
  ((entity *)IFC4X2_types[510])->set_subtypes({((entity *)IFC4X2_types[511])});
  ((entity *)IFC4X2_types[1110])
      ->set_subtypes({((entity *)IFC4X2_types[512]),
                      ((entity *)IFC4X2_types[1111]),
                      ((entity *)IFC4X2_types[1112])});
  ((entity *)IFC4X2_types[512])->set_subtypes({((entity *)IFC4X2_types[513])});
  ((entity *)IFC4X2_types[1043])
      ->set_subtypes(
          {((entity *)IFC4X2_types[521]), ((entity *)IFC4X2_types[914])});
  ((entity *)IFC4X2_types[1125])
      ->set_subtypes(
          {((entity *)IFC4X2_types[525]), ((entity *)IFC4X2_types[822])});
  ((entity *)IFC4X2_types[557])
      ->set_subtypes(
          {((entity *)IFC4X2_types[558]), ((entity *)IFC4X2_types[559]),
           ((entity *)IFC4X2_types[560]), ((entity *)IFC4X2_types[561])});
  ((entity *)IFC4X2_types[561])->set_subtypes({((entity *)IFC4X2_types[562])});
  ((entity *)IFC4X2_types[236])->set_subtypes({((entity *)IFC4X2_types[584])});
  ((entity *)IFC4X2_types[594])
      ->set_subtypes(
          {((entity *)IFC4X2_types[590]), ((entity *)IFC4X2_types[592]),
           ((entity *)IFC4X2_types[593]), ((entity *)IFC4X2_types[596]),
           ((entity *)IFC4X2_types[597]), ((entity *)IFC4X2_types[601]),
           ((entity *)IFC4X2_types[602])});
  ((entity *)IFC4X2_types[748])
      ->set_subtypes(
          {((entity *)IFC4X2_types[595]), ((entity *)IFC4X2_types[747])});
  ((entity *)IFC4X2_types[609])
      ->set_subtypes(
          {((entity *)IFC4X2_types[598]), ((entity *)IFC4X2_types[603])});
  ((entity *)IFC4X2_types[596])->set_subtypes({((entity *)IFC4X2_types[599])});
  ((entity *)IFC4X2_types[603])->set_subtypes({((entity *)IFC4X2_types[604])});
  ((entity *)IFC4X2_types[601])->set_subtypes({((entity *)IFC4X2_types[605])});
  ((entity *)IFC4X2_types[401])
      ->set_subtypes(
          {((entity *)IFC4X2_types[606]), ((entity *)IFC4X2_types[752])});
  ((entity *)IFC4X2_types[618])->set_subtypes({((entity *)IFC4X2_types[619])});
  ((entity *)IFC4X2_types[208])
      ->set_subtypes(
          {((entity *)IFC4X2_types[622]), ((entity *)IFC4X2_types[648])});
  ((entity *)IFC4X2_types[286])->set_subtypes({((entity *)IFC4X2_types[624])});
  ((entity *)IFC4X2_types[904])
      ->set_subtypes({((entity *)IFC4X2_types[647]),
                      ((entity *)IFC4X2_types[765]),
                      ((entity *)IFC4X2_types[851])});
  ((entity *)IFC4X2_types[6])->set_subtypes({((entity *)IFC4X2_types[653])});
  ((entity *)IFC4X2_types[655])
      ->set_subtypes({((entity *)IFC4X2_types[656]),
                      ((entity *)IFC4X2_types[657]),
                      ((entity *)IFC4X2_types[658])});
  ((entity *)IFC4X2_types[431])
      ->set_subtypes(
          {((entity *)IFC4X2_types[659]), ((entity *)IFC4X2_types[1186])});
  ((entity *)IFC4X2_types[659])->set_subtypes({((entity *)IFC4X2_types[661])});
  ((entity *)IFC4X2_types[90])->set_subtypes({((entity *)IFC4X2_types[667])});
  ((entity *)IFC4X2_types[687])
      ->set_subtypes(
          {((entity *)IFC4X2_types[685]), ((entity *)IFC4X2_types[688])});
  ((entity *)IFC4X2_types[702])->set_subtypes({((entity *)IFC4X2_types[701])});
  ((entity *)IFC4X2_types[706])->set_subtypes({((entity *)IFC4X2_types[707])});
  ((entity *)IFC4X2_types[1095])
      ->set_subtypes(
          {((entity *)IFC4X2_types[715]), ((entity *)IFC4X2_types[1144])});
  ((entity *)IFC4X2_types[12])
      ->set_subtypes(
          {((entity *)IFC4X2_types[724]), ((entity *)IFC4X2_types[1083])});
  ((entity *)IFC4X2_types[728])
      ->set_subtypes({((entity *)IFC4X2_types[726]),
                      ((entity *)IFC4X2_types[727]),
                      ((entity *)IFC4X2_types[731])});
  ((entity *)IFC4X2_types[772])
      ->set_subtypes({((entity *)IFC4X2_types[730]),
                      ((entity *)IFC4X2_types[771]),
                      ((entity *)IFC4X2_types[794])});
  ((entity *)IFC4X2_types[735])->set_subtypes({((entity *)IFC4X2_types[736])});
  ((entity *)IFC4X2_types[221])
      ->set_subtypes(
          {((entity *)IFC4X2_types[754]), ((entity *)IFC4X2_types[759])});
  ((entity *)IFC4X2_types[237])->set_subtypes({((entity *)IFC4X2_types[755])});
  ((entity *)IFC4X2_types[430])->set_subtypes({((entity *)IFC4X2_types[757])});
  ((entity *)IFC4X2_types[937])
      ->set_subtypes(
          {((entity *)IFC4X2_types[764]), ((entity *)IFC4X2_types[767]),
           ((entity *)IFC4X2_types[769]), ((entity *)IFC4X2_types[770]),
           ((entity *)IFC4X2_types[777]), ((entity *)IFC4X2_types[778])});
  ((entity *)IFC4X2_types[765])
      ->set_subtypes(
          {((entity *)IFC4X2_types[772]), ((entity *)IFC4X2_types[780])});
  ((entity *)IFC4X2_types[780])
      ->set_subtypes(
          {((entity *)IFC4X2_types[775]), ((entity *)IFC4X2_types[779])});
  ((entity *)IFC4X2_types[688])
      ->set_subtypes(
          {((entity *)IFC4X2_types[791]), ((entity *)IFC4X2_types[792]),
           ((entity *)IFC4X2_types[793]), ((entity *)IFC4X2_types[795]),
           ((entity *)IFC4X2_types[796]), ((entity *)IFC4X2_types[797])});
  ((entity *)IFC4X2_types[106])->set_subtypes({((entity *)IFC4X2_types[809])});
  ((entity *)IFC4X2_types[109])->set_subtypes({((entity *)IFC4X2_types[810])});
  ((entity *)IFC4X2_types[813])
      ->set_subtypes(
          {((entity *)IFC4X2_types[812]), ((entity *)IFC4X2_types[909])});
  ((entity *)IFC4X2_types[729])
      ->set_subtypes({((entity *)IFC4X2_types[823]),
                      ((entity *)IFC4X2_types[920]),
                      ((entity *)IFC4X2_types[921])});
  ((entity *)IFC4X2_types[830])
      ->set_subtypes(
          {((entity *)IFC4X2_types[825]), ((entity *)IFC4X2_types[832]),
           ((entity *)IFC4X2_types[1086]), ((entity *)IFC4X2_types[1087]),
           ((entity *)IFC4X2_types[1090])});
  ((entity *)IFC4X2_types[831])
      ->set_subtypes(
          {((entity *)IFC4X2_types[828]), ((entity *)IFC4X2_types[833]),
           ((entity *)IFC4X2_types[1088]), ((entity *)IFC4X2_types[1091]),
           ((entity *)IFC4X2_types[1093])});
  ((entity *)IFC4X2_types[865])
      ->set_subtypes(
          {((entity *)IFC4X2_types[835]), ((entity *)IFC4X2_types[874]),
           ((entity *)IFC4X2_types[876]), ((entity *)IFC4X2_types[883])});
  ((entity *)IFC4X2_types[851])
      ->set_subtypes(
          {((entity *)IFC4X2_types[836]), ((entity *)IFC4X2_types[844]),
           ((entity *)IFC4X2_types[852]), ((entity *)IFC4X2_types[864]),
           ((entity *)IFC4X2_types[865]), ((entity *)IFC4X2_types[866])});
  ((entity *)IFC4X2_types[836])
      ->set_subtypes(
          {((entity *)IFC4X2_types[837]), ((entity *)IFC4X2_types[838]),
           ((entity *)IFC4X2_types[839]), ((entity *)IFC4X2_types[841]),
           ((entity *)IFC4X2_types[842]), ((entity *)IFC4X2_types[843])});
  ((entity *)IFC4X2_types[839])->set_subtypes({((entity *)IFC4X2_types[840])});
  ((entity *)IFC4X2_types[844])
      ->set_subtypes(
          {((entity *)IFC4X2_types[845]), ((entity *)IFC4X2_types[846]),
           ((entity *)IFC4X2_types[847]), ((entity *)IFC4X2_types[848]),
           ((entity *)IFC4X2_types[849]), ((entity *)IFC4X2_types[850])});
  ((entity *)IFC4X2_types[852])
      ->set_subtypes(
          {((entity *)IFC4X2_types[853]), ((entity *)IFC4X2_types[856]),
           ((entity *)IFC4X2_types[855]), ((entity *)IFC4X2_types[857]),
           ((entity *)IFC4X2_types[858]), ((entity *)IFC4X2_types[861]),
           ((entity *)IFC4X2_types[862]), ((entity *)IFC4X2_types[863]),
           ((entity *)IFC4X2_types[871]), ((entity *)IFC4X2_types[872]),
           ((entity *)IFC4X2_types[873]), ((entity *)IFC4X2_types[875]),
           ((entity *)IFC4X2_types[877]), ((entity *)IFC4X2_types[878]),
           ((entity *)IFC4X2_types[879]), ((entity *)IFC4X2_types[880])});
  ((entity *)IFC4X2_types[853])
      ->set_subtypes(
          {((entity *)IFC4X2_types[854]), ((entity *)IFC4X2_types[860])});
  ((entity *)IFC4X2_types[858])->set_subtypes({((entity *)IFC4X2_types[859])});
  ((entity *)IFC4X2_types[866])
      ->set_subtypes(
          {((entity *)IFC4X2_types[867]), ((entity *)IFC4X2_types[868]),
           ((entity *)IFC4X2_types[869]), ((entity *)IFC4X2_types[870])});
  ((entity *)IFC4X2_types[880])->set_subtypes({((entity *)IFC4X2_types[881])});
  ((entity *)IFC4X2_types[881])->set_subtypes({((entity *)IFC4X2_types[882])});
  ((entity *)IFC4X2_types[190])->set_subtypes({((entity *)IFC4X2_types[884])});
  ((entity *)IFC4X2_types[896])->set_subtypes({((entity *)IFC4X2_types[897])});
  ((entity *)IFC4X2_types[916])->set_subtypes({((entity *)IFC4X2_types[917])});
  ((entity *)IFC4X2_types[885])
      ->set_subtypes(
          {((entity *)IFC4X2_types[932]), ((entity *)IFC4X2_types[1037])});
  ((entity *)IFC4X2_types[932])
      ->set_subtypes(
          {((entity *)IFC4X2_types[933]), ((entity *)IFC4X2_types[1130])});
  ((entity *)IFC4X2_types[946])
      ->set_subtypes(
          {((entity *)IFC4X2_types[947]), ((entity *)IFC4X2_types[948])});
  ((entity *)IFC4X2_types[972])->set_subtypes({((entity *)IFC4X2_types[967])});
  ((entity *)IFC4X2_types[970])
      ->set_subtypes(
          {((entity *)IFC4X2_types[972]), ((entity *)IFC4X2_types[974])});
  ((entity *)IFC4X2_types[993])
      ->set_subtypes(
          {((entity *)IFC4X2_types[992]), ((entity *)IFC4X2_types[1025])});
  ((entity *)IFC4X2_types[1005])
      ->set_subtypes(
          {((entity *)IFC4X2_types[996]), ((entity *)IFC4X2_types[1020])});
  ((entity *)IFC4X2_types[992])
      ->set_subtypes({((entity *)IFC4X2_types[998]),
                      ((entity *)IFC4X2_types[1022]),
                      ((entity *)IFC4X2_types[1027])});
  ((entity *)IFC4X2_types[996])
      ->set_subtypes({((entity *)IFC4X2_types[1000]),
                      ((entity *)IFC4X2_types[1023]),
                      ((entity *)IFC4X2_types[1029])});
  ((entity *)IFC4X2_types[1020])
      ->set_subtypes(
          {((entity *)IFC4X2_types[1001]), ((entity *)IFC4X2_types[1030])});
  ((entity *)IFC4X2_types[1001])
      ->set_subtypes({((entity *)IFC4X2_types[1003])});
  ((entity *)IFC4X2_types[1025])
      ->set_subtypes({((entity *)IFC4X2_types[1004]),
                      ((entity *)IFC4X2_types[1024]),
                      ((entity *)IFC4X2_types[1033])});
  ((entity *)IFC4X2_types[998])->set_subtypes({((entity *)IFC4X2_types[1006])});
  ((entity *)IFC4X2_types[1010])
      ->set_subtypes({((entity *)IFC4X2_types[1008])});
  ((entity *)IFC4X2_types[1007])
      ->set_subtypes(
          {((entity *)IFC4X2_types[1009]), ((entity *)IFC4X2_types[1012])});
  ((entity *)IFC4X2_types[1018])
      ->set_subtypes(
          {((entity *)IFC4X2_types[1011]), ((entity *)IFC4X2_types[1013]),
           ((entity *)IFC4X2_types[1014]), ((entity *)IFC4X2_types[1016]),
           ((entity *)IFC4X2_types[1019])});
  ((entity *)IFC4X2_types[1014])
      ->set_subtypes({((entity *)IFC4X2_types[1015])});
  ((entity *)IFC4X2_types[1016])
      ->set_subtypes({((entity *)IFC4X2_types[1017])});
  ((entity *)IFC4X2_types[1012])
      ->set_subtypes(
          {((entity *)IFC4X2_types[1018]), ((entity *)IFC4X2_types[1050])});
  ((entity *)IFC4X2_types[1027])
      ->set_subtypes({((entity *)IFC4X2_types[1021])});
  ((entity *)IFC4X2_types[1030])
      ->set_subtypes({((entity *)IFC4X2_types[1032])});
  ((entity *)IFC4X2_types[1037])
      ->set_subtypes({((entity *)IFC4X2_types[1036])});
  ((entity *)IFC4X2_types[1063])
      ->set_subtypes(
          {((entity *)IFC4X2_types[1047]), ((entity *)IFC4X2_types[1048])});
  ((entity *)IFC4X2_types[1057])
      ->set_subtypes({((entity *)IFC4X2_types[1056])});
  ((entity *)IFC4X2_types[1061])
      ->set_subtypes({((entity *)IFC4X2_types[1062])});
  ((entity *)IFC4X2_types[1079])
      ->set_subtypes({((entity *)IFC4X2_types[1080])});
  ((entity *)IFC4X2_types[1102])
      ->set_subtypes({((entity *)IFC4X2_types[1103])});
  ((entity *)IFC4X2_types[731])->set_subtypes({((entity *)IFC4X2_types[1106])});
  ((entity *)IFC4X2_types[1144])
      ->set_subtypes({((entity *)IFC4X2_types[1145])});
  ((entity *)IFC4X2_types[1153])
      ->set_subtypes({((entity *)IFC4X2_types[1154]),
                      ((entity *)IFC4X2_types[1155]),
                      ((entity *)IFC4X2_types[1156])});
  ((entity *)IFC4X2_types[1175])
      ->set_subtypes({((entity *)IFC4X2_types[1177])});
  ((entity *)IFC4X2_types[1190])
      ->set_subtypes(
          {((entity *)IFC4X2_types[1191]), ((entity *)IFC4X2_types[1192])});
  ((entity *)IFC4X2_types[1201])
      ->set_subtypes({((entity *)IFC4X2_types[1206])});
  ((entity *)IFC4X2_types[1215])
      ->set_subtypes(
          {((entity *)IFC4X2_types[1216]), ((entity *)IFC4X2_types[1218])});
  return new schema_definition(
      strings[3479],
      {IFC4X2_types[0],    IFC4X2_types[1],    IFC4X2_types[2],
       IFC4X2_types[3],    IFC4X2_types[4],    IFC4X2_types[5],
       IFC4X2_types[6],    IFC4X2_types[7],    IFC4X2_types[8],
       IFC4X2_types[9],    IFC4X2_types[10],   IFC4X2_types[11],
       IFC4X2_types[12],   IFC4X2_types[13],   IFC4X2_types[14],
       IFC4X2_types[15],   IFC4X2_types[16],   IFC4X2_types[17],
       IFC4X2_types[18],   IFC4X2_types[19],   IFC4X2_types[20],
       IFC4X2_types[21],   IFC4X2_types[22],   IFC4X2_types[23],
       IFC4X2_types[24],   IFC4X2_types[25],   IFC4X2_types[26],
       IFC4X2_types[27],   IFC4X2_types[28],   IFC4X2_types[29],
       IFC4X2_types[30],   IFC4X2_types[31],   IFC4X2_types[32],
       IFC4X2_types[33],   IFC4X2_types[34],   IFC4X2_types[35],
       IFC4X2_types[36],   IFC4X2_types[37],   IFC4X2_types[38],
       IFC4X2_types[39],   IFC4X2_types[40],   IFC4X2_types[41],
       IFC4X2_types[42],   IFC4X2_types[43],   IFC4X2_types[44],
       IFC4X2_types[45],   IFC4X2_types[46],   IFC4X2_types[47],
       IFC4X2_types[48],   IFC4X2_types[49],   IFC4X2_types[50],
       IFC4X2_types[51],   IFC4X2_types[52],   IFC4X2_types[53],
       IFC4X2_types[54],   IFC4X2_types[55],   IFC4X2_types[56],
       IFC4X2_types[57],   IFC4X2_types[58],   IFC4X2_types[59],
       IFC4X2_types[60],   IFC4X2_types[61],   IFC4X2_types[62],
       IFC4X2_types[63],   IFC4X2_types[64],   IFC4X2_types[65],
       IFC4X2_types[66],   IFC4X2_types[67],   IFC4X2_types[68],
       IFC4X2_types[69],   IFC4X2_types[70],   IFC4X2_types[71],
       IFC4X2_types[72],   IFC4X2_types[73],   IFC4X2_types[74],
       IFC4X2_types[75],   IFC4X2_types[76],   IFC4X2_types[77],
       IFC4X2_types[78],   IFC4X2_types[79],   IFC4X2_types[80],
       IFC4X2_types[81],   IFC4X2_types[82],   IFC4X2_types[83],
       IFC4X2_types[84],   IFC4X2_types[85],   IFC4X2_types[86],
       IFC4X2_types[87],   IFC4X2_types[88],   IFC4X2_types[89],
       IFC4X2_types[90],   IFC4X2_types[91],   IFC4X2_types[92],
       IFC4X2_types[93],   IFC4X2_types[94],   IFC4X2_types[95],
       IFC4X2_types[96],   IFC4X2_types[97],   IFC4X2_types[98],
       IFC4X2_types[99],   IFC4X2_types[100],  IFC4X2_types[101],
       IFC4X2_types[102],  IFC4X2_types[103],  IFC4X2_types[104],
       IFC4X2_types[105],  IFC4X2_types[106],  IFC4X2_types[107],
       IFC4X2_types[108],  IFC4X2_types[109],  IFC4X2_types[110],
       IFC4X2_types[111],  IFC4X2_types[112],  IFC4X2_types[113],
       IFC4X2_types[114],  IFC4X2_types[115],  IFC4X2_types[116],
       IFC4X2_types[117],  IFC4X2_types[118],  IFC4X2_types[119],
       IFC4X2_types[120],  IFC4X2_types[121],  IFC4X2_types[122],
       IFC4X2_types[123],  IFC4X2_types[124],  IFC4X2_types[125],
       IFC4X2_types[126],  IFC4X2_types[127],  IFC4X2_types[128],
       IFC4X2_types[129],  IFC4X2_types[130],  IFC4X2_types[131],
       IFC4X2_types[132],  IFC4X2_types[133],  IFC4X2_types[134],
       IFC4X2_types[135],  IFC4X2_types[136],  IFC4X2_types[137],
       IFC4X2_types[138],  IFC4X2_types[139],  IFC4X2_types[140],
       IFC4X2_types[141],  IFC4X2_types[142],  IFC4X2_types[143],
       IFC4X2_types[144],  IFC4X2_types[145],  IFC4X2_types[146],
       IFC4X2_types[147],  IFC4X2_types[148],  IFC4X2_types[149],
       IFC4X2_types[150],  IFC4X2_types[151],  IFC4X2_types[152],
       IFC4X2_types[153],  IFC4X2_types[154],  IFC4X2_types[155],
       IFC4X2_types[156],  IFC4X2_types[157],  IFC4X2_types[158],
       IFC4X2_types[159],  IFC4X2_types[160],  IFC4X2_types[161],
       IFC4X2_types[162],  IFC4X2_types[163],  IFC4X2_types[164],
       IFC4X2_types[165],  IFC4X2_types[166],  IFC4X2_types[167],
       IFC4X2_types[168],  IFC4X2_types[169],  IFC4X2_types[170],
       IFC4X2_types[171],  IFC4X2_types[172],  IFC4X2_types[173],
       IFC4X2_types[174],  IFC4X2_types[175],  IFC4X2_types[176],
       IFC4X2_types[177],  IFC4X2_types[178],  IFC4X2_types[179],
       IFC4X2_types[180],  IFC4X2_types[181],  IFC4X2_types[182],
       IFC4X2_types[183],  IFC4X2_types[184],  IFC4X2_types[185],
       IFC4X2_types[186],  IFC4X2_types[187],  IFC4X2_types[188],
       IFC4X2_types[189],  IFC4X2_types[190],  IFC4X2_types[191],
       IFC4X2_types[192],  IFC4X2_types[193],  IFC4X2_types[194],
       IFC4X2_types[195],  IFC4X2_types[196],  IFC4X2_types[197],
       IFC4X2_types[198],  IFC4X2_types[199],  IFC4X2_types[200],
       IFC4X2_types[201],  IFC4X2_types[202],  IFC4X2_types[203],
       IFC4X2_types[204],  IFC4X2_types[205],  IFC4X2_types[206],
       IFC4X2_types[207],  IFC4X2_types[208],  IFC4X2_types[209],
       IFC4X2_types[210],  IFC4X2_types[211],  IFC4X2_types[212],
       IFC4X2_types[213],  IFC4X2_types[214],  IFC4X2_types[215],
       IFC4X2_types[216],  IFC4X2_types[217],  IFC4X2_types[218],
       IFC4X2_types[219],  IFC4X2_types[220],  IFC4X2_types[221],
       IFC4X2_types[222],  IFC4X2_types[223],  IFC4X2_types[224],
       IFC4X2_types[225],  IFC4X2_types[226],  IFC4X2_types[227],
       IFC4X2_types[228],  IFC4X2_types[229],  IFC4X2_types[230],
       IFC4X2_types[231],  IFC4X2_types[232],  IFC4X2_types[233],
       IFC4X2_types[234],  IFC4X2_types[235],  IFC4X2_types[236],
       IFC4X2_types[237],  IFC4X2_types[238],  IFC4X2_types[239],
       IFC4X2_types[240],  IFC4X2_types[241],  IFC4X2_types[242],
       IFC4X2_types[243],  IFC4X2_types[244],  IFC4X2_types[245],
       IFC4X2_types[246],  IFC4X2_types[247],  IFC4X2_types[248],
       IFC4X2_types[249],  IFC4X2_types[250],  IFC4X2_types[251],
       IFC4X2_types[252],  IFC4X2_types[253],  IFC4X2_types[254],
       IFC4X2_types[255],  IFC4X2_types[256],  IFC4X2_types[257],
       IFC4X2_types[258],  IFC4X2_types[259],  IFC4X2_types[260],
       IFC4X2_types[261],  IFC4X2_types[262],  IFC4X2_types[263],
       IFC4X2_types[264],  IFC4X2_types[265],  IFC4X2_types[266],
       IFC4X2_types[267],  IFC4X2_types[268],  IFC4X2_types[269],
       IFC4X2_types[270],  IFC4X2_types[271],  IFC4X2_types[272],
       IFC4X2_types[273],  IFC4X2_types[274],  IFC4X2_types[275],
       IFC4X2_types[276],  IFC4X2_types[277],  IFC4X2_types[278],
       IFC4X2_types[279],  IFC4X2_types[280],  IFC4X2_types[281],
       IFC4X2_types[282],  IFC4X2_types[283],  IFC4X2_types[284],
       IFC4X2_types[285],  IFC4X2_types[286],  IFC4X2_types[287],
       IFC4X2_types[288],  IFC4X2_types[289],  IFC4X2_types[290],
       IFC4X2_types[291],  IFC4X2_types[292],  IFC4X2_types[293],
       IFC4X2_types[294],  IFC4X2_types[295],  IFC4X2_types[296],
       IFC4X2_types[297],  IFC4X2_types[298],  IFC4X2_types[299],
       IFC4X2_types[300],  IFC4X2_types[301],  IFC4X2_types[302],
       IFC4X2_types[303],  IFC4X2_types[304],  IFC4X2_types[305],
       IFC4X2_types[306],  IFC4X2_types[307],  IFC4X2_types[308],
       IFC4X2_types[309],  IFC4X2_types[310],  IFC4X2_types[311],
       IFC4X2_types[312],  IFC4X2_types[313],  IFC4X2_types[314],
       IFC4X2_types[315],  IFC4X2_types[316],  IFC4X2_types[317],
       IFC4X2_types[318],  IFC4X2_types[319],  IFC4X2_types[320],
       IFC4X2_types[321],  IFC4X2_types[322],  IFC4X2_types[323],
       IFC4X2_types[324],  IFC4X2_types[325],  IFC4X2_types[326],
       IFC4X2_types[327],  IFC4X2_types[328],  IFC4X2_types[329],
       IFC4X2_types[330],  IFC4X2_types[331],  IFC4X2_types[332],
       IFC4X2_types[333],  IFC4X2_types[334],  IFC4X2_types[335],
       IFC4X2_types[336],  IFC4X2_types[337],  IFC4X2_types[338],
       IFC4X2_types[339],  IFC4X2_types[340],  IFC4X2_types[341],
       IFC4X2_types[342],  IFC4X2_types[343],  IFC4X2_types[344],
       IFC4X2_types[345],  IFC4X2_types[346],  IFC4X2_types[347],
       IFC4X2_types[348],  IFC4X2_types[349],  IFC4X2_types[350],
       IFC4X2_types[351],  IFC4X2_types[352],  IFC4X2_types[353],
       IFC4X2_types[354],  IFC4X2_types[355],  IFC4X2_types[356],
       IFC4X2_types[357],  IFC4X2_types[358],  IFC4X2_types[359],
       IFC4X2_types[360],  IFC4X2_types[361],  IFC4X2_types[362],
       IFC4X2_types[363],  IFC4X2_types[364],  IFC4X2_types[365],
       IFC4X2_types[366],  IFC4X2_types[367],  IFC4X2_types[368],
       IFC4X2_types[369],  IFC4X2_types[370],  IFC4X2_types[371],
       IFC4X2_types[372],  IFC4X2_types[373],  IFC4X2_types[374],
       IFC4X2_types[375],  IFC4X2_types[376],  IFC4X2_types[377],
       IFC4X2_types[378],  IFC4X2_types[379],  IFC4X2_types[380],
       IFC4X2_types[381],  IFC4X2_types[382],  IFC4X2_types[383],
       IFC4X2_types[384],  IFC4X2_types[385],  IFC4X2_types[386],
       IFC4X2_types[387],  IFC4X2_types[388],  IFC4X2_types[389],
       IFC4X2_types[390],  IFC4X2_types[391],  IFC4X2_types[392],
       IFC4X2_types[393],  IFC4X2_types[394],  IFC4X2_types[395],
       IFC4X2_types[396],  IFC4X2_types[397],  IFC4X2_types[398],
       IFC4X2_types[399],  IFC4X2_types[400],  IFC4X2_types[401],
       IFC4X2_types[402],  IFC4X2_types[403],  IFC4X2_types[404],
       IFC4X2_types[405],  IFC4X2_types[406],  IFC4X2_types[407],
       IFC4X2_types[408],  IFC4X2_types[409],  IFC4X2_types[410],
       IFC4X2_types[411],  IFC4X2_types[412],  IFC4X2_types[413],
       IFC4X2_types[414],  IFC4X2_types[415],  IFC4X2_types[416],
       IFC4X2_types[417],  IFC4X2_types[418],  IFC4X2_types[419],
       IFC4X2_types[420],  IFC4X2_types[421],  IFC4X2_types[422],
       IFC4X2_types[423],  IFC4X2_types[424],  IFC4X2_types[425],
       IFC4X2_types[426],  IFC4X2_types[427],  IFC4X2_types[428],
       IFC4X2_types[429],  IFC4X2_types[430],  IFC4X2_types[431],
       IFC4X2_types[432],  IFC4X2_types[433],  IFC4X2_types[434],
       IFC4X2_types[435],  IFC4X2_types[436],  IFC4X2_types[437],
       IFC4X2_types[438],  IFC4X2_types[439],  IFC4X2_types[440],
       IFC4X2_types[441],  IFC4X2_types[442],  IFC4X2_types[443],
       IFC4X2_types[444],  IFC4X2_types[445],  IFC4X2_types[446],
       IFC4X2_types[447],  IFC4X2_types[448],  IFC4X2_types[449],
       IFC4X2_types[450],  IFC4X2_types[451],  IFC4X2_types[452],
       IFC4X2_types[453],  IFC4X2_types[454],  IFC4X2_types[455],
       IFC4X2_types[456],  IFC4X2_types[457],  IFC4X2_types[458],
       IFC4X2_types[459],  IFC4X2_types[460],  IFC4X2_types[461],
       IFC4X2_types[462],  IFC4X2_types[463],  IFC4X2_types[464],
       IFC4X2_types[465],  IFC4X2_types[466],  IFC4X2_types[467],
       IFC4X2_types[468],  IFC4X2_types[469],  IFC4X2_types[470],
       IFC4X2_types[471],  IFC4X2_types[472],  IFC4X2_types[473],
       IFC4X2_types[474],  IFC4X2_types[475],  IFC4X2_types[476],
       IFC4X2_types[477],  IFC4X2_types[478],  IFC4X2_types[479],
       IFC4X2_types[480],  IFC4X2_types[481],  IFC4X2_types[482],
       IFC4X2_types[483],  IFC4X2_types[484],  IFC4X2_types[485],
       IFC4X2_types[486],  IFC4X2_types[487],  IFC4X2_types[488],
       IFC4X2_types[489],  IFC4X2_types[490],  IFC4X2_types[491],
       IFC4X2_types[492],  IFC4X2_types[493],  IFC4X2_types[494],
       IFC4X2_types[495],  IFC4X2_types[496],  IFC4X2_types[497],
       IFC4X2_types[498],  IFC4X2_types[499],  IFC4X2_types[500],
       IFC4X2_types[501],  IFC4X2_types[502],  IFC4X2_types[503],
       IFC4X2_types[504],  IFC4X2_types[505],  IFC4X2_types[506],
       IFC4X2_types[507],  IFC4X2_types[508],  IFC4X2_types[509],
       IFC4X2_types[510],  IFC4X2_types[511],  IFC4X2_types[512],
       IFC4X2_types[513],  IFC4X2_types[514],  IFC4X2_types[515],
       IFC4X2_types[516],  IFC4X2_types[517],  IFC4X2_types[518],
       IFC4X2_types[519],  IFC4X2_types[520],  IFC4X2_types[521],
       IFC4X2_types[522],  IFC4X2_types[523],  IFC4X2_types[524],
       IFC4X2_types[525],  IFC4X2_types[526],  IFC4X2_types[527],
       IFC4X2_types[528],  IFC4X2_types[529],  IFC4X2_types[530],
       IFC4X2_types[531],  IFC4X2_types[532],  IFC4X2_types[533],
       IFC4X2_types[534],  IFC4X2_types[535],  IFC4X2_types[536],
       IFC4X2_types[537],  IFC4X2_types[538],  IFC4X2_types[539],
       IFC4X2_types[540],  IFC4X2_types[541],  IFC4X2_types[542],
       IFC4X2_types[543],  IFC4X2_types[544],  IFC4X2_types[545],
       IFC4X2_types[546],  IFC4X2_types[547],  IFC4X2_types[548],
       IFC4X2_types[549],  IFC4X2_types[550],  IFC4X2_types[551],
       IFC4X2_types[552],  IFC4X2_types[553],  IFC4X2_types[554],
       IFC4X2_types[555],  IFC4X2_types[556],  IFC4X2_types[557],
       IFC4X2_types[558],  IFC4X2_types[559],  IFC4X2_types[560],
       IFC4X2_types[561],  IFC4X2_types[562],  IFC4X2_types[563],
       IFC4X2_types[564],  IFC4X2_types[565],  IFC4X2_types[566],
       IFC4X2_types[567],  IFC4X2_types[568],  IFC4X2_types[569],
       IFC4X2_types[570],  IFC4X2_types[571],  IFC4X2_types[572],
       IFC4X2_types[573],  IFC4X2_types[574],  IFC4X2_types[575],
       IFC4X2_types[576],  IFC4X2_types[577],  IFC4X2_types[578],
       IFC4X2_types[579],  IFC4X2_types[580],  IFC4X2_types[581],
       IFC4X2_types[582],  IFC4X2_types[583],  IFC4X2_types[584],
       IFC4X2_types[585],  IFC4X2_types[586],  IFC4X2_types[587],
       IFC4X2_types[588],  IFC4X2_types[589],  IFC4X2_types[590],
       IFC4X2_types[591],  IFC4X2_types[592],  IFC4X2_types[593],
       IFC4X2_types[594],  IFC4X2_types[595],  IFC4X2_types[596],
       IFC4X2_types[597],  IFC4X2_types[598],  IFC4X2_types[599],
       IFC4X2_types[600],  IFC4X2_types[601],  IFC4X2_types[602],
       IFC4X2_types[603],  IFC4X2_types[604],  IFC4X2_types[605],
       IFC4X2_types[606],  IFC4X2_types[607],  IFC4X2_types[608],
       IFC4X2_types[609],  IFC4X2_types[610],  IFC4X2_types[611],
       IFC4X2_types[612],  IFC4X2_types[613],  IFC4X2_types[614],
       IFC4X2_types[615],  IFC4X2_types[616],  IFC4X2_types[617],
       IFC4X2_types[618],  IFC4X2_types[619],  IFC4X2_types[620],
       IFC4X2_types[621],  IFC4X2_types[622],  IFC4X2_types[623],
       IFC4X2_types[624],  IFC4X2_types[625],  IFC4X2_types[626],
       IFC4X2_types[627],  IFC4X2_types[628],  IFC4X2_types[629],
       IFC4X2_types[630],  IFC4X2_types[631],  IFC4X2_types[632],
       IFC4X2_types[633],  IFC4X2_types[634],  IFC4X2_types[635],
       IFC4X2_types[636],  IFC4X2_types[637],  IFC4X2_types[638],
       IFC4X2_types[639],  IFC4X2_types[640],  IFC4X2_types[641],
       IFC4X2_types[642],  IFC4X2_types[643],  IFC4X2_types[644],
       IFC4X2_types[645],  IFC4X2_types[646],  IFC4X2_types[647],
       IFC4X2_types[648],  IFC4X2_types[649],  IFC4X2_types[650],
       IFC4X2_types[651],  IFC4X2_types[652],  IFC4X2_types[653],
       IFC4X2_types[654],  IFC4X2_types[655],  IFC4X2_types[656],
       IFC4X2_types[657],  IFC4X2_types[658],  IFC4X2_types[659],
       IFC4X2_types[660],  IFC4X2_types[661],  IFC4X2_types[662],
       IFC4X2_types[663],  IFC4X2_types[664],  IFC4X2_types[665],
       IFC4X2_types[666],  IFC4X2_types[667],  IFC4X2_types[668],
       IFC4X2_types[669],  IFC4X2_types[670],  IFC4X2_types[671],
       IFC4X2_types[672],  IFC4X2_types[673],  IFC4X2_types[674],
       IFC4X2_types[675],  IFC4X2_types[676],  IFC4X2_types[677],
       IFC4X2_types[678],  IFC4X2_types[679],  IFC4X2_types[680],
       IFC4X2_types[681],  IFC4X2_types[682],  IFC4X2_types[683],
       IFC4X2_types[684],  IFC4X2_types[685],  IFC4X2_types[686],
       IFC4X2_types[687],  IFC4X2_types[688],  IFC4X2_types[689],
       IFC4X2_types[690],  IFC4X2_types[691],  IFC4X2_types[692],
       IFC4X2_types[693],  IFC4X2_types[694],  IFC4X2_types[695],
       IFC4X2_types[696],  IFC4X2_types[697],  IFC4X2_types[698],
       IFC4X2_types[699],  IFC4X2_types[700],  IFC4X2_types[701],
       IFC4X2_types[702],  IFC4X2_types[703],  IFC4X2_types[704],
       IFC4X2_types[705],  IFC4X2_types[706],  IFC4X2_types[707],
       IFC4X2_types[708],  IFC4X2_types[709],  IFC4X2_types[710],
       IFC4X2_types[711],  IFC4X2_types[712],  IFC4X2_types[713],
       IFC4X2_types[714],  IFC4X2_types[715],  IFC4X2_types[716],
       IFC4X2_types[717],  IFC4X2_types[718],  IFC4X2_types[719],
       IFC4X2_types[720],  IFC4X2_types[721],  IFC4X2_types[722],
       IFC4X2_types[723],  IFC4X2_types[724],  IFC4X2_types[725],
       IFC4X2_types[726],  IFC4X2_types[727],  IFC4X2_types[728],
       IFC4X2_types[729],  IFC4X2_types[730],  IFC4X2_types[731],
       IFC4X2_types[732],  IFC4X2_types[733],  IFC4X2_types[734],
       IFC4X2_types[735],  IFC4X2_types[736],  IFC4X2_types[737],
       IFC4X2_types[738],  IFC4X2_types[739],  IFC4X2_types[740],
       IFC4X2_types[741],  IFC4X2_types[742],  IFC4X2_types[743],
       IFC4X2_types[744],  IFC4X2_types[745],  IFC4X2_types[746],
       IFC4X2_types[747],  IFC4X2_types[748],  IFC4X2_types[749],
       IFC4X2_types[750],  IFC4X2_types[751],  IFC4X2_types[752],
       IFC4X2_types[753],  IFC4X2_types[754],  IFC4X2_types[755],
       IFC4X2_types[756],  IFC4X2_types[757],  IFC4X2_types[758],
       IFC4X2_types[759],  IFC4X2_types[760],  IFC4X2_types[761],
       IFC4X2_types[762],  IFC4X2_types[763],  IFC4X2_types[764],
       IFC4X2_types[765],  IFC4X2_types[766],  IFC4X2_types[767],
       IFC4X2_types[768],  IFC4X2_types[769],  IFC4X2_types[770],
       IFC4X2_types[771],  IFC4X2_types[772],  IFC4X2_types[773],
       IFC4X2_types[774],  IFC4X2_types[775],  IFC4X2_types[776],
       IFC4X2_types[777],  IFC4X2_types[778],  IFC4X2_types[779],
       IFC4X2_types[780],  IFC4X2_types[781],  IFC4X2_types[782],
       IFC4X2_types[783],  IFC4X2_types[784],  IFC4X2_types[785],
       IFC4X2_types[786],  IFC4X2_types[787],  IFC4X2_types[788],
       IFC4X2_types[789],  IFC4X2_types[790],  IFC4X2_types[791],
       IFC4X2_types[792],  IFC4X2_types[793],  IFC4X2_types[794],
       IFC4X2_types[795],  IFC4X2_types[796],  IFC4X2_types[797],
       IFC4X2_types[798],  IFC4X2_types[799],  IFC4X2_types[800],
       IFC4X2_types[801],  IFC4X2_types[802],  IFC4X2_types[803],
       IFC4X2_types[804],  IFC4X2_types[805],  IFC4X2_types[806],
       IFC4X2_types[807],  IFC4X2_types[808],  IFC4X2_types[809],
       IFC4X2_types[810],  IFC4X2_types[811],  IFC4X2_types[812],
       IFC4X2_types[813],  IFC4X2_types[814],  IFC4X2_types[815],
       IFC4X2_types[816],  IFC4X2_types[817],  IFC4X2_types[818],
       IFC4X2_types[819],  IFC4X2_types[820],  IFC4X2_types[821],
       IFC4X2_types[822],  IFC4X2_types[823],  IFC4X2_types[824],
       IFC4X2_types[825],  IFC4X2_types[826],  IFC4X2_types[827],
       IFC4X2_types[828],  IFC4X2_types[829],  IFC4X2_types[830],
       IFC4X2_types[831],  IFC4X2_types[832],  IFC4X2_types[833],
       IFC4X2_types[834],  IFC4X2_types[835],  IFC4X2_types[836],
       IFC4X2_types[837],  IFC4X2_types[838],  IFC4X2_types[839],
       IFC4X2_types[840],  IFC4X2_types[841],  IFC4X2_types[842],
       IFC4X2_types[843],  IFC4X2_types[844],  IFC4X2_types[845],
       IFC4X2_types[846],  IFC4X2_types[847],  IFC4X2_types[848],
       IFC4X2_types[849],  IFC4X2_types[850],  IFC4X2_types[851],
       IFC4X2_types[852],  IFC4X2_types[853],  IFC4X2_types[854],
       IFC4X2_types[855],  IFC4X2_types[856],  IFC4X2_types[857],
       IFC4X2_types[858],  IFC4X2_types[859],  IFC4X2_types[860],
       IFC4X2_types[861],  IFC4X2_types[862],  IFC4X2_types[863],
       IFC4X2_types[864],  IFC4X2_types[865],  IFC4X2_types[866],
       IFC4X2_types[867],  IFC4X2_types[868],  IFC4X2_types[869],
       IFC4X2_types[870],  IFC4X2_types[871],  IFC4X2_types[872],
       IFC4X2_types[873],  IFC4X2_types[874],  IFC4X2_types[875],
       IFC4X2_types[876],  IFC4X2_types[877],  IFC4X2_types[878],
       IFC4X2_types[879],  IFC4X2_types[880],  IFC4X2_types[881],
       IFC4X2_types[882],  IFC4X2_types[883],  IFC4X2_types[884],
       IFC4X2_types[885],  IFC4X2_types[886],  IFC4X2_types[887],
       IFC4X2_types[888],  IFC4X2_types[889],  IFC4X2_types[890],
       IFC4X2_types[891],  IFC4X2_types[892],  IFC4X2_types[893],
       IFC4X2_types[894],  IFC4X2_types[895],  IFC4X2_types[896],
       IFC4X2_types[897],  IFC4X2_types[898],  IFC4X2_types[899],
       IFC4X2_types[900],  IFC4X2_types[901],  IFC4X2_types[902],
       IFC4X2_types[903],  IFC4X2_types[904],  IFC4X2_types[905],
       IFC4X2_types[906],  IFC4X2_types[907],  IFC4X2_types[908],
       IFC4X2_types[909],  IFC4X2_types[910],  IFC4X2_types[911],
       IFC4X2_types[912],  IFC4X2_types[913],  IFC4X2_types[914],
       IFC4X2_types[915],  IFC4X2_types[916],  IFC4X2_types[917],
       IFC4X2_types[918],  IFC4X2_types[919],  IFC4X2_types[920],
       IFC4X2_types[921],  IFC4X2_types[922],  IFC4X2_types[923],
       IFC4X2_types[924],  IFC4X2_types[925],  IFC4X2_types[926],
       IFC4X2_types[927],  IFC4X2_types[928],  IFC4X2_types[929],
       IFC4X2_types[930],  IFC4X2_types[931],  IFC4X2_types[932],
       IFC4X2_types[933],  IFC4X2_types[934],  IFC4X2_types[935],
       IFC4X2_types[936],  IFC4X2_types[937],  IFC4X2_types[938],
       IFC4X2_types[939],  IFC4X2_types[940],  IFC4X2_types[941],
       IFC4X2_types[942],  IFC4X2_types[943],  IFC4X2_types[944],
       IFC4X2_types[945],  IFC4X2_types[946],  IFC4X2_types[947],
       IFC4X2_types[948],  IFC4X2_types[949],  IFC4X2_types[950],
       IFC4X2_types[951],  IFC4X2_types[952],  IFC4X2_types[953],
       IFC4X2_types[954],  IFC4X2_types[955],  IFC4X2_types[956],
       IFC4X2_types[957],  IFC4X2_types[958],  IFC4X2_types[959],
       IFC4X2_types[960],  IFC4X2_types[961],  IFC4X2_types[962],
       IFC4X2_types[963],  IFC4X2_types[964],  IFC4X2_types[965],
       IFC4X2_types[966],  IFC4X2_types[967],  IFC4X2_types[968],
       IFC4X2_types[969],  IFC4X2_types[970],  IFC4X2_types[971],
       IFC4X2_types[972],  IFC4X2_types[973],  IFC4X2_types[974],
       IFC4X2_types[975],  IFC4X2_types[976],  IFC4X2_types[977],
       IFC4X2_types[978],  IFC4X2_types[979],  IFC4X2_types[980],
       IFC4X2_types[981],  IFC4X2_types[982],  IFC4X2_types[983],
       IFC4X2_types[984],  IFC4X2_types[985],  IFC4X2_types[986],
       IFC4X2_types[987],  IFC4X2_types[988],  IFC4X2_types[989],
       IFC4X2_types[990],  IFC4X2_types[991],  IFC4X2_types[992],
       IFC4X2_types[993],  IFC4X2_types[994],  IFC4X2_types[995],
       IFC4X2_types[996],  IFC4X2_types[997],  IFC4X2_types[998],
       IFC4X2_types[999],  IFC4X2_types[1000], IFC4X2_types[1001],
       IFC4X2_types[1002], IFC4X2_types[1003], IFC4X2_types[1004],
       IFC4X2_types[1005], IFC4X2_types[1006], IFC4X2_types[1007],
       IFC4X2_types[1008], IFC4X2_types[1009], IFC4X2_types[1010],
       IFC4X2_types[1011], IFC4X2_types[1012], IFC4X2_types[1013],
       IFC4X2_types[1014], IFC4X2_types[1015], IFC4X2_types[1016],
       IFC4X2_types[1017], IFC4X2_types[1018], IFC4X2_types[1019],
       IFC4X2_types[1020], IFC4X2_types[1021], IFC4X2_types[1022],
       IFC4X2_types[1023], IFC4X2_types[1024], IFC4X2_types[1025],
       IFC4X2_types[1026], IFC4X2_types[1027], IFC4X2_types[1028],
       IFC4X2_types[1029], IFC4X2_types[1030], IFC4X2_types[1031],
       IFC4X2_types[1032], IFC4X2_types[1033], IFC4X2_types[1034],
       IFC4X2_types[1035], IFC4X2_types[1036], IFC4X2_types[1037],
       IFC4X2_types[1038], IFC4X2_types[1039], IFC4X2_types[1040],
       IFC4X2_types[1041], IFC4X2_types[1042], IFC4X2_types[1043],
       IFC4X2_types[1044], IFC4X2_types[1045], IFC4X2_types[1046],
       IFC4X2_types[1047], IFC4X2_types[1048], IFC4X2_types[1049],
       IFC4X2_types[1050], IFC4X2_types[1051], IFC4X2_types[1052],
       IFC4X2_types[1053], IFC4X2_types[1054], IFC4X2_types[1055],
       IFC4X2_types[1056], IFC4X2_types[1057], IFC4X2_types[1058],
       IFC4X2_types[1059], IFC4X2_types[1060], IFC4X2_types[1061],
       IFC4X2_types[1062], IFC4X2_types[1063], IFC4X2_types[1064],
       IFC4X2_types[1065], IFC4X2_types[1066], IFC4X2_types[1067],
       IFC4X2_types[1068], IFC4X2_types[1069], IFC4X2_types[1070],
       IFC4X2_types[1071], IFC4X2_types[1072], IFC4X2_types[1073],
       IFC4X2_types[1074], IFC4X2_types[1075], IFC4X2_types[1076],
       IFC4X2_types[1077], IFC4X2_types[1078], IFC4X2_types[1079],
       IFC4X2_types[1080], IFC4X2_types[1081], IFC4X2_types[1082],
       IFC4X2_types[1083], IFC4X2_types[1084], IFC4X2_types[1085],
       IFC4X2_types[1086], IFC4X2_types[1087], IFC4X2_types[1088],
       IFC4X2_types[1089], IFC4X2_types[1090], IFC4X2_types[1091],
       IFC4X2_types[1092], IFC4X2_types[1093], IFC4X2_types[1094],
       IFC4X2_types[1095], IFC4X2_types[1096], IFC4X2_types[1097],
       IFC4X2_types[1098], IFC4X2_types[1099], IFC4X2_types[1100],
       IFC4X2_types[1101], IFC4X2_types[1102], IFC4X2_types[1103],
       IFC4X2_types[1104], IFC4X2_types[1105], IFC4X2_types[1106],
       IFC4X2_types[1107], IFC4X2_types[1108], IFC4X2_types[1109],
       IFC4X2_types[1110], IFC4X2_types[1111], IFC4X2_types[1112],
       IFC4X2_types[1113], IFC4X2_types[1114], IFC4X2_types[1115],
       IFC4X2_types[1116], IFC4X2_types[1117], IFC4X2_types[1118],
       IFC4X2_types[1119], IFC4X2_types[1120], IFC4X2_types[1121],
       IFC4X2_types[1122], IFC4X2_types[1123], IFC4X2_types[1124],
       IFC4X2_types[1125], IFC4X2_types[1126], IFC4X2_types[1127],
       IFC4X2_types[1128], IFC4X2_types[1129], IFC4X2_types[1130],
       IFC4X2_types[1131], IFC4X2_types[1132], IFC4X2_types[1133],
       IFC4X2_types[1134], IFC4X2_types[1135], IFC4X2_types[1136],
       IFC4X2_types[1137], IFC4X2_types[1138], IFC4X2_types[1139],
       IFC4X2_types[1140], IFC4X2_types[1141], IFC4X2_types[1142],
       IFC4X2_types[1143], IFC4X2_types[1144], IFC4X2_types[1145],
       IFC4X2_types[1146], IFC4X2_types[1147], IFC4X2_types[1148],
       IFC4X2_types[1149], IFC4X2_types[1150], IFC4X2_types[1151],
       IFC4X2_types[1152], IFC4X2_types[1153], IFC4X2_types[1154],
       IFC4X2_types[1155], IFC4X2_types[1156], IFC4X2_types[1157],
       IFC4X2_types[1158], IFC4X2_types[1159], IFC4X2_types[1160],
       IFC4X2_types[1161], IFC4X2_types[1162], IFC4X2_types[1163],
       IFC4X2_types[1164], IFC4X2_types[1165], IFC4X2_types[1166],
       IFC4X2_types[1167], IFC4X2_types[1168], IFC4X2_types[1169],
       IFC4X2_types[1170], IFC4X2_types[1171], IFC4X2_types[1172],
       IFC4X2_types[1173], IFC4X2_types[1174], IFC4X2_types[1175],
       IFC4X2_types[1176], IFC4X2_types[1177], IFC4X2_types[1178],
       IFC4X2_types[1179], IFC4X2_types[1180], IFC4X2_types[1181],
       IFC4X2_types[1182], IFC4X2_types[1183], IFC4X2_types[1184],
       IFC4X2_types[1185], IFC4X2_types[1186], IFC4X2_types[1187],
       IFC4X2_types[1188], IFC4X2_types[1189], IFC4X2_types[1190],
       IFC4X2_types[1191], IFC4X2_types[1192], IFC4X2_types[1193],
       IFC4X2_types[1194], IFC4X2_types[1195], IFC4X2_types[1196],
       IFC4X2_types[1197], IFC4X2_types[1198], IFC4X2_types[1199],
       IFC4X2_types[1200], IFC4X2_types[1201], IFC4X2_types[1202],
       IFC4X2_types[1203], IFC4X2_types[1204], IFC4X2_types[1205],
       IFC4X2_types[1206], IFC4X2_types[1207], IFC4X2_types[1208],
       IFC4X2_types[1209], IFC4X2_types[1210], IFC4X2_types[1211],
       IFC4X2_types[1212], IFC4X2_types[1213], IFC4X2_types[1214],
       IFC4X2_types[1215], IFC4X2_types[1216], IFC4X2_types[1217],
       IFC4X2_types[1218], IFC4X2_types[1219], IFC4X2_types[1220],
       IFC4X2_types[1221], IFC4X2_types[1222]},
      new IFC4X2_instance_factory());
}
static std::unique_ptr<schema_definition> schema;

void Ifc4x2::clear_schema() { schema.reset(); }

const schema_definition &Ifc4x2::get_schema() {
  if (!schema) {
    schema.reset(IFC4X2_populate_schema());
  }
  return *schema;
}
