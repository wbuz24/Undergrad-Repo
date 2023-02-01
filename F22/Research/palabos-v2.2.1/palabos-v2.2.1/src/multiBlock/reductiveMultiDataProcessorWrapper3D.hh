/* This file is part of the Palabos library.
 *
 * The Palabos softare is developed since 2011 by FlowKit-Numeca Group Sarl
 * (Switzerland) and the University of Geneva (Switzerland), which jointly
 * own the IP rights for most of the code base. Since October 2019, the
 * Palabos project is maintained by the University of Geneva and accepts
 * source code contributions from the community.
 * 
 * Contact:
 * Jonas Latt
 * Computer Science Department
 * University of Geneva
 * 7 Route de Drize
 * 1227 Carouge, Switzerland
 * jonas.latt@unige.ch
 *
 * The most recent release of Palabos can be downloaded at 
 * <https://palabos.unige.ch/>
 *
 * The library Palabos is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * The library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef REDUCTIVE_MULTI_DATA_PROCESSOR_WRAPPER_3D_HH
#define REDUCTIVE_MULTI_DATA_PROCESSOR_WRAPPER_3D_HH

#include "multiBlock/reductiveMultiDataProcessorWrapper3D.h"
#include "multiBlock/multiBlockLattice3D.h"
#include "multiBlock/multiDataField3D.h"
#include "multiBlock/multiBlockOperations3D.h"
#include "atomicBlock/dataProcessor3D.h"
#include "core/plbDebug.h"

namespace plb {

/* *************** LatticeBoxProcessing3D ****************************************** */

template<typename T, template<typename U> class Descriptor>
void applyProcessingFunctional (
        ReductiveLatticeBoxProcessingFunctional3D<T,Descriptor>& functional,
        Box3D domain,
        std::vector<MultiBlockLattice3D<T,Descriptor>*> lattices )
{
    std::vector<MultiBlock3D*> multiBlocks(lattices.size());
    for (pluint iLattice=0; iLattice<lattices.size(); ++iLattice) {
        multiBlocks[iLattice] = dynamic_cast<MultiBlock3D*>(lattices[iLattice]);
    }
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, multiBlocks );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** MultiScalarFieldBoxProcessing3D ******************************* */

template<typename T>
void applyProcessingFunctional(ReductiveScalarFieldBoxProcessingFunctional3D<T>& functional,
                               Box3D domain,
                               std::vector<MultiScalarField3D<T>*> fields )
{
    std::vector<MultiBlock3D*> multiBlocks(fields.size());
    for (pluint iField=0; iField<fields.size(); ++iField) {
        multiBlocks[iField] = dynamic_cast<MultiBlock3D*>(fields[iField]);
    }
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, multiBlocks );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** MultiTensorFieldBoxProcessing3D ******************************* */

template<typename T, int nDim>
void applyProcessingFunctional (
        ReductiveTensorFieldBoxProcessingFunctional3D<T,nDim>& functional,
        Box3D domain,
        std::vector<MultiTensorField3D<T,nDim>*> fields )
{
    std::vector<MultiBlock3D*> multiBlocks(fields.size());
    for (pluint iField=0; iField<fields.size(); ++iField) {
        multiBlocks[iField] = dynamic_cast<MultiBlock3D*>(fields[iField]);
    }
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, multiBlocks );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** MultiNTensorFieldBoxProcessing3D ******************************* */

template<typename T>
void applyProcessingFunctional (
        ReductiveNTensorFieldBoxProcessingFunctional3D<T>& functional,
        Box3D domain,
        std::vector<MultiNTensorField3D<T>*> fields )
{
    std::vector<MultiBlock3D*> multiBlocks(fields.size());
    for (pluint iField=0; iField<fields.size(); ++iField) {
        multiBlocks[iField] = dynamic_cast<MultiBlock3D*>(fields[iField]);
    }
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, multiBlocks );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveBoxProcessing3D_L ******************************************* */

template<typename T, template<typename U> class Descriptor>
void applyProcessingFunctional(ReductiveBoxProcessingFunctional3D_L<T,Descriptor>& functional,
                               Box3D domain, MultiBlockLattice3D<T,Descriptor>& lattice)
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, lattice );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveBoxProcessing3D_S ******************************************* */

