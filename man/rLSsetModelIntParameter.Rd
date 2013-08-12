\name{rLSsetModelIntParameter}
\alias{rLSsetModelIntParameter}

\title{Set an integer parameter for a specified model.}

\description{
 R interface function for LINDO API function \code{LSsetModelIntParameter}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSsetModelIntParameter(model,nParameter,nValue)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nParameter}{An integer referring to an integer precision parameter.}
 \item{nValue}{An integer precision value.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSsetModelDouParameter}}
}