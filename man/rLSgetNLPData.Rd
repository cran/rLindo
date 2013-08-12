\name{rLSgetNLPData}
\alias{rLSgetNLPData}

\title{Get data about the nonlinear structure of a model.}

\description{
 R interface function for LINDO API function \code{LSgetNLPData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetNLPData(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{paiNLPcols}{An integer array containing the index of the first nonlinear nonzero in each column.}
 \item{panNLPcols}{An integer array containing the number of nonlinear elements in each column.}
 \item{padNLPcoef}{A double array containing the current values of the nonzero coefficients in the (Jacobian) matrix.}
 \item{paiNLProws}{An integer array containing the row indices of the nonlinear nonzeros in the coefficient matrix.}
 \item{pnNLPobj}{Number of nonlinear variables in the objective function.}
 \item{paiNLPobj}{An integer array containing column indices of the nonlinear terms in the objective.}
 \item{padNLPobj}{A double array containing the current partial derivatives of the objective corresponding to the variables in paiNLPobj.}
 \item{pachNLPConTypes}{A character array whose elements indicate whether a constraint has nonlinear terms or not.If
                        \code{pachNLPConTypes[i]} > 0, then constraint i has nonlinear terms.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadNLPData}}
}
