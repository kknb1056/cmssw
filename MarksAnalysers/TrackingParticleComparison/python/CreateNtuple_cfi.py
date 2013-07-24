import FWCore.ParameterSet.Config as cms

CreateNtuple = cms.EDAnalyzer('CreateNtuple',
	inputCollection = cms.InputTag("mix","MergedTrackTruth"),
	ntupleFilename = cms.string("trackingParticleTest.proto")
)