#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"

#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/ZHLeptonicTag.h"
#include "flashgg/DataFormats/interface/Electron.h"
#include "flashgg/DataFormats/interface/Muon.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "flashgg/Taggers/interface/LeptonSelection.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "flashgg/DataFormats/interface/VHTagTruth.h"
#include "DataFormats/Common/interface/RefToPtr.h"

#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TMath.h"
#include "TMVA/Reader.h"

using namespace std;
using namespace edm;


namespace flashgg {
    class ZHLeptonicTagProducer : public EDProducer
    {

    public:
        ZHLeptonicTagProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        int chooseACCategory( float stxs_mva, float ac_mva );

        EDGetTokenT<View<DiPhotonCandidate> > diPhotonToken_;
        EDGetTokenT<View<flashgg::Electron> > electronToken_;
        EDGetTokenT<View<flashgg::Muon> > muonToken_;
        std::vector<edm::EDGetTokenT<View<flashgg::Jet> > > tokenJets_;
        std::vector<edm::InputTag> inputTagJets_;
        EDGetTokenT<View<reco::Vertex> > vertexToken_;
        EDGetTokenT<double> rhoTag_;
        EDGetTokenT<View<DiPhotonMVAResult> > mvaResultToken_;
        EDGetTokenT<View<reco::GenParticle> > genParticleToken_;
        string systLabel_;

        typedef std::vector<edm::Handle<edm::View<flashgg::Jet> > > JetCollectionVector;        
        
        //Thresholds
        double leadPhoOverMassThreshold_      ;
        double subleadPhoOverMassThreshold_   ;
        double MVAThreshold_                  ;
        double PhoMVAThreshold_               ;
        double electronPtThreshold_           ;
        double invMassLepLowThreshold_        ;
        double invMassLepHighThreshold_       ;
        vector<double> electronEtaThresholds_ ;
        double DeltaRTrkElec_                 ;
        double deltaRPhoElectronThreshold_    ;
        double deltaMassElectronZThreshold_   ;
        double muonPtThreshold_               ;
        double muonEtaThreshold_              ; 
        double deltaRMuonPhoThreshold_        ;
        double muPFIsoSumRelThreshold_        ;
        double jetPtThreshold_                ;
        double jetEtaThreshold_               ;
        double deltaRJetPhoThreshold_         ;
        double deltaRJetLepThreshold_         ;


        //$$$$$$$$$$$ Declaration for AC MVA Variables $$$$$$$$$$$$$$$$$$$
        unique_ptr<TMVA::Reader> ZHiggs0MToGG_MVA_;
        unique_ptr<TMVA::Reader> ZHiggs0PHToGG_MVA_;
        unique_ptr<TMVA::Reader> ZHiggs0L1ToGG_MVA_;
        
        
        float _Anom_MVA_pho1_eta;
        float _Anom_MVA_pho1_phi;
        float _Anom_MVA_pho1_full5x5_r9;
        float _Anom_MVA_pho1_idmva;
        float _Anom_MVA_pho2_eta;
        float _Anom_MVA_pho2_phi;
        float _Anom_MVA_pho2_full5x5_r9;
        float _Anom_MVA_pho2_idmva;
        float _Anom_MVA_pho1_ptOverMgg;
        float _Anom_MVA_pho2_ptOverMgg;


        float _Anom_MVA_mu1_pt;
        float _Anom_MVA_mu1_phi;
        float _Anom_MVA_mu1_eta;
        float _Anom_MVA_mu1_energy;
        float _Anom_MVA_mu2_pt;
        float _Anom_MVA_mu2_phi;
        float _Anom_MVA_mu2_eta;
        float _Anom_MVA_mu2_energy;


        float _Anom_MVA_ele1_pt;
        float _Anom_MVA_ele1_phi;
        float _Anom_MVA_ele1_eta;
        float _Anom_MVA_ele1_energy;

        float _Anom_MVA_ele2_pt;
        float _Anom_MVA_ele2_phi;
        float _Anom_MVA_ele2_eta;
        float _Anom_MVA_ele2_energy;

        float _Anom_MVA_jet1_pt;
        float _Anom_MVA_jet1_phi;
        float _Anom_MVA_jet1_eta;
        float _Anom_MVA_jet1_energy;
        float _Anom_MVA_jet2_pt;
        float _Anom_MVA_jet2_phi;
        float _Anom_MVA_jet2_eta;
        float _Anom_MVA_jet2_energy;


        float _Anom_MVA_cosPhiGG;
        float _Anom_MVA_cosPhiG1_Mu1;
        float _Anom_MVA_cosPhiG1_Mu2;

        float _Anom_MVA_cosPhiG1_Ele1;
        float _Anom_MVA_cosPhiG1_Ele2;

        float _Anom_MVA_cosPhiG2_Mu1;
        float _Anom_MVA_cosPhiG2_Mu2;

        float _Anom_MVA_cosPhiG2_Ele1;
        float _Anom_MVA_cosPhiG2_Ele2;


        float _Anom_MVA_dR_Pho1Ele1_wh;
        float _Anom_MVA_dR_Pho1Ele2_wh;


        float _Anom_MVA_dR_Pho2Ele1_wh;
        float _Anom_MVA_dR_Pho2Ele2_wh;

        float _Anom_MVA_dR_Pho1Mu1_wh;
        float _Anom_MVA_dR_Pho1Mu2_wh;

        float _Anom_MVA_dR_Pho2Mu1_wh;
        float _Anom_MVA_dR_Pho2Mu2_wh;

        float _Anom_MVA_dR_Pho1Jet1_wh;
        float _Anom_MVA_dR_Pho2Jet1_wh;
        float _Anom_MVA_dR_Pho1Jet2_wh;
        float _Anom_MVA_dR_Pho2Jet2_wh;

        float _Anom_MVA_dR_Mu1Jet1_wh;
        float _Anom_MVA_dR_Mu1Jet2_wh;
        float _Anom_MVA_dR_Ele1Jet1_wh;
        float _Anom_MVA_dR_Ele1Jet2_wh;



        FileInPath ZHiggs0MToGG_weights_;
        FileInPath ZHiggs0PHToGG_weights_;
        FileInPath ZHiggs0L1ToGG_weights_;


        //$$$$$$$$$$$ End of Declaration for AC MVA Variables $$$$$$$$$$$$$$$$$$$


        //ZHMVA
        unique_ptr<TMVA::Reader>ZHMva_;

        float _pho1_eta         ; 
        float _pho2_eta         ; 
        float _pho1_ptoM        ; 
        float _pho2_ptoM        ; 
        float _min_phoId        ; 
        float _max_phoId        ; 
        float _cosdphi_dipho    ; 
        float _lep1_pt          ; 
        float _lep2_pt          ;
        float _lep1_eta         ; 
        float _lep2_eta         ; 
        float _dr_pho1_lep1     ; 
        float _dr_pho1_lep2     ; 
        float _dr_pho2_lep1     ; 
        float _dr_pho2_lep2     ; 
        float _dilep_mass       ; 
        float _cosdphi_dilep    ; 
        float _dphi_dipho_dilep ; 
        float _pt_balance       ; 
        float _njet             ; 
        float _max_jet_pt       ; 
        float _max_jet_dCSV     ; 
        float _leptonType       ; 
 
