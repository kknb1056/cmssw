#ifndef L1TrackTrigger_L1TrackEtMissParticle_h
#define L1TrackTrigger_L1TrackEtMissParticle_h
// -*- C++ -*-
//
// Package:     L1Trigger
// Class  :     L1TrackEtMissParticle
// 
/**\class L1TrackEtMissParticle 

 Description: L1Extra particle class for EtMiss object.
*/
//
// Original Author:  E. Perez
//         Created:  Nov 14, 2013
//      
        
// system include files
        
// user include files
#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "DataFormats/Common/interface/Ref.h"

#include "DataFormats/L1TrackTrigger/interface/L1TrackPrimaryVertex.h"



namespace l1extra {

  class L1TrackEtMissParticle : public reco::LeafCandidate
    { 
    public:
      
      enum EtMissType{ kMET, kMHT, kNumTypes } ;

      L1TrackEtMissParticle();

      L1TrackEtMissParticle(
        const LorentzVector& p4,
        EtMissType type,
        const double& etTotal,
	const double& etMissPU,
	const double& etTotalPU,
        const edm::Ref< L1TrackPrimaryVertexCollection >& aVtxRef = edm::Ref< L1TrackPrimaryVertexCollection >(),
        int bx = 0 ) ;



      // ---------- const member functions ---------------------

      EtMissType type() const { return type_ ; }  // kET or kHT

      // For type = kET, this is |MET|; for type = kHT, this is |MHT|
      double etMiss() const
        { return et() ; }

      // For type = kET, this is total ET; for type = kHT, this is total HT
      const double& etTotal() const
        { return etTot_ ; }

	// EtMiss and EtTot from PU vertices
	double etMissPU() const
	  { return etMissPU_ ; }
	double etTotalPU() const 
	  { return etTotalPU_ ; }

      int bx() const
        { return bx_ ; }

      const edm::Ref< L1TrackPrimaryVertexCollection >& getVtxRef() const
        { return vtxRef_ ; }


      // ---------- member functions ---------------------------
      void setEtTotal( const double& etTotal )
        { etTot_ = etTotal ; }

      void setBx( int bx )
        { bx_ = bx ; }

    private:

      // ---------- member data --------------------------------

      EtMissType type_ ;
      double etTot_ ;
      double etMissPU_ ;
      double etTotalPU_ ;

      edm::Ref< L1TrackPrimaryVertexCollection > vtxRef_ ;

      int bx_ ;

   };

}

#endif



