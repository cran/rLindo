\name{rLSsetDistrParamRG}
\alias{rLSsetDistrParamRG}

\title{Set distribution parameters.}

\description{
 R interface function for LINDO API function \code{LSsetDistrParamRG}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSsetDistrParamRG(rg,iParam,dParam)
}

\arguments{
 \item{rg}{A LINDO API random generator object, returned by \code{\link{rLScreateRG}}.}
 \item{iParam}{A parameter index.}
 \item{dParam}{A parameter value.}
}

\value{
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