        FileInPath ZHMVAweightfile_ ;

        vector<double> boundaries;
        vector<double> acBoundaries;


    };

    ZHLeptonicTagProducer::ZHLeptonicTagProducer( const ParameterSet &iConfig ) :
        diPhotonToken_( consumes<View<flashgg::DiPhotonCandidate> >( iConfig.getParameter<InputTag> ( "DiPhotonTag" ) ) ),
        electronToken_( consumes<View<flashgg::Electron> >( iConfig.getParameter<InputTag> ( "ElectronTag" ) ) ),
        muonToken_( consumes<View<flashgg::Muon> >( iConfig.getParameter<InputTag>( "MuonTag" ) ) ),
        inputTagJets_( iConfig.getParameter<std::vector<edm::InputTag> >( "inputTagJets" ) ),
        vertexToken_( consumes<View<reco::Vertex> >( iConfig.getParameter<InputTag> ( "VertexTag" ) ) ),
        rhoTag_( consumes<double>( iConfig.getParameter<InputTag>( "rhoTag" ) ) ),
        mvaResultToken_( consumes<View<flashgg::DiPhotonMVAResult> >( iConfig.getParameter<InputTag> ( "MVAResultTag" ) ) ),
        genParticleToken_( consumes<View<reco::GenParticle> >( iConfig.getParameter<InputTag> ( "GenParticleTag" ) ) ),
        systLabel_( iConfig.getParameter<string> ( "SystLabel" ) )
    {
        //Photon
        leadPhoOverMassThreshold_    = iConfig.getParameter<double>("leadPhoOverMassThreshold");
        subleadPhoOverMassThreshold_ = iConfig.getParameter<double>("subleadPhoOverMassThreshold");
        MVAThreshold_                = iConfig.getParameter<double>("MVAThreshold");
        PhoMVAThreshold_             = iConfig.getParameter<double>("PhoMVAThreshold");

        //Lepton
        invMassLepLowThreshold_      = iConfig.getParameter<double>("invMassLepLowThreshold");
        invMassLepHighThreshold_     = iConfig.getParameter<double>("invMassLepHighThreshold");

        //Electron
        electronPtThreshold_         = iConfig.getParameter<double>( "electronPtThreshold");
        electronEtaThresholds_       = iConfig.getParameter<vector<double > >( "electronEtaThresholds");
        DeltaRTrkElec_               = iConfig.getParameter<double>("DeltaRTrkElec");
        deltaRPhoElectronThreshold_  = iConfig.getParameter<double>("deltaRPhoElectronThreshold");
        deltaMassElectronZThreshold_ = iConfig.getParameter<double>("deltaMassElectronZThreshold");

        //Muon
        muonPtThreshold_             = iConfig.getParameter<double>("muonPtThreshold");
        muonEtaThreshold_            = iConfig.getParameter<double>("muonEtaThreshold");
        deltaRMuonPhoThreshold_      = iConfig.getParameter<double>("deltaRMuonPhoThreshold");
        muPFIsoSumRelThreshold_      = iConfig.getParameter<double>("muPFIsoSumRelThreshold");

        //Jet
        jetPtThreshold_              = iConfig.getParameter<double>("jetPtThreshold"); 
        jetEtaThreshold_             = iConfig.getParameter<double>("jetEtaThreshold");      
        deltaRJetPhoThreshold_       = iConfig.getParameter<double>("deltaRJetPhoThreshold");
        deltaRJetLepThreshold_       = iConfig.getParameter<double>("deltaRJetLepThreshold");

        for (unsigned i = 0 ; i < inputTagJets_.size() ; i++) {
            auto token = consumes<View<flashgg::Jet> >(inputTagJets_[i]);
            tokenJets_.push_back(token);
        }

        // $$$$$$$$$$$$$$$$$$$$$$ AC MVA Variable Initializations $$$$$$$$$$$$$$$$$$$$$$
        //Loading weights for AC-MVA weights file
        ZHiggs0MToGG_weights_           = iConfig.getParameter<edm::FileInPath>( "ZHiggs0MToGG_weights" );     
        ZHiggs0PHToGG_weights_          = iConfig.getParameter<edm::FileInPath>( "ZHiggs0PHToGG_weights" );      
        ZHiggs0L1ToGG_weights_          = iConfig.getParameter<edm::FileInPath>( "ZHiggs0L1ToGG_weights" );   
        _Anom_MVA_pho1_eta = -999;
        _Anom_MVA_pho1_phi = -999;
        _Anom_MVA_pho1_full5x5_r9 = -999;
        _Anom_MVA_pho1_idmva = -999;
        _Anom_MVA_pho1_ptOverMgg = -999;
        _Anom_MVA_pho2_eta = -999;
        _Anom_MVA_pho2_phi = -999;
        _Anom_MVA_pho2_full5x5_r9 = -999;
        _Anom_MVA_pho2_idmva = -999;
        _Anom_MVA_pho2_ptOverMgg = -999;
        _Anom_MVA_mu1_pt = -999;
        _Anom_MVA_mu1_phi = -999;
        _Anom_MVA_mu1_eta = -999;
        _Anom_MVA_mu1_energy = -999;
        _Anom_MVA_mu2_pt = -999;
        _Anom_MVA_mu2_phi = -999;
        _Anom_MVA_mu2_eta = -999;
        _Anom_MVA_mu2_energy = -999;
        _Anom_MVA_ele1_pt = -999;
        _Anom_MVA_ele1_phi = -999;
        _Anom_MVA_ele1_eta = -999;
        _Anom_MVA_ele1_energy = -999;
        _Anom_MVA_ele2_pt = -999;
        _Anom_MVA_ele2_phi = -999;
        _Anom_MVA_ele2_eta = -999;
        _Anom_MVA_ele2_energy = -999;
        _Anom_MVA_jet1_pt = -999;
        _Anom_MVA_jet1_phi = -999;
        _Anom_MVA_jet1_eta = -999;
        _Anom_MVA_jet1_energy = -999;
        _Anom_MVA_jet2_pt = -999;
        _Anom_MVA_jet2_phi = -999;
        _Anom_MVA_jet2_eta = -999;
        _Anom_MVA_jet2_energy = -999;
        _Anom_MVA_cosPhiGG = -999;
        _Anom_MVA_cosPhiG1_Mu1 = -999;
        _Anom_MVA_cosPhiG1_Mu2 = -999;
        _Anom_MVA_cosPhiG1_Ele1 = -999;
        _Anom_MVA_cosPhiG1_Ele2 = -999;
        _Anom_MVA_cosPhiG2_Mu1 = -999;
        _Anom_MVA_cosPhiG2_Mu2 = -999;
        _Anom_MVA_cosPhiG2_Ele1 = -999;
        _Anom_MVA_cosPhiG2_Ele2 = -999;
        _Anom_MVA_dR_Pho1Ele1_wh = -999;
        _Anom_MVA_dR_Pho1Ele2_wh = -999;
        _Anom_MVA_dR_Pho2Ele1_wh = -999;
        _Anom_MVA_dR_Pho2Ele2_wh = -999;
        _Anom_MVA_dR_Pho1Mu1_wh = -999;
        _Anom_MVA_dR_Pho1Mu2_wh = -999;
        _Anom_MVA_dR_Pho2Mu1_wh = -999;
        _Anom_MVA_dR_Pho2Mu2_wh = -999;
        _Anom_MVA_dR_Pho1Jet1_wh = -999;
        _Anom_MVA_dR_Pho2Jet1_wh = -999;
        _Anom_MVA_dR_Pho1Jet2_wh = -999;
        _Anom_MVA_dR_Pho2Jet2_wh = -999;
        _Anom_MVA_dR_Mu1Jet1_wh = -999;
        _Anom_MVA_dR_Mu1Jet2_wh = -999;
        _Anom_MVA_dR_Ele1Jet1_wh = -999;
        _Anom_MVA_dR_Ele1Jet2_wh = -999;



        ZHiggs0MToGG_MVA_.reset( new TMVA::Reader( "!Color:!Silent" ) );
        ZHiggs0MToGG_MVA_->AddVariable( "cosPhiG1_Ele1",&_Anom_MVA_cosPhiG1_Ele1);
        ZHiggs0MToGG_MVA_->AddVariable( "cosPhiG1_Ele2",&_Anom_MVA_cosPhiG1_Ele2);
        ZHiggs0MToGG_MVA_->AddVariable( "cosPhiG1_Mu1",&_Anom_MVA_cosPhiG1_Mu1);
        ZHiggs0MToGG_MVA_->AddVariable( "cosPhiG1_Mu2",&_Anom_MVA_cosPhiG1_Mu2);
        ZHiggs0MToGG_MVA_->AddVariable( "cosPhiG2_Mu2",&_Anom_MVA_cosPhiG2_Mu2);
        ZHiggs0MToGG_MVA_->AddVariable( "cosPhiGG",&_Anom_MVA_cosPhiGG);
        ZHiggs0MToGG_MVA_->AddVariable( "dR_Pho1Ele1_wh",&_Anom_MVA_dR_Pho1Ele1_wh);
        ZHiggs0MToGG_MVA_->AddVariable( "dR_Pho1Mu1_wh",&_Anom_MVA_dR_Pho1Mu1_wh);
        ZHiggs0MToGG_MVA_->AddVariable( "dR_Pho1Mu2_wh",&_Anom_MVA_dR_Pho1Mu2_wh);
        ZHiggs0MToGG_MVA_->AddVariable( "dR_Pho2Ele1_wh",&_Anom_MVA_dR_Pho2Ele1_wh);
        ZHiggs0MToGG_MVA_->AddVariable( "dR_Pho2Mu1_wh",&_Anom_MVA_dR_Pho2Mu1_wh);
        ZHiggs0MToGG_MVA_->AddVariable( "ele1_energy",&_Anom_MVA_ele1_energy);
        ZHiggs0MToGG_MVA_->AddVariable( "ele1_pt",&_Anom_MVA_ele1_pt);
        ZHiggs0MToGG_MVA_->AddVariable( "ele2_pt",&_Anom_MVA_ele2_pt);
        ZHiggs0MToGG_MVA_->AddVariable( "mu1_energy",&_Anom_MVA_mu1_energy);
        ZHiggs0MToGG_MVA_->AddVariable( "mu1_pt",&_Anom_MVA_mu1_pt);
        ZHiggs0MToGG_MVA_->AddVariable( "mu2_phi",&_Anom_MVA_mu2_phi);
        ZHiggs0MToGG_MVA_->AddVariable( "mu2_pt",&_Anom_MVA_mu2_pt);
        ZHiggs0MToGG_MVA_->AddVariable( "pho1_eta",&_Anom_MVA_pho1_eta);
        ZHiggs0MToGG_MVA_->AddVariable( "pho1_ptOverMgg",&_Anom_MVA_pho1_ptOverMgg);
        ZHiggs0MToGG_MVA_->AddVariable( "pho2_phi",&_Anom_MVA_pho2_phi);
        ZHiggs0MToGG_MVA_->AddVariable( "pho2_ptOverMgg",&_Anom_MVA_pho2_ptOverMgg);
        ZHiggs0MToGG_MVA_->BookMVA( "BDT", ZHiggs0MToGG_weights_.fullPath() );


        ZHiggs0PHToGG_MVA_.reset( new TMVA::Reader( "!Color:!Silent" ) );
        ZHiggs0PHToGG_MVA_->AddVariable( "cosPhiG1_Ele1",&_Anom_MVA_cosPhiG1_Ele1);
        ZHiggs0PHToGG_MVA_->AddVariable( "cosPhiG1_Ele2",&_Anom_MVA_cosPhiG1_Ele2);
        ZHiggs0PHToGG_MVA_->AddVariable( "cosPhiG1_Mu1",&_Anom_MVA_cosPhiG1_Mu1);
        ZHiggs0PHToGG_MVA_->AddVariable( "cosPhiG1_Mu2",&_Anom_MVA_cosPhiG1_Mu2);
        ZHiggs0PHToGG_MVA_->AddVariable( "cosPhiG2_Mu2",&_Anom_MVA_cosPhiG2_Mu2);
        ZHiggs0PHToGG_MVA_->AddVariable( "cosPhiGG",&_Anom_MVA_cosPhiGG);
        ZHiggs0PHToGG_MVA_->AddVariable( "dR_Pho1Ele1_wh",&_Anom_MVA_dR_Pho1Ele1_wh);
        ZHiggs0PHToGG_MVA_->AddVariable( "dR_Pho1Mu1_wh",&_Anom_MVA_dR_Pho1Mu1_wh);
        ZHiggs0PHToGG_MVA_->AddVariable( "dR_Pho1Mu2_wh",&_Anom_MVA_dR_Pho1Mu2_wh);
        ZHiggs0PHToGG_MVA_->AddVariable( "dR_Pho2Ele1_wh",&_Anom_MVA_dR_Pho2Ele1_wh);
        ZHiggs0PHToGG_MVA_->AddVariable( "dR_Pho2Mu1_wh",&_Anom_MVA_dR_Pho2Mu1_wh);
        ZHiggs0PHToGG_MVA_->AddVariable( "ele1_energy",&_Anom_MVA_ele1_energy);
        ZHiggs0PHToGG_MVA_->AddVariable( "ele1_pt",&_Anom_MVA_ele1_pt);
        ZHiggs0PHToGG_MVA_->AddVariable( "ele2_pt",&_Anom_MVA_ele2_pt);
        ZHiggs0PHToGG_MVA_->AddVariable( "mu1_energy",&_Anom_MVA_mu1_energy);
        ZHiggs0PHToGG_MVA_->AddVariable( "mu1_pt",&_Anom_MVA_mu1_pt);
        ZHiggs0PHToGG_MVA_->AddVariable( "mu2_phi",&_Anom_MVA_mu2_phi);
        ZHiggs0PHToGG_MVA_->AddVariable( "mu2_pt",&_Anom_MVA_mu2_pt);
        ZHiggs0PHToGG_MVA_->AddVariable( "pho1_eta",&_Anom_MVA_pho1_eta);
        ZHiggs0PHToGG_MVA_->AddVariable( "pho1_ptOverMgg",&_Anom_MVA_pho1_ptOverMgg);
        ZHiggs0PHToGG_MVA_->AddVariable( "pho2_phi",&_Anom_MVA_pho2_phi);
        ZHiggs0PHToGG_MVA_->AddVariable( "pho2_ptOverMgg",&_Anom_MVA_pho2_ptOverMgg); 
        ZHiggs0PHToGG_MVA_->BookMVA( "BDT", ZHiggs0PHToGG_weights_.fullPath() );


        ZHiggs0L1ToGG_MVA_.reset( new TMVA::Reader( "!Color:!Silent" ) );
        ZHiggs0L1ToGG_MVA_->AddVariable( "cosPhiG1_Ele1",&_Anom_MVA_cosPhiG1_Ele1);
        ZHiggs0L1ToGG_MVA_->AddVariable( "cosPhiG1_Ele2",&_Anom_MVA_cosPhiG1_Ele2);
        ZHiggs0L1ToGG_MVA_->AddVariable( "cosPhiG1_Mu1",&_Anom_MVA_cosPhiG1_Mu1);
        ZHiggs0L1ToGG_MVA_->AddVariable( "cosPhiG1_Mu2",&_Anom_MVA_cosPhiG1_Mu2);
        ZHiggs0L1ToGG_MVA_->AddVariable( "cosPhiG2_Mu2",&_Anom_MVA_cosPhiG2_Mu2);
        ZHiggs0L1ToGG_MVA_->AddVariable( "cosPhiGG",&_Anom_MVA_cosPhiGG);
        ZHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho1Ele1_wh",&_Anom_MVA_dR_Pho1Ele1_wh);
        ZHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho1Mu1_wh",&_Anom_MVA_dR_Pho1Mu1_wh);
        ZHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho1Mu2_wh",&_Anom_MVA_dR_Pho1Mu2_wh);
        ZHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho2Ele1_wh",&_Anom_MVA_dR_Pho2Ele1_wh);
        ZHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho2Mu1_wh",&_Anom_MVA_dR_Pho2Mu1_wh);
        ZHiggs0L1ToGG_MVA_->AddVariable( "ele1_energy",&_Anom_MVA_ele1_energy);
        ZHiggs0L1ToGG_MVA_->AddVariable( "ele1_pt",&_Anom_MVA_ele1_pt);
        ZHiggs0L1ToGG_MVA_->AddVariable( "ele2_pt",&_Anom_MVA_ele2_pt);
        ZHiggs0L1ToGG_MVA_->AddVariable( "mu1_energy",&_Anom_MVA_mu1_energy);
        ZHiggs0L1ToGG_MVA_->AddVariable( "mu1_pt",&_Anom_MVA_mu1_pt);
        ZHiggs0L1ToGG_MVA_->AddVariable( "mu2_phi",&_Anom_MVA_mu2_phi);
        ZHiggs0L1ToGG_MVA_->AddVariable( "mu2_pt",&_Anom_MVA_mu2_pt);
        ZHiggs0L1ToGG_MVA_->AddVariable( "pho1_eta",&_Anom_MVA_pho1_eta);
        ZHiggs0L1ToGG_MVA_->AddVariable( "pho1_ptOverMgg",&_Anom_MVA_pho1_ptOverMgg);
        ZHiggs0L1ToGG_MVA_->AddVariable( "pho2_phi",&_Anom_MVA_pho2_phi);
        ZHiggs0L1ToGG_MVA_->AddVariable( "pho2_ptOverMgg",&_Anom_MVA_pho2_ptOverMgg);   
        ZHiggs0L1ToGG_MVA_->BookMVA( "BDT", ZHiggs0L1ToGG_weights_.fullPath() );

        // $$$$$$$$$$$$$$$$$$$$$$ End of AC MVA Variable Initializations $$$$$$$$$$$$$$$$$$$$$$

        //ZHMVA
        ZHMVAweightfile_ = iConfig.getParameter<edm::FileInPath>( "ZHMVAweightfile" );

        _pho1_eta         = -999.; 
        _pho2_eta         = -999.; 
        _pho1_ptoM        = -999.; 
        _pho2_ptoM        = -999.; 
        _min_phoId        = -999.; 
        _max_phoId        = -999.; 
        _cosdphi_dipho    = -999.; 
        _lep1_pt          = -999.; 
        _lep2_pt          = -999.; 
        _lep1_eta         = -999.; 
        _lep2_eta         = -999.; 
        _dr_pho1_lep1     = -999.; 
        _dr_pho1_lep2     = -999.; 
        _dr_pho2_lep1     = -999.; 
        _dr_pho2_lep2     = -999.; 
        _dilep_mass       = -999.; 
        _cosdphi_dilep    = -999.; 
        _dphi_dipho_dilep = -999.; 
        _pt_balance       = -999.; 
        _njet             = -999.; 
        _max_jet_pt       = -999.; 
        _max_jet_dCSV     = -999.; 
        _leptonType       = -999.; 

        ZHMva_.reset( new TMVA::Reader( "!Color:!Silent" ) );
        ZHMva_->AddVariable( "pho1_eta"         ,& _pho1_eta          ); 
        ZHMva_->AddVariable( "pho2_eta"         ,& _pho2_eta          ); 
        ZHMva_->AddVariable( "pho1_ptoM"        ,& _pho1_ptoM         ); 
        ZHMva_->AddVariable( "pho2_ptoM"        ,& _pho2_ptoM         ); 
        ZHMva_->AddVariable( "min_phoId"        ,& _min_phoId         ); 
        ZHMva_->AddVariable( "max_phoId"        ,& _max_phoId         ); 
        ZHMva_->AddVariable( "cosdphi_dipho"    ,& _cosdphi_dipho     ); 
        ZHMva_->AddVariable( "lep1_pt"          ,& _lep1_pt           ); 
        ZHMva_->AddVariable( "lep2_pt"          ,& _lep2_pt           ); 
        ZHMva_->AddVariable( "lep1_eta"         ,& _lep1_eta          ); 
        ZHMva_->AddVariable( "lep2_eta"         ,& _lep2_eta          ); 
        ZHMva_->AddVariable( "dr_pho1_lep1"     ,& _dr_pho1_lep1      ); 
        ZHMva_->AddVariable( "dr_pho1_lep2"     ,& _dr_pho1_lep2      ); 
        ZHMva_->AddVariable( "dr_pho2_lep1"     ,& _dr_pho2_lep1      ); 
        ZHMva_->AddVariable( "dr_pho2_lep2"     ,& _dr_pho2_lep2      ); 
        ZHMva_->AddVariable( "dilep_mass"       ,& _dilep_mass        ); 
        ZHMva_->AddVariable( "cosdphi_dilep"    ,& _cosdphi_dilep     ); 
        ZHMva_->AddVariable( "dphi_dipho_dilep" ,& _dphi_dipho_dilep  ); 
        ZHMva_->AddVariable( "pt_balance"       ,& _pt_balance        ); 
        ZHMva_->AddVariable( "njet"             ,& _njet              ); 
        ZHMva_->AddVariable( "max_jet_pt"       ,& _max_jet_pt        ); 
        ZHMva_->AddVariable( "max_jet_dCSV"     ,& _max_jet_dCSV      ); 
        ZHMva_->AddSpectator( "leptonType", &_leptonType ); 
        ZHMva_->BookMVA( "BDT", ZHMVAweightfile_.fullPath() );

        acBoundaries  = iConfig.getParameter< vector<double> >( "acBoundaries" );
        boundaries = iConfig.getParameter<vector<double > >( "Boundaries" );
        assert( is_sorted( boundaries.begin(), boundaries.end() ) ); // we are counting on ascending order - update this to give an error message or exception

        produces<vector<ZHLeptonicTag> >();
        //produces<vector<VHTagTruth> >();

    }

