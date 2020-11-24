#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include <stdio.h>
#include <iostream>

//--------------------------------------------------------------

void studygtree(char **argv ){
  // Open the file containing the tree
  std::string input = argv[1];
  std::cout << ">>> Process input: " << input << std::endl;
  
  TChain tchain( "pulseana/ophittree" );
  tchain.Add( input.c_str() );
  
  int nevents = -1;
  if( nevents<0 || nevents>tchain.GetEntries() ){
    nevents = tchain.GetEntries();
  }

  std::vector<int> *m_pmt_array = 0;

  tchain.SetBranchAddress("channel_id", & m_pmt_array);

  // Event loop -------------------------------------------\\  
  
  if(nevents<0 || nevents>tchain.GetEntries()){ nevents = tchain.GetEntries(); }
  std::cout << ">>> Process number of events: " << nevents << std::endl;
  
  for( int event=0; event<nevents; event++ ){
    tchain.GetEntry(event);
  
    for( size_t pmtindex=0; pmtindex<m_pmt_array->size(); pmtindex++){
      int pmtid = (*m_pmt_array).at(pmtindex);
      std::cout << ">>> PMT ID: " << pmtid << std::endl;
    
    }
  
  TChain tchain( "pulseana/geotree" );
  tchain.Add( input.c_str() );
  
  int nevents = -1;
  if( nevents<0 || nevents>tchain.GetEntries() ){
    nevents = tchain.GetEntries();
  }

  std::vector<double> *m_pmt_x = 0;
  std::vector<double> *m_pmt_y = 0;
  std::vector<double> *m_pmt_z = 0;

  tchain.SetBranchAddress("pmtX", & m_pmt_x);
  tchain.SetBranchAddress("pmtY", & m_pmt_y);
  tchain.SetBranchAddress("pmtZ", & m_pmt_z);

  // Event loop -------------------------------------------\\  
  
  if(nevents<0 || nevents>tchain.GetEntries()){ nevents = tchain.GetEntries(); }
  //std::cout << ">>> Process number of events: " << nevents << std::endl;
  
  for( int event=0; event<nevents; event++ ){
    tchain.GetEntry(event);
  
    double pmtid_x = (*m_pmt_x).at(event);
    double pmtid_y = (*m_pmt_y).at(event);
    double pmtid_z = (*m_pmt_z).at(event); 
    
    std::cout << ">>> PMT X: " << pmtid_x << std::endl;
    std::cout << ">>> PMT Y: " << pmtid_y << std::endl;
    std::cout << ">>> PMT Z: " << pmtid_z << std::endl;
}
}
