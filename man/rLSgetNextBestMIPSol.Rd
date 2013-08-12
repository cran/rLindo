\name{rLSgetNextBestMIPSol}
\alias{rLSgetNextBestMIPSol}

\title{Generate the next best (in terms of objective value) 
       solution for the current mixed integer model.}

\description{
 R interface function for LINDO API function \code{LSgetNextBestMIPSol}. For more information,
 please refer to LINDO API User Manual.
}

\details{
 Repeated calls to \code{rLSgetNextBestMIPSol} will allow one to generate the so-called
 K-Best solutions to mixed-integer model. This is useful for revealing alternate optima.
}

\usage{
  rLSgetNextBestMIPSol(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnStatus}{The status on the new, next-best solution.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}


