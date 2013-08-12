\name{rLSloadBlockStructure}
\alias{rLSloadBlockStructure}

\title{Provide a block structure for the constraint matrix by specifying 
       block memberships of each variable and constraint.}

\description{
 R interface function for LINDO API function \code{LSloadBlockStructure}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadBlockStructure(model,nBlock,panRblock,panCblock,nType)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nBlock}{The name of the file from which to read the starting values.}
 \item{panRblock}{An integer array in which information about the block membership of the constraints is placed.}
 \item{panCblock}{An integer array in which information about the block membership of the variables is placed.}
 \item{nType}{The type of decomposition loaded. The possible values are identified with the following macros:
                \itemize{
                   \item{LS_LINK_BLOCKS_COLS}{The decomposed model has dual angular structure (linking columns).}
                   \item{LS_LINK_BLOCKS_ROWS}{The decomposed model has block angular structure (linking rows).}
                   \item{LS_LINK_BLOCKS_BOTH}{The decomposed model has both dual and block angular structure (linking rows and columns).}
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

\seealso{
\code{\link{rLSloadVarStartPoint}}
}
