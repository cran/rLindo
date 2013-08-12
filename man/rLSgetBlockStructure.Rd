\name{rLSgetBlockStructure}
\alias{rLSgetBlockStructure}

\title{Retrieve the block structure information.}

\description{
 R interface function for LINDO API function \code{LSgetBlockStructure}. For more information,
 please refer to LINDO API User Manual.
}

\details{
   Following a call to LSfindBlockStructure().
}

\usage{
  rLSgetBlockStructure(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnBlock}{Number of blocks to decompose the model matrix into.}
 \item{panRblock}{An integer array containing information about the block membership of the constraints.}
 \item{panCblock}{An integer array containing information about the block membership of the variables.}
 \item{pnType}{Type of the decomposition.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSfindBlockStructure}}
}