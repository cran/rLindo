\name{rLSsetModelDouParameter}
\alias{rLSsetModelDouParameter}

\title{Set a double precision parameter for a specified model.}

\description{
 R interface function for LINDO API function \code{LSsetModelDouParameter}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsetModelDouParameter(model,nParameter,dValue)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nParameter}{An integer referring to a double precision parameter.}
 \item{dValue}{A double precision value.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
