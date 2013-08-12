\name{rLSmodifyObjective}
\alias{rLSmodifyObjective}

\title{Modify selected objective coefficients of a given model.}

\description{
 R interface function for LINDO API function \code{LSmodifyObjective}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSmodifyObjective(model,nVars,paiVars,padC)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nVars}{Number of objective coefficients to modify.}
 \item{paiVars}{An integer array containing the indices of the objective coefficients to modify.}
 \item{padC}{A double array containing the new values for the modified objective coefficients.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

