import FWCore.ParameterSet.Config as cms

nmaxPerLumi = cms.EDFiler("NMaxPerLumi",
                          nMaxPerLumi = cms.uint32(10)
                          )