template<typename T>
void applyProcessingFunctional(ReductiveBoxProcessingFunctional3D_S<T>& functional,
                               Box3D domain, MultiScalarField3D<T>& field)
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveBoxProcessing3D_T ******************************************* */

template<typename T, int nDim>
void applyProcessingFunctional(ReductiveBoxProcessingFunctional3D_T<T,nDim>& functional,
                               Box3D domain, MultiTensorField3D<T,nDim>& field)
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveBoxProcessing3D_N ******************************************* */

template<typename T>
void applyProcessingFunctional(ReductiveBoxProcessingFunctional3D_N<T>& functional,
                               Box3D domain, MultiNTensorField3D<T>& field)
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** MaskedReductiveBoxProcessing3D_N ******************************************* */

template<typename T>
void applyProcessingFunctional(MaskedReductiveBoxProcessingFunctional3D_N<T>& functional,
                               Box3D domain,
                               MultiNTensorField3D<T>& field,
                               MultiNTensorField3D<int>& mask)
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, field, mask );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveBoxProcessing3D_LL******************************************* */

template<typename T1, template<typename U1> class Descriptor1,
         typename T2, template<typename U2> class Descriptor2>
void applyProcessingFunctional (
        ReductiveBoxProcessingFunctional3D_LL<T1,Descriptor1,T2,Descriptor2>& functional,
        Box3D domain,
        MultiBlockLattice3D<T1,Descriptor1>& lattice1,
        MultiBlockLattice3D<T2,Descriptor2>& lattice2 )
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, lattice1, lattice2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveBoxProcessing3D_SS ****************************************** */

template<typename T1, typename T2>
void applyProcessingFunctional(ReductiveBoxProcessingFunctional3D_SS<T1,T2>& functional,
                               Box3D domain,
                               MultiScalarField3D<T1>& field1,
                               MultiScalarField3D<T2>& field2 )
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, field1, field2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveBoxProcessing3D_TT ****************************************** */

template<typename T1, int nDim1, typename T2, int nDim2>
void applyProcessingFunctional (
        ReductiveBoxProcessingFunctional3D_TT<T1,nDim1,T2,nDim2>& functional,
        Box3D domain,
        MultiTensorField3D<T1,nDim1>& field1,
        MultiTensorField3D<T2,nDim2>& field2 )
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, field1, field2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveBoxProcessing3D_NN ****************************************** */

template<typename T1, typename T2>
void applyProcessingFunctional (
        ReductiveBoxProcessingFunctional3D_NN<T1,T2>& functional,
        Box3D domain,
        MultiNTensorField3D<T1>& field1,
        MultiNTensorField3D<T2>& field2 )
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, field1, field2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** MaskedReductiveBoxProcessing3D_NN ****************************************** */

template<typename T1, typename T2>
void applyProcessingFunctional (
        MaskedReductiveBoxProcessingFunctional3D_NN<T1,T2>& functional,
        Box3D domain,
        MultiNTensorField3D<T1>& field1,
        MultiNTensorField3D<T2>& field2,
        MultiNTensorField3D<int>& mask )
{
    std::vector<MultiBlock3D*> multiBlocks(3);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field1);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field2);
    multiBlocks[2] = dynamic_cast<MultiBlock3D*>(&mask);
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, multiBlocks );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveBoxProcessing3D_ST ****************************************** */

template<typename T1, typename T2, int nDim>
void applyProcessingFunctional(ReductiveBoxProcessingFunctional3D_ST<T1,T2,nDim>& functional,
                               Box3D domain,
                               MultiScalarField3D<T1>& field1,
                               MultiTensorField3D<T2,nDim>& field2 )
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, field1, field2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveBoxProcessing3D_SN ****************************************** */

template<typename T1, typename T2>
void applyProcessingFunctional(ReductiveBoxProcessingFunctional3D_SN<T1,T2>& functional,
                               Box3D domain,
                               MultiScalarField3D<T1>& field1,
                               MultiNTensorField3D<T2>& field2 )
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, field1, field2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveBoxProcessing3D_LS ****************************************** */

template<typename T1, template<typename U> class Descriptor, typename T2>
void applyProcessingFunctional (
        ReductiveBoxProcessingFunctional3D_LS<T1,Descriptor,T2>& functional,
        Box3D domain,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiScalarField3D<T2>& field )
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, lattice, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveBoxProcessing3D_LT ****************************************** */

