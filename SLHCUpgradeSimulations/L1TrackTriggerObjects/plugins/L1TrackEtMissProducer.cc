// -*- C++ -*-
//
//
// Original Author:  Emmanuelle Perez,40 1-A28,+41227671915,
//         Created:  Tue Nov 12 17:03:19 CET 2013
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/LorentzVector.h"

#include "SimDataFormats/SLHC/interface/StackedTrackerTypes.h"

////////////////////////////
// DETECTOR GEOMETRY HEADERS
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetType.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelTopologyBuilder.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/RectangularPixelTopology.h"
#include "Geometry/CommonDetUnit/interface/GeomDetType.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"

#include "Geometry/Records/interface/StackedTrackerGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/StackedTrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/StackedTrackerDetUnit.h"
#include "DataFormats/SiPixelDetId/interface/StackedTrackerDetId.h"


#include "DataFormats/L1TrackTrigger/interface/L1TrackEtMissParticle.h"
#include "DataFormats/L1TrackTrigger/interface/L1TrackEtMissParticleFwd.h"


using namespace l1extra;

//
// class declaration
//

class L1TrackEtMissProducer : public edm::EDProducer {
   public:

  typedef L1TkTrack_PixelDigi_                          L1TkTrackType;
  typedef std::vector< L1TkTrackType >                               L1TkTrackCollectionType;

      explicit L1TrackEtMissProducer(const edm::ParameterSet&);
      ~L1TrackEtMissProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      //virtual void endRun(edm::Run&, edm::EventSetup const&);
      //virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      //virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------

        edm::InputTag L1VtxLabel;

	float ZMAX;	// in cm
	float DeltaZ;	// in cm
	float CHI2MAX;
	float Ptmin;	// in GeV
        int nStubsmin;


        //const StackedTrackerGeometry*                   theStackedGeometry;

};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
L1TrackEtMissProducer::L1TrackEtMissProducer(const edm::ParameterSet& iConfig)
{
   //register your products
/* Examples
   produces<ExampleData2>();

   //if do put with a label
   produces<ExampleData2>("label");
 
   //if you want to put into the Run
   produces<ExampleData2,InRun>();
*/
   //now do what ever other initialization is needed
  
  L1VtxLabel = iConfig.getParameter<edm::InputTag>("L1VtxLabel") ;

  ZMAX = (float)iConfig.getParameter<double>("ZMAX");
  DeltaZ = (float)iConfig.getParameter<double>("DeltaZ");
  CHI2MAX = (float)iConfig.getParameter<double>("CHI2MAX");
  Ptmin = (float)iConfig.getParameter<double>("Ptmin");
  nStubsmin = iConfig.getParameter<int>("nStubsmin");

  produces<L1TrackEtMissParticleCollection>("MET");

}


L1TrackEtMissProducer::~L1TrackEtMissProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
L1TrackEtMissProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   std::auto_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
   iEvent.put(pOut);
*/

/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
 
 std::auto_ptr<L1TrackEtMissParticleCollection> result(new L1TrackEtMissParticleCollection);

 edm::Handle<L1TrackPrimaryVertexCollection> L1VertexHandle;
 iEvent.getByLabel(L1VtxLabel,L1VertexHandle);
 std::vector<L1TrackPrimaryVertex>::const_iterator vtxIter;

 edm::Handle<L1TkTrackCollectionType> L1TkTrackHandle;
 iEvent.getByLabel("L1Tracks","Level1TkTracks",L1TkTrackHandle);
 L1TkTrackCollectionType::const_iterator trackIter;

 int ivtx = 0;

 for (vtxIter = L1VertexHandle->begin(); vtxIter != L1VertexHandle->end(); ++vtxIter) {

    float zVTX = vtxIter -> getZvertex();
    edm::Ref< L1TrackPrimaryVertexCollection > vtxRef( L1VertexHandle, ivtx );
    ivtx ++;

    float sumPx = 0;
    float sumPy = 0;
    float etTot = 0;

    double sumPx_PU = 0;
    double sumPy_PU = 0;
    double etTot_PU = 0;

  	for (trackIter = L1TkTrackHandle->begin(); trackIter != L1TkTrackHandle->end(); ++trackIter) {
 
    	    float pt = trackIter->getMomentum().perp();
    	    float chi2 = trackIter->getChi2();
    	    float ztr  = trackIter->getVertex().z();
	
    	    if (pt < Ptmin) continue;
    	    if (fabs(ztr) > ZMAX ) continue;
    	    if (chi2 > CHI2MAX) continue;
                
            int nstubs = 0;
            std::vector< edm::Ptr< L1TkStub_PixelDigi_ > > theStubs = trackIter ->getStubPtrs();
            int tmp_trk_nstub = (int) theStubs.size();
            if ( tmp_trk_nstub < 0) continue;
            // loop over the stubs
            for (unsigned int istub=0; istub<(unsigned int)theStubs.size(); istub++) {
                bool genuine = theStubs.at(istub)->isGenuine();
                if (genuine) {
                  nstubs ++;
                }
            }
            if (nstubs < nStubsmin) continue;

            if ( fabs(ztr - zVTX) <= DeltaZ) {   // eg DeltaZ = 1 mm

	    	sumPx += trackIter->getMomentum().x();
	    	sumPy += trackIter->getMomentum().y();
	    	etTot += pt ;
	    }
	    else   {	// PU sums
                sumPx_PU += trackIter->getMomentum().x();
                sumPy_PU += trackIter->getMomentum().y();
                etTot_PU += pt ;
	    }


    	} // end loop over tracks
     float et = sqrt( sumPx*sumPx + sumPy*sumPy );
     math::XYZTLorentzVector missingEt( -sumPx, -sumPy, 0, et);

     double etmiss_PU = sqrt( sumPx_PU*sumPx_PU + sumPy_PU*sumPy_PU );

     int ibx = 0;
     result -> push_back(  L1TrackEtMissParticle( missingEt,
				 L1TrackEtMissParticle::kMET,
				 etTot,
				 etmiss_PU,
				 etTot_PU,
				 vtxRef,
				 ibx )
		         ) ;


 } // end loop over vertices

 iEvent.put( result, "MET");
}


// ------------ method called once each job just before starting event loop  ------------
void 
L1TrackEtMissProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1TrackEtMissProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
L1TrackEtMissProducer::beginRun(edm::Run& iRun, edm::EventSetup const& iSetup)
{

/*
  /// Geometry handles etc
  edm::ESHandle<TrackerGeometry>                               geometryHandle;
  //const TrackerGeometry*                                       theGeometry;
  edm::ESHandle<StackedTrackerGeometry>           stackedGeometryHandle;

  /// Geometry setup
  /// Set pointers to Geometry
  iSetup.get<TrackerDigiGeometryRecord>().get(geometryHandle);
  //theGeometry = &(*geometryHandle);
  /// Set pointers to Stacked Modules
  iSetup.get<StackedTrackerGeometryRecord>().get(stackedGeometryHandle);
  theStackedGeometry = stackedGeometryHandle.product(); /// Note this is different 
                                                        /// from the "global" geometry
  if (theStackedGeometry == 0) cout << " theStackedGeometry = 0 " << endl;      // for compil when not used...
*/

}
 
// ------------ method called when ending the processing of a run  ------------
/*
void
L1TrackEtMissProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
L1TrackEtMissProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
L1TrackEtMissProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
L1TrackEtMissProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1TrackEtMissProducer);
