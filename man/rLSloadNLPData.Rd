\name{rLSloadNLPData}
\alias{rLSloadNLPData}

\title{Load a nonlinear program's data into the model data structure.}

\description{
 R interface function for LINDO API function \code{LSloadNLPData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadNLPData(model,paiNLPcols,panNLPcols,padNLPcoef = NULL,paiNLProws,
               nNLPobj,paiNLPobj,padNLPobj = NULL)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{paiNLPcols}{An integer array containing the index of the first nonlinear nonzero in each column.}
 \item{panNLPcols}{An integer array containing the number of nonlinear elements in each column.}
 \item{padNLPcoef}{A double array containing initial values of the nonzero coefficients in the (Jacobian) matrix.}
 \item{paiNLProws}{An integer array containing the row indices of the nonlinear elements.}
 \item{nNLPobj}{The number of nonlinear variables in the objective.}
 \item{paiNLPobj}{An integer array containing the column indices of nonlinear variables in the objective function.}
 \item{padNLPobj}{A double array containing the initial nonzero coefficients in the objective.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
