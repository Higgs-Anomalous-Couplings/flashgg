import FWCore.ParameterSet.Config as cms
from flashgg.MicroAOD.flashggJets_cfi import UnpackedJetCollectionVInputTag

flashggStageOneCombinedTag = cms.EDProducer("FlashggStageOneCombinedTagProducer",
                               DiPhotonTag=cms.InputTag('flashggPreselectedDiPhotons'),
                               SystLabel=cms.string(""),
                               MVAResultTag=cms.InputTag('flashggDiPhotonMVA'),
                               VBFMVAResultTag=cms.InputTag('flashggVBFMVA'),
                               VHhadMVAResultTag=cms.InputTag('flashggVHhadMVA'),
                               GluGluHMVAResultTag=cms.InputTag('flashggGluGluHMVA'),
                               useMultiClass=cms.bool(True),
                               inputTagJets = UnpackedJetCollectionVInputTag,
                               rawDiphoBounds = cms.vdouble(),
                               rawDijetBounds = cms.vdouble(),
                               rawVhHadBounds = cms.vdouble(),
                               rawVbfpBSMBounds = cms.vdouble(),
                               rawVbfpBKGBounds = cms.vdouble(),
                               rawVbfpD0MBounds = cms.vdouble(),                                            
                               )
