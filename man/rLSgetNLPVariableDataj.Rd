\name{rLSgetNLPVariableDataj}
\alias{rLSgetNLPVariableDataj}

\title{Get data about the nonlinear structure of a specific column of the model.}

\description{
 R interface function for LINDO API function \code{LSgetNLPVariableDataj}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetNLPVariableDataj(model,iVar)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iVar}{Index of the variable you wish to receive information on.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnNnz}{Number of nonlinear nonzeros in column j.}
 \item{panNLProws}{An integer array containing the row indices of the nonlinear nonzeros in the jth column of the constraint matrix.}
 \item{padNLPcoef}{A double array containing the current values of the nonzero coefficients in the jth column of the coefficient 
                  (Jacobian) matrix with respect to the last primal solution computed during the iterations.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetNLPData}}
}
