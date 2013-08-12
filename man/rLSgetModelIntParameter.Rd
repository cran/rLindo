\name{rLSgetModelIntParameter}
\alias{rLSgetModelIntParameter}

\title{Retrieves a integer precision parameter for a specified model.}

\description{
 R interface function for LINDO API function \code{LSgetModelIntParameter}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSgetModelIntParameter(model,nParameter)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nParameter}{An integer referring to an integer precision parameter.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnValue}{The parameter's value.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetModelDouParameter}}
}