template<typename T1, template<typename U> class Descriptor, typename T2, int nDim>
void applyProcessingFunctional (
        ReductiveBoxProcessingFunctional3D_LT<T1,Descriptor,T2,nDim>& functional,
        Box3D domain,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiTensorField3D<T2,nDim>& field )
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, lattice, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveBoxProcessing3D_LN ****************************************** */

template<typename T1, template<typename U> class Descriptor, typename T2>
void applyProcessingFunctional (
        ReductiveBoxProcessingFunctional3D_LN<T1,Descriptor,T2>& functional,
        Box3D domain,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiNTensorField3D<T2>& field )
{
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, lattice, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** MaskedReductiveBoxProcessing3D_LN ****************************************** */

template<typename T1, template<typename U> class Descriptor, typename T2>
void applyProcessingFunctional (
        MaskedReductiveBoxProcessingFunctional3D_LN<T1,Descriptor,T2>& functional,
        Box3D domain,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiNTensorField3D<T2>& field,
        MultiNTensorField3D<int>& mask )
{
    std::vector<MultiBlock3D*> multiBlocks(3);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&lattice);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field);
    multiBlocks[2] = dynamic_cast<MultiBlock3D*>(&mask);
    ReductiveBoxProcessorGenerator3D generator(functional.clone(), domain);
    executeDataProcessor( generator, multiBlocks );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** LatticeDotProcessing3D ****************************************** */

template<typename T, template<typename U> class Descriptor>
void applyProcessingFunctional (
        ReductiveLatticeDotProcessingFunctional3D<T,Descriptor>& functional,
        DotList3D const& dotList,
        std::vector<MultiBlockLattice3D<T,Descriptor>*> lattices )
{
    std::vector<MultiBlock3D*> multiBlocks(lattices.size());
    for (pluint iLattice=0; iLattice<lattices.size(); ++iLattice) {
        multiBlocks[iLattice] = dynamic_cast<MultiBlock3D*>(lattices[iLattice]);
    }
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, multiBlocks );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ScalarFieldDotProcessing3D ****************************************** */

template<typename T>
void applyProcessingFunctional(ReductiveScalarFieldDotProcessingFunctional3D<T>& functional,
                               DotList3D const& dotList,
                               std::vector<MultiScalarField3D<T>*> fields )
{
    std::vector<MultiBlock3D*> multiBlocks(fields.size());
    for (pluint iField=0; iField<fields.size(); ++iField) {
        multiBlocks[iField] = dynamic_cast<MultiBlock3D*>(fields[iField]);
    }
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, multiBlocks );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}



/* *************** TensorFieldDotProcessing3D ****************************************** */

template<typename T, int nDim>
void applyProcessingFunctional (
        ReductiveTensorFieldDotProcessingFunctional3D<T,nDim>& functional,
        DotList3D const& dotList,
        std::vector<MultiTensorField3D<T,nDim>*> fields )
{
    std::vector<MultiBlock3D*> multiBlocks(fields.size());
    for (pluint iField=0; iField<fields.size(); ++iField) {
        multiBlocks[iField] = dynamic_cast<MultiBlock3D*>(fields[iField]);
    }
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, multiBlocks );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** NTensorFieldDotProcessing3D ****************************************** */

template<typename T>
void applyProcessingFunctional (
        ReductiveNTensorFieldDotProcessingFunctional3D<T>& functional,
        DotList3D const& dotList,
        std::vector<MultiNTensorField3D<T>*> fields )
{
    std::vector<MultiBlock3D*> multiBlocks(fields.size());
    for (pluint iField=0; iField<fields.size(); ++iField) {
        multiBlocks[iField] = dynamic_cast<MultiBlock3D*>(fields[iField]);
    }
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, multiBlocks );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveDotProcessing3D_L ******************************************* */

template<typename T, template<typename U> class Descriptor>
void applyProcessingFunctional(ReductiveDotProcessingFunctional3D_L<T,Descriptor>& functional,
                               DotList3D const& dotList,
                               MultiBlockLattice3D<T,Descriptor>& lattice)
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, lattice );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveDotProcessing3D_S ******************************************* */