    int ZHLeptonicTagProducer::chooseACCategory( float stxs_mva, float ac_mva )
    {
        // should return 0 if mva above all the numbers, 1 if below the first, ..., boundaries.size()-N if below the Nth, ...
        //tag_number {each tag should have 4 boundaries}
        for (uint tag_num=0;tag_num < acBoundaries.size(); tag_num+=4){
            if ((stxs_mva <= acBoundaries[tag_num + 0]) && (stxs_mva > acBoundaries[tag_num + 1]) && (ac_mva <= acBoundaries[tag_num + 2]) && (ac_mva > acBoundaries[tag_num + 3])){
                // std::cout<<"ZH "<<tag_num/4<<" "<<stxs_mva<<" "<<ac_mva<<std::endl;
                return tag_num/4;
            }
        }
        // std::cout<<"ZH "<<"-1"<<" "<<stxs_mva<<" "<<ac_mva<<std::endl;
        return -1; // Does not pass, object will not be produced
    }

    void ZHLeptonicTagProducer::produce( Event &evt, const EventSetup & )
    {
        Handle<View<flashgg::DiPhotonCandidate> > diPhotons;
        evt.getByToken( diPhotonToken_, diPhotons );

        Handle<View<flashgg::Electron> > theElectrons;
        evt.getByToken( electronToken_, theElectrons );

        Handle<View<flashgg::Muon> > theMuons;
        evt.getByToken( muonToken_, theMuons );

        JetCollectionVector Jets( inputTagJets_.size() );
        for( size_t j = 0; j < inputTagJets_.size(); ++j ) 
            evt.getByToken( tokenJets_[j], Jets[j] );

        Handle<View<reco::Vertex> > vertices;
        evt.getByToken( vertexToken_, vertices );

        edm::Handle<double>  rho;
        evt.getByToken(rhoTag_,rho);
        // double rho_    = *rho;

        Handle<View<flashgg::DiPhotonMVAResult> > mvaResults;
        evt.getByToken( mvaResultToken_, mvaResults );
        assert( diPhotons->size() == mvaResults->size() );

        Handle<View<reco::GenParticle> > genParticles;
        evt.getByToken( genParticleToken_, genParticles );

        std::unique_ptr<vector<ZHLeptonicTag> > ZHLeptonicTags( new vector<ZHLeptonicTag> );
        //std::unique_ptr<vector<VHTagTruth> > truths( new vector<VHTagTruth> );
        //edm::RefProd<vector<VHTagTruth> > rTagTruth = evt.getRefBeforePut<vector<VHTagTruth> >();

        bool associatedZ   = 0;
        bool associatedW   = 0;
        bool VhasDaughters = 0;
        bool VhasNeutrinos = 0;
        bool VhasLeptons   = 0;
        bool VhasHadrons   = 0;
        bool VhasMissingLeptons = 0;
        float Vpt = 0;

        if( ! evt.isRealData() ) {
            for( unsigned int genLoop = 0 ; genLoop < genParticles->size(); genLoop++ ) {
                int pdgid = genParticles->ptrAt( genLoop )->pdgId();
                int dpdgid[2] = {0, 0};

                //Search for Z boson
                if(pdgid == 23) {
                    associatedZ = 1;
                    if(genParticles->ptrAt( genLoop )->numberOfDaughters() == 2) {
                        VhasDaughters = 1;
                        dpdgid[0] = genParticles->ptrAt(genLoop)->daughter(0)->pdgId();
                        Vpt = genParticles->ptrAt( genLoop )->pt();
                        if(fabs(dpdgid[0]) == 12 || fabs(dpdgid[0]) == 14 || fabs(dpdgid[0]) == 16) VhasNeutrinos = 1;//look for neutrino decay of Z
                        if(fabs(dpdgid[0]) == 11 || fabs(dpdgid[0]) == 13 || fabs(dpdgid[0]) == 15) VhasLeptons = 1;//look for lepton decay of Z
                        if(fabs(dpdgid[0]) >0 && fabs(dpdgid[0]) < 9) VhasHadrons = 1; //look for quark decay of Z
                    }
                }

                //Search for W boson
                if(fabs(pdgid) == 24) {
                    associatedW = 1;
                    if(genParticles->ptrAt( genLoop )->numberOfDaughters() == 2) {
                        VhasDaughters = 1;
                        Vpt = genParticles->ptrAt( genLoop )->pt();
                        dpdgid[0] = genParticles->ptrAt(genLoop)->daughter(0)->pdgId();
                        //dpdgid[1]=genParticles->ptrAt(genLoop)->daughter(1)->pdgId();
                        if(fabs(dpdgid[0]) == 12 || fabs(dpdgid[0]) == 14 || fabs(dpdgid[0]) == 16) { VhasNeutrinos = 1; VhasLeptons = 1; }//look for neutrino decay of W
                        if(fabs(dpdgid[0]) == 11 || fabs(dpdgid[0]) == 13 || fabs(dpdgid[0]) == 15) { VhasNeutrinos = 1; VhasLeptons = 1; }//look for lepton decay of W
                        if(fabs(dpdgid[0]) > 0 && fabs(dpdgid[0]) < 9) { VhasHadrons = 1; }//look for quark decay of W
                    }
                }
            }
        }

        // unsigned int idx = 0;

        for( unsigned int diphoIndex = 0; diphoIndex < diPhotons->size(); diphoIndex++ ) {

            edm::Ptr<flashgg::DiPhotonCandidate> dipho = diPhotons->ptrAt( diphoIndex );
            edm::Ptr<flashgg::DiPhotonMVAResult> mvares = mvaResults->ptrAt( diphoIndex );
            ZHLeptonicTag ZHLeptonicTags_obj( dipho, mvares );
            ZHLeptonicTags_obj.includeWeights( *dipho );
            
            if( dipho->leadingPhoton()->pt() < ( dipho->mass() )*leadPhoOverMassThreshold_ ) { continue; }
            if( dipho->subLeadingPhoton()->pt() < ( dipho->mass() )*subleadPhoOverMassThreshold_ ) { continue; }
            double idmva1 = dipho->leadingPhoton()->phoIdMvaDWrtVtx( dipho->vtx() );
            double idmva2 = dipho->subLeadingPhoton()->phoIdMvaDWrtVtx( dipho->vtx() );
            if( idmva1 <= PhoMVAThreshold_ || idmva2 <= PhoMVAThreshold_ ) { continue; }
            if( mvares->result < MVAThreshold_ ) { continue; }

            std::vector<edm::Ptr<flashgg::Muon> > tagMuonsTemp =
                LeptonSelection2018::selectMuons(theMuons->ptrs(), dipho, vertices->ptrs(), 
                        muonPtThreshold_, muonEtaThreshold_, muPFIsoSumRelThreshold_, deltaRMuonPhoThreshold_);
            std::vector<edm::Ptr<Electron> > tagElectronsTemp =
                LeptonSelection2018::selectElectrons(theElectrons->ptrs(), dipho, 
                        electronPtThreshold_, electronEtaThresholds_, deltaRPhoElectronThreshold_, deltaMassElectronZThreshold_, DeltaRTrkElec_);

            std::vector<edm::Ptr<flashgg::Muon> > tagMuons;
            std::vector<edm::Ptr<flashgg::Electron> > tagElectrons;

            bool isDiMuon = false;
            bool isDiElectron = false;

            //check for two good muons
            if( tagMuonsTemp.size() == 2 ) {
                math::XYZTLorentzVector leptonPair = tagMuonsTemp[0]->p4() + tagMuonsTemp[1]->p4();
                if( leptonPair.M() < invMassLepHighThreshold_ && leptonPair.M() > invMassLepLowThreshold_ ) {
                    tagMuons.push_back(tagMuonsTemp[0]);
                    tagMuons.push_back(tagMuonsTemp[1]);
                    isDiMuon = true;
                }
            }

            //check for two good electrons
            if( tagElectronsTemp.size() == 2 ) {
                math::XYZTLorentzVector leptonPair = tagElectronsTemp[0]->p4()+tagElectronsTemp[1]->p4();
                if( leptonPair.M() < invMassLepHighThreshold_ && leptonPair.M() > invMassLepLowThreshold_ ) {
                    tagElectrons.push_back(tagElectronsTemp[0]);
                    tagElectrons.push_back(tagElectronsTemp[1]);
                    isDiElectron = true;
                }
            }

            if ( !isDiElectron && !isDiMuon ) continue;

            TLorentzVector diphoP4(dipho->px(), dipho->py(), dipho->pz(), dipho->energy());
            TLorentzVector dilepP4, lep1P4, lep2P4;
 
            if (isDiMuon) {
                lep1P4.SetPtEtaPhiE(tagMuons[0]->pt(), tagMuons[0]->eta(), tagMuons[0]->phi(), tagMuons[0]->energy());
                lep2P4.SetPtEtaPhiE(tagMuons[1]->pt(), tagMuons[1]->eta(), tagMuons[1]->phi(), tagMuons[1]->energy());
                ZHLeptonicTags_obj.includeWeights( *tagMuons.at(0) );
                ZHLeptonicTags_obj.includeWeights( *tagMuons.at(1) );
                _leptonType = 13.;
            } else {
                lep1P4.SetPtEtaPhiE(tagElectrons[0]->pt(), tagElectrons[0]->eta(), tagElectrons[0]->phi(), tagElectrons[0]->energy());
                lep2P4.SetPtEtaPhiE(tagElectrons[1]->pt(), tagElectrons[1]->eta(), tagElectrons[1]->phi(), tagElectrons[1]->energy());
                ZHLeptonicTags_obj.includeWeights( *tagElectrons.at(0) );
                ZHLeptonicTags_obj.includeWeights( *tagElectrons.at(1) );
                _leptonType = 11.;
            }
            dilepP4 = lep1P4 + lep2P4;

            //Jets
            float max_jet_pt          = 0.;
            float max_jet_dCSV        = 0.;
            std::vector<edm::Ptr<Jet> > tagJets;
            unsigned int jetCollectionIndex = diPhotons->ptrAt( diphoIndex )->jetCollectionIndex();
            for( unsigned int candIndex_outer = 0; candIndex_outer < Jets[jetCollectionIndex]->size() ; candIndex_outer++ ) {
 
                edm::Ptr<flashgg::Jet> thejet = Jets[jetCollectionIndex]->ptrAt( candIndex_outer );
                if( !thejet->passesJetID( flashgg::Tight2017 ) ) continue;
                if( fabs( thejet->eta() ) > jetEtaThreshold_ ) continue;
                if( thejet->pt() < jetPtThreshold_ ) continue;
                float dRPhoLeadJet = deltaR( thejet->eta(), thejet->phi(), 
                                            dipho->leadingPhoton()->superCluster()->eta(), dipho->leadingPhoton()->superCluster()->phi() ) ;
                float dRPhoSubLeadJet = deltaR( thejet->eta(), thejet->phi(), 
                                            dipho->subLeadingPhoton()->superCluster()->eta(), dipho->subLeadingPhoton()->superCluster()->phi() );

                if( dRPhoLeadJet < deltaRJetPhoThreshold_ || dRPhoSubLeadJet < deltaRJetPhoThreshold_ ) continue;

                float dRJetLep1 = deltaR( thejet->eta(), thejet->phi(), lep1P4.Eta(), lep1P4.Phi() );
                float dRJetLep2 = deltaR( thejet->eta(), thejet->phi(), lep2P4.Eta(), lep2P4.Phi() );

                if( dRJetLep1 < deltaRJetLepThreshold_ || dRJetLep2 < deltaRJetLepThreshold_) continue;

                float pt             = thejet->pt();
                float dcsv_val       = thejet->bDiscriminator("pfDeepCSVJetTags:probb") + thejet->bDiscriminator("pfDeepCSVJetTags:probbb");
                if (pt > max_jet_pt)            max_jet_pt   = pt;
                if (dcsv_val > max_jet_dCSV)    max_jet_dCSV = dcsv_val;
                tagJets.push_back( thejet );
            }

            //ZHMVA
            _pho1_eta          = dipho->leadingPhoton()->eta();
            _pho2_eta          = dipho->subLeadingPhoton()->eta();
            _pho1_ptoM         = dipho->leadingPhoton()->pt() / dipho->mass();
            _pho2_ptoM         = dipho->subLeadingPhoton()->pt() / dipho->mass();
            _min_phoId         = TMath::Min(idmva1, idmva2);
            _max_phoId         = TMath::Max(idmva1, idmva2);
            _cosdphi_dipho     = TMath::Cos( fabs(deltaPhi(dipho->leadingPhoton()->phi(), dipho->subLeadingPhoton()->phi())) );
            _lep1_pt           = lep1P4.Pt();
            _lep2_pt           = lep2P4.Pt();
            _lep1_eta          = lep1P4.Eta();
            _lep2_eta          = lep2P4.Eta();
            _dr_pho1_lep1      = deltaR( lep1P4.Eta(), lep1P4.Phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi() ) ;
            _dr_pho1_lep2      = deltaR( lep2P4.Eta(), lep2P4.Phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi() ) ;
            _dr_pho2_lep1      = deltaR( lep1P4.Eta(), lep1P4.Phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi() ) ;
            _dr_pho2_lep2      = deltaR( lep2P4.Eta(), lep2P4.Phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi() ) ;
            _dilep_mass        = dilepP4.M();
            _cosdphi_dilep     = TMath::Cos( fabs( lep1P4.DeltaPhi( lep2P4 ) ) );
            _dphi_dipho_dilep  = fabs( diphoP4.DeltaPhi(dilepP4) );
            _pt_balance        = (diphoP4.Pt() - dilepP4.Pt()) / diphoP4.Pt();
            _njet              = tagJets.size();
            _max_jet_pt        = max_jet_pt;
            _max_jet_dCSV      = max_jet_dCSV;

            float zhmva    = ZHMva_->EvaluateMVA( "BDT" );




            //Evaluating variables for AC-MVA
            _Anom_MVA_pho1_eta             = dipho->leadingPhoton()->eta();
            _Anom_MVA_pho1_phi             = dipho->leadingPhoton()->phi();
            _Anom_MVA_pho1_idmva           = dipho->leadPhotonId();
            _Anom_MVA_pho1_full5x5_r9      = dipho->leadingPhoton()->full5x5_r9();
            _Anom_MVA_pho1_ptOverMgg       = dipho->leadingPhoton()->pt() / dipho->mass();
            
            _Anom_MVA_pho2_eta             = dipho->subLeadingPhoton()->eta();
            _Anom_MVA_pho2_phi             = dipho->subLeadingPhoton()->phi();
            _Anom_MVA_pho2_idmva           = dipho->subLeadPhotonId();
            _Anom_MVA_pho2_full5x5_r9      = dipho->subLeadingPhoton()->full5x5_r9();
            _Anom_MVA_pho2_ptOverMgg       = dipho->subLeadingPhoton()->pt() / dipho->mass();
            

            _Anom_MVA_mu1_pt               = tagMuons.size()>0 ? tagMuons[0]->pt()     : -100;
            _Anom_MVA_mu1_eta              = tagMuons.size()>0 ? tagMuons[0]->eta()    : -100;
            _Anom_MVA_mu1_phi              = tagMuons.size()>0 ? tagMuons[0]->phi()    : -100;
            _Anom_MVA_mu1_energy           = tagMuons.size()>0 ? tagMuons[0]->energy() : -100;

            _Anom_MVA_mu2_pt               = tagMuons.size()>1 ? tagMuons[1]->pt()     : -100;
            _Anom_MVA_mu2_eta              = tagMuons.size()>1 ? tagMuons[1]->eta()    : -100;
            _Anom_MVA_mu2_phi              = tagMuons.size()>1 ? tagMuons[1]->phi()    : -100;
            _Anom_MVA_mu2_energy           = tagMuons.size()>1 ? tagMuons[1]->energy() : -100;


            _Anom_MVA_ele1_pt              = tagElectrons.size()>0 ? tagElectrons[0]->pt()     : -100;             
            _Anom_MVA_ele1_eta             = tagElectrons.size()>0 ? tagElectrons[0]->eta()    : -100;
            _Anom_MVA_ele1_phi             = tagElectrons.size()>0 ? tagElectrons[0]->phi()    : -100;
            _Anom_MVA_ele1_energy          = tagElectrons.size()>0 ? tagElectrons[0]->energy() : -100;

            _Anom_MVA_ele2_pt              = tagElectrons.size()>1 ? tagElectrons[1]->pt()     : -100;             
            _Anom_MVA_ele2_eta             = tagElectrons.size()>1 ? tagElectrons[1]->eta()    : -100;
            _Anom_MVA_ele2_phi             = tagElectrons.size()>1 ? tagElectrons[1]->phi()    : -100;
            _Anom_MVA_ele2_energy          = tagElectrons.size()>1 ? tagElectrons[1]->energy() : -100;
            
            _Anom_MVA_jet1_pt              = tagJets.size()>0 ? tagJets[0]->pt()     : -100;
            _Anom_MVA_jet1_phi             = tagJets.size()>0 ? tagJets[0]->phi()    : -100;
            _Anom_MVA_jet1_eta             = tagJets.size()>0 ? tagJets[0]->eta()    : -100;
            _Anom_MVA_jet1_energy          = tagJets.size()>0 ? tagJets[0]->energy() : -100;
            _Anom_MVA_jet2_pt              = tagJets.size()>1 ? tagJets[1]->pt()     : -100;
            _Anom_MVA_jet2_phi             = tagJets.size()>1 ? tagJets[1]->phi()    : -100;
            _Anom_MVA_jet2_eta             = tagJets.size()>1 ? tagJets[1]->eta()    : -100;
            _Anom_MVA_jet2_energy          = tagJets.size()>1 ? tagJets[1]->energy() : -100;
            _Anom_MVA_cosPhiGG             = TMath::Cos( deltaPhi(dipho->leadingPhoton()->phi(), dipho->subLeadingPhoton()->phi()) );
            _Anom_MVA_cosPhiG1_Mu1         = tagMuons.size() > 0     ? TMath::Cos( deltaPhi(dipho->leadingPhoton()->phi(), tagMuons[0]->phi()) )      : -100;
            _Anom_MVA_cosPhiG1_Mu2         = tagMuons.size() > 1     ? TMath::Cos( deltaPhi(dipho->leadingPhoton()->phi(), tagMuons[1]->phi()) )      : -100;
            _Anom_MVA_cosPhiG1_Ele1        = tagElectrons.size() > 0 ? TMath::Cos( deltaPhi(dipho->leadingPhoton()->phi(), tagElectrons[0]->phi()) )  : -100;
            _Anom_MVA_cosPhiG1_Ele2        = tagElectrons.size() > 1 ? TMath::Cos( deltaPhi(dipho->leadingPhoton()->phi(), tagElectrons[1]->phi()) )  : -100;
            _Anom_MVA_cosPhiG2_Mu1         = tagMuons.size() > 0     ? TMath::Cos( deltaPhi(dipho->subLeadingPhoton()->phi(), tagMuons[0]->phi()) )      : -100;
            _Anom_MVA_cosPhiG2_Mu2         = tagMuons.size() > 1     ? TMath::Cos( deltaPhi(dipho->subLeadingPhoton()->phi(), tagMuons[1]->phi()) )      : -100;
            _Anom_MVA_cosPhiG2_Ele1        = tagElectrons.size() > 0 ? TMath::Cos( deltaPhi(dipho->subLeadingPhoton()->phi(), tagElectrons[0]->phi()) )  : -100;
            _Anom_MVA_cosPhiG2_Ele2        = tagElectrons.size() > 1 ? TMath::Cos( deltaPhi(dipho->subLeadingPhoton()->phi(), tagElectrons[1]->phi()) )  : -100;
            _Anom_MVA_dR_Pho1Ele1_wh       = tagElectrons.size() > 0 ? deltaR(tagElectrons[0]->eta(), tagElectrons[0]->phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho1Ele2_wh       = tagElectrons.size() > 1 ? deltaR(tagElectrons[1]->eta(), tagElectrons[1]->phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho2Ele1_wh       = tagElectrons.size() > 0 ? deltaR(tagElectrons[0]->eta(), tagElectrons[0]->phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho2Ele2_wh       = tagElectrons.size() > 1 ? deltaR(tagElectrons[1]->eta(), tagElectrons[1]->phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho1Mu1_wh        = tagMuons.size() > 0 ? deltaR(tagMuons[0]->eta(), tagMuons[0]->phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho1Mu2_wh        = tagMuons.size() > 1 ? deltaR(tagMuons[1]->eta(), tagMuons[1]->phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho2Mu1_wh        = tagMuons.size() > 0 ? deltaR(tagMuons[0]->eta(), tagMuons[0]->phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho2Mu2_wh        = tagMuons.size() > 1 ? deltaR(tagMuons[1]->eta(), tagMuons[1]->phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho1Jet1_wh       = tagJets.size() > 0 ? deltaR(tagJets[0]->eta(), tagJets[0]->phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho1Jet2_wh       = tagJets.size() > 1 ? deltaR(tagJets[1]->eta(), tagJets[1]->phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho2Jet1_wh       = tagJets.size() > 0 ? deltaR(tagJets[0]->eta(), tagJets[0]->phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho2Jet2_wh       = tagJets.size() > 1 ? deltaR(tagJets[1]->eta(), tagJets[1]->phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Mu1Jet1_wh        = ((tagMuons.size() > 0)&&(tagJets.size() > 0))      ? deltaR(tagJets[0]->eta(), tagJets[0]->phi(), tagMuons[0]->eta(), tagMuons[0]->phi())         : -100;
            _Anom_MVA_dR_Mu1Jet2_wh        = ((tagMuons.size() > 0)&&(tagJets.size() > 1))      ? deltaR(tagJets[1]->eta(), tagJets[1]->phi(), tagMuons[0]->eta(), tagMuons[0]->phi())         : -100;
            _Anom_MVA_dR_Ele1Jet1_wh       = ((tagElectrons.size() > 0)&&(tagJets.size() > 0)) ? deltaR(tagJets[0]->eta(), tagJets[0]->phi(), tagElectrons[0]->eta(), tagElectrons[0]->phi()) : -100;
            _Anom_MVA_dR_Ele1Jet2_wh       = ((tagElectrons.size() > 0)&&(tagJets.size() > 1)) ? deltaR(tagJets[1]->eta(), tagJets[1]->phi(), tagElectrons[0]->eta(), tagElectrons[0]->phi()) : -100;


            float ZHiggs0MToGG_MVA   =ZHiggs0MToGG_MVA_->EvaluateMVA( "BDT" );   
            float ZHiggs0PHToGG_MVA  =ZHiggs0PHToGG_MVA_->EvaluateMVA( "BDT" );
            float ZHiggs0L1ToGG_MVA  =ZHiggs0L1ToGG_MVA_->EvaluateMVA( "BDT" );                   
            
            //AC MVA we are currently look at fa3=1
            float anom_mva = ZHiggs0MToGG_MVA;
 



            // Categorization by ZHMVA
            int catnum = chooseACCategory( zhmva , anom_mva);

            if( catnum != -1 ) {
                ZHLeptonicTags_obj.setCategoryNumber( catnum );
                ZHLeptonicTags_obj.setMuons( tagMuons );
                ZHLeptonicTags_obj.setElectrons( tagElectrons );
                ZHLeptonicTags_obj.setJets( tagJets );
                ZHLeptonicTags_obj.setDiPhotonIndex( diphoIndex );
                ZHLeptonicTags_obj.setSystLabel( systLabel_ );

                ZHLeptonicTags_obj.set_VHmva( zhmva );
                ZHLeptonicTags_obj.set_ZHiggs0MToGG_MVA(ZHiggs0MToGG_MVA);
                ZHLeptonicTags_obj.set_ZHiggs0PHToGG_MVA(ZHiggs0PHToGG_MVA);
                ZHLeptonicTags_obj.set_ZHiggs0L1ToGG_MVA(ZHiggs0L1ToGG_MVA);

                if( ! evt.isRealData() ) {
                    ZHLeptonicTags_obj.setAssociatedZ( associatedZ );
                    ZHLeptonicTags_obj.setAssociatedW( associatedW );
                    ZHLeptonicTags_obj.setVhasNeutrinos( VhasNeutrinos );
                    ZHLeptonicTags_obj.setVhasLeptons( VhasLeptons );
                    ZHLeptonicTags_obj.setVhasHadrons( VhasHadrons );
                    ZHLeptonicTags_obj.setVpt( Vpt );
                }

                if( catnum == 0 ) { 
                    ZHLeptonicTags_obj.setStage1recoTag( DiPhotonTagBase::stage1recoTag::RECO_ZH_LEP_Tag0 );
                } else if ( catnum == 1 ) {
                    ZHLeptonicTags_obj.setStage1recoTag( DiPhotonTagBase::stage1recoTag::RECO_ZH_LEP_Tag1 );
                } else {
                    ZHLeptonicTags_obj.setStage1recoTag( DiPhotonTagBase::stage1recoTag::LOGICERROR );
                }


                ZHLeptonicTags->push_back( ZHLeptonicTags_obj );

                if( ! evt.isRealData() ){
                    VHTagTruth truth_obj;
                    truth_obj.setAssociatedZ( associatedZ );
                    truth_obj.setAssociatedW( associatedW );
                    truth_obj.setVhasDaughters( VhasDaughters );
                    truth_obj.setVhasNeutrinos( VhasNeutrinos );
                    truth_obj.setVhasLeptons( VhasLeptons );
                    truth_obj.setVhasHadrons( VhasHadrons );
                    truth_obj.setVhasMissingLeptons( VhasMissingLeptons );
                    truth_obj.setVpt( Vpt );
                    //truths->push_back( truth_obj );
                    //ZHLeptonicTags->back().setTagTruth( edm::refToPtr( edm::Ref<vector<VHTagTruth> >( rTagTruth, idx++ ) ) );
                }
            }
        }
        evt.put( std::move( ZHLeptonicTags ) );
        //evt.put( std::move( truths ) );
    }
}
typedef flashgg::ZHLeptonicTagProducer FlashggZHLeptonicTagProducer;
DEFINE_FWK_MODULE( FlashggZHLeptonicTagProducer );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
