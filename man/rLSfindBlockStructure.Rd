\name{rLSfindBlockStructure}
\alias{rLSfindBlockStructure}

\title{Examine the nonzero structure of the constraint matrix and tries to identify block structures in the model.}

\description{
 R interface function for LINDO API function \code{LSfindBlockStructure}. For more information,
 please refer to LINDO API User Manual.
}

\details{
    If neither linking rows nor linking columns exist, then the model is called
    'totally decomposable'. Unless total decomposition is requested, the user should specify as
    an input the number of blocks to decompose the matrix into.
}

\usage{
  rLSfindBlockStructure(model,nBlock,nType)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nBlock}{Number of blocks to decompose the coefficient matrix into.}
 \item{nType}{Type of decomposition requested. The possible values are identified with the following macros:
                 \itemize{            
                    \item{LS_LINK_BLOCKS_NONE}{Try total decomposition (no linking rows or columns).}
                    \item{LS_LINK_BLOCKS_COLS}{The decomposed model will have dual angular structure (linking columns).}
                    \item{LS_LINK_BLOCKS_ROWS}{The decomposed model will have block angular structure (linking rows).}
                    \item{LS_LINK_BLOCKS_BOTH}{The decomposed model will have both dual and block angular structure (linking rows and columns).}
                    \item{LS_LINK_BLOCKS_FREE}{Solver decides which type of decomposition to use.}
                  }
               }
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