template<typename T>
void applyProcessingFunctional(ReductiveDotProcessingFunctional3D_S<T>& functional,
                               DotList3D const& dotList, MultiScalarField3D<T>& field)
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveDotProcessing3D_T ******************************************* */

template<typename T, int nDim>
void applyProcessingFunctional(ReductiveDotProcessingFunctional3D_T<T,nDim>& functional,
                               DotList3D const& dotList,
                               MultiTensorField3D<T,nDim>& field)
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveDotProcessing3D_N ******************************************* */

template<typename T>
void applyProcessingFunctional(ReductiveDotProcessingFunctional3D_N<T>& functional,
                               DotList3D const& dotList,
                               MultiNTensorField3D<T>& field)
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveDotProcessing3D_LL******************************************* */

template<typename T1, template<typename U1> class Descriptor1,
         typename T2, template<typename U2> class Descriptor2>
void applyProcessingFunctional (
        ReductiveDotProcessingFunctional3D_LL<T1,Descriptor1,T2,Descriptor2>& functional,
        DotList3D const& dotList,
        MultiBlockLattice3D<T1,Descriptor1>& lattice1,
        MultiBlockLattice3D<T2,Descriptor2>& lattice2 )
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, lattice1, lattice2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveDotProcessing3D_SS ****************************************** */

template<typename T1, typename T2>
void applyProcessingFunctional (
        ReductiveDotProcessingFunctional3D_SS<T1,T2>& functional,
        DotList3D const& dotList,
        MultiScalarField3D<T1>& field1,
        MultiScalarField3D<T2>& field2 )
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, field1, field2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveDotProcessing3D_TT ****************************************** */

template<typename T1, int nDim1, typename T2, int nDim2>
void applyProcessingFunctional (
        ReductiveDotProcessingFunctional3D_TT<T1,nDim1,T2,nDim2>& functional,
        DotList3D const& dotList,
        MultiTensorField3D<T1,nDim1>& field1,
        MultiTensorField3D<T2,nDim2>& field2 )
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, field1, field2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveDotProcessing3D_NN ****************************************** */

template<typename T1, typename T2>
void applyProcessingFunctional (
        ReductiveDotProcessingFunctional3D_NN<T1,T2>& functional,
        DotList3D const& dotList,
        MultiNTensorField3D<T1>& field1,
        MultiNTensorField3D<T2>& field2 )
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, field1, field2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveDotProcessing3D_ST ****************************************** */

template<typename T1, typename T2, int nDim>
void applyProcessingFunctional(ReductiveDotProcessingFunctional3D_ST<T1,T2,nDim>& functional,
                               DotList3D const& dotList,
                               MultiScalarField3D<T1>& field1,
                               MultiTensorField3D<T2,nDim>& field2 )
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, field1, field2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveDotProcessing3D_SN ****************************************** */

template<typename T1, typename T2>
void applyProcessingFunctional(ReductiveDotProcessingFunctional3D_SN<T1,T2>& functional,
                               DotList3D const& dotList,
                               MultiScalarField3D<T1>& field1,
                               MultiNTensorField3D<T2>& field2 )
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, field1, field2 );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveDotProcessing3D_LS ****************************************** */

template<typename T1, template<typename U> class Descriptor, typename T2>
void applyProcessingFunctional (
        ReductiveDotProcessingFunctional3D_LS<T1,Descriptor,T2>& functional,
        DotList3D const& dotList,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiScalarField3D<T2>& field )
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, lattice, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}

/* *************** ReductiveDotProcessing3D_LT ****************************************** */

template<typename T1, template<typename U> class Descriptor, typename T2, int nDim>
void applyProcessingFunctional (
        ReductiveDotProcessingFunctional3D_LT<T1,Descriptor,T2,nDim>& functional,
        DotList3D const& dotList,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiTensorField3D<T2,nDim>& field )
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, lattice, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** ReductiveDotProcessing3D_LN ****************************************** */

template<typename T1, template<typename U> class Descriptor, typename T2>
void applyProcessingFunctional (
        ReductiveDotProcessingFunctional3D_LN<T1,Descriptor,T2>& functional,
        DotList3D const& dotList,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiNTensorField3D<T2>& field )
{
    ReductiveDotProcessorGenerator3D generator(functional.clone(), dotList);
    executeDataProcessor( generator, lattice, field );
    functional.getStatistics() = generator.getFunctional().getStatistics();
}


