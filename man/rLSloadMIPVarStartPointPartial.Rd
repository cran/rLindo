\name{rLSloadMIPVarStartPointPartial}
\alias{rLSloadMIPVarStartPointPartial}

\title{Load a partial MIP initial point for MIP/MINLP models.}

\description{
 R interface function for LINDO API function \code{LSloadMIPVarStartPointPartial}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadMIPVarStartPointPartial(model,nCols,paiCols,paiPrimal)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCols}{Number of variables in the partial solution.}
 \item{paiCols}{An integer array containing the indicies of variables in the partial solution.}
 \item{paiPrimal}{An integer array containing starting values for each variable in the given model.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadMIPVarStartPoint}}
}
