\name{rLSgetNLPConstraintDatai}
\alias{rLSgetNLPConstraintDatai}

\title{Get data about the nonlinear structure of a specific row of the model.}

\description{
 R interface function for LINDO API function \code{LSgetNLPConstraintDatai}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetNLPConstraintDatai(model,iCon)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iCon}{Index of the constraint you wish to receive information on.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnNnz}{Number of nonlinear nonzeros in constraint i.}
 \item{paiNLPcols}{An integer array containing the column indices of the nonlinear nonzeros in the ith row of the constraint matrix.}
 \item{padNLPcoef}{A double array containing the current values of the nonzero coefficients in the ith row of the coefficient (Jacobian) matrix.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetNLPData}}
}