/* *************** BoundedReductiveLatticeBoxProcessing3D **************************** */

template<typename T, template<typename U> class Descriptor>
void applyProcessingFunctional (
        BoundedReductiveLatticeBoxProcessingFunctional3D<T,Descriptor>& functional,
        Box3D domain,
        std::vector<MultiBlockLattice3D<T,Descriptor>*> lattices,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(lattices.size());
    for (pluint iLattice=0; iLattice<lattices.size(); ++iLattice) {
        multiBlocks[iLattice] = dynamic_cast<MultiBlock3D*>(lattices[iLattice]);
    }
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}


/* *************** BoundedReductiveMultiScalarFieldBoxProcessing3D ************************ */

template<typename T>
void applyProcessingFunctional (
        BoundedReductiveScalarFieldBoxProcessingFunctional3D<T>& functional,
        Box3D domain,
        std::vector<MultiScalarField3D<T>*> fields,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(fields.size());
    for (pluint iField=0; iField<fields.size(); ++iField) {
        multiBlocks[iField] = dynamic_cast<MultiBlock3D*>(fields[iField]);
    }
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}


/* *************** BoundedReductiveMultiTensorFieldBoxProcessing3D ************************ */

template<typename T, int nDim>
void applyProcessingFunctional (
        BoundedReductiveTensorFieldBoxProcessingFunctional3D<T,nDim>& functional,
        Box3D domain,
        std::vector<MultiTensorField3D<T,nDim>*> fields, plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(fields.size());
    for (pluint iField=0; iField<fields.size(); ++iField) {
        multiBlocks[iField] = dynamic_cast<MultiBlock3D*>(fields[iField]);
    }
    applyProcessingFunctional(functional, domain,
                              multiBlocks, boundaryWidth);
}

/* *************** BoundedReductiveMultiNTensorFieldBoxProcessing3D ************************ */

template<typename T>
void applyProcessingFunctional (
        BoundedReductiveNTensorFieldBoxProcessingFunctional3D<T>& functional,
        Box3D domain,
        std::vector<MultiNTensorField3D<T>*> fields, plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(fields.size());
    for (pluint iField=0; iField<fields.size(); ++iField) {
        multiBlocks[iField] = dynamic_cast<MultiBlock3D*>(fields[iField]);
    }
    applyProcessingFunctional(functional, domain,
                              multiBlocks, boundaryWidth);
}

/* *************** BoundedReductiveBoxProcessing3D_L ********************************* */

template<typename T, template<typename U> class Descriptor>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_L<T,Descriptor>& functional,
        Box3D domain, MultiBlockLattice3D<T,Descriptor>& lattice, plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(1);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&lattice);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}


/* *************** BoundedReductiveBoxProcessing3D_S ********************************* */

template<typename T>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_S<T>& functional,
        Box3D domain, MultiScalarField3D<T>& field, plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(1);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}

/* *************** BoundedReductiveBoxProcessing3D_T ********************************* */

template<typename T, int nDim>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_T<T,nDim>& functional,
        Box3D domain, MultiTensorField3D<T,nDim>& field, plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(1);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}

/* *************** BoundedReductiveBoxProcessing3D_N ********************************* */

template<typename T>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_N<T>& functional,
        Box3D domain, MultiNTensorField3D<T>& field, plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(1);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}

/* *************** BoundedMaskedReductiveBoxProcessing3D_N ********************************* */

template<typename T>
void applyProcessingFunctional (
        BoundedMaskedReductiveBoxProcessingFunctional3D_N<T>& functional,
        Box3D domain,
        MultiNTensorField3D<T>& field,
        MultiNTensorField3D<int>& mask,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&mask);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}

/* *************** BoundedReductiveBoxProcessing3D_LL********************************* */

template<typename T1, template<typename U1> class Descriptor1,
         typename T2, template<typename U2> class Descriptor2>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_LL<T1,Descriptor1,T2,Descriptor2>& functional,
        Box3D domain,
        MultiBlockLattice3D<T1,Descriptor1>& lattice1,
        MultiBlockLattice3D<T2,Descriptor2>& lattice2,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&lattice1);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&lattice2);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}


