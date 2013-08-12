\name{rLSgetNLPObjectiveData}
\alias{rLSgetNLPObjectiveData}

\title{Get the NLP data of the Objective.}

\description{
 R interface function for LINDO API function \code{LSgetNLPObjectiveData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetNLPObjectiveData(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnNLPobjnnz}{Number of NLP nonzeros in objective.}
 \item{paiNLPobj}{An integer array containing the column indices for NLP elements in the objective.}
 \item{padNLPobj}{A double array containing NLP row values for NLP elements in the objective.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetNLPData}}
}