/* *************** BoundedReductiveBoxProcessing3D_SS ****************************************** */

template<typename T1, typename T2>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_SS<T1,T2>& functional,
        Box3D domain,
        MultiScalarField3D<T1>& field1,
        MultiScalarField3D<T2>& field2,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field1);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field2);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}

/* *************** BoundedReductiveBoxProcessing3D_TT ********************************** */

template<typename T1, int nDim1, typename T2, int nDim2>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_TT<T1,nDim1,T2,nDim2>& functional,
        Box3D domain,
        MultiTensorField3D<T1,nDim1>& field1,
        MultiTensorField3D<T2,nDim2>& field2,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field1);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field2);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}


/* *************** BoundedReductiveBoxProcessing3D_NN ********************************** */

template<typename T1, typename T2>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_NN<T1,T2>& functional,
        Box3D domain,
        MultiNTensorField3D<T1>& field1,
        MultiNTensorField3D<T2>& field2,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field1);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field2);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}


/* *************** BoundedMaskedReductiveBoxProcessing3D_NN ********************************** */

template<typename T1, typename T2>
void applyProcessingFunctional (
        BoundedMaskedReductiveBoxProcessingFunctional3D_NN<T1,T2>& functional,
        Box3D domain,
        MultiNTensorField3D<T1>& field1,
        MultiNTensorField3D<T2>& field2,
        MultiNTensorField3D<int>& mask,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(3);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field1);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field2);
    multiBlocks[2] = dynamic_cast<MultiBlock3D*>(&mask);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}


/* *************** BoundedReductiveBoxProcessing3D_ST ******************************** */

template<typename T1, typename T2, int nDim>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_ST<T1,T2,nDim>& functional,
        Box3D domain,
        MultiScalarField3D<T1>& field1,
        MultiTensorField3D<T2,nDim>& field2,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field1);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field2);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}


/* *************** BoundedReductiveBoxProcessing3D_SN ******************************** */

template<typename T1, typename T2>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_SN<T1,T2>& functional,
        Box3D domain,
        MultiScalarField3D<T1>& field1,
        MultiNTensorField3D<T2>& field2,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&field1);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field2);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}


/* *************** BoundedReductiveBoxProcessing3D_LS ******************************** */

template<typename T1, template<typename U> class Descriptor, typename T2>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_LS<T1,Descriptor,T2>& functional,
        Box3D domain,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiScalarField3D<T2>& field,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&lattice);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}

/* *************** BoundedReductiveBoxProcessing3D_LT ****************************************** */

template<typename T1, template<typename U> class Descriptor, typename T2, int nDim>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_LT<T1,Descriptor,T2,nDim>& functional,
        Box3D domain,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiTensorField3D<T2,nDim>& field,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&lattice);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}

/* *************** BoundedReductiveBoxProcessing3D_LN ****************************************** */

template<typename T1, template<typename U> class Descriptor, typename T2>
void applyProcessingFunctional (
        BoundedReductiveBoxProcessingFunctional3D_LN<T1,Descriptor,T2>& functional,
        Box3D domain,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiNTensorField3D<T2>& field,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&lattice);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}

/* *************** BoundedReductiveBoxProcessing3D_LN ****************************************** */

template<typename T1, template<typename U> class Descriptor, typename T2>
void applyProcessingFunctional (
        BoundedMaskedReductiveBoxProcessingFunctional3D_LN<T1,Descriptor,T2>& functional,
        Box3D domain,
        MultiBlockLattice3D<T1,Descriptor>& lattice,
        MultiNTensorField3D<T2>& field,
        MultiNTensorField3D<int>& mask,
        plint boundaryWidth )
{
    std::vector<MultiBlock3D*> multiBlocks(2);
    multiBlocks[0] = dynamic_cast<MultiBlock3D*>(&lattice);
    multiBlocks[1] = dynamic_cast<MultiBlock3D*>(&field);
    multiBlocks[2] = dynamic_cast<MultiBlock3D*>(&mask);
    applyProcessingFunctional(functional, domain, multiBlocks, boundaryWidth);
}

}  // namespace plb

#endif  // REDUCTIVE_MULTI_DATA_PROCESSOR_WRAPPER_3D_HH
